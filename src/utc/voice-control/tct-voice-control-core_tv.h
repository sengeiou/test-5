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

extern void utc_voice_control_startup(void);
extern void utc_voice_control_cleanup(void);


extern int utc_vc_initialize_p(void);
extern int utc_vc_deinitialize_p(void);
extern int utc_vc_deinitialize_n(void);
extern int utc_vc_prepare_p(void);
extern int utc_vc_prepare_n(void);
extern int utc_vc_unprepare_p(void);
extern int utc_vc_unprepare_n(void);
extern int utc_vc_unprepare_n2(void);
extern int utc_vc_foreach_supported_languages_p(void);
extern int utc_vc_foreach_supported_languages_n(void);
extern int utc_vc_foreach_supported_languages_n2(void);
extern int utc_vc_get_current_language_p(void);
extern int utc_vc_get_current_language_n(void);
extern int utc_vc_get_current_language_n2(void);
extern int utc_vc_get_state_p(void);
extern int utc_vc_get_state_p2(void);
extern int utc_vc_get_state_n(void);
extern int utc_vc_get_state_n2(void);
extern int utc_vc_get_service_state_p(void);
extern int utc_vc_get_service_state_n(void);
extern int utc_vc_get_service_state_n2(void);
extern int utc_vc_get_system_command_list_p(void);
extern int utc_vc_get_system_command_list_n(void);
extern int utc_vc_get_system_command_list_n2(void);
extern int utc_vc_set_command_list_p(void);
extern int utc_vc_set_command_list_n(void);
extern int utc_vc_set_command_list_n2(void);
extern int utc_vc_set_command_list_n3(void);
extern int utc_vc_unset_command_list_p(void);
extern int utc_vc_unset_command_list_n(void);
extern int utc_vc_unset_command_list_n2(void);
extern int utc_vc_get_result_p(void);
extern int utc_vc_get_result_n(void);
extern int utc_vc_set_result_cb_p(void);
extern int utc_vc_set_result_cb_n(void);
extern int utc_vc_set_result_cb_n2(void);
extern int utc_vc_set_result_cb_n3(void);
extern int utc_vc_unset_result_cb_p(void);
extern int utc_vc_unset_result_cb_n(void);
extern int utc_vc_unset_result_cb_n2(void);
extern int utc_vc_set_service_state_changed_cb_p(void);
extern int utc_vc_set_service_state_changed_cb_n(void);
extern int utc_vc_set_service_state_changed_cb_n2(void);
extern int utc_vc_set_service_state_changed_cb_n3(void);
extern int utc_vc_unset_service_state_changed_cb_p(void);
extern int utc_vc_unset_service_state_changed_cb_n(void);
extern int utc_vc_unset_service_state_changed_cb_n2(void);
extern int utc_vc_set_state_changed_cb_p(void);
extern int utc_vc_set_state_changed_cb_n(void);
extern int utc_vc_set_state_changed_cb_n2(void);
extern int utc_vc_set_state_changed_cb_n3(void);
extern int utc_vc_unset_state_changed_cb_p(void);
extern int utc_vc_unset_state_changed_cb_n(void);
extern int utc_vc_set_current_language_changed_cb_p(void);
extern int utc_vc_set_current_language_changed_cb_n(void);
extern int utc_vc_set_current_language_changed_cb_n2(void);
extern int utc_vc_set_current_language_changed_cb_n3(void);
extern int utc_vc_unset_current_language_changed_cb_p(void);
extern int utc_vc_unset_current_language_changed_cb_n(void);
extern int utc_vc_unset_current_language_changed_cb_n2(void);
extern int utc_vc_set_error_cb_p(void);
extern int utc_vc_set_error_cb_n(void);
extern int utc_vc_set_error_cb_n2(void);
extern int utc_vc_set_error_cb_n3(void);
extern int utc_vc_unset_error_cb_p(void);
extern int utc_vc_unset_error_cb_n(void);
extern int utc_vc_unset_error_cb_n2(void);
extern int utc_vc_set_invocation_name_p(void);
extern int utc_vc_set_invocation_name_n(void);
extern int utc_vc_request_dialog_p(void);
extern int utc_vc_request_dialog_n(void);
extern int utc_vc_cmd_list_create_p(void);
extern int utc_vc_cmd_list_create_n(void);
extern int utc_vc_cmd_list_destroy_p(void);
extern int utc_vc_cmd_list_destroy_n(void);
extern int utc_vc_cmd_list_get_count_p(void);
extern int utc_vc_cmd_list_get_count_n(void);
extern int utc_vc_cmd_list_add_p(void);
extern int utc_vc_cmd_list_add_n(void);
extern int utc_vc_cmd_list_remove_p(void);
extern int utc_vc_cmd_list_remove_n(void);
extern int utc_vc_cmd_list_foreach_commands_p(void);
extern int utc_vc_cmd_list_foreach_commands_n(void);
extern int utc_vc_cmd_list_first_p(void);
extern int utc_vc_cmd_list_first_n(void);
extern int utc_vc_cmd_list_last_p(void);
extern int utc_vc_cmd_list_last_n(void);
extern int utc_vc_cmd_list_next_p(void);
extern int utc_vc_cmd_list_next_n(void);
extern int utc_vc_cmd_list_prev_p(void);
extern int utc_vc_cmd_list_prev_n(void);
extern int utc_vc_cmd_list_get_current_p(void);
extern int utc_vc_cmd_list_get_current_n(void);
extern int utc_vc_cmd_create_p(void);
extern int utc_vc_cmd_create_n(void);
extern int utc_vc_cmd_destroy_p(void);
extern int utc_vc_cmd_destroy_n(void);
extern int utc_vc_cmd_set_command_p(void);
extern int utc_vc_cmd_set_command_n(void);
extern int utc_vc_cmd_get_command_p(void);
extern int utc_vc_cmd_get_command_n(void);
extern int utc_vc_cmd_get_unfixed_command_p(void);
extern int utc_vc_cmd_get_unfixed_command_n(void);
extern int utc_vc_cmd_set_type_p(void);
extern int utc_vc_cmd_set_type_n(void);
extern int utc_vc_cmd_get_type_p(void);
extern int utc_vc_cmd_get_type_n(void);
extern int utc_vc_cmd_set_format_p(void);
extern int utc_vc_cmd_set_format_n(void);
extern int utc_vc_cmd_get_format_p(void);
extern int utc_vc_cmd_get_format_n(void);

testcase tc_array[] = {
	{"utc_vc_initialize_p",utc_vc_initialize_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_deinitialize_p",utc_vc_deinitialize_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_deinitialize_n",utc_vc_deinitialize_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_prepare_p",utc_vc_prepare_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_prepare_n",utc_vc_prepare_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unprepare_p",utc_vc_unprepare_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unprepare_n",utc_vc_unprepare_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unprepare_n2",utc_vc_unprepare_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_foreach_supported_languages_p",utc_vc_foreach_supported_languages_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_foreach_supported_languages_n",utc_vc_foreach_supported_languages_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_foreach_supported_languages_n2",utc_vc_foreach_supported_languages_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_current_language_p",utc_vc_get_current_language_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_current_language_n",utc_vc_get_current_language_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_current_language_n2",utc_vc_get_current_language_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_state_p",utc_vc_get_state_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_state_p2",utc_vc_get_state_p2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_state_n",utc_vc_get_state_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_state_n2",utc_vc_get_state_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_service_state_p",utc_vc_get_service_state_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_service_state_n",utc_vc_get_service_state_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_service_state_n2",utc_vc_get_service_state_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_system_command_list_p",utc_vc_get_system_command_list_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_system_command_list_n",utc_vc_get_system_command_list_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_system_command_list_n2",utc_vc_get_system_command_list_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_command_list_p",utc_vc_set_command_list_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_command_list_n",utc_vc_set_command_list_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_command_list_n2",utc_vc_set_command_list_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_command_list_n3",utc_vc_set_command_list_n3,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_command_list_p",utc_vc_unset_command_list_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_command_list_n",utc_vc_unset_command_list_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_command_list_n2",utc_vc_unset_command_list_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_result_p",utc_vc_get_result_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_get_result_n",utc_vc_get_result_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_result_cb_p",utc_vc_set_result_cb_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_result_cb_n",utc_vc_set_result_cb_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_result_cb_n2",utc_vc_set_result_cb_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_result_cb_n3",utc_vc_set_result_cb_n3,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_result_cb_p",utc_vc_unset_result_cb_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_result_cb_n",utc_vc_unset_result_cb_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_result_cb_n2",utc_vc_unset_result_cb_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_service_state_changed_cb_p",utc_vc_set_service_state_changed_cb_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_service_state_changed_cb_n",utc_vc_set_service_state_changed_cb_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_service_state_changed_cb_n2",utc_vc_set_service_state_changed_cb_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_service_state_changed_cb_n3",utc_vc_set_service_state_changed_cb_n3,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_service_state_changed_cb_p",utc_vc_unset_service_state_changed_cb_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_service_state_changed_cb_n",utc_vc_unset_service_state_changed_cb_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_service_state_changed_cb_n2",utc_vc_unset_service_state_changed_cb_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_state_changed_cb_p",utc_vc_set_state_changed_cb_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_state_changed_cb_n",utc_vc_set_state_changed_cb_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_state_changed_cb_n2",utc_vc_set_state_changed_cb_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_state_changed_cb_n3",utc_vc_set_state_changed_cb_n3,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_state_changed_cb_p",utc_vc_unset_state_changed_cb_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_state_changed_cb_n",utc_vc_unset_state_changed_cb_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_current_language_changed_cb_p",utc_vc_set_current_language_changed_cb_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_current_language_changed_cb_n",utc_vc_set_current_language_changed_cb_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_current_language_changed_cb_n2",utc_vc_set_current_language_changed_cb_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_current_language_changed_cb_n3",utc_vc_set_current_language_changed_cb_n3,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_current_language_changed_cb_p",utc_vc_unset_current_language_changed_cb_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_current_language_changed_cb_n",utc_vc_unset_current_language_changed_cb_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_current_language_changed_cb_n2",utc_vc_unset_current_language_changed_cb_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_error_cb_p",utc_vc_set_error_cb_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_error_cb_n",utc_vc_set_error_cb_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_error_cb_n2",utc_vc_set_error_cb_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_error_cb_n3",utc_vc_set_error_cb_n3,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_error_cb_p",utc_vc_unset_error_cb_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_error_cb_n",utc_vc_unset_error_cb_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_unset_error_cb_n2",utc_vc_unset_error_cb_n2,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_invocation_name_p",utc_vc_set_invocation_name_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_set_invocation_name_n",utc_vc_set_invocation_name_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_request_dialog_p",utc_vc_request_dialog_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_request_dialog_n",utc_vc_request_dialog_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_create_p",utc_vc_cmd_list_create_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_create_n",utc_vc_cmd_list_create_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_destroy_p",utc_vc_cmd_list_destroy_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_destroy_n",utc_vc_cmd_list_destroy_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_get_count_p",utc_vc_cmd_list_get_count_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_get_count_n",utc_vc_cmd_list_get_count_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_add_p",utc_vc_cmd_list_add_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_add_n",utc_vc_cmd_list_add_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_remove_p",utc_vc_cmd_list_remove_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_remove_n",utc_vc_cmd_list_remove_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_foreach_commands_p",utc_vc_cmd_list_foreach_commands_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_foreach_commands_n",utc_vc_cmd_list_foreach_commands_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_first_p",utc_vc_cmd_list_first_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_first_n",utc_vc_cmd_list_first_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_last_p",utc_vc_cmd_list_last_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_last_n",utc_vc_cmd_list_last_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_next_p",utc_vc_cmd_list_next_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_next_n",utc_vc_cmd_list_next_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_prev_p",utc_vc_cmd_list_prev_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_prev_n",utc_vc_cmd_list_prev_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_get_current_p",utc_vc_cmd_list_get_current_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_list_get_current_n",utc_vc_cmd_list_get_current_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_create_p",utc_vc_cmd_create_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_create_n",utc_vc_cmd_create_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_destroy_p",utc_vc_cmd_destroy_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_destroy_n",utc_vc_cmd_destroy_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_set_command_p",utc_vc_cmd_set_command_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_set_command_n",utc_vc_cmd_set_command_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_get_command_p",utc_vc_cmd_get_command_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_get_command_n",utc_vc_cmd_get_command_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_get_unfixed_command_p",utc_vc_cmd_get_unfixed_command_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_get_unfixed_command_n",utc_vc_cmd_get_unfixed_command_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_set_type_p",utc_vc_cmd_set_type_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_set_type_n",utc_vc_cmd_set_type_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_get_type_p",utc_vc_cmd_get_type_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_get_type_n",utc_vc_cmd_get_type_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_set_format_p",utc_vc_cmd_set_format_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_set_format_n",utc_vc_cmd_set_format_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_get_format_p",utc_vc_cmd_get_format_p,utc_voice_control_startup,utc_voice_control_cleanup},
	{"utc_vc_cmd_get_format_n",utc_vc_cmd_get_format_n,utc_voice_control_startup,utc_voice_control_cleanup},
	{NULL, NULL}
};

#endif // __TCT_VOICE-CONTROL-NATIVE_H__
