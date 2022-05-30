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

#include <camera.h>
#include <stdio.h>
#include <string.h>
#include <system_info.h>
#include "assert.h"


static int g_startup_err = CAMERA_ERROR_NONE;

static camera_h camera = NULL;
static bool camera_supported = false;

#define BITRATE 16
#define GOPINTERVAL 4

/* foreach callbacks */
static bool _whitebalance_cb(camera_attr_whitebalance_e wb, void *user_data)
{
	if (user_data)
		*((camera_attr_whitebalance_e *)user_data) = wb;

	return true;
}

static bool _af_mode_cb(camera_attr_af_mode_e mode, void *user_data)
{
	if (user_data)
		*((camera_attr_af_mode_e *)user_data) = mode;

	return true;
}

static bool _af_mode_check_cb(camera_attr_af_mode_e mode, void *user_data)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_af_mode_e get_mode = CAMERA_ATTR_AF_NONE;

	if (user_data == NULL) {
		fprintf(stderr, "user_data is NULL.\n");
		return false;
	}

	ret = camera_attr_set_af_mode(camera, mode);
	if (ret != CAMERA_ERROR_NONE) {
		fprintf(stderr, "camera_attr_set_af_mode ret=[%d], mode=[%d]", ret, mode);
		*((int *)user_data) = 1;
		return false;
	}

	ret = camera_attr_get_af_mode(camera, &get_mode);
	if (ret != CAMERA_ERROR_NONE) {
		fprintf(stderr, "camera_attr_get_af_mode ret=[%d], mode=[%d]", ret, get_mode);
		*((int *)user_data) = 1;
		return false;
	}

	if (mode != get_mode) {
		fprintf(stderr, "camera_attr_get_af_mode mode=[%d], get_mode=[%d] are not same", mode, get_mode);
		*((int *)user_data) = 1;
		return false;
	}

	*((int *)user_data) = 0;

	return true;
}

static bool _effect_cb(camera_attr_effect_mode_e effect, void *user_data)
{
	if (user_data)
		*((camera_attr_effect_mode_e *)user_data) = effect;

	return true;
}

static bool _exposure_mode_cb(camera_attr_exposure_mode_e mode, void *user_data)
{
	if (user_data)
		*((camera_attr_exposure_mode_e *)user_data) = mode;

	return true;
}

static bool _flash_mode_cb(camera_attr_flash_mode_e mode, void *user_data)
{
	if (user_data)
		*((camera_attr_flash_mode_e *)user_data) = mode;

	return true;
}

static bool _fps_cb(camera_attr_fps_e fps, void *user_data)
{
	if (user_data)
		*((camera_attr_fps_e *)user_data) = fps;

	return true;
}

static bool _scene_mode_cb(camera_attr_scene_mode_e mode, void *user_data)
{
	if (user_data)
		*((camera_attr_scene_mode_e *)user_data) = mode;

	return true;
}

static bool _stream_flip_cb(camera_flip_e flip, void *user_data)
{
	if (user_data)
		*((camera_flip_e *)user_data) = flip;

	return true;
}

static bool _stream_rotation_cb(camera_rotation_e rotation, void *user_data)
{
	if (user_data)
		*((camera_rotation_e *)user_data) = rotation;

	return true;
}

static bool _theater_mode_cb(camera_attr_theater_mode_e mode, void *user_data)
{
	if (user_data)
		*((camera_attr_theater_mode_e *)user_data) = mode;

	return true;
}

static bool _ptz_type_cb(camera_attr_ptz_type_e mode, void *user_data)
{
	if (user_data)
		*((camera_attr_ptz_type_e *)user_data) = mode;

	return true;
}

static bool _iso_cb(camera_attr_iso_e iso, void *user_data)
{
	if (user_data)
		*((camera_attr_iso_e *)user_data) = iso;

	return true;
}

/**
 * @function            utc_media_camera_attr_startup
 * @description         Called before each test.
                        This is the precondition for checking apis. \n
                        This precondition is camera_create api for checking device and privilege error.
 * @scenario            1. Create camera device and check camera error. \n
                        2. Get camera state for checking the camera works fine.
 * @parameter           N/A
 * @return              N/A
 */
void utc_media_camera_attr_startup(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_state_e state = CAMERA_STATE_NONE;

	g_startup_err = CAMERA_ERROR_NONE;
	camera = NULL;
	camera_supported = false;

	system_info_get_platform_bool("http://tizen.org/feature/camera", &camera_supported);

	ret = camera_create(CAMERA_DEVICE_CAMERA0, &camera);
	if (ret != CAMERA_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " camera_create failed (code: %d)\n", ret);
		g_startup_err = ret;
		return;
	}

	ret = camera_get_state(camera, &state);
	if (ret != CAMERA_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "camera_create failed (code: %d)\n", ret);
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
 * @function            utc_media_camera_attr_cleanup
 * @description         Called after each test.
                        This is the postcondition for checking apis. \n
                        This postcondition is camera_destroy api for cleaning up the resources properly.
 * @scenario            1. Destroy camera.
 * @parameter           N/A
 * @return              N/A
 */
void utc_media_camera_attr_cleanup(void)
{
	/* end of TC */
	int ret = CAMERA_ERROR_NONE;

	if (camera) {
		ret = camera_destroy(camera);
		if (ret != CAMERA_ERROR_NONE) {
			fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, "camera_destroy failed (code: %d)\n", ret);
		} else
			camera = NULL;
	}

	return;
}

/**
 * @testcase            utc_media_camera_attr_set_preview_fps_n1
 * @since_tizen         2.3
 * @description         To check preview-fps-attribute with proper setting value or not.
 * @scenario            This test is for checking invalid parameter such as the camera handle "null".
 * @parameter           N/A
 * @return              1 is the fail.  You need to check log in tct tool.\n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_attr_set_preview_fps_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_preview_fps(NULL, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_preview_fps_n2
 * @since_tizen         2.3
 * @description         To check preview-fps-attribute within proper fps value range or not.
 * @scenario            This test is for checking invalid parameter with the invalid value which is out of range.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is out of range.
 */
int utc_media_camera_attr_set_preview_fps_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_preview_fps(camera, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_preview_fps_p
 * @since_tizen         2.3
 * @description         To check preview-fps-attribute within proper fps value range or not.
 * @scenario            This test is for checking valid paramter with supported and predefined value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success because the setting value is supported and predefined value.
 */
int utc_media_camera_attr_set_preview_fps_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_preview_fps(camera, CAMERA_ATTR_FPS_AUTO);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_image_quality_n1
 * @since_tizen         2.3
 * @description         To check image quality attribute with proper setting value or not.
 * @scenario            This test is for checking invalid parameter such as the camera handle "null".
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_attr_set_image_quality_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_image_quality(NULL, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_image_quality_n2
 * @since_tizen         2.3
 * @description         To check image quality within proper quality value range or not.
 * @scenario            This test is for checking invalid parameter with the invalid value which is out of range.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is out of range.
 */
int utc_media_camera_attr_set_image_quality_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_image_quality(camera, -1);
	assert_neq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_image_quality_p
 * @since_tizen         2.3
 * @description         To check image quality within proper image quailty value or not.
 * @scenario            This test is for checking valid parameter with the positive value up to 100 percent.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be sucess because the setting value is supported.
 */
int utc_media_camera_attr_set_image_quality_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_image_quality(camera, 100);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_preview_fps_n1
 * @since_tizen         2.3
 * @description         To check preview-fps attribute that user set correctly.
 * @scenario            This test is for checking invalid parameter such as the camera handle "null".
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" vaule should be error because the camera handle is null.
 */
int utc_media_camera_attr_get_preview_fps_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_preview_fps(NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_preview_fps_n2
 * @since_tizen         2.3
 * @description         To check preview-fps attribute that user set correctly.
 * @scenario            This test is for checking invalid memory pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error becuase the second parameter is null.
 */
int utc_media_camera_attr_get_preview_fps_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_preview_fps(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_preview_fps_p1
 * @since_tizen         2.3
 * @description         To check preview-fps attribute that user set correctly.
 * @scenario            This test is for checking valid value that user already set default value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_preview_fps_p1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_fps_e value = CAMERA_ATTR_FPS_AUTO;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_preview_fps(camera, &value);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_preview_fps_p2
 * @since_tizen         2.3
 * @description         To check preview-fps attribute that user set value.
 * @scenario            The test is for checking valid value that user set value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_preview_fps_p2(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_fps_e value = CAMERA_ATTR_FPS_AUTO;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_preview_fps(camera, CAMERA_ATTR_FPS_AUTO);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_get_preview_fps(camera, &value);
	assert_eq(ret, CAMERA_ERROR_NONE);
	assert_eq(value, CAMERA_ATTR_FPS_AUTO);

	return 0;
}


/**
 * @testcase            utc_media_camera_attr_get_image_quality_n1
 * @since_tizen         2.3
 * @description         To check image quality with proper parameter or not.
 * @scenario            This test is for checking invalid parameter such as the camera handle "null".
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because of camera handle "null".
 */
int utc_media_camera_attr_get_image_quality_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_image_quality(NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_image_quality_n2
 * @since_tizen         2.3
 * @description         To check image quality with proper parameter or not.
 * @scenario            This test is for checking invalid pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because second parameter is null.
 */
int utc_media_camera_attr_get_image_quality_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_image_quality(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_image_quality_p
 * @since_tizen         2.3
 * @description         To check image quality which user set properly or already set default value.
 * @scenario            This test is for checking which user value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success with proper value.
 */
int utc_media_camera_attr_get_image_quality_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int value = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_image_quality(camera, &value);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_zoom_n1
 * @since_tizen         2.3
 * @description         To check zoom attribute with proper setting value or not.
 * @scenario            This test is for checking invalid parameter such as the camera handle "null".
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_attr_set_zoom_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_zoom(NULL, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_zoom_p
 * @since_tizen         2.3
 * @description         To check zoom attribute within zoom value range or not.
 * @scenario            This test is for checking the value within proper range.
 * @paramter            N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_zoom_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_zoom_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (min > max) {
		fprintf(stderr, "zoom is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_zoom(camera, min);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_af_mode_n1
 * @since_tizen         2.3
 * @description         To check auto-focus mode attribute that set by user or is default value.
 * @scenario            This test is for checking invalid parameter such as the camera handle "null".
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error becuase the camera handle is null.
 */
int utc_media_camera_attr_set_af_mode_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_af_mode(NULL, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_af_mode_n2
 * @since_tizen         2.3
 * @description         To check auto-focus mode attribute within invalid range of auto-focus mode.
 * @scenario            This test is for checking invalid parameter which is out of range.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error becuase the second parameter is out of range.
 */
int utc_media_camera_attr_set_af_mode_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_af_mode(camera, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_af_mode_p
 * @since_tizen         2.3
 * @description         To check auto-focus mode attribute within valid range value.
 * @scenario            This test is for checking valid parameter within the valid range.
                        1. After checking auto-focus mode, the user can get the value which is in valid range. \n
                        2. Then, the usr set the auto-focus mode correctly. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_af_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int af_mode = CAMERA_ATTR_AF_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_af_mode(camera, _af_mode_cb, &af_mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_set_af_mode(camera, af_mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_exposure_mode_n1
 * @since_tizen         2.3
 * @description         To check exposure mode attribute within invalid exposure mode.
 * @scenario            This test is for checking valid parameter within the invalid range. \n
                        1. Check camera device which is supported or not. \n
                        2. Check exposure mode which is supported in this device. \n
                        3. Set invalid exposure mode.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because of invalid parameter.
 */
int utc_media_camera_attr_set_exposure_mode_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_exposure_mode(camera, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_exposure_mode_n2
 * @since_tizen         2.3
 * @description         To check exposure mode attribute with invalid handle.
 * @scenario            This test is for checking valid parameter within the invalid range. \n
                        1. Check camera device which is supported or not. \n
                        2. Check exposure mode which is supported in this device. \n
                        3. Set invalid handle if it's supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because value is out of range.
 */
int utc_media_camera_attr_set_exposure_mode_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	int exposure_mode = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_exposure_mode(camera, _exposure_mode_cb, &exposure_mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (exposure_mode < 0) {
		fprintf(stderr, "there is no supported exposure mode.\n");
		return 0;
	}

	ret = camera_attr_set_exposure_mode(NULL, (camera_attr_exposure_mode_e)exposure_mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_attr_set_exposure_mode_p
 * @since_tizen         2.3
 * @description         To check exposure mode attribute within the valid range.
 * @scenario            This test is for checking valid parameter setting within the valid range. \n
                        1. Check camera device which is supported or not. \n
                        2. Check exposure mode which is supported in this device. \n
                        3. Set value as supported parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success because value is in valid range.
 */
int utc_media_camera_attr_set_exposure_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int exposure_mode = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_exposure_mode(camera, _exposure_mode_cb, &exposure_mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (exposure_mode < 0) {
		fprintf(stderr, "there is no supported exposure mode.\n");
		return 0;
	}

	ret = camera_attr_set_exposure_mode(camera, (camera_attr_exposure_mode_e)exposure_mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_exposure_n1
 * @since_tizen         2.3
 * @description         To check exposure value with invalid pointer, camera handle "null".
 * @scenario            This test is for checking invalid parameters such as camera handle "null" and invalid range. \n
                        1. Check camera device which is supported or not \n
                        2. Set invalid handle if it's supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_exposure_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_exposure_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (min > max) {
		fprintf(stderr, "exposure is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_exposure(NULL, max);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;

}

/**
 * @testcase            utc_media_camera_attr_set_exposure_n2
 * @since_tizen         2.3
 * @description         To check exposure value within the invalid range.
 * @scenario            This test is for checking invalid parameter such as not supported value range. \n
                        1. Check camera device which is supported or not \n
                        2. Get exposure value range. \n
                        3. Set exposure value which is out of range.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because invalid range of exposure.
 */
int utc_media_camera_attr_set_exposure_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_exposure_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (max < min) {
		fprintf(stderr, "exposure is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_exposure(camera, min - 1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;

}

/**
 * @testcase            utc_media_camera_attr_set_exposure_p
 * @since_tizen         2.3
 * @description         To check exposure value within the valid range.
 * @scenario            This test is for checking valid parameter such as supported exposure value. \n
                        1. Check camera device which is supported or not. \n
                        2. Get exposure mode which is supported in order to find supported exposure mode. \n
                        3. Set exposure mode which is supported. \n
                        4. Get exposure value which is supported. \n
                        5. Set exposure value which is in the range of value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_exposure_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int exposure_mode = -1;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_exposure_mode(camera, _exposure_mode_cb, &exposure_mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (exposure_mode < 0) {
		ret = camera_attr_set_exposure_mode(camera, exposure_mode);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else {
		ret = camera_attr_set_exposure_mode(camera, (camera_attr_exposure_mode_e)exposure_mode);
		assert_eq(ret, CAMERA_ERROR_NONE);

		ret = camera_attr_get_exposure_range(camera, &min, &max);
		assert_eq(ret, CAMERA_ERROR_NONE);

		if (max < min) {
			fprintf(stderr, "exposure is not supported\n");
			return 0;
		}

		ret = camera_attr_set_exposure(camera, max);
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;

}

/**
 * @testcase            utc_media_camera_attr_set_iso_n1
 * @since_tizen         2.3
 * @description         To check ISO value with invalid pointer parameter.
 * @scenario            This test is for checking invalid parameter such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer parameter which is camera handle "null".
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_iso_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int iso = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_iso(camera, _iso_cb, &iso);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (iso < 0) {
		fprintf(stderr, "iso is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_iso(NULL, (camera_attr_iso_e)iso);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_iso_n2
 * @since_tizen         2.3
 * @description         To check ISO value within invalid range.
 * @scenario            This test is for checking invalid parameter which is out of range. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid range ISO value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because of value which is out of range.
 */
int utc_media_camera_attr_set_iso_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_iso(camera, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_iso_p
 * @since_tizen         2.3
 * @description         To check ISO value within valid range.
 * @scenario            This test is for checking valid range in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid range ISO value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_iso_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int iso = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_iso(camera, _iso_cb, &iso);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (iso < 0) {
		fprintf(stderr, "iso is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_iso(camera, (camera_attr_iso_e)iso);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_brightness_n1
 * @since_tizen         2.3
 * @description         To check brightness value with camera handle null.
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set camera handle as null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_brightness_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_brightness_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (min > max) {
		fprintf(stderr, "brightness is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_brightness(NULL, max);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;

}

/**
 * @testcase            utc_media_camera_attr_set_brightness_n2
 * @since_tizen         2.3
 * @description         To check brightness value within invalid range.
 * @scenario            This test is for checking invalid range of second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Get valid range of brightness value. \n
                        3. Check brightness value which is supported or not. \n
                        4. Set brightness value which is out of range.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because brightness value is out of range.
 */
int utc_media_camera_attr_set_brightness_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_brightness_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if(min > max){
		fprintf(stderr, "brightness is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_brightness(camera, max + 1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;

}

/**
 * @testcase            utc_media_camera_attr_set_brightness_p
 * @since_tizen         2.3
 * @description         To check brightness value within valid range.
 * @scenario            This test is for checking valid range of second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Get valid range of brightness value. \n
                        3. Set valid range of brightness value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_brightness_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_brightness_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if(min > max){
		fprintf(stderr, "brightness is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_brightness(camera, max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_contrast_n1
 * @since_tizen         2.3
 * @description         To check contrast value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_contrast_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_contrast_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (min > max) {
		fprintf(stderr, "contrast is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_contrast(NULL, max);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_contrast_n2
 * @since_tizen         2.3
 * @description         To check contrast value within invalid range.
 * @scenario            This test is for checking invalid parameter which is out of range. \n
                        1. Check camera device which is supported or not. \n
                        2. Get valid contrast range. \n
                        3. Check contrast which is supported or not. \n
                        4. Set invalid contrast value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because of invalid contrast value.
 */
int utc_media_camera_attr_set_contrast_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_contrast_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (min > max) {
		fprintf(stderr, "contrast is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_contrast(camera, max + 1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_contrast_p
 * @since_tizen         2.3
 * @description         To check contrast value within valid range.
 * @scenario            This test is for checking valid parameter . \n
                        1. Check camera device which is supported or not. \n
                        2. Get valid contrast range. \n
                        3. Check contrast which is supported or not. \n
                        4. Set valid contrast value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_contrast_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_contrast_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (min > max) {
		fprintf(stderr, "contrast is not supported.\n");
		return 0;
	}
	ret = camera_attr_set_contrast(camera, max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_whitebalance_n1
 * @since_tizen         2.3
 * @description         To check whitebalance mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not.
                        2. get the supported whitbalance mode.
                        3. Check whitebalance mode which is supported or not.
                        4. Set invalid pointer which is camera is "null".
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_whitebalance_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int wb = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_whitebalance(camera, _whitebalance_cb, &wb);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (wb < 0) {
		fprintf(stderr, "whitebalance is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_whitebalance(NULL, (camera_attr_whitebalance_e)wb);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_whitebalance_n2
 * @since_tizen         2.3
 * @description         To check whitebalance mode within invalid range.
 * @scenario            This test is for checking invalid parameter which is out of range. \n
                        1. Check camera device which is supported or not. \n
                        2. Get valid whitebalance mode. \n
                        3. Check whitebalance mode which is supported or not. \n
                        4. Set invalid whitebalance mode.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the whitebalance mode is out of range.
 */
int utc_media_camera_attr_set_whitebalance_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	int wb = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_whitebalance(camera, _whitebalance_cb, &wb);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (wb < 0) {
		fprintf(stderr, "whitebalance is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_whitebalance(camera, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_whitebalance_p
 * @since_tizen         2.3
 * @description         To check whitebalance mode within valid range.
 * @scenario            This test is for checking valid parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Get valid whitebalance mode. \n
                        3. Check whitebalance mode which is supported or not. \n
                        4. Set valid whitebalance mode.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_whitebalance_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int wb = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_whitebalance(camera, _whitebalance_cb, &wb);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (wb < 0) {
		fprintf(stderr, "whitebalance is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_whitebalance(camera, (camera_attr_whitebalance_e)wb);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_effect_n1
 * @since_tizen         2.3
 * @description         To check effect mode with invalid parameter.
 * @scenario            This test is for checking invalid pointer in second paramter. \n
                        1. Check camera device which is supported or not. \n
                        2. Get invalid null pointer in second paramter.
 * @paramter            N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_effect_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_effect(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_effect_n2
 * @since_tizen         2.3
 * @description         To check effect value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_effect_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_effect_mode_e effect = CAMERA_ATTR_EFFECT_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_effect(NULL, &effect);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_effect_p
 * @since_tizen         2.3
 * @description         To check effect mode within valid range.
 * @scenario            This test is for checking valid range in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid effect mode value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_effect_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_effect_mode_e effect = CAMERA_ATTR_EFFECT_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_effect(camera, &effect);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_scene_mode_n1
 * @since_tizen         2.3
 * @description         To check scene mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_scene_mode_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_scene_mode_e mode = CAMERA_ATTR_SCENE_MODE_NORMAL;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_scene_mode(NULL, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;

}

/**
 * @testcase            utc_media_camera_attr_get_scene_mode_n2
 * @since_tizen         2.3
 * @description         To check scene mode with invalid parameter.
 * @scenario            This test is for checking invalid pointer in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer such as null in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error.
 */

int utc_media_camera_attr_get_scene_mode_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_scene_mode(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_scene_mode_p
 * @since_tizen         2.3
 * @description         To check scene mode within valid range.
 * @scenario            This test is for checking valid range in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid range scene mode value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.

 */
int utc_media_camera_attr_get_scene_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_scene_mode_e mode = CAMERA_ATTR_SCENE_MODE_NORMAL;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_scene_mode(camera, &mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_enabled_tag_n1
 * @since_tizen         2.3
 * @description         To check camera-exif-tag with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_is_enabled_tag_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool enable = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_enabled_tag(NULL, &enable);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_enabled_tag_n2
 * @since_tizen         2.3
 * @description         To check camera-exif-tag with invalid pointer.
 * @scenario            This test is for checking invalid pointer about getting functions. \n
                        1. Check camera device which is supported or not. \n
                        2. Set null pointer which is second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because null pointer is set in getting parameter.
 */
int utc_media_camera_attr_is_enabled_tag_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_enabled_tag(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_enabled_tag_p
 * @since_tizen         2.3
 * @description         To check image tag enabled or not.
 * @scenario            This test is for notice ready to write tag. \n
                        1. Check camera device which is supported or not. \n
                        2. Get value which is tag enabled or not.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_is_enabled_tag_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool enable = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_enabled_tag(camera, &enable);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tag_image_description_n1
 * @since_tizen         2.3
 * @description         To check user image description with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_tag_image_description_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	char *description = NULL;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tag_image_description(NULL, &description);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tag_image_description_n2
 * @since_tizen         2.3
 * @description         To check user image description with camera handle "null".
 * @scenario            This test is for checking invalid pointer in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer about getting function.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because null is set.
 */
int utc_media_camera_attr_get_tag_image_description_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tag_image_description(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tag_image_description_p1
 * @since_tizen         2.3
 * @description         To check image description in image which user will make.
 * @scenario            This test is for checking valid pointer in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_get_tag_image_description_p1(void)
{
	int ret = CAMERA_ERROR_NONE;
	char *description = NULL;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tag_image_description(camera, &description);

	if (description) {
		free(description);
		description = NULL;
	}

	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tag_image_description_p2
 * @since_tizen         2.3
 * @description         To check image description in image which user will make. \n
                        Temporarily, the buffer for reading image description should be freed.
 * @scenario            This test is for checking string according to the writing and reading. \n
                        1. Check camera device which is supported or not. \n
                        2. Set image description. \n
                        3. Get image description and check correctly set.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_get_tag_image_description_p2(void)
{
	int ret = CAMERA_ERROR_NONE;
	char *set_description = "name";
	char *get_description = NULL;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_tag_image_description(camera, set_description);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tag_image_description(camera, &get_description);
	if (get_description == NULL || strcmp(set_description, get_description)) {
		fprintf(stderr, "image description are not same.\n");

		if (get_description) {
			free(get_description);
			get_description = NULL;
		}

		return 1;
	}

	if (get_description) {
		free(get_description);
		get_description = NULL;
	}

	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


/**
 * @testcase            utc_media_camera_attr_get_tag_orientation_n1
 * @since_tizen         2.3
 * @description         To check image orientation tag with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_tag_orientation_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_tag_orientation_e orientation = CAMERA_ATTR_TAG_ORIENTATION_TOP_LEFT;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tag_orientation(NULL, &orientation);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;

}

/**
 * @testcase            utc_media_camera_attr_get_tag_orientation_n2
 * @since_tizen         2.3
 * @description         To check image orientation tag with camera handle "null".
 * @scenario            This test is for checking invalid pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because null is set.
 */
int utc_media_camera_attr_get_tag_orientation_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tag_orientation(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tag_orientation_p
 * @since_tizen         2.3
 * @description         To check orientation tag arrtributes.
 * @scenario            This test is for checking valid pointer in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointer for getting value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_get_tag_orientation_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_tag_orientation_e orientation = CAMERA_ATTR_TAG_ORIENTATION_TOP_LEFT;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tag_orientation(camera, &orientation);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tag_software_n1
 * @since_tizen         2.3
 * @description         To check imaging software version tag with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_tag_software_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	char *software = NULL;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tag_software(NULL, &software);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tag_software_n2
 * @since_tizen         2.3
 * @description         To check imaging software version tag with "null".
 * @scenario            This test is for checking invalid pointer with "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because null is set.
 */
int utc_media_camera_attr_get_tag_software_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tag_software(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tag_software_p1
 * @since_tizen         2.3
 * @description         To get software version tag string that user set. \n
                        Temporarily, the buffer for reading image description should be freed.
 * @scenario            This test is for checking valid pointer in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_get_tag_software_p1(void)
{
	int ret = CAMERA_ERROR_NONE;
	char *software = NULL;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tag_software(camera, &software);

	if (software) {
		free(software);
		software = NULL;
	}

	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tag_software_p2
 * @since_tizen         2.3
 * @description         To get software version tag string that user set. \n
                        Temporarily, the buffer for reading image description should be freed.
 * @scenario            This test is for checking valid pointer in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointer and string. \n
                        3. Check string value which user already set.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_get_tag_software_p2(void)
{
	int ret = CAMERA_ERROR_NONE;
	char *set_software = "soft";
	char *get_software = NULL;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_tag_software(camera, set_software);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tag_software(camera, &get_software);
	if (get_software == NULL || strcmp(set_software, get_software)) {
		fprintf(stderr, "tag software are not same.\n");

		if (get_software) {
			free(get_software);
			get_software = NULL;
		}

		return 1;
	}

	if (get_software) {
		free(get_software);
		get_software = NULL;
	}

	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


/**
 * @testcase            utc_media_camera_attr_get_geotag_n1
 * @since_tizen         2.3
 * @description         To check image geo tagging with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_geotag_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	double latitude = 0.0;
	double longitude = 0.0;
	double altitude = 0.0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_geotag(NULL, &latitude, &longitude, &altitude);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_geotag_n2
 * @since_tizen         2.3
 * @description         To check the geo-tags which are valid pointers.
 * @scenario            This test is for checking valid pointer in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second, third and fourth paramter is null pointer.
 */
int utc_media_camera_attr_get_geotag_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_geotag(camera, NULL, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_geotag_p
 * @since_tizen         2.3
 * @description         To check the geo-tags which are valid pointers.
 * @scenario            This test is for checking valid pointer in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_get_geotag_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	double latitude = 0.0;
	double longitude = 0.0;
	double altitude = 0.0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_geotag(camera, &latitude, &longitude, &altitude);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_remove_geotag_n
 * @since_tizen         2.3
 * @description         To check removing image geo tagging with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_remove_geotag_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_remove_geotag(NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_remove_geotag_p
 * @since_tizen         2.3
 * @description         To check valid pointer in camera handle.
 * @scenario            This test is for checking valid camera handle. \n
                        1. Check camera device which is supported or not. \n
                        2. Set camera handle for removing geotag.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_remove_geotag_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_remove_geotag(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_flash_mode_n1
 * @since_tizen         2.3
 * @description         To check flash mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_flash_mode_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_flash_mode_e mode = CAMERA_ATTR_FLASH_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_flash_mode(NULL, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_flash_mode_n2
 * @since_tizen         2.3
 * @description         To check flash mode with invalid pointer in second parameter.
 * @scenario            This test is for checking invalid pointer in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because second parameter is invalid pointer.
 */

int utc_media_camera_attr_get_flash_mode_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_flash_mode(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_flash_mode_p
 * @since_tizen         2.3
 * @description         To check flash mode within valid pointers.
 * @scenario            This test is for checking valid pointers in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_get_flash_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_flash_mode_e mode = CAMERA_ATTR_FLASH_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_flash_mode(camera, &mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_af_mode_n1
 * @since_tizen         2.3
 * @description         To check supported autofocus mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_foreach_supported_af_mode_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_flash_mode_e mode = CAMERA_ATTR_FLASH_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_af_mode(NULL, _af_mode_cb, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_af_mode_n2
 * @since_tizen         2.3
 * @description         To check supported autofocus mode with invalid callback pointer.
 * @scenario            This test is for checking invalid pointer in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set callback which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because invalid pointers.
 */
int utc_media_camera_attr_foreach_supported_af_mode_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_flash_mode_e mode = CAMERA_ATTR_FLASH_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_af_mode(camera, NULL, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_af_mode_p
 * @since_tizen         2.3
 * @description         To check supported autofocus mode with valid callback pointer.
 * @scenario            This test is for checking valid pointer in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set callback which is not null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_foreach_supported_af_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_flash_mode_e mode = CAMERA_ATTR_FLASH_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_af_mode(camera, _af_mode_cb, &mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_exposure_mode_n1
 * @since_tizen         2.3
 * @description         To check supported exposure mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_foreach_supported_exposure_mode_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_exposure_mode_e mode = CAMERA_ATTR_EXPOSURE_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_exposure_mode(NULL, _exposure_mode_cb, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_exposure_mode_n2
 * @since_tizen         2.3
 * @description         To check supported exposure mode with invalid callback pointer.
 * @scenario            This test is for checking invalid callback pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid callback pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because callback is null pointer.
 */
int utc_media_camera_attr_foreach_supported_exposure_mode_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_exposure_mode_e mode = CAMERA_ATTR_EXPOSURE_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_exposure_mode(camera, NULL, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_exposure_mode_p
 * @since_tizen         2.3
 * @description         To check supported exposure mode with valid pointers.
 * @scenario            This test is for checking valid pointers. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid camera handle and callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_foreach_supported_exposure_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_exposure_mode_e mode = CAMERA_ATTR_EXPOSURE_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_exposure_mode(camera, _exposure_mode_cb, &mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_iso_n1
 * @since_tizen         2.3
 * @description         To check supported ISO mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_foreach_supported_iso_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_iso_e iso = CAMERA_ATTR_ISO_AUTO;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_iso(NULL, _iso_cb, &iso);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_iso_n2
 * @since_tizen         2.3
 * @description         To check supported ISO value with invalid callback pointer.
 * @scenario            This test is for checking invalid callback pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid callback pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because callback is null pointer.
 */
int utc_media_camera_attr_foreach_supported_iso_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_iso_e iso = CAMERA_ATTR_ISO_AUTO;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_iso(camera, NULL, &iso);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_iso_p
 * @since_tizen         2.3
 * @description         To check supported ISO value with valid callback pointer.
 * @scenario            This test is for checking valid pointer in first and second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid callback and handle.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_foreach_supported_iso_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_iso_e iso = CAMERA_ATTR_ISO_AUTO;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_iso(camera, _iso_cb, &iso);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_whitebalance_n1
 * @since_tizen         2.3
 * @description         To check supported whitebalance mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_foreach_supported_whitebalance_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_whitebalance_e wb = CAMERA_ATTR_WHITE_BALANCE_AUTOMATIC;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_whitebalance(NULL, _whitebalance_cb, &wb);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_whitebalance_n2
 * @since_tizen         2.3
 * @description         To check supported whitebalance mode with invalid callback pointer.
 * @scenario            This test is for checking invalid callback pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid callback pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because callback is null pointer.
 */
int utc_media_camera_attr_foreach_supported_whitebalance_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_whitebalance_e wb = CAMERA_ATTR_WHITE_BALANCE_AUTOMATIC;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_whitebalance(camera, NULL, &wb);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_whitebalance_p
 * @since_tizen         2.3
 * @description         To check supported whitebalance mode with valid handle and callback pointer.
 * @scenario            This test is for checking valid pointer in first and second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointer in first and second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_foreach_supported_whitebalance_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_whitebalance_e wb = CAMERA_ATTR_WHITE_BALANCE_AUTOMATIC;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_whitebalance(camera, _whitebalance_cb, &wb);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_effect_n1
 * @since_tizen         2.3
 * @description         To check supported effect mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_foreach_supported_effect_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_effect_mode_e effect = CAMERA_ATTR_EFFECT_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_effect(NULL, _effect_cb, &effect);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_effect_n2
 * @since_tizen         2.3
 * @description         To check supported effect mode with invalid callback pointer.
 * @scenario            This test is for checking invalid callback pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid callback pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because callback is null pointer.
 */
int utc_media_camera_attr_foreach_supported_effect_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_effect_mode_e effect = CAMERA_ATTR_EFFECT_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_effect(camera, NULL, &effect);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_effect_p
 * @since_tizen         2.3
 * @description         To check supported effect mode with valid handle and callback pointer.
 * @scenario            This test is for checking valid pointer in first and second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointer and callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_foreach_supported_effect_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_effect_mode_e effect = CAMERA_ATTR_EFFECT_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_effect(camera, _effect_cb, &effect);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_scene_mode_n1
 * @since_tizen         2.3
 * @description         To check supported scene mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_foreach_supported_scene_mode_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_scene_mode_e mode = CAMERA_ATTR_SCENE_MODE_NORMAL;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_scene_mode(NULL, _scene_mode_cb, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_scene_mode_n2
 * @since_tizen         2.3
 * @description         To check supported scene mode with invalid callback pointer.
 * @scenario            This test is for checking invalid callback pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid callback pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because callback is null pointer.
 */
int utc_media_camera_attr_foreach_supported_scene_mode_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_scene_mode_e mode = CAMERA_ATTR_SCENE_MODE_NORMAL;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_scene_mode(camera, NULL, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_scene_mode_p
 * @since_tizen         2.3
 * @description         To check supported scene mode within valid callback pointer.
 * @scenario            This test is for checking valid pointers. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid callback pointers.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_foreach_supported_scene_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_scene_mode_e mode = CAMERA_ATTR_SCENE_MODE_NORMAL;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_scene_mode(camera, _scene_mode_cb, &mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_flash_mode_n1
 * @since_tizen         2.3
 * @description         To check supported flash mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_foreach_supported_flash_mode_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_flash_mode_e mode = CAMERA_ATTR_FLASH_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_flash_mode(NULL, _flash_mode_cb, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_flash_mode_n2
 * @since_tizen         2.3
 * @description         To check supported flash mode with invalid callback pointer.
 * @scenario            This test is for checking invalid callback pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid callback pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because callback is null pointer.
 */
int utc_media_camera_attr_foreach_supported_flash_mode_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_flash_mode_e mode = CAMERA_ATTR_FLASH_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_flash_mode(camera, NULL, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_flash_mode_p
 * @since_tizen         2.3
 * @description         To check flash mode with valid pointers.
 * @scenario            This test is for checking valid pointers. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid valid pointers which are camera handle and callback function.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_foreach_supported_flash_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_flash_mode_e mode = CAMERA_ATTR_FLASH_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_flash_mode(camera, _flash_mode_cb, &mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_fps_n1
 * @since_tizen         2.3
 * @description         To check supported frame-per-second value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_foreach_supported_fps_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_fps_e fps = CAMERA_ATTR_FPS_AUTO;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_fps(NULL, _fps_cb, &fps);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_fps_n2
 * @since_tizen         2.3
 * @description         To check supported frame-per-second with invalid callback pointer.
 * @scenario            This test is for checking invalid callback pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid callback pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because callback is null pointer.
 */
int utc_media_camera_attr_foreach_supported_fps_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_fps_e fps = CAMERA_ATTR_FPS_AUTO;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_fps(camera, NULL, &fps);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_fps_by_resolution_n1
 * @since_tizen         2.4
 * @description         To check supported frame-per-second by resolution value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_foreach_supported_fps_by_resolution_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int width = 0;
	int height = 0;
	camera_attr_fps_e fps = CAMERA_ATTR_FPS_AUTO;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_recommended_preview_resolution(camera, &width, &height);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_fps_by_resolution(NULL, width, height, _fps_cb, &fps);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_fps_by_resolution_n2
 * @since_tizen         2.4
 * @description         To check supported frame-per-second by resolution with invalid callback pointer.
 * @scenario            This test is for checking invalid callback pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid callback pointer and value pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because callback is null pointer.
 */
int utc_media_camera_attr_foreach_supported_fps_by_resolution_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	int width = 0;
	int height = 0;
	camera_attr_fps_e fps = CAMERA_ATTR_FPS_AUTO;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_recommended_preview_resolution(camera, &width, &height);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_fps_by_resolution(camera, width, height, NULL, &fps);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_fps_p
 * @since_tizen         2.3
 * @description         To check supported frame-per-second with valid pointers.
 * @scenario            This test is for checking valid pointers. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers for getting supported frame-per-second value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_foreach_supported_fps_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_fps_e fps = CAMERA_ATTR_FPS_AUTO;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_fps(camera, _fps_cb, &fps);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_fps_by_resolution_p
 * @since_tizen         2.4
 * @description         To check supported frame-per-second by resolution with valid pointers.
 * @scenario            This test is for checking valid range in parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Get recommended preview resolution. \n
                        3. Set valid pointers.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_foreach_supported_fps_by_resolution_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int width = 0;
	int height = 0;
	camera_attr_fps_e fps = CAMERA_ATTR_FPS_AUTO;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_recommended_preview_resolution(camera, &width, &height);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_fps_by_resolution(camera, width, height, _fps_cb, &fps);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_lens_orientation_n1
 * @since_tizen         2.3
 * @description         To check lens orientation value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_lens_orientation_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int angle = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_lens_orientation(NULL, &angle);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_lens_orientation_n2
 * @since_tizen         2.3
 * @description         To check lens orientation in H/W with invalid pointer in second parameter.
 * @scenario            This test is for checking invalid pointer in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because second parameter is invalid pointer.
 */
int utc_media_camera_attr_get_lens_orientation_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_lens_orientation(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_lens_orientation_p
 * @since_tizen         2.3
 * @description         To check lens orientation in H/W with valid pointer.
 * @scenario            This test is for checking valid range in parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_get_lens_orientation_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int rotate = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_lens_orientation(camera, &rotate);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_af_area_n1
 * @since_tizen         2.3
 * @description         To check auto-focus area with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_af_area_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_af_area(NULL, 0, 0);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_af_area_n2
 * @since_tizen         2.3
 * @description         To check autofocus area with invalid values, negative values.
 * @scenario            This test is for checking invalid values in second, third parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid values such as negative values.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because of negative values.
 */
int utc_media_camera_attr_set_af_area_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_af_area(camera, -1, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_af_area_p
 * @since_tizen         2.3
 * @description         To check autofocus area with valid values.
 * @scenario            This test is for checking valid values in second,third parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Get supported autofocus mode. \n
                        3. Set supported autofocus mode. \n
                        4. Set valid values with not negative values.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_set_af_area_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int mode = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_af_mode(camera, _af_mode_cb, &mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (mode < 0) {
		fprintf(stderr, "there is no supported AF mode.\n");
		return 0;
	}

	ret = camera_attr_set_af_mode(camera, mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (mode != CAMERA_ATTR_AF_NONE) {
		ret = camera_attr_set_af_area(camera, 0, 0);
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_clear_af_area_n
 * @since_tizen         2.3
 * @description         To check to clear auto-focus area with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_clear_af_area_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_clear_af_area(NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_clear_af_area_p
 * @since_tizen         2.3
 * @description         To check to clear auto-focus area with valid camera handle.
 * @scenario            This test is for checking valid pointer with camera handle. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid camera handle.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_clear_af_area_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_clear_af_area(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_disable_shutter_sound_n
 * @since_tizen         2.3
 * @description         To check to disable shutter sound with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_disable_shutter_sound_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_disable_shutter_sound(NULL, false);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_disable_shutter_sound_p
 * @since_tizen         2.3
 * @description         To check to disable shutter sound with valid value.
 * @scenario            This test is for checking valid pointer and value. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid true or false value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_disable_shutter_sound_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_disable_shutter_sound(camera, false);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_supported_anti_shake_n
 * @since_tizen         2.3
 * @description         To check that anti-shake mode is supported or not with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_is_supported_anti_shake_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_supported_anti_shake(NULL);

	fprintf(stderr, "camera_attr_is_supported_anti_shake(NULL) ret %d", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_supported_anti_shake_p
 * @since_tizen         2.3
 * @description         To check anti-shake supported or not with valid camera handle.
 * @scenario            This test is for checking valid camera handle. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid camera handle.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_is_supported_anti_shake_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_supported_anti_shake(camera);

	fprintf(stderr, "camera_attr_is_supported_anti_shake(camera) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_enable_anti_shake_n
 * @since_tizen         2.3
 * @description         To check to enable anti-shake with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Check anti-shake which is supported or not. \n
                        3-1. If anti-shake is not supported, check api returns correct result. \n
                        3-2. If anti-shake is supported, Set invalid pointer which is camera handle null. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_enable_anti_shake_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_enable_anti_shake(NULL, true);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_enable_anti_shake_p
 * @since_tizen         2.3
 * @description         To check to enable anti-shake with valid camera handle.
 * @scenario            This test is for checking valid range in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Check anti-shake which is supported or not. \n
                        3-1. If anti-shake is not supported, check api returns correct result. \n
                        3-2. If anti-shake is supported, Set valid camera handle. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_enable_anti_shake_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_attr_is_supported_anti_shake(camera);

	ret = camera_attr_enable_anti_shake(camera, true);

	if (!supported) {
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else{
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_enabled_anti_shake_n1
 * @since_tizen         2.3
 * @description         To check anti-shake enabled with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. If anti-shake is supported, set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_is_enabled_anti_shake_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool enabled = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_enabled_anti_shake(NULL, &enabled);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_enabled_anti_shake_n2
 * @since_tizen         2.3
 * @description         To check anti-shake enabled or not with valid camera handle.
 * @scenario            This test is for checking valid range in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. If anti-shake is supported, set invalid pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because value should not be null.
 */
int utc_media_camera_attr_is_enabled_anti_shake_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_enabled_anti_shake(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_enabled_anti_shake_p
 * @since_tizen         2.3
 * @description         To check anti-shake enabled or not
 * @scenario            This test is for checking valid range in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Check anti-shake supported or not. \n
                        3-1. If anti-shake is not supported, check that api returns correct error. \n
                        3-2. If anti-shake is supported, set valid pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_is_enabled_anti_shake_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;
	bool enable = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_attr_is_supported_anti_shake(camera);

	ret = camera_attr_is_enabled_anti_shake(camera, &enable);

	if (!supported) {
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else{
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_supported_auto_contrast_n
 * @since_tizen         2.3
 * @description         To check auto-contrast supported value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_is_supported_auto_contrast_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_supported_auto_contrast(NULL);

	fprintf(stderr, "camera_attr_is_supported_auto_contrast(NULL) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_supported_auto_contrast_p
 * @since_tizen         2.3
 * @description         To check auto contrast supported or not within valid camera handle.
 * @scenario            This test is for checking valid camera handle. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid camera handle.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_is_supported_auto_contrast_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_supported_auto_contrast(camera);

	fprintf(stderr, "camera_attr_is_supported_auto_contrast(camera) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_enable_auto_contrast_n
 * @since_tizen         2.3
 * @description         To check to enable auto-contrast value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Check auto contrast which is supported or not. \n
                        3-1. If auto contrast is supported ,set invalid pointer which is camera handle null. \n
                        3-2. If auto contrast is not supported, set valid value for checking this api that returns not-supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_enable_auto_contrast_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_enable_auto_contrast(NULL, true);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_enable_auto_contrast_p
 * @since_tizen         2.3
 * @description         To check to enable auto-contrast value with valid value.
 * @scenario            This test is for checking valid value in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Check auto contrast which is supported or not. \n
                        3-1. If auto contrast is supported ,set invalid value. \n
                        3-2. If auto contrast is not supported, set valid value for checking this api that returns not-supported
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_enable_auto_contrast_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_attr_is_supported_auto_contrast(camera);

	ret = camera_attr_enable_auto_contrast(camera, true);

	if (supported) {
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_enabled_auto_contrast_n1
 * @since_tizen         2.3
 * @description         To check auto contrast value enabled or not with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Check auto contrast which is supported or not. \n
                        3. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_is_enabled_auto_contrast_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool enabled = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_enabled_auto_contrast(NULL, &enabled);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_enabled_auto_contrast_n2
 * @since_tizen         2.3
 * @description         To check auto contrast value enabled or not with invalid value.
 * @scenario            This test is for checking invalid pointer such a null. \n
                        1. Check camera device which is supported or not. \n
                        2. Check auto contrast which is supported or not. \n
                        3-1. If auto contrast is supported, set invalid null pointer in second parameter. \n
                        3-2. If auto contrast is not supported, set invalid pointer which is getting second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_is_enabled_auto_contrast_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_enabled_auto_contrast(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_enabled_auto_contrast_p
 * @since_tizen         2.3
 * @description         To check auto contrast value enabled or not within valid pointer.
 * @scenario            This test is for checking valid pointer in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Enable auto contrast. \n
                        3. Set and check valid pointer to get value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_is_enabled_auto_contrast_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;
	bool enable = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_attr_is_supported_auto_contrast(camera);

	ret = camera_attr_is_enabled_auto_contrast(camera, &enable);

	if (supported) {
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_enable_video_stabilization_n
 * @since_tizen         2.3
 * @description         To check video stabiliztion value enabled with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid camera handle.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.

 */
int utc_media_camera_attr_enable_video_stabilization_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_enable_video_stabilization(NULL, false);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_enable_video_stabilization_p
 * @since_tizen         2.3
 * @description         To check ability for  video stabilization.
 * @scenario            This test is for checking valid value in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid value true or false.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_enable_video_stabilization_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_supported_video_stabilization(camera);
	if (ret == false) {
		fprintf(stderr, "video stabilization is not supported.\n");

		ret = camera_attr_enable_video_stabilization(camera, true);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);

		return 0;
	}

	ret = camera_attr_enable_video_stabilization(camera, true);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_enabled_video_stabilization_n1
 * @since_tizen         2.3
 * @description         To check to be video stabilization enabled with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Check video stabilization supported. \n
                        3-1. If video stabilization is supported, set invalid pointer in second parameter. \n
                        3-2. If video stabilization is not supported, set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_is_enabled_video_stabilization_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool enabled = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_enabled_video_stabilization(NULL, &enabled);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_enabled_video_stabilization_n2
 * @since_tizen         2.3
 * @description         To check to be video stabilization enabled with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Check video stabilization supported. \n
                        3-1. If video stabilization is supported, set invalid pointer in second parameter. \n
                        3-2. If video stabilization is not supported, set invalid pointer in second parameter. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_is_enabled_video_stabilization_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_enabled_video_stabilization(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_enabled_video_stabilization_p
 * @since_tizen         2.3
 * @description         To check video stabilization enabled with valid pointer.
 * @scenario            This test is for checking valid range in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid value which enable or not.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_is_enabled_video_stabilization_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool enabled = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_supported_video_stabilization(camera);
	if (ret == false) {
		fprintf(stderr, "video stabilization is not supported");
		ret = camera_attr_is_enabled_video_stabilization(camera, &enabled);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = camera_attr_is_enabled_video_stabilization(camera, &enabled);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_supported_video_stabilization_n
 * @since_tizen         2.3
 * @description         To check video stabilization value supported with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.

 */
int utc_media_camera_attr_is_supported_video_stabilization_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_supported_video_stabilization(NULL);

	fprintf(stderr, "camera_attr_is_supported_video_stabilization(NULL) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_supported_video_stabilization_p
 * @since_tizen         2.3
 * @description         To check video stabilization supported with valid camera handle.
 * @scenario            This test is for checking valid camera handle. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid camera handle.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_is_supported_video_stabilization_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_supported_video_stabilization(camera);

	fprintf(stderr, "camera_attr_is_supported_video_stabilization(camera) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_hdr_mode_n1
 * @since_tizen         2.3
 * @description         To check HDR mode value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_hdr_mode_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_hdr_mode_e hdr = CAMERA_ATTR_HDR_MODE_DISABLE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_hdr_mode(NULL, &hdr);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_hdr_mode_n2
 * @since_tizen         2.3
 * @description         This test is for checking invalid null pointer. \n
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid null pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_hdr_mode_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_hdr_mode(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_hdr_mode_p
 * @since_tizen         2.3
 * @description         To check HDR mode value with valid pointer.
 * @scenario            This test is for checking valid pointer in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Check HDR capture which is supported or not. \n
                        3-1. If HDR capture is not supported, check valid pointer. \n
                        3-2. If HDR capture is supported, set valid pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_hdr_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_hdr_mode_e hdr = CAMERA_ATTR_HDR_MODE_DISABLE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_supported_hdr_capture(camera);
	if (ret == false) {
		fprintf(stderr, "hdr capture is not supported.\n");

		ret = camera_attr_get_hdr_mode(camera, &hdr);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);

		return 0;
	}

	ret = camera_attr_get_hdr_mode(camera, &hdr);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_hdr_mode_n1
 * @since_tizen         2.3
 * @description         To check HDR mode value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.

 */
int utc_media_camera_attr_set_hdr_mode_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_hdr_mode(camera, -1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_hdr_mode_n2
 * @since_tizen         2.3
 * @description         To check HDR mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.

 */
int utc_media_camera_attr_set_hdr_mode_n2(void)
{
	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	int ret = CAMERA_ERROR_NONE;

	ret = camera_attr_set_hdr_mode(NULL, CAMERA_ATTR_HDR_MODE_ENABLE);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_attr_set_hdr_mode_p
 * @since_tizen         2.3
 * @description         To check HDR capture mode within valid range.
 * @scenario            This test is for checking valid range in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Check HDR capture which is supported or not. \n
                        3-1. If HDR capture is not supported, check api returns not-supported correctly. \n
                        3-2. If HDR capture is supported, set valid pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_hdr_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_supported_hdr_capture(camera);
	if (ret == false) {
		fprintf(stderr, "hdr capture is not supported.\n");

		ret = camera_attr_set_hdr_mode(camera, CAMERA_ATTR_HDR_MODE_ENABLE);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);

		return 0;
	}

	ret = camera_attr_set_hdr_mode(camera, CAMERA_ATTR_HDR_MODE_ENABLE);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_stream_flip_n
 * @since_tizen         2.3
 * @description         To check stream flip mode supported with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_foreach_supported_stream_flip_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_stream_flip(NULL, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return false;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_stream_flip_p
 * @since_tizen         2.3
 * @description         To check stream flip mode supported with valid parameters.
 * @scenario            This test is for checking valid pointers. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_foreach_supported_stream_flip_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_stream_flip(camera, _stream_flip_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_stream_flip_n
 * @since_tizen         2.3
 * @description         To check stream flip mode value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_stream_flip_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_flip_e flip = CAMERA_FLIP_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_stream_flip(NULL, &flip);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_stream_flip_p
 * @since_tizen         2.3
 * @description         To check stream flip mode with valid pointer.
 * @scenario            This test is for checking valid pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Check stream flip mode which is supported or not. \n
                        3-1. If stream flip mode is supported, set valid pointer in second paramter. \n
                        3-2. If stream flip mode is not supported, check api which returns not-supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_stream_flip_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int flip = -1;
	camera_flip_e gflip = CAMERA_FLIP_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_stream_flip(camera, _stream_flip_cb, &flip);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (flip > -1) {
		ret = camera_attr_get_stream_flip(camera, &gflip);
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		fprintf(stderr, "There is no supported stream flip.\n");

		ret = camera_attr_get_stream_flip(camera, &gflip);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_stream_flip_n1
 * @since_tizen         2.3
 * @description         To check stream flip mode value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Check stream flip mode which is supported or not. \n
                        3-1. If stream flip mode is supported, set invalid pointer which is camera handle null. \n
                        3-2. If stream flip mode is not supported, check api which returns not-supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_stream_flip_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int flip = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_stream_flip(camera, _stream_flip_cb, &flip);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (flip > -1) {
		ret = camera_attr_set_stream_flip(NULL, flip);
		assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);
	} else {
		fprintf(stderr, "There is no supported stream flip.\n");

		ret = camera_attr_set_stream_flip(camera, CAMERA_FLIP_HORIZONTAL);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_stream_flip_n2
 * @since_tizen         2.3
 * @description         To check stream flip mode value with invalid range value.
 * @scenario            This test is for checking value which is out of range. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the value is out of range.
 */
int utc_media_camera_attr_set_stream_flip_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_stream_flip(camera, CAMERA_FLIP_BOTH + 1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_stream_flip_p
 * @since_tizen         2.3
 * @description         To check stream filp value within valid range.
 * @scenario            This test is for checking valid value. \n
                        1. Check camera device which is supported or not. \n
                        2. Check stream flip mode which is supported or not. \n
                        3-1. If stream flip mode is supported, set valid range value. \n
                        3-2. If stream flip mode is not supported, check api which returns not-supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_stream_flip_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int flip = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_stream_flip(camera, _stream_flip_cb, &flip);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (flip > -1) {
		ret = camera_attr_set_stream_flip(camera, flip);
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		fprintf(stderr, "There is no supported stream flip.\n");

		ret = camera_attr_set_stream_flip(camera, CAMERA_FLIP_HORIZONTAL);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_stream_rotation_n
 * @since_tizen         2.3
 * @description         To check stream rotation value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_foreach_supported_stream_rotation_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_stream_rotation(NULL, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_stream_rotation_p
 * @since_tizen         2.3
 * @description         To check stream rotation value supported with value parameters.
 * @scenario            This test is for checking valid parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_foreach_supported_stream_rotation_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_stream_rotation(camera, _stream_rotation_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_stream_rotation_n
 * @since_tizen         2.3
 * @description         To check stream rotation mode value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Check stream rotation mode which is supported or not. \n
                        3-1. If stream rotation mode is supported, set invalid pointer which is camera handle null. \n
                        3-2. If stream rotation mode is not supported, check api which returns not-supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_stream_rotation_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int rotation = -1;
	camera_rotation_e grotation = CAMERA_ROTATION_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_stream_rotation(camera, _stream_rotation_cb, &rotation);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (rotation > -1) {
		ret = camera_attr_get_stream_rotation(NULL, &grotation);
		assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);
	} else {
		fprintf(stderr, "There is no supported stream rotation.\n");

		ret = camera_attr_get_stream_rotation(camera, &grotation);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_stream_rotation_p
 * @since_tizen         2.3
 * @description         To check and get stream rotation value correctly with valid pointers.
 * @scenario            This test is for checking valid pointers. \n
                        1. Check camera device which is supported or not. \n
                        2. Check stream rotation mode which is supported or not. \n
                        3-1. If stream rotation mode is supported, set valid pointers. \n
                        3-2. If stream rotation mode is not supported, check api which returns not-supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_stream_rotation_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int rotation = -1;
	camera_rotation_e grotation = CAMERA_ROTATION_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_stream_rotation(camera, _stream_rotation_cb, &rotation);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (rotation > -1) {
		ret = camera_attr_get_stream_rotation(camera, &grotation);
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		fprintf(stderr, "There is no supported stream rotation.\n");

		ret = camera_attr_get_stream_rotation(camera, &grotation);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_media_camera_attr_set_stream_rotation_n1
 * @since_tizen         2.3
 * @description         To check stream rotation mode value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Check stream rotation mode which is supported or not. \n
                        3-1. If stream rotation mode is supported, set invalid pointer which is camera handle null. \n
                        3-2. If stream rotation mode is not supported, check api which returns not-supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_stream_rotation_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int rotation = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_stream_rotation(camera, _stream_rotation_cb, &rotation);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (rotation > -1) {
		ret = camera_attr_set_stream_rotation(NULL, rotation);
		assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);
	} else {
		fprintf(stderr, "There is no supported stream rotation.\n");

		ret = camera_attr_set_stream_rotation(camera, CAMERA_ROTATION_270);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_stream_rotation_n2
 * @since_tizen         2.3
 * @description         To check stream rotation mode value which is out of range.
 * @scenario            This test is for checking invald value. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the value is out of range.
 */
int utc_media_camera_attr_set_stream_rotation_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_stream_rotation(camera, CAMERA_ROTATION_270 + 1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_attr_set_stream_rotation_p
 * @since_tizen         2.3
 * @description         To check stream rotation value within valid range.
 * @scenario            This test is for checking valid range in all parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Check stream rotation mode which is supported or not. \n
                        3-1. If stream rotation mode is supported, set valid value. \n
                        3-2. If stream rotation mode is not supported, check api which returns not-supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_stream_rotation_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int rotation = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_stream_rotation(camera, _stream_rotation_cb, &rotation);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (rotation > -1) {
		ret = camera_attr_set_stream_rotation(camera, rotation);
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		fprintf(stderr, "There is no supported stream rotation.\n");

		ret = camera_attr_set_stream_rotation(camera, rotation);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_theater_mode_n
 * @since_tizen         2.3
 * @description         To check theater mode value supported with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_foreach_supported_theater_mode_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_theater_mode(NULL, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return false;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_theater_mode_p
 * @since_tizen         2.3
 * @description         To check supported theater mode within valid parameters.
 * @scenario            This test is for checking valid parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_foreach_supported_theater_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_theater_mode(camera, _theater_mode_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_theater_mode_n
 * @since_tizen         2.3
 * @description         To check theater mode value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_theater_mode_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_theater_mode_e mode = CAMERA_ATTR_THEATER_MODE_DISABLE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_theater_mode(NULL, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_theater_mode_p
 * @since_tizen         2.3
 * @description         To check theater mode value with valid parameters.
 * @scenario            This test is for checking valid parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Check theater mode which is supported or not. \n
                        3-1. If theater mode is supported, set valid pointer. \n
                        3-2. If theater mode is not supported, check api which returns not-supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_theater_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int mode = -1;
	camera_attr_theater_mode_e gmode = CAMERA_ATTR_THEATER_MODE_DISABLE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_theater_mode(camera, _theater_mode_cb, &mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (mode > -1) {
		ret = camera_attr_get_theater_mode(camera, &gmode);
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		fprintf(stderr, "There is no supported theater mode.\n");

		ret = camera_attr_get_theater_mode(camera, &gmode);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_theater_mode_n
 * @since_tizen         2.3
 * @description         To check theater mode value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_theater_mode_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_theater_mode(NULL, CAMERA_ATTR_THEATER_MODE_ENABLE);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_theater_mode_p
 * @since_tizen         2.3
 * @description         To check theater mode value within valid range.
 * @scenario            This test is for checking valid range in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Check theater mode which is supported or not. \n
                        3-1. If theater mode is supported, set valid value. \n
                        3-2. If theater mode is not supported, check api which returns not-supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_theater_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int mode = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_theater_mode(camera, _theater_mode_cb, &mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (mode > -1) {
		ret = camera_attr_set_theater_mode(camera, mode);
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		fprintf(stderr, "There is no supported theater mode.\n");

		ret = camera_attr_set_theater_mode(camera, -1);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_get_display_flip_n
 * @since_tizen         2.3
 * @description         To check display flip value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_get_display_flip_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_flip_e mode = CAMERA_FLIP_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_display_flip(NULL, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_display_flip_p
 * @since_tizen         2.3
 * @description         To get display flip value within valid range.
 * @scenario            This test is for checking valid range in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_get_display_flip_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_flip_e mode = CAMERA_FLIP_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_display_flip(camera, &mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_display_flip_n
 * @since_tizen         2.3
 * @description         To check display flip value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_set_display_flip_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_flip(NULL, CAMERA_FLIP_HORIZONTAL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_set_display_flip_p
 * @since_tizen         2.3
 * @description         To check display flip value within valid range.
 * @scenario            This test is for checking valid parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set the valid parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_set_display_flip_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_flip(camera, CAMERA_FLIP_HORIZONTAL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_supported_hdr_capture_n
 * @since_tizen         2.3
 * @description         To check hdr capture supported with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_is_supported_hdr_capture_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_supported_hdr_capture(NULL);

	fprintf(stderr, "camera_attr_is_supported_hdr_capture(NULL) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_is_supported_hdr_capture_p
 * @since_tizen         2.3
 * @description         To check hdr capture supported with valid camera handle.
 * @scenario            This test is for checking valid camera handle. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid camera handle.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_is_supported_hdr_capture_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_is_supported_hdr_capture(camera);

	fprintf(stderr, "camera_attr_is_supported_hdr_capture(camera) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_is_supported_face_detection_n
 * @since_tizen         2.3
 * @description         To check face detection supported with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_is_supported_face_detection_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_is_supported_face_detection(NULL);

	fprintf(stderr, "camera_is_supported_face_detection(NULL) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_is_supported_face_detection_p
 * @since_tizen         2.3
 * @description         To check face detection supported with valid camera handle.
 * @scenario            This test is for checking valid camera handle. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid camera handle.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_is_supported_face_detection_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_is_supported_face_detection(camera);

	fprintf(stderr, "camera_is_supported_face_detection(camera) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_is_supported_zero_shutter_lag_n
 * @since_tizen         2.3
 * @description         To check zero shutter lag supported with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_is_supported_zero_shutter_lag_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_is_supported_zero_shutter_lag(NULL);

	fprintf(stderr, "camera_is_supported_zero_shutter_lag(NULL) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_is_supported_zero_shutter_lag_p
 * @since_tizen         2.3
 * @description         To check zero shutter lag supported with valid camera handle.
 * @scenario            This test is for checking valid camera handle. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid camera handle.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_is_supported_zero_shutter_lag_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_is_supported_zero_shutter_lag(camera);

	fprintf(stderr, "camera_is_supported_zero_shutter_lag(camera) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_is_supported_media_packet_preview_cb_n
 * @since_tizen         2.3
 * @description         To check media packet preview callback supported with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_is_supported_media_packet_preview_cb_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_is_supported_media_packet_preview_cb(NULL);

	fprintf(stderr, "camera_is_supported_media_packet_preview_cb(NULL) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_is_supported_media_packet_preview_cb_p
 * @since_tizen         2.3
 * @description         To check media packet preview callback supported with camera handle.
 * @scenario            This test is for checking valid camera handle. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid camera handle.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_is_supported_media_packet_preview_cb_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_is_supported_media_packet_preview_cb(camera);

	fprintf(stderr, "camera_is_supported_media_packet_preview_cb(camera) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_device_count_n
 * @since_tizen         2.3
 * @description         To check to get device count with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_get_device_count_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int count = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_device_count(NULL, &count);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_device_count_p
 * @since_tizen         2.3
 * @description         To check to get device count with valid parameters.
 * @scenario            This test is for checking valid parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointer in all parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_get_device_count_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int count = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_device_count(camera, &count);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_recommended_preview_resolution_n
 * @since_tizen         2.3
 * @description         To check recommanded preview resolution with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_get_recommended_preview_resolution_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int width = 0;
	int height = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_recommended_preview_resolution(NULL, &width, &height);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_recommended_preview_resolution_p
 * @since_tizen         2.3
 * @description         To check recommended preview resolution which is valid pointer in all parameters.
 * @scenario            This test is for checking valid parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointer in all parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_get_recommended_preview_resolution_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int width = 0;
	int height = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_recommended_preview_resolution(camera, &width, &height);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_enable_tag_n
 * @since_tizen         2.3
 * @description         To check to enable tag with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_enable_tag_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_enable_tag(NULL, true);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_enable_tag_p
 * @since_tizen         2.3
 * @description         To check tag enable which is valid pointer in all parameter.
 * @scenario            This test is for checking valid range in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_enable_tag_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_enable_tag(camera, true);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_af_mode_n
 * @since_tizen         2.3
 * @description         To check to get auto-focus mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_af_mode_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_af_mode_e get_mode = CAMERA_ATTR_AF_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_af_mode(NULL, &get_mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_af_mode_p1
 * @since_tizen         2.3
 * @description         To check to get auto-focus mode with valid pointers.
 * @scenario            This test is for checking valid range in all. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers which are not null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_af_mode_p1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_af_mode_e get_mode = CAMERA_ATTR_AF_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_af_mode(camera, &get_mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_af_mode_p2
 * @since_tizen         2.3
 * @description         To check auto-focus mode which are correctly working with valid parameters.
 * @scenario            This test is for checking valid pointers. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid range pointers including camera handle and callback.
                        3. Callback function will check auto-focus mode that works fine in all modes.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_af_mode_p2(void)
{
	int ret = CAMERA_ERROR_NONE;
	int cb_err = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_af_mode(camera, _af_mode_check_cb, &cb_err);
	assert_eq(ret, CAMERA_ERROR_NONE);
	assert_eq(cb_err, 0);

	return 0;
}


/**
 * @testcase            utc_media_camera_attr_get_brightness_n
 * @since_tizen         2.3
 * @description         To check brightness level with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_brightness_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int level = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_brightness(NULL, &level);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_brightness_p
 * @since_tizen         2.3
 * @description         To check brighness value with valid pointers.
 * @scenario            This test is for checking valid pointers in all parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_brightness_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int level = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_brightness(camera, &level);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_brightness_range_n
 * @since_tizen         2.3
 * @description         To check brightness range with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_brightness_range_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_brightness_range(NULL, &min, &max);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_brightness_range_p
 * @since_tizen         2.3
 * @description         To check valid brightness range without any invalid parameters.
 * @scenario            This test is for checking valid pointers in all parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_brightness_range_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_brightness_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_contrast_n
 * @since_tizen         2.3
 * @description         To check contrast value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_contrast_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int value = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_contrast(NULL, &value);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_contrast_p
 * @since_tizen         2.3
 * @description         To check contrast value with valid pointers.
 * @scenario            This test is for checking valid pointers in all parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers to get correct contrast value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_contrast_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int value = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_contrast(camera, &value);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_contrast_range_n
 * @since_tizen         2.3
 * @description         To check contrast range with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_contrast_range_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_contrast_range(NULL, &min , &max);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_contrast_range_p
 * @since_tizen         2.3
 * @description         To check contrast range with valid pointers.
 * @scenario            This test is for checking valid pointers in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_contrast_range_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_contrast_range(camera, &min , &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_exposure_n
 * @since_tizen         2.3
 * @description         To check exposure value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_exposure_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int value = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_exposure(NULL, &value);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_exposure_p
 * @since_tizen         2.3
 * @description         To check exposure value with valid pointers.
 * @scenario            This test is for checking valid pointers in all parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers to get exposure value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_exposure_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int value = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_exposure(camera, &value);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_exposure_mode_n
 * @since_tizen         2.3
 * @description         To check exposure mode value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_exposure_mode_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_exposure_mode_e mode = CAMERA_ATTR_EXPOSURE_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_exposure_mode(NULL, &mode);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_exposure_mode_p
 * @since_tizen         2.3
 * @description         To check exposure mode value with valid pointers.
 * @scenario            This test is for checking valid pointers in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Check exposure mode which is supported or not. \n
                        3-1. If exposure mode is not supported, check api which returns not-supported. \n
                        3-2. If exposure mode is supported, set valid pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_exposure_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int exposure_mode = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_exposure_mode(camera, _exposure_mode_cb, &exposure_mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (exposure_mode < 0) {
		ret = camera_attr_get_exposure_mode(camera, (camera_attr_exposure_mode_e *)&exposure_mode);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}else {
		ret = camera_attr_get_exposure_mode(camera, (camera_attr_exposure_mode_e *)&exposure_mode);
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_exposure_range_n
 * @since_tizen         2.3
 * @description         To check exposure range with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_exposure_range_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_exposure_range(NULL, &min, &max);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_exposure_range_p
 * @since_tizen         2.3
 * @description         To check exposure range with valid pointers.
 * @scenario            This test is for checking valid pointers in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_exposure_range_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_exposure_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_iso_n
 * @since_tizen         2.3
 * @description         To check ISO value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_iso_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_iso_e iso = CAMERA_ATTR_ISO_AUTO;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_iso(NULL, &iso);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_iso_p
 * @since_tizen         2.3
 * @description         To check ISO value within valid pointers.
 * @scenario            This test is for checking valid range in second parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers to get ISO values.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_iso_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_iso_e iso = CAMERA_ATTR_ISO_AUTO;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_iso(camera, &iso);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_whitebalance_n
 * @since_tizen         2.3
 * @description         To check whitebalance value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_whitebalance_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_whitebalance_e wb;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_whitebalance(NULL, &wb);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_whitebalance_p
 * @since_tizen         2.3
 * @description         To check whitebalance value with valid pointers.
 * @scenario            This test is for checking valid pointers in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Check whitebalance which is supported or not. \n
                        3-1. If whitebalance is supported, set valid pointers to get whitebalance value. \n
                        3-2. If whitebalance is not supported, check api that returns not-supported.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_whitebalance_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int set_wb = -1;
	camera_attr_whitebalance_e wb = CAMERA_ATTR_WHITE_BALANCE_AUTOMATIC;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_whitebalance(camera, _whitebalance_cb, &set_wb);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (set_wb > -1) {
		ret = camera_attr_get_whitebalance(camera, &wb);
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		fprintf(stderr, "there is no supported white balance");
		ret = camera_attr_get_whitebalance(camera, &wb);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_zoom_n
 * @since_tizen         2.3
 * @description         To check zoom level with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_zoom_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int level = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_zoom(NULL, &level);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_zoom_p
 * @since_tizen         2.3
 * @description         To check zoom value with valid pointers.
 * @scenario            This test is for checking valid pointers in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers to get zoom value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_zoom_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int level = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_zoom(camera, &level);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_zoom_range_n
 * @since_tizen         2.3
 * @description         To check zoom range with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_zoom_range_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_zoom_range(NULL, &min , &max);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_zoom_range_p
 * @since_tizen         2.3
 * @description         To check zoom range with valid pointers.
 * @scenario            This test is for checking valid pointers in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid pointers to get zoom range.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_zoom_range_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_zoom_range(camera, &min , &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_effect_n
 * @since_tizen         2.3
 * @description         To check effect mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_effect_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_effect_mode_e effect = CAMERA_ATTR_EFFECT_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_effect(NULL, effect);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_effect_p
 * @since_tizen         2.3
 * @description         To check effect mode in valid value.
 * @scenario            This test is for checking valid value and pointer in all parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid effect mode that works correctly.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_effect_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_effect_mode_e effect = CAMERA_ATTR_EFFECT_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_effect(camera, effect);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_flash_mode_n
 * @since_tizen         2.3
 * @description         To check flash mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_flash_mode_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_flash_mode_e flash = CAMERA_ATTR_FLASH_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_flash_mode(NULL,flash);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_flash_mode_p
 * @since_tizen         2.3
 * @description         To check falsh mode with valid value
 * @scenario            This test is for checking valid value and pointer in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid flash mode.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */

int utc_media_camera_attr_set_flash_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_flash_mode_e flash = CAMERA_ATTR_FLASH_MODE_OFF;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	/* TODO: need new API to tell whether flash of this camera is supported or not. */
	ret = camera_attr_set_flash_mode(camera, flash);
	if (ret != CAMERA_ERROR_NONE && ret != CAMERA_ERROR_NOT_SUPPORTED)
		assert(false);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_geotag_n
 * @since_tizen         2.3
 * @description         To check geo-tag with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_geotag_n(void)
{
	double lng = 1.12;
	double lat = 1.13;
	double alt = 1.14;
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_geotag(NULL, lat, lng, alt);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_geotag_p
 * @since_tizen         2.3
 * @description         To check geo-tag value.
 * @scenario            This test is for checking correct value. \n
                        1. Check camera device which is supported or not. \n
                        2. Set geo-tag which correct values.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_geotag_p(void)
{
	double lng = 1.12;
	double lat = 1.13;
	double alt = 1.14;
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_geotag(camera, lat, lng, alt);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_scene_mode_n
 * @since_tizen         2.3
 * @description         To check scene mode with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_scene_mode_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_scene_mode_e scene = CAMERA_ATTR_SCENE_MODE_NORMAL;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_scene_mode(NULL , scene);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_scene_mode_p
 * @since_tizen         2.3
 * @description         To check scene mode with valid value.
 * @scenario            This test is for checking valid range and pointer in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid value to set scene mode.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_scene_mode_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_scene_mode_e scene = CAMERA_ATTR_SCENE_MODE_NORMAL;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_scene_mode(camera , scene);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_tag_image_description_n
 * @since_tizen         2.3
 * @description         To check image description string with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.

 */
int utc_media_camera_attr_set_tag_image_description_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_tag_image_description(NULL, "12345678901234567890");
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_tag_image_description_p
 * @since_tizen         2.3
 * @description         To check image description string.
 * @scenario            This test is for checking valid pointers in all parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid image description string to set.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_tag_image_description_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_tag_image_description(camera, "12345678901234567890");
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_tag_orientation_n
 * @since_tizen         2.3
 * @description         To check image orientation tag with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_tag_orientation_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_tag_orientation_e orientation = CAMERA_ATTR_TAG_ORIENTATION_TOP_LEFT;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_tag_orientation(NULL, orientation);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_tag_orientation_p
 * @since_tizen         2.3
 * @description         To check orientation tag value with valid range.
 * @scenario            This test is for checking valid range and pointer in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid value in valid range.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_tag_orientation_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_tag_orientation_e orientation = CAMERA_ATTR_TAG_ORIENTATION_TOP_LEFT;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_tag_orientation(camera, orientation);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_tag_software_n
 * @since_tizen         2.3
 * @description         To check software version with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_tag_software_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	char *string = "1.0";

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_tag_software(NULL, string);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_tag_software_p
 * @since_tizen         2.3
 * @description         To check software tag string with valid pointers.
 * @scenario            This test is for checking valid string and pointers in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid string to set software tag.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_tag_software_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	char *string = "1.0";

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_tag_software(camera, string);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


static bool _preview_format_cb(camera_pixel_format_e format, void *user_data)
{
	bool *format_match = NULL;

	format_match = (bool*)user_data;

	if (format == CAMERA_PIXEL_FORMAT_H264) {
		*format_match = true;
		return false;
	}

    return true;
}

/**
 * @testcase            utc_media_camera_attr_get_encoded_preview_bitrate_p
 * @since_tizen         3.0
 * @description         To check encoded preview bitrate value with valid pointers.
 * @scenario            This test is for checking valid pointers in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Check encoded preview format is supported or not. \n
                        3. Get bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_encoded_preview_bitrate_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int bitrate = 0;
	bool is_supported_encoded_preview = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_preview_format(camera, _preview_format_cb, &is_supported_encoded_preview);

	if (is_supported_encoded_preview) {
		ret = camera_attr_get_encoded_preview_bitrate(camera, &bitrate);
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		fprintf(stderr, "encoded preview is not supported");
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_encoded_preview_bitrate_n
 * @since_tizen         3.0
 * @description         To check encoded preview bitrate value with invalid pointers.
 * @scenario            This test is for checking invalid pointers such as camera handle "null" and bitrate "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointers which is camera handle null and bitrate "null".
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_encoded_preview_bitrate_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_encoded_preview_bitrate(NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_encoded_preview_bitrate_p
 * @since_tizen         3.0
 * @description         To check encoded preview bitrate value with valid pointers.
 * @scenario            This test is for checking valid pointer and value in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Check encoded preview format is supported or not. \n
                        3. Set valid bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_encoded_preview_bitrate_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool is_supported_encoded_preview = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_preview_format(camera, _preview_format_cb, &is_supported_encoded_preview);

	if (is_supported_encoded_preview) {
		ret = camera_set_preview_format(camera, CAMERA_PIXEL_FORMAT_H264);
		assert_eq(ret, CAMERA_ERROR_NONE);

		ret = camera_attr_set_encoded_preview_bitrate(camera, BITRATE);
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		fprintf(stderr, "encoded preview format is not supported.\n");
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_encoded_preview_bitrate_n
 * @since_tizen         3.0
 * @description         To check encoded preview bitrate value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_encoded_preview_bitrate_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_encoded_preview_bitrate(NULL, BITRATE);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_attr_get_encoded_preview_gop_interval_p
 * @since_tizen         3.0
 * @description         To check encoded preview gop interval value with valid pointers.
 * @scenario            This test is for checking valid pointer and value in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Check encoded preview format is supported or not. \n
                        3. Get gop interval.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_encoded_preview_gop_interval_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int gop_interval = 0;
	bool is_supported_encoded_preview = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_preview_format(camera, _preview_format_cb, &is_supported_encoded_preview);

	if (is_supported_encoded_preview) {
		ret = camera_attr_get_encoded_preview_gop_interval(camera, &gop_interval);
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		fprintf(stderr, "encoded preview format is not supported.\n");
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_encoded_preview_gop_interval_n
 * @since_tizen         3.0
 * @description         To check encoded preview gop interval value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_encoded_preview_gop_interval_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = camera_attr_get_encoded_preview_gop_interval(NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_encoded_preview_gop_interval_p
 * @since_tizen         3.0
 * @description         To check encoded preview gop interval value with valid pointers.
 * @scenario            This test is for checking valid pointer and value in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Check encoded preview format is supported or not. \n
                        3. Set valid value to set preview gop interval.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_encoded_preview_gop_interval_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool is_supported_encoded_preview = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_foreach_supported_preview_format(camera, _preview_format_cb, &is_supported_encoded_preview);

	if (is_supported_encoded_preview) {
		ret = camera_set_preview_format(camera, CAMERA_PIXEL_FORMAT_H264);
		assert_eq(ret, CAMERA_ERROR_NONE);

		ret = camera_attr_set_encoded_preview_gop_interval(camera, GOPINTERVAL);
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		fprintf(stderr, "encoded preview format is not supported.\n");
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_encoded_preview_gop_interval_n
 * @since_tizen         3.0
 * @description         To check encoded preview gop interval value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_encoded_preview_gop_interval_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_encoded_preview_gop_interval(NULL, GOPINTERVAL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_pan_p
 * @since_tizen         3.0
 * @description         To check pan value with valid pointers.
 * @scenario            This test is for checking valid pointer and value in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid value to set pan.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_pan_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;
	camera_attr_ptz_move_type_e move_type = CAMERA_ATTR_PTZ_MOVE_RELATIVE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_pan_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (min > max) {
		fprintf(stderr, "Pan is not supported.");
		return 0;
	} else {
		ret = camera_attr_set_pan(camera, move_type, min);
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_pan_n
 * @since_tizen         3.0
 * @description         To check pan value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_pan_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int pan_step = 1;
	camera_attr_ptz_move_type_e move_type = CAMERA_ATTR_PTZ_MOVE_RELATIVE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_pan(NULL, move_type, pan_step);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_pan_p
 * @since_tizen         3.0
 * @description         To check pan value with valid pointers.
 * @scenario            This test is for checking valid pointer and value in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid value to get pan.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_pan_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int pan_step = 0;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_pan_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (min > max) {
		fprintf(stderr, "Pan is not supported.");
		return 0;
	} else {
		ret = camera_attr_get_pan(camera, &pan_step);
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_pan_n1
 * @since_tizen         3.0
 * @description         To check pan value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_pan_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int pan_step = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_pan(NULL, &pan_step);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_pan_n2
 * @since_tizen         3.0
 * @description         To check pan value with invalid null pointer in second parameter.
 * @scenario            This test is for checking invalid null pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer.
 */
int utc_media_camera_attr_get_pan_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_pan(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_pan_range_p
 * @since_tizen         3.0
 * @description         To check pan range value with valid pointers.
 * @scenario            This test is for checking valid pointer and value in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid value to get pan range.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_pan_range_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int x, y;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_pan_range(camera, &x, &y);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_pan_range_n1
 * @since_tizen         3.0
 * @description         To check pan range value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_pan_range_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int x, y;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_pan_range(NULL, &x, &y);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_pan_range_n2
 * @since_tizen         3.0
 * @description         To check pan range value with invalid null pointer in second & third parameter.
 * @scenario            This test is for checking invalid null pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second & third parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer.
 */
int utc_media_camera_attr_get_pan_range_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_pan_range(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_tilt_p
 * @since_tizen         3.0
 * @description         To check tilt value with valid pointers.
 * @scenario            This test is for checking valid pointer and value in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid value to set tilt.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_tilt_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;
	camera_attr_ptz_move_type_e move_type = CAMERA_ATTR_PTZ_MOVE_RELATIVE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tilt_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (min > max) {
		fprintf(stderr, "Tilt is not supported.");
		return 0;
	} else {
		ret = camera_attr_set_tilt(camera, move_type, min);
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_tilt_n
 * @since_tizen         3.0
 * @description         To check tilt value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_tilt_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int tilt_step = 1;
	camera_attr_ptz_move_type_e move_type = CAMERA_ATTR_PTZ_MOVE_RELATIVE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_tilt(NULL, move_type, tilt_step);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tilt_p
 * @since_tizen         3.0
 * @description         To check tilt value with valid pointers.
 * @scenario            This test is for checking valid pointer and value in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid value to get tilt.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_tilt_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int tilt_step = 0;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tilt_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (min > max) {
		fprintf(stderr, "Tilt is not supported.");
		return 0;
	} else {
		ret = camera_attr_get_tilt(camera, &tilt_step);
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tilt_n1
 * @since_tizen         3.0
 * @description         To check tilt value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_tilt_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int tilt_degree = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tilt(NULL, &tilt_degree);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tilt_n2
 * @since_tizen         3.0
 * @description         To check tilt value with invalid null pointer in second parameter.
 * @scenario            This test is for checking invalid null pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer.
 */
int utc_media_camera_attr_get_tilt_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tilt(camera, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tilt_range_p
 * @since_tizen         3.0
 * @description         To check tilt range value with valid pointers.
 * @scenario            This test is for checking valid pointer and value in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid value to get tilt range.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_tilt_range_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int x, y;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tilt_range(camera, &x, &y);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tilt_range_n1
 * @since_tizen         3.0
 * @description         To check tilt range value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_tilt_range_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int x, y;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tilt_range(NULL, &x, &y);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_tilt_range_n2
 * @since_tizen         3.0
 * @description         To check tilt range value with invalid null pointer in second & third parameter.
 * @scenario            This test is for checking invalid null pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in second & third parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer.
 */
int utc_media_camera_attr_get_tilt_range_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_tilt_range(camera, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_ptz_type_p
 * @since_tizen         3.0
 * @description         To check the type of PTZ(Pan Tilt Zoom) with valid parameters.
 * @scenario            This test is for checking valid pointer and value in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid value to set the type of ptz.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_ptz_type_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_ptz_type_e ptz_type = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_ptz_type(camera, _ptz_type_cb, &ptz_type);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if ((int)ptz_type < 0) {
		fprintf(stderr, "PTZ is not supported.");
		return 0;
	} else {
		ret = camera_attr_set_ptz_type(camera, ptz_type);
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_ptz_type_n
 * @since_tizen         3.0
 * @description         To check the type of PTZ(Pan Tilt Zoom) with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_ptz_type_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_ptz_type_e ptz_type = -1;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_set_ptz_type(NULL, ptz_type);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_ptz_type_p
 * @since_tizen         3.0
 * @description         To check supported PTZ(Pan Tilt Zoom) type with valid parameters.
 * @scenario            This test is for checking valid parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_foreach_supported_ptz_type_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_ptz_type(camera, _ptz_type_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_foreach_supported_ptz_type_n
 * @since_tizen         3.0
 * @description         To check PTZ(Pan Tilt Zoom) type supported with invalid parameters.
 * @scenario            This test is for checking invalid pointers such as camera handle "null" and callback function "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointers which is camera handle null and callback function "null".
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle and callback function are null.
 */
int utc_media_camera_attr_foreach_supported_ptz_type_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_foreach_supported_ptz_type(NULL, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return false;
}

/**
 * @testcase            utc_media_camera_attr_set_display_roi_area_p
 * @since_tizen         3.0
 * @description         To check display ROI(Region Of Interest) area with valid pointers.
 * @scenario            This test is for checking valid pointer and value in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid value to set display ROI area.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_display_roi_area_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int x = 100;
	int y = 100;
	int width = 360;
	int height = 480;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_mode(camera, CAMERA_DISPLAY_MODE_CUSTOM_ROI);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_set_display_roi_area(camera, x, y, width, height);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_tilt_n
 * @since_tizen         3.0
 * @description         To check display ROI(Region Of Interest) area with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_display_roi_area_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	int x = 100;
	int y = 100;
	int width = 360;
	int height = 480;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_mode(camera, CAMERA_DISPLAY_MODE_CUSTOM_ROI);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_set_display_roi_area(NULL, x, y, width, height);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_display_roi_area_p
 * @since_tizen         3.0
 * @description         To check display ROI(Region Of Interest) area with valid pointers.
 * @scenario            This test is for checking valid pointer and value in all parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Set valid value to get display ROI area.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_get_display_roi_area_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int x;
	int y;
	int width;
	int height;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_mode(camera, CAMERA_DISPLAY_MODE_CUSTOM_ROI);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_get_display_roi_area(camera, &x, &y, &width, &height);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_display_roi_area_n1
 * @since_tizen         3.0
 * @description         To check display ROI(Region Of Interest) area with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_get_display_roi_area_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int x;
	int y;
	int width;
	int height;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_mode(camera, CAMERA_DISPLAY_MODE_CUSTOM_ROI);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_get_display_roi_area(NULL, &x, &y, &width, &height);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_get_display_roi_area_n2
 * @since_tizen         3.0
 * @description         To check display ROI(Region Of Interest) area with invalid null pointer in coord parameters.
 * @scenario            This test is for checking invalid null pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer in coord parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer.
 */
int utc_media_camera_attr_get_display_roi_area_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display_mode(camera, CAMERA_DISPLAY_MODE_CUSTOM_ROI);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_get_display_roi_area(camera, NULL, NULL, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_hue_n1
 * @since_tizen         5.0
 * @description         To check hue value with camera handle "null".
 * @scenario            This test is for checking invalid pointer such as camera handle "null". \n
                        1. Check camera device which is supported or not. \n
                        2. Set invalid pointer which is camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_camera_attr_set_hue_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_hue_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (min > max) {
		fprintf(stderr, "hue is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_hue(NULL, max);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_hue_n2
 * @since_tizen         5.0
 * @description         To check hue value within invalid range.
 * @scenario            This test is for checking invalid parameter which is out of range. \n
                        1. Check camera device which is supported or not. \n
                        2. Get valid hue range. \n
                        3. Check hue which is supported or not. \n
                        4. Set invalid hue value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because of invalid hue value.
 */
int utc_media_camera_attr_set_hue_n2(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_hue_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (min > max) {
		fprintf(stderr, "hue is not supported.\n");
		return 0;
	}

	ret = camera_attr_set_hue(camera, max + 1);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_attr_set_hue_p
 * @since_tizen         5.0
 * @description         To check hue value within valid range.
 * @scenario            This test is for checking valid parameter . \n
                        1. Check camera device which is supported or not. \n
                        2. Get valid hue range. \n
                        3. Check hue which is supported or not. \n
                        4. Set valid hue value.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_attr_set_hue_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int min = 0;
	int max = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_attr_get_hue_range(camera, &min, &max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (min > max) {
		fprintf(stderr, "hue is not supported.\n");
		return 0;
	}
	ret = camera_attr_set_hue(camera, max);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}
