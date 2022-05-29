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
#ifndef __TCT_RECORDER-NATIVE_H__
#define __TCT_RECORDER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_recorder_startup(void);
extern void ITs_recorder_cleanup(void);
extern void ITs_recorder_attr_startup(void);
extern void ITs_recorder_attr_cleanup(void);

extern int ITc_recorder_create_audiorecorder_p(void);
extern int ITc_recorder_create_videorecorder_p(void);
extern int ITc_recorder_prepare_unprepare_p(void);
extern int ITc_recorder_start_cancel_p(void);
extern int ITc_recorder_start_commit_p(void);
extern int ITc_recorder_get_state_p(void);
extern int ITc_recorder_pause_p(void);
extern int ITc_recorder_set_get_filename_p(void);
extern int ITc_recorder_set_get_audio_encoder_p(void);
extern int ITc_recorder_set_get_video_encoder_p(void);
extern int ITc_recorder_set_get_video_resolution_p(void);
extern int ITc_recorder_set_get_file_format_p(void);
extern int ITc_recorder_get_audio_level_p(void);
extern int ITc_recorder_set_unset_interrupted_cb_p(void);
extern int ITc_recorder_set_unset_error_cb_p(void);
extern int ITc_recorder_set_unset_recording_limit_reached_cb_p(void);
extern int ITc_recorder_set_unset_recording_status_cb_p(void);
extern int ITc_recorder_set_unset_state_changed_cb_p(void);
extern int ITc_recorder_set_unset_audio_stream_cb_p(void);
extern int ITc_recorder_foreach_supported_file_format_p(void);
extern int ITc_recorder_foreach_supported_audio_encoder_p(void);
extern int ITc_recorder_foreach_supported_video_encoder_p(void);
extern int ITc_recorder_foreach_supported_video_resolution_p(void);
extern int ITc_recorder_set_sound_stream_info_p(void);
extern int ITc_recorder_get_device_state_p(void);
extern int ITc_recorder_add_remove_device_state_changed_cb_p(void);
extern int ITc_recorder_set_unset_muxed_stream_cb_p(void);
extern int ITc_recorder_set_unset_video_encode_decision_cb_p(void);
extern int ITc_recorder_attr_set_get_audio_channel_p(void);
extern int ITc_recorder_attr_set_get_audio_device_p(void);
extern int ITc_recorder_attr_set_get_audio_encoder_bitrate_p(void);
extern int ITc_recorder_attr_set_get_audio_samplerate_p(void);
extern int ITc_recorder_attr_set_get_orientation_tag_p(void);
extern int ITc_recorder_attr_set_get_recording_motion_rate_p(void);
extern int ITc_recorder_attr_set_get_size_limit_p(void);
extern int ITc_recorder_attr_set_get_time_limit_p(void);
extern int ITc_recorder_attr_set_get_video_encoder_bitrate_p(void);
extern int ITc_recorder_attr_mute_p(void);

testcase tc_array[] = {
	{"ITc_recorder_create_audiorecorder_p",ITc_recorder_create_audiorecorder_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_create_videorecorder_p",ITc_recorder_create_videorecorder_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_prepare_unprepare_p",ITc_recorder_prepare_unprepare_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_start_cancel_p",ITc_recorder_start_cancel_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_start_commit_p",ITc_recorder_start_commit_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_get_state_p",ITc_recorder_get_state_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_pause_p",ITc_recorder_pause_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_get_filename_p",ITc_recorder_set_get_filename_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_get_audio_encoder_p",ITc_recorder_set_get_audio_encoder_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_get_video_encoder_p",ITc_recorder_set_get_video_encoder_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_get_video_resolution_p",ITc_recorder_set_get_video_resolution_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_get_file_format_p",ITc_recorder_set_get_file_format_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_get_audio_level_p",ITc_recorder_get_audio_level_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_unset_interrupted_cb_p",ITc_recorder_set_unset_interrupted_cb_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_unset_error_cb_p",ITc_recorder_set_unset_error_cb_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_unset_recording_limit_reached_cb_p",ITc_recorder_set_unset_recording_limit_reached_cb_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_unset_recording_status_cb_p",ITc_recorder_set_unset_recording_status_cb_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_unset_state_changed_cb_p",ITc_recorder_set_unset_state_changed_cb_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_unset_audio_stream_cb_p",ITc_recorder_set_unset_audio_stream_cb_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_foreach_supported_file_format_p",ITc_recorder_foreach_supported_file_format_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_foreach_supported_audio_encoder_p",ITc_recorder_foreach_supported_audio_encoder_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_foreach_supported_video_encoder_p",ITc_recorder_foreach_supported_video_encoder_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_foreach_supported_video_resolution_p",ITc_recorder_foreach_supported_video_resolution_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_sound_stream_info_p",ITc_recorder_set_sound_stream_info_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_get_device_state_p",ITc_recorder_get_device_state_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_add_remove_device_state_changed_cb_p",ITc_recorder_add_remove_device_state_changed_cb_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_unset_muxed_stream_cb_p",ITc_recorder_set_unset_muxed_stream_cb_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_set_unset_video_encode_decision_cb_p",ITc_recorder_set_unset_video_encode_decision_cb_p,ITs_recorder_startup,ITs_recorder_cleanup},
	{"ITc_recorder_attr_set_get_audio_channel_p",ITc_recorder_attr_set_get_audio_channel_p,ITs_recorder_attr_startup,ITs_recorder_attr_cleanup},
	{"ITc_recorder_attr_set_get_audio_device_p",ITc_recorder_attr_set_get_audio_device_p,ITs_recorder_attr_startup,ITs_recorder_attr_cleanup},
	{"ITc_recorder_attr_set_get_audio_encoder_bitrate_p",ITc_recorder_attr_set_get_audio_encoder_bitrate_p,ITs_recorder_attr_startup,ITs_recorder_attr_cleanup},
	{"ITc_recorder_attr_set_get_audio_samplerate_p",ITc_recorder_attr_set_get_audio_samplerate_p,ITs_recorder_attr_startup,ITs_recorder_attr_cleanup},
	{"ITc_recorder_attr_set_get_orientation_tag_p",ITc_recorder_attr_set_get_orientation_tag_p,ITs_recorder_attr_startup,ITs_recorder_attr_cleanup},
	{"ITc_recorder_attr_set_get_recording_motion_rate_p",ITc_recorder_attr_set_get_recording_motion_rate_p,ITs_recorder_attr_startup,ITs_recorder_attr_cleanup},
	{"ITc_recorder_attr_set_get_size_limit_p",ITc_recorder_attr_set_get_size_limit_p,ITs_recorder_attr_startup,ITs_recorder_attr_cleanup},
	{"ITc_recorder_attr_set_get_time_limit_p",ITc_recorder_attr_set_get_time_limit_p,ITs_recorder_attr_startup,ITs_recorder_attr_cleanup},
	{"ITc_recorder_attr_set_get_video_encoder_bitrate_p",ITc_recorder_attr_set_get_video_encoder_bitrate_p,ITs_recorder_attr_startup,ITs_recorder_attr_cleanup},
	{"ITc_recorder_attr_mute_p",ITc_recorder_attr_mute_p,ITs_recorder_attr_startup,ITs_recorder_attr_cleanup},
	{NULL, NULL}
};

#endif // __TCT_RECORDER-NATIVE_H__
