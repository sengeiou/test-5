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

extern void ITs_tts_startup(void);
extern void ITs_tts_cleanup(void);
extern void ITs_ttse_startup(void);
extern void ITs_ttse_cleanup(void);

extern int ITc_tts_create_destroy_p(void);
extern int ITc_tts_set_get_mode_p(void);
extern int ITc_tts_get_default_voice_p(void);
extern int ITc_tts_get_state_p(void);
extern int ITc_tts_prepare_unprepare_p(void);
extern int ITc_tts_setunset_state_changed_cb_p(void);
extern int ITc_tts_get_max_text_size_p(void);
extern int ITc_tts_get_speed_range_p(void);
extern int ITc_tts_add_text_play_p(void);
extern int ITc_tts_pause_stop_p(void);
extern int ITc_tts_setunset_utterance_started_completed_cb_p(void);
extern int ITc_tts_setunset_error_cb_p(void);
extern int ITc_tts_setunset_default_voice_changed_cb_p(void);
extern int ITc_tts_foreach_supported_voices_p(void);
extern int ITc_tts_set_credential_p(void);
extern int ITc_tts_set_get_private_data_p(void);
extern int ITc_tts_set_unset_engine_changed_cb_p(void);
extern int ITc_ttse_main_p(void);
extern int ITc_ttse_get_speed_range_p(void);
extern int ITc_ttse_get_pitch_range_p(void);
extern int ITc_ttse_set_private_data_set_cb_p(void);
extern int ITc_ttse_set_private_data_requested_cb_p(void);
extern int ITc_tts_check_screen_reader_on_p(void);
extern int ITc_tts_set_unset_screen_reader_changed_cb_p(void);
extern int ITc_tts_prepare_sync_p(void);
extern int ITc_ttse_terminate_p(void);

testcase tc_array[] = {
	{"ITc_tts_create_destroy_p",ITc_tts_create_destroy_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_set_get_mode_p",ITc_tts_set_get_mode_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_get_default_voice_p",ITc_tts_get_default_voice_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_get_state_p",ITc_tts_get_state_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_prepare_unprepare_p",ITc_tts_prepare_unprepare_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_setunset_state_changed_cb_p",ITc_tts_setunset_state_changed_cb_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_get_max_text_size_p",ITc_tts_get_max_text_size_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_get_speed_range_p",ITc_tts_get_speed_range_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_add_text_play_p",ITc_tts_add_text_play_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_pause_stop_p",ITc_tts_pause_stop_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_setunset_utterance_started_completed_cb_p",ITc_tts_setunset_utterance_started_completed_cb_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_setunset_error_cb_p",ITc_tts_setunset_error_cb_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_setunset_default_voice_changed_cb_p",ITc_tts_setunset_default_voice_changed_cb_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_foreach_supported_voices_p",ITc_tts_foreach_supported_voices_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_set_credential_p",ITc_tts_set_credential_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_set_get_private_data_p",ITc_tts_set_get_private_data_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_set_unset_engine_changed_cb_p",ITc_tts_set_unset_engine_changed_cb_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_ttse_main_p",ITc_ttse_main_p,ITs_ttse_startup,ITs_ttse_cleanup},
	{"ITc_ttse_get_speed_range_p",ITc_ttse_get_speed_range_p,ITs_ttse_startup,ITs_ttse_cleanup},
	{"ITc_ttse_get_pitch_range_p",ITc_ttse_get_pitch_range_p,ITs_ttse_startup,ITs_ttse_cleanup},
	{"ITc_ttse_set_private_data_set_cb_p",ITc_ttse_set_private_data_set_cb_p,ITs_ttse_startup,ITs_ttse_cleanup},
	{"ITc_ttse_set_private_data_requested_cb_p",ITc_ttse_set_private_data_requested_cb_p,ITs_ttse_startup,ITs_ttse_cleanup},
	{"ITc_tts_check_screen_reader_on_p",ITc_tts_check_screen_reader_on_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_set_unset_screen_reader_changed_cb_p",ITc_tts_set_unset_screen_reader_changed_cb_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_tts_prepare_sync_p",ITc_tts_prepare_sync_p,ITs_tts_startup,ITs_tts_cleanup},
	{"ITc_ttse_terminate_p",ITc_ttse_terminate_p,ITs_ttse_startup,ITs_ttse_cleanup},
	{NULL, NULL}
};

#endif // __TCT_TTS-NATIVE_H__
