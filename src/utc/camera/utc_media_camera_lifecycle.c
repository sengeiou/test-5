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
#include <unistd.h>
#include <glib.h>
#include <pthread.h>
#include <glib-object.h>
#include <system_info.h>

#include "assert.h"


static int g_startup_err = CAMERA_ERROR_NONE;

static camera_h camera = NULL;
static bool camera_supported = false;

typedef enum {
	ASYNC_READY,
	ASYNC_DONE
} async_state;

async_state async_flag;

/**
 * @function            utc_media_camera_lifecycle_startup
 * @description         Called before each test.
                        This is the precondition for checking apis. \n
                        This precondition is camera_create api for checking device and privilege error.
 * @scenario            1. Create camera device and check camera error. \n
                        2. Get camera state for checking the camera works fine.
 * @parameter           N/A
 * @return              N/A
 */
void utc_media_camera_lifecycle_startup(void)
{
	g_startup_err = CAMERA_ERROR_NONE;
	camera = NULL;
	camera_supported = false;

	system_info_get_platform_bool("http://tizen.org/feature/camera", &camera_supported);

	g_startup_err = camera_create(CAMERA_DEVICE_CAMERA0, &camera);
	if (g_startup_err != CAMERA_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "camera_create failed (code: 0x%x)\n", g_startup_err);
	}

	return;
}


/**
 * @function            utc_media_camera_lifecycle_cleanup
 * @description         Called after each test.
                        This is the postcondition for checking apis. \n
                        This postcondition is camera_destroy api for cleaning up the resources properly.
 * @scenario            1. Destroy camera.
 * @parameter           N/A
 * @return              N/A
 */
void utc_media_camera_lifecycle_cleanup(void)
{
	if (camera)
		camera_destroy(camera);

	return;
}


/**
 * @testcase            utc_media_camera_create_n
 * @since_tizen         2.3
 * @description         To check camera creation with invalid pointer.
 * @scenario            This test for checking invalid pointer parameter. \n
                        1. Check camera device which is supported or not .\n
                        2. Create camera with invalid pointer in getting function.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the pointer for getting handle is null.
 */
int utc_media_camera_create_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_create(CAMERA_DEVICE_CAMERA0, NULL);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_create_p
 * @since_tizen         2.3
 * @description         To check camera creation with valid pointer and value.
 * @scenario            This test for checking valid pointer parameter. \n
                        1. Check camera device which is supported or not .\n
                        2. Destroy camera because of precondition. @see utc_media_camera_lifecycle_startup. \n
                        3. Create camera with valid pointer in getting function.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_create_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_destroy(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	camera = NULL;

	ret = camera_create(CAMERA_DEVICE_CAMERA0, &camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_destroy_n
 * @since_tizen         2.3
 * @description         To check camera destruction with invalid pointer.
 * @scenario            This test for checking invalid pointer parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Destroy camera with invalid handle. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the pointer for getting handle is null.
 */
int utc_media_camera_destroy_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_destroy(NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_destroy_p
 * @since_tizen         2.3
 * @description         To check camera destruction with valid pointer.
 * @scenario            This test for checking valid pointer parameter. \n
                        1. Check camera device which is supported or not. \n
                        2. Destroy camera with valid handle. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_destroy_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_destroy(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	camera = NULL;

	return 0;
}

/**
 * @testcase            utc_media_camera_start_preview_n
 * @since_tizen         2.3
 * @description         To check camera start preview with in valid handle.
 * @scenario            This test for checking camera preview with invalid handle. \n
                        1. Already created camera according to precondition. \n
                        2. Start preview with null pointer handle. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because of null pointer handle.
 */
int utc_media_camera_start_preview_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_start_preview(NULL);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


static void _error_cb(int error, camera_state_e current_state, void *user_data)
{
	return;
}

static void _preview_cb(camera_preview_data_s *frame, void *user_data)
{
	return;
}

static void _media_packet_preview_cb(media_packet_h pkt, void *user_data)
{
	if (pkt) {
		media_packet_destroy(pkt);
		pkt = NULL;
	}

	return;
}

/**
 * @testcase            utc_media_camera_start_preview_p1
 * @since_tizen         2.3
 * @description         To check camera start preview with valid parameters.
 * @scenario            This test for checking camera preview with valid parameters. \n
                        1. Already created camera according to precondition. \n
                        2. Check camera device which is supported or not .\n
                        3. add callback about error. \n
                        4. add callback about preview callback. \n
                        5. Start preview with valid parameter. \n
                        6. Use sleep function because of getting callback. You can remove this sleep function. \n
                        7. Stop preview. \n
                        8. unset error callback. \n
                        9. unset preview callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_start_preview_p1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_error_cb(camera, _error_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_set_preview_cb(camera, _preview_cb, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_start_preview(camera);

	usleep(50 * 1000);

	camera_stop_preview(camera);
	camera_unset_error_cb(camera);
	camera_unset_preview_cb(camera);

	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_start_preview_p2
 * @since_tizen         2.3
 * @description         To check camera start preview with valid parameters.
 * @scenario            This test for checking camera media packet preview with valid parameters. \n
                        1. Already created camera according to precondition. \n
                        2. Check camera device which is supported or not .\n
                        3. Check media packet preview callback supported or not . \n
                        4-1. If supported, add media packet preview callback. \n
                        4-2. If not supported, This api should return not supported. \n
                        5. Start preview with valid parameter.
                        6. Use sleep function because of getting callback. You can remove this sleep function. \n
                        7. Stop preview.
                        8. unset media packet preview callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_start_preview_p2(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool is_supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	is_supported = camera_is_supported_media_packet_preview_cb(camera);

	if (is_supported) {
		ret = camera_set_media_packet_preview_cb(camera, _media_packet_preview_cb, NULL);
		assert_eq(ret, CAMERA_ERROR_NONE);
	} else {
		ret = camera_set_media_packet_preview_cb(camera, _media_packet_preview_cb, NULL);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	}

	ret = camera_start_preview(camera);

	usleep(50 * 1000);

	camera_stop_preview(camera);
	camera_unset_media_packet_preview_cb(camera);

	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}


/**
 * @testcase            utc_media_camera_stop_preview_n
 * @since_tizen         2.3
 * @description         To check camera stop preview with invalid parameter.
 * @scenario            This test for checking camera stop preview with invalid camera handle "null"
                        1. Already created camera according to precondition. \n
                        2. Check camera device which is supported or not. \n
                        3. Stop preview with camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because camera handle is null pointer.
 */
int utc_media_camera_stop_preview_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_stop_preview(NULL);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_stop_preview_p
 * @since_tizen         2.3
 * @description         To check camera stop preview with valid parameter.
 * @scenario            This test for checking camera stop preview with valid parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Start preview. \n
                        3. Stop preview. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_stop_preview_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_start_preview(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_stop_preview(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

static void _camera_capture_cb(camera_image_data_s *image, camera_image_data_s *postview, camera_image_data_s *thumbnail, void *data)
{
	return;
}

static void _camera_capture_completed_cb(void *data)
{
	return;
}

/**
 * @testcase            utc_media_camera_start_capture_n
 * @since_tizen         2.3
 * @description         To check camera start capture with precondition
 * @scenario            This test for checking camera start capture without camera start preview.
                        1. Check camera device which is supported or not. \n
                        2. Start capture. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because there's no start preview.
 */
int utc_media_camera_start_capture_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_start_capture(camera, NULL, NULL, NULL);

	assert_eq(ret, CAMERA_ERROR_INVALID_STATE);

	return 0;
}

/**
 * @testcase            utc_media_camera_start_capture_p
 * @since_tizen         2.3
 * @description         To check camera start capture with precondition.
 * @scenario            This test for checking camera start capture with valid parameter.
                        1. Check camera device which is supported or not. \n
                        2. Set display settings. \n
                        3. Start preview. \n
                        4. Start capture. \n
                        5. Stop preview. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_start_capture_p(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_set_display(camera, CAMERA_DISPLAY_TYPE_NONE, NULL);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_start_preview(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	usleep(50 * 1000);

	ret = camera_start_capture(camera, _camera_capture_cb, _camera_capture_completed_cb, NULL);

	usleep(1000 * 2000);

	camera_start_preview(camera);
	camera_stop_preview(camera);

	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_state_n
 * @since_tizen         2.3
 * @description         To check camera state with invalid parameter.
 * @scenario            This test for checking camera state with invalid pointer.
                        1. Check camera device which is supported or not. \n
                        2. Get camera state with null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because invalid null pointer parameter.
 */
int utc_media_camera_get_state_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_state(camera, NULL);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_get_state_p
 * @since_tizen         2.3
 * @description         To check camera state with valid parameter.
 * @scenario            This test is for camera state with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Get camera state with null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_get_state_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_state_e state = CAMERA_STATE_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_state(camera, &state);

	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_start_focusing_n
 * @since_tizen         2.3
 * @description         To check camera start focus with invalid parameter.
 * @scenario            This test is for camera start focus with camera handle "null"
                        1. Check camera device which is supported or not. \n
                        2. Start camera focusing.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_start_focusing_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_start_focusing(NULL, false);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_start_focusing_p1
 * @since_tizen         2.3
 * @description         To check camera start focus with valid parameters.
 * @scenario            This test is for camera start focus with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Start preview. \n
                        3. Get autofocus mode. \n
                        4-1. If autofocus mode is AF_NONE, stop preview because this is not supported "Fixed Focus". \n
                        4-2. If others, start focus. \n
                        5. Cancel focus. \n
                        6. Stop preview.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_start_focusing_p1(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_af_mode_e focus_mode = CAMERA_ATTR_AF_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_start_preview(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_get_af_mode(camera, &focus_mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (focus_mode == CAMERA_ATTR_AF_NONE) {
		camera_stop_preview(camera);
		fprintf(stderr, "auto focus is not supported, this is fixed focus.\n");
		return 0;
	}

	ret = camera_start_focusing(camera, false);

	sleep(5);

	camera_cancel_focusing(camera);
	camera_stop_preview(camera);

	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_start_focusing_p2
 * @since_tizen         2.3
 * @description         To check camera start focus with valid parameters.
 * @scenario            This test is for camera start focus with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Start preview. \n
                        3. Get autofocus mode. \n
                        4-1. If autofocus mode is AF_NONE, stop preview because this is not supported "Fixed Focus". \n
                        4-2. If others, start focus for checking continuous autofocus. \n
                        5. Cancel focus. \n
                        6. Stop preview.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_start_focusing_p2(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_af_mode_e focus_mode = CAMERA_ATTR_AF_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_start_preview(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_get_af_mode(camera, &focus_mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (focus_mode == CAMERA_ATTR_AF_NONE) {
		camera_stop_preview(camera);
		fprintf(stderr, "auto focus is not supported, this is fixed focus.\n");
		return 0;
	}

	ret = camera_start_focusing(camera, true);
	if (ret == CAMERA_ERROR_NOT_SUPPORTED) {
		ret = camera_start_focusing(camera, false);
	}

	sleep(5);

	camera_cancel_focusing(camera);
	camera_stop_preview(camera);

	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_camera_cancel_focusing_n1
 * @since_tizen         2.3
 * @description         To check camera cancel focus with invalid precodition.
 * @scenario            This test is for camera cancel focus without start focusing.
                        1. Check camera device which is supported or not. \n
                        2. Cancel focus.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because the camera does not start preview and focus.
 */
int utc_media_camera_cancel_focusing_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_cancel_focusing(camera);

	assert_eq(ret, CAMERA_ERROR_INVALID_STATE);

	return 0;
}

/**
 * @testcase            utc_media_camera_cancel_focusing_n2
 * @since_tizen         2.3
 * @description         To check camera cancel focus with invalid parameter.
 * @scenario            This test is for camera cancel focus with camera handle null.
                        1. Check camera device which is supported or not. \n
                        2. Cancel focus.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_cancel_focusing_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_cancel_focusing(NULL);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_cancel_focusing_p
 * @since_tizen         2.3
 * @description         To check camera cancel focus with valid parameters.
 * @scenario            This test is for camera cancel focus with all precondition and valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Start Preview. \n
                        3. Check autofocus mode. \n
                        4-1. If autofocus mode is AF_NONE, autofocus is not supported, only for rixed focus. \n
                        4-2. If there's other mode, start focusing without countinous focus. \n
                        5. Cancel focusing.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_cancel_focusing_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	camera_attr_af_mode_e focus_mode = CAMERA_ATTR_AF_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_start_preview(camera);
	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_attr_get_af_mode(camera, &focus_mode);
	assert_eq(ret, CAMERA_ERROR_NONE);

	if (focus_mode == CAMERA_ATTR_AF_NONE) {
		camera_stop_preview(camera);
		fprintf(stderr, "auto focus is not supported, this is fixed focus.\n");
		return 0;
	}

	ret = camera_start_focusing(camera, false);
	if (ret != CAMERA_ERROR_NONE) {
		camera_stop_preview(camera);
		return 0;
	}

	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_cancel_focusing(camera);

	camera_stop_preview(camera);

	assert_eq(ret, CAMERA_ERROR_NONE);

	return 0;
}

static void _face_detected_cb(camera_detected_face_s *faces, int count, void *user_data)
{
	if (user_data)
		*(int *)user_data = faces->id;

	async_flag = ASYNC_DONE;

	return;
}

/**
 * @testcase            utc_media_camera_is_supported_continuous_capture_n
 * @since_tizen         2.3
 * @description         To check camera continous capture supported or not.
 * @scenario            This test is for checking continous capture supported or not with invalid handle.
                        1. Check camera device which is supported or not. \n
                        2. Check continous capture supported or not.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_is_supported_continuous_capture_n(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_is_supported_continuous_capture(NULL);

	fprintf(stderr, "camera_is_supported_continuous_capture(NULL) ret %d.\n", ret);

	return 0;
}

/**
 * @testcase            utc_media_camera_is_supported_continuous_capture_p
 * @since_tizen         2.3
 * @description         To check camera continous capture supported or not.
 * @scenario            This test is for checking continous capture supported or not with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Check continous capture supported or not.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_is_supported_continuous_capture_p(void)
{
	int ret = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_is_supported_continuous_capture(camera);

	fprintf(stderr, "camera_is_supported_continuous_capture(camera) ret %d.\n", ret);

	return 0;

}

/**
 * @testcase            utc_media_camera_start_continuous_capture_n1
 * @since_tizen         2.3
 * @description         To check camera to start continous capture with invalid values.
 * @scenario            This test is for checking camera start continous capture with invalid values such as count of picture and interval of time.
                        1. Check camera device which is supported or not. \n
                        2. Check continous capture supported or not. \n
                        3-1. It not supported, the api should returns not-supported.
                        3-2. It supported, the api will be set " 0 count, 0 interval"
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because the values of parameters are not invalid.
 */
int utc_media_camera_start_continuous_capture_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_is_supported_continuous_capture(camera);

	if (!supported) {
		ret = camera_start_continuous_capture(camera, 0, 0, NULL, NULL, NULL);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else {
		ret = camera_start_continuous_capture(camera, 0, 0, NULL, NULL, NULL);
		assert_eq(ret , CAMERA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_start_continuous_capture_n2
 * @since_tizen         2.3
 * @description         To check camera to start continous capture with invalid handle.
 * @scenario            This test is for checking camera start continous capture with invalid camera handle.
                        1. Check camera device which is supported or not. \n
                        2. Start contounous capture with camera handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because the pointer are not invalid.
 */
int utc_media_camera_start_continuous_capture_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_start_continuous_capture(NULL, 0, 0, NULL, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}



/**
 * @testcase            utc_media_camera_start_continuous_capture_p
 * @since_tizen         2.3
 * @description         To check camera to start continous capture with valid parameters.
 * @scenario            This test is for checking camera start continous capture with valid parameters. \n
                        1. Check camera device which is supported or not. \n
                        2. Check continous capture supported or not. \n
                        3-1. It not supported, the api should returns not-supported. \n
                        3-2. It supported, the api will be set display. \n
                        4. Start Preview. \n
                        5. Start continuous capture with valid parameters. \n
                        6. Stop continuous capture. \n
                        7. Stop preview.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_start_continuous_capture_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_is_supported_continuous_capture(camera);

	if (!supported) {
		ret = camera_start_continuous_capture(camera, 10, 100, NULL, NULL, NULL);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else {
		ret = camera_set_display(camera, CAMERA_DISPLAY_TYPE_NONE, 0);
		assert_eq(ret, CAMERA_ERROR_NONE);

		ret = camera_start_preview(camera);
		assert_eq(ret, CAMERA_ERROR_NONE);

		ret = camera_start_continuous_capture(camera, 10, 100, NULL, NULL, NULL);

		sleep(3);

		camera_stop_continuous_capture(camera);
		camera_start_preview(camera);
		camera_stop_preview(camera);

		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_stop_continuous_capture_n
 * @since_tizen         2.3
 * @description         To check camera to stop continous capture with invalid pointer.
 * @scenario            This test is for checking stop countinous captuer with null pointer. \n
                        1. Check camera device which is supported or not. \n
                        2. Check continous capture supported or not. \n
                        3-1. If not supported, the api should return not-supported. \n
                        3-2. If supported, set null pointer in stop continous capture.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_stop_continuous_capture_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_is_supported_continuous_capture(camera);

	if (!supported) {
		ret = camera_stop_continuous_capture(camera);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else {
		ret = camera_stop_continuous_capture(NULL);
		assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_stop_continuous_capture_p
 * @since_tizen         2.3
 * @description         To check camera to stop continous capture with valid pointer.
 * @scenario            This test is for checking stop continous capture with valid parameters.
                        1. Check camera device which is supported or not. \n
                        2. Check continous capture supported or not. \n
                        3-1. If not supported, the api should return not-supported. \n
                        3-2. If supported, set display mode. \n
                        4. Start Preview. \n
                        5. Start continous capture. \n
                        6. Stop valid parameter in stop continous capture.
                        7. Stop Preview.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_stop_continuous_capture_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_is_supported_continuous_capture(camera);

	if (!supported) {
		ret = camera_stop_continuous_capture(camera);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else {
		ret = camera_set_display(camera, CAMERA_DISPLAY_TYPE_NONE, 0);
		assert_eq(ret, CAMERA_ERROR_NONE);

		ret = camera_start_preview(camera);
		assert_eq(ret, CAMERA_ERROR_NONE);

		ret = camera_start_continuous_capture(camera, 10, 300, NULL, NULL, NULL);
		assert_eq(ret, CAMERA_ERROR_NONE);

		sleep(1);

		ret = camera_stop_continuous_capture(camera);

		camera_start_preview(camera);
		camera_stop_preview(camera);

		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}


/**
 * @testcase            utc_media_camera_start_face_detection_n1
 * @since_tizen         2.3
 * @description         To check camera to start face detection with invalid pointer.
 * @scenario            This test is for checking to start face detection.
                        1. Check camera device which is supported or not. \n
                        2. Check face detection supported. \n
                        3-1. If not supported, this api should return not supported. \n
                        3-2. If supported, start face detection with null camera handle.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_start_face_detection_n1(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_is_supported_face_detection(camera);

	if (!supported) {
		ret = camera_start_face_detection(camera, NULL, NULL);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else {
		ret = camera_start_face_detection(NULL, _face_detected_cb, NULL);
		assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_media_camera_start_face_detection_n2
 * @since_tizen         2.3
 * @description         To check camera to start face detection with invalid pointer.
 * @scenario            This test is for checking to start face detection.
                        1. Check camera device which is supported or not. \n
                        2. Check face detection supported. \n
                        3. Start face detection with null camera handle.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_start_face_detection_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_start_face_detection(NULL, NULL, NULL);
	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_camera_start_face_detection_p
 * @since_tizen         2.3
 * @description         To check camera to start face detection with valid parameters.
 * @scenario            This test is for checking to start face detection.
                        1. Check camera device which is supported or not. \n
                        2. Check face detection supported. \n
                        3-1. If not supported, this api should return not-supported. \n
                        3-2. If supported, set display mode. \n 
                        4. Start preview. \n
                        5. Start face detection with valid camera handle. \n
                        6. Stop preview.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_start_face_detection_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_is_supported_face_detection(camera);

	if (!supported) {
		ret = camera_start_face_detection(camera, NULL, NULL);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else {
		ret = camera_set_display(camera, CAMERA_DISPLAY_TYPE_NONE, 0);
		assert_eq(ret, CAMERA_ERROR_NONE);

		ret = camera_start_preview(camera);
		assert_eq(ret, CAMERA_ERROR_NONE);

		ret = camera_start_face_detection(camera, NULL, NULL);
		if (ret == CAMERA_ERROR_NONE) {
			camera_stop_face_detection(camera);
		}

		camera_stop_preview(camera);

		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}



/**
 * @testcase            utc_media_camera_stop_face_detection_n
 * @since_tizen         2.3
 * @description         To check camera to stop face detection with valid parameters.
 * @scenario            This test is for checking to stop face detection.
                        1. Check camera device which is supported or not. \n
                        2. Check face detection supported. \n
                        3-1. If not supported, this api should return not-supported. \n
                        3-2. If supported, stop face detection with null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_stop_face_detection_n(void)
{
	int ret = CAMERA_ERROR_NONE;
	bool supported = false;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	supported = camera_is_supported_face_detection(camera);

	if (!supported) {
		ret =camera_stop_face_detection(camera);
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else {
		ret = camera_stop_face_detection(NULL);
		assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/**
 * @testcase            utc_media_camera_change_device_p
 * @since_tizen         3.0
 * @description         To check camera device change with valid parameters.
 * @scenario            This test is for checking to change camera device.
                        1. Check camera device which is supported or not. \n
                        2. Change camera device
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be success.
 */
int utc_media_camera_change_device_p(void)
{
	int ret = CAMERA_ERROR_NONE;
	int device_count = 0;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_get_device_count(camera, &device_count);

	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_change_device(camera, CAMERA_DEVICE_CAMERA1);

	if (device_count < 2) {
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	return 0;
}


/**
 * @testcase            utc_media_camera_change_device_n1
 * @since_tizen         3.0
 * @description         To check camera device change with invalid parameter.
 * @scenario            This test is for checking to change camera device.
                        1. Check camera device which is supported or not. \n
                        2. Change camera device with invalid parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because the camera handle is null.
 */
int utc_media_camera_change_device_n1(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_change_device(NULL, CAMERA_DEVICE_CAMERA1);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_change_device_n2
 * @since_tizen         3.0
 * @description         To check camera device change with invalid parameter.
 * @scenario            This test is for checking to change camera device.
                        1. Check camera device which is supported or not. \n
                        2. Change camera device with invalid parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because the device type is invalid.
 */
int utc_media_camera_change_device_n2(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_change_device(camera, -1);

	assert_eq(ret, CAMERA_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_camera_change_device_n3
 * @since_tizen         3.0
 * @description         To check camera to change device at invalid state.
 * @scenario            This test is for checking to change camera device.
                        1. Check camera device which is supported or not. \n
                        2. Start preview. \n
                        3. Change camera device.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is success. \n
                        The "ret" value should be error because the camera state is not #CAMERA_STATE_CREATED.
 */
int utc_media_camera_change_device_n3(void)
{
	int ret = CAMERA_ERROR_NONE;

	if (!camera_supported) {
		assert_eq(g_startup_err, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(g_startup_err, CAMERA_ERROR_NONE);

	ret = camera_start_preview(camera);

	assert_eq(ret, CAMERA_ERROR_NONE);

	ret = camera_change_device(camera, CAMERA_DEVICE_CAMERA1);

	camera_stop_preview(camera);

	assert_eq(ret, CAMERA_ERROR_INVALID_STATE);

	return 0;
}
