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
#ifndef __TCT_MULTI-ASSISTANT-NATIVE_H__
#define __TCT_MULTI-ASSISTANT-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_ma_startup(void);
extern void ITs_ma_cleanup(void);

extern int ITc_ma_initialize_deinitialize_p(void);
extern int ITc_ma_get_state_p(void);
extern int ITc_ma_get_current_language_p(void);
extern int ITc_ma_get_recording_audio_format_p(void);
extern int ITc_ma_prepare_unprepare_set_unset_state_changed_cb_p(void);
extern int ITc_ma_set_unset_error_cb_p(void);
extern int ITc_ma_set_unset_language_changed_cb_p(void);
extern int ITc_ma_set_unset_audio_streaming_cb_p(void);
extern int ITc_ma_send_asr_result_p(void);
extern int ITc_ma_send_result_p(void);
extern int ITc_ma_send_recognition_result_p(void);
extern int ITc_ma_set_unset_active_state_changed_cb_p(void);
extern int ITc_ma_start_stop_receiving_audio_streaming_data_p(void);
extern int ITc_ma_update_voice_feedback_state_p(void);
extern int ITc_ma_send_assistant_specific_command_p(void);
extern int ITc_ma_set_unset_wakeup_engine_command_cb_p(void);
extern int ITc_ma_set_wake_word_audio_require_flag_p(void);
extern int ITc_ma_set_unset_audio_streaming_data_section_changed_cb_p(void);
extern int ITc_ma_assistant_info_foreach_assistants_p(void);
extern int ITc_ma_assistant_info_get_app_id_p(void);
extern int ITc_ma_assistant_info_get_enabled_status_p(void);
extern int ITc_ma_get_recording_audio_source_type_p(void);
extern int ITc_ma_set_background_volume_p(void);
extern int ITc_ma_set_preprocessing_allow_mode_p(void);
extern int ITc_ma_set_unset_preprocessing_information_changed_cb_p(void);
extern int ITc_ma_send_preprocessing_result_p(void);
extern int ITc_ma_set_assistant_wakeup_language_p(void);
extern int ITc_ma_set_unset_service_state_changed_cb_p(void);
extern int ITc_ma_set_unset_voice_key_status_changed_cb_p(void);
extern int ITc_ma_add_remove_wake_word_p(void);

testcase tc_array[] = {
	{"ITc_ma_initialize_deinitialize_p",ITc_ma_initialize_deinitialize_p,ITs_ma_startup,ITs_ma_cleanup},
	{"ITc_ma_get_state_p",ITc_ma_get_state_p,ITs_ma_startup,ITs_ma_cleanup},
	{"ITc_ma_get_current_language_p",ITc_ma_get_current_language_p,ITs_ma_startup,ITs_ma_cleanup},
	{"ITc_ma_get_recording_audio_format_p",ITc_ma_get_recording_audio_format_p,ITs_ma_startup,ITs_ma_cleanup},
	{"ITc_ma_prepare_unprepare_set_unset_state_changed_cb_p",ITc_ma_prepare_unprepare_set_unset_state_changed_cb_p,ITs_ma_startup,ITs_ma_cleanup},
	{"ITc_ma_set_unset_error_cb_p",ITc_ma_set_unset_error_cb_p,ITs_ma_startup,ITs_ma_cleanup},
	{"ITc_ma_set_unset_language_changed_cb_p",ITc_ma_set_unset_language_changed_cb_p,ITs_ma_startup,ITs_ma_cleanup},
	{"ITc_ma_set_unset_audio_streaming_cb_p",ITc_ma_set_unset_audio_streaming_cb_p,ITs_ma_startup,ITs_ma_cleanup},
	{"ITc_ma_send_asr_result_p",ITc_ma_send_asr_result_p,ITs_ma_startup,ITs_ma_cleanup},
	{"ITc_ma_send_result_p",ITc_ma_send_result_p,ITs_ma_startup,ITs_ma_cleanup},
	{"ITc_ma_send_recognition_result_p", ITc_ma_send_recognition_result_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_set_unset_active_state_changed_cb_p", ITc_ma_set_unset_active_state_changed_cb_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_start_stop_receiving_audio_streaming_data_p", ITc_ma_start_stop_receiving_audio_streaming_data_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_update_voice_feedback_state_p", ITc_ma_update_voice_feedback_state_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_send_assistant_specific_command_p", ITc_ma_send_assistant_specific_command_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_set_unset_wakeup_engine_command_cb_p", ITc_ma_set_unset_wakeup_engine_command_cb_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_set_wake_word_audio_require_flag_p", ITc_ma_set_wake_word_audio_require_flag_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_set_unset_audio_streaming_data_section_changed_cb_p", ITc_ma_set_unset_audio_streaming_data_section_changed_cb_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_assistant_info_foreach_assistants_p", ITc_ma_assistant_info_foreach_assistants_p, ITs_ma_startup,ITs_ma_cleanup},
	{"ITc_ma_assistant_info_get_app_id_p", ITc_ma_assistant_info_get_app_id_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_assistant_info_get_enabled_status_p", ITc_ma_assistant_info_get_enabled_status_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_get_recording_audio_source_type_p", ITc_ma_get_recording_audio_source_type_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_set_background_volume_p", ITc_ma_set_background_volume_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_set_preprocessing_allow_mode_p", ITc_ma_set_preprocessing_allow_mode_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_set_unset_preprocessing_information_changed_cb_p", ITc_ma_set_unset_preprocessing_information_changed_cb_p, ITs_ma_startup, ITs_ma_cleanup},
	{"ITc_ma_send_preprocessing_result_p", ITc_ma_send_preprocessing_result_p, ITs_ma_startup, ITs_ma_cleanup},
        {"ITc_ma_set_assistant_wakeup_language_p", ITc_ma_set_assistant_wakeup_language_p, ITs_ma_startup, ITs_ma_cleanup},
        {"ITc_ma_set_unset_service_state_changed_cb_p", ITc_ma_set_unset_service_state_changed_cb_p, ITs_ma_startup, ITs_ma_cleanup},
        {"ITc_ma_set_unset_voice_key_status_changed_cb_p", ITc_ma_set_unset_voice_key_status_changed_cb_p, ITs_ma_startup, ITs_ma_cleanup},
        {"ITc_ma_add_remove_wake_word_p", ITc_ma_add_remove_wake_word_p, ITs_ma_startup, ITs_ma_cleanup},
	{NULL, NULL}
};

#endif // __TCT_MULTI-ASSISTANT-NATIVE_H__
