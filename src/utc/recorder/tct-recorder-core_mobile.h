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
#ifndef __TCT_RECORDER_NATIVE_H__
#define __TCT_RECORDER_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_media_recorder_startup(void);
extern void utc_media_recorder_cleanup(void);
extern void utc_media_recorder_callback_startup(void);
extern void utc_media_recorder_callback_cleanup(void);
extern void utc_media_recorder_lifecycle_startup(void);

extern int utc_media_recorder_attr_get_audio_channel_p(void);
extern int utc_media_recorder_attr_get_audio_channel_n1(void);
extern int utc_media_recorder_attr_get_audio_channel_n2(void);
extern int utc_media_recorder_attr_get_audio_device_p(void);
extern int utc_media_recorder_attr_get_audio_device_n1(void);
extern int utc_media_recorder_attr_get_audio_device_n2(void);
extern int utc_media_recorder_attr_get_audio_encoder_bitrate_p(void);
extern int utc_media_recorder_attr_get_audio_encoder_bitrate_n1(void);
extern int utc_media_recorder_attr_get_audio_encoder_bitrate_n2(void);
extern int utc_media_recorder_attr_get_audio_samplerate_p(void);
extern int utc_media_recorder_attr_get_audio_samplerate_n1(void);
extern int utc_media_recorder_attr_get_audio_samplerate_n2(void);
extern int utc_media_recorder_attr_get_orientation_tag_p(void);
extern int utc_media_recorder_attr_get_orientation_tag_n1(void);
extern int utc_media_recorder_attr_get_orientation_tag_n2(void);
extern int utc_media_recorder_attr_get_recording_motion_rate_p(void);
extern int utc_media_recorder_attr_get_recording_motion_rate_n1(void);
extern int utc_media_recorder_attr_get_recording_motion_rate_n2(void);
extern int utc_media_recorder_attr_get_size_limit_p(void);
extern int utc_media_recorder_attr_get_size_limit_n1(void);
extern int utc_media_recorder_attr_get_size_limit_n2(void);
extern int utc_media_recorder_attr_get_time_limit_p(void);
extern int utc_media_recorder_attr_get_time_limit_n1(void);
extern int utc_media_recorder_attr_get_time_limit_n2(void);
extern int utc_media_recorder_attr_get_video_encoder_bitrate_p(void);
extern int utc_media_recorder_attr_get_video_encoder_bitrate_n1(void);
extern int utc_media_recorder_attr_get_video_encoder_bitrate_n2(void);
extern int utc_media_recorder_attr_is_muted_p(void);
extern int utc_media_recorder_attr_is_muted_n(void);
extern int utc_media_recorder_attr_set_audio_channel_p(void);
extern int utc_media_recorder_attr_set_audio_channel_n1(void);
extern int utc_media_recorder_attr_set_audio_channel_n2(void);
extern int utc_media_recorder_attr_set_audio_device_p(void);
extern int utc_media_recorder_attr_set_audio_device_n(void);
extern int utc_media_recorder_attr_set_audio_encoder_bitrate_p(void);
extern int utc_media_recorder_attr_set_audio_encoder_bitrate_n(void);
extern int utc_media_recorder_attr_set_audio_samplerate_p(void);
extern int utc_media_recorder_attr_set_audio_samplerate_n(void);
extern int utc_media_recorder_attr_set_size_limit_p(void);
extern int utc_media_recorder_attr_set_size_limit_n1(void);
extern int utc_media_recorder_attr_set_size_limit_n2(void);
extern int utc_media_recorder_attr_set_time_limit_p(void);
extern int utc_media_recorder_attr_set_time_limit_n1(void);
extern int utc_media_recorder_attr_set_time_limit_n2(void);
extern int utc_media_recorder_attr_set_video_encoder_bitrate_p(void);
extern int utc_media_recorder_attr_set_video_encoder_bitrate_n1(void);
extern int utc_media_recorder_attr_set_video_encoder_bitrate_n2(void);
extern int utc_media_recorder_attr_set_mute_p(void);
extern int utc_media_recorder_attr_set_mute_n(void);
extern int utc_media_recorder_attr_set_orientation_tag_p(void);
extern int utc_media_recorder_attr_set_orientation_tag_n1(void);
extern int utc_media_recorder_attr_set_orientation_tag_n2(void);
extern int utc_media_recorder_attr_set_recording_motion_rate_p(void);
extern int utc_media_recorder_attr_set_recording_motion_rate_n(void);
extern int utc_media_recorder_get_audio_encoder_p(void);
extern int utc_media_recorder_get_audio_encoder_n1(void);
extern int utc_media_recorder_get_audio_encoder_n2(void);
extern int utc_media_recorder_set_get_audio_encoder_p(void);
extern int utc_media_recorder_get_file_format_p(void);
extern int utc_media_recorder_get_file_format_n(void);
extern int utc_media_recorder_get_video_encoder_p(void);
extern int utc_media_recorder_get_video_encoder_n1(void);
extern int utc_media_recorder_get_video_encoder_n2(void);
extern int utc_media_recorder_set_get_video_encoder_p(void);
extern int utc_media_recorder_get_audio_level_p(void);
extern int utc_media_recorder_get_audio_level_n(void);
extern int utc_media_recorder_get_video_resolution_p(void);
extern int utc_media_recorder_get_video_resolution_n1(void);
extern int utc_media_recorder_get_video_resolution_n2(void);
extern int utc_media_recorder_set_audio_encoder_p(void);
extern int utc_media_recorder_set_audio_encoder_n1(void);
extern int utc_media_recorder_set_audio_encoder_n2(void);
extern int utc_media_recorder_set_audio_encoder_n3(void);
extern int utc_media_recorder_set_file_format_p(void);
extern int utc_media_recorder_set_file_format_n(void);
extern int utc_media_recorder_set_filename_p(void);
extern int utc_media_recorder_set_filename_n(void);
extern int utc_media_recorder_set_video_encoder_p(void);
extern int utc_media_recorder_set_video_encoder_n1(void);
extern int utc_media_recorder_set_video_encoder_n2(void);
extern int utc_media_recorder_set_video_resolution_p(void);
extern int utc_media_recorder_set_get_file_format_p(void);
extern int utc_media_recorder_set_video_resolution_n1(void);
extern int utc_media_recorder_set_video_resolution_n2(void);
extern int utc_media_recorder_get_filename_p(void);
extern int utc_media_recorder_get_filename_n(void);
extern int utc_media_recorder_set_sound_stream_info_p(void);
extern int utc_media_recorder_set_sound_stream_info_n(void);
extern int utc_media_recorder_foreach_supported_audio_encoder_p(void);
extern int utc_media_recorder_foreach_supported_audio_encoder_n(void);
extern int utc_media_recorder_foreach_supported_file_format_p(void);
extern int utc_media_recorder_foreach_supported_file_format_n(void);
extern int utc_media_recorder_foreach_supported_video_encoder_p(void);
extern int utc_media_recorder_foreach_supported_video_encoder_n(void);
extern int utc_media_recorder_foreach_supported_video_resolution_p(void);
extern int utc_media_recorder_foreach_supported_video_resolution_n(void);
extern int utc_media_recorder_set_recording_limit_reached_cb_p(void);
extern int utc_media_recorder_set_recording_limit_reached_cb_n(void);
extern int utc_media_recorder_set_recording_status_cb_p(void);
extern int utc_media_recorder_set_recording_status_cb_n(void);
extern int utc_media_recorder_set_state_changed_cb_p(void);
extern int utc_media_recorder_set_state_changed_cb_n(void);
extern int utc_media_recorder_set_interrupted_cb_p(void);
extern int utc_media_recorder_set_interrupted_cb_n(void);
extern int utc_media_recorder_set_audio_stream_cb_p(void);
extern int utc_media_recorder_set_audio_stream_cb_n(void);
extern int utc_media_recorder_set_error_cb_p(void);
extern int utc_media_recorder_set_error_cb_n(void);
extern int utc_media_recorder_unset_recording_limit_reached_cb_p(void);
extern int utc_media_recorder_unset_recording_limit_reached_cb_n(void);
extern int utc_media_recorder_unset_recording_status_cb_p(void);
extern int utc_media_recorder_unset_recording_status_cb_n(void);
extern int utc_media_recorder_unset_state_changed_cb_p(void);
extern int utc_media_recorder_unset_state_changed_cb_n(void);
extern int utc_media_recorder_unset_interrupted_cb_p(void);
extern int utc_media_recorder_unset_interrupted_cb_n(void);
extern int utc_media_recorder_unset_audio_stream_cb_p(void);
extern int utc_media_recorder_unset_audio_stream_cb_n(void);
extern int utc_media_recorder_unset_error_cb_p(void);
extern int utc_media_recorder_unset_error_cb_n(void);
extern int utc_media_recorder_add_device_state_changed_cb_p(void);
extern int utc_media_recorder_add_device_state_changed_cb_n1(void);
extern int utc_media_recorder_add_device_state_changed_cb_n2(void);
extern int utc_media_recorder_remove_device_state_changed_cb_p(void);
extern int utc_media_recorder_remove_device_state_changed_cb_n1(void);
extern int utc_media_recorder_remove_device_state_changed_cb_n2(void);
extern int utc_media_recorder_set_muxed_stream_cb_p(void);
extern int utc_media_recorder_set_muxed_stream_cb_n(void);
extern int utc_media_recorder_unset_muxed_stream_cb_p(void);
extern int utc_media_recorder_unset_muxed_stream_cb_n(void);
extern int utc_media_recorder_set_video_encode_decision_cb_p(void);
extern int utc_media_recorder_set_video_encode_decision_cb_n(void);
extern int utc_media_recorder_unset_video_encode_decision_cb_p(void);
extern int utc_media_recorder_unset_video_encode_decision_cb_n(void);
extern int utc_media_recorder_create_audiorecorder_n(void);
extern int utc_media_recorder_create_audiorecorder_p(void);
extern int utc_media_recorder_cancel_p(void);
extern int utc_media_recorder_cancel_n(void);
extern int utc_media_recorder_commit_p(void);
extern int utc_media_recorder_commit_n(void);
extern int utc_media_recorder_create_videorecorder_p(void);
extern int utc_media_recorder_create_videorecorder_n(void);
extern int utc_media_recorder_destroy_p(void);
extern int utc_media_recorder_destroy_n(void);
extern int utc_media_recorder_pause_p(void);
extern int utc_media_recorder_pause_n(void);
extern int utc_media_recorder_prepare_p(void);
extern int utc_media_recorder_prepare_n1(void);
extern int utc_media_recorder_prepare_n2(void);
extern int utc_media_recorder_start_p(void);
extern int utc_media_recorder_start_n(void);
extern int utc_media_recorder_unprepare_p(void);
extern int utc_media_recorder_unprepare_n1(void);
extern int utc_media_recorder_unprepare_n2(void);
extern int utc_media_recorder_get_state_p(void);
extern int utc_media_recorder_get_state_n1(void);
extern int utc_media_recorder_get_state_n2(void);
extern int utc_media_recorder_get_device_state_p(void);
extern int utc_media_recorder_get_device_state_n1(void);
extern int utc_media_recorder_get_device_state_n2(void);
extern int utc_media_recorder_set_interrupt_started_cb_p(void);
extern int utc_media_recorder_set_interrupt_started_cb_n1(void);
extern int utc_media_recorder_set_interrupt_started_cb_n2(void);
extern int utc_media_recorder_unset_interrupt_started_cb_p(void);
extern int utc_media_recorder_unset_interrupt_started_cb_n(void);

testcase tc_array[] = {
	{"utc_media_recorder_attr_get_audio_channel_p",utc_media_recorder_attr_get_audio_channel_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_audio_channel_n1",utc_media_recorder_attr_get_audio_channel_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_audio_channel_n2",utc_media_recorder_attr_get_audio_channel_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_audio_device_p",utc_media_recorder_attr_get_audio_device_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_audio_device_n1",utc_media_recorder_attr_get_audio_device_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_audio_device_n2",utc_media_recorder_attr_get_audio_device_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_audio_encoder_bitrate_p",utc_media_recorder_attr_get_audio_encoder_bitrate_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_audio_encoder_bitrate_n1",utc_media_recorder_attr_get_audio_encoder_bitrate_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_audio_encoder_bitrate_n2",utc_media_recorder_attr_get_audio_encoder_bitrate_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_audio_samplerate_p",utc_media_recorder_attr_get_audio_samplerate_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_audio_samplerate_n1",utc_media_recorder_attr_get_audio_samplerate_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_audio_samplerate_n2",utc_media_recorder_attr_get_audio_samplerate_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_orientation_tag_p",utc_media_recorder_attr_get_orientation_tag_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_orientation_tag_n1",utc_media_recorder_attr_get_orientation_tag_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_orientation_tag_n2",utc_media_recorder_attr_get_orientation_tag_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_recording_motion_rate_p",utc_media_recorder_attr_get_recording_motion_rate_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_recording_motion_rate_n1",utc_media_recorder_attr_get_recording_motion_rate_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_recording_motion_rate_n2",utc_media_recorder_attr_get_recording_motion_rate_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_size_limit_p",utc_media_recorder_attr_get_size_limit_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_size_limit_n1",utc_media_recorder_attr_get_size_limit_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_size_limit_n2",utc_media_recorder_attr_get_size_limit_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_time_limit_p",utc_media_recorder_attr_get_time_limit_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_time_limit_n1",utc_media_recorder_attr_get_time_limit_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_time_limit_n2",utc_media_recorder_attr_get_time_limit_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_video_encoder_bitrate_p",utc_media_recorder_attr_get_video_encoder_bitrate_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_video_encoder_bitrate_n1",utc_media_recorder_attr_get_video_encoder_bitrate_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_get_video_encoder_bitrate_n2",utc_media_recorder_attr_get_video_encoder_bitrate_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_is_muted_p",utc_media_recorder_attr_is_muted_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_is_muted_n",utc_media_recorder_attr_is_muted_n,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_audio_channel_p",utc_media_recorder_attr_set_audio_channel_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_audio_channel_n1",utc_media_recorder_attr_set_audio_channel_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_audio_channel_n2",utc_media_recorder_attr_set_audio_channel_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_audio_device_p",utc_media_recorder_attr_set_audio_device_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_audio_device_n",utc_media_recorder_attr_set_audio_device_n,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_audio_encoder_bitrate_p",utc_media_recorder_attr_set_audio_encoder_bitrate_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_audio_encoder_bitrate_n",utc_media_recorder_attr_set_audio_encoder_bitrate_n,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_audio_samplerate_p",utc_media_recorder_attr_set_audio_samplerate_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_audio_samplerate_n",utc_media_recorder_attr_set_audio_samplerate_n,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_size_limit_p",utc_media_recorder_attr_set_size_limit_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_size_limit_n1",utc_media_recorder_attr_set_size_limit_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_size_limit_n2",utc_media_recorder_attr_set_size_limit_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_time_limit_p",utc_media_recorder_attr_set_time_limit_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_time_limit_n1",utc_media_recorder_attr_set_time_limit_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_time_limit_n2",utc_media_recorder_attr_set_time_limit_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_video_encoder_bitrate_p",utc_media_recorder_attr_set_video_encoder_bitrate_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_video_encoder_bitrate_n1",utc_media_recorder_attr_set_video_encoder_bitrate_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_video_encoder_bitrate_n2",utc_media_recorder_attr_set_video_encoder_bitrate_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_mute_p",utc_media_recorder_attr_set_mute_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_mute_n",utc_media_recorder_attr_set_mute_n,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_orientation_tag_p",utc_media_recorder_attr_set_orientation_tag_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_orientation_tag_n1",utc_media_recorder_attr_set_orientation_tag_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_orientation_tag_n2",utc_media_recorder_attr_set_orientation_tag_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_recording_motion_rate_p",utc_media_recorder_attr_set_recording_motion_rate_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_attr_set_recording_motion_rate_n",utc_media_recorder_attr_set_recording_motion_rate_n,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_audio_encoder_p",utc_media_recorder_get_audio_encoder_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_audio_encoder_n1",utc_media_recorder_get_audio_encoder_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_audio_encoder_n2",utc_media_recorder_get_audio_encoder_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_get_audio_encoder_p",utc_media_recorder_set_get_audio_encoder_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_file_format_p",utc_media_recorder_get_file_format_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_file_format_n",utc_media_recorder_get_file_format_n,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_video_encoder_p",utc_media_recorder_get_video_encoder_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_video_encoder_n1",utc_media_recorder_get_video_encoder_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_video_encoder_n2",utc_media_recorder_get_video_encoder_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_get_video_encoder_p",utc_media_recorder_set_get_video_encoder_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_audio_level_p",utc_media_recorder_get_audio_level_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_audio_level_n",utc_media_recorder_get_audio_level_n,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_video_resolution_p",utc_media_recorder_get_video_resolution_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_video_resolution_n1",utc_media_recorder_get_video_resolution_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_video_resolution_n2",utc_media_recorder_get_video_resolution_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_audio_encoder_p",utc_media_recorder_set_audio_encoder_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_audio_encoder_n1",utc_media_recorder_set_audio_encoder_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_audio_encoder_n2",utc_media_recorder_set_audio_encoder_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_audio_encoder_n3",utc_media_recorder_set_audio_encoder_n3,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_file_format_p",utc_media_recorder_set_file_format_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_file_format_n",utc_media_recorder_set_file_format_n,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_filename_p",utc_media_recorder_set_filename_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_filename_n",utc_media_recorder_set_filename_n,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_video_encoder_p",utc_media_recorder_set_video_encoder_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_video_encoder_n1",utc_media_recorder_set_video_encoder_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_video_encoder_n2",utc_media_recorder_set_video_encoder_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_video_resolution_p",utc_media_recorder_set_video_resolution_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_get_file_format_p",utc_media_recorder_set_get_file_format_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_video_resolution_n1",utc_media_recorder_set_video_resolution_n1,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_video_resolution_n2",utc_media_recorder_set_video_resolution_n2,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_filename_p",utc_media_recorder_get_filename_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_get_filename_n",utc_media_recorder_get_filename_n,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_sound_stream_info_p",utc_media_recorder_set_sound_stream_info_p,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_set_sound_stream_info_n",utc_media_recorder_set_sound_stream_info_n,utc_media_recorder_startup,utc_media_recorder_cleanup},
	{"utc_media_recorder_foreach_supported_audio_encoder_p",utc_media_recorder_foreach_supported_audio_encoder_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_foreach_supported_audio_encoder_n",utc_media_recorder_foreach_supported_audio_encoder_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_foreach_supported_file_format_p",utc_media_recorder_foreach_supported_file_format_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_foreach_supported_file_format_n",utc_media_recorder_foreach_supported_file_format_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_foreach_supported_video_encoder_p",utc_media_recorder_foreach_supported_video_encoder_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_foreach_supported_video_encoder_n",utc_media_recorder_foreach_supported_video_encoder_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_foreach_supported_video_resolution_p",utc_media_recorder_foreach_supported_video_resolution_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_foreach_supported_video_resolution_n",utc_media_recorder_foreach_supported_video_resolution_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_recording_limit_reached_cb_p",utc_media_recorder_set_recording_limit_reached_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_recording_limit_reached_cb_n",utc_media_recorder_set_recording_limit_reached_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_recording_status_cb_p",utc_media_recorder_set_recording_status_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_recording_status_cb_n",utc_media_recorder_set_recording_status_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_state_changed_cb_p",utc_media_recorder_set_state_changed_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_state_changed_cb_n",utc_media_recorder_set_state_changed_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_interrupted_cb_p",utc_media_recorder_set_interrupted_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_interrupted_cb_n",utc_media_recorder_set_interrupted_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_audio_stream_cb_p",utc_media_recorder_set_audio_stream_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_audio_stream_cb_n",utc_media_recorder_set_audio_stream_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_error_cb_p",utc_media_recorder_set_error_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_error_cb_n",utc_media_recorder_set_error_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_recording_limit_reached_cb_p",utc_media_recorder_unset_recording_limit_reached_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_recording_limit_reached_cb_n",utc_media_recorder_unset_recording_limit_reached_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_recording_status_cb_p",utc_media_recorder_unset_recording_status_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_recording_status_cb_n",utc_media_recorder_unset_recording_status_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_state_changed_cb_p",utc_media_recorder_unset_state_changed_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_state_changed_cb_n",utc_media_recorder_unset_state_changed_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_interrupted_cb_p",utc_media_recorder_unset_interrupted_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_interrupted_cb_n",utc_media_recorder_unset_interrupted_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_audio_stream_cb_p",utc_media_recorder_unset_audio_stream_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_audio_stream_cb_n",utc_media_recorder_unset_audio_stream_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_error_cb_p",utc_media_recorder_unset_error_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_error_cb_n",utc_media_recorder_unset_error_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_add_device_state_changed_cb_p",utc_media_recorder_add_device_state_changed_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_add_device_state_changed_cb_n1",utc_media_recorder_add_device_state_changed_cb_n1,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_add_device_state_changed_cb_n2",utc_media_recorder_add_device_state_changed_cb_n2,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_remove_device_state_changed_cb_p",utc_media_recorder_remove_device_state_changed_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_remove_device_state_changed_cb_n1",utc_media_recorder_remove_device_state_changed_cb_n1,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_remove_device_state_changed_cb_n2",utc_media_recorder_remove_device_state_changed_cb_n2,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_muxed_stream_cb_p",utc_media_recorder_set_muxed_stream_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_muxed_stream_cb_n",utc_media_recorder_set_muxed_stream_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_muxed_stream_cb_p",utc_media_recorder_unset_muxed_stream_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_muxed_stream_cb_n",utc_media_recorder_unset_muxed_stream_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_video_encode_decision_cb_p",utc_media_recorder_set_video_encode_decision_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_video_encode_decision_cb_n",utc_media_recorder_set_video_encode_decision_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_video_encode_decision_cb_p",utc_media_recorder_unset_video_encode_decision_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_video_encode_decision_cb_n",utc_media_recorder_unset_video_encode_decision_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_create_audiorecorder_n",utc_media_recorder_create_audiorecorder_n,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_create_audiorecorder_p",utc_media_recorder_create_audiorecorder_p,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_cancel_p",utc_media_recorder_cancel_p,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_cancel_n",utc_media_recorder_cancel_n,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_commit_p",utc_media_recorder_commit_p,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_commit_n",utc_media_recorder_commit_n,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_create_videorecorder_p",utc_media_recorder_create_videorecorder_p,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_create_videorecorder_n",utc_media_recorder_create_videorecorder_n,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_destroy_p",utc_media_recorder_destroy_p,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_destroy_n",utc_media_recorder_destroy_n,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_pause_p",utc_media_recorder_pause_p,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_pause_n",utc_media_recorder_pause_n,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_prepare_p",utc_media_recorder_prepare_p,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_prepare_n1",utc_media_recorder_prepare_n1,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_prepare_n2",utc_media_recorder_prepare_n2,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_start_p",utc_media_recorder_start_p,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_start_n",utc_media_recorder_start_n,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_unprepare_p",utc_media_recorder_unprepare_p,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_unprepare_n1",utc_media_recorder_unprepare_n1,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_unprepare_n2",utc_media_recorder_unprepare_n2,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_get_state_p",utc_media_recorder_get_state_p,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_get_state_n1",utc_media_recorder_get_state_n1,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_get_state_n2",utc_media_recorder_get_state_n2,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_get_device_state_p",utc_media_recorder_get_device_state_p,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_get_device_state_n1",utc_media_recorder_get_device_state_n1,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_get_device_state_n2",utc_media_recorder_get_device_state_n2,utc_media_recorder_lifecycle_startup,NULL},
	{"utc_media_recorder_set_interrupt_started_cb_p",utc_media_recorder_set_interrupt_started_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_interrupt_started_cb_n1",utc_media_recorder_set_interrupt_started_cb_n1,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_set_interrupt_started_cb_n2",utc_media_recorder_set_interrupt_started_cb_n2,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_interrupt_started_cb_p",utc_media_recorder_unset_interrupt_started_cb_p,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},
	{"utc_media_recorder_unset_interrupt_started_cb_n",utc_media_recorder_unset_interrupt_started_cb_n,utc_media_recorder_callback_startup,utc_media_recorder_callback_cleanup},

	{NULL, NULL}
};

#endif // __TCT_RECORDER_NATIVE_H__
