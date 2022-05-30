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
#include <system_info.h>
#include <media/audio_io.h>

//& set: Audio Input
#define SAMPLE_RATE_44100 44100
#define SAMPLE_RATE_48000 48000
#define SAMPLE_RATE_192000 192000

#define TEST_SAMPLE_LENGTH 1024

#define MICROPHONE_FEATURE      "http://tizen.org/feature/microphone"

static pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

bool g_bFeatureSupported;

typedef struct _thread_data_s
{
    pthread_mutex_t* mutex;
    pthread_cond_t*  cond;
    int              callback_ret;
    int              peek_ret;
    int              drop_ret;
} thread_data_s;

typedef struct _create_test_condition_s
{
    int sample_rate;
    audio_channel_e channel_type;
    audio_sample_type_e sample_type;
} create_test_condition_s;

static void _audio_in_stream_cb(audio_in_h handle, size_t nbytes, void *userdata)
{
    thread_data_s* td = (thread_data_s*)userdata;
    if (td == NULL) {
        return;
    }

    pthread_mutex_lock(td->mutex);
    td->callback_ret = AUDIO_IO_ERROR_NONE;
    pthread_cond_signal(td->cond);
    pthread_mutex_unlock(td->mutex);
}

static void _audio_in_stream_cb_peek_drop(audio_in_h handle, size_t nbytes, void *userdata)
{
    thread_data_s* td = (thread_data_s*)userdata;
    if (td == NULL) {
        return;
    }

    unsigned int len = nbytes;
    void* peeked_ptr = NULL;

    td->peek_ret = audio_in_peek(handle, (const void **)&peeked_ptr, &len);
    td->drop_ret = audio_in_drop(handle);

    pthread_mutex_lock(td->mutex);
    td->callback_ret = AUDIO_IO_ERROR_NONE;
    pthread_cond_signal(td->cond);
    pthread_mutex_unlock(td->mutex);
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
 * @function		utc_media_audio_in_startup
 * @description		Called before each test.
 * @parameter		NA
 * @return			NA
 */
void utc_media_audio_in_startup(void)
{
	IS_FEATURE_SUPPORTED(MICROPHONE_FEATURE, g_bFeatureSupported, "AUDIO_IO_UTC");
}

/**
 * @function		utc_media_audio_in_cleanup
 * @description		Called after each test.
 * @parameter		NA
 * @return			NA
 */
void utc_media_audio_in_cleanup(void)
{
}

/**
 * @testcase		utc_media_audio_in_create_p
 * @since_tizen		2.3
 * @description		Create an audio handle of device.
 * 					- Create an audio handle of device.\n
 * 					- Destroy audio handle.(repeat)
 */
int utc_media_audio_in_create_p(void)
{
    int ret;
    audio_in_h input = NULL;
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
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S24_LE },      /* since 5.0 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S24_32_LE },   /* since 5.0 */
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_3, AUDIO_SAMPLE_TYPE_S16_LE },     /* since 5.5 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_4, AUDIO_SAMPLE_TYPE_S24_LE },     /* since 5.5 */
        { SAMPLE_RATE_192000, AUDIO_CHANNEL_MULTI_5, AUDIO_SAMPLE_TYPE_S24_32_LE }, /* since 5.5 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_6, AUDIO_SAMPLE_TYPE_S32_LE },     /* since 5.5 */
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_7, AUDIO_SAMPLE_TYPE_S24_LE },     /* since 5.5 */
        { SAMPLE_RATE_192000, AUDIO_CHANNEL_MULTI_8, AUDIO_SAMPLE_TYPE_S32_LE },    /* since 5.5 */
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_9, AUDIO_SAMPLE_TYPE_S16_LE },     /* since 6.5 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_10, AUDIO_SAMPLE_TYPE_S24_LE },    /* since 6.5 */
        { SAMPLE_RATE_192000, AUDIO_CHANNEL_MULTI_11, AUDIO_SAMPLE_TYPE_S24_32_LE },/* since 6.5 */
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_12, AUDIO_SAMPLE_TYPE_S32_LE },    /* since 6.5 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_13, AUDIO_SAMPLE_TYPE_S16_LE },    /* since 6.5 */
        { SAMPLE_RATE_192000, AUDIO_CHANNEL_MULTI_14, AUDIO_SAMPLE_TYPE_S24_LE },   /* since 6.5 */
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_15, AUDIO_SAMPLE_TYPE_S24_32_LE }, /* since 6.5 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_16, AUDIO_SAMPLE_TYPE_S16_LE }     /* since 6.5 */
    };

    for (i = 0; i < sizeof(pcond) / sizeof(create_test_condition_s); i++) {
        ret = audio_in_create(pcond[i].sample_rate, pcond[i].channel_type, pcond[i].sample_type, &input);
        if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
            return 0;
        assert_eq(ret, AUDIO_IO_ERROR_NONE);

        audio_in_destroy(input);
    }

    return 0;
}

/**
 * @testcase		utc_media_audio_in_create_n
 * @since_tizen		2.3
 * @description		Create an audio handle of device.\n
 * 					- Create an audio handle of device with invalid parameters.(repeat)
 */
int utc_media_audio_in_create_n(void)
{
    int ret;
    audio_in_h input = NULL;
    int i;

    create_test_condition_s ncond[] = {
        { SAMPLE_RATE_44100, 0, AUDIO_SAMPLE_TYPE_S16_LE },
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MONO - 1, AUDIO_SAMPLE_TYPE_S16_LE },
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, 0 },
        { 0, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE },
        { SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_U8 - 1 },
        { SAMPLE_RATE_192000 + 1, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S24_32_LE }, /* since 5.0 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_4, AUDIO_SAMPLE_TYPE_S32_LE + 1 },    /* since 5.5 */
        { SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_16 + 1, AUDIO_SAMPLE_TYPE_S24_LE },   /* since 6.5 */
    };

    for (i = 0; i < sizeof(ncond) / sizeof(create_test_condition_s); i++) {
        ret = audio_in_create(ncond[i].sample_rate, ncond[i].channel_type, ncond[i].sample_type, &input);
        assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);
    }

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_destroy_p
 * @since_tizen		2.3
 * @description		Release the audio input handle.\n
 * 					- Create an audio handle of device.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_in_destroy_p(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_destroy(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_destroy_n
 * @since_tizen		2.3
 * @description		Release the audio input handle.\n
 * 					- Destroy audio handle with invalid parameter.
 */
int utc_media_audio_in_destroy_n(void)
{
    int ret;

    ret = audio_in_destroy(NULL);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_read_p
 * @since_tizen		2.3
 * @description		Read audio data from the audio input buffer.\n
 * 					- Prepare audio input.\n
 * 					- Get buffer size.\n
 * 					- Read audio input buffer to allocated buffer.\n
 * 					- Unprepare audio input.
 */
int utc_media_audio_in_read_p(void)
{
    int ret, size;
    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_get_buffer_size(input, &size);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    char *buffer = NULL;
    buffer = malloc(size);

    ret = audio_in_read(input, (void*)buffer, size);

    audio_in_unprepare(input);
    audio_in_destroy(input);

    if (buffer) {
        free (buffer);
    }

    assert_gt(ret, 0);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_read_n
 * @since_tizen		2.3
 * @description		Read audio data from the audio input buffer.\n
 * 					- Prepare audio input.\n
 * 					- Get buffer size.\n
 * 					- Read audio input buffer with invalid parameter.\n
 * 					- Unprepare audio input.\n
 * 					- Set stream callback to use async mode.\n
 * 					- Prepare audio input.\n
 * 					- Get buffer size.\n
 * 					- Read audio input buffer using sync API.
 * 					- Unprepare audio input.\n
 */
int utc_media_audio_in_read_n1(void)
{
    int ret, size;
    audio_in_h input = NULL;
    char *buffer = NULL;

    // 1) Check sync API
    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_get_buffer_size(input, &size);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_read(input, (void*)buffer, 0);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    audio_in_unprepare(input);

    audio_in_destroy(input);

    // 2) Check async API
    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_set_stream_cb(input, _audio_in_stream_cb_peek_drop, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_get_buffer_size(input, &size);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    buffer = malloc(size);

    ret = audio_in_read(input, (void*)buffer, size);

    audio_in_unprepare(input);
    audio_in_destroy(input);

    if (buffer) {
        free(buffer);
    }

    assert_eq(ret, AUDIO_IO_ERROR_INVALID_OPERATION);

    return 0;
}


/**
 * @testcase		utc_media_audio_in_read_n2
 * @since_tizen		2.3
 * @description		Check whether audio_in_read return invalid operation error properly.
 */
int utc_media_audio_in_read_n2(void)
{
    int ret;
    char buffer[TEST_SAMPLE_LENGTH];
    audio_in_h input = NULL;

    /* pre */
    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    /* check #1 : read before prepare */
    ret = audio_in_read(input, (void*)buffer, TEST_SAMPLE_LENGTH);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_OPERATION);

    /* check #2 : read after pause */
    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_in_pause(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_in_read(input, (void*)buffer, TEST_SAMPLE_LENGTH);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_OPERATION);

    /* check #3 : read after unprepare */
    ret = audio_in_unprepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_in_read(input, (void*)buffer, TEST_SAMPLE_LENGTH);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_OPERATION);

    /* cleanup */
    ret = audio_in_destroy(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_get_buffer_size_p
 * @since_tizen		2.3
 * @description		Get the size to be allocated for the audio input buffer.\n
 * 					- Create an audio handle of device.\n
 * 					- Get buffer size of audio input buffer.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_in_get_buffer_size_p(void)
{
    int ret, size;
    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_get_buffer_size(input, &size);

    audio_in_destroy(input);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_get_buffer_size_n
 * @since_tizen		2.3
 * @description		Get the size to be allocated for the audio input buffer.\n
 * 					- Create an audio handle of device.\n
 * 					- Get buffer size of audio input buffer with invalid parameter.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_in_get_buffer_size_n(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_get_buffer_size(input, NULL);

    audio_in_destroy(input);

    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;

}

/**
 * @testcase		utc_media_audio_in_get_sample_rate_p
 * @since_tizen		2.3
 * @description		Get the sample rate of the audio input stream.\n
 * 					- Create an audio handle of device.\n
 * 					- Get sample rate of audio input stream.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_in_get_sample_rate_p(void)
{
    int ret;
    audio_in_h input = NULL;
    int sample_rate;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_get_sample_rate(input, &sample_rate);

    audio_in_destroy(input);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_get_sample_rate_n
 * @since_tizen		2.3
 * @description		Get the sample rate of the audio input stream.\n
 * 					- Get sample rate of audio input stream with invalid parameter.
 */
int utc_media_audio_in_get_sample_rate_n(void)
{
    int ret, sample_rate;
    audio_in_h input = NULL;

    ret = audio_in_get_sample_rate(input, &sample_rate);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_get_channel_p
 * @since_tizen		2.3
 * @description		Get the channel type of the audio input stream.\n
 * 					- Create an audio handle of device.\n
 * 					- Get channel type of audio input stream.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_in_get_channel_p(void)
{
    int ret;
    audio_in_h input = NULL;
    audio_channel_e channel;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_get_channel(input, &channel);

    audio_in_destroy(input);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_get_channel_n
 * @since_tizen		2.3
 * @description		Get the channel type of the audio input stream.\n
 * 					- Get channel type of audio input stream with invalid parameter.
 */
int utc_media_audio_in_get_channel_n(void)
{
    int ret;
    audio_channel_e channel;
    audio_in_h input = NULL;

    ret = audio_in_get_channel(input, &channel);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_get_sample_type_p
 * @since_tizen		2.3
 * @description		Get the sample audio format of the audio input stream.\n
 * 					- Create an audio handle of device.\n
 * 					- Get sample format of audio input stream.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_in_get_sample_type_p(void)
{
    int ret;
    audio_in_h input = NULL;
    audio_sample_type_e type;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_get_sample_type(input, &type);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_in_destroy(input);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_get_sample_type_n
 * @since_tizen		2.3
 * @description		Get the sample audio format of the audio input stream.\n
 * 					- Get sample format of audio input stream with invalid parameter.
 */
int utc_media_audio_in_get_sample_type_n(void)
{
    int ret;
    audio_sample_type_e type;
    audio_in_h input = NULL;

    ret = audio_in_get_sample_type(input, &type);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_prepare_p
 * @since_tizen		2.3
 * @description		Prepare and start of reading audio input.\n
 * 					- Create an audio handle of device.\n
 * 					- Prepare audio input.\n
 * 					- Unprepare audio input.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_in_prepare_p(void)
{
    int ret;
    audio_in_h input = NULL;
    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);

    audio_in_unprepare(input);
    audio_in_destroy(input);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_prepare_n
 * @since_tizen		2.3
 * @description		Prepare and start of reading audio input.\n
 * 					- Unprepare audio input with invalid parameter.
 */
int utc_media_audio_in_prepare_n(void)
{
    int ret;
    audio_in_h input = NULL;
    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_unprepare_p
 * @since_tizen		2.3
 * @description		Unprepare and stop of reading audio input.\n
 * 					- Create an audio handle of device.\n
 * 					- Prepare audio input.\n
 * 					- Unprepare audio input.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_in_unprepare_p(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);
    ret = audio_in_unprepare(input);

    audio_in_destroy(input);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_unprepare_n
 * @since_tizen		2.3
 * @description		Unprepare and stop of reading audio input.\n
 * 					- Unprepare audio input with invalid parameter.
 */
int utc_media_audio_in_unprepare_n(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_unprepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_set_stream_cb_p
 * @since_tizen		2.3
 * @description		Set an asynchronous(event) callback function to handle recording data.\n
 * 					- Set stream callback to use async mode.\n
 * 					- Prepare audio input.\n
 * 					- Read audio input buffer.\n
 * 					- Unprepare audio input.
 */
int utc_media_audio_in_set_stream_cb_p(void)
{
    int ret;
    audio_in_h      input = NULL;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    thread_data_s td;
    td.mutex        = &mutex;
    td.cond         = &cond;
    td.callback_ret = -1;

    ret = audio_in_set_stream_cb(input, _audio_in_stream_cb, &td);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);

    audio_in_unprepare(input);
    audio_in_destroy(input);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    assert_eq(td.callback_ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_set_stream_cb_n
 * @since_tizen		2.3
 * @description		Set an asynchronous(event) callback function to handle recording data.\n
 * 					- Set stream callback with invalid parameter.
 */
int utc_media_audio_in_set_stream_cb_n(void)
{
    int ret;

    audio_in_h input = NULL;

    ret = audio_in_set_stream_cb(input, _audio_in_stream_cb, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_unset_stream_cb_p
 * @since_tizen		2.3
 * @description		Unregister the callback function.\n
 * 					- Create an audio handle of device.\n
 * 					- Set stream callback to use async mode.\n
 * 					- Unset stream callback.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_in_unset_stream_cb_p(void)
{
    int ret;

    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_set_stream_cb(input, _audio_in_stream_cb, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    assert(input);
    ret = audio_in_unset_stream_cb(input);

    audio_in_destroy(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_unset_stream_cb_n
 * @since_tizen		2.3
 * @description		Unregister the callback function.\n
 * 					- Unset stream callback function with invalid parameter.
 */
int utc_media_audio_in_unset_stream_cb_n(void)
{
    int ret;

    audio_in_h input = NULL;

    ret = audio_in_unset_stream_cb(input);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_peek_p
 * @since_tizen		2.3
 * @description		Peek from audio in buffer.\n
 * 					- Set stream callback to use async mode.\n
 * 					- Prepare audio input.\n
 * 					- Peek buffer from audio input stream.\n
 * 					- Unprepare audio input.
 */
int utc_media_audio_in_peek_p(void)
{
    int ret, ret_peek;
    audio_in_h      input = NULL;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    thread_data_s td;
    td.mutex    = &mutex;
    td.cond     = &cond;
    td.peek_ret = -1;
    td.drop_ret = -1;

    ret = audio_in_set_stream_cb(input, _audio_in_stream_cb_peek_drop, &td);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);

    ret_peek = td.peek_ret;

    audio_in_unprepare(input);
    audio_in_destroy(input);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    assert_eq(ret_peek, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_peek_n1
 * @since_tizen		2.3
 * @description		Peek from audio in buffer.\n
 * 					- Peek buffer with invalid parameter.\n
 * 					- Prepare audio input.\n
 * 					- Peek buffer from audio input stream in sync mode.(not support peek in sync mode)\n
 * 					- Unprepare audio input.
 */
int utc_media_audio_in_peek_n1(void)
{
    int ret;
    audio_in_h input = NULL;
    void* buf = NULL;
    unsigned int len = 0;

    // 1) Check NULL pointer
    ret = audio_in_peek(input, (const void **)&buf, &len);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    // 2) Check async API
    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    buf = malloc(sizeof(char)*1024);
    len = 1024;

    ret = audio_in_peek(input, (const void **)&buf, &len);
    if (buf) {
        free(buf);
    }

    assert_eq(ret, AUDIO_IO_ERROR_INVALID_OPERATION);

    audio_in_unprepare(input);
    audio_in_destroy(input);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_peek_n2
 * @since_tizen		2.3
 * @description		Peek from audio in buffer.\n
 * 					- Set stream callback to use async mode.\n
 * 					- Prepare audio input.\n
 * 					- Peek buffer with invalid parameters.\n
 * 					- Unprepare audio input.
 */
int utc_media_audio_in_peek_n2(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_set_stream_cb(input, _audio_in_stream_cb_peek_drop, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    void** buf = NULL; // invalid out-parameter type (use void* buf)
    unsigned int* len = NULL; // invalid out-parameter type (use int len)

    ret = audio_in_peek(input, (const void **)buf, len); // This is same code as "ret = audio_in_peek(input, NULL, NULL);"
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    audio_in_unprepare(input);
    audio_in_destroy(input);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_peek_n3
 * @since_tizen		2.3
 * @description		Peek from audio in buffer.\n
 * 					- Set stream callback to use async mode.\n
 * 					- Prepare audio input.\n
 * 					- Peek buffer from audio input stream.\n
 * 					- Check Buffers.\n
 * 					- Unprepare audio input.
 */
int utc_media_audio_in_peek_n3(void)
{
    int ret;
    audio_in_h input = NULL;
    unsigned int len = 1024;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_set_stream_cb(input, _audio_in_stream_cb_peek_drop, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    void* buf = malloc(sizeof(char)*len);
    void* origin_buf = buf;

    // memory leak
    ret = audio_in_peek(input, (const void **)&buf, &len);

    audio_in_unprepare(input);
    audio_in_destroy(input);

    if (buf == origin_buf) {
        free(origin_buf);
        return 1;
    }
    free(origin_buf);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_drop_p
 * @since_tizen		2.3
 * @description		Drop peeked audio buffer.\n
 * 					- Set stream callback to use async mode.\n
 * 					- Prepare audio input.\n
 * 					- Peek buffer from audio input stream.\n
 * 					- Drop buffer from audio input stream.\n
 * 					- Unprepare audio input.
 */
int utc_media_audio_in_drop_p(void)
{
    int ret, ret_peek, ret_drop;
    audio_in_h input = NULL;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    thread_data_s td;
    td.mutex    = &mutex;
    td.cond     = &cond;
    td.peek_ret = -1;
    td.drop_ret = -1;

    ret = audio_in_set_stream_cb(input, _audio_in_stream_cb_peek_drop, &td);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);

    ret_peek = td.peek_ret;
    ret_drop = td.drop_ret;

    audio_in_unprepare(input);
    audio_in_destroy(input);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    assert_eq(ret_peek, AUDIO_IO_ERROR_NONE);
    assert_eq(ret_drop, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_drop_n
 * @since_tizen		2.3
 * @description		Drop peeked audio buffer.\n
 * 					- Drop buffer with invalid parameters.\n
 * 					- Prepare audio input.\n
 * 					- Drop buffer from audio input stream in sync mode.(not support drop in sync mode)\n
 * 					- Unprepare audio input.
 */
int utc_media_audio_in_drop_n(void)
{
    int ret;
    audio_in_h input = NULL;

    // 1) Check NULL pointer
    ret = audio_in_drop(input);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    // 2) Check sync API
    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_drop(input);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_OPERATION);

    audio_in_unprepare(input);
    audio_in_destroy(input);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_set_sound_stream_info_p
 * @since_tizen		3.0
 * @description		Set the sound stream information to the audio input.\n
 * 					- Create an audio handle of device.\n
 * 					- Create stream information.\n
 * 					- Set stream information.\n
 * 					- Destroy audio handle.\n
 * 					- Destroy stream information.
 */
int utc_media_audio_in_set_sound_stream_info_p(void)
{
    int ret;
    audio_in_h input = NULL;
    sound_stream_info_h stream_info_h = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _focus_changed_cb, NULL, &stream_info_h);
    ret = audio_in_set_sound_stream_info(input, stream_info_h);

    audio_in_destroy(input);

    sound_manager_destroy_stream_information(stream_info_h);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_set_sound_stream_info_n
 * @since_tizen		3.0
 * @description		Set the sound stream information to the audio input.\n
 * 					- Create an audio handle of device.\n
 * 					- Set stream information with invalid parameter.\n
 * 					- Destroy audio handle.\n
 * 					- Create an audio handle of device.\n
 * 					- Create stream information.\n
 * 					- Set stream information with unsupported stream type.\n
 * 					- Destroy audio handle.\n
 * 					- Destroy stream information.
 */
int utc_media_audio_in_set_sound_stream_info_n(void)
{
    int ret;
    audio_in_h input = NULL;
    sound_stream_info_h stream_info_h = NULL;

    // 1) Check parameters
    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_set_sound_stream_info(NULL, NULL);

    audio_in_destroy(input);

    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    // 2) Check unsupported stream type
    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    sound_manager_create_stream_information(SOUND_STREAM_TYPE_SYSTEM, _focus_changed_cb, NULL, &stream_info_h);  // output only
    ret = audio_in_set_sound_stream_info(input, stream_info_h);

    audio_in_destroy(input);

    sound_manager_destroy_stream_information(stream_info_h);

    assert_eq(ret, AUDIO_IO_ERROR_NOT_SUPPORTED_TYPE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_pause_p
 * @since_tizen		3.0
 * @description		Pause buffering of audio data from the device.\n
 * 					- Prepare audio input.\n
 * 					- Pause audio input.\n
 * 					- Unprepare audio input.
 */
int utc_media_audio_in_pause_p(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_pause(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_in_unprepare(input);

    audio_in_destroy(input);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_pause_n1
 * @since_tizen		3.0
 * @description		Pause buffering of audio data from the device.\n
 * 					- Pause audio input with invalid parameter.
 */
int utc_media_audio_in_pause_n1(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_pause(input);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_pause_n2
 * @since_tizen		3.0
 * @description		Pause buffering of audio data from the device.\n
 * 					- Pause audio input with invalid state.
 */
int utc_media_audio_in_pause_n2(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_pause(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_pause(input);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_STATE);

    ret = audio_in_unprepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_destroy(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}


/**
 * @testcase		utc_media_audio_in_resume_p
 * @since_tizen		3.0
 * @description		Resume buffering audio data from the device.\n
 * 					- Prepare audio input.\n
 * 					- Pause audio input.\n
 * 					- Resume audio input.\n
 * 					- Unprepare audio input.
 */
int utc_media_audio_in_resume_p(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_pause(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_resume(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_in_unprepare(input);

    audio_in_destroy(input);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_resume_n1
 * @since_tizen		3.0
 * @description		Resume buffering audio data from the device.\n
 * 					- Resume audio input with invalid parameter.
 */
int utc_media_audio_in_resume_n1(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_resume(input);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_resume_n2
 * @since_tizen		3.0
 * @description		Resume buffering audio data from the device.\n
 * 					- Resume audio input with invalid state.
 */
int utc_media_audio_in_resume_n2(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_resume(input);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_STATE);

    ret = audio_in_pause(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_resume(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_resume(input);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_STATE);

    ret = audio_in_unprepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_destroy(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}


/**
 * @testcase		utc_media_audio_in_flush_p
 * @since_tizen		2.4
 * @description		Flush and discard buffered audio data from the input stream.\n
 * 					- Prepare audio input.\n
 * 					- Flush buffer from audio input stream.\n
 * 					- Unprepare audio input.\n
 * 					- Set stream callback to use async mode.\n
 * 					- Prepare audio input.\n
 * 					- Flush buffer from audio input stream.\n
 * 					- Unprepare audio input.
 */
int utc_media_audio_in_flush_p(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    // 1) Check sync API
    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_flush(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_in_unprepare(input);

    // 2) Check async API
    ret = audio_in_set_stream_cb(input, _audio_in_stream_cb_peek_drop, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_prepare(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_flush(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    audio_in_unprepare(input);

    audio_in_destroy(input);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_flush_n
 * @since_tizen		2.4
 * @description		Flush and discard buffered audio data from the input stream.\n
 * 					- Flush buffer with invalid parameter.
 */
int utc_media_audio_in_flush_n(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_flush(input);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_set_state_changed_cb_p
 * @since_tizen		3.0
 * @description		Sets the state changed callback function to the audio input handle.\n
 * 					- Create an audio handle of device.\n
 * 					- Set state changed callback.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_in_set_state_changed_cb_p(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_set_state_changed_cb(input, _audio_io_state_changed_cb, NULL);

    audio_in_destroy(input);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_set_state_changed_cb_n
 * @since_tizen		3.0
 * @description		Sets the state changed callback function to the audio input handle.\n
 * 					- Set state changed callback with invalid parameter.
 */
int utc_media_audio_in_set_state_changed_cb_n(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_set_state_changed_cb(input, _audio_io_state_changed_cb, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_unset_state_changed_cb_p
 * @since_tizen		3.0
 * @description		Unregisters the state changed callback function of the audio input handle.\n
 * 					- Create an audio handle of device.\n
 * 					- Set state changed callback.\n
 * 					- Unset state changed callback.\n
 * 					- Destroy audio handle.
 */
int utc_media_audio_in_unset_state_changed_cb_p(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_set_state_changed_cb(input, _audio_io_state_changed_cb, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    ret = audio_in_unset_state_changed_cb(input);

    audio_in_destroy(input);

    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_unset_state_changed_cb_n
 * @since_tizen		3.0
 * @description		Unregisters the state changed callback function of the audio input handle.\n
 * 					- Unset state changed callback with invalid parameter.
 */
int utc_media_audio_in_unset_state_changed_cb_n(void)
{
    int ret;
    audio_in_h input = NULL;

    ret = audio_in_unset_state_changed_cb(input);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_set_volume_p
 * @since_tizen		6.0
 * @description		Set audio recording volume with valid parameters.
 */
int utc_media_audio_in_set_volume_p(void)
{
    int i;
    int ret;
    audio_in_h input = NULL;
    double pcond[] = { 0.0, 2.0, 0.7, 1.5 };

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    for (i = 0; i < sizeof(pcond) / sizeof(double); i++) {
        ret = audio_in_set_volume(input, pcond[i]);
        assert_eq(ret, AUDIO_IO_ERROR_NONE);
    }

    ret = audio_in_destroy(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_set_volume_n
 * @since_tizen		6.0
 * @description		Set audio recording volume with invalid parameters.\n
 * 					- Check if the invalid parameter error is returned with given null handle.\n
 * 					- Check if the invalid parameter error is returned with given invalid volume.
 */
int utc_media_audio_in_set_volume_n(void)
{
    int i;
    int ret;
    audio_in_h input = NULL;
    double ncond[] = { -1.0, 3.0 };

    /* checks null handle */
    ret = audio_in_set_volume(NULL, 1.0);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    /* checks invalid volume */
    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    for (i = 0; i < sizeof(ncond) / sizeof(double); i++) {
        ret = audio_in_set_volume(input, ncond[i]);
        assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);
    }

    ret = audio_in_destroy(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_get_volume_p
 * @since_tizen		6.0
 * @description		Get audio recording volume and checks whether it is properly set.\n
 * 					- Check if the returned volume is same as what we set before.
 */
int utc_media_audio_in_get_volume_p(void)
{
    int i;
    int ret;
    double volume;
    audio_in_h input = NULL;
    double pcond[] = { 0.0, 2.0, 0.7, 1.5 };

    ret = audio_in_create(SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &input);
    if (ret == AUDIO_IO_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false)
        return 0;
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    for (i = 0; i < sizeof(pcond) / sizeof(double); i++) {
        ret = audio_in_set_volume(input, pcond[i]);
        assert_eq(ret, AUDIO_IO_ERROR_NONE);

        ret = audio_in_get_volume(input, &volume);
        assert_eq(volume, pcond[i]);
    }

    ret = audio_in_destroy(input);
    assert_eq(ret, AUDIO_IO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_audio_in_get_volume_n
 * @since_tizen		6.0
 * @description		Get audio recording volume with invalid parameter.
 */
int utc_media_audio_in_get_volume_n(void)
{
    int ret = audio_in_get_volume(NULL, NULL);
    assert_eq(ret, AUDIO_IO_ERROR_INVALID_PARAMETER);

    return 0;
}
