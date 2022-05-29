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
#ifndef __TCT_AUDIO-IO-NATIVE_H__
#define __TCT_AUDIO-IO-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_audio_input_startup(void);
extern void ITs_audio_input_cleanup(void);
extern void ITs_audio_input1_startup(void);
extern void ITs_audio_input1_cleanup(void);
extern void ITs_audio_output1_startup(void);
extern void ITs_audio_output1_cleanup(void);
extern void ITs_audio_output_startup(void);
extern void ITs_audio_output_cleanup(void);

extern int ITc_audio_in_prepare_unprepare_p(void);
extern int ITc_audio_in_get_buffer_size_p(void);
extern int ITc_audio_in_read_p(void);
extern int ITc_audio_in_get_channel_p(void);
extern int ITc_audio_in_get_sample_type_p(void);
extern int ITc_audio_in_get_sample_rate_p(void);
extern int ITc_audio_in_peek_drop_p(void);
extern int ITc_audio_in_set_unset_stream_cb_p(void);
extern int ITc_audio_in_resume_pause_p(void);
extern int ITc_audio_in_flush_p(void);
extern int ITc_audio_in_set_unset_state_changed_cb_p(void);
extern int ITc_audio_in_set_sound_stream_info_p(void);
extern int ITc_audio_in_create_destroy_p(void);
extern int ITc_audio_in_set_get_volume_p(void);
extern int ITc_audio_out_create_new_destroy_p(void);
extern int ITc_audio_out_prepare_unprepare_p(void);
extern int ITc_audio_out_get_buffer_size_p(void);
extern int ITc_audio_out_get_channel_p(void);
extern int ITc_audio_out_get_sample_type_p(void);
extern int ITc_audio_out_get_sample_rate_p(void);
extern int ITc_audio_out_get_sound_type_p(void);
extern int ITc_audio_out_write_p(void);
extern int ITc_audio_out_set_unset_stream_cb_p(void);
extern int ITc_audio_out_set_sound_stream_info_p(void);
extern int ITc_audio_out_resume_pause_p(void);
extern int ITc_audio_out_drain_p(void);
extern int ITc_audio_out_flush_p(void);
extern int ITc_audio_out_set_unset_state_changed_cb_p(void);

testcase tc_array[] = {
	{"ITc_audio_in_prepare_unprepare_p",ITc_audio_in_prepare_unprepare_p,ITs_audio_input_startup,ITs_audio_input_cleanup},
	{"ITc_audio_in_get_buffer_size_p",ITc_audio_in_get_buffer_size_p,ITs_audio_input_startup,ITs_audio_input_cleanup},
	{"ITc_audio_in_read_p",ITc_audio_in_read_p,ITs_audio_input_startup,ITs_audio_input_cleanup},
	{"ITc_audio_in_get_channel_p",ITc_audio_in_get_channel_p,ITs_audio_input_startup,ITs_audio_input_cleanup},
	{"ITc_audio_in_get_sample_type_p",ITc_audio_in_get_sample_type_p,ITs_audio_input_startup,ITs_audio_input_cleanup},
	{"ITc_audio_in_get_sample_rate_p",ITc_audio_in_get_sample_rate_p,ITs_audio_input_startup,ITs_audio_input_cleanup},
	{"ITc_audio_in_peek_drop_p",ITc_audio_in_peek_drop_p,ITs_audio_input_startup,ITs_audio_input_cleanup},
	{"ITc_audio_in_set_unset_stream_cb_p",ITc_audio_in_set_unset_stream_cb_p,ITs_audio_input_startup,ITs_audio_input_cleanup},
	{"ITc_audio_in_resume_pause_p",ITc_audio_in_resume_pause_p,ITs_audio_input_startup,ITs_audio_input_cleanup},
	{"ITc_audio_in_flush_p",ITc_audio_in_flush_p,ITs_audio_input_startup,ITs_audio_input_cleanup},
	{"ITc_audio_in_set_unset_state_changed_cb_p",ITc_audio_in_set_unset_state_changed_cb_p,ITs_audio_input_startup,ITs_audio_input_cleanup},
	{"ITc_audio_in_set_sound_stream_info_p",ITc_audio_in_set_sound_stream_info_p,ITs_audio_input_startup,ITs_audio_input_cleanup},
	{"ITc_audio_in_create_destroy_p",ITc_audio_in_create_destroy_p,ITs_audio_input1_startup,ITs_audio_input1_cleanup},
	{"ITc_audio_in_set_get_volume_p",ITc_audio_in_set_get_volume_p,ITs_audio_input_startup,ITs_audio_input_cleanup},
	{"ITc_audio_out_create_new_destroy_p",ITc_audio_out_create_new_destroy_p,ITs_audio_output1_startup,ITs_audio_output1_cleanup},
	{"ITc_audio_out_prepare_unprepare_p",ITc_audio_out_prepare_unprepare_p,ITs_audio_output_startup,ITs_audio_output_cleanup},
	{"ITc_audio_out_get_buffer_size_p",ITc_audio_out_get_buffer_size_p,ITs_audio_output_startup,ITs_audio_output_cleanup},
	{"ITc_audio_out_get_channel_p",ITc_audio_out_get_channel_p,ITs_audio_output_startup,ITs_audio_output_cleanup},
	{"ITc_audio_out_get_sample_type_p",ITc_audio_out_get_sample_type_p,ITs_audio_output_startup,ITs_audio_output_cleanup},
	{"ITc_audio_out_get_sample_rate_p",ITc_audio_out_get_sample_rate_p,ITs_audio_output_startup,ITs_audio_output_cleanup},
	{"ITc_audio_out_get_sound_type_p",ITc_audio_out_get_sound_type_p,ITs_audio_output_startup,ITs_audio_output_cleanup},
	{"ITc_audio_out_write_p",ITc_audio_out_write_p,ITs_audio_output_startup,ITs_audio_output_cleanup},
	{"ITc_audio_out_set_unset_stream_cb_p",ITc_audio_out_set_unset_stream_cb_p,ITs_audio_output_startup,ITs_audio_output_cleanup},
	{"ITc_audio_out_set_sound_stream_info_p",ITc_audio_out_set_sound_stream_info_p,ITs_audio_output_startup,ITs_audio_output_cleanup},
	{"ITc_audio_out_resume_pause_p",ITc_audio_out_resume_pause_p,ITs_audio_output_startup,ITs_audio_output_cleanup},
	{"ITc_audio_out_drain_p",ITc_audio_out_drain_p,ITs_audio_output_startup,ITs_audio_output_cleanup},
	{"ITc_audio_out_flush_p",ITc_audio_out_flush_p,ITs_audio_output_startup,ITs_audio_output_cleanup},
	{"ITc_audio_out_set_unset_state_changed_cb_p",ITc_audio_out_set_unset_state_changed_cb_p,ITs_audio_output_startup,ITs_audio_output_cleanup},
	{NULL, NULL}
};

#endif // __TCT_AUDIO-IO-NATIVE_H__
