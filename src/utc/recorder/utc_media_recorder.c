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
#include <storage.h>
#include <string.h>
#include <system_info.h>
#include <sound_manager.h>

static char *media = ".test_record.amr";
static char *media_path = NULL;
static bool audio_recording_supported = false;
static recorder_h recorder = NULL;
static int startup_ret = RECORDER_ERROR_NONE;
static bool video_recording_supported = false;
static camera_h camera = NULL;
static int startup_ret_camera = CAMERA_ERROR_NONE;

#define UTC_AUDIO_CODEC_NUM 5
#define UTC_FILE_FORMAT_NUM 7

enum {
	USER_DATA_AUDIO_CODEC,
	USER_DATA_FILE_FORMAT,
	USER_DATA_MAX
};

static bool	audiocodec_fileformat_compatibility_table[UTC_AUDIO_CODEC_NUM][UTC_FILE_FORMAT_NUM] =
{        /* 3GP MP4 AMR ADTS WAV OGG M2TS */
/*AMR*/     {1,  0,  1,  0,   0,  0,  0},
/*AAC*/     {1,  1,  0,  0,   0,  0,  1},
/*VORBIS*/  {0,  0,  0,  0,   0,  1,  0},
/*PCM*/     {0,  0,  0,  0,   1,  0,  0},
/*MP3*/     {0,  1,  0,  0,   0,  0,  1}
};

static bool _audio_encoder_cb(recorder_audio_codec_e codec, void *user_data)
{
	if (user_data != NULL) {
		*((recorder_audio_codec_e *)user_data) = codec;
		return false;
	}

	return true;
}

static bool _file_format_cb(recorder_file_format_e format, void *user_data)
{
	int *l_user_data = NULL;

	if (user_data != NULL) {
		l_user_data = (int *)user_data;
		if (audiocodec_fileformat_compatibility_table[l_user_data[USER_DATA_AUDIO_CODEC]][(int)format]) {
			l_user_data[USER_DATA_FILE_FORMAT] = (int)format;
			return false;
		}
	}

	return true;
}

static int _get_supported_audio_encoder_and_file_format(recorder_h recorder, int *audio_codec, int *file_format)
{
	int ret = RECORDER_ERROR_NONE;
	int l_audio_codec = RECORDER_AUDIO_CODEC_DISABLE;
	int l_file_format = -1;
	int user_data[USER_DATA_MAX];

	if (audio_codec == NULL || file_format == NULL)
		return RECORDER_ERROR_INVALID_PARAMETER;

	memset(user_data, 0, sizeof(int) * USER_DATA_MAX);
	ret = recorder_foreach_supported_audio_encoder(recorder, _audio_encoder_cb, &l_audio_codec);
	assert_eq(ret, RECORDER_ERROR_NONE);

	if ((int)l_audio_codec >= 0 && (int)l_audio_codec < UTC_AUDIO_CODEC_NUM) {
		user_data[USER_DATA_AUDIO_CODEC] = (int)l_audio_codec;
		ret = recorder_foreach_supported_file_format(recorder, _file_format_cb, user_data);
		assert_eq(ret, RECORDER_ERROR_NONE);

		l_file_format = (recorder_file_format_e)user_data[USER_DATA_FILE_FORMAT];
		if ((int)l_file_format >= 0 && (int)l_file_format < UTC_FILE_FORMAT_NUM) {
			*audio_codec = l_audio_codec;
			*file_format = l_file_format;

			return RECORDER_ERROR_NONE;
		}
	}

	return RECORDER_ERROR_NOT_SUPPORTED;
}

static bool _storage_device_cb(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
	int size_of_path = 0;

	if (type == STORAGE_TYPE_INTERNAL) {
		size_of_path = strlen(path) + strlen(media) + 2;
		media_path = (char *)malloc(size_of_path);
		if (media_path != NULL) {
			snprintf(media_path, size_of_path, "%s/%s", path, media);
		}

		return false;
	}

	return true;
}

static void _sound_stream_focus_state_changed_cb(sound_stream_info_h stream_info, sound_stream_focus_mask_e focus_mask, sound_stream_focus_state_e focus_state,
	sound_stream_focus_change_reason_e reason_for_change, int sound_behavior, const char *additional_info, void *user_data)
{
	return;
}

/**
 * @function            utc_media_recorder_startup
 * @description         Called before each test. \n
                        This is the precondition for checking apis. \n
                        Tiis precondition is create_audiorecorder api for checking device and privilege error.
 * @scenario            1. Check device storage supported. \n
                        2. Get platform feature for audio recording and video recording. \n
                        3. Create audio recorder. \n
                        4. Create camera.
 * @parameter           N/A
 * @return              N/A
 */
void utc_media_recorder_startup(void)
{
	storage_foreach_device_supported(_storage_device_cb, NULL);

	system_info_get_platform_bool("http://tizen.org/feature/media.audio_recording", &audio_recording_supported);
	system_info_get_platform_bool("http://tizen.org/feature/media.video_recording", &video_recording_supported);

	startup_ret = recorder_create_audiorecorder(&recorder);
	startup_ret_camera = camera_create(CAMERA_DEVICE_CAMERA0, &camera);

	return;
}

/**
 * @function            utc_media_recorder_cleanup
 * @description         Called after each test. \n
                        This is the postcondition for checking apis. \n
                        This postcondition is recorder_destroy for cleaning up all recorder resources for next test.
 * @scenario            1. Destroy recorder. \n
                        2. Destroy camera.
 * @parameter           N/A
 * @return              N/A
 */
void utc_media_recorder_cleanup(void)
{
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

/**
 * @testcase            utc_media_recorder_attr_get_audio_channel_p
 * @since_tizen         2.3
 * @description         To check audio channel count with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Get audio channel.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_get_audio_channel_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	int channel = 0;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_audio_channel(recorder, &channel);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_audio_channel_n1
 * @since_tizen         2.3
 * @description         To check audio channel count with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Check microphone supported or not. \n
                        2. Get audio channel.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_media_recorder_attr_get_audio_channel_n1(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_audio_channel(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_audio_channel_n2
 * @since_tizen         2.3
 * @description         To check audio channel count with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Get audio channel.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_get_audio_channel_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_audio_channel(NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_attr_get_audio_device_p
 * @since_tizen         2.3
 * @description         To check audio device with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Get audio device.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_get_audio_device_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_audio_device_e device = RECORDER_AUDIO_DEVICE_MIC;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_audio_device(recorder, &device);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_audio_device_n1
 * @since_tizen         2.3
 * @description         To check audio device with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Check microphone supported or not. \n
                        2. Get audio device.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_media_recorder_attr_get_audio_device_n1(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_audio_device(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_audio_device_n2
 * @since_tizen         2.3
 * @description         To check audio device with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Get audio device.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_get_audio_device_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_audio_device(NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_attr_get_audio_encoder_bitrate_p
 * @since_tizen         2.3
 * @description         To check audio encoder bitrate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Get audio encodeer bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_get_audio_encoder_bitrate_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	int bitrate = 0;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_audio_encoder_bitrate(recorder, &bitrate);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_audio_encoder_bitrate_n1
 * @since_tizen         2.3
 * @description         To check audio encoder bitrate with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Check microphone supported or not. \n
                        2. Get audio encoder bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_media_recorder_attr_get_audio_encoder_bitrate_n1(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_audio_encoder_bitrate(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_audio_encoder_bitrate_n2
 * @since_tizen         2.3
 * @description         To check audio encoder bitrate with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Get audio encoder bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_get_audio_encoder_bitrate_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_audio_encoder_bitrate(NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_attr_get_audio_samplerate_p
 * @since_tizen         2.3
 * @description         To check audio sample-rate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Get audio sample-rate.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_get_audio_samplerate_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	int samplerate = 0;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_audio_samplerate(recorder, &samplerate);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_audio_samplerate_n1
 * @since_tizen         2.3
 * @description         To check audio sample-rate with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Check microphone supported or not. \n
                        2. Get audio sample-rate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_media_recorder_attr_get_audio_samplerate_n1(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_audio_samplerate(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_audio_samplerate_n2
 * @since_tizen         2.3
 * @description         To check audio sample-rate with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Get audio sample-rate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_get_audio_samplerate_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_audio_samplerate(NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_attr_get_orientation_tag_p
 * @since_tizen         2.3
 * @description         To check orientation tag with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get orientation tag.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_get_orientation_tag_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_rotation_e rotation_tag = RECORDER_ROTATION_NONE;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_orientation_tag(recorder, &rotation_tag);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_orientation_tag_n1
 * @since_tizen         2.3
 * @description         To check orientation tag with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get orientation tag.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_media_recorder_attr_get_orientation_tag_n1(void)
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

	ret = recorder_attr_get_orientation_tag(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_orientation_tag_n2
 * @since_tizen         2.3
 * @description         To check orientation tag with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get orientation tag.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_get_orientation_tag_n2(void)
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

	ret = recorder_attr_get_orientation_tag(NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_attr_get_recording_motion_rate_p
 * @since_tizen         2.3
 * @description         To check recording motion rate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get recording motion rate.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_get_recording_motion_rate_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	double rate = 0.0;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_recording_motion_rate(recorder, &rate);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_recording_motion_rate_n1
 * @since_tizen         2.3
 * @description         To check recording motion rate count with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get recording motion rate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_media_recorder_attr_get_recording_motion_rate_n1(void)
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

	ret = recorder_attr_get_recording_motion_rate(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_recording_motion_rate_n2
 * @since_tizen         2.3
 * @description         To check recording motion rate count with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get recording motion rate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_get_recording_motion_rate_n2(void)
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

	ret = recorder_attr_get_recording_motion_rate(NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_attr_get_size_limit_p
 * @since_tizen         2.3
 * @description         To check recording file size limitation with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Get recording file size limitation.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_get_size_limit_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	int size = 0;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_size_limit(recorder, &size);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_size_limit_n1
 * @since_tizen         2.3
 * @description         To check recording file size limitation with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Check microphone supported or not. \n
                        2. Get recording file size limitation.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_media_recorder_attr_get_size_limit_n1(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_size_limit(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_size_limit_n2
 * @since_tizen         2.3
 * @description         To check recording file size limitation  with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Get recording file size limitation.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_get_size_limit_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_size_limit(NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_attr_get_time_limit_p
 * @since_tizen         2.3
 * @description         To check recording time limitation with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Get recording time limitation.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_get_time_limit_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	int value = 0;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_time_limit(recorder, &value);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_time_limit_n1
 * @since_tizen         2.3
 * @description         To check recording time limitation with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Check microphone supported or not. \n
                        2. Get recording time limitation.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_media_recorder_attr_get_time_limit_n1(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_time_limit(recorder, NULL);
	assert_neq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_time_limit_n2
 * @since_tizen         2.3
 * @description         To check recording time limitation with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Get recording time limitation.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_get_time_limit_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_time_limit(NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_attr_get_video_encoder_bitrate_p
 * @since_tizen         2.3
 * @description         To check video encoder bitrate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get video encoder bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_get_video_encoder_bitrate_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	int value = 0;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_get_video_encoder_bitrate(recorder, &value);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_video_encoder_bitrate_n1
 * @since_tizen         2.3
 * @description         To check video encoder bitrate with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get video encoder bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_media_recorder_attr_get_video_encoder_bitrate_n1(void)
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

	ret = recorder_attr_get_video_encoder_bitrate(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_get_video_encoder_bitrate_n2
 * @since_tizen         2.3
 * @description         To check video encoder bitrate with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get video encoder bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_get_video_encoder_bitrate_n2(void)
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

	ret = recorder_attr_get_video_encoder_bitrate(NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_is_muted_p
 * @since_tizen         2.3
 * @description         To check sound mute or not with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Check supported audio encoder and file format. \n
                        3. Set supported audio encoder. \n
                        4. Set supported file format. \n
                        5. Set file name with path. \n
                        6. Prepare recorder. \n
                        7. Start recorder. \n
                        8. Set mute. \n
                        9. Check muted or not. \n
                        10. Set unmute. \n
                        11. Cancel recorder. \n
                        12. Unprepare recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_is_muted_p(void)
{
	int ret=RECORDER_ERROR_NONE;
	int audio_codec = RECORDER_AUDIO_CODEC_DISABLE;
	int file_format = -1;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _get_supported_audio_encoder_and_file_format(recorder, &audio_codec, &file_format);
	assert_eq(ret, RECORDER_ERROR_NONE);

	if (audio_codec < 0 || file_format < 0) {
		fprintf(stderr, "Audio codec(or file format) is not supported.\n");
		return 1;
	}

	ret = recorder_set_audio_encoder(recorder, audio_codec);
	ret |= recorder_set_file_format(recorder, file_format);
	ret |= recorder_set_filename(recorder, media_path);
	ret |= recorder_prepare(recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	ret = recorder_start(recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	ret = recorder_attr_set_mute(recorder, true);
	assert_eq(ret, RECORDER_ERROR_NONE);

	ret = recorder_attr_is_muted(recorder);
	assert_eq(ret, true);

	ret = recorder_attr_set_mute(recorder, false);
	assert_eq(ret, RECORDER_ERROR_NONE);

	recorder_cancel(recorder);
	recorder_unprepare(recorder);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_is_muted_n
 * @since_tizen         2.3
 * @description         To check sound muted or not with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Get sound which is muted or not.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_is_muted_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_is_muted(NULL);
	assert_eq(ret, false);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_audio_channel_p
 * @since_tizen         2.3
 * @description         To set audio channel count with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set audio channel count.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_set_audio_channel_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_audio_channel(recorder, 1);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_audio_channel_n1
 * @since_tizen         2.3
 * @description         To check with invalid parameter.
 * @scenario            This test is for checking invalid value. \n
                        1. Check microphone supported or not. \n
                        2. Set audio channel count.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_media_recorder_attr_set_audio_channel_n1(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_audio_channel(recorder, 10);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_audio_channel_n2
 * @since_tizen         2.3
 * @description         To check audio channel count with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Set audio channel.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_set_audio_channel_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_audio_channel(NULL, 10);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_audio_device_p
 * @since_tizen         2.3
 * @description         To check audio device with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set audio device.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_set_audio_device_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_audio_device_e device = RECORDER_AUDIO_DEVICE_MIC;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_audio_device(recorder, device);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_audio_device_n
 * @since_tizen         2.3
 * @description         To check audio device with invalid value.
 * @scenario            This test is for checking invalid value which is out of range. \n
                        1. Check microphone supported or not. \n
                        2. Set audio device.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_media_recorder_attr_set_audio_device_n(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_audio_device_e device = 10;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_audio_device(recorder, device);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_audio_encoder_bitrate_p
 * @since_tizen         2.3
 * @description         To check audio encoder bitrate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set audio encoder bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_set_audio_encoder_bitrate_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_audio_encoder_bitrate(recorder, 11111);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_audio_encoder_bitrate_n
 * @since_tizen         2.3
 * @description         To check audio encoder bitrate with invalid paramter.
 * @scenario            This test is for checking invalid value which is out of range. \n
                        1. Check microphone supported or not. \n
                        2. Set audio encoder bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_media_recorder_attr_set_audio_encoder_bitrate_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_audio_encoder_bitrate(recorder, -1);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_audio_samplerate_p
 * @since_tizen         2.3
 * @description         To check audio sample-rate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Get audio sample-rate.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_set_audio_samplerate_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_audio_samplerate(recorder, 11111);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_audio_samplerate_n
 * @since_tizen         2.3
 * @description         To check audio sample-rate with invalid value.
 * @scenario            This test is for checking invalid value which is out of range. \n
                        1. Check microphone supported or not. \n
                        2. Set audio sample-rate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_media_recorder_attr_set_audio_samplerate_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_audio_samplerate(recorder, -1);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_size_limit_p
 * @since_tizen         2.3
 * @description         To check file size limitation with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Get filesize limitation.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_set_size_limit_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_size_limit(recorder, 0);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_size_limit_n1
 * @since_tizen         2.3
 * @description         To check file size limitation with invalid parameter.
 * @scenario            This test is for checking invalid value which is out of range. \n
                        1. Check microphone supported or not. \n
                        2. Get file size limitation.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_media_recorder_attr_set_size_limit_n1(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_size_limit(recorder, -1);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_size_limit_n2
 * @since_tizen         2.3
 * @description         To check file size limitation with invalid handle.
 * @scenario            This test is for checking invalid parameter such as reorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Get audio channel.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_set_size_limit_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_size_limit(NULL, 0);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_attr_set_time_limit_p
 * @since_tizen         2.3
 * @description         To check time limitation with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set time limitation.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_set_time_limit_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_time_limit(recorder, 11111);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_time_limit_n1
 * @since_tizen         2.3
 * @description         To check time limitation with invalid parameter.
 * @scenario            This test is for checking invalid value which is out of range. \n
                        1. Check microphone supported or not. \n
                        2. Set time limitation.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_media_recorder_attr_set_time_limit_n1(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_time_limit(recorder, -1);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_time_limit_n2
 * @since_tizen         2.3
 * @description         To check time limitation with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Set time limitation.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_set_time_limit_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_time_limit(NULL, 10);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_video_encoder_bitrate_p
 * @since_tizen         2.3
 * @description         To check video encoder bitrate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get video encoder bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_set_video_encoder_bitrate_p(void)
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

	ret = recorder_attr_set_video_encoder_bitrate(recorder, 1000000);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_video_encoder_bitrate_n1
 * @since_tizen         2.3
 * @description         To check video encoder bitrate with invalid parameter.
 * @scenario            This test is for checking invalid pointer which is out of range. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Set video encoder bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_media_recorder_attr_set_video_encoder_bitrate_n1(void)
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

	ret = recorder_attr_set_video_encoder_bitrate(recorder, -1);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_video_encoder_bitrate_n2
 * @since_tizen         2.3
 * @description         To check video encoder bitrate with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Set video encoder bitrate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_set_video_encoder_bitrate_n2(void)
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

	ret = recorder_attr_set_video_encoder_bitrate(NULL, -1);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_mute_p
 * @since_tizen         2.3
 * @description         To check mute with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set sound mute.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_set_mute_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_mute(recorder, false);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_mute_n
 * @since_tizen         2.3
 * @description         To check mute count with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Set mute.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_set_mute_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_mute(NULL, false);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_orientation_tag_p
 * @since_tizen         2.3
 * @description         To check orientation tag with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        2. Set orientation tag.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_set_orientation_tag_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_rotation_e rotation = RECORDER_ROTATION_NONE;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_orientation_tag(recorder, rotation);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_orientation_tag_n1
 * @since_tizen         2.3
 * @description         To check orientation tag with invalid parameter.
 * @scenario            This test is for checking invalid value which is out of range. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Set orientation tag.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_media_recorder_attr_set_orientation_tag_n1(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_rotation_e rotation = -1;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_orientation_tag(recorder, rotation);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_orientation_tag_n2
 * @since_tizen         2.3
 * @description         To check orientation tag with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Set orientation tag.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_set_orientation_tag_n2(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_rotation_e rotation = -1;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_attr_set_orientation_tag(NULL, rotation);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_attr_set_recording_motion_rate_p
 * @since_tizen         2.3
 * @description         To check recording motion rate with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Set recording motion rate.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_attr_set_recording_motion_rate_p(void)
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

	ret = recorder_attr_set_recording_motion_rate(recorder, 1.0);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_attr_set_recording_motion_rate_n
 * @since_tizen         2.3
 * @description         To check recording motion rate with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Set recording motion rate.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_attr_set_recording_motion_rate_n(void)
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

	ret = recorder_attr_set_recording_motion_rate(NULL, -1.0);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_audio_encoder_p
 * @since_tizen         2.3
 * @description         To check audio encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Get audio encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_get_audio_encoder_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_audio_codec_e value;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_get_audio_encoder(recorder, &value);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_audio_encoder_n1
 * @since_tizen         2.3
 * @description         To check audio encoder with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Check microphone supported or not. \n
                        2. Get audio encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_media_recorder_get_audio_encoder_n1(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_get_audio_encoder(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_audio_encoder_n2
 * @since_tizen         2.3
 * @description         To check audio encoder with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Set audio encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_get_audio_encoder_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_get_audio_encoder(NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_get_audio_encoder_p
 * @since_tizen         2.3
 * @description         To check audio encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set audio encoder AMR. \n
                        3. Get audio encoder. \n
                        4. Set audio encoder AAC. \n
                        5. Get audio encoder. \n
                        6. Set audio encoder VORBIS. \n
                        7. Get audio encoder. \n
                        8. Set audio encoder PCM. \n
                        9. Get audio encoder. \n
                        10. Set audio encoder DISABLE. \n
                        11. Get audio encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_get_audio_encoder_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_audio_codec_e codec = RECORDER_AUDIO_CODEC_AMR;
	recorder_audio_codec_e ret_codec = RECORDER_AUDIO_CODEC_AMR;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	codec = RECORDER_AUDIO_CODEC_AMR;
	ret = recorder_set_audio_encoder(recorder, codec);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_audio_encoder(recorder, &ret_codec);
	assert_eq(ret, RECORDER_ERROR_NONE);

	codec = RECORDER_AUDIO_CODEC_AAC;
	ret = recorder_set_audio_encoder(recorder, codec);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_audio_encoder(recorder, &ret_codec);
	assert_eq(ret, RECORDER_ERROR_NONE);

	codec = RECORDER_AUDIO_CODEC_VORBIS;
	ret = recorder_set_audio_encoder(recorder, codec);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_audio_encoder(recorder, &ret_codec);
	assert_eq(ret, RECORDER_ERROR_NONE);

	codec = RECORDER_AUDIO_CODEC_PCM;
	ret = recorder_set_audio_encoder(recorder, codec);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_audio_encoder(recorder, &ret_codec);
	assert_eq(ret, RECORDER_ERROR_NONE);

	codec = RECORDER_AUDIO_CODEC_DISABLE;
	ret = recorder_set_audio_encoder(recorder, codec);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_audio_encoder(recorder, &ret_codec);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}



/**
 * @testcase            utc_media_recorder_get_file_format_p
 * @since_tizen         2.3
 * @description         To check file format with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Get file format.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_get_file_format_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_file_format_e value = RECORDER_FILE_FORMAT_3GP;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_get_file_format(recorder, &value);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_file_format_n
 * @since_tizen         2.3
 * @description         To check file format with invalid handle.
 * @scenario            This test is for checking invalid pointer. \n
                        1. Check microphone supported or not. \n
                        2. Get file format.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if this api is getting function.
 */
int utc_media_recorder_get_file_format_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_get_file_format(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_video_encoder_p
 * @since_tizen         2.3
 * @description         To check video encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get video encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_get_video_encoder_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_video_codec_e value = RECORDER_VIDEO_CODEC_MPEG4;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_get_video_encoder(recorder, &value);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_video_encoder_n1
 * @since_tizen         2.3
 * @description         To check video encoder with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get video encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_media_recorder_get_video_encoder_n1(void)
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

	ret = recorder_get_video_encoder(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_video_encoder_n2
 * @since_tizen         2.3
 * @description         To check video encoder count with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get video encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_get_video_encoder_n2(void)
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

	ret = recorder_get_video_encoder(NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_get_video_encoder_p
 * @since_tizen         2.3
 * @description         To check video encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Set video encoder H263. \n
                        4. Get video encoder. \n
                        5. Set video encoder H264. \n
                        6. Get video encoder. \n
                        7. Set video encoder MPEG4. \n
                        8. Get video encoder. \n
                        9. Set video encoder THEORA. \n
                        10. Get video encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_get_video_encoder_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_video_codec_e codec = RECORDER_VIDEO_CODEC_H263;
	recorder_video_codec_e ret_codec = RECORDER_VIDEO_CODEC_H263;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	codec = RECORDER_VIDEO_CODEC_H263;
	ret = recorder_set_video_encoder(recorder, codec);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_video_encoder(recorder, &ret_codec);
	assert_eq(ret, RECORDER_ERROR_NONE);

	codec = RECORDER_VIDEO_CODEC_H264;
	ret = recorder_set_video_encoder(recorder, codec);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_video_encoder(recorder, &ret_codec);
	assert_eq(ret, RECORDER_ERROR_NONE);

	codec = RECORDER_VIDEO_CODEC_MPEG4;
	ret = recorder_set_video_encoder(recorder, codec);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_video_encoder(recorder, &ret_codec);
	assert_eq(ret, RECORDER_ERROR_NONE);

	codec = RECORDER_VIDEO_CODEC_THEORA;
	ret = recorder_set_video_encoder(recorder, codec);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_video_encoder(recorder, &ret_codec);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}



/**
 * @testcase            utc_media_recorder_get_audio_level_p
 * @since_tizen         2.3
 * @description         To check audio level with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Check supported audio encoder and file format. \n
                        3. Set supported audio encoder. \n
                        4. Set supported file format. \n
                        5. Set file name. \n
                        6. Prepare recorder. \n
                        7. Get audio level. \n
                        8. Cancel recorder. \n
                        9. Unprepare recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_get_audio_level_p(void)
{
	double value = 0.0;
	int ret = RECORDER_ERROR_NONE;
	int audio_codec = RECORDER_AUDIO_CODEC_DISABLE;
	int file_format = -1;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _get_supported_audio_encoder_and_file_format(recorder, &audio_codec, &file_format);
	assert_eq(ret, RECORDER_ERROR_NONE);

	if (audio_codec < 0 || file_format < 0) {
		fprintf(stderr, "Audio codec(or file format) is not supported.\n");
		return 1;
	}

	ret = recorder_set_audio_encoder(recorder, audio_codec);
	ret |= recorder_set_file_format(recorder, file_format);
	ret |= recorder_set_filename(recorder, media_path);
	ret |= recorder_prepare(recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	ret = recorder_start(recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	ret = recorder_get_audio_level(recorder, &value);

	recorder_cancel(recorder);
	recorder_unprepare(recorder);

	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_audio_level_n
 * @since_tizen         2.3
 * @description         To check audio level with invalid parameter.
 * @scenario            This test is for checking invalid pointer. \n
                        1. Check microphone supported or not. \n
                        2. Get audio level.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null even if this api is getting function.
 */
int utc_media_recorder_get_audio_level_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_get_audio_level(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_video_resolution_p
 * @since_tizen         2.3
 * @description         To check video resolution with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get video resolution.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_get_video_resolution_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	int mHeight = 0;
	int mWidth = 0;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_get_video_resolution(recorder, &mWidth, &mHeight);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_video_resolution_n1
 * @since_tizen         2.3
 * @description         To check video resolution with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as null. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get video resolution.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer even if the api is getting function.
 */
int utc_media_recorder_get_video_resolution_n1(void)
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

	ret = recorder_get_video_resolution(recorder, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_video_resolution_n2
 * @since_tizen         2.3
 * @description         To check video resolution with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Get video resolution.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_get_video_resolution_n2(void)
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

	ret = recorder_get_video_resolution(NULL, NULL, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_set_audio_encoder_p
 * @since_tizen         2.3
 * @description         To check audio encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set audio encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_audio_encoder_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_audio_codec_e codec = RECORDER_AUDIO_CODEC_DISABLE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_foreach_supported_audio_encoder(recorder, _audio_encoder_cb, &codec);
	assert_eq(ret, RECORDER_ERROR_NONE);

	if (codec < 0) {
		fprintf(stderr, "Audio codec is not supported.\n");
		return 1;
	}

	ret = recorder_set_audio_encoder(recorder, codec);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_audio_encoder_n1
 * @since_tizen         2.3
 * @description         To check audio encoder with invalid parameter.
 * @scenario            This test is for checking invalid value which is out of range. \n
                        1. Check microphone supported or not. \n
                        2. Set audio encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_media_recorder_set_audio_encoder_n1(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_audio_codec_e codec = -2;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_audio_encoder(recorder, codec);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;

}

/**
 * @testcase            utc_media_recorder_set_audio_encoder_n2
 * @since_tizen         2.3
 * @description         To check audio encoder with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check microphone supported or not. \n
                        2. Set audio encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_set_audio_encoder_n2(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_audio_codec_e codec = -2;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_audio_encoder(NULL, codec);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;

}

/**
 * @testcase            utc_media_recorder_set_audio_encoder_n3
 * @since_tizen         2.3
 * @description         To check audio encoder with invalid parameter with precodition.
 * @scenario            This test is for checking invalid parameter disable audio with creating audio recorder. \n
                        1. Check microphone supported or not. \n
                        2. Set audio encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is invalid parameter.
 */
int utc_media_recorder_set_audio_encoder_n3(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_audio_encoder(recorder, RECORDER_AUDIO_CODEC_DISABLE);
	assert_eq(ret, RECORDER_ERROR_NOT_SUPPORTED);

	return 0;

}



/**
 * @testcase            utc_media_recorder_set_file_format_p
 * @since_tizen         2.3
 * @description         To check file format with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set file format.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_file_format_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_file_format_e format = RECORDER_FILE_FORMAT_3GP;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_file_format(recorder, format);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_file_format_n
 * @since_tizen         2.3
 * @description         To check set file format with invalid parameter.
 * @scenario            This test is for checking invalid value which is out of range \n
                        1. Check microphone supported or not. \n
                        2. Set file format.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_media_recorder_set_file_format_n(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_file_format_e format = -1;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_file_format(recorder, format);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_filename_p
 * @since_tizen         2.3
 * @description         To check file name with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set file name.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_filename_p(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_filename(recorder, media_path);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_filename_n
 * @since_tizen         2.3
 * @description         To check file name with invalid handle.
 * @scenario            This test is for checking invalid pointer. \n
                        1. Check microphone supported or not. \n
                        2. Set file name.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null even if this api is getting function.
 */
int utc_media_recorder_set_filename_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_filename(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_video_encoder_p
 * @since_tizen         2.3
 * @description         To check video encoder with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Set video encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_video_encoder_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_video_codec_e codec = RECORDER_VIDEO_CODEC_MPEG4;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_video_encoder(recorder, codec);
	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_video_encoder_n1
 * @since_tizen         2.3
 * @description         To check video encoder with invalid parameter.
 * @scenario            This test is for checking invalid pointer which is out of range. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Set video encodeer.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_media_recorder_set_video_encoder_n1(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_video_codec_e codec = -1;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_video_encoder(recorder, codec);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_video_encoder_n2
 * @since_tizen         2.3
 * @description         To check video encoder with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Set video encoder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_set_video_encoder_n2(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_video_codec_e codec = -1;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_video_encoder(NULL, codec);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_set_video_resolution_p
 * @since_tizen         2.3
 * @description         To check video resolution with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Create video recorder. \n
                        4. Get video resolution. \n
                        5. Set video resolution. \n
                        6. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_video_resolution_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	int width = 0;
	int height = 0;
	recorder_h video_recorder = NULL;

	if (!video_recording_supported) {
		assert_eq(startup_ret_camera, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_create_videorecorder(camera, &video_recorder);
	assert_eq(ret, RECORDER_ERROR_NONE);

	ret = recorder_get_video_resolution(video_recorder, &width, &height);
	assert_eq(ret, RECORDER_ERROR_NONE);

	ret = recorder_set_video_resolution(video_recorder, width, height);

	recorder_destroy(video_recorder);

	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_get_file_format_p
 * @since_tizen         2.3
 * @description         To check file fomrat with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set file format 3GP. \n
                        3. Get file format. \n
                        4. Set file format MP4. \n
                        5. Get file format. \n
                        6. Set file format AMR. \n
                        7. Get file format. \n
                        8. Set file format ADTS. \n
                        9. Get file format. \n
                        10. Set file format WAV. \n
                        11. Get file format. \n
                        12. Set file format OGG. \n
                        13. Get file format.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_get_file_format_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_file_format_e format = RECORDER_FILE_FORMAT_3GP;
	recorder_file_format_e ret_format = RECORDER_FILE_FORMAT_3GP;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	format = RECORDER_FILE_FORMAT_3GP;
	ret = recorder_set_file_format(recorder, format);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_file_format(recorder, &ret_format);
	assert_eq(ret, RECORDER_ERROR_NONE);

	format = RECORDER_FILE_FORMAT_MP4;
	ret = recorder_set_file_format(recorder, format);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_file_format(recorder, &ret_format);
	assert_eq(ret, RECORDER_ERROR_NONE);

	format = RECORDER_FILE_FORMAT_AMR;
	ret = recorder_set_file_format(recorder, format);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_file_format(recorder, &ret_format);
	assert_eq(ret, RECORDER_ERROR_NONE);

	format = RECORDER_FILE_FORMAT_ADTS;
	ret = recorder_set_file_format(recorder, format);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_file_format(recorder, &ret_format);
	assert_eq(ret, RECORDER_ERROR_NONE);

	format = RECORDER_FILE_FORMAT_WAV;
	ret = recorder_set_file_format(recorder, format);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_file_format(recorder, &ret_format);
	assert_eq(ret, RECORDER_ERROR_NONE);

	format = RECORDER_FILE_FORMAT_OGG;
	ret = recorder_set_file_format(recorder, format);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	ret = recorder_get_file_format(recorder, &ret_format);
	if (ret != RECORDER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_video_resolution_n1
 * @since_tizen         2.3
 * @description         To check video resolution with invalid parameter.
 * @scenario            This test is for checking invalid value which is out of range. \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Set video resolution.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is out of range.
 */
int utc_media_recorder_set_video_resolution_n1(void)
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

	ret = recorder_set_video_resolution(recorder, 0, 0);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_video_resolution_n2
 * @since_tizen         2.3
 * @description         To check video resolution with invalid handle.
 * @scenario            This test is for checking invalid pointer such as recorder handle "null". \n
                        1. Check camera supported or not. \n
                        2. Check microphone supported or not. \n
                        3. Set video resolution.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null pointer handle.
 */
int utc_media_recorder_set_video_resolution_n2(void)
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

	ret = recorder_set_video_resolution(NULL, 0, 0);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_get_filename_p
 * @since_tizen         2.3
 * @description         To check file name with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Set file name. \n
                        3. Get file name. \n
                        4. Free file name.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_get_filename_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	char *f_name = NULL;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_filename(recorder, media_path);
	assert_eq(ret, RECORDER_ERROR_NONE);

	ret = recorder_get_filename(recorder, &f_name);
	if (f_name) {
		free(f_name);
		f_name = NULL;
	}

	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_filename_n
 * @since_tizen         2.3
 * @description         To check file name with invalid handle.
 * @scenario            This test is for checking invalid pointer which is null. \n
                        1. Check microphone supported or not. \n
                        2. Get filename.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null even if this api is getting function.
 */
int utc_media_recorder_get_filename_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_get_filename(recorder, NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_sound_stream_info_p
 * @since_tizen         3.0
 * @description         To check sound stream information setting with valid pointer and parameters.
 * @scenario            This test is for checking parameters valid or not. \n
                        1. Check microphone supported or not. \n
                        2. Create sound stream information. \n
                        3. Check sound stream information. \n
                        4. Set sound stream information.
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_set_sound_stream_info_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	int ret2 = SOUND_MANAGER_ERROR_NONE;
	sound_stream_info_h stream_info = NULL;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret2 = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA,
		_sound_stream_focus_state_changed_cb, NULL, &stream_info);

	assert_eq(ret2, SOUND_MANAGER_ERROR_NONE);
	assert_neq(stream_info, NULL);

	ret = recorder_set_sound_stream_info(recorder, stream_info);

	sound_manager_destroy_stream_information(stream_info);
	stream_info = NULL;

	assert_eq(ret, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_set_sound_stream_info_n
 * @since_tizen         3.0
 * @description         To check sound stream information setting with invalid stream information pointer.
 * @scenario            This test is for checking invalid pointer which is null. \n
                        1. Check microphone supported or not. \n
                        2. Set NULL for stream_info parameter.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null.
 */
int utc_media_recorder_set_sound_stream_info_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	if (!audio_recording_supported) {
		assert_eq(startup_ret, RECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = recorder_set_sound_stream_info(recorder, NULL);

	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}
