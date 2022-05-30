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

#include "assert.h"
#include <media/recorder.h>
#include <system_info.h>

static recorder_h recorder = NULL;
static camera_h camera = NULL;
static bool video_recording_supported = false;
static bool audio_recording_supported = false;
static int startup_ret = RECORDER_ERROR_NONE;
static int startup_ret_camera = CAMERA_ERROR_NONE;

/**
 * @function            utc_media_recorder_callback_startup
 * @description         Called before each test. \n
                        This is the precondition for checking apis. \n
                        Tiis precondition is create_audiorecorder api for checking device and privilege error.
 * @scenario            1. Check device storage supported. \n
                        2. Create audio recorder.
 * @parameter           N/A
 * @return              N/A
 */
void utc_media_recorder_callback_startup(void)
{
	/* start of TC */
	system_info_get_platform_bool("http://tizen.org/feature/media.audio_recording", &audio_recording_supported);
	system_info_get_platform_bool("http://tizen.org/feature/media.video_recording", &video_recording_supported);

	startup_ret = recorder_create_audiorecorder(&recorder);
	startup_ret_camera = camera_create(CAMERA_DEVICE_CAMERA0, &camera);

	return;
}

/**
 * @function            utc_media_recorder_callback_cleanup
 * @description         Called after each test. \n
                        This is the postcondition for checking apis. \n
                        This postcondition is recorder_destroy for cleaning up all recorder resources for next test.
 * @scenario            1. Destroy recorder.
 * @parameter           N/A
 * @return              N/A
 */
void utc_media_recorder_callback_cleanup(void)
{
	/* end of TC */
	if (recorder) {
		recorder_destroy(recorder);
		recorder = NULL;
	}

	if (camera) {
		camera_destroy(camera);
		camera = NULL;
	}

	return;
}

static bool _audio_encoder_cb(recorder_audio_codec_e codec, void *user_data)
{
	return true;
}

static bool _file_format_cb(recorder_file_format_e format, void *user_data)
{
	return true;
}

static bool _video_encoder_cb(recorder_video_codec_e codec,  void *user_data)
{
	return true;
}

static bool _video_resolution_cb(int width, int height, void *user_data)
{
	return true;
}

static void _limit_reached_cb(recorder_recording_limit_type_e type, void *user_data)
{
	return;
}

static void _recording_statis_cb(unsigned long long elapsed_time, unsigned long long file_size,  void *user_data)
{
	return;
}

static void _state_changed_cb(recorder_state_e previous, recorder_state_e current, bool by_asm,  void *user_data)
{
	return;
}

static void _interrupted_cb(recorder_policy_e policy, recorder_state_e previous, recorder_state_e current, void *user_data)
{
	return;
}

static void _interrupt_started_cb(recorder_policy_e policy, recorder_state_e state, void *user_data)
{
	return;
}

static void _audio_stream_cb(void *stream, int size, audio_sample_type_e format, int channel, unsigned int timestamp, void *user_data)
{
	return;
}

static void _error_cb(recorder_error_e error, recorder_state_e current_state, void *user_data)
{
	return;
}

static void _device_state_changed_cb(recorder_type_e type, recorder_device_state_e state, void *user_data)
{
	return;
}

static void _muxed_stream_cb(void *stream, int size, unsigned long long offset, void *user_data)
{
	return;
}

static bool _video_encode_decision_cb(recorder_video_data_s *frame, void *user_data)
{
	return true;
}


/**
 * @testcase            utc_media_recorder_foreach_supported_audio_encoder_p
 * @since_tizen         2.3
 * @description         To check supported audio encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Check supported audio encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_foreach_supported_audio_encoder_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_foreach_supported_audio_encoder(recorder, _audio_encoder_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_foreach_supported_audio_encoder_n
 * @since_tizen         2.3
 * @description         To check supported audio encoder with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check microphone supported or not. \n
                        2. Check supported audio encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_media_recorder_foreach_supported_audio_encoder_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_foreach_supported_audio_encoder(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_foreach_supported_file_format_p
 * @since_tizen         2.3
 * @description         To check supported file format with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Check supported file format.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_foreach_supported_file_format_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_foreach_supported_file_format(recorder, _file_format_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_foreach_supported_file_format_n
 * @since_tizen         2.3
 * @description         To check supported file format with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check microphone supported or not. \n
                        2. Check supported file format.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_media_recorder_foreach_supported_file_format_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_foreach_supported_file_format(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_foreach_supported_video_encoder_p
 * @since_tizen         2.3
 * @description         To check supported video encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Check supported video encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_foreach_supported_video_encoder_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_foreach_supported_video_encoder(recorder, _video_encoder_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_foreach_supported_video_encoder_n
 * @since_tizen         2.3
 * @description         To check supported video encoder with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Check supported video encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_media_recorder_foreach_supported_video_encoder_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_foreach_supported_video_encoder(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_foreach_supported_video_resolution_p
 * @since_tizen	        2.3
 * @description         To check supported video resolution with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Check supported video resolution.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_foreach_supported_video_resolution_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_foreach_supported_video_resolution(recorder, _video_resolution_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_foreach_supported_video_resolution_n
 * @since_tizen         2.3
 * @description         To check supported video resolution with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Check supported video resolution.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_media_recorder_foreach_supported_video_resolution_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_foreach_supported_video_resolution(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_recording_limit_reached_cb_p
 * @since_tizen         2.3
 * @description         To check file size, time limited callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set limited callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_recording_limit_reached_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_recording_limit_reached_cb(recorder, _limit_reached_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_recording_limit_reached_cb_n
 * @since_tizen         2.3
 * @description         To check file size, time limited callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check microphone supported or not. \n
                        2. Set limited callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_media_recorder_set_recording_limit_reached_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_recording_limit_reached_cb(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;

}

/**
 * @testcase            utc_media_recorder_set_recording_status_cb_p
 * @since_tizen         2.3
 * @description         To check recording status with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set recording status callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_recording_status_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_recording_status_cb(recorder, _recording_statis_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_recording_status_cb_n
 * @since_tizen         2.3
 * @description         To check recording status with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check microphone supported or not. \n
                        2. Set recording status callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_media_recorder_set_recording_status_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_recording_status_cb(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_state_changed_cb_p
 * @since_tizen         2.3
 * @description         To check state changed callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set changed callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_state_changed_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_state_changed_cb(recorder, _state_changed_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_state_changed_cb_n
 * @since_tizen         2.3
 * @description         To check state changed callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check microphone supported or not. \n
                        2. Set state changed callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_media_recorder_set_state_changed_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_state_changed_cb(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_interrupted_cb_p
 * @since_tizen         2.3
 * @description         To check interrupted callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set interrupted callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_interrupted_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_interrupted_cb(recorder, _interrupted_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_interrupted_cb_n
 * @since_tizen         2.3
 * @description         To check interrupted callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check microphone supported or not. \n
                        2. Set interrupted callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_media_recorder_set_interrupted_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_interrupted_cb(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_audio_stream_cb_p
 * @since_tizen         2.3
 * @description         To check audio stream callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set audio stream callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_audio_stream_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_audio_stream_cb(recorder, _audio_stream_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_audio_stream_cb_n
 * @since_tizen         2.3
 * @description         To check audio stream callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check microphone supported or not. \n
                        2. Set audio stream callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_media_recorder_set_audio_stream_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_audio_stream_cb(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_error_cb_p
 * @since_tizen         2.3
 * @description         To check error callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set error callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_error_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_error_cb(recorder, _error_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_error_cb_n
 * @since_tizen         2.3
 * @description         To check error callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check microphone supported or not. \n
                        2. Set error callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_media_recorder_set_error_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_error_cb(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_recording_limit_reached_cb_p
 * @since_tizen         2.3
 * @description         To check to unset recording limit callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Unset recording limit callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_unset_recording_limit_reached_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_recording_limit_reached_cb(recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_recording_limit_reached_cb_n
 * @since_tizen         2.3
 * @description         To check to unset recording limit callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Check microphone supported or not. \n
                        2. Unset recording limit callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_media_recorder_unset_recording_limit_reached_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_recording_limit_reached_cb(NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_recording_status_cb_p
 * @since_tizen         2.3
 * @description         To check to unset recording status callback  with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Unset recording status callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_unset_recording_status_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_recording_status_cb(recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_recording_status_cb_n
 * @since_tizen         2.3
 * @description         To check to unset recording status callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Check microphone supported or not. \n
                        2. Unset recording status callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_media_recorder_unset_recording_status_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_recording_status_cb(NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_state_changed_cb_p
 * @since_tizen         2.3
 * @description         To check to unset state changed callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Unset state changed callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_unset_state_changed_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_state_changed_cb(recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_state_changed_cb_n
 * @since_tizen         2.3
 * @description         To check to unset state changed callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Check microphone supported or not. \n
                        2. Check supported audio encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_media_recorder_unset_state_changed_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_state_changed_cb(NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_interrupted_cb_p
 * @since_tizen         2.3
 * @description         To check to unset interrupted callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Unset interrupted callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_unset_interrupted_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_interrupted_cb(recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_interrupted_cb_n
 * @since_tizen         2.3
 * @description         To check to unset interrupted callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Check microphone supported or not. \n
                        2. Unset interrupted callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_media_recorder_unset_interrupted_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_interrupted_cb(NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_audio_stream_cb_p
 * @since_tizen         2.3
 * @description         To check to unset audio stream callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Unset audio stream callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_unset_audio_stream_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_audio_stream_cb(recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_audio_stream_cb_n
 * @since_tizen         2.3
 * @description         To check to unset audio stream callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Check microphone supported or not. \n
                        2. Unset audio stream callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle null.
 */
int utc_media_recorder_unset_audio_stream_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_audio_stream_cb(NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_error_cb_p
 * @since_tizen         2.3
 * @description         To check to unset error callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Unset error callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_unset_error_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_error_cb(recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_error_cb_n
 * @since_tizen         2.3
 * @description         To check to unset error callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Check microphone supported or not. \n
                        2. Unset error callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle null.
 */
int utc_media_recorder_unset_error_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_error_cb(NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_add_device_state_changed_cb_p
 * @since_tizen         3.0
 * @description         To check adding device state changed callback with valid parameters.
 * @scenario            This test is for checking device state changed callback adding with valid parameters.
                        1. Add device state changed callback with valid parameters. \n
                        2. Check microphone device which is supported or not. \n
                        3-1. If supported, compare "ret" value with RECORDER_ERROR_NONE. \n
                        3-1. If not supported, compare "ret" value with RECORDER_ERROR_NOT_SUPPORTED. \n
                        4. Remove added callback if cb_id is valid.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_add_device_state_changed_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	int check_ret = RECORDER_ERROR_NONE;
	int cb_id = 0;

	ret = recorder_add_device_state_changed_cb(_device_state_changed_cb, NULL, &cb_id);

	if (audio_recording_supported)
		check_ret = RECORDER_ERROR_NONE;
	else
		check_ret = RECORDER_ERROR_NOT_SUPPORTED;

	if (cb_id > 0)
		recorder_remove_device_state_changed_cb(cb_id);

	assert_eq(ret, check_ret);

	return 0;
}


/**
 * @testcase            utc_media_recorder_add_device_state_changed_cb_n1
 * @since_tizen         3.0
 * @description         To check adding device state changed callback with invalid parameters.
 * @scenario            This test is for checking device state changed callback adding with invalid parameters.
                        1. Add device state changed callback with invalid parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the first parameter is null.
 */
int utc_media_recorder_add_device_state_changed_cb_n1(void)
{
	int ret = RECORDER_ERROR_NONE;
	int cb_id = 0;

	ret = recorder_add_device_state_changed_cb(NULL, NULL, &cb_id);

	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_add_device_state_changed_cb_n2
 * @since_tizen         3.0
 * @description         To check adding device state changed callback with invalid parameters.
 * @scenario            This test is for checking device state changed callback adding with invalid parameters.
                        1. Add device state changed callback with invalid parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the third parameter is null.
 */
int utc_media_recorder_add_device_state_changed_cb_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	ret = recorder_add_device_state_changed_cb(_device_state_changed_cb, NULL, NULL);

	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_remove_device_state_changed_cb_p
 * @since_tizen         3.0
 * @description         To check removing device state changed callback with valid parameter.
 * @scenario            This test is for checking device state changed callback removing with valid parameter.
                        1. Add device state changed callback with valid parameters. \n
                        2. Check microphone device which is supported or not. \n
                        3-1. If supported, remove device state changed callback with cb_id from recorder_add_device_state_changed_cb(). \n
                        3-1. If not supported, compare "ret" value with RECORDER_ERROR_NOT_SUPPORTED.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success if microphone device is supported.
 */
int utc_media_recorder_remove_device_state_changed_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	int cb_id = 0;

	ret = recorder_add_device_state_changed_cb(_device_state_changed_cb, NULL, &cb_id);

	if (audio_recording_supported) {
		assert_eq(ret, RECORDER_ERROR_NONE);
		assert_neq(cb_id, 0);

		ret = recorder_remove_device_state_changed_cb(cb_id);

		assert_eq(ret, RECORDER_ERROR_NONE);
	} else {
		assert_eq(ret, RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase            utc_media_recorder_remove_device_state_changed_cb_n1
 * @since_tizen         3.0
 * @description         To check removing device state changed callback with invalid condition.
 * @scenario            This test is for checking device state changed callback removing with invalid condition.
                        1. Remove device state changed callback without adding device state changed callback. \n
                        2. Check microphone device which is supported or not. \n
                        3-1. If supported, compare "ret" value with RECORDER_ERROR_INVALID_OPERATION. \n
                        3-2. If not supported, compare "ret" value with RECORDER_ERROR_NOT_SUPPORTED.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the first parameter is null.
 */
int utc_media_recorder_remove_device_state_changed_cb_n1(void)
{
	int ret = RECORDER_ERROR_NONE;
	int check_ret = RECORDER_ERROR_NONE;

	ret = recorder_remove_device_state_changed_cb(0);

	if (audio_recording_supported)
		check_ret = RECORDER_ERROR_INVALID_OPERATION;
	else
		check_ret = RECORDER_ERROR_NOT_SUPPORTED;

	assert_eq(ret, check_ret);

	return 0;
}


/**
 * @testcase            utc_media_recorder_remove_device_state_changed_cb_n2
 * @since_tizen         3.0
 * @description         To check removing device state changed callback with valid parameter.
 * @scenario            This test is for checking device state changed callback removing with invalid parameter.
                        1. Remove device state changed callback with invalid parameter. \n
                        2. Check microphone device which is supported or not. \n
                        3-1. If supported, remove device state changed callback with invalid cb_id. \n
                        3-2. If not supported, compare "ret" value with RECORDER_ERROR_NOT_SUPPORTED.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the first parameter is null.
 */
int utc_media_recorder_remove_device_state_changed_cb_n2(void)
{
	int ret = RECORDER_ERROR_NONE;
	int cb_id = 0;

	ret = recorder_add_device_state_changed_cb(_device_state_changed_cb, NULL, &cb_id);

	if (audio_recording_supported) {
		assert_eq(ret, RECORDER_ERROR_NONE);
		assert_neq(cb_id, 0);

		ret = recorder_remove_device_state_changed_cb(cb_id + 100);

		recorder_remove_device_state_changed_cb(cb_id);

		assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase            utc_media_recorder_set_muxed_stream_cb_p
 * @since_tizen         4.0
 * @description         To check muxed stream callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set muxed stream callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_muxed_stream_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_muxed_stream_cb(recorder, _muxed_stream_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_muxed_stream_cb_n
 * @since_tizen         4.0
 * @description         To check muxed stream callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check microphone supported or not. \n
                        2. Set muxed stream callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_media_recorder_set_muxed_stream_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_muxed_stream_cb(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_unset_muxed_stream_cb_p
 * @since_tizen         4.0
 * @description         To check to unset muxed stream callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Unset muxed stream callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_unset_muxed_stream_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_muxed_stream_cb(recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}


/**
 * @testcase            utc_media_recorder_unset_muxed_stream_cb_n
 * @since_tizen         4.0
 * @description         To check to unset muxed stream callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Check microphone supported or not. \n
                        2. Unset muxed stream callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle null.
 */
int utc_media_recorder_unset_muxed_stream_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_muxed_stream_cb(NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_set_video_encode_decision_cb_p
 * @since_tizen         6.0
 * @description         To check video encode decision callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set video encode decision callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_video_encode_decision_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_video_encode_decision_cb(recorder, _video_encode_decision_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}


/**
 * @testcase            utc_media_recorder_set_video_encode_decision_cb_n
 * @since_tizen         6.0
 * @description         To check video encode decision callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check microphone supported or not. \n
                        2. Set video encode decision callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_media_recorder_set_video_encode_decision_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_video_encode_decision_cb(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_unset_video_encode_decision_cb_p
 * @since_tizen         6.0
 * @description         To check to unset video encode decision callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Unset video encode decision callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_unset_video_encode_decision_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_video_encode_decision_cb(recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}


/**
 * @testcase            utc_media_recorder_unset_video_encode_decision_cb_n
 * @since_tizen         6.0
 * @description         To check to unset video encode decision callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Check microphone supported or not. \n
                        2. Unset video encode decision callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle null.
 */
int utc_media_recorder_unset_video_encode_decision_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_video_encode_decision_cb(NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_set_interrupt_started_cb_p
 * @since_tizen         4.0
 * @description         To check interrupt started callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set interrupt started callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_interrupt_started_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_interrupt_started_cb(recorder, _interrupt_started_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_interrupt_started_cb_n1
 * @since_tizen         4.0
 * @description         To check interrupt started callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check microphone supported or not. \n
                        2. Set invalid pointer in second parameter which is null pointer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_media_recorder_set_interrupt_started_cb_n1(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_interrupt_started_cb(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_interrupt_started_cb_n2
 * @since_tizen         4.0
 * @description         To check interrupt started callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Set invalid pointer which is recorder handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the recorder handle is null.
 */
int utc_media_recorder_set_interrupt_started_cb_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_interrupt_started_cb(NULL, _interrupt_started_cb, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_interrupt_started_cb_p
 * @since_tizen         4.0
 * @description         To check to unset interrupt started callback with valid parameter.
 * @scenario            This test is for checking parameter valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Unset interrupt started callback.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_unset_interrupt_started_cb_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_interrupt_started_cb(recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_unset_interrupt_started_cb_n
 * @since_tizen         4.0
 * @description         To check to unset interrupt started callback with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Check microphone supported or not. \n
                        2. Set invalid pointer which is recorder handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_media_recorder_unset_interrupt_started_cb_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_unset_interrupt_started_cb(NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}
