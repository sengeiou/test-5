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

//& set: MediaImage

static image_meta_h g_image = NULL;
static image_meta_h g_image_dst = NULL;
static char *g_media_id = NULL;

static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool media_item_cb(media_info_h media, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_media_id(media, &g_media_id);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_media_id == NULL))
		return false;

	ret = media_info_get_image(media, &g_image);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_image == NULL))
		return false;

	return true;
}

/**
 * @function		utc_media_image_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_image_startup(void)
{
	filter_h filter = NULL;
	g_image = NULL;
	g_image_dst = NULL;
	g_media_id = NULL;

	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_connect();
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	char *condition = "MEDIA_TYPE=0 AND MEDIA_STORAGE_TYPE=0";	//Image

	media_filter_create(&filter);
	media_filter_set_condition(filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	media_filter_set_order(filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_DISPLAY_NAME, MEDIA_CONTENT_COLLATE_DEFAULT);
	if (filter == NULL) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "filter is NULL");
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
}

/**
 * @function		utc_media_image_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_image_cleanup(void)
{
	if (g_media_id) {
		free(g_media_id);
		g_media_id = NULL;
	}

	if (g_image) {
		image_meta_destroy(g_image);
		g_image = NULL;
	}

	if (g_image_dst) {
		image_meta_destroy(g_image_dst);
		g_image_dst = NULL;
	}

	media_content_disconnect();
}

/**
 * @testcase		utc_image_meta_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_destroy()
 */
int utc_image_meta_destroy_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = image_meta_destroy(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_destroy()
 */
int utc_image_meta_destroy_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	/* precondition */
	ret = image_meta_clone(&g_image_dst, g_image);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	/* actual test */
	ret = image_meta_destroy(g_image_dst);
	g_image_dst = NULL;
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_clone_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_clone()
 */
int utc_image_meta_clone_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = image_meta_clone(&g_image_dst, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_clone_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_clone()
 */
int utc_image_meta_clone_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = image_meta_clone(&g_image_dst, g_image);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_media_id_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_get_media_id()
 */
int utc_image_meta_get_media_id_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = image_meta_get_media_id(NULL, &media_id);

	if (media_id) {
		free(media_id);
		media_id = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_media_id_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_get_media_id()
 */
int utc_image_meta_get_media_id_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = image_meta_get_media_id(g_image, &media_id);

	if (media_id) {
		free(media_id);
		media_id = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_width_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_get_width()
 */
int utc_image_meta_get_width_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int width = 0;

	ret = image_meta_get_width(NULL, &width);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_width_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_get_width()
 */
int utc_image_meta_get_width_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int width = 0;

	ret = image_meta_get_width(g_image, &width);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_height_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_get_height()
 */
int utc_image_meta_get_height_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int height = 0;

	ret = image_meta_get_height(NULL, &height);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_height_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_get_height()
 */
int utc_image_meta_get_height_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int height = 0;

	ret = image_meta_get_height(g_image, &height);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_orientation_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_get_orientation()
 */
int utc_image_meta_get_orientation_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_orientation_e orientation = 0;

	ret = image_meta_get_orientation(NULL, &orientation);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_orientation_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_get_orientation()
 */
int utc_image_meta_get_orientation_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_orientation_e orientation = 0;

	ret = image_meta_get_orientation(g_image, &orientation);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_date_taken_n
 * @since_tizen		2.3
 * @description		Negative test case of image_meta_get_date_taken()
 */
int utc_image_meta_get_date_taken_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *date_taken = NULL;

	ret = image_meta_get_date_taken(NULL, &date_taken);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_date_taken_p
 * @since_tizen		2.3
 * @description		Positive test case of image_meta_get_date_taken()
 */
int utc_image_meta_get_date_taken_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *date_taken = NULL;

	ret = image_meta_get_date_taken(g_image, &date_taken);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (date_taken) {
		free(date_taken);
		date_taken = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_image_meta_get_exposure_time_n
 * @since_tizen		2.4
 * @description		Negative test case of image_meta_get_exposure_time()
 */
int utc_image_meta_get_exposure_time_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *exposure_time = NULL;

	ret = image_meta_get_exposure_time(NULL, &exposure_time);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_exposure_time_p
 * @since_tizen		2.4
 * @description		Positive test case of image_meta_get_exposure_time()
 */
int utc_image_meta_get_exposure_time_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *exposure_time = NULL;

	ret = image_meta_get_exposure_time(g_image, &exposure_time);

	if (exposure_time) {
		free(exposure_time);
		exposure_time = NULL;
	}
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_fnumber_n
 * @since_tizen		2.4
 * @description		Negative test case of image_meta_get_fnumber()
 */
int utc_image_meta_get_fnumber_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	double fnumber = 0;

	ret = image_meta_get_fnumber(NULL, &fnumber);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_fnumber_p
 * @since_tizen		2.4
 * @description		Positive test case of image_meta_get_fnumber()
 */
int utc_image_meta_get_fnumber_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	double fnumber = 0;

	ret = image_meta_get_fnumber(g_image, &fnumber);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_iso_n
 * @since_tizen		2.4
 * @description		Negative test case of image_meta_get_iso()
 */
int utc_image_meta_get_iso_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int iso = 0;

	ret = image_meta_get_iso(NULL, &iso);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_iso_p
 * @since_tizen		2.4
 * @description		Positive test case of image_meta_get_iso()
 */
int utc_image_meta_get_iso_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int iso = 0;

	ret = image_meta_get_iso(g_image, &iso);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_model_n
 * @since_tizen		2.4
 * @description		Negative test case of image_meta_get_model()
 */
int utc_image_meta_get_model_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *model = NULL;

	ret = image_meta_get_model(NULL, &model);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_meta_get_model_p
 * @since_tizen		2.4
 * @description		Positive test case of image_meta_get_model()
 */
int utc_image_meta_get_model_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *model = NULL;

	ret = image_meta_get_model(g_image, &model);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (model) {
		free(model);
		model = NULL;
	}

	return 0;
}
