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
#ifndef __TCT_TTS-NATIVE_H__
#define __TCT_TTS-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_tts_startup(void);
extern void utc_tts_cleanup(void);
extern void utc_ttse_startup(void);
extern void utc_ttse_cleanup(void);

extern int utc_tts_create_p(void);
extern int utc_tts_create_n(void);
extern int utc_tts_destroy_p(void);
extern int utc_tts_destroy_p2(void);
extern int utc_tts_destroy_p3(void);
extern int utc_tts_destroy_p4(void);
extern int utc_tts_destroy_n(void);
extern int utc_tts_destroy_n2(void);
extern int utc_tts_destroy_n3(void);
extern int utc_tts_set_mode_p(void);
extern int utc_tts_set_mode_p2(void);
extern int utc_tts_set_mode_n(void);
extern int utc_tts_set_mode_n2(void);
extern int utc_tts_set_mode_n3(void);
extern int utc_tts_get_mode_p(void);
extern int utc_tts_get_mode_n(void);
extern int utc_tts_get_mode_n2(void);
extern int utc_tts_get_speed_range_p(void);
extern int utc_tts_get_speed_range_n(void);
extern int utc_tts_get_speed_range_n2(void);
extern int utc_tts_prepare_p(void);
extern int utc_tts_prepare_n(void);
extern int utc_tts_prepare_n2(void);
extern int utc_tts_prepare_sync_p(void);
extern int utc_tts_prepare_sync_n(void);
extern int utc_tts_prepare_sync_n2(void);
extern int utc_tts_foreach_supported_voices_p(void);
extern int utc_tts_foreach_supported_voices_n(void);
extern int utc_tts_foreach_supported_voices_n2(void);
extern int utc_tts_foreach_supported_voices_n3(void);
extern int utc_tts_get_default_voice_p(void);
extern int utc_tts_get_default_voice_n(void);
extern int utc_tts_get_default_voice_n2(void);
extern int utc_tts_get_default_voice_n3(void);
extern int utc_tts_get_max_text_size_p(void);
extern int utc_tts_get_max_text_size_n(void);
extern int utc_tts_get_max_text_size_n2(void);
extern int utc_tts_get_max_text_size_n3(void);
extern int utc_tts_get_state_p(void);
extern int utc_tts_get_state_p2(void);
extern int utc_tts_get_state_p3(void);
extern int utc_tts_get_state_p4(void);
extern int utc_tts_get_state_n(void);
extern int utc_tts_get_state_n2(void);
extern int utc_tts_add_text_p(void);
extern int utc_tts_add_text_n(void);
extern int utc_tts_add_text_n2(void);
extern int utc_tts_add_text_n3(void);
extern int utc_tts_add_text_n4(void);
extern int utc_tts_add_text_n5(void);
extern int utc_tts_play_p(void);
extern int utc_tts_play_p2(void);
extern int utc_tts_play_n(void);
extern int utc_tts_play_n2(void);
extern int utc_tts_play_n3(void);
extern int utc_tts_pause_p(void);
extern int utc_tts_pause_n(void);
extern int utc_tts_pause_n2(void);
extern int utc_tts_pause_n3(void);
extern int utc_tts_stop_p(void);
extern int utc_tts_stop_n(void);
extern int utc_tts_stop_n2(void);
extern int utc_tts_stop_n3(void);
extern int utc_tts_repeat_p(void);
extern int utc_tts_repeat_n(void);
extern int utc_tts_repeat_n2(void);
extern int utc_tts_repeat_n3(void);
extern int utc_tts_unprepare_p(void);
extern int utc_tts_unprepare_p2(void);
extern int utc_tts_unprepare_n(void);
extern int utc_tts_unprepare_n2(void);
extern int utc_tts_unprepare_n3(void);
extern int utc_tts_set_state_changed_cb_p(void);
extern int utc_tts_set_state_changed_cb_n(void);
extern int utc_tts_set_state_changed_cb_n2(void);
extern int utc_tts_set_state_changed_cb_n3(void);
extern int utc_tts_unset_state_changed_cb_p(void);
extern int utc_tts_unset_state_changed_cb_n(void);
extern int utc_tts_unset_state_changed_cb_n2(void);
extern int utc_tts_unset_state_changed_cb_n3(void);
extern int utc_tts_set_utterance_started_cb_p(void);
extern int utc_tts_set_utterance_started_cb_n(void);
extern int utc_tts_set_utterance_started_cb_n2(void);
extern int utc_tts_set_utterance_started_cb_n3(void);
extern int utc_tts_unset_utterance_started_cb_p(void);
extern int utc_tts_unset_utterance_started_cb_n(void);
extern int utc_tts_unset_utterance_started_cb_n2(void);
extern int utc_tts_unset_utterance_started_cb_n3(void);
extern int utc_tts_set_utterance_completed_cb_p(void);
extern int utc_tts_set_utterance_completed_cb_n(void);
extern int utc_tts_set_utterance_completed_cb_n2(void);
extern int utc_tts_set_utterance_completed_cb_n3(void);
extern int utc_tts_unset_utterance_completed_cb_p(void);
extern int utc_tts_unset_utterance_completed_cb_n(void);
extern int utc_tts_unset_utterance_completed_cb_n2(void);
extern int utc_tts_unset_utterance_completed_cb_n3(void);
extern int utc_tts_set_error_cb_p(void);
extern int utc_tts_set_error_cb_n(void);
extern int utc_tts_set_error_cb_n2(void);
extern int utc_tts_set_error_cb_n3(void);
extern int utc_tts_unset_error_cb_p(void);
extern int utc_tts_unset_error_cb_n(void);
extern int utc_tts_unset_error_cb_n2(void);
extern int utc_tts_unset_error_cb_n3(void);
extern int utc_tts_set_default_voice_changed_cb_p(void);
extern int utc_tts_set_default_voice_changed_cb_n(void);
extern int utc_tts_set_default_voice_changed_cb_n2(void);
extern int utc_tts_set_default_voice_changed_cb_n3(void);
extern int utc_tts_unset_default_voice_changed_cb_p(void);
extern int utc_tts_unset_default_voice_changed_cb_n(void);
extern int utc_tts_unset_default_voice_changed_cb_n2(void);
extern int utc_tts_unset_default_voice_changed_cb_n3(void);
extern int utc_tts_get_error_message_p(void);
extern int utc_tts_get_error_message_n(void);
extern int utc_tts_get_error_message_n1(void);
extern int utc_tts_get_private_data_p(void);
extern int utc_tts_get_private_data_n(void);
extern int utc_tts_get_private_data_n1(void);
extern int utc_tts_get_private_data_n2(void);
extern int utc_tts_get_private_data_n3(void);
extern int utc_tts_set_private_data_p(void);
extern int utc_tts_set_private_data_n(void);
extern int utc_tts_set_private_data_n1(void);
extern int utc_tts_set_private_data_n2(void);
extern int utc_tts_set_private_data_n3(void);
extern int utc_tts_set_credential_p(void);
extern int utc_tts_set_credential_n(void);
extern int utc_tts_set_credential_n1(void);
extern int utc_tts_set_credential_n2(void);
extern int utc_tts_check_screen_reader_on_p(void);
extern int utc_tts_check_screen_reader_on_n(void);
extern int utc_tts_set_screen_reader_changed_cb_p(void);
extern int utc_tts_set_screen_reader_changed_cb_n(void);
extern int utc_tts_set_screen_reader_changed_cb_n1(void);
extern int utc_tts_set_screen_reader_changed_cb_n2(void);
extern int utc_tts_unset_screen_reader_changed_cb_p(void);
extern int utc_tts_unset_screen_reader_changed_cb_n(void);
extern int utc_tts_unset_screen_reader_changed_cb_n1(void);
extern int utc_tts_set_engine_changed_cb_p(void);
extern int utc_tts_set_engine_changed_cb_n(void);
extern int utc_tts_set_engine_changed_cb_n1(void);
extern int utc_tts_unset_engine_changed_cb_p(void);
extern int utc_tts_unset_engine_changed_cb_n(void);
extern int utc_tts_unset_engine_changed_cb_n1(void);
extern int utc_ttse_main_p(void);
extern int utc_ttse_main_n(void);
extern int utc_ttse_main_n1(void);
extern int utc_ttse_terminate_p(void);
extern int utc_ttse_terminate_n(void);
extern int utc_ttse_get_speed_range_p(void);
extern int utc_ttse_get_speed_range_n(void);
extern int utc_ttse_get_pitch_range_p(void);
extern int utc_ttse_get_pitch_range_n(void);
extern int utc_ttse_send_result_n(void);
extern int utc_ttse_send_error_p(void);
extern int utc_ttse_set_private_data_set_cb_p(void);
extern int utc_ttse_set_private_data_set_cb_n(void);
extern int utc_ttse_set_private_data_requested_cb_p(void);
extern int utc_ttse_set_private_data_requested_cb_n(void);

testcase tc_array[] = {
	{"utc_tts_create_p",utc_tts_create_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_create_n",utc_tts_create_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_destroy_p",utc_tts_destroy_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_destroy_p2",utc_tts_destroy_p2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_destroy_p3",utc_tts_destroy_p3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_destroy_p4",utc_tts_destroy_p4,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_destroy_n",utc_tts_destroy_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_destroy_n2",utc_tts_destroy_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_destroy_n3",utc_tts_destroy_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_mode_p",utc_tts_set_mode_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_mode_p2",utc_tts_set_mode_p2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_mode_n",utc_tts_set_mode_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_mode_n2",utc_tts_set_mode_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_mode_n3",utc_tts_set_mode_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_mode_p",utc_tts_get_mode_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_mode_n",utc_tts_get_mode_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_mode_n2",utc_tts_get_mode_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_speed_range_p",utc_tts_get_speed_range_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_speed_range_n",utc_tts_get_speed_range_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_speed_range_n2",utc_tts_get_speed_range_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_prepare_p",utc_tts_prepare_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_prepare_n",utc_tts_prepare_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_prepare_n2",utc_tts_prepare_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_prepare_sync_p",utc_tts_prepare_sync_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_prepare_sync_n",utc_tts_prepare_sync_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_prepare_sync_n2",utc_tts_prepare_sync_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_foreach_supported_voices_p",utc_tts_foreach_supported_voices_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_foreach_supported_voices_n",utc_tts_foreach_supported_voices_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_foreach_supported_voices_n2",utc_tts_foreach_supported_voices_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_foreach_supported_voices_n3",utc_tts_foreach_supported_voices_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_default_voice_p",utc_tts_get_default_voice_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_default_voice_n",utc_tts_get_default_voice_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_default_voice_n2",utc_tts_get_default_voice_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_default_voice_n3",utc_tts_get_default_voice_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_max_text_size_p",utc_tts_get_max_text_size_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_max_text_size_n",utc_tts_get_max_text_size_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_max_text_size_n2",utc_tts_get_max_text_size_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_max_text_size_n3",utc_tts_get_max_text_size_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_state_p",utc_tts_get_state_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_state_p2",utc_tts_get_state_p2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_state_p3",utc_tts_get_state_p3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_state_p4",utc_tts_get_state_p4,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_state_n",utc_tts_get_state_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_state_n2",utc_tts_get_state_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_add_text_p",utc_tts_add_text_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_add_text_n",utc_tts_add_text_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_add_text_n2",utc_tts_add_text_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_add_text_n3",utc_tts_add_text_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_add_text_n4",utc_tts_add_text_n4,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_add_text_n5",utc_tts_add_text_n5,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_play_p",utc_tts_play_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_play_p2",utc_tts_play_p2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_play_n",utc_tts_play_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_play_n2",utc_tts_play_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_play_n3",utc_tts_play_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_pause_p",utc_tts_pause_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_pause_n",utc_tts_pause_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_pause_n2",utc_tts_pause_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_pause_n3",utc_tts_pause_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_stop_p",utc_tts_stop_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_stop_n",utc_tts_stop_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_stop_n2",utc_tts_stop_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_stop_n3",utc_tts_stop_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_repeat_p",utc_tts_repeat_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_repeat_n",utc_tts_repeat_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_repeat_n2",utc_tts_repeat_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_repeat_n3",utc_tts_repeat_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unprepare_p",utc_tts_unprepare_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unprepare_p2",utc_tts_unprepare_p2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unprepare_n",utc_tts_unprepare_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unprepare_n2",utc_tts_unprepare_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unprepare_n3",utc_tts_unprepare_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_state_changed_cb_p",utc_tts_set_state_changed_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_state_changed_cb_n",utc_tts_set_state_changed_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_state_changed_cb_n2",utc_tts_set_state_changed_cb_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_state_changed_cb_n3",utc_tts_set_state_changed_cb_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_state_changed_cb_p",utc_tts_unset_state_changed_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_state_changed_cb_n",utc_tts_unset_state_changed_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_state_changed_cb_n2",utc_tts_unset_state_changed_cb_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_state_changed_cb_n3",utc_tts_unset_state_changed_cb_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_utterance_started_cb_p",utc_tts_set_utterance_started_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_utterance_started_cb_n",utc_tts_set_utterance_started_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_utterance_started_cb_n2",utc_tts_set_utterance_started_cb_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_utterance_started_cb_n3",utc_tts_set_utterance_started_cb_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_utterance_started_cb_p",utc_tts_unset_utterance_started_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_utterance_started_cb_n",utc_tts_unset_utterance_started_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_utterance_started_cb_n2",utc_tts_unset_utterance_started_cb_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_utterance_started_cb_n3",utc_tts_unset_utterance_started_cb_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_utterance_completed_cb_p",utc_tts_set_utterance_completed_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_utterance_completed_cb_n",utc_tts_set_utterance_completed_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_utterance_completed_cb_n2",utc_tts_set_utterance_completed_cb_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_utterance_completed_cb_n3",utc_tts_set_utterance_completed_cb_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_utterance_completed_cb_p",utc_tts_unset_utterance_completed_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_utterance_completed_cb_n",utc_tts_unset_utterance_completed_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_utterance_completed_cb_n2",utc_tts_unset_utterance_completed_cb_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_utterance_completed_cb_n3",utc_tts_unset_utterance_completed_cb_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_error_cb_p",utc_tts_set_error_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_error_cb_n",utc_tts_set_error_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_error_cb_n2",utc_tts_set_error_cb_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_error_cb_n3",utc_tts_set_error_cb_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_error_cb_p",utc_tts_unset_error_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_error_cb_n",utc_tts_unset_error_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_error_cb_n2",utc_tts_unset_error_cb_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_error_cb_n3",utc_tts_unset_error_cb_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_default_voice_changed_cb_p",utc_tts_set_default_voice_changed_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_default_voice_changed_cb_n",utc_tts_set_default_voice_changed_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_default_voice_changed_cb_n2",utc_tts_set_default_voice_changed_cb_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_default_voice_changed_cb_n3",utc_tts_set_default_voice_changed_cb_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_default_voice_changed_cb_p",utc_tts_unset_default_voice_changed_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_default_voice_changed_cb_n",utc_tts_unset_default_voice_changed_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_default_voice_changed_cb_n2",utc_tts_unset_default_voice_changed_cb_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_default_voice_changed_cb_n3",utc_tts_unset_default_voice_changed_cb_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_error_message_p",utc_tts_get_error_message_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_error_message_n",utc_tts_get_error_message_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_error_message_n1",utc_tts_get_error_message_n1,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_private_data_p",utc_tts_get_private_data_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_private_data_n",utc_tts_get_private_data_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_private_data_n1",utc_tts_get_private_data_n1,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_private_data_n2",utc_tts_get_private_data_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_get_private_data_n3",utc_tts_get_private_data_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_private_data_p",utc_tts_set_private_data_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_private_data_n",utc_tts_set_private_data_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_private_data_n1",utc_tts_set_private_data_n1,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_private_data_n2",utc_tts_set_private_data_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_private_data_n3",utc_tts_set_private_data_n3,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_credential_p",utc_tts_set_credential_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_credential_n",utc_tts_set_credential_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_credential_n1",utc_tts_set_credential_n1,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_credential_n2",utc_tts_set_credential_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_check_screen_reader_on_p",utc_tts_check_screen_reader_on_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_check_screen_reader_on_n",utc_tts_check_screen_reader_on_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_screen_reader_changed_cb_p",utc_tts_set_screen_reader_changed_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_screen_reader_changed_cb_n",utc_tts_set_screen_reader_changed_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_screen_reader_changed_cb_n1",utc_tts_set_screen_reader_changed_cb_n1,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_screen_reader_changed_cb_n2",utc_tts_set_screen_reader_changed_cb_n2,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_screen_reader_changed_cb_p",utc_tts_unset_screen_reader_changed_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_screen_reader_changed_cb_n",utc_tts_unset_screen_reader_changed_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_screen_reader_changed_cb_n1",utc_tts_unset_screen_reader_changed_cb_n1,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_engine_changed_cb_p",utc_tts_set_engine_changed_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_engine_changed_cb_n",utc_tts_set_engine_changed_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_set_engine_changed_cb_n1",utc_tts_set_engine_changed_cb_n1,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_engine_changed_cb_p",utc_tts_unset_engine_changed_cb_p,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_engine_changed_cb_n",utc_tts_unset_engine_changed_cb_n,utc_tts_startup,utc_tts_cleanup},
	{"utc_tts_unset_engine_changed_cb_n1",utc_tts_unset_engine_changed_cb_n1,utc_tts_startup,utc_tts_cleanup},
	{"utc_ttse_main_p",utc_ttse_main_p,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_main_n",utc_ttse_main_n,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_main_n1",utc_ttse_main_n1,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_terminate_p",utc_ttse_terminate_p,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_terminate_n",utc_ttse_terminate_n,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_get_speed_range_p",utc_ttse_get_speed_range_p,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_get_speed_range_n",utc_ttse_get_speed_range_n,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_get_pitch_range_p",utc_ttse_get_pitch_range_p,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_get_pitch_range_n",utc_ttse_get_pitch_range_n,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_send_result_n",utc_ttse_send_result_n,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_send_error_p",utc_ttse_send_error_p,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_set_private_data_set_cb_p",utc_ttse_set_private_data_set_cb_p,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_set_private_data_set_cb_n",utc_ttse_set_private_data_set_cb_n,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_set_private_data_requested_cb_p",utc_ttse_set_private_data_requested_cb_p,utc_ttse_startup,utc_ttse_cleanup},
	{"utc_ttse_set_private_data_requested_cb_n",utc_ttse_set_private_data_requested_cb_n,utc_ttse_startup,utc_ttse_cleanup},
	{NULL, NULL}
};

#endif // __TCT_TTS-NATIVE_H__
