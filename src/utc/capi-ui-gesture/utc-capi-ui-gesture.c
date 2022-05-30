//
// Copyright (c) 2020 Samsung Electronics Co., Ltd.
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
#include <string.h>
#include <gesture.h>
#include <gesture_common.h>


static bool g_supported = false;

/**
 * @function		utc_capi_ui_gesture_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_capi_ui_gesture_startup(void)
{
	system_info_get_platform_bool("http://tizen.org/feature/sensor.gesture_recognition", &g_supported);
}

/**
 * @function		utc_capi_ui_gesture_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_capi_ui_gesture_cleanup(void)
{
}


static void gesture_cb(hand_gesture_h handle, hand_gesture_type_e gesture, double timestamp, hand_gesture_error_e error, void *user_data)
{
}

static void gesture_error_cb(hand_gesture_h handle, hand_gesture_error_e error, const char* msg, void *user_data)
{
}


/**
 * @testcase		utc_hand_gesture_is_supported_type_p
 * @since_tizen		6.0
 * @description		Positive UTC of the function that checks whether the gesture is supported or not.
 */
int utc_hand_gesture_is_supported_type_p(void)
{
	int ret = 0;
	bool supported = true;
	hand_gesture_h handle = NULL;

	ret = hand_gesture_create(&handle);

	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_NONE);

	ret = hand_gesture_is_supported_type(handle, HAND_GESTURE_WRIST_UP, &supported);
	assert_eq(ret, HAND_GESTURE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_hand_gesture_create_p
 * @since_tizen		6.0
 * @description		Positive UTC of the function that request to create a gesture handle.
 */
int utc_hand_gesture_create_p(void)
{
	int ret = 0;
	hand_gesture_h handle = NULL;
	ret = hand_gesture_create(&handle);

	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_hand_gesture_destroy_p
 * @since_tizen		6.0
 * @description		Positive UTC of the function that request to destroy a gesture handle.
 */
int utc_hand_gesture_destroy_p(void)
{
	int ret = 0;
	hand_gesture_h handle = NULL;
	ret = hand_gesture_create(&handle);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_NONE);

	ret = hand_gesture_destroy(handle);
	assert_eq(ret, HAND_GESTURE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_set_option_p
 * @since_tizen		6.0
 * @description		Positive UTC of the function that set option for gesture engine.
 */
int utc_hand_gesture_set_option_p(void)
{
	int ret = 0;
	hand_gesture_h handle = NULL;
	ret = hand_gesture_create(&handle);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_NONE);

	ret = hand_gesture_set_option(handle, HAND_GESTURE_OPTION_DEFAULT);
	assert_eq(ret, HAND_GESTURE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_start_recognition_p
 * @since_tizen		6.0
 * @description		Positive UTC of the function that request to start engine recognition for receiving gesture event.
 */
int utc_hand_gesture_start_recognition_p(void)
{
	int ret = 0;
	hand_gesture_h handle = NULL;
	ret = hand_gesture_create(&handle);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_NONE);

	ret = hand_gesture_start_recognition(handle, HAND_GESTURE_WRIST_UP, gesture_cb, NULL);
	assert_eq(ret, HAND_GESTURE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_stop_recognition_p
 * @since_tizen		6.0
 * @description		Positive UTC of the function that request to stop engine recognition.
 */
int utc_hand_gesture_stop_recognition_p(void)
{
	int ret = 0;
	hand_gesture_h handle = NULL;
	ret = hand_gesture_create(&handle);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_NONE);

	ret = hand_gesture_stop_recognition(handle);
	assert_eq(ret, HAND_GESTURE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_get_engine_info_p
 * @since_tizen		6.0
 * @description		Positive UTC of the function that request to get a current active engine information.
 */
int utc_hand_gesture_get_engine_info_p(void)
{
	int ret = 0;
	hand_gesture_h handle = NULL;
	ret = hand_gesture_create(&handle);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_NONE);

	char *engine_app_id = "appid";
	char *engine_name = "name";

	ret = hand_gesture_get_engine_info(handle, &engine_app_id, &engine_name);
	assert_eq(ret, HAND_GESTURE_ERROR_NONE);
	assert(engine_app_id);
	assert(engine_name);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_set_error_cb_p
 * @since_tizen		6.0
 * @description		Positive UTC of the function that set error callback function.
 */
int utc_hand_gesture_set_error_cb_p(void)
{
	int ret = 0;
	hand_gesture_h handle = NULL;
	ret = hand_gesture_create(&handle);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_NONE);

	ret = hand_gesture_set_error_cb(handle, gesture_error_cb, NULL);
	assert_eq(ret, HAND_GESTURE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_unset_error_cb_p
 * @since_tizen		6.0
 * @description		Positive UTC of the function that unset error callback function.
 */
int utc_hand_gesture_unset_error_cb_p(void)
{
	int ret = 0;
	hand_gesture_h handle = NULL;
	ret = hand_gesture_create(&handle);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_NONE);

	ret = hand_gesture_unset_error_cb(handle);
	assert_eq(ret, HAND_GESTURE_ERROR_NONE);
	return 0;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////



/**
 * @testcase		utc_hand_gesture_is_supported_type_n
 * @since_tizen		6.0
 * @description		Negative UTC of the function that checks whether the gesture is supported or not.
 */
int utc_hand_gesture_is_supported_type_n(void)
{
	int ret = hand_gesture_is_supported_type(NULL, HAND_GESTURE_WRIST_UP, NULL);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_create_n
 * @since_tizen		6.0
 * @description		Negative UTC of the function that request to create a gesture handle.
 */
int utc_hand_gesture_create_n(void)
{
	int ret = hand_gesture_create(NULL);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_destroy_n
 * @since_tizen		6.0
 * @description		Negative UTC of the function that request to destroy a gesture handle.
 */
int utc_hand_gesture_destroy_n(void)
{
	int ret = hand_gesture_destroy(NULL);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_set_option_n
 * @since_tizen		6.0
 * @description		Negative UTC of the function that set option for gesture engine.
 */
int utc_hand_gesture_set_option_n(void)
{
	int ret = hand_gesture_set_option(NULL, HAND_GESTURE_OPTION_DEFAULT);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_start_recognition_n
 * @since_tizen		6.0
 * @description		Negative UTC of the function that request to start engine recognition for receiving gesture event.
 */
int utc_hand_gesture_start_recognition_n(void)
{
	int ret = hand_gesture_start_recognition(NULL, HAND_GESTURE_WRIST_UP, NULL, NULL);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_stop_recognition_n
 * @since_tizen		6.0
 * @description		Negative UTC of the function that request to stop engine recognition.
 */
int utc_hand_gesture_stop_recognition_n(void)
{
	int ret = hand_gesture_stop_recognition(NULL);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_get_engine_info_n
 * @since_tizen		6.0
 * @description		Negative UTC of the function that request to get a current active engine information.
 */
int utc_hand_gesture_get_engine_info_n(void)
{
	int ret = hand_gesture_get_engine_info(NULL, NULL, NULL);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_set_error_cb_n
 * @since_tizen		6.0
 * @description		Negative UTC of the function that set error callback function.
 */
int utc_hand_gesture_set_error_cb_n(void)
{
	int ret = hand_gesture_set_error_cb(NULL, NULL, NULL);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_hand_gesture_unset_error_cb_n
 * @since_tizen		6.0
 * @description		Negative UTC of the function that unset error callback function.
 */
int utc_hand_gesture_unset_error_cb_n(void)
{
	int ret = hand_gesture_unset_error_cb(NULL);
	if (g_supported == false) {
		assert_eq(ret, HAND_GESTURE_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, HAND_GESTURE_ERROR_INVALID_PARAMETER);
	return 0;
}
