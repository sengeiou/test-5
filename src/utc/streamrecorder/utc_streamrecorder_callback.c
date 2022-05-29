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
#include <media/streamrecorder.h>
#include <media_packet.h>
#include <system_info.h>

static streamrecorder_h recorder = NULL;
static int startup_ret;
static bool is_streamrecorder_supported = false;

/**
 * @function		utc_streamrecorder_callback_startup
 * @description         Called before each test. \n
                        This is the precondition for checking apis. \n
                        Tiis precondition is create streamrecorder for checking device and privilege error.
 * @scenario            1. Check device storage supported. \n
                        2. Create audio recorder.
 * @parameter           N/A
 * @return              N/A
 */
void utc_streamrecorder_callback_startup(void)
{
    /* start of TC */
    startup_ret = STREAMRECORDER_ERROR_NONE;

    system_info_get_platform_bool("http://tizen.org/feature/multimedia.stream_recorder", &is_streamrecorder_supported);

    startup_ret = streamrecorder_create(&recorder);
    startup_ret |= streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);

}

/**
 * @function		utc_streamrecorder_callback_cleanup
 * @description         Called after each test. \n
                        This is the postcondition for checking apis. \n
                        This postcondition is streamrecorder_destroy for cleaning up all recorder resources for next test.
 * @scenario            1. Destroy recorder.
 * @parameter           N/A
 * @return              N/A
 */
void utc_streamrecorder_callback_cleanup(void)
{
    /* end of TC */
    streamrecorder_destroy(recorder);
    recorder = NULL;
}

static bool _audio_encoder_cb(streamrecorder_audio_codec_e codec , void *user_data){
    return true;
}

static bool _file_format_cb(streamrecorder_file_format_e format , void *user_data){
    return true;
}

static bool _video_encoder_cb(streamrecorder_video_codec_e codec ,  void *user_data){
    return true;
}

static bool _video_resolution_cb(int width, int height, void *user_data){
    return true;
}


static void _consume_completed_cb(void *buffer , void *user_data){
}

static void _limit_reached_cb(streamrecorder_recording_limit_type_e type,  void *user_data){
}

static void _recording_status_cb(unsigned long long elapsed_time, unsigned long long file_size,  void *user_data){
}

static void _notify_cb(streamrecorder_state_e previous , streamrecorder_state_e current , streamrecorder_notify_e notification,  void *user_data){
}

static void _error_cb(streamrecorder_error_e error, streamrecorder_state_e current_state, void *user_data){
}


/**
 * @testcase            utc_streamrecorder_foreach_supported_audio_encoder_p
 * @description         To check supported audio encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check supported audio encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_foreach_supported_audio_encoder_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_foreach_supported_audio_encoder(recorder, _audio_encoder_cb, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_foreach_supported_audio_encoder_n
 * @description         To check supported audio encoder with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check supported audio encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_streamrecorder_foreach_supported_audio_encoder_n(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_foreach_supported_audio_encoder(recorder, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_foreach_supported_file_format_p
 * @description         To check supported file format with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check supported file format. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_foreach_supported_file_format_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_foreach_supported_file_format(recorder, _file_format_cb, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_foreach_supported_file_format_n1
 * @description         To check supported file format with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check supported file format. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_streamrecorder_foreach_supported_file_format_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_foreach_supported_file_format(recorder, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_foreach_supported_file_format_n2
 * @description         To check supported file format with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check supported file format. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_streamrecorder_foreach_supported_file_format_n2(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_foreach_supported_file_format(NULL, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);


    return 0;
}


/**
 * @testcase            utc_streamrecorder_foreach_supported_video_encoder_p
 * @description         To check supported video encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check supported video encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_foreach_supported_video_encoder_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_foreach_supported_video_encoder(recorder, _video_encoder_cb, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_foreach_supported_video_encoder_n1
 * @description         To check supported video encoder with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check supported video encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_streamrecorder_foreach_supported_video_encoder_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_foreach_supported_video_encoder(NULL, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase            utc_streamrecorder_foreach_supported_video_encoder_n2
 * @description         To check supported video encoder with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check supported video encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_streamrecorder_foreach_supported_video_encoder_n2(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_foreach_supported_video_encoder(recorder, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase            utc_streamrecorder_foreach_supported_video_resolution_p
 * @description         To check supported video resolution with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check supported video resolution. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_foreach_supported_video_resolution_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_foreach_supported_video_resolution(recorder, _video_resolution_cb, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_foreach_supported_video_resolution_n
 * @description         To check supported video resolution with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Check supported video resolution. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_streamrecorder_foreach_supported_video_resolution_n(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_foreach_supported_video_resolution(recorder, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase            utc_streamrecorder_set_buffer_consume_completed_cb_p
 * @description         To check callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set limited callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_buffer_consume_completed_cb_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_buffer_consume_completed_cb(recorder, _consume_completed_cb, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_buffer_consume_completed_cb_n1
 * @description         To check callback with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Set consume completed callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_streamrecorder_set_buffer_consume_completed_cb_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_buffer_consume_completed_cb(recorder, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;

}

/**
 * @testcase            utc_streamrecorder_set_buffer_consume_complete_cb_n2
 * @description         To check file size, time limited callback  with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Set limited callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_streamrecorder_set_buffer_consume_completed_cb_n2(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_buffer_consume_completed_cb(NULL, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;

}
/**
 * @testcase            utc_streamrecorder_set_recording_limit_reached_cb_p
 * @description         To check file size, time limited callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set limited callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_recording_limit_reached_cb_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_recording_limit_reached_cb(recorder, _limit_reached_cb, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_recording_limit_reached_cb_n1
 * @description         To check file size, time limited callback with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Set limited callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_streamrecorder_set_recording_limit_reached_cb_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_recording_limit_reached_cb(recorder, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;

}

/**
 * @testcase            utc_streamrecorder_set_recording_limit_reached_cb_n2
 * @description         To check file size, time limited callback  with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Set limited callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_streamrecorder_set_recording_limit_reached_cb_n2(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_recording_limit_reached_cb(NULL, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;

}


/**
 * @testcase            utc_streamrecorder_set_recording_status_cb_p
 * @description         To check recording status with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set recording status callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_recording_status_cb_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_recording_status_cb(recorder, _recording_status_cb, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_recording_status_cb_n1
 * @description         To check recording status with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Set recording status callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_streamrecorder_set_recording_status_cb_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_recording_status_cb(recorder, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_recording_status_cb_n2
 * @description         To check recording status with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Set recording status callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_streamrecorder_set_recording_status_cb_n2(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_recording_status_cb(NULL, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase            utc_streamrecorder_set_notify_cb_p
 * @description         To check state changed callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set notify callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_notify_cb_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_notify_cb(recorder, _notify_cb, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_notify_cb_n1
 * @description         To check state changed callback with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Set notify callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_streamrecorder_set_notify_cb_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_notify_cb(recorder, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_notify_cb_n2
 * @description         To check state changed callback with invliad parameter.
 * @scenario            This test is for checking invalid pointer such recorder handle null. \n
                        1. Set notify callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null. \n
 */
int utc_streamrecorder_set_notify_cb_n2(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_notify_cb(NULL, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase            utc_streamrecorder_set_error_cb_p
 * @description         To check error callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set error callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_error_cb_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_error_cb(recorder, _error_cb, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_error_cb_n1
 * @description         To check error callback with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as null callback. \n
                        1. Set error callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_streamrecorder_set_error_cb_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_error_cb(recorder, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_error_cb_n2
 * @description         To check error callback with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as recoder handle null. \n
                        1. Set error callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_streamrecorder_set_error_cb_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_error_cb(NULL, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase            utc_streamrecorder_unset_recording_limit_reached_cb_p
 * @description         To check to unset recording limit callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Unset recording limit callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_unset_recording_limit_reached_cb_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_unset_recording_limit_reached_cb(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_unset_recording_limit_reached_cb_n
 * @description         To check to unset recording limit callback with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Unset recording limit callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_streamrecorder_unset_recording_limit_reached_cb_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_unset_recording_limit_reached_cb(NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_unset_buffer_consume_completed_cb_p
 * @description         To check callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. unSet buffer consumed callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_unset_buffer_consume_completed_cb_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_unset_buffer_consume_completed_cb(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_unset_buffer_consume_completed_cb_n
 * @description         To check callback with invliad parameter.
 * @scenario            This test is for checking invalid pointer with handle NULL\n
                        1. unSet consume completed callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because paramter is null pointer about callback.
 */
int utc_streamrecorder_unset_buffer_consume_completed_cb_n1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_unset_buffer_consume_completed_cb(NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}
/**
 * @testcase            utc_streamrecorder_unset_recording_status_cb_p
 * @description         To check to unset recording status callback  with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Unset recording status callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_unset_recording_status_cb_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_unset_recording_status_cb(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_unset_recording_status_cb_n
 * @description         To check to unset recording status callback with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Unset recording status callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_streamrecorder_unset_recording_status_cb_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_unset_recording_status_cb(NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_unset_notify_cb_p
 * @description         To check to unset notify callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Unset notify callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_unset_notify_cb_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_unset_notify_cb(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_unset_notify_cb_n
 * @description         To check to unset notify callback with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_streamrecorder_unset_notify_cb_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_unset_notify_cb(NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_unset_error_cb_p
 * @description         To check to unset error callback with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Unset error callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_unset_error_cb_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_unset_error_cb(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_unset_error_cb_n
 * @description         To check to unset error callback with invliad parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null. \n
                        1. Unset error callback. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle null.
 */
int utc_streamrecorder_unset_error_cb_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_unset_error_cb(NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}
