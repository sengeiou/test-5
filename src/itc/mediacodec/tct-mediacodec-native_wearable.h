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
#ifndef __TCT_MEDIACODEC-NATIVE_H__
#define __TCT_MEDIACODEC-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_media_codec_startup(void);
extern void ITs_media_codec_cleanup(void);

extern int ITc_mediacodec_create_destroy_p(void);
extern int ITc_mediacodec_prepare_unprepare_p(void);
extern int ITc_mediacodec_set_venc_info_p(void);
extern int ITc_mediacodec_set_adec_info_p(void);
extern int ITc_mediacodec_set_aenc_info_p(void);
extern int ITc_mediacodec_set_vdec_info_p(void);
extern int ITc_mediacodec_set_codec_p(void);
extern int ITc_mediacodec_process_input_p(void);
extern int ITc_mediacodec_get_output_p(void);
extern int ITc_mediacodec_set_unset_error_cb_p(void);
extern int ITc_mediacodec_set_eos_cb_p(void);
extern int ITc_mediacodec_set_unset_input_buffer_used_cb_p(void);
extern int ITc_mediacodec_set_unset_output_buffer_available_cb_p(void);
extern int ITc_mediacodec_flush_buffers_p(void);
extern int ITc_mediacodec_foreach_supported_codec_p(void);
extern int ITc_mediacodec_get_supported_type_p(void);
extern int ITc_mediacodec_set_unset_buffer_status_cb_p(void);
extern int ITc_mediacodec_get_packet_pool_p(void);
extern int ITc_mediacodec_configure_from_media_format_audio_video_decoder_p(void);
extern int ITc_mediacodec_configure_from_media_format_audio_video_encoder_p(void);

testcase tc_array[] = {
	{"ITc_mediacodec_create_destroy_p",ITc_mediacodec_create_destroy_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_prepare_unprepare_p",ITc_mediacodec_prepare_unprepare_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_set_venc_info_p",ITc_mediacodec_set_venc_info_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_set_adec_info_p",ITc_mediacodec_set_adec_info_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_set_aenc_info_p",ITc_mediacodec_set_aenc_info_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_set_vdec_info_p",ITc_mediacodec_set_vdec_info_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_set_codec_p",ITc_mediacodec_set_codec_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_process_input_p",ITc_mediacodec_process_input_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_get_output_p",ITc_mediacodec_get_output_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_set_unset_error_cb_p",ITc_mediacodec_set_unset_error_cb_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_set_eos_cb_p",ITc_mediacodec_set_eos_cb_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_set_unset_input_buffer_used_cb_p",ITc_mediacodec_set_unset_input_buffer_used_cb_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_set_unset_output_buffer_available_cb_p",ITc_mediacodec_set_unset_output_buffer_available_cb_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_flush_buffers_p",ITc_mediacodec_flush_buffers_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_foreach_supported_codec_p",ITc_mediacodec_foreach_supported_codec_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_get_supported_type_p",ITc_mediacodec_get_supported_type_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_set_unset_buffer_status_cb_p",ITc_mediacodec_set_unset_buffer_status_cb_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_get_packet_pool_p",ITc_mediacodec_get_packet_pool_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_configure_from_media_format_audio_video_decoder_p",ITc_mediacodec_configure_from_media_format_audio_video_decoder_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{"ITc_mediacodec_configure_from_media_format_audio_video_encoder_p",ITc_mediacodec_configure_from_media_format_audio_video_encoder_p,ITs_media_codec_startup,ITs_media_codec_cleanup},
	{NULL, NULL}
};

#endif // __TCT_MEDIACODEC-NATIVE_H__
