//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#include <image_util.h>
#include <storage.h>
#include <glib.h>
#include "tct_common.h"
#include "utc-image-util-common.h"

#define API_NAMESPACE			"[IMAGE-UTIL]"

#define SAFE_FREE(ptr)			{ if (ptr) {free(ptr); ptr = NULL; } }
#define FILENAME_ORIGIN			"sample.gif"
#define FILENAME_ENCODE_AGIF	"test_output.gif"

#define NUM_OF_ANIM_FILES		5
#define LAST_ANIM_TYPE			IMAGE_UTIL_ANIM_WEBP

typedef struct {
	unsigned char *buffer;
	size_t buffer_size;
} utc_buffer_data_t;

static char *g_utc_path_origin = NULL;
static char *g_utc_path_agif = NULL;

static image_util_agif_encode_h g_utc_agif_encode_h = NULL;

static image_util_image_h g_utc_img_origin = NULL;
static utc_buffer_data_t g_utc_buf_agif = { NULL, 0 };

static const char *g_utc_anim_files[NUM_OF_ANIM_FILES] = {
	"sample_anim1.png",
	"sample_anim2.png",
	"sample_anim3.png",
	"sample_anim4.png",
	"sample_anim5.png",
};
static const char *g_utc_anim_output_files[] = {
	[IMAGE_UTIL_ANIM_GIF] = "test_output.gif",
	[IMAGE_UTIL_ANIM_WEBP] = "test_output.webp",
};

static unsigned int g_utc_anim_idx = 0;
static image_util_anim_type_e g_utc_anim_type = IMAGE_UTIL_ANIM_GIF;
static image_util_image_h g_utc_anim_images[NUM_OF_ANIM_FILES] = { NULL, };
static image_util_anim_encode_h g_utc_anim_encode_h[] = {
	[IMAGE_UTIL_ANIM_GIF] = NULL,
	[IMAGE_UTIL_ANIM_WEBP] = NULL,
};
static char *g_utc_anim_output_path[] = {
	[IMAGE_UTIL_ANIM_GIF] = NULL,
	[IMAGE_UTIL_ANIM_WEBP] = NULL,
};
static utc_buffer_data_t g_utc_anim_output_buffer[] = {
	[IMAGE_UTIL_ANIM_GIF] = { NULL, 0 },
	[IMAGE_UTIL_ANIM_WEBP] = { NULL, 0 },
};

/**
 * @function		utc_image_util_encode_agif_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_image_util_agif_encode_startup(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE )) {
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		g_utc_path_origin = _utc_get_test_path(pszValue, FILENAME_ORIGIN);
		g_utc_path_agif = _utc_get_test_path(pszValue, FILENAME_ENCODE_AGIF);
		FPRINTF("[%d:%s] IMAGE PATH [Decode: %s], [Encode: %s] \\n", __LINE__, __FUNCTION__, g_utc_path_origin, g_utc_path_agif);
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	if (!g_utc_path_origin || !g_utc_path_agif)
		FPRINTF("[%d:%s] Get UTC Path error! \\n", __LINE__, __FUNCTION__);

	ret = _utc_decode_from_file(g_utc_path_origin, &g_utc_img_origin);
	if (ret != IMAGE_UTIL_ERROR_NONE)
		FPRINTF("[%d:%s] Startup error! \\n", __LINE__, __FUNCTION__);
}

/**
 * @function		utc_image_util_encode_agif_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_image_util_agif_encode_cleanup(void)
{
	/* end of TC */
	SAFE_FREE(g_utc_path_origin);
	SAFE_FREE(g_utc_path_agif);
	SAFE_FREE(g_utc_buf_agif.buffer);

	image_util_destroy_image(g_utc_img_origin);
	g_utc_img_origin = NULL;

	image_util_agif_encode_destroy(g_utc_agif_encode_h);
	g_utc_agif_encode_h = NULL;
}

/**
 * @testcase		utc_image_util_agif_encode_create_p
 * @since_tizen		5.5
 * @description		Positive test case for image_util_agif_encode_create
 */
int utc_image_util_agif_encode_create_p(void)
{
	int ret;

	ret = image_util_agif_encode_create(&g_utc_agif_encode_h);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_agif_encode_create_n
 * @since_tizen		5.5
 * @description		Negative test case for image_util_agif_encode_create
 */
int utc_image_util_agif_encode_create_n(void)
{
	int ret;

	ret = image_util_agif_encode_create(NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_agif_encode_add_frame_p
 * @since_tizen		5.5
 * @description		Positive test case for image_util_agif_encode_add_frame
 */
int utc_image_util_agif_encode_add_frame_p(void)
{
	int ret;

	ret = image_util_agif_encode_create(&g_utc_agif_encode_h);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_agif_encode_add_frame(g_utc_agif_encode_h, g_utc_img_origin, 20);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_agif_encode_add_frame_n
 * @since_tizen		5.5
 * @description		Negative test case for image_util_agif_encode_add_frame
 */
int utc_image_util_agif_encode_add_frame_n(void)
{
	int ret;

	ret = image_util_agif_encode_create(&g_utc_agif_encode_h);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_agif_encode_add_frame(NULL, g_utc_img_origin, 20);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_agif_encode_add_frame(g_utc_agif_encode_h, NULL, 20);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_agif_encode_save_to_file_p
 * @since_tizen		5.5
 * @description		Positive test case for image_util_agif_encode_save_to_file
 */
int utc_image_util_agif_encode_save_to_file_p(void)
{
	int ret;

	ret = image_util_agif_encode_create(&g_utc_agif_encode_h);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_agif_encode_add_frame(g_utc_agif_encode_h, g_utc_img_origin, 20);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_agif_encode_save_to_file(g_utc_agif_encode_h, g_utc_path_agif);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_agif_encode_save_to_file_n
 * @since_tizen		5.5
 * @description		Negative test case for image_util_agif_encode_save_to_file
 */
int utc_image_util_agif_encode_save_to_file_n(void)
{
	int ret;

	ret = image_util_agif_encode_create(&g_utc_agif_encode_h);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_agif_encode_add_frame(g_utc_agif_encode_h, g_utc_img_origin, 20);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_agif_encode_save_to_file(NULL, g_utc_path_agif);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_agif_encode_save_to_file(g_utc_agif_encode_h, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_agif_encode_save_to_buffer_p
 * @since_tizen		5.5
 * @description		Positive test case for image_util_agif_encode_save_to_buffer
 */
int utc_image_util_agif_encode_save_to_buffer_p(void)
{
	int ret;

	ret = image_util_agif_encode_create(&g_utc_agif_encode_h);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_agif_encode_add_frame(g_utc_agif_encode_h, g_utc_img_origin, 20);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_agif_encode_save_to_buffer(g_utc_agif_encode_h, &g_utc_buf_agif.buffer, &g_utc_buf_agif.buffer_size);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	assert_neq(g_utc_buf_agif.buffer, NULL);
	assert_gt(g_utc_buf_agif.buffer_size, 0);

	return 0;
}

/**
 * @testcase		utc_image_util_agif_encode_save_to_buffer_n
 * @since_tizen		5.5
 * @description		Negative test case for image_util_agif_encode_save_to_buffer
 */
int utc_image_util_agif_encode_save_to_buffer_n(void)
{
	int ret;

	ret = image_util_agif_encode_create(&g_utc_agif_encode_h);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_agif_encode_add_frame(g_utc_agif_encode_h, g_utc_img_origin, 20);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_agif_encode_save_to_buffer(NULL, &g_utc_buf_agif.buffer, &g_utc_buf_agif.buffer_size);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_agif_encode_save_to_buffer(g_utc_agif_encode_h, NULL, &g_utc_buf_agif.buffer_size);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_agif_encode_save_to_buffer(g_utc_agif_encode_h, &g_utc_buf_agif.buffer, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_agif_encode_destroy_p
 * @since_tizen		5.5
 * @description		Positive test case for image_util_agif_encode_destroy
 */
int utc_image_util_agif_encode_destroy_p(void)
{
	int ret;

	ret = image_util_agif_encode_create(&g_utc_agif_encode_h);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_agif_encode_destroy(g_utc_agif_encode_h);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	g_utc_agif_encode_h = NULL;

	return 0;
}

/**
 * @testcase		utc_image_util_agif_encode_destroy_n
 * @since_tizen		5.5
 * @description		Negative test case for image_util_agif_encode_destroy
 */
int utc_image_util_agif_encode_destroy_n(void)
{
	int ret;

	ret = image_util_agif_encode_destroy(NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function		utc_image_util_anim_encode_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_image_util_anim_encode_startup(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	char *anim_src_paths[NUM_OF_ANIM_FILES] = { NULL, };

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE )) {
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		for (g_utc_anim_idx = 0; g_utc_anim_idx < NUM_OF_ANIM_FILES; g_utc_anim_idx++) {
			anim_src_paths[g_utc_anim_idx] = _utc_get_test_path(pszValue, g_utc_anim_files[g_utc_anim_idx]);
			FPRINTF("[%d:%s] IMAGE PATH [Decode: %s] \\n", __LINE__, __FUNCTION__, anim_src_paths[g_utc_anim_idx]);
		}

		for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
			g_utc_anim_output_path[g_utc_anim_type] = _utc_get_test_path(pszValue, g_utc_anim_output_files[g_utc_anim_type]);
			FPRINTF("[%d:%s] IMAGE PATH [Encode: %s] \\n", __LINE__, __FUNCTION__, g_utc_anim_output_path[g_utc_anim_type]);
		}
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
		return;
	}

	for (g_utc_anim_idx = 0; g_utc_anim_idx < NUM_OF_ANIM_FILES; g_utc_anim_idx++) {
		ret = _utc_decode_from_file(anim_src_paths[g_utc_anim_idx], &g_utc_anim_images[g_utc_anim_idx]);
		if (ret != IMAGE_UTIL_ERROR_NONE)
			FPRINTF("[%d:%s] Startup error! \\n", __LINE__, __FUNCTION__);
		g_free(anim_src_paths[g_utc_anim_idx]);
	}
}

/**
 * @function		utc_image_util_anim_encode_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_image_util_anim_encode_cleanup(void)
{
	/* end of TC */
	for (g_utc_anim_idx = 0; g_utc_anim_idx < NUM_OF_ANIM_FILES; g_utc_anim_idx++) {
		image_util_destroy_image(g_utc_anim_images[g_utc_anim_idx]);
		g_utc_anim_images[g_utc_anim_idx] = NULL;
	}

	for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
		g_free(g_utc_anim_output_path[g_utc_anim_type]);
		g_utc_anim_output_path[g_utc_anim_type] = NULL;

		g_free(g_utc_anim_output_buffer[g_utc_anim_type].buffer);
		g_utc_anim_output_buffer[g_utc_anim_type].buffer = NULL;

		image_util_anim_encode_destroy(g_utc_anim_encode_h[g_utc_anim_type]);
		g_utc_anim_encode_h[g_utc_anim_type] = NULL;
	}
}

/**
 * @testcase		utc_image_util_anim_encode_create_p
 * @since_tizen		6.0
 * @description		Positive test case for image_util_anim_encode_create
 */
int utc_image_util_anim_encode_create_p(void)
{
	int ret;

	for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
		ret = image_util_anim_encode_create(g_utc_anim_type, &g_utc_anim_encode_h[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_anim_encode_destroy(g_utc_anim_encode_h[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		g_utc_anim_encode_h[g_utc_anim_type] = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_create_n1
 * @since_tizen		6.0
 * @description		Negative test case for image_util_anim_encode_create
 */
int utc_image_util_anim_encode_create_n1(void)
{
	int ret;

	for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
		ret = image_util_anim_encode_create(g_utc_anim_type, NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_create_n2
 * @since_tizen		6.0
 * @description		Negative test case for image_util_anim_encode_create
 */
int utc_image_util_anim_encode_create_n2(void)
{
	int ret;

	ret = image_util_anim_encode_create(-1, &g_utc_anim_encode_h[0]);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	ret = image_util_anim_encode_create(LAST_ANIM_TYPE + 2, &g_utc_anim_encode_h[0]);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_set_loop_count_p
 * @since_tizen		6.0
 * @description		Positive test case for image_util_anim_encode_set_loop_count
 */
int utc_image_util_anim_encode_set_loop_count_p(void)
{
	int ret;

	for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
		ret = image_util_anim_encode_create(g_utc_anim_type, &g_utc_anim_encode_h[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_anim_encode_set_loop_count(g_utc_anim_encode_h[g_utc_anim_type], 0);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_anim_encode_set_loop_count(g_utc_anim_encode_h[g_utc_anim_type], 10);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_set_loop_count_n
 * @since_tizen		6.0
 * @description		Negative test case for image_util_anim_encode_set_loop_count
 */
int utc_image_util_anim_encode_set_loop_count_n(void)
{
	int ret;

	ret = image_util_anim_encode_set_loop_count(NULL, 10);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_set_background_color_p
 * @since_tizen		6.0
 * @description		Positive test case for image_util_anim_encode_set_background_color
 */
int utc_image_util_anim_encode_set_background_color_p(void)
{
	int ret;

	ret = image_util_anim_encode_create(IMAGE_UTIL_ANIM_WEBP, &g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP]);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_anim_encode_set_background_color(g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP], 0xFF, 0x00, 0x00, 0xFF);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_anim_encode_set_background_color(g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP], 0x00, 0xFF, 0x00, 0xFF);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_anim_encode_set_background_color(g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP], 0x00, 0x00, 0xFF, 0xFF);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_set_background_color_n1
 * @since_tizen		6.0
 * @description		Negative test case for image_util_anim_encode_set_background_color
 */
int utc_image_util_anim_encode_set_background_color_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_anim_encode_set_background_color(NULL, 0x00, 0x00, 0x00, 0xFF);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_set_background_color_n2
 * @since_tizen		6.0
 * @description		Negative test case for image_util_anim_encode_set_background_color
 */
int utc_image_util_anim_encode_set_background_color_n2(void)
{
	int ret;

	ret = image_util_anim_encode_create(IMAGE_UTIL_ANIM_GIF, &g_utc_anim_encode_h[IMAGE_UTIL_ANIM_GIF]);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_anim_encode_set_background_color(g_utc_anim_encode_h[IMAGE_UTIL_ANIM_GIF], 0x00, 0x00, 0x00, 0xFF);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_set_lossless_p
 * @since_tizen		6.0
 * @description		Positive test case for image_util_anim_encode_set_lossless
 */
int utc_image_util_anim_encode_set_lossless_p(void)
{
	int ret;

	ret = image_util_anim_encode_create(IMAGE_UTIL_ANIM_WEBP, &g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP]);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_anim_encode_set_lossless(g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP], true);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_anim_encode_set_lossless(g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP], false);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_set_lossless_n1
 * @since_tizen		6.0
 * @description		Negative test case for image_util_anim_encode_set_lossless
 */
int utc_image_util_anim_encode_set_lossless_n1(void)
{
	int ret;

	ret = image_util_anim_encode_set_lossless(NULL, true);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_set_lossless_n2
 * @since_tizen		6.0
 * @description		Negative test case for image_util_anim_encode_set_lossless
 */
int utc_image_util_anim_encode_set_lossless_n2(void)
{
	int ret;

	ret = image_util_anim_encode_create(IMAGE_UTIL_ANIM_GIF, &g_utc_anim_encode_h[IMAGE_UTIL_ANIM_GIF]);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_anim_encode_set_lossless(g_utc_anim_encode_h[IMAGE_UTIL_ANIM_GIF], true);
	assert_eq(ret, IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT);

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_add_frame_p
 * @since_tizen		6.0
 * @description		Positive test case for image_util_anim_encode_add_frame
 */
int utc_image_util_anim_encode_add_frame_p(void)
{
	int ret;

	for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
		ret = image_util_anim_encode_create(g_utc_anim_type, &g_utc_anim_encode_h[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_anim_encode_add_frame(g_utc_anim_encode_h[g_utc_anim_type], g_utc_anim_images[0], 20);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_add_frame_n
 * @since_tizen		6.0
 * @description		Negative test case for image_util_anim_encode_add_frame
 */
int utc_image_util_anim_encode_add_frame_n(void)
{
	int ret;

	for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
		ret = image_util_anim_encode_create(g_utc_anim_type, &g_utc_anim_encode_h[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_anim_encode_add_frame(NULL, g_utc_anim_images[0], 20);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_anim_encode_add_frame(g_utc_anim_encode_h[g_utc_anim_type], NULL, 20);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_save_to_file_p1
 * @since_tizen		6.0
 * @description		Positive test case for image_util_anim_encode_save_to_file
 */
int utc_image_util_anim_encode_save_to_file_p1(void)
{
	int ret;

	for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
		ret = image_util_anim_encode_create(g_utc_anim_type, &g_utc_anim_encode_h[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_anim_encode_set_loop_count(g_utc_anim_encode_h[g_utc_anim_type], 0);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		for (g_utc_anim_idx = 0; g_utc_anim_idx < NUM_OF_ANIM_FILES; g_utc_anim_idx++) {
			ret = image_util_anim_encode_add_frame(g_utc_anim_encode_h[g_utc_anim_type], g_utc_anim_images[g_utc_anim_idx], 100);
			assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		}

		ret = image_util_anim_encode_save_to_file(g_utc_anim_encode_h[g_utc_anim_type], g_utc_anim_output_path[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_save_to_file_p2
 * @since_tizen		6.0
 * @description		Positive test case for image_util_anim_encode_save_to_file
 */
int utc_image_util_anim_encode_save_to_file_p2(void)
{
	int ret;

	ret = image_util_anim_encode_create(IMAGE_UTIL_ANIM_WEBP, &g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP]);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_anim_encode_set_lossless(g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP], true);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	for (g_utc_anim_idx = 0; g_utc_anim_idx < NUM_OF_ANIM_FILES; g_utc_anim_idx++) {
		ret = image_util_anim_encode_add_frame(g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP], g_utc_anim_images[IMAGE_UTIL_ANIM_WEBP], 100);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	ret = image_util_anim_encode_save_to_file(g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP], g_utc_anim_output_path[IMAGE_UTIL_ANIM_WEBP]);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_save_to_file_n1
 * @since_tizen		6.0
 * @description		Negative test case for image_util_anim_encode_save_to_file
 */
int utc_image_util_anim_encode_save_to_file_n1(void)
{
	int ret;

	for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
		ret = image_util_anim_encode_create(g_utc_anim_type, &g_utc_anim_encode_h[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		for (g_utc_anim_idx = 0; g_utc_anim_idx < NUM_OF_ANIM_FILES; g_utc_anim_idx++) {
			ret = image_util_anim_encode_add_frame(g_utc_anim_encode_h[g_utc_anim_type], g_utc_anim_images[g_utc_anim_idx], 100);
			assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		}

		ret = image_util_anim_encode_save_to_file(NULL, g_utc_anim_output_path[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_anim_encode_save_to_file(g_utc_anim_encode_h[g_utc_anim_type], NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_save_to_file_n2
 * @since_tizen		6.0
 * @description		Negative test case for image_util_anim_encode_save_to_file
 */
int utc_image_util_anim_encode_save_to_file_n2(void)
{
	int ret;

	for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
		ret = image_util_anim_encode_create(g_utc_anim_type, &g_utc_anim_encode_h[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_anim_encode_save_to_file(g_utc_anim_encode_h[g_utc_anim_type], g_utc_anim_output_path[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_save_to_buffer_p1
 * @since_tizen		6.0
 * @description		Positive test case for image_util_anim_encode_save_to_buffer
 */
int utc_image_util_anim_encode_save_to_buffer_p1(void)
{
	int ret;

	for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
		ret = image_util_anim_encode_create(g_utc_anim_type, &g_utc_anim_encode_h[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_anim_encode_set_loop_count(g_utc_anim_encode_h[g_utc_anim_type], 0);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		for (g_utc_anim_idx = 0; g_utc_anim_idx < NUM_OF_ANIM_FILES; g_utc_anim_idx++) {
			ret = image_util_anim_encode_add_frame(g_utc_anim_encode_h[g_utc_anim_type], g_utc_anim_images[g_utc_anim_idx], 100);
			assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		}

		ret = image_util_anim_encode_save_to_buffer(g_utc_anim_encode_h[g_utc_anim_type],
							&g_utc_anim_output_buffer[g_utc_anim_type].buffer,
							&g_utc_anim_output_buffer[g_utc_anim_type].buffer_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		assert_neq(g_utc_anim_output_buffer[g_utc_anim_type].buffer, NULL);
		assert_gt(g_utc_anim_output_buffer[g_utc_anim_type].buffer_size, 8);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_save_to_buffer_p2
 * @since_tizen		6.0
 * @description		Positive test case for image_util_anim_encode_save_to_buffer
 */
int utc_image_util_anim_encode_save_to_buffer_p2(void)
{
	int ret;

	ret = image_util_anim_encode_create(IMAGE_UTIL_ANIM_WEBP, &g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP]);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_anim_encode_set_lossless(g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP], true);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	for (g_utc_anim_idx = 0; g_utc_anim_idx < NUM_OF_ANIM_FILES; g_utc_anim_idx++) {
		ret = image_util_anim_encode_add_frame(g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP], g_utc_anim_images[IMAGE_UTIL_ANIM_WEBP], 100);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	}

	ret = image_util_anim_encode_save_to_buffer(g_utc_anim_encode_h[IMAGE_UTIL_ANIM_WEBP],
						&g_utc_anim_output_buffer[IMAGE_UTIL_ANIM_WEBP].buffer,
						&g_utc_anim_output_buffer[IMAGE_UTIL_ANIM_WEBP].buffer_size);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	assert_neq(g_utc_anim_output_buffer[IMAGE_UTIL_ANIM_WEBP].buffer, NULL);
	assert_gt(g_utc_anim_output_buffer[IMAGE_UTIL_ANIM_WEBP].buffer_size, 8);

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_save_to_buffer_n1
 * @since_tizen		6.0
 * @description		Negative test case for image_util_anim_encode_save_to_buffer
 */
int utc_image_util_anim_encode_save_to_buffer_n1(void)
{
	int ret;

	for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
		ret = image_util_anim_encode_create(g_utc_anim_type, &g_utc_anim_encode_h[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		for (g_utc_anim_idx = 0; g_utc_anim_idx < NUM_OF_ANIM_FILES; g_utc_anim_idx++) {
			ret = image_util_anim_encode_add_frame(g_utc_anim_encode_h[g_utc_anim_type], g_utc_anim_images[g_utc_anim_idx], 100);
			assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		}

		ret = image_util_anim_encode_save_to_buffer(NULL,
							&g_utc_anim_output_buffer[g_utc_anim_type].buffer,
							&g_utc_anim_output_buffer[g_utc_anim_type].buffer_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_anim_encode_save_to_buffer(g_utc_anim_encode_h[g_utc_anim_type],
							NULL,
							&g_utc_anim_output_buffer[g_utc_anim_type].buffer_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

		ret = image_util_anim_encode_save_to_buffer(g_utc_anim_encode_h[g_utc_anim_type],
							&g_utc_anim_output_buffer[g_utc_anim_type].buffer,
							NULL);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_save_to_buffer_n2
 * @since_tizen		6.0
 * @description		Negative test case for image_util_anim_encode_save_to_buffer
 */
int utc_image_util_anim_encode_save_to_buffer_n2(void)
{
	int ret;

	for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
		ret = image_util_anim_encode_create(g_utc_anim_type, &g_utc_anim_encode_h[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_anim_encode_save_to_buffer(g_utc_anim_encode_h[g_utc_anim_type],
							&g_utc_anim_output_buffer[g_utc_anim_type].buffer,
							&g_utc_anim_output_buffer[g_utc_anim_type].buffer_size);
		assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_destroy_p
 * @since_tizen		6.0
 * @description		Positive test case for image_util_anim_encode_destroy
 */
int utc_image_util_anim_encode_destroy_p(void)
{
	int ret;

	for (g_utc_anim_type = 0; g_utc_anim_type <= LAST_ANIM_TYPE; g_utc_anim_type++) {
		ret = image_util_anim_encode_create(g_utc_anim_type, &g_utc_anim_encode_h[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

		ret = image_util_anim_encode_destroy(g_utc_anim_encode_h[g_utc_anim_type]);
		assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
		g_utc_anim_encode_h[g_utc_anim_type] = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_image_util_anim_encode_destroy_n
 * @since_tizen		6.0
 * @description		Negative test case for image_util_anim_encode_destroy
 */
int utc_image_util_anim_encode_destroy_n(void)
{
	int ret;

	ret = image_util_anim_encode_destroy(NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}
