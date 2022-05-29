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

extern void utc_media_audio_in_startup(void);
extern void utc_media_audio_in_cleanup(void);
extern void utc_media_audio_out_startup(void);
extern void utc_media_audio_out_cleanup(void);

extern int utc_media_audio_in_create_p(void);
extern int utc_media_audio_in_create_n(void);
extern int utc_media_audio_in_destroy_p(void);
extern int utc_media_audio_in_destroy_n(void);
extern int utc_media_audio_in_read_p(void);
extern int utc_media_audio_in_read_n1(void);
extern int utc_media_audio_in_read_n2(void);
extern int utc_media_audio_in_get_buffer_size_p(void);
extern int utc_media_audio_in_get_buffer_size_n(void);
extern int utc_media_audio_in_get_sample_rate_p(void);
extern int utc_media_audio_in_get_sample_rate_n(void);
extern int utc_media_audio_in_get_channel_p(void);
extern int utc_media_audio_in_get_channel_n(void);
extern int utc_media_audio_in_get_sample_type_p(void);
extern int utc_media_audio_in_get_sample_type_n(void);
extern int utc_media_audio_in_prepare_p(void);
extern int utc_media_audio_in_prepare_n(void);
extern int utc_media_audio_in_unprepare_p(void);
extern int utc_media_audio_in_unprepare_n(void);
extern int utc_media_audio_in_set_stream_cb_p(void);
extern int utc_media_audio_in_set_stream_cb_n(void);
extern int utc_media_audio_in_unset_stream_cb_p(void);
extern int utc_media_audio_in_unset_stream_cb_n(void);
extern int utc_media_audio_in_peek_p(void);
extern int utc_media_audio_in_peek_n1(void);
extern int utc_media_audio_in_peek_n2(void);
extern int utc_media_audio_in_peek_n3(void);
extern int utc_media_audio_in_drop_p(void);
extern int utc_media_audio_in_drop_n(void);
extern int utc_media_audio_in_set_sound_stream_info_p(void);
extern int utc_media_audio_in_set_sound_stream_info_n(void);
extern int utc_media_audio_in_pause_p(void);
extern int utc_media_audio_in_pause_n1(void);
extern int utc_media_audio_in_pause_n2(void);
extern int utc_media_audio_in_resume_p(void);
extern int utc_media_audio_in_resume_n1(void);
extern int utc_media_audio_in_resume_n2(void);
extern int utc_media_audio_in_flush_p(void);
extern int utc_media_audio_in_flush_n(void);
extern int utc_media_audio_in_set_state_changed_cb_p(void);
extern int utc_media_audio_in_set_state_changed_cb_n(void);
extern int utc_media_audio_in_unset_state_changed_cb_p(void);
extern int utc_media_audio_in_unset_state_changed_cb_n(void);
extern int utc_media_audio_in_set_volume_p(void);
extern int utc_media_audio_in_set_volume_n(void);
extern int utc_media_audio_in_get_volume_p(void);
extern int utc_media_audio_in_get_volume_n(void);
extern int utc_media_audio_out_create_new_p(void);
extern int utc_media_audio_out_create_new_n(void);
extern int utc_media_audio_out_destroy_p(void);
extern int utc_media_audio_out_destroy_n(void);
extern int utc_media_audio_out_write_p(void);
extern int utc_media_audio_out_write_n1(void);
extern int utc_media_audio_out_write_n2(void);
extern int utc_media_audio_out_get_buffer_size_p(void);
extern int utc_media_audio_out_get_buffer_size_n(void);
extern int utc_media_audio_out_get_sample_rate_p(void);
extern int utc_media_audio_out_get_sample_rate_n(void);
extern int utc_media_audio_out_get_channel_p(void);
extern int utc_media_audio_out_get_channel_n(void);
extern int utc_media_audio_out_get_sample_type_p(void);
extern int utc_media_audio_out_get_sample_type_n(void);
extern int utc_media_audio_out_get_sound_type_p(void);
extern int utc_media_audio_out_get_sound_type_n(void);
extern int utc_media_audio_out_prepare_p(void);
extern int utc_media_audio_out_prepare_n(void);
extern int utc_media_audio_out_unprepare_p(void);
extern int utc_media_audio_out_unprepare_n(void);
extern int utc_media_audio_out_set_stream_cb_p(void);
extern int utc_media_audio_out_set_stream_cb_n(void);
extern int utc_media_audio_out_unset_stream_cb_p(void);
extern int utc_media_audio_out_unset_stream_cb_n(void);
extern int utc_media_audio_out_set_sound_stream_info_p(void);
extern int utc_media_audio_out_set_sound_stream_info_n(void);
extern int utc_media_audio_out_pause_p(void);
extern int utc_media_audio_out_pause_n1(void);
extern int utc_media_audio_out_pause_n2(void);
extern int utc_media_audio_out_resume_p(void);
extern int utc_media_audio_out_resume_n1(void);
extern int utc_media_audio_out_resume_n2(void);
extern int utc_media_audio_out_drain_p(void);
extern int utc_media_audio_out_drain_n(void);
extern int utc_media_audio_out_flush_p(void);
extern int utc_media_audio_out_flush_n(void);
extern int utc_media_audio_out_set_state_changed_cb_p(void);
extern int utc_media_audio_out_set_state_changed_cb_n(void);
extern int utc_media_audio_out_unset_state_changed_cb_p(void);
extern int utc_media_audio_out_unset_state_changed_cb_n(void);

testcase tc_array[] = {
	{"utc_media_audio_in_create_p",utc_media_audio_in_create_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_create_n",utc_media_audio_in_create_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_destroy_p",utc_media_audio_in_destroy_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_destroy_n",utc_media_audio_in_destroy_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_read_p",utc_media_audio_in_read_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_read_n1",utc_media_audio_in_read_n1,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_read_n2",utc_media_audio_in_read_n2,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_get_buffer_size_p",utc_media_audio_in_get_buffer_size_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_get_buffer_size_n",utc_media_audio_in_get_buffer_size_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_get_sample_rate_p",utc_media_audio_in_get_sample_rate_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_get_sample_rate_n",utc_media_audio_in_get_sample_rate_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_get_channel_p",utc_media_audio_in_get_channel_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_get_channel_n",utc_media_audio_in_get_channel_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_get_sample_type_p",utc_media_audio_in_get_sample_type_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_get_sample_type_n",utc_media_audio_in_get_sample_type_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_prepare_p",utc_media_audio_in_prepare_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_prepare_n",utc_media_audio_in_prepare_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_unprepare_p",utc_media_audio_in_unprepare_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_unprepare_n",utc_media_audio_in_unprepare_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_set_stream_cb_p",utc_media_audio_in_set_stream_cb_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_set_stream_cb_n",utc_media_audio_in_set_stream_cb_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_unset_stream_cb_p",utc_media_audio_in_unset_stream_cb_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_unset_stream_cb_n",utc_media_audio_in_unset_stream_cb_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_peek_p",utc_media_audio_in_peek_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_peek_n1",utc_media_audio_in_peek_n1,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_peek_n2",utc_media_audio_in_peek_n2,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_peek_n3",utc_media_audio_in_peek_n3,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_drop_p",utc_media_audio_in_drop_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_drop_n",utc_media_audio_in_drop_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_set_sound_stream_info_p",utc_media_audio_in_set_sound_stream_info_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_set_sound_stream_info_n",utc_media_audio_in_set_sound_stream_info_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_pause_p",utc_media_audio_in_pause_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_pause_n1",utc_media_audio_in_pause_n1,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_pause_n2",utc_media_audio_in_pause_n2,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_resume_p",utc_media_audio_in_resume_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_resume_n1",utc_media_audio_in_resume_n1,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_resume_n2",utc_media_audio_in_resume_n2,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_flush_p",utc_media_audio_in_flush_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_flush_n",utc_media_audio_in_flush_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_set_state_changed_cb_p",utc_media_audio_in_set_state_changed_cb_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_set_state_changed_cb_n",utc_media_audio_in_set_state_changed_cb_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_unset_state_changed_cb_p",utc_media_audio_in_unset_state_changed_cb_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_unset_state_changed_cb_n",utc_media_audio_in_unset_state_changed_cb_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_set_volume_p",utc_media_audio_in_set_volume_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_set_volume_n",utc_media_audio_in_set_volume_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_get_volume_p",utc_media_audio_in_get_volume_p,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_in_get_volume_n",utc_media_audio_in_get_volume_n,utc_media_audio_in_startup,utc_media_audio_in_cleanup},
	{"utc_media_audio_out_create_new_p",utc_media_audio_out_create_new_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_create_new_n",utc_media_audio_out_create_new_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_destroy_p",utc_media_audio_out_destroy_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_destroy_n",utc_media_audio_out_destroy_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_write_p",utc_media_audio_out_write_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_write_n1",utc_media_audio_out_write_n1,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_write_n2",utc_media_audio_out_write_n2,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_get_buffer_size_p",utc_media_audio_out_get_buffer_size_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_get_buffer_size_n",utc_media_audio_out_get_buffer_size_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_get_sample_rate_p",utc_media_audio_out_get_sample_rate_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_get_sample_rate_n",utc_media_audio_out_get_sample_rate_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_get_channel_p",utc_media_audio_out_get_channel_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_get_channel_n",utc_media_audio_out_get_channel_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_get_sample_type_p",utc_media_audio_out_get_sample_type_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_get_sample_type_n",utc_media_audio_out_get_sample_type_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_get_sound_type_p",utc_media_audio_out_get_sound_type_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_get_sound_type_n",utc_media_audio_out_get_sound_type_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_prepare_p",utc_media_audio_out_prepare_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_prepare_n",utc_media_audio_out_prepare_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_unprepare_p",utc_media_audio_out_unprepare_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_unprepare_n",utc_media_audio_out_unprepare_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_set_stream_cb_p",utc_media_audio_out_set_stream_cb_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_set_stream_cb_n",utc_media_audio_out_set_stream_cb_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_unset_stream_cb_p",utc_media_audio_out_unset_stream_cb_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_unset_stream_cb_n",utc_media_audio_out_unset_stream_cb_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_set_sound_stream_info_p",utc_media_audio_out_set_sound_stream_info_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_set_sound_stream_info_n",utc_media_audio_out_set_sound_stream_info_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_pause_p",utc_media_audio_out_pause_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_pause_n1",utc_media_audio_out_pause_n1,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_pause_n2",utc_media_audio_out_pause_n2,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_resume_p",utc_media_audio_out_resume_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_resume_n1",utc_media_audio_out_resume_n1,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_resume_n2",utc_media_audio_out_resume_n2,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_drain_p",utc_media_audio_out_drain_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_drain_n",utc_media_audio_out_drain_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_flush_p",utc_media_audio_out_flush_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_flush_n",utc_media_audio_out_flush_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_set_state_changed_cb_p",utc_media_audio_out_set_state_changed_cb_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_set_state_changed_cb_n",utc_media_audio_out_set_state_changed_cb_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_unset_state_changed_cb_p",utc_media_audio_out_unset_state_changed_cb_p,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{"utc_media_audio_out_unset_state_changed_cb_n",utc_media_audio_out_unset_state_changed_cb_n,utc_media_audio_out_startup,utc_media_audio_out_cleanup},
	{NULL, NULL}
};

#endif // __TCT_AUDIO-IO-NATIVE_H__
