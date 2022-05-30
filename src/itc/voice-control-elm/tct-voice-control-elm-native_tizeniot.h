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
#ifndef __TCT_VOICE-CONTROL-ELM-NATIVE_H__
#define __TCT_VOICE-CONTROL-ELM-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_voice_control_elm_startup(void);
extern void ITs_voice_control_elm_cleanup(void);

extern int ITc_vc_elm_initialize_deinitialize_p(void);
extern int ITc_vc_elm_get_current_language_p(void);
extern int ITc_vc_elm_set_unset_current_language_changed_cb_p(void);
extern int ITc_vc_elm_foreach_supported_languages_p(void);
extern int ITc_vc_elm_foreach_supported_widgets_p(void);
extern int ITc_vc_elm_create_destroy_object_p(void);
extern int ITc_vc_elm_create_destroy_item_p(void);
extern int ITc_vc_elm_foreach_supported_actions_p(void);
extern int ITc_vc_elm_get_action_command_p(void);
extern int ITc_vc_elm_set_unset_command_p(void);
extern int ITc_vc_elm_set_unset_command_hint_p(void);
extern int ITc_vc_elm_set_get_command_hint_direction_p(void);
extern int ITc_vc_elm_set_get_command_hint_offset_p(void);

testcase tc_array[] = {
	{"ITc_vc_elm_initialize_deinitialize_p",ITc_vc_elm_initialize_deinitialize_p,ITs_voice_control_elm_startup,ITs_voice_control_elm_cleanup},
	{"ITc_vc_elm_get_current_language_p",ITc_vc_elm_get_current_language_p,ITs_voice_control_elm_startup,ITs_voice_control_elm_cleanup},
	{"ITc_vc_elm_set_unset_current_language_changed_cb_p",ITc_vc_elm_set_unset_current_language_changed_cb_p,ITs_voice_control_elm_startup,ITs_voice_control_elm_cleanup},
	{"ITc_vc_elm_foreach_supported_languages_p",ITc_vc_elm_foreach_supported_languages_p,ITs_voice_control_elm_startup,ITs_voice_control_elm_cleanup},
	{"ITc_vc_elm_foreach_supported_widgets_p",ITc_vc_elm_foreach_supported_widgets_p,ITs_voice_control_elm_startup,ITs_voice_control_elm_cleanup},
	{"ITc_vc_elm_create_destroy_object_p",ITc_vc_elm_create_destroy_object_p,ITs_voice_control_elm_startup,ITs_voice_control_elm_cleanup},
	{"ITc_vc_elm_create_destroy_item_p",ITc_vc_elm_create_destroy_item_p,ITs_voice_control_elm_startup,ITs_voice_control_elm_cleanup},
	{"ITc_vc_elm_foreach_supported_actions_p",ITc_vc_elm_foreach_supported_actions_p,ITs_voice_control_elm_startup,ITs_voice_control_elm_cleanup},
	{"ITc_vc_elm_get_action_command_p",ITc_vc_elm_get_action_command_p,ITs_voice_control_elm_startup,ITs_voice_control_elm_cleanup},
	{"ITc_vc_elm_set_unset_command_p",ITc_vc_elm_set_unset_command_p,ITs_voice_control_elm_startup,ITs_voice_control_elm_cleanup},
	{"ITc_vc_elm_set_unset_command_hint_p",ITc_vc_elm_set_unset_command_hint_p,ITs_voice_control_elm_startup,ITs_voice_control_elm_cleanup},
	{"ITc_vc_elm_set_get_command_hint_direction_p",ITc_vc_elm_set_get_command_hint_direction_p,ITs_voice_control_elm_startup,ITs_voice_control_elm_cleanup},
	{"ITc_vc_elm_set_get_command_hint_offset_p",ITc_vc_elm_set_get_command_hint_offset_p,ITs_voice_control_elm_startup,ITs_voice_control_elm_cleanup},
	{NULL, NULL}
};

#endif // __TCT_VOICE-CONTROL-ELM-NATIVE_H__
