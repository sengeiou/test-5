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

extern void utc_voice_control_elm_startup(void);
extern void utc_voice_control_elm_cleanup(void);

extern int utc_voice_control_elm_vc_elm_initialize_p(void);
extern int utc_voice_control_elm_vc_elm_initialize_n(void);
extern int utc_voice_control_elm_vc_elm_deinitialize_p(void);
extern int utc_voice_control_elm_vc_elm_deinitialize_n(void);
extern int utc_voice_control_elm_vc_elm_get_current_language_p(void);
extern int utc_voice_control_elm_vc_elm_get_current_language_n(void);
extern int utc_voice_control_elm_vc_elm_create_object_p1(void);
extern int utc_voice_control_elm_vc_elm_create_object_p2(void);
extern int utc_voice_control_elm_vc_elm_create_object_p3(void);
extern int utc_voice_control_elm_vc_elm_create_object_p4(void);
extern int utc_voice_control_elm_vc_elm_create_object_p5(void);
extern int utc_voice_control_elm_vc_elm_create_object_p6(void);
extern int utc_voice_control_elm_vc_elm_create_object_p7(void);
extern int utc_voice_control_elm_vc_elm_create_object_p8(void);
extern int utc_voice_control_elm_vc_elm_create_object_p9(void);
extern int utc_voice_control_elm_vc_elm_create_object_p10(void);
extern int utc_voice_control_elm_vc_elm_create_object_n1(void);
extern int utc_voice_control_elm_vc_elm_create_object_n2(void);
extern int utc_voice_control_elm_vc_elm_create_object_n3(void);
extern int utc_voice_control_elm_vc_elm_create_item_p(void);
extern int utc_voice_control_elm_vc_elm_create_item_n1(void);
extern int utc_voice_control_elm_vc_elm_create_item_n2(void);
extern int utc_voice_control_elm_vc_elm_create_item_n3(void);
extern int utc_voice_control_elm_vc_elm_destroy_p(void);
extern int utc_voice_control_elm_vc_elm_destroy_n1(void);
extern int utc_voice_control_elm_vc_elm_destroy_n2(void);
extern int utc_voice_control_elm_vc_elm_destroy_n3(void);
extern int utc_voice_control_elm_vc_elm_set_command_p1(void);
extern int utc_voice_control_elm_vc_elm_set_command_p2(void);
extern int utc_voice_control_elm_vc_elm_set_command_n(void);
extern int utc_voice_control_elm_vc_elm_unset_command_p1(void);
extern int utc_voice_control_elm_vc_elm_unset_command_p2(void);
extern int utc_voice_control_elm_vc_elm_unset_command_n(void);
extern int utc_voice_control_elm_vc_elm_set_command_hint_p1(void);
extern int utc_voice_control_elm_vc_elm_set_command_hint_p2(void);
extern int utc_voice_control_elm_vc_elm_set_command_hint_n(void);
extern int utc_voice_control_elm_vc_elm_unset_command_hint_p1(void);
extern int utc_voice_control_elm_vc_elm_unset_command_hint_p2(void);
extern int utc_voice_control_elm_vc_elm_unset_command_hint_n(void);
extern int utc_voice_control_elm_vc_elm_set_command_hint_direction_p1(void);
extern int utc_voice_control_elm_vc_elm_set_command_hint_direction_p2(void);
extern int utc_voice_control_elm_vc_elm_set_command_hint_direction_n(void);
extern int utc_voice_control_elm_vc_elm_get_command_hint_direction_p1(void);
extern int utc_voice_control_elm_vc_elm_get_command_hint_direction_p2(void);
extern int utc_voice_control_elm_vc_elm_get_command_hint_direction_n(void);
extern int utc_voice_control_elm_vc_elm_set_command_hint_offset_p1(void);
extern int utc_voice_control_elm_vc_elm_set_command_hint_offset_p2(void);
extern int utc_voice_control_elm_vc_elm_set_command_hint_offset_n(void);
extern int utc_voice_control_elm_vc_elm_get_command_hint_offset_p1(void);
extern int utc_voice_control_elm_vc_elm_get_command_hint_offset_p2(void);
extern int utc_voice_control_elm_vc_elm_get_command_hint_offset_n1(void);
extern int utc_voice_control_elm_vc_elm_get_command_hint_offset_n2(void);
extern int utc_voice_control_elm_vc_elm_set_current_language_changed_cb_p(void);
extern int utc_voice_control_elm_vc_elm_set_current_language_changed_cb_n1(void);
extern int utc_voice_control_elm_vc_elm_set_current_language_changed_cb_n2(void);
extern int utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_p(void);
extern int utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_n1(void);
extern int utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_n2(void);
extern int utc_voice_control_elm_vc_elm_foreach_supported_languages_p(void);
extern int utc_voice_control_elm_vc_elm_foreach_supported_languages_n(void);
extern int utc_voice_control_elm_vc_elm_foreach_supported_widgets_p(void);
extern int utc_voice_control_elm_vc_elm_foreach_supported_widgets_n1(void);
extern int utc_voice_control_elm_vc_elm_foreach_supported_widgets_n2(void);
extern int utc_voice_control_elm_vc_elm_foreach_supported_actions_p(void);
extern int utc_voice_control_elm_vc_elm_foreach_supported_actions_n1(void);
extern int utc_voice_control_elm_vc_elm_foreach_supported_actions_n2(void);
extern int utc_voice_control_elm_vc_elm_foreach_supported_actions_n3(void);
extern int utc_voice_control_elm_vc_elm_get_action_command_p(void);
extern int utc_voice_control_elm_vc_elm_get_action_command_n1(void);
extern int utc_voice_control_elm_vc_elm_get_action_command_n2(void);
extern int utc_voice_control_elm_vc_elm_get_action_command_n3(void);

testcase tc_array[] = {
	{"utc_voice_control_elm_vc_elm_initialize_p",utc_voice_control_elm_vc_elm_initialize_p,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_initialize_n",utc_voice_control_elm_vc_elm_initialize_n,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_deinitialize_p",utc_voice_control_elm_vc_elm_deinitialize_p,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_deinitialize_n",utc_voice_control_elm_vc_elm_deinitialize_n,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_get_current_language_p",utc_voice_control_elm_vc_elm_get_current_language_p,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_get_current_language_n",utc_voice_control_elm_vc_elm_get_current_language_n,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_object_p1",utc_voice_control_elm_vc_elm_create_object_p1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_object_p2",utc_voice_control_elm_vc_elm_create_object_p2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_object_p3",utc_voice_control_elm_vc_elm_create_object_p3,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_object_p4",utc_voice_control_elm_vc_elm_create_object_p4,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_object_p5",utc_voice_control_elm_vc_elm_create_object_p5,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_object_p6",utc_voice_control_elm_vc_elm_create_object_p6,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_object_p7",utc_voice_control_elm_vc_elm_create_object_p7,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_object_p8",utc_voice_control_elm_vc_elm_create_object_p8,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_object_p9",utc_voice_control_elm_vc_elm_create_object_p9,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_object_p10",utc_voice_control_elm_vc_elm_create_object_p10,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_object_n1",utc_voice_control_elm_vc_elm_create_object_n1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_object_n2",utc_voice_control_elm_vc_elm_create_object_n2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_object_n3",utc_voice_control_elm_vc_elm_create_object_n3,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_item_p",utc_voice_control_elm_vc_elm_create_item_p,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_item_n1",utc_voice_control_elm_vc_elm_create_item_n1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_item_n2",utc_voice_control_elm_vc_elm_create_item_n2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_create_item_n3",utc_voice_control_elm_vc_elm_create_item_n3,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_destroy_p",utc_voice_control_elm_vc_elm_destroy_p,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_destroy_n1",utc_voice_control_elm_vc_elm_destroy_n1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_destroy_n2",utc_voice_control_elm_vc_elm_destroy_n2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_destroy_n3",utc_voice_control_elm_vc_elm_destroy_n3,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_command_p1",utc_voice_control_elm_vc_elm_set_command_p1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_command_p2",utc_voice_control_elm_vc_elm_set_command_p2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_command_n",utc_voice_control_elm_vc_elm_set_command_n,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_unset_command_p1",utc_voice_control_elm_vc_elm_unset_command_p1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_unset_command_p2",utc_voice_control_elm_vc_elm_unset_command_p2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_unset_command_n",utc_voice_control_elm_vc_elm_unset_command_n,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_command_hint_p1",utc_voice_control_elm_vc_elm_set_command_hint_p1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_command_hint_p2",utc_voice_control_elm_vc_elm_set_command_hint_p2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_command_hint_n",utc_voice_control_elm_vc_elm_set_command_hint_n,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_unset_command_hint_p1",utc_voice_control_elm_vc_elm_unset_command_hint_p1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_unset_command_hint_p2",utc_voice_control_elm_vc_elm_unset_command_hint_p2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_unset_command_hint_n",utc_voice_control_elm_vc_elm_unset_command_hint_n,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_command_hint_direction_p1",utc_voice_control_elm_vc_elm_set_command_hint_direction_p1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_command_hint_direction_p2",utc_voice_control_elm_vc_elm_set_command_hint_direction_p2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_command_hint_direction_n",utc_voice_control_elm_vc_elm_set_command_hint_direction_n,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_get_command_hint_direction_p1",utc_voice_control_elm_vc_elm_get_command_hint_direction_p1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_get_command_hint_direction_p2",utc_voice_control_elm_vc_elm_get_command_hint_direction_p2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_get_command_hint_direction_n",utc_voice_control_elm_vc_elm_get_command_hint_direction_n,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_command_hint_offset_p1",utc_voice_control_elm_vc_elm_set_command_hint_offset_p1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_command_hint_offset_p2",utc_voice_control_elm_vc_elm_set_command_hint_offset_p2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_command_hint_offset_n",utc_voice_control_elm_vc_elm_set_command_hint_offset_n,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_get_command_hint_offset_p1",utc_voice_control_elm_vc_elm_get_command_hint_offset_p1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_get_command_hint_offset_p2",utc_voice_control_elm_vc_elm_get_command_hint_offset_p2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_get_command_hint_offset_n1",utc_voice_control_elm_vc_elm_get_command_hint_offset_n1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_get_command_hint_offset_n2",utc_voice_control_elm_vc_elm_get_command_hint_offset_n2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_current_language_changed_cb_p",utc_voice_control_elm_vc_elm_set_current_language_changed_cb_p,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_current_language_changed_cb_n1",utc_voice_control_elm_vc_elm_set_current_language_changed_cb_n1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_set_current_language_changed_cb_n2",utc_voice_control_elm_vc_elm_set_current_language_changed_cb_n2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_p",utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_p,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_n1",utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_n1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_n2",utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_n2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_foreach_supported_languages_p",utc_voice_control_elm_vc_elm_foreach_supported_languages_p,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_foreach_supported_languages_n",utc_voice_control_elm_vc_elm_foreach_supported_languages_n,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_foreach_supported_widgets_p",utc_voice_control_elm_vc_elm_foreach_supported_widgets_p,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_foreach_supported_widgets_n1",utc_voice_control_elm_vc_elm_foreach_supported_widgets_n1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_foreach_supported_widgets_n2",utc_voice_control_elm_vc_elm_foreach_supported_widgets_n2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_foreach_supported_actions_p",utc_voice_control_elm_vc_elm_foreach_supported_actions_p,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_foreach_supported_actions_n1",utc_voice_control_elm_vc_elm_foreach_supported_actions_n1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_foreach_supported_actions_n2",utc_voice_control_elm_vc_elm_foreach_supported_actions_n2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_foreach_supported_actions_n3",utc_voice_control_elm_vc_elm_foreach_supported_actions_n3,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_get_action_command_p",utc_voice_control_elm_vc_elm_get_action_command_p,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_get_action_command_n1",utc_voice_control_elm_vc_elm_get_action_command_n1,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_get_action_command_n2",utc_voice_control_elm_vc_elm_get_action_command_n2,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{"utc_voice_control_elm_vc_elm_get_action_command_n3",utc_voice_control_elm_vc_elm_get_action_command_n3,utc_voice_control_elm_startup,utc_voice_control_elm_cleanup},
	{NULL, NULL}
};

#endif // __TCT_VOICE-CONTROL-ELM-NATIVE_H__