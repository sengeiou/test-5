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
#include <media/media_packet.h>
#include <media/media_format.h>
#include <media/media_packet_pool.h>

#include <tbm_surface.h>

static media_format_h format = NULL;
static media_format_h format_audio = NULL;
static media_format_h format_for_tbm = NULL;
static media_format_h format_text = NULL;
static media_format_h empty_format = NULL;
static media_packet_h packet;
static media_packet_h packet2;
static media_packet_h pkt_create_alloc;
static media_packet_h pkt_create_alloc_tbm;
static media_packet_h pkt_new_alloc;
static media_packet_pool_h pool;

static bool finalizeCB_called = false;
static bool disposeCB_called = false;

static int _finalize_callback(media_packet_h packet, int err, void *userdata);
static void _dispose_callback(media_packet_h packet, void *userdata);

/**
 * @function		utc_media_packet_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_packet_startup(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	if (media_format_create(&format) == MEDIA_FORMAT_ERROR_NONE) {
		ret = media_format_set_video_mime(format, MEDIA_FORMAT_H264_HP);
		ret |= media_format_set_video_width(format, 480);
		ret |= media_format_set_video_height(format, 640);
		ret |= media_format_set_video_avg_bps(format, 10000000);
		ret |= media_format_set_video_max_bps(format, 15000000);
		ret |= media_format_set_video_frame_rate(format, 30);
		if (ret != MEDIA_FORMAT_ERROR_NONE)
			fprintf(stderr, "video format failed[0x%x]", ret);
	}

	if (media_format_create(&format_audio) == MEDIA_FORMAT_ERROR_NONE) {
		ret = media_format_set_audio_mime(format_audio, MEDIA_FORMAT_AAC_LC);
		ret |= media_format_set_audio_channel(format_audio, 2);
		ret |= media_format_set_audio_samplerate(format_audio, 20000);
		ret |= media_format_set_audio_bit(format_audio, 200000);
		ret |= media_format_set_audio_avg_bps(format_audio, 1000000);
		ret |= media_format_set_audio_aac_type(format_audio, false);
		ret |= media_format_set_audio_aac_header_type(format_audio, MEDIA_FORMAT_AAC_HEADER_ADIF);
		if (ret != MEDIA_FORMAT_ERROR_NONE)
			fprintf(stderr, "audio format failed[0x%x]", ret);

	}

	if (media_format_create(&format_for_tbm) == MEDIA_FORMAT_ERROR_NONE) {
		ret = media_format_set_video_mime(format_for_tbm, MEDIA_FORMAT_I420);
		ret |= media_format_set_video_width(format_for_tbm, 128);
		ret |= media_format_set_video_height(format_for_tbm, 128);
		ret |= media_format_set_video_avg_bps(format_for_tbm, 10000000);
		ret |= media_format_set_video_max_bps(format_for_tbm, 15000000);
		if (ret != MEDIA_FORMAT_ERROR_NONE)
			fprintf(stderr, "video format for tbm failed[0x%x]", ret);
	}

	if (media_format_create(&empty_format) != MEDIA_FORMAT_ERROR_NONE)
		fprintf(stderr, "media_format_create , empty_format failed!");

	if (media_format_create(&format_text) == MEDIA_FORMAT_ERROR_NONE) {
		ret = media_format_set_text_mime(format_text, MEDIA_FORMAT_TEXT_MP4);
		ret |= media_format_set_text_type(format_text, MEDIA_FORMAT_TEXT_TYPE_TIMED_TEXT_3GPP);
		if (ret != MEDIA_FORMAT_ERROR_NONE)
			fprintf(stderr, "media_format_set_text_xxxx failed!");
	}

	if (media_packet_create_alloc(format, NULL, NULL, &pkt_create_alloc) != MEDIA_PACKET_ERROR_NONE)
		fprintf(stderr, "media_packet_create_alloc , pkt_create_alloc failed!");

	if (media_packet_create_alloc(format_for_tbm, NULL, NULL, &pkt_create_alloc_tbm) != MEDIA_PACKET_ERROR_NONE)
		fprintf(stderr, "media_packet_create_alloc , pkt_create_alloc_tbm failed!");

	if (media_packet_new_alloc(format, _dispose_callback, NULL, &pkt_new_alloc) != MEDIA_PACKET_ERROR_NONE)
		fprintf(stderr, "media_packet_new_alloc , pkt_new_alloc failed!");
}

/**
 * @function		utc_media_packet_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_packet_cleanup(void)
{
	if (pkt_new_alloc) {
		media_packet_unref(pkt_new_alloc);
		pkt_new_alloc = NULL;
	}
	if (pkt_create_alloc_tbm) {
		media_packet_destroy(pkt_create_alloc_tbm);
		pkt_create_alloc_tbm = NULL;
	}
	if (pkt_create_alloc) {
		media_packet_destroy(pkt_create_alloc);
		pkt_create_alloc = NULL;
	}
	if (empty_format) {
		media_format_unref(empty_format);
		empty_format = NULL;
	}
	if (format) {
		media_format_unref(format);
		format = NULL;
	}
	if (format_audio) {
		media_format_unref(format_audio);
		format_audio = NULL;
	}
	if (format_text) {
		media_format_unref(format_text);
		format_text = NULL;
	}
	if (format_for_tbm) {
		media_format_unref(format_for_tbm);
		format_for_tbm = NULL;
	}
}


static int _finalize_callback(media_packet_h packet, int err, void *userdata)
{
	finalizeCB_called = true;
	return MEDIA_PACKET_FINALIZE;
}


static void _dispose_callback(media_packet_h packet, void *userdata)
{
	disposeCB_called = true;
}


/**
 * @testcase		utc_media_packet_create_alloc_p
 * @since_tizen		2.3
 * @description	Positive test case to create media_packet_h handle and allocate buffer
 */
int utc_media_packet_create_alloc_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_create_alloc(format, NULL, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	if (ret == MEDIA_PACKET_ERROR_NONE)
		media_packet_destroy(packet);

	return 0;
}

/**
 * @testcase		utc_media_packet_create_alloc_n
 * @since_tizen		2.3
 * @description	Negative test case to create media_packet_h handle and allocate buffer
 */
int utc_media_packet_create_alloc_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_create_alloc(empty_format, NULL, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_OPERATION, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_create_p
 * @since_tizen		2.3
 * @description	Positive test case to create media_packet_h handle
 */
int utc_media_packet_create_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_create(format, NULL, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	if (ret == MEDIA_PACKET_ERROR_NONE)
		media_packet_destroy(packet);

	return 0;
}

/**
 * @testcase		utc_media_packet_create_n
 * @since_tizen		2.3
 * @description	Negative test case to create media_packet_h handle
 */
int utc_media_packet_create_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_create(empty_format, NULL, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_OPERATION, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_copy_p
 * @since_tizen		2.3
 * @description	Positive test case to copy media_packet_h handle
 */
int utc_media_packet_copy_p(void)
{
	int ret1 = MEDIA_PACKET_ERROR_NONE;
	int ret2 = MEDIA_PACKET_ERROR_NONE;

	ret1 = media_packet_create(format, NULL, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret1);

	ret2 = media_packet_copy(packet, NULL, NULL, &packet2);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret2);

	if (ret1 == MEDIA_PACKET_ERROR_NONE)
		media_packet_destroy(packet);

	if (ret2 == MEDIA_PACKET_ERROR_NONE)
		media_packet_destroy(packet2);

	return 0;
}

/**
 * @testcase		utc_media_packet_copy_n
 * @since_tizen		2.3
 * @description	Negative test case to create media_packet_h handle
 */
int utc_media_packet_copy_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_copy(NULL, NULL, NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_format_p
 * @since_tizen		2.3
 * @description	Positive test case to set media_format_h to media_packet_h
 */
int utc_media_packet_set_format_p(void)
{
	int ret1 = MEDIA_PACKET_ERROR_NONE;
	int ret2 = MEDIA_PACKET_ERROR_NONE;

	media_format_h fmt;

	if (media_format_create(&fmt) == MEDIA_FORMAT_ERROR_NONE) {
		int ret_video = MEDIA_FORMAT_ERROR_NONE;
		ret_video = media_format_set_video_mime(fmt, MEDIA_FORMAT_H264_HP);
		ret_video = media_format_set_video_width(fmt, 320);
		ret_video = media_format_set_video_height(fmt, 240);
		ret_video = media_format_set_video_avg_bps(fmt, 10000000);
		ret_video = media_format_set_video_max_bps(fmt, 15000000);
		if (ret_video != MEDIA_FORMAT_ERROR_NONE)
		{
			fprintf(stderr, "media_format_set_video_xxxx failed!");
		}
	} else {
		fprintf(stderr, "media_format_create failed!");
	}

	ret1 = media_packet_create(format, NULL, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret1);

	ret2 = media_packet_set_format(packet, fmt);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret2);

	if(ret1 == MEDIA_PACKET_ERROR_NONE)
		media_packet_destroy(packet);

	media_format_unref(fmt);
	return 0;

}

/**
 * @testcase		utc_media_packet_set_format_n
 * @since_tizen		2.3
 * @description	Negative test case to set media_format_h to media_packet_h
 */
int utc_media_packet_set_format_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_set_format(NULL, NULL);

	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_media_packet_alloc_p
 * @since_tizen		2.3
 * @description	Positive test case to allocate buffer of media_packet_h handle
 */
int utc_media_packet_alloc_p(void)
{
	int ret1 = MEDIA_PACKET_ERROR_NONE;
	int ret2 = MEDIA_PACKET_ERROR_NONE;

	ret1 = media_packet_create(format, NULL, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret1);

	ret2 = media_packet_alloc(packet);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret2);

	if(ret2 == MEDIA_PACKET_ERROR_NONE)
		media_packet_destroy(packet);

	return 0;
}

/**
 * @testcase		utc_media_packet_alloc_n
 * @since_tizen		2.3
 * @description	Negative test case to allocate buffer of media_packet_h handle
 */
int utc_media_packet_alloc_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_alloc(NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_flags_p
 * @since_tizen		2.3
 * @description	Positive test case to set flags
 */
int utc_media_packet_set_flags_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	media_buffer_flags_e flag = MEDIA_PACKET_CODEC_CONFIG;

	ret = media_packet_set_flags(pkt_create_alloc, flag);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_flags_n
 * @since_tizen		2.3
 * @description	Negative test case to set flags
 */
int utc_media_packet_set_flags_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_set_flags(NULL, 0);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_flags_p
 * @since_tizen		3.0
 * @description	Positive test case to get flags
 */
int utc_media_packet_get_flags_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	media_buffer_flags_e set_flag = MEDIA_PACKET_CODEC_CONFIG;
	media_packet_set_flags(pkt_create_alloc, set_flag);

	media_buffer_flags_e flag;
	ret = media_packet_get_flags(pkt_create_alloc, &flag);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);
	assert(flag & set_flag);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_flags_n
 * @since_tizen		3.0
 * @description	Negative test case to get flags
 */
int utc_media_packet_get_flags_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_get_flags(NULL, NULL);

	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_unset_flags_p
 * @since_tizen		2.3
 * @description	Positive test case to unset flags
 */
int utc_media_packet_unset_flags_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	media_buffer_flags_e flag = MEDIA_PACKET_CODEC_CONFIG;

	ret = media_packet_unset_flags(pkt_create_alloc, flag);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_unset_flags_n
 * @since_tizen		2.3
 * @description	Negative test case to unset flags
 */
int utc_media_packet_unset_flags_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_unset_flags(NULL, 0);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}
/**
 * @testcase		utc_media_packet_is_codec_config_p
 * @since_tizen		2.3
 * @description	Positive test case to get whether MEDIA_PACKET_CODEC_CONFIG	is set or not
 */
int utc_media_packet_is_codec_config_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	bool is_codec_config;

	ret = media_packet_is_codec_config(pkt_create_alloc, &is_codec_config);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);
	assert(!is_codec_config);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_codec_config_n
 * @since_tizen		2.3
 * @description	Negative test case to get whether MEDIA_PACKET_CODEC_CONFIG is set or not
 */
int utc_media_packet_is_codec_config_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_is_codec_config(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_end_of_stream_p
 * @since_tizen		2.3
 * @description	Positive test case to get get whether MEDIA_PACKET_END_OF_STREAM	 is set or not
 */
int utc_media_packet_is_end_of_stream_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	bool is_eos;

	ret = media_packet_is_end_of_stream(pkt_create_alloc, &is_eos);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);
	assert(!is_eos);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_end_of_stream_n
 * @since_tizen		2.3
 * @description	Negative test case to get whether MEDIA_PACKET_END_OF_STREAM is set or not
 */
int utc_media_packet_is_end_of_stream_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_is_end_of_stream(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_sync_frame_p
 * @since_tizen		2.3
 * @description	Positive test case to get whether MEDIA_PACKET_SYNC_FRAME is set or not
 */
int utc_media_packet_is_sync_frame_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	bool is_sync;

	ret = media_packet_is_sync_frame(pkt_create_alloc, &is_sync);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);
	assert(!is_sync);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_sync_frame_n
 * @since_tizen		2.3
 * @description	Negative test case to get whether MEDIA_PACKET_SYNC_FRAME is set or not
 */
int utc_media_packet_is_sync_frame_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_is_sync_frame(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_has_tbm_surface_buffer_p
 * @since_tizen		2.3
 * @description	Positive test case to get whether the allocated buffer is tbm surface or not
 */
int utc_media_packet_has_tbm_surface_buffer_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	bool has_tbm;

	ret = media_packet_has_tbm_surface_buffer(pkt_create_alloc, &has_tbm);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);
	assert(!has_tbm);

	return 0;
}

/**
 * @testcase		utc_media_packet_has_tbm_surface_buffer_n
 * @since_tizen		2.3
 * @description	Negative test case to get whether the allocated buffer is tbm surface or not
 */
int utc_media_packet_has_tbm_surface_buffer_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_has_tbm_surface_buffer(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_create_from_tbm_surface_p
 * @since_tizen		2.3
 * @description	Positive test case to create media_packet_h handle and allocates buffer with #tbm_surface_h
 */
int utc_media_packet_create_from_tbm_surface_p(void)
{

	int ret = MEDIA_PACKET_ERROR_NONE;

	tbm_surface_h surface;
	int width = 128;
	int height = 128;
	tbm_format tbm_fmt = TBM_FORMAT_YUV420;
	surface = tbm_surface_create(width, height, tbm_fmt);

	ret = media_packet_create_from_tbm_surface(format_for_tbm, surface, _finalize_callback, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);


	if (ret == MEDIA_PACKET_ERROR_NONE) {
		media_packet_destroy(packet);
		tbm_surface_destroy(surface);
	}

	return 0;
}

/**
 * @testcase		utc_media_packet_create_from_tbm_surface_n
 * @since_tizen		2.3
 * @description	Negative test case to create media_packet_h handle and allocates buffer with #tbm_surface_h
 */
int utc_media_packet_create_from_tbm_surface_n(void)
{

	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_create_from_tbm_surface(NULL, NULL, NULL,NULL, NULL);

	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_create_from_external_memory_p
 * @since_tizen		2.4
 * @description	Positive test case to creates media packet handle with already allocated external buffer
 */
int utc_media_packet_create_from_external_memory_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	uint64_t size = 1000;
	void* ext_mem = (void*)malloc(size);

	if (ext_mem == NULL)
		assert(false);

	ret = media_packet_create_from_external_memory(format, ext_mem, size, NULL, NULL, &packet);
	if (ret != MEDIA_PACKET_ERROR_NONE) {
		free(ext_mem);
		ext_mem = NULL;
	}

	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	if (ret == MEDIA_PACKET_ERROR_NONE)
		media_packet_destroy(packet);

	if (ext_mem)
		free(ext_mem);

	return 0;
}

/**
 * @testcase		utc_media_packet_create_from_external_memory_n
 * @since_tizen		2.4
 * @description	Negative test case to creates media packet handle with already allocated external buffer
 */
int utc_media_packet_create_from_external_memory_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	uint64_t size = 1000;
	void* ext_mem = (void*)malloc(size);

	if (ext_mem == NULL)
		assert(false);

	ret = media_packet_create_from_external_memory(empty_format, ext_mem, size, NULL, NULL, &packet);
	if (ret != MEDIA_PACKET_ERROR_NONE) {
		free(ext_mem);
		ext_mem = NULL;
	}

	assert_eq(MEDIA_PACKET_ERROR_INVALID_OPERATION, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_format_p
 * @since_tizen		2.3
 * @description	Positive test case to get media_format_h handle
 */
int utc_media_packet_get_format_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	media_format_h fmt;
	int width;
	ret = media_packet_get_format(pkt_create_alloc, &fmt);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	media_format_get_video_info(fmt, NULL, &width, NULL, NULL, NULL);
	assert_eq(480, width);

	media_format_unref(fmt);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_format_n
 * @since_tizen		2.3
 * @description	Negative test case to get media_format_h handle
 */
int utc_media_packet_get_format_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_get_format(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_pts_p
 * @since_tizen		2.3
 * @description	Positive test case to set pts
 */
int utc_media_packet_set_pts_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	uint64_t pts = 1234567;

	ret = media_packet_set_pts(pkt_create_alloc, pts);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_pts_n
 * @since_tizen		2.3
 * @description	Negative test case to set pts
 */
int utc_media_packet_set_pts_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_set_pts(NULL, 0);

	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_dts_p
 * @since_tizen		2.3
 * @description	Positive test case to set dts
 */
int utc_media_packet_set_dts_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	uint64_t dts = 7654321;

	ret = media_packet_set_dts(pkt_create_alloc, dts);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_dts_n
 * @since_tizen		2.3
 * @description	Negative test case to set dts
 */
int utc_media_packet_set_dts_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_set_dts(NULL, 0);

	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_duration_p
 * @since_tizen		2.3
 * @description	Positive test case to set duration
 */
int utc_media_packet_set_duration_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	uint64_t duration = 5000000;

	ret = media_packet_set_duration(pkt_create_alloc, duration);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_duration_n
 * @since_tizen		2.3
 * @description	Negative test case to set duration
 */
int utc_media_packet_set_duration_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_set_duration(NULL, 0);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_buffer_size_p
 * @since_tizen		2.3
 * @description	Positive test case to set buffer size
 */
int utc_media_packet_set_buffer_size_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	uint64_t size = 10000;

	ret = media_packet_set_buffer_size(pkt_create_alloc, size);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_buffer_size_n
 * @since_tizen		2.3
 * @description	Negative test case to set buffer size
 */
int utc_media_packet_set_buffer_size_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_set_buffer_size(NULL, 0);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_pts_p
 * @since_tizen		2.3
 * @description	Positive test case to get pts
 */
int utc_media_packet_get_pts_p(void)
{
	int ret1 = MEDIA_PACKET_ERROR_NONE;
	int ret2 = MEDIA_PACKET_ERROR_NONE;

	uint64_t get_pts;
	uint64_t pts = 1234567;

	ret1 = media_packet_set_pts(pkt_create_alloc, pts);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret1);

	ret2 = media_packet_get_pts(pkt_create_alloc, &get_pts);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret2);
	assert_eq(1234567, get_pts);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_pts_n
 * @since_tizen		2.3
 * @description	Negative test case to get pts
 */
int utc_media_packet_get_pts_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_get_pts(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_dts_p
 * @since_tizen		2.3
 * @description	Positive test case to get dts
 */
int utc_media_packet_get_dts_p(void)
{
	int ret1 = MEDIA_PACKET_ERROR_NONE;
	int ret2 = MEDIA_PACKET_ERROR_NONE;
	uint64_t get_dts;
	uint64_t dts = 7654321;

	ret1 = media_packet_set_dts(pkt_create_alloc, dts);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret1);

	ret2 = media_packet_get_dts(pkt_create_alloc, &get_dts);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret2);
	assert_eq(7654321, get_dts);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_dts_n
 * @since_tizen		2.3
 * @description	Negative  test case to get dts
 */
int utc_media_packet_get_dts_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_get_dts(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_duration_p
 * @since_tizen		2.3
 * @description	Positive test case to get duration
 */
int utc_media_packet_get_duration_p(void)
{
	int ret1 = MEDIA_PACKET_ERROR_NONE;
	int ret2 = MEDIA_PACKET_ERROR_NONE;
	uint64_t get_duration;
	uint64_t duration = 5000000;

	ret1 = media_packet_set_duration(pkt_create_alloc, duration);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret1);

	ret2 = media_packet_get_duration(pkt_create_alloc, &get_duration);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret2);
	assert_eq(5000000, duration);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_duration_n
 * @since_tizen		2.3
 * @description	Negative test case to get duration
 */
int utc_media_packet_get_duration_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_get_duration(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_buffer_size_p
 * @since_tizen		2.3
 * @description	Positive test case to get buffer size
 */
int utc_media_packet_get_buffer_size_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	uint64_t size;

	ret = media_packet_get_buffer_size(pkt_create_alloc, &size);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_buffer_size_n
 * @since_tizen		2.3
 * @description	Negative  test case to get buffer size
 */
int utc_media_packet_get_buffer_size_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_get_buffer_size(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_buffer_data_ptr_p
 * @since_tizen		2.3
 * @description	Positive test case to get buffer data pointer
 */
int utc_media_packet_get_buffer_data_ptr_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	void* data;

	ret = media_packet_get_buffer_data_ptr(pkt_create_alloc, &data);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	if (data == NULL)
		assert(false);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_buffer_data_ptr_n
 * @since_tizen		2.3
 * @description	Negative test case to get buffer data pointer
 */
int utc_media_packet_get_buffer_data_ptr_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_get_buffer_data_ptr(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_tbm_surface_p
 * @since_tizen		2.3
 * @description	Positive test case to get tbm surface data
 */
int utc_media_packet_get_tbm_surface_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	tbm_surface_h surface;

	ret = media_packet_get_tbm_surface(pkt_create_alloc, &surface);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_tbm_surface_n
 * @since_tizen		2.3
 * @description	Negative test case to get tbm surface data
 */
int utc_media_packet_get_tbm_surface_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_get_tbm_surface(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_extra_p
 * @since_tizen		2.3
 * @description	Positive test case to set extra data pointer
 */
int utc_media_packet_set_extra_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	char* extra = "extra";

	ret = media_packet_set_extra(pkt_create_alloc, (void*)extra);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_extra_n
 * @since_tizen		2.3
 * @description	Negative test case to set extra data pointer
 */
int utc_media_packet_set_extra_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_set_extra(NULL, NULL);

	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_extra_p
 * @since_tizen		2.3
 * @description	Positive test case to get extra data pointer
 */
int utc_media_packet_get_extra_p(void)
{
	int ret1 = MEDIA_PACKET_ERROR_NONE;
	int ret2 = MEDIA_PACKET_ERROR_NONE;
	void* get_extra;
	char* extra = "extra";

	ret1 = media_packet_set_extra(pkt_create_alloc, (void*)extra);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret1);

	ret2 = media_packet_get_extra(pkt_create_alloc, &get_extra);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret2);

	if (strcmp (extra, (char*)get_extra) != 0)
		assert(false);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_extra_n
 * @since_tizen		2.3
 * @description	Negative test case to get extra data pointer
 */
int utc_media_packet_get_extra_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_get_extra(NULL, NULL);

	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_media_packet_is_video_p
 * @since_tizen		2.3
 * @description	Positive test case to get whether the given media packet is for video or not
 */
int utc_media_packet_is_video_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	bool is_video;

	ret = media_packet_is_video(pkt_create_alloc, &is_video);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_video_n
 * @since_tizen		2.3
 * @description	Negative test case to get whether the given media packet is for video or not
 */
int utc_media_packet_is_video_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_is_video(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_audio_p
 * @since_tizen		2.3
 * @description	Positive test case to get whether the given media packet is for audio or not
 */
int utc_media_packet_is_audio_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	bool is_audio;

	ret = media_packet_is_audio(pkt_create_alloc, &is_audio);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_audio_n
 * @since_tizen		2.3
 * @description	Negative test case to get whether the given media packet is for audio or not
 */
int utc_media_packet_is_audio_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_is_audio(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_encoded_p
 * @since_tizen		2.3
 * @description	Positive test case to get whether the given media packet is encoded type or not
 */
int utc_media_packet_is_encoded_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	bool is_enc;

	ret = media_packet_is_encoded(pkt_create_alloc, &is_enc);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_encoded_n
 * @since_tizen		2.3
 * @description	Negative test case to get whether the given media packet is encoded type or not
 */
int utc_media_packet_is_encoded_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_is_encoded(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_raw_p
 * @since_tizen		2.3
 * @description	Positive test case to get whether the given media packet is raw type or not
 */
int utc_media_packet_is_raw_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	bool is_raw;

	ret = media_packet_is_raw(pkt_create_alloc, &is_raw);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_raw_n
 * @since_tizen		2.3
 * @description	Negative test case to get whether the given media packet is raw type or not
 */
int utc_media_packet_is_raw_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_is_raw(NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_number_of_video_planes_p
 * @since_tizen		2.4
 * @description	Positive test case to get the number of planes from tbm surface in the given media packet
 */
int utc_media_packet_get_number_of_video_planes_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	uint32_t num;

	ret = media_packet_get_number_of_video_planes(pkt_create_alloc_tbm, &num);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_number_of_video_planes_n
 * @since_tizen		2.4
 * @description	Negative test case  test case to get the number of planes from tbm surface in the given media packet
 */
int utc_media_packet_get_number_of_video_planes_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	uint32_t num;

	ret = media_packet_get_number_of_video_planes(pkt_create_alloc, &num);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_OPERATION, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_video_stride_width_p
 * @since_tizen		2.4
 * @description	Positive test case to get stride width from tbm surface in the given media packet
 */
int utc_media_packet_get_video_stride_width_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	int stride_w;

	ret = media_packet_get_video_stride_width(pkt_create_alloc_tbm, 0, &stride_w);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_video_stride_width_n
 * @since_tizen		2.4
 * @description	Negative test case to get stride width from tbm surface in the given media packet
 */
int utc_media_packet_get_video_stride_width_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	int stride_w;

	ret = media_packet_get_video_stride_width(pkt_create_alloc, 0, &stride_w);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_OPERATION, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_video_stride_height_p
 * @since_tizen		2.4
 * @description	Positive test case to stride height from tbm surface in the given media packet
 */
int utc_media_packet_get_video_stride_height_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	int stride_h;

	ret = media_packet_get_video_stride_height(pkt_create_alloc_tbm, 0, &stride_h);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_video_stride_height_n
 * @since_tizen		2.4
 * @description	Negative test case to stride height from tbm surface in the given media packet
 */
int utc_media_packet_get_video_stride_height_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	int stride_h;

	ret = media_packet_get_video_stride_height(pkt_create_alloc, 0, &stride_h);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_OPERATION, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_video_plane_data_ptr_p
 * @since_tizen		2.4
 * @description	Positive test case to get plane data pointer from tbm surface in the given media packet
 */
int utc_media_packet_get_video_plane_data_ptr_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	void* ptr;

	ret = media_packet_get_video_plane_data_ptr(pkt_create_alloc_tbm, 0, &ptr);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_video_plane_data_ptr_n
 * @since_tizen		2.4
 * @description	Negative test case to get plane data pointer from tbm surface in the given media packet
 */
int utc_media_packet_get_video_plane_data_ptr_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	void* ptr;

	ret = media_packet_get_video_plane_data_ptr(pkt_create_alloc, 0, &ptr);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_OPERATION, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_codec_data_n
 * @since_tizen		2.4
 * @description	Negative test case to get codec data
 */
int utc_media_packet_get_codec_data_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_get_codec_data(NULL, NULL, NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_destroy_p
 * @since_tizen		2.3
 * @description	Positive test case to destroy media_packet_h handle
 */
int utc_media_packet_destroy_p(void)
{
	int ret1 = MEDIA_PACKET_ERROR_NONE;
	int ret2 = MEDIA_PACKET_ERROR_NONE;

	ret1 = media_packet_create_alloc(format, _finalize_callback, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret1);

	ret2 = media_packet_destroy(packet);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret2);
	assert_eq(true, finalizeCB_called);

	return 0;
}

/**
 * @testcase		utc_media_packet_destroy_n
 * @since_tizen		2.3
 * @description	Negative test case to destroy media_packet_h handle
 */
int utc_media_packet_destroy_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_destroy(NULL);
	assert_neq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_create_p
 * @since_tizen		2.3
 * @description	Positive test case to create media_format_h handle
 */
int utc_media_format_create_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	media_format_h fmt;
	ret = media_format_create(&fmt);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	if (ret == MEDIA_FORMAT_ERROR_NONE)
		media_format_unref(fmt);

	return 0;
}

/**
 * @testcase		utc_media_format_create_n
 * @since_tizen		2.3
 * @description	Negative test case to create media_format_h handle
 */
int utc_media_format_create_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_create(NULL);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_get_video_info_p
 * @since_tizen		2.3
 * @description	Positive test case to get video information
 */
int utc_media_format_get_video_info_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	media_format_mimetype_e mime;
	int w;
	int h;
	int avg_bps;
	int max_bps;

	ret = media_format_get_video_info(format, &mime, &w, &h, &avg_bps, &max_bps);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_get_video_info_n
 * @since_tizen		2.3
 * @description	Negative test case to get video information
 */
int utc_media_format_get_video_info_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_get_video_info(format_audio, NULL, NULL, NULL, NULL, NULL);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_media_format_get_audio_info_p
 * @since_tizen		2.3
 * @description	Positive test case to get audio information
 */
int utc_media_format_get_audio_info_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	media_format_mimetype_e mime;
	int channel;
	int samplerate;
	int bit;
	int avg_bps;

	ret = media_format_get_audio_info(format_audio, &mime, &channel, &samplerate, &bit, &avg_bps);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_get_audio_info_n
 * @since_tizen		2.3
 * @description	Negative test case to get audio information
 */
int utc_media_format_get_audio_info_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_get_audio_info(format, NULL, NULL, NULL, NULL, NULL);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_get_audio_aac_type_p
 * @since_tizen		2.4
 * @description	Positive test case to get audio aac type
 */
int utc_media_format_get_audio_aac_type_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	bool is_adts;
	media_format_set_audio_mime(format_audio, MEDIA_FORMAT_AAC_LC);

	ret = media_format_get_audio_aac_type(format_audio, &is_adts);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_get_audio_aac_type_n
 * @since_tizen		2.4
 * @description	Negative test case to get audio aac type
 */
int utc_media_format_get_audio_aac_type_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	bool is_adts;

	ret = media_format_get_audio_aac_type(empty_format, &is_adts);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_video_mime_p
 * @since_tizen		2.3
 * @description	Positive test case to set video mime
 */
int utc_media_format_set_video_mime_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	media_format_h fmt;

	media_format_create(&fmt);
	ret = media_format_set_video_mime(fmt, MEDIA_FORMAT_H264_HP);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	media_format_unref(fmt);

	return 0;
}

/**
 * @testcase		utc_media_format_set_video_mime_n
 * @since_tizen		2.3
 * @description	Negative test case to set video mime
 */
int utc_media_format_set_video_mime_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_video_mime(NULL, MEDIA_FORMAT_H264_HP);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_video_width_p
 * @since_tizen		2.3
 * @description	Positive test case to set video width
 */
int utc_media_format_set_video_width_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	media_format_h fmt;

	media_format_create(&fmt);
	media_format_set_video_mime(fmt, MEDIA_FORMAT_H264_HP);

	ret = media_format_set_video_width(fmt, 320);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	media_format_unref(fmt);

	return 0;
}

/**
 * @testcase		utc_media_format_set_video_width_n
 * @since_tizen		2.3
 * @description	Negative test case to set video width
 */
int utc_media_format_set_video_width_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_video_width(format_audio, 320);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_video_height_p
 * @since_tizen		2.3
 * @description	Positive test case to set video height
 */
int utc_media_format_set_video_height_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	media_format_h fmt;

	media_format_create(&fmt);
	media_format_set_video_mime(fmt, MEDIA_FORMAT_H264_HP);

	ret = media_format_set_video_height(fmt, 240);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	media_format_unref(fmt);
	return 0;
}

/**
 * @testcase		utc_media_format_set_video_height_n
 * @since_tizen		2.3
 * @description	Negative test case to set video height
 */
int utc_media_format_set_video_height_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_video_height(format_audio, 240);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_video_avg_bps_p
 * @since_tizen		2.3
 * @description	Positive test case to set video average bps
 */
int utc_media_format_set_video_avg_bps_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	media_format_h fmt;

	media_format_create(&fmt);
	media_format_set_video_mime(fmt, MEDIA_FORMAT_H264_HP);

	ret = media_format_set_video_avg_bps(fmt, 200000);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	media_format_unref(fmt);
	return 0;
}

/**
 * @testcase		utc_media_format_set_video_avg_bps_n
 * @since_tizen		2.3
 * @description	Negative test case to set video average bps
 */
int utc_media_format_set_video_avg_bps_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_video_avg_bps(format_audio, 200000);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_video_max_bps_p
 * @since_tizen		2.3
 * @description	Positive test case to set video max bps
 */
int utc_media_format_set_video_max_bps_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	media_format_h fmt;

	media_format_create(&fmt);
	media_format_set_video_mime(fmt, MEDIA_FORMAT_H264_HP);

	ret = media_format_set_video_max_bps(fmt, 1000000);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	media_format_unref(fmt);

	return 0;
}

/**
 * @testcase		utc_media_format_set_video_max_bps_n
 * @since_tizen		2.3
 * @description	Negative test case to set video max bps
 */
int utc_media_format_set_video_max_bps_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_video_max_bps(format_audio, 1000000);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_mime_p
 * @since_tizen		2.3
 * @description	Positive test case to set audio mime
 */
int utc_media_format_set_audio_mime_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_audio_mime(format_audio, MEDIA_FORMAT_AAC_HE);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_mime_n
 * @since_tizen		2.3
 * @description	Negative test case to set audio mime
 */
int utc_media_format_set_audio_mime_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_audio_mime(format_audio, MEDIA_FORMAT_H264_HP);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_channel_p
 * @since_tizen		2.3
 * @description	Positive test case to set audio channel
 */
int utc_media_format_set_audio_channel_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_audio_channel(format_audio, 4);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_channel_n
 * @since_tizen		2.3
 * @description	Negative test case to set audio channel
 */
int utc_media_format_set_audio_channel_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_audio_channel(format_text, 4);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_samplerate_p
 * @since_tizen		2.3
 * @description	Positive test case to set audio sample rate
 */
int utc_media_format_set_audio_samplerate_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_audio_samplerate(format_audio, 200);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_samplerate_n
 * @since_tizen		2.3
 * @description	Negative test case to set audio sample rate
 */
int utc_media_format_set_audio_samplerate_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_audio_samplerate(format_text, 200);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_bit_p
 * @since_tizen		2.3
 * @description	Positive test case to set audio bit
 */
int utc_media_format_set_audio_bit_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_audio_bit(format_audio, 2000);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_bit_n
 * @since_tizen		2.3
 * @description	Negative test case to set audio bit
 */
int utc_media_format_set_audio_bit_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_audio_bit(format_text, 2000);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_avg_bps_p
 * @since_tizen		2.3
 * @description	Positive test case to set audio average bps
 */
int utc_media_format_set_audio_avg_bps_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_audio_avg_bps(format_audio, 20000);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_avg_bps_n
 * @since_tizen		2.3
 * @description	Negative test case to set audio average bps
 */
int utc_media_format_set_audio_avg_bps_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_audio_avg_bps(format_text, 20000);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_aac_type_p
 * @since_tizen		2.4
 * @description	Positive test case to set audio aac type
 */
int utc_media_format_set_audio_aac_type_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	bool adts = true;

	ret = media_format_set_audio_aac_type(format_audio, adts);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_aac_type_n
 * @since_tizen		2.4
 * @description	Negative test case to set audio aac type
 */
int utc_media_format_set_audio_aac_type_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	media_format_h fmt;
	bool adts = true;

	media_format_create(&fmt);
	media_format_set_video_mime(fmt, MEDIA_FORMAT_H264_HP);

	ret = media_format_set_audio_aac_type(fmt, adts);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	media_format_unref(fmt);

	return 0;
}


/**
 * @testcase		utc_media_format_ref_p
 * @since_tizen		2.3
 * @description	Positive test case to refer media_format_h handle
 */
int utc_media_format_ref_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_ref(format);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	ret = media_format_unref(format);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_ref_n
 * @since_tizen		2.3
 * @description	Negative test case to refer media_format_h handle
 */
int utc_media_format_ref_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_ref(NULL);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_unref_p
 * @since_tizen		2.3
 * @description	Positive test case to unrefer media_format_h handle
 */
int utc_media_format_unref_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_ref(format);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	ret = media_format_unref(format);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_unref_n
 * @since_tizen		2.3
 * @description	Negative test case to unrefer media_format_h handle
 */
int utc_media_format_unref_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_unref(NULL);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_is_writable_p
 * @since_tizen		2.3
 * @description	Positive test case to get whether media_format_h is writable or not
 */
int utc_media_format_is_writable_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	bool writable;

	ret = media_format_is_writable(format, &writable);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_is_writable_n
 * @since_tizen		2.3
 * @description	Negative test case to get whether media_format_h is writable or not
 */
int utc_media_format_is_writable_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_is_writable(NULL, NULL);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_make_writable_p
 * @since_tizen		2.3
 * @description	Positive test case to make media_format_h writable
 */
int utc_media_format_make_writable_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	media_format_h fmt;

	ret = media_format_make_writable(format, &fmt);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	format = NULL;

	ret = media_format_unref(fmt);
	assert_eq(MEDIA_FORMAT_ERROR_NONE,ret);

	return 0;
}

/**
 * @testcase		utc_media_format_make_writable_n
 * @since_tizen		2.3
 * @description	Negative test case to make media_format_h writable
 */
int utc_media_format_make_writable_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_make_writable(NULL, NULL);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_container_mime_p
 * @since_tizen		3.0
 * @description	Positive test case to set container mime
 */
int utc_media_format_set_container_mime_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	media_format_h fmt_container;
	media_format_create(&fmt_container);

	ret = media_format_set_container_mime(fmt_container, MEDIA_FORMAT_CONTAINER_MP4);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);
	media_format_unref(fmt_container);

	return 0;
}

/**
 * @testcase		utc_media_format_set_container_mime_n
 * @since_tizen		3.0
 * @description	Negative test case to set container mime
 */
int utc_media_format_set_container_mime_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	media_format_h fmt_container;
	media_format_create(&fmt_container);

	ret = media_format_set_container_mime(fmt_container, MEDIA_FORMAT_MP3);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	media_format_unref(fmt_container);

	return 0;
}

/**
 * @testcase		utc_media_format_get_container_mime_p
 * @since_tizen		3.0
 * @description	Positive test case to get container mime
 */
int utc_media_format_get_container_mime_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	media_format_h fmt_container;
	media_format_mimetype_e mime;

	media_format_create(&fmt_container);

	ret = media_format_set_container_mime(fmt_container, MEDIA_FORMAT_CONTAINER_MP4);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	ret = media_format_get_container_mime(fmt_container, &mime);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	media_format_unref(fmt_container);

	return 0;
}

/**
 * @testcase		utc_media_format_get_container_mime_n
 * @since_tizen		3.0
 * @description	Negative test case to get container mime
 */
int utc_media_format_get_container_mime_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	media_format_mimetype_e mime;

	ret = media_format_get_container_mime(format, &mime);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_get_type_p
 * @since_tizen		3.0
 * @description	Positive test case to get media_format_h handle type
 */
int utc_media_format_get_type_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	media_format_type_e fmt_type;

	ret = media_format_get_type(format, &fmt_type);

	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);
	assert_eq(MEDIA_FORMAT_VIDEO, fmt_type);

	ret = media_format_get_type(format_audio, &fmt_type);

	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);
	assert_eq(MEDIA_FORMAT_AUDIO, fmt_type);

	return 0;
}

/**
 * @testcase		utc_media_format_get_type_n
 * @since_tizen		3.0
 * @description	Negative test case to get media_format_h handle type
 */
int utc_media_format_get_type_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_get_type(empty_format, NULL);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_video_frame_rate_p
 * @since_tizen		3.0
 * @description	Positive test case to set video frame rate
 */
int utc_media_format_set_video_frame_rate_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	int frame_rate = 10000;
	media_format_h fmt;

	media_format_create(&fmt);

	ret = media_format_set_video_mime(fmt, MEDIA_FORMAT_MPEG4_SP);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	ret = media_format_set_video_frame_rate(fmt, frame_rate);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	media_format_unref(fmt);

	return 0;
}

/**
 * @testcase		utc_media_format_set_video_frame_rate_n
 * @since_tizen		3.0
 * @description	Negative test case to set video frame rate
 */
int utc_media_format_set_video_frame_rate_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	int frame_rate = 10000;
	media_format_h fmt;

	media_format_create(&fmt);

	ret = media_format_set_audio_mime(fmt, MEDIA_FORMAT_AAC_LC);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	ret = media_format_set_video_frame_rate(fmt, frame_rate);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	media_format_unref(fmt);

	return 0;
}

/**
 * @testcase		utc_media_format_get_video_frame_rate_p
 * @since_tizen		3.0
 * @description	Positive test case Positive test case to get video frame rate
 */
int utc_media_format_get_video_frame_rate_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	int frame_rate = 0;

	ret = media_format_get_video_frame_rate(format ,&frame_rate);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);
	assert_eq(frame_rate, 30);

	return 0;
}

/**
 * @testcase		utc_media_format_get_video_frame_rate_n
 * @since_tizen		3.0
 * @description	Negative test case to get video frame rate
 */
int utc_media_format_get_video_frame_rate_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	int frame_rate = 0;

	ret = media_format_get_video_frame_rate(format_audio ,&frame_rate);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_text_mime_p
 * @since_tizen		3.0
 * @description	Positive test case to set text mime
 */
int utc_media_format_set_text_mime_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	media_format_h fmt_text;

	media_format_create(&fmt_text);

	ret = media_format_set_text_mime(fmt_text, MEDIA_FORMAT_TEXT_MP4);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	media_format_unref(fmt_text);

	return 0;
}

/**
 * @testcase		utc_media_format_set_text_mime_n
 * @since_tizen		3.0
 * @description	Negative test case to set text mime
 */
int utc_media_format_set_text_mime_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_text_mime(NULL, MEDIA_FORMAT_TEXT_MP4);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_text_type_p
 * @since_tizen		3.0
 * @description	Positive test case to set text type
 */
int utc_media_format_set_text_type_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	media_format_h fmt_text;

	media_format_create(&fmt_text);

	ret = media_format_set_text_mime(fmt_text, MEDIA_FORMAT_TEXT_MP4);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	ret = media_format_set_text_type(fmt_text, MEDIA_FORMAT_TEXT_TYPE_TIMED_TEXT_3GPP);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	media_format_unref(fmt_text);

	return 0;
}

/**
 * @testcase		utc_media_format_set_text_type_n
 * @since_tizen		3.0
 * @description	Negative test case to set text type
 */
int utc_media_format_set_text_type_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_text_type(format_audio, MEDIA_FORMAT_TEXT_TYPE_TIMED_TEXT_3GPP);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_get_text_info_p
 * @since_tizen		3.0
 * @description	Positive test case to get text info
 */
int utc_media_format_get_text_info_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	media_format_mimetype_e mime;
	media_format_text_type_e text_type;

	ret = media_format_get_text_info(format_text, &mime, &text_type);

	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);
	assert_eq(MEDIA_FORMAT_TEXT_MP4, mime);
	assert_eq(MEDIA_FORMAT_TEXT_TYPE_TIMED_TEXT_3GPP, text_type);

	return 0;
}

/**
 * @testcase		utc_media_format_get_text_info_n
 * @since_tizen		3.0
 * @description	Negative test case to get text info
 */
int utc_media_format_get_text_info_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	media_format_mimetype_e mime;
	media_format_text_type_e text_type;

	ret = media_format_get_text_info(format_audio, &mime, &text_type);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_aac_header_type_p
 * @since_tizen		3.0
 * @description	Positive test case to set audio aac header type
 */
int utc_media_format_set_audio_aac_header_type_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_audio_aac_header_type(format_audio, MEDIA_FORMAT_AAC_HEADER_ADIF);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_audio_aac_header_type_n
 * @since_tizen		3.0
 * @description	Negative test case to set audio aac header type
 */
int utc_media_format_set_audio_aac_header_type_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_audio_aac_header_type(format_text, MEDIA_FORMAT_AAC_HEADER_ADIF);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_get_audio_aac_header_type_p
 * @since_tizen		3.0
 * @description	Positive test case to get audio aac header type
 */
int utc_media_format_get_audio_aac_header_type_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	media_format_aac_header_type_e aac_header_type;

	ret = media_format_get_audio_aac_header_type(format_audio, &aac_header_type);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);
	assert_eq(MEDIA_FORMAT_AAC_HEADER_ADIF, aac_header_type);

	return 0;
}

/**
 * @testcase		utc_media_format_get_audio_aac_header_type_n
 * @since_tizen		3.0
 * @description	Negative test case to get audio aac header type
 */
int utc_media_format_get_audio_aac_header_type_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	media_format_aac_header_type_e aac_header_type;

	ret = media_format_get_audio_aac_header_type(format_text, &aac_header_type);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_text_p
 * @since_tizen		3.0
 * @description	Positive test case to get whether the given media packet is for text or not
 */
int utc_media_packet_is_text_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	bool is_text;

	ret = media_packet_is_text(pkt_create_alloc , &is_text);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_is_text_n
 * @since_tizen		3.0
 * @description	Negative test case to get whether the given media packet is for text or not
 */
int utc_media_packet_is_text_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	bool is_text;

	ret = media_packet_is_text(NULL , &is_text);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_create_p
 * @since_tizen		3.0
 * @description	Positive test case to create media_packet_pool_h handle
 */
int utc_media_packet_pool_create_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_create_n
 * @since_tizen		3.0
 * @description	Negetive test case to create media_packet_pool_h handle
 */
int utc_media_packet_pool_create_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_pool_create(NULL);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_set_media_format_p
 * @since_tizen		3.0
 * @description	Positive test case to Set the media format
 */
int utc_media_packet_pool_set_media_format_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_set_media_format_n
 * @since_tizen		3.0
 * @description	Negetive test case to Set the media format
 */
int utc_media_packet_pool_set_media_format_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, empty_format);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_set_size_p
 * @since_tizen		3.0
 * @description	Positive test case to set size
 */
int utc_media_packet_pool_set_size_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, 3, 5);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_set_size_n
 * @since_tizen		3.0
 * @description	Negetive test case to set size
 */
int utc_media_packet_pool_set_size_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, -3, 5);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_get_size_p
 * @since_tizen		3.0
 * @description	Positive test case to get size
 */
int utc_media_packet_pool_get_size_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	int min, max, curr;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, 3, 5);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_get_size(pool, &min, &max, &curr);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_set_size_n
 * @since_tizen		3.0
 * @description	Negetive test case to get size
 */
int utc_media_packet_pool_get_size_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	int min, max, curr;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, 3, 5);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_get_size(NULL, &min, &max, &curr);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_allocate_p
 * @since_tizen		3.0
 * @description	Positive test case to allocate pool
 */
int utc_media_packet_pool_allocate_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, 3, 5);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_allocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_deallocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_allocate_n
 * @since_tizen		3.0
 * @description	Positive test case to allocate pool
 */
int utc_media_packet_pool_allocate_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, 3, 5);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_allocate(NULL);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_acquire_packet_p
 * @since_tizen		3.0
 * @description	Positive test case to acquire packet from the pool
 */
int utc_media_packet_pool_acquire_packet_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	media_packet_h pkt;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, 3, 5);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_allocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_acquire_packet(pool, &pkt, 3000);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_release_packet(pool, pkt);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_deallocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_acquire_packet_n
 * @since_tizen		3.0
 * @description	Positive test case to acquire packet from the pool
 */
int utc_media_packet_pool_acquire_packet_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	media_packet_h pkt;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, 3, 5);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_allocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_acquire_packet(NULL, &pkt, 3000);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	ret = media_packet_pool_deallocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_relase_packet_p
 * @since_tizen		3.0
 * @description	Positive test case to relase packet to the pool
 */
int utc_media_packet_pool_release_packet_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	media_packet_h pkt;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, 3, 5);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_allocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_acquire_packet(pool, &pkt, 3000);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_release_packet(pool, pkt);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_deallocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_relase_packet_n
 * @since_tizen		3.0
 * @description	Positive test case to release packet to the pool
 */
int utc_media_packet_pool_release_packet_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	media_packet_h pkt;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, 3, 5);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_allocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_acquire_packet(pool, &pkt, 3000);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_release_packet(NULL, pkt);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	ret = media_packet_pool_release_packet(pool, pkt);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_deallocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_deallocate_p
 * @since_tizen		3.0
 * @description	Positive test case to deallocate pool
 */
int utc_media_packet_pool_deallocate_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, 3, 5);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_allocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_deallocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_deallocate_n
 * @since_tizen		3.0
 * @description	Positive test case to deallocate pool
 + */
int utc_media_packet_pool_deallocate_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, 3, 5);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_allocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_deallocate(NULL);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	ret = media_packet_pool_deallocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_destroy_p
 * @since_tizen		3.0
 * @description	Positive test case to destroy pool
 */
int utc_media_packet_pool_destroy_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, 3, 5);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_allocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_deallocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_pool_destroy_n
 * @since_tizen		3.0
 * @description	Positive test case to destroy pool
 */
int utc_media_packet_pool_destroy_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_pool_create(&pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_media_format(pool, format);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_set_size(pool, 3, 5);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_allocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_deallocate(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_pool_destroy(NULL);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	ret = media_packet_pool_destroy(pool);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_extra_p
 * @since_tizen		4.0
 * @description		Positive test case to set extra data pointer
 */
int utc_media_format_set_extra_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	char* extra = "extra";

	ret = media_format_set_extra(format, (void*)extra);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_set_extra_n
 * @since_tizen		4.0
 * @description		Negative test case to set extra data pointer
 */
int utc_media_format_set_extra_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_set_extra(NULL, NULL);

	assert_neq(MEDIA_FORMAT_ERROR_NONE, ret);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_get_extra_p
 * @since_tizen		4.0
 * @description		Positive test case to get extra data pointer
 */
int utc_media_format_get_extra_p(void)
{
	int ret1 = MEDIA_FORMAT_ERROR_NONE;
	int ret2 = MEDIA_FORMAT_ERROR_NONE;
	void* get_extra;
	char* extra = "extra";

	ret1 = media_format_set_extra(format, (void*)extra);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret1);

	ret2 = media_format_get_extra(format, &get_extra);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret2);

	if (strcmp (extra, (char*)get_extra) != 0)
		assert(false);

	return 0;
}

/**
 * @testcase		utc_media_format_get_extra_n
 * @since_tizen		4.0
 * @description		Negative test case to get extra data pointer
 */
int utc_media_format_get_extra_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;

	ret = media_format_get_extra(NULL, NULL);

	assert_neq(MEDIA_FORMAT_ERROR_NONE, ret);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_rotate_method_p
 * @since_tizen		5.0
 * @description		Positive test case to set the rotation method
 */
int utc_media_packet_set_rotate_method_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	media_packet_rotate_method_e method;

	ret = media_packet_set_rotate_method(pkt_create_alloc, MEDIA_PACKET_ROTATE_180);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_get_rotate_method(pkt_create_alloc, &method);
	assert_eq(MEDIA_PACKET_ROTATE_180, method);

	return 0;
}

/**
 * @testcase		utc_media_packet_set_rotate_method_n
 * @since_tizen		5.0
 * @description		Negative test case to set the rotation method
 */
int utc_media_packet_set_rotate_method_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_set_rotate_method(NULL, MEDIA_PACKET_ROTATE_HORIZONTAL_FLIP);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_rotate_method_p
 * @since_tizen		5.0
 * @description		Positive test case to get the rotation method
 */
int utc_media_packet_get_rotate_method_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	media_packet_rotate_method_e method;

	ret = media_packet_set_rotate_method(pkt_create_alloc, MEDIA_PACKET_ROTATE_180);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	ret = media_packet_get_rotate_method(pkt_create_alloc, &method);
	assert_eq(MEDIA_PACKET_ROTATE_180, method);

	return 0;
}

/**
 * @testcase		utc_media_packet_get_rotate_method_n
 * @since_tizen		5.0
 * @description		Negative test case to get the rotation method
 */
int utc_media_packet_get_rotate_method_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	media_packet_rotate_method_e method;

	ret = media_packet_get_rotate_method(NULL, &method);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_format_channel_positions_to_mask_n
 * @since_tizen		5.5
 * @description		Negative test case to change posions to mask
 */
int utc_media_format_channel_positions_to_mask_n(void)
{
	uint64_t channel_mask;
	media_format_channel_position_e position[2];
	int ret = MEDIA_FORMAT_ERROR_NONE;

	position[0] = MEDIA_FORMAT_CHANNEL_POSITION_INVALID;
	position[1] = MEDIA_FORMAT_CHANNEL_POSITION_MONO;

	ret = media_format_set_audio_channel(format_audio, 2);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	ret = media_format_channel_positions_to_mask(format_audio, position, &channel_mask);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_OPERATION, ret);

	return 0;
}

/**
 * @testcase		utc_format_channel_positions_to_mask_p
 * @since_tizen		5.5
 * @description		Positive test case to change posions to mask
 */
int utc_media_format_channel_positions_to_mask_p(void)
{
	uint64_t channel_mask;
	media_format_channel_position_e position[2];
	int ret = MEDIA_FORMAT_ERROR_NONE;

	position[0] = MEDIA_FORMAT_CHANNEL_POSITION_FRONT_LEFT;
	position[1] = MEDIA_FORMAT_CHANNEL_POSITION_FRONT_RIGHT;

	ret = media_format_set_audio_channel(format_audio, 2);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	ret = media_format_channel_positions_to_mask(format_audio, position, &channel_mask);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_get_audio_channel_mask_n
 * @since_tizen		5.5
 * @description		Negative test case to get audio channel mask
 */
int utc_media_format_get_audio_channel_mask_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	int channels;
	uint64_t channel_mask;

	/* set the invalid channel */
	ret = media_format_set_audio_channel(format_audio, 10);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	ret = media_format_set_audio_channel_mask(format_audio, 0x3);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	ret = media_format_get_audio_channel_mask(format_audio, &channel_mask);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);
	assert_eq(channel_mask, 0);

	return 0;
}


/**
 * @testcase		utc_media_format_get_audio_channel_mask_p
 * @since_tizen		5.5
 * @description		Positive test case to get audio channel mask
 */
int utc_media_format_get_audio_channel_mask_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	int channels;
	uint64_t channel_mask;
	bool check_position = true;
	media_format_channel_position_e *positions;

	ret = media_format_get_audio_info(format_audio, NULL, &channels, NULL, NULL, NULL);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);


	ret = media_format_set_audio_channel_mask(format_audio, 0x3);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	ret = media_format_get_audio_channel_mask(format_audio, &channel_mask);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	positions = malloc(channels * sizeof(media_format_channel_position_e));
	ret = media_format_channel_positions_from_mask(format_audio, channel_mask, &positions);
	if (ret != MEDIA_FORMAT_ERROR_NONE) {
		free(positions);
		return 1;
	}

	if (positions[0] != MEDIA_FORMAT_CHANNEL_POSITION_FRONT_LEFT || positions[1] != MEDIA_FORMAT_CHANNEL_POSITION_FRONT_RIGHT)
		check_position = false;

	free(positions);
	assert_eq(check_position, true);

	return 0;
}

/**
 * @testcase		utc_media_format_is_little_endian_n
 * @since_tizen		5.5
 * @description		Negative test case to check little endian
 */
int utc_media_format_is_little_endian_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	bool is_little_endian;

	ret = media_format_is_little_endian(NULL, &is_little_endian);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_is_little_endian_p
 * @since_tizen		5.5
 * @description		Positive test case to check little endian
 */
int utc_media_format_is_little_endian_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	bool is_little_endian;
	media_format_h format_pcm;

	ret = media_format_create(&format_pcm);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	ret = media_format_set_audio_mime(format_pcm, MEDIA_FORMAT_PCM_S24LE);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	ret = media_format_is_little_endian(format_pcm, &is_little_endian);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);
	assert_eq(true, is_little_endian);

	return 0;
}

/**
 * @testcase		utc_media_format_get_audio_bit_depth_n
 * @since_tizen		5.5
 * @description		Negative test case to get audio bit bepth
 */
int utc_media_format_get_audio_bit_depth_n(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	int bit_depth;

	ret = media_format_get_audio_bit_depth(NULL, &bit_depth);
	assert_eq(MEDIA_FORMAT_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_media_format_get_audio_bit_depth_p
 * @since_tizen		5.5
 * @description		Positive test case to get audio bit depth
 */
int utc_media_format_get_audio_bit_depth_p(void)
{
	int ret = MEDIA_FORMAT_ERROR_NONE;
	int bit_depth;
	media_format_h format_pcm;

	ret = media_format_create(&format_pcm);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	ret = media_format_set_audio_mime(format_pcm, MEDIA_FORMAT_PCM_S24LE);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

	ret = media_format_get_audio_bit_depth(format_pcm, &bit_depth);
	assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);
	assert_eq(24, bit_depth);

	return 0;
}

/**
 * @testcase	utc_media_packet_new_p
 * @since_tizen	6.5
 * @description	Positive test case to make media_packet_h handle
 */
int utc_media_packet_new_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	media_packet_h new_pkt = NULL;

	ret = media_packet_new(format, NULL, NULL, &new_pkt);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	media_packet_unref(new_pkt);

	return 0;
}

/**
 * @testcase	utc_media_packet_new_n
 * @since_tizen	6.5
 * @description	Negative test case to make media_packet_h handle
 */
int utc_media_packet_new_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_new(empty_format, NULL, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_OPERATION, ret);

	return 0;
}

/**
 * @testcase	utc_media_packet_new_alloc_p
 * @since_tizen	6.5
 * @description	Positive test case to make media_packet_h handle and allocate buffer
 */
int utc_media_packet_new_alloc_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_new_alloc(format, NULL, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	media_packet_unref(packet);

	return 0;
}

/**
 * @testcase	utc_media_packet_new_alloc_n
 * @since_tizen	6.5
 * @description	Negative test case to make media_packet_h handle and allocate buffer
 */
int utc_media_packet_new_alloc_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_new_alloc(empty_format, NULL, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_OPERATION, ret);

	return 0;
}

/**
 * @testcase	utc_media_packet_new_from_tbm_surface_p
 * @since_tizen	6.5
 * @description	Positive test case to make media_packet_h handle and allocates buffer with #tbm_surface_h
 */
int utc_media_packet_new_from_tbm_surface_p(void)
{

	int ret = MEDIA_PACKET_ERROR_NONE;
	tbm_surface_h surface = NULL;

	surface = tbm_surface_create(128, 128, TBM_FORMAT_YUV420);
	assert_neq(NULL, surface);

	ret = media_packet_new_from_tbm_surface(format_for_tbm, surface, _dispose_callback, NULL, &packet);
	tbm_surface_destroy(surface);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	media_packet_unref(packet);

	return 0;
}

/**
 * @testcase	utc_media_packet_new_from_tbm_surface_n
 * @since_tizen	6.5
 * @description	Negative test case to make media_packet_h handle and allocates buffer with #tbm_surface_h
 */
int utc_media_packet_new_from_tbm_surface_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_new_from_tbm_surface(NULL, NULL, NULL, NULL, NULL);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase	utc_media_packet_new_from_external_memory_p
 * @since_tizen	6.5
 * @description	Positive test case to make media packet handle with already allocated external buffer
 */
int utc_media_packet_new_from_external_memory_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	char ext_mem[100];

	ret = media_packet_new_from_external_memory(format, ext_mem, 100, NULL, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	media_packet_unref(packet);

	return 0;
}

/**
 * @testcase	utc_media_packet_new_from_external_memory_n
 * @since_tizen	6.5
 * @description	Negative test case to make media packet handle with already allocated external buffer
 */
int utc_media_packet_new_from_external_memory_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;
	char ext_mem[100];

	ret = media_packet_new_from_external_memory(empty_format, ext_mem, 100, NULL, NULL, &packet);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_OPERATION, ret);

	if (ret == MEDIA_PACKET_ERROR_NONE)
		media_packet_unref(packet);


	return 0;
}

/**
 * @testcase	utc_media_packet_ref_p
 * @since_tizen	6.5
 * @description	Positive test case to ref media_packet_h handle
 */
int utc_media_packet_ref_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_ref(pkt_new_alloc);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	media_packet_unref(pkt_new_alloc);

	return 0;
}

/**
 * @testcase	utc_media_packet_ref_n
 * @since_tizen	6.5
 * @description	Negative test case to ref media_packet_h handle
 */
int utc_media_packet_ref_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_ref(NULL);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase	utc_media_packet_unref_p
 * @since_tizen	6.5
 * @description	Positive test case to unref media_packet_h handle
 */
int utc_media_packet_unref_p(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	disposeCB_called = false;

	ret = media_packet_unref(pkt_new_alloc);
	assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

	pkt_new_alloc = NULL;

	assert_eq(true, disposeCB_called);

	return 0;
}

/**
 * @testcase	utc_media_packet_unref_n
 * @since_tizen	6.5
 * @description	Negative test case to unref media_packet_h handle
 */
int utc_media_packet_unref_n(void)
{
	int ret = MEDIA_PACKET_ERROR_NONE;

	ret = media_packet_unref(NULL);
	assert_eq(MEDIA_PACKET_ERROR_INVALID_PARAMETER, ret);

	return 0;
}
