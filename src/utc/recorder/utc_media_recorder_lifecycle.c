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
#include <unistd.h>
#include <media/recorder.h>
#include <string.h>
#include <storage.h>
#include <system_info.h>

static char *media = ".test_record.amr";
static char *media_path = NULL;
static bool video_recording_supported = false;
static bool audio_recording_supported = false;

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

static bool _storage_device_cb(int storage_id, storage_type_e type, storage_state_e state, const char* path, void* user_data)
{
	int size_of_path = 0;

	if (type == STORAGE_TYPE_INTERNAL) {
		size_of_path = strlen(path) + strlen(media) + 6;
		media_path = (char *)malloc(size_of_path);
		if (media_path != NULL) {
			snprintf(media_path, size_of_path, "%s/%s", path, media);
		}

		return false;
	}

	return true;
}

/**
 * @function            utc_media_recorder_lifecycle_startup
 * @description         Called before each test. \n
                        This is the precondition for checking apis. \n
                        Tiis precondition is create_audiorecorder api for checking device and privilege error.
 * @scenario            1. Check device storage supported. \n
 * @parameter           N/A
 * @return              N/A
 */
void utc_media_recorder_lifecycle_startup(void)
{
	storage_foreach_device_supported(_storage_device_cb, NULL);

	system_info_get_platform_bool("http://tizen.org/feature/media.audio_recording", &audio_recording_supported);
	system_info_get_platform_bool("http://tizen.org/feature/media.video_recording", &video_recording_supported);

	return;
}


/**
 * @testcase            utc_media_recorder_create_audiorecorder_n
 * @since_tizen         2.3
 * @description         To check audio recorder creation with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null.
                        1. Create audio recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_media_recorder_create_audiorecorder_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	ret = recorder_create_audiorecorder(NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_create_audiorecorder_p
 * @since_tizen         2.3
 * @description         To check audio recorder creation with valid parameter.
 * @scenario            This test is for checking valid pointer and parameters.
                        1. Create audio recorder. \n
                        2. Check microphone supported or not.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_create_audiorecorder_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;

	ret = recorder_create_audiorecorder(&recorder);

	if (!audio_recording_supported) {
		assert_eq(ret, RECORDER_ERROR_NOT_SUPPORTED);
	} else {
		recorder_destroy(recorder);
		assert_eq(ret, RECORDER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_cancel_p
 * @since_tizen         2.3
 * @description         To check recorder cancel with valid parameter.
 * @scenario            This test is for checking valid pointer and parameters.
                        1. Create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. Check supported audio encoder and file format. \n
                        4. Set supported audio encoder. \n
                        5. Set supported file format. \n
                        6. Set file name. \n
                        7. Prepare recorder. \n
                        8. Start recorder. \n
                        9. Record for some time while sleep. \n
                        10. Cancel recorder. \n
                        11. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_cancel_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;
	int audio_codec = RECORDER_AUDIO_CODEC_DISABLE;
	int file_format = -1;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
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
		ret |= recorder_start(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);

		sleep(2);

		ret = recorder_cancel(recorder);

		recorder_unprepare(recorder);
		recorder_destroy(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);
	} else {
		assert_eq(ret,RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_cancel_n
 * @since_tizen         2.3
 * @description         To check recorder cancel with invalid precondition.
 * @scenario            This test is for checking with invalid precondition without calling recorder_start.
                        1. Create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. Check supported audio encoder and file format. \n
                        4. Set supported audio encoder. \n
                        5. Set supported file format. \n
                        6. Prepare recorder. \n
                        7. Cancel recorder. \n
                        8. Unprepare recorder. \n
                        9. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because precondition does not match.
 */
int utc_media_recorder_cancel_n(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;
	int audio_codec = RECORDER_AUDIO_CODEC_DISABLE;
	int file_format = -1;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
		ret = _get_supported_audio_encoder_and_file_format(recorder, &audio_codec, &file_format);
		assert_eq(ret, RECORDER_ERROR_NONE);

		if (audio_codec < 0 || file_format < 0) {
			fprintf(stderr, "Audio codec(or file format) is not supported.\n");
			return 1;
		}

		ret = recorder_set_audio_encoder(recorder, audio_codec);
		ret |= recorder_set_file_format(recorder, file_format);
		ret |= recorder_prepare(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);

		ret = recorder_cancel(recorder);

		recorder_unprepare(recorder);
		recorder_destroy(recorder);

		assert_eq(ret, RECORDER_ERROR_INVALID_STATE);
	} else {
		assert_eq(ret,RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_commit_p
 * @since_tizen         2.3
 * @description         To check recorder commit with valid precondition.
 * @scenario            This test is for checking with valid parameters and preconditions.
                        1. Create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. Check supported audio encoder and file format. \n
                        4. Set supported audio encoder. \n
                        5. Set supported file format. \n
                        6. Set file name. \n
                        7. Prepare recorder. \n
                        8. Start recorder. \n
                        9. Sleep for a while. \n
                        10. Commit recorder. \n
                        11. Unprepare recorder. \n
                        12. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_commit_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;
	int audio_codec = RECORDER_AUDIO_CODEC_DISABLE;
	int file_format = -1;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
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
		ret |= recorder_start(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);

		sleep(2);

		ret = recorder_commit(recorder);

		recorder_unprepare(recorder);
		recorder_destroy(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);
	} else {
		assert_eq(ret,RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_commit_n
 * @since_tizen         2.3
 * @description         To check recorder commit with invalid precondition.
 * @scenario            This test is for checking without precondition such as recorder_start. \n
                        1. Create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. Check supported audio encoder and file format. \n
                        4. Set supported audio encoder. \n
                        5. Set supported file format. \n
                        6. Prepare recorder. \n
                        7. Commit recorder. \n
                        8. Unprepare recorder. \n
                        9. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because precondition does not match.
 */
int utc_media_recorder_commit_n(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;
	int audio_codec = RECORDER_AUDIO_CODEC_DISABLE;
	int file_format = -1;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
		ret = _get_supported_audio_encoder_and_file_format(recorder, &audio_codec, &file_format);
		assert_eq(ret, RECORDER_ERROR_NONE);

		if (audio_codec < 0 || file_format < 0) {
			fprintf(stderr, "Audio codec(or file format) is not supported.\n");
			return 1;
		}

		ret = recorder_set_audio_encoder(recorder, audio_codec);
		ret |= recorder_set_file_format(recorder, file_format);
		ret |= recorder_prepare(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);

		ret = recorder_commit(recorder);

		recorder_unprepare(recorder);
		recorder_destroy(recorder);

		assert_neq(ret, RECORDER_ERROR_NONE);
	} else {
		assert_eq(ret,RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_create_videorecorder_p
 * @since_tizen         2.3
 * @description         To check video recorder creation with valid precondition.
 * @scenario            This test is for checking with proper precondition. \n
                        1. Create camera. \n
                        2. Check camera supported or not. \n
                        3. Create video recorder. \n
                        4. Destroy recorder. \n
                        5. Destroy camera.
 * @paramter            N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_create_videorecorder_p(void)
{
	recorder_h recorder = NULL;
	camera_h camera = NULL;
	int ret = CAMERA_ERROR_NONE;
	int ret2 = RECORDER_ERROR_NONE;

	ret = camera_create(CAMERA_DEVICE_CAMERA0, &camera);
	if (!video_recording_supported) {
		assert_eq(ret, CAMERA_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		assert_eq(ret, CAMERA_ERROR_NONE);
	}

	ret2 = recorder_create_videorecorder(camera, &recorder);

	if (recorder)
		recorder_destroy(recorder);

	if (camera)
		camera_destroy(camera);

	assert_eq(ret2, RECORDER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_media_recorder_create_videorecorder_n
 * @since_tizen         2.3
 * @description         To check video recorder creation with invalid parameter.
 * @scenario            This test is for checking with camera handle null. \n
                        1. Create video recorder.
 * @paramter            N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because camera handle is null.
 */
int utc_media_recorder_create_videorecorder_n(void)
{
	recorder_h recorder = NULL;
	int ret = RECORDER_ERROR_NONE;

	ret = recorder_create_videorecorder(NULL, &recorder);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_destroy_p
 * @since_tizen         2.3
 * @description         To check to destroy recorder with valid precondition.
 * @scenario            This test is for checking with valid precondition.
                        1. create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_destroy_p(void)
{
	recorder_h recorder = NULL;
	int ret = RECORDER_ERROR_NONE;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
		assert_eq(ret, RECORDER_ERROR_NONE);

		ret = recorder_destroy(recorder);
		assert_eq(ret, RECORDER_ERROR_NONE);
	} else {
		assert_eq(ret,RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_destroy_n
 * @since_tizen         2.3
 * @description         To check to destroy recorder with invalid parameter.
 * @scenario            This test is for checking with recorder handle null. \n
                        1. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_media_recorder_destroy_n(void)
{
	int ret = RECORDER_ERROR_NONE;

	ret = recorder_destroy(NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_pause_p
 * @since_tizen         2.3
 * @description         To check to pause recorder with valid precondition.
 * @scenario            This test is for checking with valid precondition.
                        1. Create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. Check supported audio encoder and file format. \n
                        4. Set supported audio encoder. \n
                        5. Set supported file format. \n
                        6. Set file name. \n
                        7. Prepare recorder. \n
                        8. Start recorder. \n
                        9. Sleep for a while. \n
                        10. Pause recorder. \n
                        11. Cancel recorder. \n
                        12. Unprepare recorder. \n
                        13. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_pause_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;
	int audio_codec = RECORDER_AUDIO_CODEC_DISABLE;
	int file_format = -1;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
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
		ret |= recorder_start(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);

		sleep(2);

		ret = recorder_pause(recorder);

		recorder_cancel(recorder);
		recorder_unprepare(recorder);
		recorder_destroy(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);
	} else {
		assert_eq(ret,RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_pause_n
 * @since_tizen         2.3
 * @description         To check to pause recorder with invalid precondition.
 * @scenario            This test is for checking with invalid preconditon such as recorder_start. \n
                        1. Create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. Check supported audio encoder and file format. \n
                        4. Set supported audio encoder. \n
                        5. Set supported file format. \n
                        6. Prepare recorder. \n
                        7. Pause recorder. \n
                        8. Unprepare recorder. \n
                        9. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because precondition does not match.
 */
int utc_media_recorder_pause_n(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;
	int audio_codec = RECORDER_AUDIO_CODEC_DISABLE;
	int file_format = -1;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
		ret = _get_supported_audio_encoder_and_file_format(recorder, &audio_codec, &file_format);
		assert_eq(ret, RECORDER_ERROR_NONE);

		if (audio_codec < 0 || file_format < 0) {
			fprintf(stderr, "Audio codec(or file format) is not supported.\n");
			return 1;
		}

		ret = recorder_set_audio_encoder(recorder, audio_codec);
		ret |= recorder_set_file_format(recorder, file_format);
		ret |= recorder_prepare(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);

		ret = recorder_pause(recorder);

		recorder_unprepare(recorder);
		recorder_destroy(recorder);

		assert_eq(ret, RECORDER_ERROR_INVALID_STATE);
	} else {
		assert_eq(ret,RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_prepare_p
 * @since_tizen         2.3
 * @description         To check to prepare recorder with valid precondition.
 * @scenario            This test is for checking with valid precondition. \n
                        1. Create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. Check supported audio encoder and file format. \n
                        4. Set supported audio encoder. \n
                        5. Set supported file format. \n
                        6. Prepare recorder. \n
                        7. Unprepare recorder. \n
                        8. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_prepare_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;
	int audio_codec = RECORDER_AUDIO_CODEC_DISABLE;
	int file_format = -1;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
		ret = _get_supported_audio_encoder_and_file_format(recorder, &audio_codec, &file_format);
		assert_eq(ret, RECORDER_ERROR_NONE);

		if (audio_codec < 0 || file_format < 0) {
			fprintf(stderr, "Audio codec(or file format) is not supported.\n");
			return 1;
		}

		ret = recorder_set_audio_encoder(recorder, audio_codec);
		ret |= recorder_set_file_format(recorder,file_format);

		assert_eq(ret, RECORDER_ERROR_NONE);

		ret = recorder_prepare(recorder);

		recorder_unprepare(recorder);
		recorder_destroy(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);
	} else {
		assert_eq(ret,RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_prepare_n1
 * @since_tizen         2.3
 * @description         To check prepare recorder with invalid precondition.
 * @scenario            This test is for checking with invalid precondition with default setting. \n
                        1. Create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. Prepare recorder. \n
                        4. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because default setting was not prepared. \n
                        Please check default setting for encoder and file format.
 */
int utc_media_recorder_prepare_n1(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
		assert_eq(ret, RECORDER_ERROR_NONE);

		ret = recorder_prepare(recorder);

		recorder_destroy(recorder);

		assert_eq(ret, RECORDER_ERROR_INVALID_OPERATION);
	} else {
		assert_eq(ret,RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_prepare_n2
 * @since_tizen         2.3
 * @description         To check to prepare recorder with invalid parameter.
 * @scenario            This test is for checking with invalid parameter such as recorder handle null. \n
                        1. Prepare recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_media_recorder_prepare_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	ret = recorder_prepare(NULL);
	assert_eq(ret,RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_start_p
 * @since_tizen         2.3
 * @description         To check to start recorder with valid precondition.
 * @scenario            This test is for checking with valid precondition. \n
                        1. Create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. Check supported audio encoder and file format. \n
                        4. Set supported audio encoder. \n
                        5. Set supported file format. \n
                        6. Set file name. \n
                        7. Prepare recorder. \n
                        8. Start recorder. \n
                        9. Cancel recorder. \n
                        10. Unprepare recorder. \n
                        11. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_start_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;
	int audio_codec = RECORDER_AUDIO_CODEC_DISABLE;
	int file_format = -1;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
		ret = _get_supported_audio_encoder_and_file_format(recorder, &audio_codec, &file_format);
		assert_eq(ret, RECORDER_ERROR_NONE);

		if (audio_codec < 0 || file_format < 0) {
			fprintf(stderr, "Audio codec(or file format) is not supported.\n");
			return 1;
		}

		ret = recorder_set_audio_encoder(recorder, audio_codec);
		ret |= recorder_set_file_format(recorder,file_format);
		ret |= recorder_set_filename(recorder, media_path);
		ret |= recorder_prepare(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);

		ret = recorder_start(recorder);

		recorder_cancel(recorder);
		recorder_unprepare(recorder);
		recorder_destroy(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);
	} else {
		assert_eq(ret, RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_start_n
 * @since_tizen         2.3
 * @description         To check to start recorder with invalid precondition.
 * @scenario            This test is for checking with invalid precondition such as recorder_prepare. \n
                        1. Create audiorecorder. \n
                        2. Check microphone supported or not. \n
                        3. Start recorder. \n
                        4. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder_prepare was not called before recorder_start.
 */
int utc_media_recorder_start_n(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
		assert_eq(ret, RECORDER_ERROR_NONE);

		ret = recorder_start(recorder);

		recorder_destroy(recorder);

		assert_eq(ret, RECORDER_ERROR_INVALID_STATE);
	} else {
		assert_eq(ret, RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_unprepare_p
 * @since_tizen         2.3
 * @description         To check to unprepare recorder with valid precondition.
 * @scenario            This test is for checking with valid precondition. \n
                        1. Create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. Check supported audio encoder and file format. \n
                        4. Set supported audio encoder. \n
                        5. Set supported file format. \n
                        6. Prepare recorder. \n
                        7. Unprepare recorder. \n
                        8. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_unprepare_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;
	int audio_codec = RECORDER_AUDIO_CODEC_DISABLE;
	int file_format = -1;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
		ret = _get_supported_audio_encoder_and_file_format(recorder, &audio_codec, &file_format);
		assert_eq(ret, RECORDER_ERROR_NONE);

		if (audio_codec < 0 || file_format < 0) {
			fprintf(stderr, "Audio codec(or file format) is not supported.\n");
			return 1;
		}

		ret = recorder_set_audio_encoder(recorder, audio_codec);
		ret |= recorder_set_file_format(recorder,file_format);
		ret |= recorder_prepare(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);

		ret = recorder_unprepare(recorder);

		recorder_destroy(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);
	} else {
		assert_eq(ret,RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_unprepare_n1
 * @since_tizen         2.3
 * @description         To check to unprepare recorder with invalid precondition.
 * @scenario            This test is for checking with invalid precondition such as recorder_prepare. \n
                        1. Create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. Unprepare recorder. \n
                        4. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because precondition does not match.
 */
int utc_media_recorder_unprepare_n1(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
		assert_eq(ret, RECORDER_ERROR_NONE);

		ret = recorder_unprepare(recorder);

		recorder_destroy(recorder);

		assert_eq(ret, RECORDER_ERROR_INVALID_STATE);
	} else {
		assert_eq(ret, RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_unprepare_n2
 * @since_tizen         2.3
 * @description         To check to unprepare recorder with invalid parameter.
 * @scenario            This test is for checking with invalid parameter such as recorder handle null. \n
                        1. Unprepare recorder with recorder handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle null.
 */
int utc_media_recorder_unprepare_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	ret = recorder_unprepare(NULL);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_get_state_p
 * @since_tizen         2.3
 * @description         To check recorder state with valid precondition.
 * @scenario            This test is for checking valid state of recorder. \n
                        1. Create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. Get state. \n
                        4. Destroy recorder.
 * @parameter          N/A
 * @return             1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_get_state_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;
	recorder_state_e state = RECORDER_STATE_NONE;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
		assert_eq(ret, RECORDER_ERROR_NONE);

		ret = recorder_get_state(recorder, &state);

		recorder_destroy(recorder);

		assert_eq(ret, RECORDER_ERROR_NONE);
	} else {
		assert_eq(ret,RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_state_n1
 * @since_tizen         2.3
 * @description         To check recorder state with invalid parameter.
 * @scenario            This test is for checking invalid parameter such as recorder handle null. \n
                        1. Get state.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder was not created.
 */
int utc_media_recorder_get_state_n1(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_state_e state = RECORDER_STATE_NONE;

	ret = recorder_get_state(NULL, &state);
	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_state_n2
 * @since_tizen         2.3
 * @description         To check recorder state with invalid parameter.
 * @scenario            This test is for checking invalid parameter such as null. \n
                        1. Create audio recorder. \n
                        2. Check microphone supported or not. \n
                        3. Get state. \n
                        4. Destroy recorder.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null even if this api is getting function.
 */
int utc_media_recorder_get_state_n2(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_h recorder = NULL;

	ret = recorder_create_audiorecorder(&recorder);

	if (audio_recording_supported) {
		ret = recorder_get_state(recorder, NULL);

		recorder_destroy(recorder);

		assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, RECORDER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_media_recorder_get_device_state_p
 * @since_tizen         3.0
 * @description         To check device state with valid value in parameters.
 * @scenario            This test is for checking device state getting with valid parameters.
                        1. Get device state with valid parameters. \n
                        2. Check microphone which is supported or not. \n
                        3-1. If supported, compare "ret" value with RECORDER_ERROR_NONE. \n
                        3-1. If not supported, compare "ret" value with RECORDER_ERROR_NOT_SUPPORTED.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_media_recorder_get_device_state_p(void)
{
	int ret = RECORDER_ERROR_NONE;
	int check_ret = RECORDER_ERROR_NONE;
	recorder_device_state_e device_state = RECORDER_DEVICE_STATE_IDLE;

	ret = recorder_get_device_state(RECORDER_TYPE_AUDIO, &device_state);

	if (audio_recording_supported)
		check_ret = RECORDER_ERROR_NONE;
	else
		check_ret = RECORDER_ERROR_NOT_SUPPORTED;

	assert_eq(ret, check_ret);

	return 0;
}


/**
 * @testcase            utc_media_recorder_get_device_state_n1
 * @since_tizen         3.0
 * @description         To check device state with invalid value in parameters.
 * @scenario            This test is for checking invalid value in parameters.
                        1. Get device state with invalid parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the first parameter is invalid.
 */
int utc_media_recorder_get_device_state_n1(void)
{
	int ret = RECORDER_ERROR_NONE;
	recorder_device_state_e device_state = RECORDER_DEVICE_STATE_IDLE;

	ret = recorder_get_device_state(-1, &device_state);

	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase            utc_media_recorder_get_device_state_n2
 * @since_tizen         3.0
 * @description         To check device state with invalid value in parameters.
 * @scenario            This test is for checking invalid value in parameters.
                        1. Get device state with invalid parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because the second parameter is null.
 */
int utc_media_recorder_get_device_state_n2(void)
{
	int ret = RECORDER_ERROR_NONE;

	ret = recorder_get_device_state(RECORDER_TYPE_AUDIO, NULL);

	assert_eq(ret, RECORDER_ERROR_INVALID_PARAMETER);

	return 0;
}
