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
#include <storage.h>
#include <system_info.h>

static char* media=".test_record.mp4";
static char* media_path=NULL;

static streamrecorder_h recorder = NULL;
static int startup_ret;
static bool is_streamrecorder_supported = false;

static bool storage_device_cb(int storage_id, storage_type_e type, storage_state_e state, const char* path, void* user_data)
{
    int size_of_path = 0;

    if (type == STORAGE_TYPE_INTERNAL) {
        size_of_path = strlen(path)+strlen(media)+6;
        media_path = (char*)malloc(size_of_path);
        if (media_path != NULL) {
            snprintf(media_path, size_of_path, "%s/%s",path,media);
        }
        return false;
    }
    return true;
}

/**
 * @function            utc_streamrecorder_startup
 * @description         Called before each test. \n
                        This is the precondition for checking apis. \n
                        Tiis precondition is create streamrecorder and set video source as buffer
 * @scenario            1. Check device storage supported. \n
                        2. Create streamrecorder. \n
                        3. Set videosource.
 * @parameter           N/A
 * @return              N/A
 */
void utc_streamrecorder_startup(void)
{
    system_info_get_platform_bool("http://tizen.org/feature/multimedia.stream_recorder", &is_streamrecorder_supported);

    startup_ret = STREAMRECORDER_ERROR_NONE;
    storage_foreach_device_supported(storage_device_cb,NULL);

    startup_ret = streamrecorder_create(&recorder);
    startup_ret |= streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
}

/**
 * @function            utc_streamrecorder_cleanup
 * @description         Called after each test. \n
                        This is the postcondition for checking apis. \n
                        This postcondition is streamrecorder_destroy for cleaning up all recorder resources for next test.
 * @scenario            1. Destroy recorder.
 * @parameter           N/A
 * @return              N/A
 */
void utc_streamrecorder_cleanup(void)
{
	if (recorder) {
		streamrecorder_destroy(recorder);
		recorder = NULL;
	}
	if (media_path) {
		free(media_path);
		media_path = NULL;
	}
}

/**
 * @testcase            utc_streamrecorder_get_audio_channel_p
 * @description         To check audio channel count with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1.Set audiosource as buffer. \n
                        2.Get audio channel.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_audio_channel_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    int channel = 0;
    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_audio_channel(recorder, &channel);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_audio_channel_n1
 * @description         To check audio channel count with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Get audio channel.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_streamrecorder_get_audio_channel_n1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_audio_channel(recorder, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_audio_channel_n2
 * @description         To check audio channel count with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Get audio channel.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_get_audio_channel_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_audio_channel (NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase            utc_streamrecorder_get_audio_encoder_bitrate_p
 * @description         To check audio encoder bitrate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set audiosource as buffer. \n
                        2. Get audio encoder bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_audio_encoder_bitrate_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    int bitrate = 0;

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_audio_encoder_bitrate(recorder, &bitrate);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_audio_encoder_bitrate_n1
 * @description         To check audio encoder bitrate with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. set audiosource as buffer
                        2. Get audio encoder bitrate. \n
                        3. Check return type
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_streamrecorder_get_audio_encoder_bitrate_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_audio_encoder_bitrate(recorder, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

   return 0;
}

/**
 * @testcase            utc_streamrecorder_get_audio_encoder_bitrate_n2
 * @description         To check audio encoder bitrate with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Get audio encoder bitrate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_get_audio_encoder_bitrate_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_audio_encoder_bitrate(NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_audio_samplerate_p
 * @description         To check audio sample-rate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. set audiosource as buffer
                        2. Get audio sample-rate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_audio_samplerate_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;
    int samplerate;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_audio_samplerate(recorder, &samplerate);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_attr_get_audio_samplerate_n1
 * @description         To check audio sample-rate with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. set audiosource as buffer \n
                        2. Get audio sample-rate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_streamrecorder_get_audio_samplerate_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_audio_samplerate(recorder, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_audio_samplerate_n2
 * @description         To check audio sample-rate with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. set audiosource as buffer \n
                        2. Get audio sample-rate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_get_audio_samplerate_n2(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_AUDIO);

    ret = streamrecorder_get_audio_samplerate(NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase            utc_streamrecorder_get_recording_limit_p
 * @description         To check recording recording limitation with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Get recording file size limitation. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_recording_limitation_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    int value = 0;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_recording_limit(recorder, STREAMRECORDER_RECORDING_LIMIT_TYPE_SIZE, &value);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_get_recording_limit(recorder, STREAMRECORDER_RECORDING_LIMIT_TYPE_TIME, &value);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_recording_limit_n1
 * @description         To check recording limitation with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Get recording file size limitation. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_streamrecorder_get_recording_limit_n1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_recording_limit(recorder, STREAMRECORDER_RECORDING_LIMIT_TYPE_SIZE, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    ret = streamrecorder_get_recording_limit(recorder, STREAMRECORDER_RECORDING_LIMIT_TYPE_TIME, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_recording_limit_n2
 * @description         To check recording file size limitation  with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Get recording  limitation. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_get_recording_limit_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_recording_limit(NULL, STREAMRECORDER_RECORDING_LIMIT_TYPE_SIZE, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    ret = streamrecorder_get_recording_limit(NULL, STREAMRECORDER_RECORDING_LIMIT_TYPE_TIME, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_framerate_p
 * @description         To check gettting video framerate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Get video frmaerate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_video_framerate_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;
    int value = 0;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_framerate(recorder, &value);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_framerate_n1
 * @description         To check video frmaerate with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        Get video  framerate \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_streamrecorder_get_video_framerate_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_framerate(recorder, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_framerate_n2
 * @description         To check video frmaerate with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Get video frmaerate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_get_video_frmaerate_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_framerate(NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_source_format_p
 * @description         To check video source format with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Get video source format. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_video_source_format_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_video_source_format_e value;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_source_format(recorder, &value);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_source_format_n1
 * @description         To check video source format with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        Get video source format. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_streamrecorder_get_video_source_format_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_source_format(recorder, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_source_format_n2
 * @description         To check video source format with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Get video source format. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_get_video_source_format_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_source_format(NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_encoder_bitrate_p
 * @description         To check video encoder bitrate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Get video encoder bitrate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_video_encoder_bitrate_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;
    int value = 0;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_encoder_bitrate(recorder, &value);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_encoder_bitrate_n1
 * @description         To check video encoder bitrate with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        Get video encoder bitrate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_streamrecorder_get_video_encoder_bitrate_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_encoder_bitrate(recorder, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_encoder_bitrate_n2
 * @description         To check video encoder bitrate with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Get video encoder bitrate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_get_video_encoder_bitrate_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_encoder_bitrate(NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase		utc_streamrecorder_set_audio_channel_p
 * @description         To set audio channel count with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. set audiosource as buffer
                        2. Set audio channel count. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_audio_channel_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_audio_channel(recorder, 1);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_audio_channel_n3
 * @description         To check audio channel count with invalid value.
 * @scenario            This test is for checking invalid value such as 0 channel. \n
                        1.set audiosource as buffer \n
                        2.Set audio channel \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.

 */
int utc_streamrecorder_set_audio_channel_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_set_audio_channel(recorder, -1);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_streamrecorder_set_audio_channel_n2
 * @description         To check audio channel count with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1.set audiosource as buffer. \n
                        2.Set audio channel. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.

 */
int utc_streamrecorder_set_audio_channel_n2(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_set_audio_channel(NULL, 10);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_audio_encoder_bitrate_p
 * @description         To check audio encoder bitrate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. set audiosource as buffer. \n
                        2. Set audio encoder bitrate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_audio_encoder_bitrate_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_set_audio_encoder_bitrate(recorder, 11111);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_audio_encoder_bitrate_n
 * @description         To check audio encoder bitrate with invalid paramter.
 * @scenario            This test is for checking invalid value which is out of range. \n
                        1. set audiosource as buffer \n
                        2. Set audio encoder bitrate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_streamrecorder_set_audio_encoder_bitrate_n(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_set_audio_encoder_bitrate(recorder, -1);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_audio_samplerate_p
 * @description         To check audio sample-rate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        Get audio sample-rate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_audio_samplerate_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_audio_samplerate(recorder, 11111);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_audio_samplerate_n
 * @description         To check audio sample-rate with invalid value.
 * @scenario            This test is for checking invalid value which is out of range. \n
                        1. set audiosource as buffer. \n
                        1. Set audio sample-rate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.

 */
int utc_streamrecorder_set_audio_samplerate_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_set_audio_samplerate(recorder, -1);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_recording_limit_p
 * @description         To check file size limitation with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Get recording limitation. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_recording_limit_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_recording_limit(recorder, STREAMRECORDER_RECORDING_LIMIT_TYPE_SIZE, 1000);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_recording_limit(recorder, STREAMRECORDER_RECORDING_LIMIT_TYPE_TIME, 120);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_recording_limit_n1
 * @description         To check file size limitation with invalid parameter.
 * @scenario            This test is for checking invalid value which is out of range. \n
                        1. Get recording limitation. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.

 */
int utc_streamrecorder_set_recording_limit_n1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_recording_limit(recorder, STREAMRECORDER_RECORDING_LIMIT_TYPE_SIZE, -1);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    ret = streamrecorder_set_recording_limit(recorder, STREAMRECORDER_RECORDING_LIMIT_TYPE_TIME, -1);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_recording_limit_n2
 * @description         To check file size limitation with invalid handle.
 * @scenario            This test is for checking invalid parameter such as reorder handle "null". \n
                        1. set recording limit \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_set_recording_limit_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_recording_limit(NULL, STREAMRECORDER_RECORDING_LIMIT_TYPE_SIZE, 1000);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    ret = streamrecorder_set_recording_limit(NULL, STREAMRECORDER_RECORDING_LIMIT_TYPE_TIME, 120);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_video_encoder_bitrate_p
 * @description         To check video encoder bitrate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set video encoder bitrate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_video_encoder_bitrate_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_video_encoder_bitrate(recorder, 0);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_recorder_set_video_encoder_bitrate_n1
 * @description         To check video encoder bitrate with invalid parameter.
 * @scenario            This test is for checking invalid pointer which is out of range. \n
                        1. Set video encoder bitrate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_streamrecorder_set_video_encoder_bitrate_n1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_video_encoder_bitrate(recorder, -1);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_video_encoder_bitrate_n2
 * @description         To check video encoder bitrate with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Set video encoder bitrate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_set_video_encoder_bitrate_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_video_encoder_bitrate(NULL, -1);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_audio_encoder_p
 * @description         To check audio encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Get audio encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_audio_encoder_p1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    streamrecorder_audio_codec_e value;

    ret = streamrecorder_enable_source_buffer(recorder,STREAMRECORDER_SOURCE_AUDIO);
    ret |= streamrecorder_get_audio_encoder(recorder, &value);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_audio_encoder_p2
 * @description         To check audio encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set audio encoder AMR. \n
                        2. Get audio encoder. \n
                        3. Set audio encoder AAC. \n
                        4. Get audio encoder. \n
                        5. Set audio encoder VORBIS. \n
                        6. Get audio encoder. \n
                        7. Set audio encoder PCM. \n
                        8. Get audio encoder. \n
                        9. Set audio encoder DISABLE. \n
                        10. Get audio encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_audio_encoder_p2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_audio_codec_e codec = STREAMRECORDER_AUDIO_CODEC_AMR;
    streamrecorder_audio_codec_e ret_codec = STREAMRECORDER_AUDIO_CODEC_AMR;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_enable_source_buffer(recorder,STREAMRECORDER_SOURCE_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    codec = STREAMRECORDER_AUDIO_CODEC_AMR;
    ret = streamrecorder_set_audio_encoder(recorder, codec);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_audio_encoder(recorder, &ret_codec);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    assert_eq(ret_codec, codec);

    codec = STREAMRECORDER_AUDIO_CODEC_AAC;
    ret = streamrecorder_set_audio_encoder(recorder, codec);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_audio_encoder(recorder, &ret_codec);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    assert_eq(ret_codec, codec);

    codec = STREAMRECORDER_AUDIO_CODEC_PCM;
    ret = streamrecorder_set_audio_encoder(recorder, codec);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_audio_encoder(recorder, &ret_codec);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    assert_eq(ret_codec, codec);

    return 0;
}


/**
 * @testcase		    utc_streamrecorder_get_audio_encoder_n1
 * @description         To check audio encoder with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Get audio encoder. \n
                        2. Check return type.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_streamrecorder_get_audio_encoder_n1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_audio_encoder(recorder, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_audio_encoder_n2
 * @description         To check audio encoder with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Set audio encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_get_audio_encoder_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_audio_encoder(NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase            utc_streamrecorder_get_file_format_p
 * @description         To check file format with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Get file format. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_file_format_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    streamrecorder_file_format_e value;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_file_format(recorder, &value);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_file_format_n
 * @description         To check file format with invalid handle.
 * @scenario            This test is for checking invalid pointer. \n
                        1. Get file format. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if this api is getting function.
 */
int utc_streamrecorder_get_file_format_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_file_format(recorder, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_recorder_get_video_encoder_p1
 * @description         To check video encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Get video encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_video_encoder_p1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_video_codec_e value;
    streamrecorder_video_codec_e codec = STREAMRECORDER_VIDEO_CODEC_H263;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret |= streamrecorder_set_video_encoder(recorder, codec);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_video_encoder(recorder, &value);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    assert_eq(codec, value);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_encoder_p2
 * @description         To check video encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set video encoder H263. \n
                        2. Get video encoder. \n
                        3. Set video encoder MPEG4. \n
                        4. Get video encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.

 */
int utc_streamrecorder_get_video_encoder_p2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_video_codec_e codec = STREAMRECORDER_VIDEO_CODEC_H263;
    streamrecorder_video_codec_e ret_codec = STREAMRECORDER_VIDEO_CODEC_H263;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    codec = STREAMRECORDER_VIDEO_CODEC_H263;
    ret = streamrecorder_set_video_encoder(recorder, codec);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_video_encoder(recorder, &ret_codec);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    assert_eq(ret_codec, codec);

    codec = STREAMRECORDER_VIDEO_CODEC_MPEG4;
    ret = streamrecorder_set_video_encoder(recorder, codec);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_video_encoder(recorder, &ret_codec);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    assert_eq(ret_codec, codec);

    return 0;
}


/**
 * @testcase            utc_streamrecorder_get_video_encoder_n1
 * @description         To check video encoder with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Get video encoder. \n
                        2. check return type.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_streamrecorder_get_video_encoder_n1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_encoder(recorder, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_encoder_n2
 * @description         To check video encoder count with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Get video encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_get_video_encoder_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_encoder(NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_resolution_p
 * @description         To check video resolution with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Get video resolution. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_video_resolution_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;
    int mHeight = 0;
    int mWidth = 0;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_resolution(recorder, &mWidth, &mHeight);

    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_resolution_n1
 * @description         To check video resolution with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Get video resolution. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_streamrecorder_get_video_resolution_n1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_resolution(recorder, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_video_resolution_n2
 * @description         To check video resolution with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Get video resolution. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_get_video_resolution_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_video_resolution(NULL, NULL, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase            utc_streamrecorder_set_audio_encoder_p
 * @description         To check audio encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set audio encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_audio_encoder_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_audio_codec_e codec = STREAMRECORDER_AUDIO_CODEC_AMR;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_audio_encoder(recorder, codec);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_audio_encoder_n1
 * @description         To check audio encoder with invalid parameter.
 * @scenario            This test is for checking invalid value which is out of range. \n
                        1. Set audio encoder. \n
                        2. Check return type.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_streamrecorder_set_audio_encoder_n1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_audio_codec_e codec = -2;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_audio_encoder(recorder, codec);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;

}

/**
 * @testcase            utc_streamrecorder_set_audio_encoder_n2
 * @description         To check audio encoder with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Set audio encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_set_audio_encoder_n2(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_audio_codec_e codec = -2;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_audio_encoder(NULL, codec);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_file_format_p1
 * @description         To check file format with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set file format. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_file_format_p1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_file_format_e format = STREAMRECORDER_FILE_FORMAT_3GP;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_file_format(recorder, format);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_streamrecorder_get_file_format_p2
 * @description         To check file fomrat with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set file format 3GP. \n
                        2. Get file format. \n
                        3. Set file format MP4. \n
                        4. Get file format. \n
                        5. Set file format AMR. \n
                        6. Get file format. \n
                        7. Set file format WAV. \n
                        8. Get file format. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_file_format_p2(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_file_format_e format;
    streamrecorder_file_format_e ret_format;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    format = STREAMRECORDER_FILE_FORMAT_3GP;
    ret = streamrecorder_set_file_format(recorder, format);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_file_format(recorder,&ret_format);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    assert_eq(ret_format, format);

    format = STREAMRECORDER_FILE_FORMAT_MP4;
    ret = streamrecorder_set_file_format(recorder, format);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_file_format(recorder,&ret_format);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    assert_eq(ret_format, format);

    format = STREAMRECORDER_FILE_FORMAT_AMR;
    ret = streamrecorder_set_file_format(recorder, format);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_file_format(recorder,&ret_format);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    assert_eq(ret_format, format);

    format = STREAMRECORDER_FILE_FORMAT_WAV;
    ret = streamrecorder_set_file_format(recorder, format);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_get_file_format(recorder,&ret_format);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    assert_eq(ret_format, format);

    return 0;
}


/**
 * @testcase            utc_streamrecorder_set_file_format_n
 * @description         To check set file format with invalid parameter.
 * @scenario            This test is for checking invalid value which is out of range \n
                        1. Set file format. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_streamrecorder_set_file_format_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_file_format_e format = -1;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_file_format(recorder, format);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_filename_p
 * @description         To check file name with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Get file name. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_filename_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_filename(recorder, "/mnt/nfs/test.test");
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_filename_n
 * @description         To check file name with invalid handle.
 * @scenario            This test is for checking invalid pointer. \n
                        1. Set file name. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null even if this api is getting function.
 */
int utc_streamrecorder_set_filename_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_filename(recorder, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_video_encoder_p
 * @description         To check video encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set video encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_video_encoder_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_video_codec_e codec = STREAMRECORDER_VIDEO_CODEC_MPEG4;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_video_encoder(recorder, codec);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_video_encoder_n1
 * @description         To check video encoder with invalid parameter.
 * @scenario            This test is for checking invalid pointer which is out of range. \n
                        1. Set video encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_streamrecorder_set_video_encoder_n1(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_video_codec_e codec = -1;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_video_encoder(recorder, codec);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_video_encoder_n2
 * @description         To check video encoder with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Set video encoder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_set_video_encoder_n2(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_video_codec_e codec = -1;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_video_encoder(NULL, codec);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase		utc_recorder_set_video_resolution_p
 * @description         To check video resolution with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        set video resolution
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_video_resolution_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    int width = 1280;
    int height = 720;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_video_resolution(recorder, width, height);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    return 0;
}

/**
 * @testcase            utc_recorder_set_video_resolution_n1
 * @description         To check video resolution with invalid parameter.
 * @scenario            This test is for checking invalid value which is out of range. \n
                        1. Get video resolution. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_streamrecorder_set_video_resolution_n1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_video_resolution(recorder, 0, 0);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_video_resolution_n2
 * @description         To check video resolution with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Set video resolution. \n
                        2. check return value
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_streamrecorder_set_video_resolution_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_video_resolution(NULL, 1280, 720);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase            utc_streamrecorder_get_filename_p
 * @description         To check file name with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set file name. \n
                        2. Get file name. \n
                        3. Free file name . \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_get_filename_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    char* f_name = NULL;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_filename(recorder, "/mnt/nfs/test.test");
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_get_filename(recorder,&f_name);
    assert_eq(strncmp(f_name,"/mnt/nfs/test.test",strlen(f_name)),0);

    if (f_name) {
        free(f_name);
        f_name = NULL;
    }

    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_filename_n
 * @description         To check file name with invalid handle.
 * @scenario            This test is for checking invalid pointer which is null. \n
                        1. Get filename. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null even if this api is getting function.
 */
int utc_streamrecorder_get_filename_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_get_filename(recorder,NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_video_source_format_p
 * @description         To check to set valid handle and value.
 * @scenario            This test is for checking valid pointer. \n
                        1. Set video source format with valid parameters. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_video_source_format_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_video_source_format_e format = STREAMRECORDER_VIDEO_SOURCE_FORMAT_NV12;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_video_source_format(recorder,format);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    return 0;
}


/**
 * @testcase            utc_streamrecorder_set_video_source_format_n
 * @description         To check to set valid handle and value.
 * @scenario            This test is for checking valid pointer. \n
                        1. Set video source format with invalid parameters. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_video_source_format_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    streamrecorder_video_source_format_e format = STREAMRECORDER_VIDEO_SOURCE_FORMAT_NV12;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_video_source_format(NULL,format);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_video_framerate_p
 * @description         To check gettting video framerate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Set video frmaerate. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_video_framerate_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;
    int value = 20;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_video_framerate(recorder, value);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_video_framerate_n
 * @description         To check video frmaerate with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        Set video  framerate \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_streamrecorder_set_video_framerate_n(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;
    int framerate = 30;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = streamrecorder_set_video_framerate(NULL, framerate);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

