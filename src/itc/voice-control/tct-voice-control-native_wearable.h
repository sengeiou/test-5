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
#ifndef __TCT_VOICE-CONTROL-NATIVE_H__
#define __TCT_VOICE-CONTROL-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_voice_control_startup(void);
extern void ITs_voice_control_cleanup(void);
extern void ITs_voice_control_engine_startup(void);
extern void ITs_voice_control_engine_cleanup(void);
extern int ITc_vc_cmd_create_destroy_p(void);
extern int ITc_vc_cmd_set_get_command_p(void);
extern int ITc_vc_cmd_set_get_type_p(void);
extern int ITc_vc_cmd_list_create_destroy_p(void);
extern int ITc_vc_cmd_list_add_remove_p(void);
extern int ITc_vc_cmd_list_first_last_p(void);
extern int ITc_vc_cmd_list_next_prev_p(void);
extern int ITc_vc_cmd_list_get_current_p(void);
extern int ITc_vc_cmd_list_get_count_p(void);
extern int ITc_vc_cmd_list_foreach_commands_p(void);
extern int ITc_vc_initialize_deinitialize_p(void);
extern int ITc_vc_set_unset_state_changed_cb_p(void);
extern int ITc_vc_prepare_unprepare_p(void);
extern int ITc_vc_get_state_p(void);
extern int ITc_vc_get_service_state_p(void);
extern int ITc_vc_set_unset_command_list_p(void);
extern int ITc_vc_set_unset_error_cb_p(void);
extern int ITc_vc_set_unset_current_language_changed_cb_p(void);
extern int ITc_vc_set_unset_service_state_changed_cb_p(void);
extern int ITc_vc_set_unset_result_cb_p(void);
extern int ITc_vc_get_current_language_p(void);
extern int ITc_vc_foreach_supported_languages_p(void);
extern int ITc_vc_get_system_command_list_p(void);
extern int ITc_vc_set_invocation_name_p(void);
extern int ITc_vc_request_dialog_p(void);
extern int ITc_vc_cmd_get_unfixed_command_p(void);
extern int ITc_vc_cmd_set_get_format_p(void);
extern int ITc_vce_main_p(void);
extern int ITc_vce_send_error_p(void);
extern int ITc_vce_set_private_data_set_cb_p(void);
extern int ITc_vce_set_nlu_base_info_requested_cb_p(void);
extern int ITc_vce_get_command_count_p(void);
extern int ITc_vce_get_audio_type_p(void);
extern int ITc_vce_start_stop_recording_p(void);
extern int ITc_vce_set_private_data_requested_cb_p(void);
extern int ITc_vce_send_specific_engine_result_p(void);
extern int ITc_vce_set_unset_specific_engine_request_cb_p(void);
extern int ITc_vce_send_feedback_audio_format_p(void);
extern int ITc_vce_send_feedback_streaming_p(void);
extern int ITc_vce_set_unset_request_tts_cb_p(void);
extern int ITc_vce_set_unset_cancel_tts_cb_p(void);
extern int ITc_vce_set_unset_tts_audio_format_request_cb_p(void);

testcase tc_array[] = {
	{"ITc_vc_cmd_create_destroy_p",ITc_vc_cmd_create_destroy_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_cmd_set_get_command_p",ITc_vc_cmd_set_get_command_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_cmd_set_get_type_p",ITc_vc_cmd_set_get_type_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_cmd_list_create_destroy_p",ITc_vc_cmd_list_create_destroy_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_cmd_list_add_remove_p",ITc_vc_cmd_list_add_remove_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_cmd_list_first_last_p",ITc_vc_cmd_list_first_last_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_cmd_list_next_prev_p",ITc_vc_cmd_list_next_prev_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_cmd_list_get_current_p",ITc_vc_cmd_list_get_current_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_cmd_list_get_count_p",ITc_vc_cmd_list_get_count_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_cmd_list_foreach_commands_p",ITc_vc_cmd_list_foreach_commands_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_initialize_deinitialize_p",ITc_vc_initialize_deinitialize_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_set_unset_state_changed_cb_p",ITc_vc_set_unset_state_changed_cb_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_prepare_unprepare_p",ITc_vc_prepare_unprepare_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_get_state_p",ITc_vc_get_state_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_get_service_state_p",ITc_vc_get_service_state_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_set_unset_command_list_p",ITc_vc_set_unset_command_list_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_set_unset_error_cb_p",ITc_vc_set_unset_error_cb_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_set_unset_current_language_changed_cb_p",ITc_vc_set_unset_current_language_changed_cb_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_set_unset_service_state_changed_cb_p",ITc_vc_set_unset_service_state_changed_cb_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_set_unset_result_cb_p",ITc_vc_set_unset_result_cb_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_get_current_language_p",ITc_vc_get_current_language_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_foreach_supported_languages_p",ITc_vc_foreach_supported_languages_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_get_system_command_list_p",ITc_vc_get_system_command_list_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_set_invocation_name_p",ITc_vc_set_invocation_name_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_request_dialog_p",ITc_vc_request_dialog_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_cmd_get_unfixed_command_p",ITc_vc_cmd_get_unfixed_command_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vc_cmd_set_get_format_p",ITc_vc_cmd_set_get_format_p,ITs_voice_control_startup,ITs_voice_control_cleanup},
	{"ITc_vce_main_p",ITc_vce_main_p,ITs_voice_control_engine_startup,ITs_voice_control_engine_cleanup},
	{"ITc_vce_send_error_p",ITc_vce_send_error_p,ITs_voice_control_engine_startup,ITs_voice_control_engine_cleanup},
	{"ITc_vce_set_private_data_set_cb_p",ITc_vce_set_private_data_set_cb_p,ITs_voice_control_engine_startup,ITs_voice_control_engine_cleanup},
	{"ITc_vce_set_nlu_base_info_requested_cb_p",ITc_vce_set_nlu_base_info_requested_cb_p,ITs_voice_control_engine_startup,ITs_voice_control_engine_cleanup},
	{"ITc_vce_get_command_count_p",ITc_vce_get_command_count_p,ITs_voice_control_engine_startup,ITs_voice_control_engine_cleanup},
	{"ITc_vce_get_audio_type_p",ITc_vce_get_audio_type_p,ITs_voice_control_engine_startup,ITs_voice_control_engine_cleanup},
	{"ITc_vce_start_stop_recording_p",ITc_vce_start_stop_recording_p,ITs_voice_control_engine_startup,ITs_voice_control_engine_cleanup},
	{"ITc_vce_set_private_data_requested_cb_p",ITc_vce_set_private_data_requested_cb_p,ITs_voice_control_engine_startup,ITs_voice_control_engine_cleanup},
	{"ITc_vce_send_specific_engine_result_p", ITc_vce_send_specific_engine_result_p, ITs_voice_control_engine_startup, ITs_voice_control_engine_cleanup},
	{"ITc_vce_set_unset_specific_engine_request_cb_p", ITc_vce_set_unset_specific_engine_request_cb_p, ITs_voice_control_engine_startup, ITs_voice_control_engine_cleanup},
	{"ITc_vce_send_feedback_audio_format_p", ITc_vce_send_feedback_audio_format_p, ITs_voice_control_engine_startup, ITs_voice_control_engine_cleanup},
	{"ITc_vce_send_feedback_streaming_p", ITc_vce_send_feedback_streaming_p, ITs_voice_control_engine_startup, ITs_voice_control_engine_cleanup},
	{"ITc_vce_set_unset_request_tts_cb_p", ITc_vce_set_unset_request_tts_cb_p, ITs_voice_control_engine_startup, ITs_voice_control_engine_cleanup},
	{"ITc_vce_set_unset_cancel_tts_cb_p", ITc_vce_set_unset_cancel_tts_cb_p, ITs_voice_control_engine_startup, ITs_voice_control_engine_cleanup},
	{"ITc_vce_set_unset_tts_audio_format_request_cb_p", ITc_vce_set_unset_tts_audio_format_request_cb_p, ITs_voice_control_engine_startup, ITs_voice_control_engine_cleanup},
	{NULL, NULL}
};

#endif // __TCT_VOICE-CONTROL-NATIVE_H__
