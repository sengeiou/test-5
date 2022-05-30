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
#include <unistd.h>
#include <media/streamrecorder.h>
#include <media_packet.h>
#include <storage.h>
#include <system_info.h>

static streamrecorder_h recorder = NULL;

static char* file_path = NULL;
static char* raw_file = "I420_352x288.yuv";

static char* media=".test_record.mp4";
static char* media_path=NULL;
static int count =0;
static media_packet_h vid_pkt = NULL;
static media_format_h media_format = NULL;

static int startup_ret;
static bool is_streamrecorder_supported = false;

static bool storage_device_cb(int storage_id, storage_type_e type, storage_state_e state, const char* path, void* user_data) {

    int size_of_path;

    if (type == STORAGE_TYPE_INTERNAL) {
        size_of_path = strlen(path)+strlen(media)+6;
        media_path = (char*)malloc(size_of_path);
        if (media_path != NULL) {
            snprintf(media_path, size_of_path, "%s/%s", path, media);
        }
        size_of_path = strlen(path)+strlen(raw_file)+6;
        file_path=(char*)malloc(size_of_path);
        if (file_path != NULL) {
            snprintf(file_path, size_of_path, "%s/res/%s", path, raw_file);
        }

        return false;
    }
    return true;
}

static void _event_notified_cb(streamrecorder_state_e previous , streamrecorder_state_e current , streamrecorder_notify_e notification,  void *user_data){
}

static void _recording_status_cb(unsigned long long elapsed_time, unsigned long long file_size,  void *user_data){
}


/**
 * @function            utc_streamrecorder_lifecycle_startup
 * @description         Called before each test. \n
                        This is the precondition for checking apis. \
 * @scenario            creating streamrecorder handle
 * @parameter           N/A
 * @return              N/A
 */
void utc_streamrecorder_lifecycle_startup(void)
{
	startup_ret = STREAMRECORDER_ERROR_NONE;

	storage_foreach_device_supported(storage_device_cb,NULL);

    system_info_get_platform_bool("http://tizen.org/feature/multimedia.stream_recorder", &is_streamrecorder_supported);

	startup_ret |= streamrecorder_create(&recorder);
}


/**
 * @function            utc_streamrecorder_lifecycle_cleanup
 * @description         Called after each test.
                        This is the postcondition for checking apis. \n
                        This postcondition is streamrecorder_destroy api for cleaning up the resources properly.
 * @scenario            1. Destroy streamrecorder.
 * @parameter           N/A
 * @return              N/A

 */
void utc_streamrecorder_lifecycle_cleanup(void)
{
	if (recorder) {
		streamrecorder_destroy(recorder);
		recorder = NULL;
	}
	if (media_path) {
		free(media_path);
		media_path = NULL;
	}
	if (file_path) {
		free(file_path);
		file_path = NULL;
	}

    if (media_format != NULL) {
        media_format_unref(media_format);
        media_format = NULL;
    }
    if (vid_pkt != NULL) {
        media_packet_destroy(vid_pkt);
        vid_pkt = NULL;
    }
}


/**
 * @testcase            utc_streamrecorder_enable_source_buffer_n
 * @description		    To check video recorder with buffer with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_streamrecorder_enable_source_buffer_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_enable_source_buffer(NULL, STREAMRECORDER_SOURCE_VIDEO_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_enable_source_buffer_p
 * @description         To check video recording with buffer with valid parameter.
 * @scenario            This test is for checking valid pointer and parameters.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_enable_source_buffer_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO_AUDIO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_streamrecorder_cancel_p
 * @description		To check streamrecorder cancel with valid parameter.
 * @scenario            This test is for checking valid pointer and parameters.
                            1. set video source as screen \n
                            2. Set video source format I420 \n
                            3. Set file format as MP4. \n
                            4. Set video encoder MPEG4. \n
                            5. Set video resolution \n
                            6. Prepare recorder. \n
                            7. Start recorder. \n
                            8. Cancel recorder. \n
                            9. Destroy recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_cancel_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret  = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
    ret |= streamrecorder_set_video_source_format(recorder, STREAMRECORDER_VIDEO_SOURCE_FORMAT_I420);
    ret |= streamrecorder_set_file_format(recorder, STREAMRECORDER_FILE_FORMAT_MP4);
    ret |= streamrecorder_set_video_encoder(recorder, STREAMRECORDER_VIDEO_CODEC_MPEG4);
    ret |= streamrecorder_set_video_resolution(recorder, 352, 288);
    ret |= streamrecorder_set_video_framerate(recorder, 30);
    ret |= streamrecorder_set_filename(recorder, media_path);
    ret |= streamrecorder_set_notify_cb(recorder, _event_notified_cb, NULL);
    ret |= streamrecorder_set_recording_status_cb(recorder, _recording_status_cb, NULL);
    ret |= streamrecorder_prepare(recorder);
    if (ret != STREAMRECORDER_ERROR_NONE) {
        assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    }
    ret = streamrecorder_start(recorder);
    if (ret != STREAMRECORDER_ERROR_NONE) {
        streamrecorder_unprepare(recorder);
        assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    }
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_cancel(recorder);
    streamrecorder_unprepare(recorder);

    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    return 0;
}

/**
 * @testcase            utc_streamrecorder_cancel_n
 * @description         To check recorder cancel with invalid handle.
 * @scenario            This test is for checking with invalid handle
			            pass recorder handle as NULL
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because precondition does not match.
 */
int utc_streamrecorder_cancel_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_cancel(NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_commit_p
 * @description         To check recorder commit with valid precondition.
 * @scenario            This test is for checking with valid parameters and preconditions.
                            1. set video source as buffer \n
                            2. Set video source format I420n
                            3. Set file format as MP4. \n
                            4. Set video encoder MPEG4. \n
                            5. Set video resolution \n
                            6. Prepare recorder. \n
                            7. Start recorder. \n
                            8. commit recorder \n
                            9. unprepare recorder. \n
                            10. Destroy recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_commit_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    size_t total_ysize = 352 * 288;
    size_t total_uvsize = 352 * 288 / 4;
    size_t read_sum;
    size_t total_read = 0;
    FILE *pvFile = NULL;
    unsigned char *dptr = NULL;
    int i = 0;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    //Create media packet
    media_format_create(&media_format);
    ret = media_format_set_video_mime(media_format, MEDIA_FORMAT_I420);
    if (ret != MEDIA_FORMAT_ERROR_NONE) {
        fprintf(stderr, "Fail to set video mime\n");
        assert_neq(0, 0);
    }
    media_format_set_video_width(media_format, 352);
    media_format_set_video_height(media_format, 288);
    if (media_packet_create(media_format, NULL, NULL, &vid_pkt)) {
        fprintf(stderr, "Fail to create media packet\n");
        assert_neq(0, 0);
    }
    if (media_packet_alloc(vid_pkt)) {
        fprintf(stderr, "Fail to alloc media packet\n");
        assert_neq(0, 0);
    }

    //Read data
    pvFile = fopen(file_path, "rb");
    if (pvFile == NULL) {
        fprintf(stderr, "File open error %s\n", file_path);
        assert_neq(0, 0);
    }

    read_sum = 0;
    media_packet_get_video_plane_data_ptr(vid_pkt, 0, (void**)&dptr);
    while (total_ysize - read_sum)
    {
        read_sum += fread(dptr + read_sum, 1, total_ysize - read_sum, pvFile);

        fprintf(stderr, "Read raw data (read size %d, left %d)\n", read_sum, total_ysize - read_sum);

        if (feof(pvFile)) {
            fprintf(stderr, "EoF occured in reading file\n");
            fclose(pvFile);
            return 1;
        }
        if (ferror(pvFile)) {
            fprintf(stderr, "Error occured in reading file\n");
            fclose(pvFile);
            return 1;
        }
    }
    total_read += read_sum;

    read_sum = 0;
    media_packet_get_video_plane_data_ptr(vid_pkt, 1, (void**)&dptr);
    while (total_uvsize - read_sum)
    {
        read_sum += fread(dptr + read_sum, 1, total_uvsize - read_sum, pvFile);

        fprintf(stderr, "Read raw data (read size %d, left %d)\n", read_sum, total_uvsize - read_sum);

        if (feof(pvFile)) {
            fprintf(stderr, "EoF occured in reading file\n");
            fclose(pvFile);
            return 1;
        }
        if (ferror(pvFile)) {
            fprintf(stderr, "Error occured in reading file\n");
            fclose(pvFile);
            return 1;
        }
    }
    total_read += read_sum;

    read_sum = 0;
    media_packet_get_video_plane_data_ptr(vid_pkt, 2, (void**)&dptr);
    while (total_uvsize - read_sum)
    {
        read_sum += fread(dptr + read_sum, 1, total_uvsize - read_sum, pvFile);

        fprintf(stderr, "Read raw data (read size %d, left %d)\n", read_sum, total_uvsize - read_sum);

        if (feof(pvFile)) {
            fprintf(stderr, "EoF occured in reading file\n");
            fclose(pvFile);
            return 1;
        }
        if (ferror(pvFile)) {
            fprintf(stderr, "Error occured in reading file\n");
            fclose(pvFile);
            return 1;
        }
    }
    total_read += read_sum;
    fclose(pvFile);

    if (media_packet_set_buffer_size(vid_pkt, total_read)) {
        fprintf(stderr, "Fail to set media packet size\n");
        assert_neq(0, 0);
    }

    ret  = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
    ret |= streamrecorder_set_video_source_format(recorder, STREAMRECORDER_VIDEO_SOURCE_FORMAT_I420);
    ret |= streamrecorder_set_file_format(recorder, STREAMRECORDER_FILE_FORMAT_MP4);
    ret |= streamrecorder_set_video_encoder(recorder, STREAMRECORDER_VIDEO_CODEC_MPEG4);
    ret |= streamrecorder_set_video_resolution(recorder, 352, 288);
    ret |= streamrecorder_set_video_framerate(recorder, 30);
    ret |= streamrecorder_set_filename(recorder, media_path);
    ret |= streamrecorder_prepare(recorder);
    if (ret != STREAMRECORDER_ERROR_NONE) {
        assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    }
    ret = streamrecorder_start(recorder);
    if (ret != STREAMRECORDER_ERROR_NONE) {
        streamrecorder_unprepare(recorder);
        assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    }

    for (i = 0; i <10;i++) {
        if (media_packet_set_pts(vid_pkt, count)) {
            fprintf(stderr, "Fail to set media packet PTS\n");
            assert_neq(0, 0);
        }
        streamrecorder_push_stream_buffer(recorder, vid_pkt);
        count = count + 33000000;
    }

    ret = streamrecorder_commit(recorder);
    streamrecorder_unprepare(recorder);

    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    return 0;
}

/**
 * @testcase            utc_streamrecorder_commit_n
 * @description         To check recorder commit with invalid precondition.
 * @scenario            This test is for checking without precondition such as recorder_start. \n
                            1. set video source as screen \n
                            2. Set video source format I420 \n
                            3. Set file format as MP4. \n
                            4. Set video encoder MPEG4. \n
                            5. Set video resolution \n
                            6. Prepare recorder. \n
                            7. Commit recorder. \n
                            8. Unprepare recorder. \n
                            9. Destroy recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because precondition does not match.
 */
int utc_streamrecorder_commit_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret |= streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
    ret |= streamrecorder_set_video_source_format(recorder, STREAMRECORDER_VIDEO_SOURCE_FORMAT_I420);
    ret |= streamrecorder_set_file_format(recorder, STREAMRECORDER_FILE_FORMAT_MP4);
    ret |= streamrecorder_set_video_encoder(recorder, STREAMRECORDER_VIDEO_CODEC_MPEG4);
    ret |= streamrecorder_set_video_resolution(recorder, 1280, 720);
    ret |= streamrecorder_set_filename(recorder, media_path);
    if (ret != STREAMRECORDER_ERROR_NONE) {
        assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    }

    ret = streamrecorder_commit(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_STATE);
    return 0;
}

/**
 * @testcase            utc_streamrecorder_destroy_p
 * @description         To check to destroy recorder with valid precondition.
 * @scenario            This test is for checking with valid precondition
                         destroy recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_destroy_p(void)
{

    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    ret = streamrecorder_destroy(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    recorder = NULL;

    return 0;
}

/**
 * @testcase            utc_streamrecorder_destroy_n
 * @description         To check to destroy recorder with invalid parameter.
 * @scenario            This test is for checking with recorder handle null. \n
                        Destroy recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_streamrecorder_destroy_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_destroy(NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_pause_p
 * @description         To check to pause recorder with valid precondition.
 * @scenario            This test is for checking with valid precondition.
                            1. set video source as screen \n
                            2. Set video source format I420 \n
                            3. Set file format as MP4. \n
                            4. Set video encoder MPEG4. \n
                            5. Set video resolution \n
                            6. Prepare recorder. \n
                            7. Start recorder. \n
                            8. Sleep for a while. \n
                            9. Pause recorder. \n
                            10. Cancel recorder. \n
                            11. Unprepare recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_pause_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;
    size_t total_ysize = 352 * 288;
    size_t total_uvsize = 352 * 288 / 4;
    size_t read_sum;
    size_t total_read = 0;
    FILE *pvFile = NULL;
    unsigned char *dptr = NULL;
    int i = 0;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    //Create media packet
    media_format_create(&media_format);
    ret = media_format_set_video_mime(media_format, MEDIA_FORMAT_I420);
    if (ret != MEDIA_FORMAT_ERROR_NONE) {
        fprintf(stderr, "Fail to set video mime\n");
        assert_neq(0, 0);
    }
    media_format_set_video_width(media_format, 352);
    media_format_set_video_height(media_format, 288);
    if (media_packet_create(media_format, NULL, NULL, &vid_pkt)) {
        fprintf(stderr, "Fail to create media packet\n");
        assert_neq(0, 0);
    }
    if (media_packet_alloc(vid_pkt)) {
        fprintf(stderr, "Fail to alloc media packet\n");
        assert_neq(0, 0);
    }

    //Read data
    pvFile = fopen(file_path, "rb");
    if (pvFile == NULL) {
        fprintf(stderr, "File open error %s\n", file_path);
        assert_neq(0, 0);
    }

    read_sum = 0;
    media_packet_get_video_plane_data_ptr(vid_pkt, 0, (void**)&dptr);
    while (total_ysize - read_sum)
    {
        read_sum += fread(dptr + read_sum, 1, total_ysize - read_sum, pvFile);

        fprintf(stderr, "Read raw data (read size %d, left %d)\n", read_sum, total_ysize - read_sum);

        if (feof(pvFile)) {
            fprintf(stderr, "EoF occured in reading file\n");
            fclose(pvFile);
            return 1;
        }
        if (ferror(pvFile)) {
            fprintf(stderr, "Error occured in reading file\n");
            fclose(pvFile);
            return 1;
        }
    }
    total_read += read_sum;

    read_sum = 0;
    media_packet_get_video_plane_data_ptr(vid_pkt, 1, (void**)&dptr);
    while (total_uvsize - read_sum)
    {
        read_sum += fread(dptr + read_sum, 1, total_uvsize - read_sum, pvFile);

        fprintf(stderr, "Read raw data (read size %d, left %d)\n", read_sum, total_uvsize - read_sum);

        if (feof(pvFile)) {
            fprintf(stderr, "EoF occured in reading file\n");
            fclose(pvFile);
            return 1;
        }
        if (ferror(pvFile)) {
            fprintf(stderr, "Error occured in reading file\n");
            fclose(pvFile);
            return 1;
        }
    }
    total_read += read_sum;

    read_sum = 0;
    media_packet_get_video_plane_data_ptr(vid_pkt, 2, (void**)&dptr);
    while (total_uvsize - read_sum)
    {
        read_sum += fread(dptr + read_sum, 1, total_uvsize - read_sum, pvFile);

        fprintf(stderr, "Read raw data (read size %d, left %d)\n", read_sum, total_uvsize - read_sum);

        if (feof(pvFile)) {
            fprintf(stderr, "EoF occured in reading file\n");
            fclose(pvFile);
            return 1;
        }
        if (ferror(pvFile)) {
            fprintf(stderr, "Error occured in reading file\n");
            fclose(pvFile);
            return 1;
        }
    }
    total_read += read_sum;

    fclose(pvFile);

    if (media_packet_set_buffer_size(vid_pkt, total_read)) {
        fprintf(stderr, "Fail to set media packet size\n");
        assert_neq(0, 0);
    }

    ret |= streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
    ret |= streamrecorder_set_video_source_format(recorder, STREAMRECORDER_VIDEO_SOURCE_FORMAT_I420);
    ret |= streamrecorder_set_file_format(recorder, STREAMRECORDER_FILE_FORMAT_MP4);
    ret |= streamrecorder_set_video_encoder(recorder, STREAMRECORDER_VIDEO_CODEC_MPEG4);
    ret |= streamrecorder_set_video_resolution(recorder, 352, 288);
    ret |= streamrecorder_set_video_framerate(recorder, 30);
    ret |= streamrecorder_set_filename(recorder, media_path);
    ret |= streamrecorder_prepare(recorder);
    if (ret != STREAMRECORDER_ERROR_NONE) {
        assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    }
    ret = streamrecorder_start(recorder);
    if (ret != STREAMRECORDER_ERROR_NONE) {
        streamrecorder_unprepare(recorder);
        assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    }

    for (i = 0; i <10;i++) {
        if (media_packet_set_pts(vid_pkt, count)) {
            fprintf(stderr, "Fail to set media packet PTS\n");
            assert_neq(0, 0);
        }
        streamrecorder_push_stream_buffer(recorder, vid_pkt);
        count = count + 33000000;
    }

    ret = streamrecorder_pause(recorder);
    streamrecorder_cancel(recorder);
    streamrecorder_unprepare(recorder);

    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_pause_n
 * @description         To check to pause recorder with invalid precondition.
 * @scenario            This test is for checking with invalid preconditon such as recorder_start. \n
                            1. set video source as screen \n
                            2. Set video source format I420 \n
                            3. Set file format as MP4. \n
                            4. Set video encoder MPEG4. \n
                            5. Set video resolution \n
                            6. Prepare recorder. \n
                            7. Pause recorder. \n
                            8. Unprepare recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because precondition does not match.
 */
int utc_streamrecorder_pause_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
    ret |= streamrecorder_set_video_source_format(recorder, STREAMRECORDER_VIDEO_SOURCE_FORMAT_I420);
    ret |= streamrecorder_set_file_format(recorder, STREAMRECORDER_FILE_FORMAT_MP4);
    ret |= streamrecorder_set_video_encoder(recorder, STREAMRECORDER_VIDEO_CODEC_MPEG4);
    ret |= streamrecorder_set_video_resolution(recorder, 1280, 720);
    ret |= streamrecorder_set_filename(recorder, media_path);
    ret |= streamrecorder_prepare(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_pause(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_STATE);
    streamrecorder_unprepare(recorder);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_prepare_p
 * @description         To check to prepare recorder with valid precondition.
 * @scenario            This test is for checking with valid precondition. \n
                            1. set video source as buffer \n
                            2. Set video source format I420 \n
                            3. Set file format as MP4. \n
                            4. Set video encoder MPEG4. \n
                            5. Set video resolution \n
                            6. Prepare recorder. \n
                            7. Unprepare recorder. \n
                            8. Destroy recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_prepare_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret |= streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
    ret |= streamrecorder_set_video_source_format(recorder, STREAMRECORDER_VIDEO_SOURCE_FORMAT_I420);
    ret |= streamrecorder_set_file_format(recorder, STREAMRECORDER_FILE_FORMAT_MP4);
    ret |= streamrecorder_set_video_encoder(recorder, STREAMRECORDER_VIDEO_CODEC_MPEG4);
    ret |= streamrecorder_set_video_resolution(recorder, 1280, 720);
    ret |= streamrecorder_set_filename(recorder, media_path);
    ret |= streamrecorder_prepare(recorder);
    if (ret != STREAMRECORDER_ERROR_NONE) {
        assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    }
    streamrecorder_unprepare(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_prepare_n1
 * @description         To check prepare recorder with invalid precondition.
 * @scenario            This test is for checking with invalid precondition. \n
                            1. Prepare recorder. \n
                            2. Prepare recorder again. \n
                            3. Unprepare recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because default setting was not prepared. \n
                        Please check default setting file.
 */
int utc_streamrecorder_prepare_n1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret |= streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
    ret |= streamrecorder_set_video_source_format(recorder, STREAMRECORDER_VIDEO_SOURCE_FORMAT_I420);
    ret |= streamrecorder_set_file_format(recorder, STREAMRECORDER_FILE_FORMAT_MP4);
    ret |= streamrecorder_set_video_encoder(recorder, STREAMRECORDER_VIDEO_CODEC_MPEG4);
    ret |= streamrecorder_set_video_resolution(recorder, 1280, 720);
    ret |= streamrecorder_set_filename(recorder, media_path);
    ret |= streamrecorder_prepare(recorder);
    if (ret != STREAMRECORDER_ERROR_NONE) {
        assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    }

    ret = streamrecorder_prepare(recorder);
    streamrecorder_unprepare(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_prepare_n2
 * @description         To check to prepare recorder with invalid parameter.
 * @scenario            This test is for checking with invalid parameter such as recorder handle null. \n
                        1. Prepare recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_streamrecorder_prepare_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_prepare(NULL);
    assert_eq(ret,STREAMRECORDER_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase            utc_streamrecorder_start_p
 * @description         To check to start recorder with valid precondition.
 * @scenario            This test is for checking with valid precondition. \n
                            1. set video source as screen \n
                            2. Set video source format I420 \n
                            3. Set file format as MP4. \n
                            4. Set video encoder MPEG4. \n
                            5. Set video resolution \n
                            6. Prepare recorder. \n
                            7. Start recorder. \n
                            8. Cancel recorder. \n
                            9. Unprepare recorder. \n
                            10. Destroy recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_start_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret  = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
    ret |= streamrecorder_set_video_source_format(recorder, STREAMRECORDER_VIDEO_SOURCE_FORMAT_I420);
    ret |= streamrecorder_set_file_format(recorder, STREAMRECORDER_FILE_FORMAT_MP4);
    ret |= streamrecorder_set_video_encoder(recorder, STREAMRECORDER_VIDEO_CODEC_MPEG4);
    ret |= streamrecorder_set_video_resolution(recorder, 1280, 720);
    ret |= streamrecorder_set_filename(recorder, media_path);
    ret |= streamrecorder_prepare(recorder);
    if (ret != STREAMRECORDER_ERROR_NONE) {
        assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    }

    ret = streamrecorder_start(recorder);
    if (ret != STREAMRECORDER_ERROR_NONE) {
        streamrecorder_unprepare(recorder);
        assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    }
    streamrecorder_cancel(recorder);
    streamrecorder_unprepare(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_recorder_start_n
 * @description         To check to start recorder with invalid precondition.
 * @scenario            This test is for checking with invalid precondition such as recorder_prepare. \n
                            1. Start recorder. \n
                            2. Destroy recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder_prepare was not called before recorder_start.
 */
int utc_streamrecorder_start_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_start(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase            utc_recorder_unprepare_p
 * @description         To check to unprepare recorder with valid precondition.
 * @scenario            This test is for checking with valid precondition. \n
                            1. set video source as screen \n
                            2. Set video source format I420 \n
                            3. Set file format as MP4. \n
                            4. Set video encoder MPEG4. \n
                            5. Set video resolution \n
                            6. Prepare recorder. \n
                            7. Unprepare recorder. \n
                            8. Destroy recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_unprepare_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret |= streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
    ret |= streamrecorder_set_video_source_format(recorder, STREAMRECORDER_VIDEO_SOURCE_FORMAT_I420);
    ret |= streamrecorder_set_file_format(recorder, STREAMRECORDER_FILE_FORMAT_MP4);
    ret |= streamrecorder_set_video_encoder(recorder, STREAMRECORDER_VIDEO_CODEC_MPEG4);
    ret |= streamrecorder_set_video_resolution(recorder, 1280, 720);
    ret |= streamrecorder_set_filename(recorder, media_path);
    ret |= streamrecorder_prepare(recorder);

    ret = streamrecorder_unprepare(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_recorder_unprepare_n1
 * @description         To check to unprepare recorder with invalid precondition.
 * @scenario            This test is for checking with invalid precondition such as streamrecorder_prepare. \n
                            1. Unprepare recorder. \n
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because precondition does not match.
 */
int utc_streamrecorder_unprepare_n1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_unprepare(recorder);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_unprepare_n2
 * @description         To check to unprepare recorder with invalid parameter.
 * @scenario            This test is for checking with invalid parameter such as recorder handle null. \n
                        1. Unprepare recorder with recorder handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle null.
 */
int utc_streamrecorder_unprepare_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_unprepare(NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase            utc_streamrecorder_get_state_p
 * @description         To check recorder state with valid precondition.
 * @scenario            This test is for checking valid state of recorder. \n
                            1. set videosource as screen
                            2. Get state. \n
                            3. Destroy recorder. \n
 * @parameter          N/A
 * @return             1 is the fail. You need to check log in tct tool. \n
                       0 is the success. \n
                       The "ret" value should be success.
 */
int utc_streamrecorder_get_state_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    streamrecorder_state_e state = STREAMRECORDER_STATE_NONE;
    ret = streamrecorder_enable_source_buffer(recorder, STREAMRECORDER_SOURCE_VIDEO);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_get_state(recorder, &state);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_state_n1
 * @description         To check recorder state with invalid precondition.
 * @scenario            This test is for checking invalid precondition.
                         Get state.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder was not created.
 */
int utc_streamrecorder_get_state_n1(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_get_state(recorder, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_state_n2
 * @description         To check recorder state with invalid precondition and null parameter.
 * @scenario            This test is for checking invalid precondition and null parameter. \n
                        Get state with null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because parameter is null even if this api is getting function.
 */
int utc_streamrecorder_get_state_n2(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    streamrecorder_state_e state = STREAMRECORDER_STATE_NONE;
    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_get_state(NULL, &state);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_mode_p
 * @description		    To check recorder mode with buffer with valid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be success.
 */
int utc_streamrecorder_set_mode_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_mode(recorder, STREAMRECORDER_MODE_DEVICE_LOOPBACK);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_set_mode_n
 * @description		    To check recorder mode with buffer with invalid parameter.
 * @scenario            This test is for checking invalid pointer such as recorder handle null.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder handle is null.
 */
int utc_streamrecorder_set_mode_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_set_mode(NULL, STREAMRECORDER_MODE_DEVICE_LOOPBACK);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase            utc_streamrecorder_get_mode_p
 * @description         To check recorder mode with valid precondition.
 * @scenario            This test is for checking valid mode of recorder. \n
                            1. set mode as loopback mode
                            2. Get mode. \n
                            3. Destroy recorder. \n
 * @parameter          N/A
 * @return             1 is the fail. You need to check log in tct tool. \n
                       0 is the success. \n
                       The "ret" value should be success.
 */
int utc_streamrecorder_get_mode_p(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    streamrecorder_mode_e mode = STREAMRECORDER_MODE_DEVICE_LOOPBACK;
    ret = streamrecorder_set_mode(recorder, mode);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_get_mode(recorder, &mode);
    assert_eq(ret, STREAMRECORDER_ERROR_NONE);
    assert_eq(mode, STREAMRECORDER_MODE_DEVICE_LOOPBACK);

    return 0;
}

/**
 * @testcase            utc_streamrecorder_get_mode_n
 * @description         To check recorder mode with invalid precondition.
 * @scenario            This test is for checking invalid precondition.
                         Get mode.
 * @parameter           N/A
 * @return              1 is the fail. You need to check log in tct tool. \n
                        0 is the success. \n
                        The "ret" value should be error because recorder was not created.
 */
int utc_streamrecorder_get_mode_n(void)
{
    int ret = STREAMRECORDER_ERROR_NONE;

    if (!is_streamrecorder_supported) {
		assert_eq(startup_ret, STREAMRECORDER_ERROR_NOT_SUPPORTED);
		return 0;
	}

    assert_eq(startup_ret, STREAMRECORDER_ERROR_NONE);

    ret = streamrecorder_get_mode(recorder, NULL);
    assert_eq(ret, STREAMRECORDER_ERROR_INVALID_PARAMETER);
    return 0;
}
