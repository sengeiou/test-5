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
#include <stdbool.h>
#include <image_util.h>
#include <storage.h>
#include <glib.h>
#include "tct_common.h"
#include "utc-image-util-common.h"

#define API_NAMESPACE			"[IMAGE-UTIL]"

#define WRONG_PATH ""

#define UTC_IMAGE_TYPE_N		IMAGE_UTIL_JPEG_XL
#define INVALID_IMAGE_TYPE		(UTC_IMAGE_TYPE_N * 2)

typedef struct {
	const char *decode_test;
	const char *encode_test;
	bool compression;
	bool lossless;
} utc_validator_t;

static const utc_validator_t UTC_CONFIG[] = {
	[IMAGE_UTIL_JPEG] = { "sample.jpg", "test_output.jpg", false, false },
	[IMAGE_UTIL_PNG] = { "sample.png", "test_output.png", true, false },
	[IMAGE_UTIL_GIF] = { "sample.gif", "test_output.gif", false, false },
	[IMAGE_UTIL_BMP] = { "sample.bmp", "test_output.bmp", false, false },
	[IMAGE_UTIL_WEBP] = { "sample.webp", "test_output.webp", false, true },
	[IMAGE_UTIL_HEIF] = { "sample.heic", NULL, false, false },
	[IMAGE_UTIL_JPEG_XL] = { "sample.jxl", "test_output.jxl", false, true },
};

typedef struct {
	unsigned char *buffer;
	size_t size;
	unsigned int width;
	unsigned int height;
} decode_result_t;

typedef struct {
	char *source;
	image_util_decode_h handle;
	image_util_image_h decoded;
	decode_result_t result;
} utc_decode_t;

static utc_decode_t utc_decode[] = {
	[IMAGE_UTIL_JPEG] = { NULL, NULL, NULL, { NULL, 0, 0, 0 } },
	[IMAGE_UTIL_PNG] = { NULL, NULL, NULL, { NULL, 0, 0, 0 } },
	[IMAGE_UTIL_GIF] = { NULL, NULL, NULL, { NULL, 0, 0, 0 } },
	[IMAGE_UTIL_BMP] = { NULL, NULL, NULL, { NULL, 0, 0, 0 } },
	[IMAGE_UTIL_WEBP] = { NULL, NULL, NULL, { NULL, 0, 0, 0 } },
	[IMAGE_UTIL_HEIF] = { NULL, NULL, NULL, { NULL, 0, 0, 0 } },
	[IMAGE_UTIL_JPEG_XL] = { NULL, NULL, NULL, { NULL, 0, 0, 0 } },
};

typedef struct {
	unsigned char *buffer;
	unsigned long long size;
	size_t buffer_size;
} encode_result_t;

typedef struct {
	char *output;
	image_util_encode_h handle;
	encode_result_t result;
} utc_encode_t;

static utc_encode_t utc_encode[] = {
	[IMAGE_UTIL_JPEG] = { NULL, NULL, { NULL, 0, 0 } },
	[IMAGE_UTIL_PNG] = { NULL, NULL, { NULL, 0, 0 } },
	[IMAGE_UTIL_GIF] = { NULL, NULL, { NULL, 0, 0 } },
	[IMAGE_UTIL_BMP] = { NULL, NULL, { NULL, 0, 0 } },
	[IMAGE_UTIL_WEBP] = { NULL, NULL, { NULL, 0, 0 } },
	[IMAGE_UTIL_HEIF] = { NULL, NULL, { NULL, 0, 0 } },
	[IMAGE_UTIL_JPEG_XL] = { NULL, NULL, { NULL, 0, 0, 0 } },
};

static int callback_error = IMAGE_UTIL_ERROR_NONE;

static GMainLoop *g_image_util_mainloop = NULL;

static gboolean timeout_func(gpointer data)
{
	fprintf(stderr, "Timeout! Test case failed!\n");
	g_main_loop_quit((GMainLoop *) data);
	return FALSE;
}

static void wait_for_async()
{
	int timeout_id = 0;
	g_image_util_mainloop = g_main_loop_new(NULL, FALSE);

	timeout_id = g_timeout_add(5000, timeout_func, g_image_util_mainloop);
	g_main_loop_run(g_image_util_mainloop);
	g_source_remove(timeout_id);
	g_main_loop_unref(g_image_util_mainloop);
	g_image_util_mainloop = NULL;
}

static void _signal()
{
	fprintf(stderr, "===> send signal to test proc \n");
	if (g_image_util_mainloop != NULL)
		g_main_loop_quit(g_image_util_mainloop);
}

static void utc_decode_completed_cb(int error, void *user_param, unsigned long width, unsigned long height, unsigned long long size)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	callback_error = error;
	_signal();
}

static void utc_decode_completed2_cb(int error_code, image_util_image_h image, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	callback_error = error_code;
	_signal();

	return;
}

static void utc_encode_completed_cb(int error, void *user_param, unsigned long long size)
{
	callback_error = error;
	_signal();
}

static void utc_encode_to_file_completed_cb(image_util_error_e error, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	callback_error = error;
	_signal();
}

static void utc_encode_to_buffer_completed_cb(image_util_error_e error, unsigned char *buffer, size_t buffer_size, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);
	encode_result_t *buf_enc = (encode_result_t *)user_data;

	callback_error = error;

	if (buf_enc) {
		buf_enc->buffer = g_memdup(buffer, buffer_size);
		buf_enc->buffer_size = buffer_size;
	}

	_signal();
}

static int __fill_test_buffer(image_util_type_e type)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_image_h decoded_image = NULL;
	GError *error = NULL;

	ret = _utc_decode_from_file(utc_decode[type].source, &decoded_image);
	if (ret != IMAGE_UTIL_ERROR_NONE) {
		FPRINTF("[%d:%s] _utc_decode_from_file failed! %d \\n", __LINE__, __FUNCTION__, ret);
		return ret;
	}

	ret = image_util_get_image(decoded_image, &utc_decode[type].result.width, &utc_decode[type].result.height, NULL,
								&utc_decode[type].result.buffer, &utc_decode[type].result.size);
	if (ret != IMAGE_UTIL_ERROR_NONE) {
		FPRINTF("[%d:%s] image_util_get_image failed! %d \\n", __LINE__, __FUNCTION__, ret);
		image_util_destroy_image(decoded_image);
		return ret;
	}

	FPRINTF("[%d:%s] decode[%d] buffer: %zu \\n", __LINE__, __FUNCTION__, type, utc_decode[type].result.size);

	if (!g_file_get_contents(utc_decode[type].source, &utc_encode[type].result.buffer, &utc_encode[type].result.size, &error)) {
		FPRINTF("[%d:%s] g_file_get_contents failed! %s \\n", __LINE__, __FUNCTION__, (error ? error->message : "none"));
		if (error)
			g_error_free(error);
		ret = IMAGE_UTIL_ERROR_INVALID_PARAMETER;
	}

	FPRINTF("[%d:%s] encode[%d] buffer: %zu \\n", __LINE__, __FUNCTION__, type, utc_encode[type].result.size);

	image_util_destroy_image(decoded_image);

	return ret;
}

static void __utc_decode_free()
{
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		IMAGEUTIL_SAFE_G_FREE(utc_decode[type].result.buffer);
		utc_decode[type].result.size = 0;
		image_util_destroy_image(utc_decode[type].decoded);
		utc_decode[type].decoded = NULL;
		IMAGEUTIL_SAFE_G_FREE(utc_decode[type].source);
		image_util_decode_destroy(utc_decode[type].handle);
		utc_decode[type].handle = NULL;
	}
}

static void __utc_encode_free()
{
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		IMAGEUTIL_SAFE_G_FREE(utc_encode[type].result.buffer);
		utc_encode[type].result.size = 0;
		utc_encode[type].result.buffer_size = 0;
		IMAGEUTIL_SAFE_G_FREE(utc_encode[type].output);
		image_util_encode_destroy(utc_encode[type].handle);
		utc_encode[type].handle = NULL;
	}
}

/**
 * @function		utc_image_util_decode_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_image_util_decode_startup(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);

		for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
			if (!UTC_CONFIG[type].decode_test) {
				FPRINTF("[%d:%s] PATH [Type: %d] [Decode: not support] \\n", __LINE__, __FUNCTION__, type);
				continue;
			}

			utc_decode[type].source = _utc_get_test_path(pszValue, UTC_CONFIG[type].decode_test);
			FPRINTF("[%d:%s] PATH [Type: %d] [Decode: %s] \\n", __LINE__, __FUNCTION__, type, utc_decode[type].source);

			if (!utc_decode[type].source) {
				FPRINTF("[%d:%s] Get UTC Path error! \\n", __LINE__, __FUNCTION__);
				return;
			}

			if (!UTC_CONFIG[type].encode_test) {
				FPRINTF("[%d:%s] PATH [Type: %d] [Encode: not support] \\n", __LINE__, __FUNCTION__, type);
				continue;
			}

			utc_encode[type].output = _utc_get_test_path(pszValue, UTC_CONFIG[type].encode_test);
			FPRINTF("[%d:%s] PATH [Type: %d] [Encode: %s] \\n", __LINE__, __FUNCTION__, type, utc_encode[type].output);

			if (!utc_encode[type].output) {
				FPRINTF("[%d:%s] Get UTC Path error! \\n", __LINE__, __FUNCTION__);
				return;
			}
		}
	}
	else
	{
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].decode_test)
			continue;

		ret = image_util_decode_create(&utc_decode[type].handle);
		if (IMAGE_UTIL_ERROR_NONE != ret)
			PRINT_UTC_LOG("[Line : %d][%s] image_util_decode_create is failed(%d).\n", __LINE__, API_NAMESPACE, ret);
	}

}

/**
 * @function		utc_image_util_decode_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_image_util_decode_cleanup(void)
{
	__utc_decode_free();
	__utc_encode_free();
}

static bool _image_util_supported_colorspace_cb(image_util_colorspace_e colorspace, void *user_data)
{
	return false;
}

/**
 * @testcase		utc_image_util_foreach_supported_colorspace_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_foreach_supported_colorspace
 */
int utc_image_util_foreach_supported_colorspace_n1(void)
{
	int ret = image_util_foreach_supported_colorspace(IMAGE_UTIL_JPEG, NULL, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_image_util_foreach_supported_colorspace_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_foreach_supported_colorspace
 */
int utc_image_util_foreach_supported_colorspace_n2(void)
{
	int ret = image_util_foreach_supported_colorspace(-1, _image_util_supported_colorspace_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_foreach_supported_colorspace(INVALID_IMAGE_TYPE, _image_util_supported_colorspace_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_foreach_supported_colorspace_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_foreach_supported_colorspace
 */
int utc_image_util_foreach_supported_colorspace_p(void)
{
	int ret = image_util_foreach_supported_colorspace(IMAGE_UTIL_JPEG, _image_util_supported_colorspace_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_image_util_decode_create_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_create
 */
int utc_image_util_decode_create_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_decode_create(NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_decode_create_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_decode_create
 */
int utc_image_util_decode_create_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_destroy(utc_decode[type].handle);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		utc_decode[type].handle = NULL;

		ret = image_util_decode_create(&utc_decode[type].handle);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_input_path_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_input_path
 */
int utc_image_util_decode_set_input_path_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_input_path(NULL, utc_decode[type].source);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_input_path_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_input_path
 */
int utc_image_util_decode_set_input_path_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_input_path(utc_encode[type].handle, utc_decode[type].source);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_input_path_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_input_path
 */
int utc_image_util_decode_set_input_path_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_input_path(utc_decode[type].handle, WRONG_PATH);
		assert_eq(ret, IMAGE_UTIL_ERROR_NO_SUCH_FILE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_input_path_n4
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_input_path
 */
int utc_image_util_decode_set_input_path_n4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_input_path(utc_decode[type].handle, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_NO_SUCH_FILE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_input_path_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_decode_set_input_path
 */
int utc_image_util_decode_set_input_path_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_input_path(utc_decode[type].handle, utc_decode[type].source);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_input_buffer_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_input_buffer
 */
int utc_image_util_decode_set_input_buffer_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_input_buffer(NULL, utc_encode[type].result.buffer, utc_encode[type].result.size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_input_buffer_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_input_buffer
 */
int utc_image_util_decode_set_input_buffer_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_input_buffer(utc_encode[type].handle, utc_encode[type].result.buffer, utc_encode[type].result.size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_input_buffer_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_input_buffer
 */
int utc_image_util_decode_set_input_buffer_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_input_buffer(utc_decode[type].handle, NULL, utc_encode[type].result.size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_input_buffer_n4
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_input_buffer
 */
int utc_image_util_decode_set_input_buffer_n4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_input_buffer(utc_decode[type].handle, utc_encode[type].result.buffer, 0);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_input_buffer_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_decode_set_input_buffer
 */
int utc_image_util_decode_set_input_buffer_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_input_buffer(utc_decode[type].handle, utc_encode[type].result.buffer, utc_encode[type].result.size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_output_buffer_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_output_buffer
 */
int utc_image_util_decode_set_output_buffer_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;

	ret = image_util_decode_set_output_buffer(NULL, &data);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_output_buffer_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_output_buffer
 */
int utc_image_util_decode_set_output_buffer_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_output_buffer(utc_encode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_output_buffer_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_output_buffer
 */
int utc_image_util_decode_set_output_buffer_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_output_buffer(utc_decode[type].handle, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_output_buffer_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_decode_set_output_buffer
 */
int utc_image_util_decode_set_output_buffer_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_output_buffer(utc_decode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

static int jpeg_colorspace_tbl[] = {
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_YUV420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV422 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_I420 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_NV12 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_UYVY */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUYV */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB565 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_RGB888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_ARGB8888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_BGRA8888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_RGBA8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_BGRX8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV21 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV16 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV61 */
};

static int png_colorspace_tbl[] = {
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV422 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_I420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV12 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_UYVY */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUYV */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB565 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_ARGB8888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_BGRA8888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_RGBA8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_BGRX8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV21 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV16 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV61 */
};

static int gif_colorspace_tbl[] = {
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV422 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_I420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV12 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_UYVY */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUYV */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB565 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_ARGB8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_BGRA8888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_RGBA8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_BGRX8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV21 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV16 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV61 */
};

static int bmp_colorspace_tbl[] = {
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV422 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_I420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV12 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_UYVY */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUYV */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB565 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_ARGB8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_BGRA8888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_RGBA8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_BGRX8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV21 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV16 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV61 */
};

/**
 * @testcase		utc_image_util_decode_set_colorspace_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_colorspace
 */
int utc_image_util_decode_set_colorspace_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_decode_set_colorspace(NULL, IMAGE_UTIL_COLORSPACE_RGBA8888);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_colorspace_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_colorspace
 */
int utc_image_util_decode_set_colorspace_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_colorspace(utc_decode[type].handle, IMAGE_UTIL_COLORSPACE_RGBA8888);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_colorspace_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_colorspace
 */
int utc_image_util_decode_set_colorspace_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_input_path(utc_decode[type].handle, utc_decode[type].source);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_colorspace(utc_decode[type].handle, -1);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_decode_set_colorspace(utc_decode[type].handle, IMAGE_UTIL_COLORSPACE_NV61 + 1);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_colorspace_n4
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_colorspace
 */
int utc_image_util_decode_set_colorspace_n4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	int color_space = IMAGE_UTIL_COLORSPACE_YV12;

	ret = image_util_decode_set_input_path(utc_decode[IMAGE_UTIL_JPEG].handle, utc_decode[IMAGE_UTIL_JPEG].source);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	for (color_space = IMAGE_UTIL_COLORSPACE_YV12; color_space <= IMAGE_UTIL_COLORSPACE_NV61; color_space++) {
		if (jpeg_colorspace_tbl[color_space] == IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT) {
			ret = image_util_decode_set_colorspace(utc_decode[IMAGE_UTIL_JPEG].handle, color_space);
			assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);
		}
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_colorspace_n5
 * @since_tizen		6.0
 * @description		Negative test case for image_util_decode_set_colorspace
 */
int utc_image_util_decode_set_colorspace_n5(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	int color_space = IMAGE_UTIL_COLORSPACE_YV12;

	ret = image_util_decode_set_input_path(utc_decode[IMAGE_UTIL_PNG].handle, utc_decode[IMAGE_UTIL_PNG].source);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	for (color_space = IMAGE_UTIL_COLORSPACE_YV12; color_space <= IMAGE_UTIL_COLORSPACE_NV61; color_space++) {
		if (png_colorspace_tbl[color_space] == IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT) {
			ret = image_util_decode_set_colorspace(utc_decode[IMAGE_UTIL_PNG].handle, color_space);
			assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);
		}
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_colorspace_n6
 * @since_tizen		6.0
 * @description		Negative test case for image_util_decode_set_colorspace
 */
int utc_image_util_decode_set_colorspace_n6(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	int color_space = IMAGE_UTIL_COLORSPACE_YV12;

	ret = image_util_decode_set_input_path(utc_decode[IMAGE_UTIL_GIF].handle, utc_decode[IMAGE_UTIL_GIF].source);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	for (color_space = IMAGE_UTIL_COLORSPACE_YV12; color_space <= IMAGE_UTIL_COLORSPACE_NV61; color_space++) {
		if (gif_colorspace_tbl[color_space] == IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT) {
			ret = image_util_decode_set_colorspace(utc_decode[IMAGE_UTIL_GIF].handle, color_space);
			assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);
		}
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_colorspace_n7
 * @since_tizen		6.0
 * @description		Negative test case for image_util_decode_set_colorspace
 */
int utc_image_util_decode_set_colorspace_n7(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	int color_space = IMAGE_UTIL_COLORSPACE_YV12;

	ret = image_util_decode_set_input_path(utc_decode[IMAGE_UTIL_BMP].handle, utc_decode[IMAGE_UTIL_BMP].source);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	for (color_space = IMAGE_UTIL_COLORSPACE_YV12; color_space <= IMAGE_UTIL_COLORSPACE_NV61; color_space++) {
		if (bmp_colorspace_tbl[color_space] == IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT) {
			ret = image_util_decode_set_colorspace(utc_decode[IMAGE_UTIL_BMP].handle, color_space);
			assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);
		}
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_colorspace_p1
 * @since_tizen		3.0
 * @description		Positive test case for image_util_decode_set_colorspace
 */
int utc_image_util_decode_set_colorspace_p1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	int color_space = IMAGE_UTIL_COLORSPACE_YV12;

	ret = image_util_decode_set_input_path(utc_decode[IMAGE_UTIL_JPEG].handle, utc_decode[IMAGE_UTIL_JPEG].source);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	for (color_space = IMAGE_UTIL_COLORSPACE_YV12; color_space <= IMAGE_UTIL_COLORSPACE_NV61; color_space++) {
		if (jpeg_colorspace_tbl[color_space] == IMAGE_UTIL_ERROR_NONE) {
			ret = image_util_decode_set_colorspace(utc_decode[IMAGE_UTIL_JPEG].handle, color_space);
			assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_colorspace_p2
 * @since_tizen		6.0
 * @description		Positive test case for image_util_decode_set_colorspace
 */
int utc_image_util_decode_set_colorspace_p2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	int color_space = IMAGE_UTIL_COLORSPACE_YV12;

	ret = image_util_decode_set_input_path(utc_decode[IMAGE_UTIL_PNG].handle, utc_decode[IMAGE_UTIL_PNG].source);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	for (color_space = IMAGE_UTIL_COLORSPACE_YV12; color_space <= IMAGE_UTIL_COLORSPACE_NV61; color_space++) {
		if (png_colorspace_tbl[color_space] == IMAGE_UTIL_ERROR_NONE) {
			ret = image_util_decode_set_colorspace(utc_decode[IMAGE_UTIL_PNG].handle, color_space);
			assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_colorspace_p3
 * @since_tizen		6.0
 * @description		Positive test case for image_util_decode_set_colorspace
 */
int utc_image_util_decode_set_colorspace_p3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	int color_space = IMAGE_UTIL_COLORSPACE_YV12;

	ret = image_util_decode_set_input_path(utc_decode[IMAGE_UTIL_GIF].handle, utc_decode[IMAGE_UTIL_GIF].source);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	for (color_space = IMAGE_UTIL_COLORSPACE_YV12; color_space <= IMAGE_UTIL_COLORSPACE_NV61; color_space++) {
		if (gif_colorspace_tbl[color_space] == IMAGE_UTIL_ERROR_NONE) {
			ret = image_util_decode_set_colorspace(utc_decode[IMAGE_UTIL_GIF].handle, color_space);
			assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_colorspace_p4
 * @since_tizen		6.0
 * @description		Positive test case for image_util_decode_set_colorspace
 */
int utc_image_util_decode_set_colorspace_p4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	int color_space = IMAGE_UTIL_COLORSPACE_YV12;

	ret = image_util_decode_set_input_path(utc_decode[IMAGE_UTIL_BMP].handle, utc_decode[IMAGE_UTIL_BMP].source);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	for (color_space = IMAGE_UTIL_COLORSPACE_YV12; color_space <= IMAGE_UTIL_COLORSPACE_NV61; color_space++) {
		if (bmp_colorspace_tbl[color_space] == IMAGE_UTIL_ERROR_NONE) {
			ret = image_util_decode_set_colorspace(utc_decode[IMAGE_UTIL_BMP].handle, color_space);
			assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_jpeg_downscale_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_jpeg_downscale
 */
int utc_image_util_decode_set_jpeg_downscale_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_decode_set_jpeg_downscale(NULL, IMAGE_UTIL_DOWNSCALE_1_1);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_jpeg_downscale_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_jpeg_downscale
 */
int utc_image_util_decode_set_jpeg_downscale_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_decode_set_jpeg_downscale(utc_encode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_DOWNSCALE_1_1);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_jpeg_downscale_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_jpeg_downscale
 */
int utc_image_util_decode_set_jpeg_downscale_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_decode_set_input_path(utc_decode[IMAGE_UTIL_JPEG].handle, utc_decode[IMAGE_UTIL_JPEG].source);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_decode_set_jpeg_downscale(utc_decode[IMAGE_UTIL_PNG].handle, IMAGE_UTIL_DOWNSCALE_1_1);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	ret = image_util_decode_set_jpeg_downscale(utc_decode[IMAGE_UTIL_GIF].handle, IMAGE_UTIL_DOWNSCALE_1_1);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	ret = image_util_decode_set_jpeg_downscale(utc_decode[IMAGE_UTIL_BMP].handle, IMAGE_UTIL_DOWNSCALE_1_1);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_jpeg_downscale_n4
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_set_jpeg_downscale
 */
int utc_image_util_decode_set_jpeg_downscale_n4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_decode_set_input_path(utc_decode[IMAGE_UTIL_JPEG].handle, utc_decode[IMAGE_UTIL_JPEG].source);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_decode_set_jpeg_downscale(utc_decode[IMAGE_UTIL_JPEG].handle, -1);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_decode_set_jpeg_downscale(utc_decode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_DOWNSCALE_1_8 + 1);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_decode_set_jpeg_downscale_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_decode_set_jpeg_downscale
 */
int utc_image_util_decode_set_jpeg_downscale_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_decode_set_input_path(utc_decode[IMAGE_UTIL_JPEG].handle, utc_decode[IMAGE_UTIL_JPEG].source);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_decode_set_jpeg_downscale(utc_decode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_DOWNSCALE_1_1);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_run
 */
int utc_image_util_decode_run_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long image_width = 0, image_height = 0;
	unsigned long long image_size = 0;

	ret = image_util_decode_run(NULL, &image_width, &image_height, &image_size);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_run
 */
int utc_image_util_decode_run_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long image_width = 0, image_height = 0;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_run(utc_encode[type].handle, &image_width, &image_height, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_run
 */
int utc_image_util_decode_run_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	unsigned long image_width = 0, image_height = 0;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_output_buffer(utc_decode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run(utc_decode[type].handle, &image_width, &image_height, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_n4
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_run
 */
int utc_image_util_decode_run_n4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long image_width = 0, image_height = 0;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_input_path(utc_decode[type].handle, utc_decode[type].source);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run(utc_decode[type].handle, &image_width, &image_height, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_n5
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_run
 */
int utc_image_util_decode_run_n5(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long image_width = 0, image_height = 0;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_input_buffer(utc_decode[type].handle, utc_encode[type].result.buffer, utc_encode[type].result.size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run(utc_decode[type].handle, &image_width, &image_height, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_p1
 * @since_tizen		3.0
 * @description		Positive test case for image_util_decode_run
 */
int utc_image_util_decode_run_p1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	unsigned long image_width = 0, image_height = 0;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_input_path(utc_decode[type].handle, utc_decode[type].source);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_output_buffer(utc_decode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run(utc_decode[type].handle, &image_width, &image_height, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		IMAGEUTIL_SAFE_FREE(data);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_p2
 * @since_tizen		3.0
 * @description		Positive test case for image_util_decode_run
 */
int utc_image_util_decode_run_p2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	unsigned long image_width = 0, image_height = 0;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_input_buffer(utc_decode[type].handle, utc_encode[type].result.buffer, utc_encode[type].result.size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_output_buffer(utc_decode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run(utc_decode[type].handle, &image_width, &image_height, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		IMAGEUTIL_SAFE_FREE(data);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run2_n
 * @since_tizen		5.5
 * @description		Negative test case for image_util_decode_run2
 */
int utc_image_util_decode_run2_n(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_input_path(utc_decode[type].handle, utc_decode[type].source);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run2(utc_decode[type].handle, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run2_p1
 * @since_tizen		5.5
 * @description		Positive test case for image_util_decode_run2
 */
int utc_image_util_decode_run2_p1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_image_h decoded_image = NULL;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_input_path(utc_decode[type].handle, utc_decode[type].source);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run2(utc_decode[type].handle, &decoded_image);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_destroy_image(decoded_image);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run2_p2
 * @since_tizen		5.5
 * @description		Positive test case for image_util_decode_run2
 */
int utc_image_util_decode_run2_p2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_image_h decoded_image = NULL;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_input_buffer(utc_decode[type].handle, utc_encode[type].result.buffer, utc_encode[type].result.size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run2(utc_decode[type].handle, &decoded_image);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_destroy_image(decoded_image);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_async_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_run_async
 */
int utc_image_util_decode_run_async_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_decode_run_async(NULL, (image_util_decode_completed_cb) utc_decode_completed_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_async_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_run_async
 */
int utc_image_util_decode_run_async_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_run_async(utc_encode[type].handle, (image_util_decode_completed_cb) utc_decode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_async_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_run_async
 */
int utc_image_util_decode_run_async_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_output_buffer(utc_decode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run_async(utc_decode[type].handle, (image_util_decode_completed_cb) utc_decode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_async_n4
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_run_async
 */
int utc_image_util_decode_run_async_n4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_input_path(utc_decode[type].handle, utc_decode[type].source);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run_async(utc_decode[type].handle, (image_util_decode_completed_cb) utc_decode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_async_n5
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_run_async
 */
int utc_image_util_decode_run_async_n5(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_input_buffer(utc_decode[type].handle, utc_encode[type].result.buffer, utc_encode[type].result.size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run_async(utc_decode[type].handle, (image_util_decode_completed_cb) utc_decode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_async_n6
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_run_async
 */
int utc_image_util_decode_run_async_n6(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_input_path(utc_decode[type].handle, utc_decode[type].source);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_output_buffer(utc_decode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run_async(utc_decode[type].handle, NULL, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_async_p1
 * @since_tizen		3.0
 * @description		Positive test case for image_util_decode_run_async
 */
int utc_image_util_decode_run_async_p1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_set_input_path(utc_decode[type].handle, utc_decode[type].source);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_output_buffer(utc_decode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run_async(utc_decode[type].handle, (image_util_decode_completed_cb) utc_decode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		wait_for_async();
		IMAGEUTIL_SAFE_FREE(data);
		assert_eq(callback_error, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_async_p2
 * @since_tizen		3.0
 * @description		Positive test case for image_util_decode_run_async
 */
int utc_image_util_decode_run_async_p2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_input_buffer(utc_decode[type].handle, utc_encode[type].result.buffer, utc_encode[type].result.size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_output_buffer(utc_decode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run_async(utc_decode[type].handle, (image_util_decode_completed_cb) utc_decode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		wait_for_async();
		IMAGEUTIL_SAFE_FREE(data);
		assert_eq(callback_error, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_async2_n1
 * @since_tizen		5.5
 * @description		Negative test case for image_util_decode_run_async2
 */
int utc_image_util_decode_run_async2_n(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_run_async2(utc_decode[type].handle, utc_decode_completed2_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_decode_set_input_path(utc_decode[type].handle, utc_decode[type].source);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run_async2(utc_decode[type].handle, NULL, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_async2_p1
 * @since_tizen		5.5
 * @description		Positive test case for image_util_decode_run_async2
 */
int utc_image_util_decode_run_async2_p1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		callback_error = -1;
		ret = image_util_decode_set_input_path(utc_decode[type].handle, utc_decode[type].source);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run_async2(utc_decode[type].handle, utc_decode_completed2_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		wait_for_async();
		assert_eq(callback_error, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_run_async2_p2
 * @since_tizen		5.5
 * @description		Positive test case for image_util_decode_run_async2
 */
int utc_image_util_decode_run_async2_p2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		callback_error = -1;
		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_set_input_buffer(utc_decode[type].handle, utc_encode[type].result.buffer, utc_encode[type].result.size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_decode_run_async2(utc_decode[type].handle, utc_decode_completed2_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		wait_for_async();
		assert_eq(callback_error, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_destroy_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_destroy
 */
int utc_image_util_decode_destroy_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_decode_destroy(NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_decode_destroy_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_decode_destroy
 */
int utc_image_util_decode_destroy_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_destroy(utc_encode[type].handle);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_decode_destroy_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_decode_destroy
 */
int utc_image_util_decode_destroy_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		ret = image_util_decode_destroy(utc_decode[type].handle);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		utc_decode[type].handle = NULL;
	}

	return 0;
}

/**
 * @function		utc_image_util_encode_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_image_util_encode_startup(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);

		for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
			if (!UTC_CONFIG[type].decode_test) {
				FPRINTF("[%d:%s] PATH [Type: %d] [Decode: not support] \\n", __LINE__, __FUNCTION__, type);
				continue;
			}

			utc_decode[type].source = _utc_get_test_path(pszValue, UTC_CONFIG[type].decode_test);
			FPRINTF("[%d:%s] PATH [Type: %d] [Decode: %s] \\n", __LINE__, __FUNCTION__, type, utc_decode[type].source);

			if (!utc_decode[type].source) {
				FPRINTF("[%d:%s] Get UTC Path error! \\n", __LINE__, __FUNCTION__);
				return;
			}

			if (!UTC_CONFIG[type].encode_test) {
				FPRINTF("[%d:%s] PATH [Type: %d] [Encode: not support] \\n", __LINE__, __FUNCTION__, type);
				continue;
			}

			utc_encode[type].output = _utc_get_test_path(pszValue, UTC_CONFIG[type].encode_test);
			FPRINTF("[%d:%s] PATH [Type: %d] [Encode: %s] \\n", __LINE__, __FUNCTION__, type, utc_encode[type].output);

			if (!utc_encode[type].output) {
				FPRINTF("[%d:%s] Get UTC Path error! \\n", __LINE__, __FUNCTION__);
				return;
			}
		}
	}
	else
	{
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_create(type, &utc_encode[type].handle);
		if (IMAGE_UTIL_ERROR_NONE != ret)
			PRINT_UTC_LOG("[Line : %d][%s] image_util_encode_create is failed(%d).\n", __LINE__, API_NAMESPACE, ret);
	}
}

/**
 * @function		utc_image_util_encode_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_image_util_encode_cleanup(void)
{
	/* end of TC */
	__utc_decode_free();
	__utc_encode_free();
}

/**
 * @testcase		utc_image_util_encode_create_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_create
 */
int utc_image_util_encode_create_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_create(IMAGE_UTIL_PNG, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_create_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_create
 */
int utc_image_util_encode_create_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_destroy(utc_encode[type].handle);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		utc_encode[type].handle = NULL;

		ret = image_util_encode_create(-1, &utc_encode[type].handle);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_encode_create(INVALID_IMAGE_TYPE, &utc_encode[type].handle);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_create_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_create
 */
int utc_image_util_encode_create_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_destroy(utc_encode[type].handle);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		utc_encode[type].handle = NULL;

		ret = image_util_encode_create(type, &utc_encode[type].handle);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_resolution_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_resolution
 */
int utc_image_util_encode_set_resolution_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_resolution(NULL, 320, 240);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_resolution_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_resolution
 */
int utc_image_util_encode_set_resolution_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_resolution(utc_decode[type].handle, 320, 240);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_resolution_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_resolution
 */
int utc_image_util_encode_set_resolution_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_resolution(utc_encode[type].handle, 0, 240);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_encode_set_resolution(utc_encode[type].handle, 320, 0);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_resolution_n4
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_resolution
 */
int utc_image_util_encode_set_resolution_n4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_resolution(utc_encode[IMAGE_UTIL_GIF].handle, 320, 240);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_resolution(utc_encode[IMAGE_UTIL_GIF].handle, 320, 250);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_resolution_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_set_resolution
 */
int utc_image_util_encode_set_resolution_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_resolution(utc_encode[type].handle, 320, 240);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_colorspace_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_colorspace
 */
int utc_image_util_encode_set_colorspace_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_colorspace(NULL, IMAGE_UTIL_COLORSPACE_RGBA8888);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_colorspace_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_colorspace
 */
int utc_image_util_encode_set_colorspace_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_colorspace(utc_decode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_COLORSPACE_RGBA8888);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_colorspace_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_colorspace
 */
int utc_image_util_encode_set_colorspace_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_colorspace(utc_encode[IMAGE_UTIL_JPEG].handle, -1);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_encode_set_colorspace(utc_encode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_COLORSPACE_NV61 + 1);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_colorspace_n4
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_colorspace
 */
int utc_image_util_encode_set_colorspace_n4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_colorspace(utc_encode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_COLORSPACE_YUV422);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	ret = image_util_encode_set_colorspace(utc_encode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_COLORSPACE_UYVY);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	ret = image_util_encode_set_colorspace(utc_encode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_COLORSPACE_YUYV);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	ret = image_util_encode_set_colorspace(utc_encode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_COLORSPACE_RGB565);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	ret = image_util_encode_set_colorspace(utc_encode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_COLORSPACE_BGRX8888);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	ret = image_util_encode_set_colorspace(utc_encode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_COLORSPACE_NV21);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	ret = image_util_encode_set_colorspace(utc_encode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_COLORSPACE_NV16);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	ret = image_util_encode_set_colorspace(utc_encode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_COLORSPACE_NV61);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_colorspace_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_set_colorspace
 */
int utc_image_util_encode_set_colorspace_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_colorspace(utc_encode[IMAGE_UTIL_JPEG].handle, IMAGE_UTIL_COLORSPACE_RGBA8888);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_quality_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_quality
 */
int utc_image_util_encode_set_quality_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_quality(NULL, 1);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_quality_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_quality
 */
int utc_image_util_encode_set_quality_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_quality(utc_decode[IMAGE_UTIL_JPEG].handle, 1);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_quality_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_quality
 */
int utc_image_util_encode_set_quality_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_quality(utc_encode[type].handle, 1);
		if (type != IMAGE_UTIL_JPEG)
			assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_quality_n4
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_quality
 */
int utc_image_util_encode_set_quality_n4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_quality(utc_encode[IMAGE_UTIL_JPEG].handle, 0);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_encode_set_quality(utc_encode[IMAGE_UTIL_JPEG].handle, 101);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_quality_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_set_quality
 */
int utc_image_util_encode_set_quality_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_quality(utc_encode[IMAGE_UTIL_JPEG].handle, 1);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_png_compression_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_png_compression
 */
int utc_image_util_encode_set_png_compression_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_png_compression(NULL, IMAGE_UTIL_PNG_COMPRESSION_0);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_png_compression_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_png_compression
 */
int utc_image_util_encode_set_png_compression_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_png_compression(utc_decode[IMAGE_UTIL_PNG].handle, IMAGE_UTIL_PNG_COMPRESSION_0);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_png_compression_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_png_compression
 */
int utc_image_util_encode_set_png_compression_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test || UTC_CONFIG[type].compression)
			continue;

		ret = image_util_encode_set_png_compression(utc_encode[type].handle, IMAGE_UTIL_PNG_COMPRESSION_0);
		assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_png_compression_n4
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_png_compression
 */
int utc_image_util_encode_set_png_compression_n4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_png_compression(utc_encode[IMAGE_UTIL_PNG].handle, -1);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_encode_set_png_compression(utc_encode[IMAGE_UTIL_PNG].handle, IMAGE_UTIL_PNG_COMPRESSION_9 + 1);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_png_compression_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_set_png_compression
 */
int utc_image_util_encode_set_png_compression_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_png_compression(utc_encode[IMAGE_UTIL_PNG].handle, IMAGE_UTIL_PNG_COMPRESSION_0);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_gif_frame_delay_time_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_gif_frame_delay_time
 */
int utc_image_util_encode_set_gif_frame_delay_time_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_gif_frame_delay_time(NULL, 100);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_gif_frame_delay_time_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_gif_frame_delay_time
 */
int utc_image_util_encode_set_gif_frame_delay_time_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_gif_frame_delay_time(utc_decode[IMAGE_UTIL_GIF].handle, 100);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_gif_frame_delay_time_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_gif_frame_delay_time
 */
int utc_image_util_encode_set_gif_frame_delay_time_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_gif_frame_delay_time(utc_encode[type].handle, 100);
		if (type != IMAGE_UTIL_GIF)
			assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_gif_frame_delay_time_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_set_gif_frame_delay_time
 */
int utc_image_util_encode_set_gif_frame_delay_time_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_gif_frame_delay_time(utc_encode[IMAGE_UTIL_GIF].handle, 100);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_webp_lossless_n1
 * @since_tizen		6.0
 * @description		Negative test case for image_util_encode_set_webp_lossless
 */
int utc_image_util_encode_set_webp_lossless_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	ret = image_util_encode_set_webp_lossless(NULL, true);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_webp_lossless_n2
 * @since_tizen		6.0
 * @description		Negative test case for image_util_encode_set_webp_lossless
 */
int utc_image_util_encode_set_webp_lossless_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N && type != IMAGE_UTIL_WEBP; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_webp_lossless(utc_encode[type].handle, true);
		assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_webp_lossless_p
 * @since_tizen		6.0
 * @description		Positive test case for image_util_encode_set_webp_lossless
 */
int utc_image_util_encode_set_webp_lossless_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_webp_lossless(utc_encode[IMAGE_UTIL_WEBP].handle, true);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_webp_lossless(utc_encode[IMAGE_UTIL_WEBP].handle, false);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_lossless_n1
 * @since_tizen		7.0
 * @description		Negative test case for utc_image_util_encode_set_lossless
 */
int utc_image_util_encode_set_lossless_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	ret = image_util_encode_set_lossless(NULL, true);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_lossless_n2
 * @since_tizen		7.0
 * @description		Negative test case for utc_image_util_encode_set_lossless
 */
int utc_image_util_encode_set_lossless_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test || UTC_CONFIG[type].lossless)
			continue;

		ret = image_util_encode_set_lossless(utc_encode[type].handle, true);
		assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_lossless_p
 * @since_tizen		7.0
 * @description		Positive test case for utc_image_util_encode_set_lossless
 */
int utc_image_util_encode_set_lossless_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_set_lossless(utc_encode[IMAGE_UTIL_WEBP].handle, true);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_lossless(utc_encode[IMAGE_UTIL_WEBP].handle, false);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_lossless(utc_encode[IMAGE_UTIL_JPEG_XL].handle, true);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_lossless(utc_encode[IMAGE_UTIL_JPEG_XL].handle, false);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_input_buffer_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_input_buffer
 */
int utc_image_util_encode_set_input_buffer_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_input_buffer(NULL, utc_decode[type].result.buffer);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_input_buffer_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_input_buffer
 */
int utc_image_util_encode_set_input_buffer_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_input_buffer(utc_decode[type].handle, utc_decode[type].result.buffer);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_input_buffer_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_input_buffer
 */
int utc_image_util_encode_set_input_buffer_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_input_buffer(utc_encode[type].handle, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_input_buffer_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_set_input_buffer
 */
int utc_image_util_encode_set_input_buffer_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_input_buffer(utc_encode[type].handle, utc_decode[type].result.buffer);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_output_path_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_output_path
 */
int utc_image_util_encode_set_output_path_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_output_path(NULL, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_output_path_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_output_path
 */
int utc_image_util_encode_set_output_path_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_output_path(utc_decode[type].handle, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_output_path_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_output_path
 */
int utc_image_util_encode_set_output_path_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_output_path(utc_encode[type].handle, WRONG_PATH);
		assert_eq(ret, IMAGE_UTIL_ERROR_NO_SUCH_FILE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_output_path_n4
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_output_path
 */
int utc_image_util_encode_set_output_path_n4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_output_path(utc_encode[type].handle, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_NO_SUCH_FILE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_output_path_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_set_output_path
 */
int utc_image_util_encode_set_output_path_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_output_path(utc_encode[type].handle, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_output_buffer_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_output_buffer
 */
int utc_image_util_encode_set_output_buffer_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;

	ret = image_util_encode_set_output_buffer(NULL, &data);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_output_buffer_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_output_buffer
 */
int utc_image_util_encode_set_output_buffer_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_output_buffer(utc_decode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_output_buffer_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_set_output_buffer
 */
int utc_image_util_encode_set_output_buffer_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_output_buffer(utc_encode[type].handle, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_set_output_buffer_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_set_output_buffer
 */
int utc_image_util_encode_set_output_buffer_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_output_buffer(utc_encode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run
 */
int utc_image_util_encode_run_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long long image_size = 0;

	ret = image_util_encode_run(NULL, &image_size);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run
 */
int utc_image_util_encode_run_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_run(utc_decode[type].handle, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run
 */
int utc_image_util_encode_run_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_run(utc_encode[type].handle, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_n4
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run
 */
int utc_image_util_encode_run_n4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_input_buffer(utc_encode[type].handle, utc_decode[type].result.buffer);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run(utc_encode[type].handle, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_n5
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run
 */
int utc_image_util_encode_run_n5(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_output_path(utc_encode[type].handle, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run(utc_encode[type].handle, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_n6
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run
 */
int utc_image_util_encode_run_n6(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_output_buffer(utc_encode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run(utc_encode[type].handle, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_n7
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run
 */
int utc_image_util_encode_run_n7(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_input_buffer(utc_encode[type].handle, utc_decode[type].result.buffer);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_output_path(utc_encode[type].handle, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run(utc_encode[type].handle, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_n8
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run
 */
int utc_image_util_encode_run_n8(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long long image_size = 0;

	ret = __fill_test_buffer(IMAGE_UTIL_GIF);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_resolution(utc_encode[IMAGE_UTIL_GIF].handle, utc_decode[IMAGE_UTIL_GIF].result.width, utc_decode[IMAGE_UTIL_GIF].result.height);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_resolution(utc_encode[IMAGE_UTIL_GIF].handle, utc_decode[IMAGE_UTIL_GIF].result.width, utc_decode[IMAGE_UTIL_GIF].result.height);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_input_buffer(utc_encode[IMAGE_UTIL_GIF].handle, utc_decode[IMAGE_UTIL_GIF].result.buffer);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_output_path(utc_encode[IMAGE_UTIL_GIF].handle, utc_encode[IMAGE_UTIL_GIF].output);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_run(utc_encode[IMAGE_UTIL_GIF].handle, &image_size);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_p1
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_run
 */
int utc_image_util_encode_run_p1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_resolution(utc_encode[type].handle, utc_decode[type].result.width, utc_decode[type].result.height);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_input_buffer(utc_encode[type].handle, utc_decode[type].result.buffer);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_output_path(utc_encode[type].handle, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run(utc_encode[type].handle, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_p2
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_run
 */
int utc_image_util_encode_run_p2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	unsigned long long image_size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_resolution(utc_encode[type].handle, utc_decode[type].result.width, utc_decode[type].result.height);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_input_buffer(utc_encode[type].handle, utc_decode[type].result.buffer);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_output_buffer(utc_encode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run(utc_encode[type].handle, &image_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		IMAGEUTIL_SAFE_FREE(data);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_p3
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_run
 */
int utc_image_util_encode_run_p3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long long size = 0;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_resolution(utc_encode[type].handle, utc_decode[type].result.width, utc_decode[type].result.height);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_input_buffer(utc_encode[type].handle, utc_decode[type].result.buffer);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_output_path(utc_encode[type].handle, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run(utc_encode[type].handle, &size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_p4
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_run
 */
int utc_image_util_encode_run_p4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned long long size = 0;

	ret = __fill_test_buffer(IMAGE_UTIL_GIF);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_resolution(utc_encode[IMAGE_UTIL_GIF].handle, utc_decode[IMAGE_UTIL_GIF].result.width, utc_decode[IMAGE_UTIL_GIF].result.height);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_resolution(utc_encode[IMAGE_UTIL_GIF].handle, utc_decode[IMAGE_UTIL_GIF].result.width, utc_decode[IMAGE_UTIL_GIF].result.height);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_input_buffer(utc_encode[IMAGE_UTIL_GIF].handle, utc_decode[IMAGE_UTIL_GIF].result.buffer);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_input_buffer(utc_encode[IMAGE_UTIL_GIF].handle, utc_decode[IMAGE_UTIL_GIF].result.buffer);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_gif_frame_delay_time(utc_encode[IMAGE_UTIL_GIF].handle, 100);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_gif_frame_delay_time(utc_encode[IMAGE_UTIL_GIF].handle, 100);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_set_output_path(utc_encode[IMAGE_UTIL_GIF].handle, utc_encode[IMAGE_UTIL_GIF].output);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_encode_run(utc_encode[IMAGE_UTIL_GIF].handle, &size);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run_async
 */
int utc_image_util_encode_run_async_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_run_async(NULL, (image_util_encode_completed_cb) utc_encode_completed_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run_async
 */
int utc_image_util_encode_run_async_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_run_async(utc_decode[type].handle, (image_util_encode_completed_cb) utc_encode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_n3
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run_async
 */
int utc_image_util_encode_run_async_n3(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_run_async(utc_encode[type].handle, (image_util_encode_completed_cb) utc_encode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_n4
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run_async
 */
int utc_image_util_encode_run_async_n4(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_input_buffer(utc_encode[type].handle, utc_decode[type].result.buffer);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_async(utc_encode[type].handle, (image_util_encode_completed_cb) utc_encode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_n5
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run_async
 */
int utc_image_util_encode_run_async_n5(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_output_path(utc_encode[type].handle, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_async(utc_encode[type].handle, (image_util_encode_completed_cb) utc_encode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_n6
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run_async
 */
int utc_image_util_encode_run_async_n6(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_set_output_buffer(utc_encode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_async(utc_encode[type].handle, (image_util_encode_completed_cb) utc_encode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_n7
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run_async
 */
int utc_image_util_encode_run_async_n7(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_input_buffer(utc_encode[type].handle, utc_decode[type].result.buffer);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_output_path(utc_encode[type].handle, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_async(utc_encode[type].handle, (image_util_encode_completed_cb) utc_encode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_n8
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_run_async
 */
int utc_image_util_encode_run_async_n8(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_resolution(utc_encode[type].handle, utc_decode[type].result.width, utc_decode[type].result.height);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_input_buffer(utc_encode[type].handle, utc_decode[type].result.buffer);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_output_path(utc_encode[type].handle, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_async(utc_encode[type].handle, NULL, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_async_n9
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_async
 */
int utc_image_util_encode_run_async_n9(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = __fill_test_buffer(IMAGE_UTIL_GIF);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	ret = image_util_encode_set_resolution(utc_encode[IMAGE_UTIL_GIF].handle, utc_decode[IMAGE_UTIL_GIF].result.width, utc_decode[IMAGE_UTIL_GIF].result.height);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	ret = image_util_encode_set_resolution(utc_encode[IMAGE_UTIL_GIF].handle, utc_decode[IMAGE_UTIL_GIF].result.width, utc_decode[IMAGE_UTIL_GIF].result.height);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	ret = image_util_encode_set_input_buffer(utc_encode[IMAGE_UTIL_GIF].handle, utc_decode[IMAGE_UTIL_GIF].result.buffer);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	ret = image_util_encode_set_output_path(utc_encode[IMAGE_UTIL_GIF].handle, utc_encode[IMAGE_UTIL_GIF].output);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	ret = image_util_encode_run_async(utc_encode[IMAGE_UTIL_GIF].handle, (image_util_encode_completed_cb) utc_encode_completed_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	wait_for_async();
	assert_eq(callback_error, IMAGE_UTIL_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_p1
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_run_async
 */
int utc_image_util_encode_run_async_p1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_resolution(utc_encode[type].handle, utc_decode[type].result.width, utc_decode[type].result.height);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_input_buffer(utc_encode[type].handle, utc_decode[type].result.buffer);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_output_path(utc_encode[type].handle, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_async(utc_encode[type].handle, (image_util_encode_completed_cb) utc_encode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		wait_for_async();
		assert_eq(callback_error, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_p2
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_run_async
 */
int utc_image_util_encode_run_async_p2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned char *data = NULL;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = __fill_test_buffer(type);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_resolution(utc_encode[type].handle, utc_decode[type].result.width, utc_decode[type].result.height);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_input_buffer(utc_encode[type].handle, utc_decode[type].result.buffer);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_set_output_buffer(utc_encode[type].handle, &data);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_async(utc_encode[type].handle, (image_util_encode_completed_cb) utc_encode_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		wait_for_async();
		IMAGEUTIL_SAFE_FREE(data);
		assert_eq(callback_error, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_to_file_p
 * @since_tizen		5.5
 * @description		Positive test case for image_util_encode_run_to_file
 */
int utc_image_util_encode_run_to_file_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = _utc_decode_from_file(utc_decode[type].source, &utc_decode[type].decoded);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_to_file(utc_encode[type].handle, utc_decode[type].decoded, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_to_file_n
 * @since_tizen		5.5
 * @description		Negative test case for image_util_encode_run_to_file
 */
int utc_image_util_encode_run_to_file_n(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = _utc_decode_from_file(utc_decode[type].source, &utc_decode[type].decoded);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_to_file(NULL, utc_decode[type].decoded, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_encode_run_to_file(utc_encode[type].handle, NULL, utc_encode[type].output);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_encode_run_to_file(utc_encode[type].handle, utc_decode[type].decoded, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_to_buffer_p
 * @since_tizen		5.5
 * @description		Positive test case for image_util_encode_run_to_buffer
 */
int utc_image_util_encode_run_to_buffer_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = _utc_decode_from_file(utc_decode[type].source, &utc_decode[type].decoded);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_to_buffer(utc_encode[type].handle, utc_decode[type].decoded, &utc_encode[type].result.buffer, &utc_encode[type].result.buffer_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		assert_neq(utc_encode[type].result.buffer, NULL);
		assert_gt(utc_encode[type].result.buffer_size, 0);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_to_buffer_n
 * @since_tizen		5.5
 * @description		Negative test case for image_util_encode_run_to_buffer
 */
int utc_image_util_encode_run_to_buffer_n(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = _utc_decode_from_file(utc_decode[type].source, &utc_decode[type].decoded);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_to_buffer(NULL, utc_decode[type].decoded, &utc_encode[type].result.buffer, &utc_encode[type].result.buffer_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_encode_run_to_buffer(utc_encode[type].handle, NULL, &utc_encode[type].result.buffer, &utc_encode[type].result.buffer_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_encode_run_to_buffer(utc_encode[type].handle, utc_decode[type].decoded, NULL, &utc_encode[type].result.buffer_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_encode_run_to_buffer(utc_encode[type].handle, utc_decode[type].decoded, &utc_encode[type].result.buffer, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_to_file_p
 * @since_tizen		5.5
 * @description		Positive test case for image_util_encode_run_async_to_file
 */
int utc_image_util_encode_run_async_to_file_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = _utc_decode_from_file(utc_decode[type].source, &utc_decode[type].decoded);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_async_to_file(utc_encode[type].handle, utc_decode[type].decoded, utc_encode[type].output,
												utc_encode_to_file_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		wait_for_async();
		assert_eq(callback_error, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_to_file_n
 * @since_tizen		5.5
 * @description		Negative test case for image_util_encode_run_async_to_file
 */
int utc_image_util_encode_run_async_to_file_n(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = _utc_decode_from_file(utc_decode[type].source, &utc_decode[type].decoded);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_async_to_file(NULL, utc_decode[type].decoded, utc_encode[type].output, utc_encode_to_file_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_encode_run_async_to_file(utc_encode[type].handle, NULL, utc_encode[type].output, utc_encode_to_file_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_encode_run_async_to_file(utc_encode[type].handle, utc_decode[type].decoded, NULL, utc_encode_to_file_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_encode_run_async_to_file(utc_encode[type].handle, utc_decode[type].decoded, utc_encode[type].output, NULL, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_to_buffer_p
 * @since_tizen		5.5
 * @description		Positive test case for image_util_encode_run_async_to_buffer
 */
int utc_image_util_encode_run_async_to_buffer_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = _utc_decode_from_file(utc_decode[type].source, &utc_decode[type].decoded);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_async_to_buffer(utc_encode[type].handle, utc_decode[type].decoded, utc_encode_to_buffer_completed_cb,
													&utc_encode[type].result);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		wait_for_async();
		assert_eq(callback_error, IMAGE_UTIL_ERROR_NONE);
		assert_neq(utc_encode[type].result.buffer, NULL);
		assert_gt(utc_encode[type].result.buffer_size, 0);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_run_async_to_buffer_n
 * @since_tizen		5.5
 * @description		Negative test case for image_util_encode_run_async_to_buffer
 */
int utc_image_util_encode_run_async_to_buffer_n(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = _utc_decode_from_file(utc_decode[type].source, &utc_decode[type].decoded);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_encode_run_async_to_buffer(NULL, utc_decode[type].decoded, utc_encode_to_buffer_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_encode_run_async_to_buffer(utc_encode[type].handle, NULL, utc_encode_to_buffer_completed_cb, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_encode_run_async_to_buffer(utc_encode[type].handle, utc_decode[type].decoded, NULL, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_destroy_n1
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_destroy
 */
int utc_image_util_encode_destroy_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_encode_destroy(NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_encode_destroy_n2
 * @since_tizen		3.0
 * @description		Negative test case for image_util_encode_destroy
 */
int utc_image_util_encode_destroy_n2(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_destroy(utc_decode[type].handle);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_encode_destroy_p
 * @since_tizen		3.0
 * @description		Positive test case for image_util_encode_destroy
 */
int utc_image_util_encode_destroy_p(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_type_e type = 0;

	for (type = 0; type <= UTC_IMAGE_TYPE_N; type++) {
		if (!UTC_CONFIG[type].encode_test)
			continue;

		ret = image_util_encode_destroy(utc_encode[type].handle);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		utc_encode[type].handle = NULL;
	}

	return 0;
}
