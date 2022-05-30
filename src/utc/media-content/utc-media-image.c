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
#include <limits.h>
#include <storage.h>

//& set: MediaImage

static image_meta_h g_image;
static char *g_val_str = NULL;
static int g_val_int = 0;
static double g_val_double = 0;
static int startup_ret = MEDIA_CONTENT_ERROR_NONE;

/**
 * @function		utc_media_image_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_image_startup(void)
{
	char *root_path = NULL;
	char image_path[PATH_MAX + 1] = { 0, };
	media_info_h media = NULL;

	if (storage_get_root_directory(0, &root_path) == STORAGE_ERROR_NONE) {
		snprintf(image_path, PATH_MAX, "%s/res/image.jpg", root_path);
		FREE_MEMORY(root_path);
	}

	startup_ret = media_content_connect();
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_content_connect failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_info_get_media_from_db_by_path(image_path, &media);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = media_info_insert_to_db(image_path, &media);
		if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
			FPRINTF("[Line : %d] media_info_insert_to_db failed.\\n", __LINE__);
			return;
		}
	}

	startup_ret = media_info_get_image(media, &g_image);
	media_info_destroy(media);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_info_get_image failed.\\n", __LINE__);
		return;
	}
}

/**
 * @function		utc_media_image_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_image_cleanup(void)
{
	if (g_image) {
		image_meta_destroy(g_image);
		g_image = NULL;
	}

	FREE_MEMORY(g_val_str);

	media_content_disconnect();
}

/**
 * @testcase		utc_image_meta_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_destroy()
 */
int utc_image_meta_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_destroy(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_destroy()
 */
int utc_image_meta_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_destroy(g_image), MEDIA_CONTENT_ERROR_NONE);
	g_image = NULL;

	return 0;
}

/**
 * @testcase		utc_image_meta_clone_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_clone()
 */
int utc_image_meta_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	image_meta_h image = NULL;

	assert_eq(image_meta_clone(&image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(image_meta_clone(NULL, g_image), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_clone_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_clone()
 */
int utc_image_meta_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	image_meta_h image = NULL;

	assert_eq(image_meta_clone(&image, g_image), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_destroy(image), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_media_id_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_get_media_id()
 */
int utc_image_meta_get_media_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_media_id(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(image_meta_get_media_id(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_media_id_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_get_media_id()
 */
int utc_image_meta_get_media_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_media_id(g_image, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_width_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_get_width()
 */
int utc_image_meta_get_width_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_width(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(image_meta_get_width(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_width_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_get_width()
 */
int utc_image_meta_get_width_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_width(g_image, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_height_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_get_height()
 */
int utc_image_meta_get_height_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_height(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(image_meta_get_height(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_height_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_get_height()
 */
int utc_image_meta_get_height_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_height(g_image, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_orientation_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_get_orientation()
 */
int utc_image_meta_get_orientation_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	media_content_orientation_e orientation = MEDIA_CONTENT_ORIENTATION_NOT_AVAILABLE;

	assert_eq(image_meta_get_orientation(NULL, &orientation), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(image_meta_get_orientation(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_orientation_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_get_orientation()
 */
int utc_image_meta_get_orientation_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	media_content_orientation_e orientation = MEDIA_CONTENT_ORIENTATION_NOT_AVAILABLE;

	assert_eq(image_meta_get_orientation(g_image, &orientation), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_date_taken_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_get_date_taken()
 */
int utc_image_meta_get_date_taken_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_date_taken(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(image_meta_get_date_taken(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_date_taken_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_get_date_taken()
 */
int utc_image_meta_get_date_taken_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_date_taken(g_image, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_exposure_time_n
 * @since_tizen		2.4
 * @description		Negative test case of image_meta_get_exposure_time()
 */
int utc_image_meta_get_exposure_time_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_exposure_time(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(image_meta_get_exposure_time(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_exposure_time_p
 * @since_tizen		2.4
 * @description		Positive test case of image_meta_get_exposure_time()
 */
int utc_image_meta_get_exposure_time_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_exposure_time(g_image, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_fnumber_n
 * @since_tizen		2.4
 * @description		Negative test case of image_meta_get_fnumber()
 */
int utc_image_meta_get_fnumber_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_fnumber(NULL, &g_val_double), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(image_meta_get_fnumber(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_fnumber_p
 * @since_tizen		2.4
 * @description		Positive test case of image_meta_get_fnumber()
 */
int utc_image_meta_get_fnumber_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_fnumber(g_image, &g_val_double), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_iso_n
 * @since_tizen		2.4
 * @description		Negative test case of image_meta_get_iso()
 */
int utc_image_meta_get_iso_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_iso(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(image_meta_get_iso(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_iso_p
 * @since_tizen		2.4
 * @description		Positive test case of image_meta_get_iso()
 */
int utc_image_meta_get_iso_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_iso(g_image, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_model_n
 * @since_tizen		2.4
 * @description		Negative test case of image_meta_get_model()
 */
int utc_image_meta_get_model_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_model(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(image_meta_get_model(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_model_p
 * @since_tizen		2.4
 * @description		Positive test case of image_meta_get_model()
 */
int utc_image_meta_get_model_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_get_model(g_image, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
