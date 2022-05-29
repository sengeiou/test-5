/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <media/camera.h>
#include <stdio.h>
#include <glib.h>
#include <pthread.h>
#include <system_info.h>
#ifndef TIZENIOT
#include <Elementary.h>
#include <Evas.h>
#endif /* TIZENIOT */
#include "tct_common.h"
#include "assert.h"


static int g_startup_err = CAMERA_ERROR_NONE;

static camera_h camera = NULL;
static bool camera_supported = false;
static bool front_flash_supported = false;
static bool back_flash_supported = false;

#ifndef TIZENIOT
static Evas_Object *camera_win = NULL;


static void _camera_window_delete(void *data, Evas_Object *obj, void *event)
{
	return;
}

static void _camera_window_destroy()
{
	if (camera_win) {
		evas_object_del(camera_win);
		camera_win = NULL;
	}

	return;
}

static void _camera_window_create()
{
	int w = 0;
	int h = 0;

	_camera_window_destroy();   /* destroy window in case the clean_up is not called */

	camera_win = elm_win_util_standard_add("camera_utc", "camera_utc");

	if (camera_win) {
		elm_win_borderless_set(camera_win, EINA_TRUE);
		evas_object_smart_callback_add(camera_win, "delete,request", _camera_window_delete, NULL);
		elm_win_screen_size_get(camera_win, NULL, NULL, &w, &h);
		evas_object_resize(camera_win, w, h);
		elm_win_autodel_set(camera_win, EINA_TRUE);
	} else {
		PRINT_UTC_LOG("\n\nfail to create window\n\n");
	}

	return;
}
#endif /* TIZENIOT */

/**
 * @function            utc_media_camera_setting_startup
 * @description         Called before each test. \n
                        This is the precondition for checking apis. \n
                        This precondition is camera_create api for checking device and privilege error.
 * @scenario            1. Create camera device and check camera error. \n
                        2. Get camera state for checking the camera works fine.
 * @parameter           N/A
 * @return              N/A
 */
void utc_media_camera_setting_startup(void)
{
	/* start of TC */
	int ret = CAMERA_ERROR_NONE;
	camera_state_e state = CAMERA_STATE_NONE;

	g_startup_err = CAMERA_ERROR_NONE;
	camera = NULL;
	camera_supported = false;

	system_info_get_platform_bool("http://tizen.org/feature/camera", &camera_supported);
	system_info_get_platform_bool("http://tizen.org/feature/camera.front.flash", &front_flash_supported);
	system_info_get_platform_bool("http://tizen.org/feature/camera.back.flash", &back_flash_supported);

	ret = camera_create(CAMERA_DEVICE_CAMERA0, &camera);
	if (ret != CAMERA_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " camera_create failed (code: 0x%x)\n", ret);
		g_startup_err = ret;
		return;
	}

	ret = camera_get_state(camera, &state);
	if (ret != CAMERA_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "camera_create failed (code: 0x%x)\n", ret);
		g_startup_err = ret;
		return;
	} else if (state != CAMERA_STATE_CREATED) {
		fprintf(stderr, "Startup warning at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "Unexpected camera state: %d\n", state);
		g_startup_err = ret;
		return;
	}

	return;
}

/**
 * @function            utc_media_camera_setting_cleanup
 * @description         Called after each test. \n
                        This is the postcondition for checking apis. \n
                        This postcondition is camera_destroy api for cleaning up all camera resource for next test. \n
 * @scenario            1. Destroy camera.
 * @parameter           N/A
 * @return              N/A
 */
void utc_media_camera_setting_cleanup(void)
{
	/* end of TC */
	int ret = CAMERA_ERROR_NONE;

	if (camera) {
		ret = camera_destroy(camera);
		if (ret != CAMERA_ERROR_NONE) {
			fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, "camera_destroy failed (code: 0x%x)\n", ret);
		}

		camera = NULL;
	}

	return;
}

/**
 * @testcase            utc_media_camera_set_display_n1
 * @since_tizen         2.3
 * @description         To check display setting with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_display_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display(NULL, CAMERA_DISPLAY_TYPE_NONE, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_display_n2
 * @since_tizen         2.3
 * @description         To check display setting with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters even if the display handle is needed.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in third parameter which is null pointer even if display mode is CAMERA_DISPLAY_TYPE_OVERLAY.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the third parameter should be display handle from application.
 */
int utc_media_camera_set_display_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display(camera, CAMERA_DISPLAY_TYPE_OVERLAY, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_display_p
 * @since_tizen         2.3
 * @description         To check display setting with valid pointers in parameters.
 * @scenario            This test is for checking display mode setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for setting display.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_display_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display(camera, CAMERA_DISPLAY_TYPE_NONE, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_preview_resolution_n1
 * @since_tizen         2.3
 * @description         To check preview resolution setting with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_preview_resolution_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_preview_resolution(NULL, 0, 0);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_preview_resolution_n2
 * @since_tizen         2.3
 * @description         To check display setting with invalid value which is not supported in parameters.
 * @scenario            This test is for checking invalid value in parameters which is not supported.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid value which is not supported in this device.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because invalid value.
 */
int utc_media_camera_set_preview_resolution_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_preview_resolution(camera, 1, 1);
	assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);

	return 0;
}


static bool _preview_resolution_cb(int width, int height, void *user_data)
{
	int *resolution = NULL;

	if (user_data == NULL) {
		fprintf(stderr, "user_data is NULL.\n");
		return false;
	}

	resolution = (int *)user_data;

	resolution[0] = width;
	resolution[1] = height;

	return false;
}

/**
 * @testcase            utc_media_camera_set_preview_resolution_p
 * @since_tizen         2.3
 * @description         To check preview resolution with valid pointers in parameters.
 * @scenario            This test is for checking preview resolution setting with valid pointers.
                        1. Check camera device which is supported or not. \n
                        2. Check supported preview resolution. \n
                        3. Set camera handle and supported values.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_preview_resolution_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int resolution[2] = {0, 0};

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	camera_foreach_supported_preview_resolution(camera, _preview_resolution_cb, resolution);

	ret = camera_set_preview_resolution(camera, resolution[0], resolution[1]);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_display_rotation_n1
 * @since_tizen         2.3
 * @description         To check display rotation with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_display_rotation_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_rotation(NULL, CAMERA_ROTATION_NONE);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_display_rotation_n2
 * @since_tizen         2.3
 * @description         To check display rotation which is out of range.
 * @scenario            This test is for checking value which is out of range in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set improper value such as -1, out of range.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the value is out of range.
 */
int utc_media_camera_set_display_rotation_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_rotation(camera, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_display_rotation_p
 * @since_tizen         2.3
 * @description         To check display rotation with proper value in parameters.
 * @scenario            This test is for checking display mode setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for setting rotation in display.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_display_rotation_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_rotation(camera, CAMERA_ROTATION_NONE);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}
/**
 * @testcase            utc_media_camera_set_capture_resolution_n
 * @since_tizen         2.3
 * @description         To check capture resolution with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_capture_resolution_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_capture_resolution(NULL, 0, 0);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

static bool _capture_resolution_cb(int width, int height, void *user_data)
{
	int *resolution = NULL;

	if (user_data == NULL) {
		fprintf(stderr, "user_data is NULL.\n");
		return false;
	}

	resolution = (int *)user_data;

	resolution[0] = width;
	resolution[1] = height;

	return false;
}

/**
 * @testcase            utc_media_camera_set_capture_resolution_p
 * @since_tizen         2.3
 * @description         To check resolution setting with proper values and pointers in parameters.
 * @scenario            This test is for checking capture resolution setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Search supported capture resolution with callback. \n
                        3. Set proper parameters such as supported resolution and valid camera handle.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_capture_resolution_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int resolution[2] = {0, 0};

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	camera_foreach_supported_capture_resolution(camera, _capture_resolution_cb, resolution);

	ret = camera_set_capture_resolution(camera, resolution[0], resolution[1]);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

static bool _capture_format_cb(camera_pixel_format_e format, void *user_data)
{
	int *ret = NULL;

	if (user_data == NULL) {
		fprintf(stderr, "user_data is NULL.\n");
		return false;
	}

	ret = (int *)user_data;

	*ret = format;

	return false;
}

/**
 * @testcase            utc_media_camera_set_capture_format_n1
 * @since_tizen         2.3
 * @description         To check capture format with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_capture_format_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int value = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	camera_foreach_supported_capture_format(camera, _capture_format_cb, &value);

	ret = camera_set_capture_format(NULL, value);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_capture_format_n2
 * @since_tizen         2.3
 * @description         To check capture format with invalid value in parameters.
 * @scenario            This test is for checking improper value in parameters which are out of range.
                        1. Check camera device which is supported or not. \n
                        2. Set improper value such as -1 that is out of range.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because of improper value.
 */
int utc_media_camera_set_capture_format_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_capture_format(camera, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_capture_format_p1
 * @since_tizen         2.3
 * @description         To check capture format with valid pointers in parameters.
 * @scenario            This test is for checking capture format setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Search supported capture format. \n
                        3. Set valid parameters and value for capture format which are supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_capture_format_p1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int value = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	camera_foreach_supported_capture_format(camera, _capture_format_cb, &value);

	ret = camera_set_capture_format(camera, value);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

static bool _capture_full_format_cb(camera_pixel_format_e format, void *user_data)
{
	int ret = CAMERA_ERROR_NONE;
	camera_pixel_format_e get_format = CAMERA_PIXEL_FORMAT_NV12;

	if (user_data == NULL) {
		fprintf(stderr, "user_data is NULL.\n");
		return false;
	}

	ret = camera_set_capture_format(camera, format);
	if (ret != CAMERA_ERROR_NONE) {
		fprintf(stderr, "camera_set_capture_format failed.\n");
		*((int *)user_data) = 1;
		return false;
	}

	ret = camera_get_capture_format(camera, &get_format);
	if (ret != CAMERA_ERROR_NONE) {
		fprintf(stderr, "camera_get_capture_format fail.\n");
		*((int *)user_data) = 1;
		return false;
	}

	if (format != get_format) {
		*((int *)user_data) = 1;
		fprintf(stderr, "different : format=[%d], get_format=[%d].\n", format, get_format);
		return false;
	}

	*((int *)user_data) = 0;

	return true;
}

/**
 * @testcase            utc_media_camera_set_capture_format_p2
 * @since_tizen         2.3
 * @description         To check capture format  with valid pointers in parameters.
 * @scenario            This test is for checking capture format with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Check supported capture format with callbacks. \n
                        3. Callback will check all format that camera supports. \n
                        4. Set valid parameters in camera and verify capture format set correctly.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_capture_format_p2(void)
{
	int ret = CAMERA_ERROR_NONE;
	int cb_err = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_capture_format(camera, _capture_full_format_cb, &cb_err);
	assert_eq(ret, CAMERA_ERROR_NONE);
	assert_eq(cb_err,0);

	return 0;
}


static bool _preview_format_cb(camera_pixel_format_e format, void *user_data)
{
	camera_pixel_format_e *ret = NULL;

	if (user_data == NULL) {
		fprintf(stderr, "user_data is NULL.\n");
		return false;
	}

	ret = (camera_pixel_format_e *)user_data;
	*ret = format;

	return false;
}

/**
 * @testcase            utc_media_camera_set_preview_format_n1
 * @since_tizen         2.3
 * @description         To check preview format with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_preview_format_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_pixel_format_e format = CAMERA_PIXEL_FORMAT_NV12;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	camera_foreach_supported_preview_format(camera, _preview_format_cb, &format);

	ret = camera_set_preview_format(NULL, format);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_preview_format_n2
 * @since_tizen         2.3
 * @description         To check preview format with improper value in second parameter.
 * @scenario            This test is for checking improper value in parameter which is out of range.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is -1, out of range.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the preview format value is improper.
 */
int utc_media_camera_set_preview_format_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_preview_format(camera, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_preview_format_p1
 * @since_tizen         2.3
 * @description         To check preview format with valid pointers in parameters.
 * @scenario            This test is for checking proper preview format value with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Search the supported preview format.
                        3. Set proper value for preview format.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_preview_format_p1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_pixel_format_e format = CAMERA_PIXEL_FORMAT_NV12;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	camera_foreach_supported_preview_format(camera, _preview_format_cb, &format);

	ret = camera_set_preview_format(camera, format);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


static bool _preview_full_format_cb(camera_pixel_format_e format, void *user_data)
{
	int ret = CAMERA_ERROR_NONE;
	camera_pixel_format_e get_format = CAMERA_PIXEL_FORMAT_NV12;

	if (user_data == NULL) {
		fprintf(stderr, "user_data is NULL.\n");
		return false;
	}

	ret = camera_set_preview_format(camera, format);
	if (ret != CAMERA_ERROR_NONE) {
		fprintf(stderr, "camera_set_preview_format failed. 0x%x [format %d]\n", ret, format);
		*((int *)user_data) = 1;
		return false;
	}

	ret = camera_get_preview_format(camera, &get_format);
	if (ret != CAMERA_ERROR_NONE) {
		fprintf(stderr, "camera_get_preview_format failed. 0x%x\n", ret);
		*((int *)user_data) = 1;
		return false;
	}

	if (format != get_format) {
		fprintf(stderr, "format[%d] and get_format[%d] are different.\n", format, get_format);
		*((int *)user_data) = 1;
		return false;
	}

	*((int *)user_data) = 0;

	return true;
}

/**
 * @testcase            utc_media_camera_set_preview_format_p2
 * @since_tizen         2.3
 * @description         To check preview format with valid pointers in parameters.
 * @scenario            This test is for checking preview format setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Search supported preview format with callback. \n
                        3. In callback, set preview format which are supported.
                        4. In callback, get preview format which is previous setting, comapre it.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_preview_format_p2(void)
{
	int ret = CAMERA_ERROR_NONE;
	int cb_err = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_preview_format(camera, _preview_full_format_cb, &cb_err);
	assert_eq(ret, CAMERA_ERROR_NONE);
	assert_eq(cb_err, 0);

	return 0;
}


/**
 * @testcase            utc_media_camera_get_preview_resolution_n1
 * @since_tizen         2.3
 * @description         To check preview resolution with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_get_preview_resolution_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int width = 0;
	int height = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_preview_resolution(NULL, &width, &height);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_preview_resolution_n2
 * @since_tizen         2.3
 * @description         To check preview resolution with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in second parameter.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second and third parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_get_preview_resolution_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_preview_resolution(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_preview_resolution_p
 * @since_tizen         2.3
 * @description         To check preview resolution with valid pointers in parameters.
 * @scenario            This test is for checking preview resolution setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for getting preview resolution.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_get_preview_resolution_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int width = 0;
	int height = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_preview_resolution(camera, &width, &height);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_display_rotation_n1
 * @since_tizen         2.3
 * @description         To check display rotate setting with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_get_display_rotation_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_rotation_e rotation = CAMERA_ROTATION_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_display_rotation(NULL, &rotation);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_display_rotation_n2
 * @since_tizen         2.3
 * @description         To check display rotate setting with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_get_display_rotation_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_display_rotation(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_display_rotation_p
 * @since_tizen         2.3
 * @description         To check display rotation setting with valid pointers in parameters.
 * @scenario            This test is for checking display rotation setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for getting display rotation.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_get_display_rotation_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_rotation_e rotation = CAMERA_ROTATION_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_display_rotation(camera, &rotation);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_capture_resolution_n1
 * @since_tizen         2.3
 * @description         To check capture resolution setting with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_get_capture_resolution_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int width = 0;
	int height = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_capture_resolution(NULL, &width, &height);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_capture_resolution_n2
 * @since_tizen         2.3
 * @description         To check capture resolution setting with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in second parameter.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second and third parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter should not be null pointer in getting function.
 */
int utc_media_camera_get_capture_resolution_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_capture_resolution(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_capture_resolution_p
 * @since_tizen         2.3
 * @description         To check capture resolution setting with valid pointers in parameters.
 * @scenario            This test is for checking capture resolution setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for getting capture resolution.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_get_capture_resolution_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int width = 0;
	int height = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_capture_resolution(camera, &width, &height);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_preview_format_n1
 * @since_tizen         2.3
 * @description         To check preview format setting with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_get_preview_format_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_pixel_format_e format = CAMERA_PIXEL_FORMAT_NV12;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret =  camera_get_preview_format(NULL, &format);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_preview_format_n2
 * @since_tizen         2.3
 * @description         To check preview format setting with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer for getting function.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter should not be null.
 */
int utc_media_camera_get_preview_format_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_preview_format(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_preview_format_p
 * @since_tizen         2.3
 * @description         To check preview format setting with valid pointers in parameters.
 * @scenario            This test is for checking preview format setting with valid parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for getting preview format.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_get_preview_format_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_pixel_format_e format = CAMERA_PIXEL_FORMAT_NV12;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret =  camera_get_preview_format(camera, &format);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


static void _preview_cb(camera_preview_data_s *frame, void *user_data)
{
	return;
}

/**
 * @testcase            utc_media_camera_set_preview_cb_n1
 * @since_tizen         2.3
 * @description         To check preview callback with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_preview_cb_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_preview_cb(NULL, _preview_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_preview_cb_n2
 * @since_tizen         2.3
 * @description         To check preview callback with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error. \n
                        The second parameter should not be null for checking preview status.
 */
int utc_media_camera_set_preview_cb_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_preview_cb(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_preview_cb_p
 * @since_tizen         2.3
 * @description         To check preview callback with valid pointers in parameters.
 * @scenario            This test is for checking preview callback setting with valid parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for preview callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_preview_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_preview_cb(camera, _preview_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_preview_cb_n
 * @since_tizen         2.3
 * @description         To check to unset preview callback with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_unset_preview_cb_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_unset_preview_cb(NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_preview_cb_p
 * @since_tizen         2.3
 * @description         To check to unset preview callback with valid pointers in parameters.
 * @scenario            This test is for checking about un-setting preview callback with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for release preview callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_unset_preview_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_unset_preview_cb(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


static void _media_packet_preview_cb(media_packet_h pkt, void *user_data)
{
	return;
}

/**
 * @testcase            utc_media_camera_set_media_packet_preview_cb_n1
 * @since_tizen         2.3
 * @description         To check media packet preview callback with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Check "mediapacket-preview-callback" is supported or not. \n
                        3-1. If supported, set mediapacket preview callback with invalid second parameter such as null. \n
                        3-2. Is not supported, Set invalid pointer which is camera handle null in first parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle and callback function is null.
 */
int utc_media_camera_set_media_packet_preview_cb_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_is_supported_media_packet_preview_cb(camera);

	if (!supported) {
		ret = camera_set_media_packet_preview_cb(camera, NULL, NULL);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else {
		ret = camera_set_media_packet_preview_cb(camera, NULL, NULL);
		assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_set_media_packet_preview_cb_n2
 * @since_tizen         2.3
 * @description         To check media packet preview callback with camera handle "null".
 * @scenario            This test is for checking invalid null pointer such as camera handle "null". \n
                        1. Set invalid pointer which is camera handle null in first parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_set_media_packet_preview_cb_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_media_packet_preview_cb(NULL, _media_packet_preview_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_media_packet_preview_cb_p
 * @since_tizen         2.3
 * @description         To check mediapacket preview callback with valid pointers in parameters.
 * @scenario            This test is for checking mediapacket preview callback with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for getting callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_media_packet_preview_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_is_supported_media_packet_preview_cb(camera);

	if (!supported) {
		ret = camera_set_media_packet_preview_cb(camera, _media_packet_preview_cb, NULL);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else {
		ret = camera_set_media_packet_preview_cb(camera, _media_packet_preview_cb, NULL);
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_media_packet_preview_cb_n
 * @since_tizen         2.3
 * @description         To check to unset mediapacket preview callback with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Unset media packet preview function with null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_unset_media_packet_preview_cb_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_unset_media_packet_preview_cb(NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_media_packet_preview_cb_p
 * @since_tizen         2.3
 * @description         To check to unset mediapakcet preview callback with valid pointers in parameters.
 * @scenario            This test is for unsetting mediapacket preview callback with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for unseting callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_unset_media_packet_preview_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_is_supported_media_packet_preview_cb(camera);

	if (!supported) {
		ret = camera_unset_media_packet_preview_cb(camera);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else {
		ret = camera_unset_media_packet_preview_cb(camera);
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}


static void _changed_cb(camera_state_e previous, camera_state_e current, bool by_asm, void *user_data)
{
	return;
}

/**
 * @testcase            utc_media_camera_set_state_changed_cb_n1
 * @since_tizen         2.3
 * @description         To check callback about state-change with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_state_changed_cb_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_state_changed_cb(NULL, _changed_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_state_changed_cb_n2
 * @since_tizen         2.3
 * @description         To check callback about state-change with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer for getting callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter should not be null.
 */
int utc_media_camera_set_state_changed_cb_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_state_changed_cb(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_state_changed_cb_p
 * @since_tizen         2.3
 * @description         To check callback about state-change with valid pointers in parameters.
 * @scenario            This test is for checking callback about state-change with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for setting callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_state_changed_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_state_changed_cb(camera, _changed_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_state_changed_cb_n
 * @since_tizen         2.3
 * @description         To check an unsetting callback about state-change with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_unset_state_changed_cb_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_unset_state_changed_cb(NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_state_changed_cb_p
 * @since_tizen         2.3
 * @description         To check an unsetting callback about state-change with valid pointers in parameters.
 * @scenario            This test is for checking invalid pointer in valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for unsetting callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_unset_state_changed_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_unset_state_changed_cb(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


static void _focus_changed_cb(camera_focus_state_e state, void *user_data)
{
	return;
}

/**
 * @testcase            utc_media_camera_set_focus_changed_cb_n1
 * @since_tizen         2.3
 * @description         To check to set focus changed callback  with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_focus_changed_cb_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_focus_changed_cb(NULL, _focus_changed_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_focus_changed_cb_n2
 * @since_tizen         2.3
 * @description         To check to set focus changed callback with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_set_focus_changed_cb_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_focus_changed_cb(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_focus_changed_cb_p
 * @since_tizen         2.3
 * @description         To check to set focus-changed callback with valid pointers in parameters.
 * @scenario            This test is for checking invalid pointer in valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for setting focus changed callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_focus_changed_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_focus_changed_cb(camera, _focus_changed_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_focus_changed_cb_n
 * @since_tizen         2.3
 * @description         To check to unset focus-changed callback with camera handle "null".
 * @scenario            This test is for checking the invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_unset_focus_changed_cb_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_unset_focus_changed_cb(NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_focus_changed_cb_p
 * @since_tizen         2.3
 * @description         To check to unset focus-changed callback with valid pointers in parameters.
 * @scenario            This test is for checking the valid pointer.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for unsetting focus changed callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_unset_focus_changed_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_unset_focus_changed_cb(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


static bool _preview_resolution_cb2(int width, int height, void *user_data)
{
	return true;
}

static void _device_state_changed_cb(camera_device_e device, camera_device_state_e state, void *user_data)
{
	return;
}

/**
 * @testcase            utc_media_camera_foreach_supported_preview_resolution_n1
 * @since_tizen         2.3
 * @description         To check supported preview resolution with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_foreach_supported_preview_resolution_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_preview_resolution(NULL, _preview_resolution_cb2, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_foreach_supported_preview_resolution_n2
 * @since_tizen         2.3
 * @description         To check supported preview resolution with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_foreach_supported_preview_resolution_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_preview_resolution(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_foreach_supported_preview_resolution_p
 * @since_tizen         2.3
 * @description         To check supported preview resolution with valid pointers in parameters.
 * @scenario            This test is for checking valid pointer in parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers for supported preview resolution callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_foreach_supported_preview_resolution_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_preview_resolution(camera, _preview_resolution_cb2, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


static bool _capture_resolution_cb2(int width, int height, void *user_data)
{
	return true;
}

/**
 * @testcase            utc_media_camera_foreach_supported_capture_resolution_n1
 * @since_tizen         2.3
 * @description         To check supported capture resolution with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_foreach_supported_capture_resolution_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_capture_resolution(NULL, _capture_resolution_cb2, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_foreach_supported_capture_resolution_n2
 * @since_tizen         2.3
 * @description         To check supported capture resolution with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in third parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter callback is null.
 */
int utc_media_camera_foreach_supported_capture_resolution_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_capture_resolution(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_foreach_supported_capture_resolution_p
 * @since_tizen         2.3
 * @description         To check supported capture resolution with valid pointers in parameters.
 * @scenario            This test is for checking supported capture resolution setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for supported capture resolution callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_foreach_supported_capture_resolution_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_capture_resolution(camera, _capture_resolution_cb2, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


static bool _capture_format_cb2(camera_pixel_format_e format, void *user_data)
{
	return true;
}

/**
 * @testcase            utc_media_camera_foreach_supported_capture_format_n1
 * @since_tizen         2.3
 * @description         To check supported capture format with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_foreach_supported_capture_format_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_capture_format(NULL, _capture_format_cb2, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_foreach_supported_capture_format_n2
 * @since_tizen         2.3
 * @description         To check supported capture format with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter callback is null.
 */
int utc_media_camera_foreach_supported_capture_format_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_capture_format(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_foreach_supported_capture_format_p
 * @since_tizen         2.3
 * @description         To check supported capture format with valid pointers in parameters.
 * @scenario            This test is for checking the supported capture format setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for callback about supported capture format.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_foreach_supported_capture_format_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_capture_format(camera, _capture_format_cb2, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


static bool _preview_format_cb2(camera_pixel_format_e format, void *user_data)
{
	return true;
}

/**
 * @testcase            utc_media_camera_foreach_supported_preview_format_n1
 * @since_tizen         2.3
 * @description         To check the supported preview format with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_foreach_supported_preview_format_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_preview_format(NULL, _preview_format_cb2, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_foreach_supported_preview_format_n2
 * @since_tizen         2.3
 * @description         To check the supported preview format with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter callback is null pointer.
 */
int utc_media_camera_foreach_supported_preview_format_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_preview_format(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_foreach_supported_preview_format_p
 * @since_tizen         2.3
 * @description         To check the supported preview format with valid pointers in parameters.
 * @scenario            This test is for checking the valid pointers with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for preview format callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_foreach_supported_preview_format_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_preview_format(camera, _preview_format_cb2, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_display_visible_n
 * @since_tizen         2.3
 * @description         To check display visible with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_display_visible_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_visible(NULL, true);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_display_visible_p
 * @since_tizen         2.3
 * @description         To check display visible with valid pointers in parameters.
 * @scenario            This test is for checking display visible setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for setting display visible.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_display_visible_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_visible(camera, true);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_is_display_visible_n1
 * @since_tizen         2.3
 * @description         To check display visible or not with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_is_display_visible_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool visible = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_is_display_visible(NULL, &visible);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_is_display_visible_n2
 * @since_tizen         2.3
 * @description         To check display visible with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer for getting true or false.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null pointer.
 */
int utc_media_camera_is_display_visible_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_is_display_visible(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_is_display_visible_p
 * @since_tizen         2.3
 * @description         To check display visible with valid pointers in parameters.
 * @scenario            This test is for checking value with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for check display visible.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_is_display_visible_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool visible = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_is_display_visible(camera, &visible);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_display_mode_n1
 * @since_tizen         2.3
 * @description         To check display mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_display_mode_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_mode(NULL, CAMERA_DISPLAY_MODE_LETTER_BOX);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_display_mode_n2
 * @since_tizen         2.3
 * @description         To check display mode with invalid value in parameters.
 * @scenario            This test is for checking value which is out of range.
                        1. Check camera device which is supported or not. \n
                        2. Set improper value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is out of range.
 */
int utc_media_camera_set_display_mode_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_mode(camera, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_display_mode_p
 * @since_tizen         2.3
 * @description         To check display mode with valid pointer and value in parameters.
 * @scenario            This test is for checking display mode setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for setting display mode.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_display_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_mode(camera, CAMERA_DISPLAY_MODE_LETTER_BOX);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_display_mode_n1
 * @since_tizen         2.3
 * @description         To check display mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_get_display_mode_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_display_mode_e mode = CAMERA_DISPLAY_MODE_LETTER_BOX;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_display_mode(NULL, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_display_mode_n2
 * @since_tizen         2.3
 * @description         To check display mode with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer for getting value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_get_display_mode_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_display_mode(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_display_mode_p
 * @since_tizen         2.3
 * @description         To check display mode with valid value in parameters.
 * @scenario            This test is for checking display mode setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for getting display mode.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_get_display_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_display_mode_e mode = CAMERA_DISPLAY_MODE_LETTER_BOX;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_display_mode(camera, &mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_capture_format_n1
 * @since_tizen         2.3
 * @description         To check capture format with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_get_capture_format_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_pixel_format_e format = CAMERA_PIXEL_FORMAT_NV12;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_capture_format(NULL, &format);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_capture_format_n2
 * @since_tizen         2.3
 * @description         To check capture format with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_get_capture_format_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_capture_format(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_capture_format_p
 * @since_tizen         2.3
 * @description         To check capture format with valid pointers in parameters.
 * @scenario            This test is for checking display mode setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for getting display.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_get_capture_format_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_pixel_format_e format = CAMERA_PIXEL_FORMAT_NV12;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_capture_format(camera, &format);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


static void _error_cb(int error, camera_state_e current_state, void *user_data)
{
	return;
}

/**
 * @testcase            utc_media_camera_set_error_cb_n1
 * @since_tizen         2.3
 * @description         To check display setting with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_error_cb_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_error_cb(NULL, _error_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_error_cb_n2
 * @since_tizen         2.3
 * @description         To check error callback with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_set_error_cb_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_error_cb(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_error_cb_p
 * @since_tizen         2.3
 * @description         To check error callback with valid pointers in parameters.
 * @scenario            This test is for checking error callback setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for setting error callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_error_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_error_cb(camera, _error_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_error_cb_n
 * @since_tizen         2.3
 * @description         To check unsetting error callback with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_unset_error_cb_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_unset_error_cb(NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_error_cb_p
 * @since_tizen         2.3
 * @description         To check unsetting error callback with valid pointers in parameters.
 * @scenario            This test is for checking unsetting error callback with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for unsetting error callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_unset_error_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_unset_error_cb(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


static void _interrupted_cb(camera_policy_e policy, camera_state_e previous, camera_state_e current, void *user_data)
{
	return;
}


static void _interrupt_started_cb(camera_policy_e policy, camera_state_e state, void *user_data)
{
	return;
}

/**
 * @testcase            utc_media_camera_set_interrupted_cb_n1
 * @since_tizen         2.3
 * @description         To check interrupted callback setting with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_interrupted_cb_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_interrupted_cb(NULL, _interrupted_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_interrupted_cb_n2
 * @since_tizen         2.3
 * @description         To check interrupted callback setting with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_set_interrupted_cb_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_interrupted_cb(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_interrupted_cb_p
 * @since_tizen         2.3
 * @description         To check interrupted callback with valid pointers in parameters.
 * @scenario            This test is for interrupted callback setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for setting interrupted callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_interrupted_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_interrupted_cb(camera, _interrupted_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_interrupted_cb_n
 * @since_tizen         2.3
 * @description         To check to unset interrupted callback with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_unset_interrupted_cb_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_unset_interrupted_cb(NULL);
	assert_neq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_interrupted_cb_p
 * @since_tizen         2.3
 * @description         To check to unset interrupted callback with valid pointers in parameters.
 * @scenario            This test is for checking interrupted callback setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for unsetting interrupted callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_unset_interrupted_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_unset_interrupted_cb(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


static void _attr_hdr_progress_cb(int percent, void *user_data)
{
	return;
}

/**
 * @testcase            utc_media_camera_attr_set_hdr_capture_progress_cb_n1
 * @since_tizen         2.3
 * @description         To check HDR capture progress callback with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_attr_set_hdr_capture_progress_cb_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_hdr_capture_progress_cb(NULL, _attr_hdr_progress_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_hdr_capture_progress_cb_n2
 * @since_tizen         2.3
 * @description         To check HDR capture progress callback with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Check HDR capture supported or not \n
                        3-1. If not supported, this api should return not supported error. \n
                        3-2. If supported, set invalid pointer in second parameter which is null pointer for callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_attr_set_hdr_capture_progress_cb_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_attr_is_supported_hdr_capture(camera);

	ret = camera_attr_set_hdr_capture_progress_cb(camera, NULL, NULL);

	if (supported) {
		assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_hdr_capture_progress_cb_p
 * @since_tizen         2.3
 * @description         To check HDR capture progress callback with valid pointers in parameters.
 * @scenario            This test is for checking HDR capture progress callback setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Check HDR capture supported or not. \n
                        3-1. If not supported, this api should return not supported error. \n
                        3-2. If supported, set valid parameters for setting HDR capture progress callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_hdr_capture_progress_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_attr_is_supported_hdr_capture(camera);

	ret = camera_attr_set_hdr_capture_progress_cb(camera, _attr_hdr_progress_cb, NULL);

	if (supported) {
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_unset_hdr_capture_progress_cb_n
 * @since_tizen         2.3
 * @description         To check to unset HDR capture prgress callback with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null pointer.
 */
int utc_media_camera_attr_unset_hdr_capture_progress_cb_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_unset_hdr_capture_progress_cb(NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_attr_unset_hdr_capture_progress_cb_p
 * @since_tizen         2.3
 * @description         To check to unset HDR capture progress callback with valid pointers in parameters.
 * @scenario            This test is for checking to unset HDR capture progress callback with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Check HDR capture supported or not. \n
                        3-1. If not supported, this api should return not-supported error.
                        3-2. If supported, set valid parameters for unsetting HDR capture progress callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_unset_hdr_capture_progress_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_attr_is_supported_hdr_capture(camera);

	ret = camera_attr_unset_hdr_capture_progress_cb(camera);

	if (supported) {
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_get_facing_direction_p
 * @since_tizen         3.0
 * @description         To check the facing direction of camera module with valid pointer and value in parameters.
 * @scenario            This test is for checking the facing direction status with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for getting the facing direction.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the third parameter is null.
 */
int utc_media_camera_get_facing_direction_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_facing_direction_e direction = CAMERA_FACING_DIRECTION_REAR;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_facing_direction(camera, &direction);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_facing_direction_n1
 * @since_tizen         3.0
 * @description         To check the facing direction of camera module with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_get_facing_direction_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_facing_direction_e direction = CAMERA_FACING_DIRECTION_REAR;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_facing_direction(NULL, &direction);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_facing_direction_n2
 * @since_tizen         3.0
 * @description         To check the facing direction of camera module with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_get_facing_direction_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_facing_direction(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_flash_state_p
 * @since_tizen         3.0
 * @description         To check the flash state with valid pointer and value in parameters.
 * @scenario            This test is for checking the flash state status with valid parameters.
                        1. Check camera and flash device which is supported or not. \n
                        2. Set valid parameters for getting the flash state.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the third parameter is null.
 */
int utc_media_camera_get_flash_state_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_flash_state_e state = CAMERA_FLASH_STATE_NOT_USED;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_flash_state(CAMERA_DEVICE_CAMERA0, &state);
	if (back_flash_supported) {
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_get_flash_state_n1
 * @since_tizen         3.0
 * @description         To check the flash state of camera module with camera handle "null".
 * @scenario            This test is for checking invalid value such as "-1". \n
                        1. Check camera and flash device which is supported or not. \n
                        2. Set invalid value which is camera device as "-1".
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_get_flash_state_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_flash_state_e state = CAMERA_FLASH_STATE_NOT_USED;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_flash_state(-1, &state);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_flash_state_n2
 * @since_tizen         3.0
 * @description         To check the flash state of camera module with invalid pointer in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera and flash device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_get_flash_state_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_flash_state(CAMERA_DEVICE_CAMERA0, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


#ifndef TIZENIOT

/**
 * @testcase            utc_media_camera_set_display_reuse_hint_p
 * @since_tizen         3.0
 * @description         To check display reuse hint with valid pointer and value in parameters.
 * @scenario            This test is for checking display reuse hint setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Start preview. \n
                        3. Set valid parameters for setting display reuse hint.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_display_reuse_hint_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	_camera_window_create();

	ret = camera_set_display(camera, CAMERA_DISPLAY_TYPE_OVERLAY, GET_DISPLAY(camera_win));
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_start_preview(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_set_display_reuse_hint(camera, true);

	camera_stop_preview(camera);

	_camera_window_destroy();

	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


/**
 * @testcase            utc_media_camera_set_display_reuse_hint_n1
 * @since_tizen         3.0
 * @description         To check display reuse hint with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Start preview. \n
                        3. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_display_reuse_hint_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_start_preview(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_set_display_reuse_hint(NULL, true);

	camera_stop_preview(camera);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_set_display_reuse_hint_n2
 * @since_tizen         3.0
 * @description         To check display reuse hint at invalid state.
 * @scenario            This test is for checking invalid state. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for setting display reuse hint.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera state is not #CAMERA_STATE_PREVIEW.
 */
int utc_media_camera_set_display_reuse_hint_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_reuse_hint(camera, true);

	assert_eq(ret, CAMERA_ERROR_INVALID_STATE);

	return 0;
}


/**
 * @testcase            utc_media_camera_get_display_reuse_hint_p
 * @since_tizen         3.0
 * @description         To check display reuse hint with valid value in parameters.
 * @scenario            This test is for checking display reuse hint getting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Start preview. \n
                        3. Set valid parameters for getting display reuse hint.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_get_display_reuse_hint_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool reuse_hint = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	_camera_window_create();

	ret = camera_set_display(camera, CAMERA_DISPLAY_TYPE_OVERLAY, GET_DISPLAY(camera_win));
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_start_preview(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_get_display_reuse_hint(camera, &reuse_hint);

	camera_stop_preview(camera);

	_camera_window_destroy();

	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


/**
 * @testcase            utc_media_camera_get_display_reuse_hint_n1
 * @since_tizen         3.0
 * @description         To check display reuse hint with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Start preview. \n
                        3. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_get_display_reuse_hint_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool reuse_hint = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_start_preview(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_get_display_reuse_hint(NULL, &reuse_hint);

	camera_stop_preview(camera);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_get_display_reuse_hint_n2
 * @since_tizen         3.0
 * @description         To check display reuse hint with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Start preview. \n
                        3. Set invalid pointer in second parameter which is null pointer for getting value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_get_display_reuse_hint_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_start_preview(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_get_display_reuse_hint(camera, NULL);

	camera_stop_preview(camera);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

#endif /* TIZENIOT */

/**
 * @testcase            utc_media_camera_get_device_state_p
 * @since_tizen         3.0
 * @description         To check device state with valid value in parameters.
 * @scenario            This test is for checking device state getting with valid parameters.
                        1. Get device state with valid parameters. \n
                        2. Check camera device which is supported or not. \n
                        3-1. If supported, compare "ret" value with CAMERA_ERROR_NONE. \n
                        3-1. If not supported, compare "ret" value with CAMERA_ERROR_NOT_SUPPORTED.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_get_device_state_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int check_ret = CAMERA_ERROR_NONE;
	camera_device_state_e device_state = CAMERA_DEVICE_STATE_NULL;

	ret = camera_get_device_state(CAMERA_DEVICE_CAMERA0, &device_state);

	if (camera_supported)
		check_ret = CAMERA_ERROR_NONE;
	else
		check_ret = CAMERA_ERROR_NOT_SUPPORTED;

	assert_eq(ret, check_ret);

	return 0;
}


/**
 * @testcase            utc_media_camera_get_device_state_n1
 * @since_tizen         3.0
 * @description         To check device state with invalid value in parameters.
 * @scenario            This test is for checking invalid value in parameters.
                        1. Get device state with invalid parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the first parameter is invalid.
 */
int utc_media_camera_get_device_state_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_device_state_e device_state = CAMERA_DEVICE_STATE_NULL;

	ret = camera_get_device_state(-1, &device_state);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_get_device_state_n2
 * @since_tizen         3.0
 * @description         To check device state with invalid value in parameters.
 * @scenario            This test is for checking invalid value in parameters.
                        1. Get device state with invalid parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_get_device_state_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	ret = camera_get_device_state(CAMERA_DEVICE_CAMERA0, NULL);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_add_device_state_changed_cb_p
 * @since_tizen         3.0
 * @description         To check adding device state changed callback with valid parameters.
 * @scenario            This test is for checking device state changed callback adding with valid parameters.
                        1. Add device state changed callback with valid parameters. \n
                        2. Check camera device which is supported or not. \n
                        3-1. If supported, compare "ret" value with CAMERA_ERROR_NONE. \n
                        3-1. If not supported, compare "ret" value with CAMERA_ERROR_NOT_SUPPORTED. \n
                        4. Remove added callback if cb_id is valid.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_add_device_state_changed_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int check_ret = CAMERA_ERROR_NONE;
	int cb_id = 0;

	ret = camera_add_device_state_changed_cb(_device_state_changed_cb, NULL, &cb_id);

	if (camera_supported)
		check_ret = CAMERA_ERROR_NONE;
	else
		check_ret = CAMERA_ERROR_NOT_SUPPORTED;

	if (cb_id > 0)
		camera_remove_device_state_changed_cb(cb_id);

	assert_eq(ret, check_ret);

	return 0;
}


/**
 * @testcase            utc_media_camera_add_device_state_changed_cb_n1
 * @since_tizen         3.0
 * @description         To check adding device state changed callback with invalid parameters.
 * @scenario            This test is for checking device state changed callback adding with invalid parameters.
                        1. Add device state changed callback with invalid parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the first parameter is null.
 */
int utc_media_camera_add_device_state_changed_cb_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int cb_id = 0;

	ret = camera_add_device_state_changed_cb(NULL, NULL, &cb_id);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_add_device_state_changed_cb_n2
 * @since_tizen         3.0
 * @description         To check adding device state changed callback with invalid parameters.
 * @scenario            This test is for checking device state changed callback adding with invalid parameters.
                        1. Add device state changed callback with invalid parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the third parameter is null.
 */
int utc_media_camera_add_device_state_changed_cb_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	ret = camera_add_device_state_changed_cb(_device_state_changed_cb, NULL, NULL);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_remove_device_state_changed_cb_p
 * @since_tizen         3.0
 * @description         To check removing device state changed callback with valid parameter.
 * @scenario            This test is for checking device state changed callback removing with valid parameter.
                        1. Add device state changed callback with valid parameters. \n
                        2. Check camera device which is supported or not. \n
                        3-1. If supported, remove device state changed callback with cb_id from camera_add_device_state_changed_cb(). \n
                        3-1. If not supported, compare "ret" value with CAMERA_ERROR_NOT_SUPPORTED.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success if camera device is supported.
 */
int utc_media_camera_remove_device_state_changed_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int cb_id = 0;

	ret = camera_add_device_state_changed_cb(_device_state_changed_cb, NULL, &cb_id);

	if (camera_supported) {
		assert_eq(ret, CAMERA_ERROR_NONE);
		assert_neq(cb_id, 0);

		ret = camera_remove_device_state_changed_cb(cb_id);

		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase            utc_media_camera_remove_device_state_changed_cb_n1
 * @since_tizen         3.0
 * @description         To check removing device state changed callback with invalid condition.
 * @scenario            This test is for checking device state changed callback removing with invalid condition.
                        1. Remove device state changed callback without adding device state changed callback. \n
                        2. Check camera device which is supported or not. \n
                        3-1. If supported, compare "ret" value with CAMERA_ERROR_INVALID_OPERATION. \n
                        3-2. If not supported, compare "ret" value with CAMERA_ERROR_NOT_SUPPORTED.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the first parameter is null.
 */
int utc_media_camera_remove_device_state_changed_cb_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int check_ret = CAMERA_ERROR_NONE;

	ret = camera_remove_device_state_changed_cb(0);

	if (camera_supported)
		check_ret = CAMERA_ERROR_INVALID_OPERATION;
	else
		check_ret = CAMERA_ERROR_NOT_SUPPORTED;

	assert_eq(ret, check_ret);

	return 0;
}


/**
 * @testcase            utc_media_camera_remove_device_state_changed_cb_n2
 * @since_tizen         3.0
 * @description         To check removing device state changed callback with valid parameter.
 * @scenario            This test is for checking device state changed callback removing with invalid parameter.
                        1. Remove device state changed callback with invalid parameter. \n
                        2. Check camera device which is supported or not. \n
                        3-1. If supported, remove device state changed callback with invalid cb_id. \n
                        3-2. If not supported, compare "ret" value with CAMERA_ERROR_NOT_SUPPORTED.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the first parameter is null.
 */
int utc_media_camera_remove_device_state_changed_cb_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	int cb_id = 0;

	ret = camera_add_device_state_changed_cb(_device_state_changed_cb, NULL, &cb_id);

	if (camera_supported) {
		assert_eq(ret, CAMERA_ERROR_NONE);
		assert_neq(cb_id, 0);

		ret = camera_remove_device_state_changed_cb(cb_id + 100);

		camera_remove_device_state_changed_cb(cb_id);

		assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase            utc_media_camera_set_interrupt_started_cb_n1
 * @since_tizen         4.0
 * @description         To check interrupt started callback setting with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_set_interrupt_started_cb_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_interrupt_started_cb(NULL, _interrupt_started_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_interrupt_started_cb_n2
 * @since_tizen         4.0
 * @description         To check interrupt started callback setting with invalid pointers in parameters.
 * @scenario            This test is for checking invalid null pointer in parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_camera_set_interrupt_started_cb_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_interrupt_started_cb(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_interrupt_started_cb_p
 * @since_tizen         4.0
 * @description         To check interrupt started callback with valid pointers in parameters.
 * @scenario            This test is for interrupt started callback setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for setting interrupted callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_interrupt_started_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_interrupt_started_cb(camera, _interrupt_started_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_interrupt_started_cb_n
 * @since_tizen         4.0
 * @description         To check to unset interrupt started callback with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_unset_interrupt_started_cb_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_unset_interrupt_started_cb(NULL);
	assert_neq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_unset_interrupt_started_cb_p
 * @since_tizen         4.0
 * @description         To check to unset interrupt started callback with valid pointers in parameters.
 * @scenario            This test is for checking interrupt started callback setting with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters for unsetting interrupt started callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_unset_interrupt_started_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_unset_interrupt_started_cb(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}
