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
#include <storage.h>
#include <system_info.h>

#define MAX_FORMAT 10
static char* media=".test_record.mp4";
static char* media_path=NULL;

static streamrecorder_h recorder = NULL;
static int startup_ret;
static bool is_streamrecorder_supported = false;
static media_format_h media_format = NULL;
static media_packet_h out_pkt = NULL;
static media_format_h media_audio_format = NULL;
static media_packet_h aud_pkt = NULL;

static bool storage_device_cb(int storage_id, storage_type_e type, storage_state_e state, const char* path, void* user_data) {

    int size_of_path;

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
 * @function            utc_streamrecorder_buffer_startup
 * @description         Called before each test. \n
                        This is the precondition for checking apis. \n
                        Tiis precondition is create streamrecorder
 * @scenario            1. Check device storage supported. \n
                        2. Create streamrecorder
 * @parameter           N/A
 * @return              N/A
 */
void utc_streamrecorder_buffer_startup(void)
{
    startup_ret = STREAMRECORDER_ERROR_NONE;
    storage_foreach_device_supported(storage_device_cb,NULL);
    system_info_get_platform_bool("http://tizen.org/feature/multimedia.stream_recorder", &is_streamrecorder_supported);
    startup_ret = streamrecorder_create(&recorder);

}

/**
 * @function            utc_streamrecorder_buffer_cleanup
 * @description         Called after each test. \n
                        This is the postcondition for checking apis. \n
                        This postcondition is streamrecorder_destroy for cleaning up all recorder resources for next test.
 * @scenario             Destroy recorder.
 * @parameter           N/A
 * @return              N/A
 */
void utc_streamrecorder_buffer_cleanup(void)
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
 * @testcase            utc_streamrecorder_push_stream_buffer_p
 * @description         To check the api  with valid parameters
 * @scenario            This test is for checking parameters valid or not. \n
                        1. set videosource as buffer
                        2. create media packet
                        3. call push stream buffer
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_push_stream_buffer_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    if (media_format_create(&media_format)) {
        return 1;
    }

    ret = media_format_set_video_mime(media_format, MEDIA_FORMAT_I420);
    if (ret != MEDIA_FORMAT_ERROR_NONE) {
        assert_neq(0, 0);
    }

    media_format_set_video_width(media_format, 352);
    media_format_set_video_height(media_format, 288);

    if (media_packet_create(media_format, NULL, NULL, &out_pkt)) {
        return 1;
    }
    if (media_packet_alloc(out_pkt)) {
        return 1;
    }

    media_format_create(&media_audio_format);
    media_format_set_audio_mime(media_audio_format, MEDIA_FORMAT_PCM);
    media_format_set_audio_samplerate(media_audio_format, 48000);
    media_format_set_audio_channel(media_audio_format, 2);
    media_format_set_audio_bit(media_audio_format, 16);
    media_format_set_audio_avg_bps(media_audio_format, 128000);

    media_packet_create(media_audio_format, NULL, NULL, &aud_pkt);
    media_packet_alloc(aud_pkt);

    assert_neq(NULL, out_pkt);
    ret  = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
    ret |= streamrecorder_set_video_source_format(recorder, STREAMRECORDER_VIDEO_SOURCE_FORMAT_I420);
    ret |= streamrecorder_set_file_format(recorder, STREAMRECORDER_FILE_FORMAT_MP4);
    ret |= streamrecorder_set_video_encoder(recorder, STREAMRECORDER_VIDEO_CODEC_MPEG4);
    ret |= streamrecorder_set_video_resolution(recorder, 1280, 720);
    ret |= streamrecorder_set_filename(recorder, media_path);
    ret |= streamrecorder_prepare(recorder);
    ret = streamrecorder_start(recorder);
    ret = streamrecorder_push_stream_buffer(recorder, out_pkt);
    ret = streamrecorder_push_stream_buffer(recorder, aud_pkt);
    streamrecorder_cancel(recorder);
    streamrecorder_unprepare(recorder);
    media_format_unref(media_format);
    media_packet_destroy(out_pkt);

    media_format_unref(media_audio_format);
    media_packet_destroy(aud_pkt);

    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_push_stream_buffer_n
 * @description         To check the api  with recorder handle NULL
 * @scenario            This test is for checking api with invalid parameters. \n
                        1. set videosource as buffer
                        2. create media packet
                        3. call push stream buffer  with recorder handle NULL
 * @parameter           N/A
 * @return              1 is the fail. You need  to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_push_stream_buffer_n(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);
    if (media_format_create(&media_format)) {
        assert_neq(0, 0);
    }

    ret = media_format_set_video_mime(media_format, MEDIA_FORMAT_I420);
    if (ret != MEDIA_FORMAT_ERROR_NONE) {
        assert_neq(0, 0);
    }

    media_format_set_video_width(media_format, 352);
    media_format_set_video_height(media_format, 288);

    if (media_packet_create(media_format, NULL, NULL, &out_pkt)) {
        assert_neq(0, 0);
    }
    if (media_packet_alloc(out_pkt)) {
        assert_neq(0, 0);
    }

    assert_neq(NULL, out_pkt);
    streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
    ret = streamrecorder_push_stream_buffer(NULL, out_pkt);
    media_format_unref(media_format);
    media_packet_destroy(out_pkt);

    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;

}
