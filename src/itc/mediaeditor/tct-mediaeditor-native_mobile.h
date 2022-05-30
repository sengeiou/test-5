//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#ifndef __TCT_MEDIAEDITOR_NATIVE_H__
#define __TCT_MEDIAEDITOR_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_mediaeditor_startup(void);
extern void ITs_mediaeditor_cleanup(void);

extern int ITc_mediaeditor_create_destroy_p(void);
extern int ITc_mediaeditor_set_display_p(void);
extern int ITc_mediaeditor_get_state_p(void);
extern int ITc_mediaeditor_add_remove_layer_p(void);
extern int  ITc_mediaeditor_move_layer_p(void);
extern int ITc_mediaeditor_activate_deactivate_layer_p(void);
extern int ITc_mediaeditor_get_layer_priority_p(void);
extern int ITc_mediaeditor_get_layer_lowest_priority_p(void);
extern int ITc_mediaeditor_get_layer_id_p(void);
extern int ITc_mediaeditor_add_remove_clip_p(void);
extern int ITc_mediaeditor_split_clip_p(void);
extern int ITc_mediaeditor_group_ungroup_clip_p(void);
extern int ITc_mediaeditor_move_clip_layer_p(void);
extern int ITc_mediaeditor_set_get_clip_start_p(void);
extern int ITc_mediaeditor_set_get_clip_duration_p(void);
extern int ITc_mediaeditor_set_get_clip_in_point_p(void);
extern int ITc_mediaeditor_set_get_clip_resolution_p(void);
extern int ITc_mediaeditor_set_get_clip_volume_p(void);
extern int ITc_mediaeditor_add_transition_p(void);
extern int ITc_add_remove_effect_p(void);
extern int ITc_mediaeditor_create_save_project_p(void);
extern int ITc_mediaeditor_load_project_p(void);
extern int ITc_mediaeditor_start_stop_preview_p(void);
extern int ITc_mediaeditor_set_unset_state_changed_cb_p(void);
extern int ITc_mediaeditor_set_unset_error_cb_p(void);
extern int ITc_mediaeditor_set_unset_layer_priority_changed_cb_p(void);
extern int ITc_mediaeditor_start_cancel_render_p(void);

testcase tc_array[] = {
	{"ITc_mediaeditor_create_destroy_p", ITc_mediaeditor_create_destroy_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_set_display_p", ITc_mediaeditor_set_display_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_get_state_p", ITc_mediaeditor_get_state_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_add_remove_layer_p", ITc_mediaeditor_add_remove_layer_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_move_layer_p", ITc_mediaeditor_move_layer_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_activate_deactivate_layer_p", ITc_mediaeditor_activate_deactivate_layer_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_get_layer_priority_p", ITc_mediaeditor_get_layer_priority_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_get_layer_lowest_priority_p", ITc_mediaeditor_get_layer_lowest_priority_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_get_layer_id_p", ITc_mediaeditor_get_layer_id_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_add_remove_clip_p", ITc_mediaeditor_add_remove_clip_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_split_clip_p", ITc_mediaeditor_split_clip_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_group_ungroup_clip_p", ITc_mediaeditor_group_ungroup_clip_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_move_clip_layer_p", ITc_mediaeditor_move_clip_layer_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_set_get_clip_start_p", ITc_mediaeditor_set_get_clip_start_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_set_get_clip_duration_p", ITc_mediaeditor_set_get_clip_duration_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_set_get_clip_in_point_p", ITc_mediaeditor_set_get_clip_in_point_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_set_get_clip_resolution_p", ITc_mediaeditor_set_get_clip_resolution_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_set_get_clip_volume_p", ITc_mediaeditor_set_get_clip_volume_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_add_transition_p", ITc_mediaeditor_add_transition_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_add_remove_effect_p", ITc_add_remove_effect_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_create_save_project_p", ITc_mediaeditor_create_save_project_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_load_project_p", ITc_mediaeditor_load_project_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_start_stop_preview_p", ITc_mediaeditor_start_stop_preview_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_set_unset_state_changed_cb_p", ITc_mediaeditor_set_unset_state_changed_cb_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_set_unset_error_cb_p", ITc_mediaeditor_set_unset_error_cb_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
	{"ITc_mediaeditor_set_unset_layer_priority_changed_cb_p", ITc_mediaeditor_set_unset_layer_priority_changed_cb_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},	
	{"ITc_mediaeditor_start_cancel_render_p", ITc_mediaeditor_start_cancel_render_p, ITs_mediaeditor_startup, ITs_mediaeditor_cleanup},
    {NULL, NULL}
};

#endif // __TCT_MEDIAEDITOR_NATIVE_H__
