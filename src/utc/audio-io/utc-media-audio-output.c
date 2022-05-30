//
// Copyright (c) 2015 Samsung Electronics Co., Ltd.
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
#include <pthread.h>
#include <string.h>
#include <storage.h>
#include <media/audio_io.h>

//& set: Audio Output
#define SAMPLE_RATE_44100 44100
#define SAMPLE_RATE_48000 48000
#define SAMPLE_RATE_192000 192000

#define TEST_SAMPLE_LENGTH 1024

static char *AUDIO_PATH = NULL;
static char *AUDIO_FILE = "sound_5.wav";

static pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct _thread_data_s
{
    pthread_mutex_t* mutex;
    pthread_cond_t*  cond;
    int              callback_ret;
} thread_data_s;

typedef struct _create_test_condition_s
{
    int sample_rate;
    audio_channel_e channel_type;
    audio_sample_type_e sample_type;
} create_test_condition_s;

static void _audio_out_stream_cb(audio_out_h handle, size_t nbytes, void *userdata)
{
    thread_data_s* td = (thread_data_s*)userdata;
    if (td == NULL)
    {
        return;
    }

    pthread_mutex_lock(td->mutex);
    td->callback_ret = AUDIO_IO_ERROR_NONE;
    pthread_cond_signal(td->cond);
    pthread_mutex_unlock(td->mutex);
}

static bool _storage_supported_cb(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
    if (type == STORAGE_TYPE_INTERNAL) {
        AUDIO_PATH = (char*)malloc(strlen(path) + strlen(AUDIO_FILE) + 6);
        snprintf(AUDIO_PATH, strlen(path) + strlen(AUDIO_FILE) + 6, "%s/res/%s", path, AUDIO_FILE);
        return false;
    }

    return true;
}

static void _audio_io_state_changed_cb(audio_in_h handle, audio_io_state_e previous, audio_io_state_e current, bool by_policy, void *user_data)
{
    // dummy callback for test
}

static void _focus_changed_cb(sound_stream_info_h stream_info, sound_stream_focus_mask_e focus_mask, sound_stream_focus_state_e focus_state,
                            sound_stream_focus_change_reason_e reason_for_change, int sound_behavior, const char *additional_info, void *user_data)
{
    // dummy callback for test
}


/**
 * @function		utc_media_audio_out_startup
 * @description		Called before each test.
 * @parameter		NA
 * @return			NA
 */
void utc_media_audio_out_startup(void)
{
    if (storage_foreach_device_supported(_storage_supported_cb, NULL) != STORAGE_ERROR_NONE) {
        fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
    }
}

/**
 * @function		utc_media_audio_out_cleanup
 * @description		Called after each test.
 * @parameter		NA
 * @return			NA
 */
void utc_media_audio_out_cleanup(void)
{
    if (AUDIO_PATH)
        free(AUDIO_PATH);
}

/**
 * @testcase		utc_media_audio_out_create_new_p
 * @since_tizen		2.3
 * @description		Create an audio handle of device.\n
 * 					- Create an audio handle of device.\n
 * 					- Destroy audio handle.(repeat)
 */
int utc_media_audio_out_create_new_p(void)
{
    int ret;
    audio_out_h output = NULL;
    int i;

    create_test_condition_s pcond[] = {
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE },
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_U8 },
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE },
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_U8 },
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE },
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_U8 },
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE },
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_U8 },
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S24_LE },    /* since 5.0 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S24_32_LE }, /* since 5.0 */
        { SAMPLE_RATE_192000, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S32_LE },   /* since 5.5 */
    };

    for (i = 0; i < sizeof(pcond) / sizeof(create_test_condition_s); i++) {
        ret = audio_out_create_new(pcond[i].sample_rate, pcond[i].channel_type, pcond[i].sample_type, &output);
        assert_eq(ret, AUDIO_IO_ERROR_NONE);

        audio_out_destroy(output);
    }

    return 0;
}

/**
 * @testcase		utc_media_audio_out_create_n
 * @since_tizen		2.3
 * @description		Create an audio handle of device.\n
 * 					- Create an audio handle of device with invalid parameters.(repeat)
 */
int utc_media_audio_out_create_new_n(void)
{
    int ret;
    audio_out_h output = NULL;
    int i;

    create_test_condition_s ncond[] = {
        { 0, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE },
        { SAMPLE_RATE_44100, 0, AUDIO_SAMPLE_TYPE_S16_LE },
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, 0 },
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_U8 - 1},
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MONO - 1, AUDIO_SAMPLE_TYPE_S16_LE },
        { SAMPLE_RATE_192000 + 1, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE }, /* since 5.0 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S32_LE + 1 },    /* since 5.5 */
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_3, AUDIO_SAMPLE_TYPE_U8 },         /* since 5.5 */
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_4, AUDIO_SAMPLE_TYPE_S16_LE },     /* since 5.5 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_5, AUDIO_SAMPLE_TYPE_S24_LE },     /* since 5.5 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_6, AUDIO_SAMPLE_TYPE_S24_32_LE },  /* since 5.5 */
        { SAMPLE_RATE_192000, AUDIO_CHANNEL_MULTI_7, AUDIO_SAMPLE_TYPE_S32_LE },    /* since 5.5 */
        { SAMPLE_RATE_192000, AUDIO_CHANNEL_MULTI_8, AUDIO_SAMPLE_TYPE_S24_LE },    /* since 5.5 */
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_9, AUDIO_SAMPLE_TYPE_S32_LE },     /* since 6.5 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_10, AUDIO_SAMPLE_TYPE_S24_32_LE }, /* since 6.5 */
        { SAMPLE_RATE_192000, AUDIO_CHANNEL_MULTI_11, AUDIO_SAMPLE_TYPE_S16_LE },   /* since 6.5 */
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_12, AUDIO_SAMPLE_TYPE_S24_LE },    /* since 6.5 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_13, AUDIO_SAMPLE_TYPE_S24_32_LE }, /* since 6.5 */
        { SAMPLE_RATE_192000, AUDIO_CHANNEL_MULTI_14, AUDIO_SAMPLE_TYPE_S32_LE },   /* since 6.5 */
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_15, AUDIO_SAMPLE_TYPE_S16_LE },    /* since 6.5 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_16, AUDIO_SAMPLE_TYPE_S16_LE },    /* since 6.5 */
    };

    for (i = 0; i < sizeof(ncond) / sizeof(create_test_condition_s); i++) {
        ret = audio_out_create_new(ncond[i].sample_rate, ncond[i].channel_type, ncond[i].sample_type, &output);
        assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);
    }

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_destroy_p
 * @since_tizen		2.3
 * @description		Release the audio output handle.\n
 * 					- Create an audio handle of device.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_out_destroy_p(void)
{
    int ret;
    audio_out_h output;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_destroy(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_destroy_n
 * @since_tizen		2.3
 * @description		Release the audio output handle.\n
 * 					- Destroy audio handle with invalid parameter.
 */
int utc_media_audio_out_destroy_n(void)
{
    int ret;

    ret = audio_out_destroy(NULL);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_write_p
 * @since_tizen		2.3
 * @description		Start writing the audio data to the device.\n
 * 					- Prepare audio output.\n
 * 					- Get buffer size.\n
 * 					- Write audio output buffer.\n
 * 					- Unprepare audio output.
 * 					- Set stream callback to use async mode.\n
 * 					- Prepare audio output.\n
 * 					- Get buffer size.\n
 * 					- Write audio output buffer.\n
 * 					- Unprepare audio output.
 */
int utc_media_audio_out_write_p(void)
{
    int ret, size, read;
    audio_out_h output;
    char *buffer = NULL;
    FILE *fp = NULL;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // 1) Check sync API
    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_get_buffer_size(output, &size);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    if (size == 0)  size = 8096;

    buffer = malloc(size);
    if (buffer == NULL) {
        return 1;
    }

    fp = fopen(AUDIO_PATH, "r");
    if (fp != NULL) {
        read = fread(buffer, size, sizeof(char), fp);
        if (read <= 0) {
            read = size;
            memset(buffer, 0, size);
        }
        fclose(fp);
    } else {
        read = size;
        memset(buffer, 0, size);
    }

    ret = audio_out_write(output, (void*)buffer, read);

    if (buffer) {
        free(buffer);
    }

    audio_out_unprepare(output);
    audio_out_destroy(output);

    assert_gt(ret, 0);

    // 2) Check async API
    thread_data_s td;
    td.mutex        = &mutex;
    td.cond         = &cond;
    td.callback_ret = -1;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_set_stream_cb(output, _audio_out_stream_cb, &td);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_get_buffer_size(output, &size);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    if (size == 0)  size = 8096;

    pthread_mutex_lock(&mutex);
    if (td.callback_ret == -1)
        pthread_cond_wait(&cond, &mutex);
    assert_eq(td.callback_ret, AUDIO_IO_ERROR_NONE);
    pthread_mutex_unlock(&mutex);

    buffer = malloc(size);
    if (buffer == NULL) {
        return 1;
    }

    fp = fopen(AUDIO_PATH, "r");
    if (fp != NULL) {
        read = fread(buffer, size, sizeof(char), fp);
        if (read <= 0) {
            read = size;
            memset(buffer, 0, size);
        }
        fclose(fp);
    } else {
        read = size;
        memset(buffer, 0, size);
    }

    ret = audio_out_write(output, (void*)buffer, read);

    if (buffer) {
        free(buffer);
    }

    audio_out_unprepare(output);
    audio_out_destroy(output);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    assert_gt(ret, 0);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_write_n1
 * @since_tizen		2.3
 * @description		Start writing the audio data to the device.\n
 * 					- Prepare audio output.\n
 * 					- Get buffer size.\n
 * 					- Write audio output buffer with invalid parameter.\n
 * 					- Unprepare audio output.
 */
int utc_media_audio_out_write_n1(void)
{
    int ret, size;
    audio_out_h output;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_get_buffer_size(output, &size);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_write(output, NULL, 0);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    ret = audio_out_unprepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_destroy(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_write_n2
 * @since_tizen		2.3
 * @description		Check whether audio_out_write return invalid operation error properly.
 */
int utc_media_audio_out_write_n2(void)
{
    int ret, size;
    audio_out_h output;
    char buffer[TEST_SAMPLE_LENGTH];

    /* pre */
    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    /* check #1 : write before prepare */
    ret = audio_out_write(output, buffer, TEST_SAMPLE_LENGTH);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_OPERATION);

    /* check #2 : write after pause */
    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_pause(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_write(output, buffer, TEST_SAMPLE_LENGTH);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_OPERATION);

    /* check #3 : write after unprepare */
    ret = audio_out_unprepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_write(output, buffer, TEST_SAMPLE_LENGTH);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_OPERATION);

    /* cleanup */
    ret = audio_out_destroy(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_get_buffer_size_p
 * @since_tizen		2.3
 * @description		Get the size to be allocated for the audio output buffer.\n
 * 					- Create an audio handle of device.\n
 * 					- Get buffer size of audio output buffer.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_out_get_buffer_size_p(void)
{
    int ret, size;
    audio_out_h output;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_get_buffer_size(output, &size);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_out_destroy(output);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_get_buffer_size_n
 * @since_tizen		2.3
 * @description		Get the size to be allocated for the audio output buffer.\n
 * 					- Create an audio handle of device.\n
 * 					- Get buffer size of audio output buffer with invalid parameter.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_out_get_buffer_size_n(void)
{
    int ret;
    audio_out_h output;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_get_buffer_size(output, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    audio_out_destroy(output);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_get_sample_rate_p
 * @since_tizen		2.3
 * @description		Get the sample rate of the audio output stream.\n
 * 					- Create an audio handle of device.\n
 * 					- Get sample rate of audio output stream.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_out_get_sample_rate_p(void)
{
    int ret;
    audio_out_h output;
    int sample_rate;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_get_sample_rate(output, &sample_rate);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_out_destroy(output);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_get_sample_rate_n
 * @since_tizen		2.3
 * @description		Get the sample rate of the audio output stream.\n
 * 					- Get sample rate of audio output stream with invalid parameter.
 */
int utc_media_audio_out_get_sample_rate_n(void)
{
    int ret, sample_rate;
    audio_out_h output = NULL;

    ret = audio_out_get_sample_rate(output, &sample_rate);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_get_channel_p
 * @since_tizen		2.3
 * @description		Get the channel type of the audio output stream.\n
 * 					- Create an audio handle of device.\n
 * 					- Get channel type of audio output stream.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_out_get_channel_p(void)
{
    int ret;
    audio_out_h output;
    audio_channel_e channel;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_get_channel(output, &channel);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_out_destroy(output);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_get_channel_n
 * @since_tizen		2.3
 * @description		Get the channel type of the audio output stream.\n
 * 					- Get channel type of audio output stream with invalid parameter.
 */
int utc_media_audio_out_get_channel_n(void)
{
    int ret;
    audio_channel_e channel;
    audio_out_h output = NULL;

    ret = audio_out_get_channel(output, &channel);

    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_get_sample_type_p
 * @since_tizen		2.3
 * @description		Get the sample audio format of the audio output stream.\n
 * 					- Create an audio handle of device.\n
 * 					- Get sample format of audio output stream.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_out_get_sample_type_p(void)
{
    int ret;
    audio_out_h output;
    audio_sample_type_e type;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_get_sample_type(output, &type);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_out_destroy(output);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_get_sample_type_n
 * @since_tizen		2.3
 * @description		Get the sample audio format of the audio output stream.\n
 * 					- Get sample format of audio output stream with invalid parameter.
 */
int utc_media_audio_out_get_sample_type_n(void)
{
    int ret;
    audio_sample_type_e type;
    audio_out_h output = NULL;

    ret = audio_out_get_sample_type(output, &type);

    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_get_sound_type_p
 * @since_tizen		2.3
 * @description		Get the sound type supported by the audio output device.\n
 * 					- Create an audio handle of device.\n
 * 					- Get sound type of audio output stream.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_out_get_sound_type_p(void)
{
    int ret;
    audio_out_h output;
    sound_type_e type;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_get_sound_type(output, &type);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_out_destroy(output);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_get_sound_type_n
 * @since_tizen		2.3
 * @description		Get the sound type supported by the audio output device.\n
 * 					- Get sound type of audio output stream with invalid parameter.
 */
int utc_media_audio_out_get_sound_type_n(void)
{
    int ret;
    sound_type_e type;
    audio_out_h output = NULL;

    ret = audio_out_get_sound_type(output, &type);

    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_prepare_p
 * @since_tizen		2.3
 * @description		Prepare and start of playing audio output.\n
 * 					- Create an audio handle of device.\n
 * 					- Prepare audio output.\n
 * 					- Unprepare audio output.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_out_prepare_p(void)
{
    int ret;
    audio_out_h output;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_out_unprepare(output);
    audio_out_destroy(output);

    return 0;

}

/**
 * @testcase		utc_media_audio_out_prepare_n
 * @since_tizen		2.3
 * @description		Prepare and start of playing audio output.\n
 * 					- Unprepare audio output with invalid parameter.
 */
int utc_media_audio_out_prepare_n(void)
{
    int ret;
    audio_out_h output = NULL;

    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_unprepare_p
 * @since_tizen		2.3
 * @description		Unprepare and stop of playing audio output.\n
 * 					- Create an audio handle of device.\n
 * 					- Prepare audio output.\n
 * 					- Unprepare audio output.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_out_unprepare_p(void)
{
    int ret;
    audio_out_h output;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_unprepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_out_unprepare(output);
    audio_out_destroy(output);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_unprepare_n
 * @since_tizen		2.3
 * @description		Unprepare and stop of playing audio output.\n
 * 					- Unprepare audio output with invalid parameter.
 */
int utc_media_audio_out_unprepare_n(void)
{
    int ret;
    audio_out_h output = NULL;

    ret = audio_out_unprepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_set_stream_cb_p
 * @since_tizen		2.3
 * @description		Set an asynchronous(event) callback function to handle playing data.\n
 * 					- Set stream callback to use async mode.\n
 * 					- Prepare audio output.\n
 * 					- Write audio output buffer.\n
 * 					- Unprepare audio input.
 */
int utc_media_audio_out_set_stream_cb_p(void)
{
    int ret;
    audio_out_h     output = NULL;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    thread_data_s td;
    td.mutex        = &mutex;
    td.cond         = &cond;
    td.callback_ret = -1;

    ret = audio_out_set_stream_cb(output, _audio_out_stream_cb, &td);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    pthread_mutex_lock(&mutex);
    if (td.callback_ret == -1)
        pthread_cond_wait(&cond, &mutex);
    assert_eq(td.callback_ret, AUDIO_IO_ERROR_NONE);
    pthread_mutex_unlock(&mutex);

    audio_out_unprepare(output);
    audio_out_destroy(output);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    assert_eq(td.callback_ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_set_stream_cb_n
 * @since_tizen		2.3
 * @description		Set an asynchronous(event) callback function to handle playing data.\n
 * 					- Set stream callback with invalid parameter.
 */
int utc_media_audio_out_set_stream_cb_n(void)
{
    int ret;

    audio_out_h output = NULL;

    ret = audio_out_set_stream_cb(output, _audio_out_stream_cb, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_unset_stream_cb_p
 * @since_tizen		2.3
 * @description		Unregister the callback function.\n
 * 					- Create an audio handle of device.\n
 * 					- Set stream callback to use async mode.\n
 * 					- Unset stream callback.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_out_unset_stream_cb_p(void)
{
    int ret;

    audio_out_h output = NULL;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_set_stream_cb(output, _audio_out_stream_cb, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    assert(output);
    ret = audio_out_unset_stream_cb(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_out_destroy(output);


    return 0;
}

/**
 * @testcase		utc_media_audio_out_unset_stream_cb_n
 * @since_tizen		2.3
 * @description		Unregister the callback function.\n
 * 					- Unset stream callback function with invalid parameter.
 */
int utc_media_audio_out_unset_stream_cb_n(void)
{
    int ret;

    audio_out_h output = NULL;

    ret = audio_out_unset_stream_cb(output);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_set_sound_stream_info_p
 * @since_tizen		3.0
 * @description		Set the sound stream information to the audio output.\n
 * 					- Create an audio handle of device.\n
 * 					- Create stream information.\n
 * 					- Set stream information.\n
 * 					- Destroy audio handle.\n
 * 					- Destroy stream information.
 */
int utc_media_audio_out_set_sound_stream_info_p(void)
{
    int ret;
    audio_out_h output = NULL;
    sound_stream_info_h stream_info_h = NULL;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _focus_changed_cb, NULL, &stream_info_h);
    ret = audio_out_set_sound_stream_info(output, stream_info_h);

    audio_out_destroy(output);

    sound_manager_destroy_stream_information(stream_info_h);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_set_sound_stream_info_n
 * @since_tizen		3.0
 * @description		Set the sound stream information to the audio output.\n
 * 					- Create an audio handle of device.\n
 * 					- Set stream information with invalid parameter.\n
 * 					- Destroy audio handle.\n
 * 					- Create an audio handle of device.\n
 * 					- Create stream information.\n
 * 					- Set stream information with unsupported stream type.\n
 * 					- Destroy audio handle.\n
 * 					- Destroy stream information.
 */
int utc_media_audio_out_set_sound_stream_info_n(void)
{
    int ret;
    audio_out_h output = NULL;
    sound_stream_info_h stream_info_h = NULL;

    // 1) Check parameters
    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_set_sound_stream_info(NULL, NULL);

    audio_out_destroy(output);

    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    // 2) Check unsupported stream type
    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOICE_RECOGNITION, _focus_changed_cb, NULL, &stream_info_h);  // input only
    ret = audio_out_set_sound_stream_info(output, stream_info_h);

    audio_out_destroy(output);

    sound_manager_destroy_stream_information(stream_info_h);

    assert_eq(ret, AUDIO_IO_ERROR_NOT_SUPPORTED_TYPE);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_pause_p
 * @since_tizen		3.0
 * @description		Pause buffering of audio data from the device.\n
 * 					- Prepare audio output.\n
 * 					- Pause audio output.\n
 * 					- Unprepare audio output.
 */
int utc_media_audio_out_pause_p(void)
{
    int ret;
    audio_out_h output;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_pause(output);

    audio_out_unprepare(output);

    audio_out_destroy(output);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_pause_n1
 * @since_tizen		3.0
 * @description		Pause buffering of audio data from the device.\n
 * 					- Pause audio output with invalid parameter.
 */
int utc_media_audio_out_pause_n1(void)
{
    int ret;
    audio_out_h output = NULL;

    ret = audio_out_pause(output);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_pause_n2
 * @since_tizen		3.0
 * @description		Pause buffering of audio data from the device.\n
 * 					- Pause audio output with invalid state.
 */
int utc_media_audio_out_pause_n2(void)
{
    int ret;
    audio_out_h output = NULL;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_pause(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_pause(output);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_STATE);

    ret = audio_out_unprepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_destroy(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_resume_p
 * @since_tizen		3.0
 * @description		Resume buffering audio data from the device.\n
 * 					- Prepare audio output.\n
 * 					- Pause audio output.\n
 * 					- Resume audio output.\n
 * 					- Unprepare audio output.
 */
int utc_media_audio_out_resume_p(void)
{
    int ret;
    audio_out_h output;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_pause(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_resume(output);

    audio_out_unprepare(output);

    audio_out_destroy(output);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_resume_n1
 * @since_tizen		3.0
 * @description		Resume buffering audio data from the device.\n
 * 					- Resume audio input with invalid parameter.
 */
int utc_media_audio_out_resume_n1(void)
{
    int ret;
    audio_out_h output = NULL;

    ret = audio_out_resume(output);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_resume_n2
 * @since_tizen		3.0
 * @description		Resume buffering audio data from the device.\n
 * 					- Resume audio input with invalid state.
 */
int utc_media_audio_out_resume_n2(void)
{
    int ret;
    audio_out_h output = NULL;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_resume(output);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_STATE);

    ret = audio_out_pause(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_resume(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_resume(output);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_STATE);

    ret = audio_out_unprepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_out_destroy(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_drain_p
 * @since_tizen		2.4
 * @description		Drain buffered audio data from the output stream.\n
 * 					- Prepare audio output.\n
 * 					- Get buffer size.\n
 * 					- Write audio output buffer.\n
 * 					- Drain buffer from audio output stream.\n
 * 					- Unprepare audio output.
 */
int utc_media_audio_out_drain_p(void)
{
    int ret, size, read;
    audio_out_h output;
    char *buffer = NULL;
    FILE *fp = NULL;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_get_buffer_size(output, &size);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    buffer = malloc(size);
    if (buffer == NULL) {
        return 1;
    }

    fp = fopen(AUDIO_PATH,"r");
    if (fp != NULL) {
        read = fread(buffer, size, sizeof(char), fp);
        if (read <= 0) {
            read = size;
            memset(buffer, 0, size);
        }
        fclose(fp);
    } else {
        read = size;
        memset(buffer, 0, size);
    }

    ret = audio_out_write(output, (void*)buffer, read);

    if (buffer) {
        free(buffer);
    }

    assert_gt(ret, 0);

    ret = audio_out_drain(output);

    audio_out_unprepare(output);

    audio_out_destroy(output);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_drain_n
 * @since_tizen		2.4
 * @description		Drain buffered audio data from the output stream.\n
 * 					- Drain buffer with invalid parameter.
 */
int utc_media_audio_out_drain_n(void)
{
    int ret;
    audio_out_h output = NULL;

    ret = audio_out_drain(output);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_flush_p
 * @since_tizen		2.4
 * @description		Flush and discard buffered audio data from the output stream.\n
 * 					- Prepare audio output.\n
 * 					- Get buffer size.\n
 * 					- Write audio output buffer.\n
 * 					- Flush buffer from audio output stream.\n
 * 					- Unprepare audio output.
 * 					- Set stream callback to use async mode.\n
 * 					- Prepare audio output.\n
 * 					- Flush buffer from audio output stream.\n
 * 					- Unprepare audio output.
 */
int utc_media_audio_out_flush_p(void)
{
    int ret, size, read;
    audio_out_h output;
    char *buffer = NULL;
    FILE *fp = NULL;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    // 1) Check sync API
    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_get_buffer_size(output, &size);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    buffer = malloc(size);
    if (buffer == NULL) {
        return 1;
    }

    fp = fopen(AUDIO_PATH,"r");
    if (fp != NULL) {
        read = fread(buffer, size, sizeof(char), fp);
        if (read <= 0) {
            read = size;
            memset(buffer, 0, size);
        }
        fclose(fp);
    } else {
        read = size;
        memset(buffer, 0, size);
    }

    ret = audio_out_write(output, (void*)buffer, read);

    if (buffer) {
        free(buffer);
    }

    assert_gt(ret, 0);

    ret = audio_out_flush(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_out_unprepare(output);

    // 2) Check async API
    ret = audio_out_set_stream_cb(output, _audio_out_stream_cb, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_prepare(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_flush(output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_out_unprepare(output);

    audio_out_destroy(output);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_flush_n
 * @since_tizen		2.4
 * @description		Flush and discard buffered audio data from the output stream.\n
 * 					- Flush buffer with invalid parameter.
 */
int utc_media_audio_out_flush_n(void)
{
    int ret;
    audio_out_h output = NULL;

    ret = audio_out_flush(output);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase		utc_media_audio_out_set_state_changed_cb_p
 * @since_tizen		3.0
 * @description		Sets the state changed callback function to the audio output handle.\n
 * 					- Create an audio handle of device.\n
 * 					- Set state changed callback.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_out_set_state_changed_cb_p(void)
{
    int ret;
    audio_out_h output;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_set_state_changed_cb(output, _audio_io_state_changed_cb, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_out_destroy(output);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_set_state_changed_cb_n
 * @since_tizen		3.0
 * @description		Sets the state changed callback function to the audio output handle.\n
 * 					- Set state changed callback with invalid parameter.
 */
int utc_media_audio_out_set_state_changed_cb_n(void)
{
    int ret;
    audio_out_h output = NULL;

    ret = audio_out_set_state_changed_cb(output, _audio_io_state_changed_cb, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_unset_state_changed_cb_p
 * @since_tizen		3.0
 * @description		Unregisters the state changed callback function of the audio output handle.\n
 * 					- Create an audio handle of device.\n
 * 					- Set state changed callback.\n
 * 					- Unset state changed callback.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_out_unset_state_changed_cb_p(void)
{
    int ret;
    audio_out_h output;

    ret = audio_out_create_new(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &output);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_set_state_changed_cb(output, _audio_io_state_changed_cb, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_out_unset_state_changed_cb(output);

    audio_out_destroy(output);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_out_unset_state_changed_cb_n
 * @since_tizen		3.0
 * @description		Unregisters the state changed callback function of the audio output handle.\n
 * 					- Unset state changed callback with invalid parameter.
 */
int utc_media_audio_out_unset_state_changed_cb_n(void)
{
    int ret;
    audio_out_h output = NULL;

    ret = audio_out_unset_state_changed_cb(output);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}
