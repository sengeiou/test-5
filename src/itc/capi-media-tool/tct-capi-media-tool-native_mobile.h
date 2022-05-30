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
#ifndef __TCT_CAPI-MEDIA-TOOL-NATIVE_H__
#define __TCT_CAPI-MEDIA-TOOL-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_media_pool_startup(void);
extern void ITs_media_pool_cleanup(void);
extern void ITs_media_tools_startup(void);
extern void ITs_media_tools_cleanup(void);
extern void ITs_media_format_startup(void);
extern void ITs_media_format_cleanup(void);

extern int ITc_media_packet_pool_create_destroy_p(void);
extern int ITc_media_packet_pool_set_media_format_p(void);
extern int ITc_media_packet_pool_set_get_size_p(void);
extern int ITc_media_packet_pool_acquire_release_packet_p(void);
extern int ITc_media_packet_pool_allocate_deallocate_p(void);
extern int ITc_media_packet_new_p(void);
extern int ITc_media_packet_alloc_p(void);
extern int ITc_media_packet_new_alloc_p(void);
extern int ITc_media_packet_ref_unref_p(void);
extern int ITc_media_packet_get_buffer_data_ptr_p(void);
extern int ITc_media_packet_is_video_p(void);
extern int ITc_media_packet_is_audio_p(void);
extern int ITc_media_packet_is_codec_config_p(void);
extern int ITc_media_packet_is_encoded_p(void);
extern int ITc_media_packet_is_end_of_stream_p(void);
extern int ITc_media_packet_is_raw_p(void);
extern int ITc_media_packet_is_sync_frame_p(void);
extern int ITc_media_packet_set_get_format_p(void);
extern int ITc_media_packet_set_get_pts_p(void);
extern int ITc_media_packet_set_get_dts_p(void);
extern int ITc_media_packet_set_get_duration_p(void);
extern int ITc_media_packet_set_get_buffer_size_p(void);
extern int ITc_media_packet_set_get_extra_p(void);
extern int ITc_media_packet_set_unset_flags_p(void);
extern int ITc_media_packet_set_get_flags_p(void);
extern int ITc_media_packet_get_tbm_surface_p(void);
extern int ITc_media_packet_new_from_tbm_surface_p(void);
extern int ITc_media_packet_has_tbm_surface_buffer_p(void);
extern int ITc_media_packet_new_from_external_memory_p(void);
extern int ITc_media_packet_get_number_of_video_planes_p(void);
extern int ITc_media_packet_get_video_stride_width_p(void);
extern int ITc_media_packet_get_video_stride_height_p(void);
extern int ITc_media_packet_get_video_plane_data_ptr_p(void);
extern int ITc_media_packet_is_text_p(void);
extern int ITc_media_packet_set_get_rotate_method(void);
extern int ITc_media_format_ref_p(void);
extern int ITc_media_format_is_writable_p(void);
extern int ITc_media_format_make_writable_p(void);
extern int ITc_media_format_set_video_mime_p(void);
extern int ITc_media_format_set_video_width_p(void);
extern int ITc_media_format_set_video_height_p(void);
extern int ITc_media_format_set_video_avg_bps_p(void);
extern int ITc_media_format_set_video_max_bps_p(void);
extern int ITc_media_format_get_video_info_p(void);
extern int ITc_media_format_set_audio_mime_p(void);
extern int ITc_media_format_set_audio_channel_p(void);
extern int ITc_media_format_set_audio_samplerate_p(void);
extern int ITc_media_format_set_audio_bit_p(void);
extern int ITc_media_format_set_audio_avg_bps_p(void);
extern int ITc_media_format_get_audio_info_p(void);
extern int ITc_media_format_set_audio_aac_type_p(void);
extern int ITc_media_format_get_audio_aac_type_p(void);
extern int ITc_media_format_get_type_p(void);
extern int ITc_media_format_set_get_video_frame_rate_p(void);
extern int ITc_media_format_set_get_container_mime_p(void);
extern int ITc_media_format_set_text_mime_set_text_type_get_text_info_p(void);
extern int ITc_media_format_set_get_audio_aac_header_type_p(void);
extern int ITc_media_format_set_extra_p(void);
extern int ITc_media_format_get_extra_p(void);
extern int ITc_media_format_set_get_audio_channel_mask_p(void);
extern int ITc_media_format_channel_positions_to_from_mask_p(void);
extern int ITc_media_format_is_little_endian_p(void);
extern int ITc_media_format_get_audio_bit_depth_p(void);

testcase tc_array[] = {
	{"ITc_media_packet_pool_create_destroy_p",ITc_media_packet_pool_create_destroy_p,ITs_media_pool_startup,ITs_media_pool_cleanup},
	{"ITc_media_packet_pool_set_media_format_p",ITc_media_packet_pool_set_media_format_p,ITs_media_pool_startup,ITs_media_pool_cleanup},
	{"ITc_media_packet_pool_set_get_size_p",ITc_media_packet_pool_set_get_size_p,ITs_media_pool_startup,ITs_media_pool_cleanup},
	{"ITc_media_packet_pool_acquire_release_packet_p",ITc_media_packet_pool_acquire_release_packet_p,ITs_media_pool_startup,ITs_media_pool_cleanup},
	{"ITc_media_packet_pool_allocate_deallocate_p",ITc_media_packet_pool_allocate_deallocate_p,ITs_media_pool_startup,ITs_media_pool_cleanup},
	{"ITc_media_packet_new_p",ITc_media_packet_new_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_alloc_p",ITc_media_packet_alloc_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_new_alloc_p",ITc_media_packet_new_alloc_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_ref_unref_p",ITc_media_packet_ref_unref_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_get_buffer_data_ptr_p",ITc_media_packet_get_buffer_data_ptr_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_is_video_p",ITc_media_packet_is_video_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_is_audio_p",ITc_media_packet_is_audio_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_is_codec_config_p",ITc_media_packet_is_codec_config_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_is_encoded_p",ITc_media_packet_is_encoded_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_is_end_of_stream_p",ITc_media_packet_is_end_of_stream_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_is_raw_p",ITc_media_packet_is_raw_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_is_sync_frame_p",ITc_media_packet_is_sync_frame_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_set_get_format_p",ITc_media_packet_set_get_format_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_set_get_pts_p",ITc_media_packet_set_get_pts_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_set_get_dts_p",ITc_media_packet_set_get_dts_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_set_get_duration_p",ITc_media_packet_set_get_duration_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_set_get_buffer_size_p",ITc_media_packet_set_get_buffer_size_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_set_get_extra_p",ITc_media_packet_set_get_extra_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_set_unset_flags_p",ITc_media_packet_set_unset_flags_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_set_get_flags_p",ITc_media_packet_set_get_flags_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_get_tbm_surface_p",ITc_media_packet_get_tbm_surface_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_new_from_tbm_surface_p",ITc_media_packet_new_from_tbm_surface_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_has_tbm_surface_buffer_p",ITc_media_packet_has_tbm_surface_buffer_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_new_from_external_memory_p",ITc_media_packet_new_from_external_memory_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_get_number_of_video_planes_p",ITc_media_packet_get_number_of_video_planes_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_get_video_stride_width_p",ITc_media_packet_get_video_stride_width_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_get_video_stride_height_p",ITc_media_packet_get_video_stride_height_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_get_video_plane_data_ptr_p",ITc_media_packet_get_video_plane_data_ptr_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_is_text_p",ITc_media_packet_is_text_p,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_packet_set_get_rotate_method",ITc_media_packet_set_get_rotate_method,ITs_media_tools_startup,ITs_media_tools_cleanup},
	{"ITc_media_format_ref_p",ITc_media_format_ref_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_is_writable_p",ITc_media_format_is_writable_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_make_writable_p",ITc_media_format_make_writable_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_video_mime_p",ITc_media_format_set_video_mime_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_video_width_p",ITc_media_format_set_video_width_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_video_height_p",ITc_media_format_set_video_height_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_video_avg_bps_p",ITc_media_format_set_video_avg_bps_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_video_max_bps_p",ITc_media_format_set_video_max_bps_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_get_video_info_p",ITc_media_format_get_video_info_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_audio_mime_p",ITc_media_format_set_audio_mime_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_audio_channel_p",ITc_media_format_set_audio_channel_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_audio_samplerate_p",ITc_media_format_set_audio_samplerate_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_audio_bit_p",ITc_media_format_set_audio_bit_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_audio_avg_bps_p",ITc_media_format_set_audio_avg_bps_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_get_audio_info_p",ITc_media_format_get_audio_info_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_audio_aac_type_p",ITc_media_format_set_audio_aac_type_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_get_audio_aac_type_p",ITc_media_format_get_audio_aac_type_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_get_type_p",ITc_media_format_get_type_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_get_video_frame_rate_p",ITc_media_format_set_get_video_frame_rate_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_get_container_mime_p",ITc_media_format_set_get_container_mime_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_text_mime_set_text_type_get_text_info_p",ITc_media_format_set_text_mime_set_text_type_get_text_info_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_get_audio_aac_header_type_p",ITc_media_format_set_get_audio_aac_header_type_p,ITs_media_format_startup,ITs_media_format_cleanup},
	{"ITc_media_format_set_extra_p",ITc_media_format_set_extra_p,ITs_media_format_startup,ITs_media_format_cleanup}, 
	{"ITc_media_format_get_extra_p",ITc_media_format_get_extra_p,ITs_media_format_startup,ITs_media_format_cleanup}, 
	{"ITc_media_format_set_get_audio_channel_mask_p", ITc_media_format_set_get_audio_channel_mask_p, ITs_media_format_startup, ITs_media_format_cleanup},
	{"ITc_media_format_channel_positions_to_from_mask_p", ITc_media_format_channel_positions_to_from_mask_p, ITs_media_format_startup, ITs_media_format_cleanup},
	{"ITc_media_format_is_little_endian_p", ITc_media_format_is_little_endian_p, ITs_media_format_startup, ITs_media_format_cleanup},
	{"ITc_media_format_get_audio_bit_depth_p", ITc_media_format_get_audio_bit_depth_p, ITs_media_format_startup, ITs_media_format_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CAPI-MEDIA-TOOL-NATIVE_H__
