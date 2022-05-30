/*
 * Copyright (c) 2022 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __TCT_MEDIAEDITOR-NATIVE_H__
#define __TCT_MEDIAEDITOR-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_mediaeditor_startup(void);
extern void utc_mediaeditor_cleanup(void);
extern void utc_mediaeditor_startup_create_win(void);
extern void utc_mediaeditor_cleanup_destroy_win(void);
extern void utc_mediaeditor_startup_callback(void);
extern void utc_mediaeditor_cleanup_callback(void);

extern int utc_mediaeditor_create_p(void);
extern int utc_mediaeditor_create_n(void);
extern int utc_mediaeditor_destroy_p(void);
extern int utc_mediaeditor_destroy_n(void);
extern int utc_mediaeditor_set_display_p(void);
extern int utc_mediaeditor_set_display_n1(void);
extern int utc_mediaeditor_set_display_n2(void);
extern int utc_mediaeditor_set_display_n3(void);
extern int utc_mediaeditor_get_state_p(void);
extern int utc_mediaeditor_get_state_n1(void);
extern int utc_mediaeditor_get_state_n2(void);
extern int utc_mediaeditor_start_render_p(void);
extern int utc_mediaeditor_start_render_n1(void);
extern int utc_mediaeditor_start_render_n2(void);
extern int utc_mediaeditor_start_render_n3(void);
extern int utc_mediaeditor_start_render_n4(void);
extern int utc_mediaeditor_cancel_render_p(void);
extern int utc_mediaeditor_cancel_render_n1(void);
extern int utc_mediaeditor_cancel_render_n2(void);
extern int utc_mediaeditor_start_preview_p(void);
extern int utc_mediaeditor_start_preview_n(void);
extern int utc_mediaeditor_stop_preview_p(void);
extern int utc_mediaeditor_stop_preview_n1(void);
extern int utc_mediaeditor_stop_preview_n2(void);
extern int utc_mediaeditor_add_layer_p(void);
extern int utc_mediaeditor_add_layer_n1(void);
extern int utc_mediaeditor_add_layer_n2(void);
extern int utc_mediaeditor_remove_layer_p(void);
extern int utc_mediaeditor_remove_layer_n1(void);
extern int utc_mediaeditor_remove_layer_n2(void);
extern int utc_mediaeditor_move_layer_p(void);
extern int utc_mediaeditor_move_layer_n1(void);
extern int utc_mediaeditor_move_layer_n2(void);
extern int utc_mediaeditor_activate_layer_p(void);
extern int utc_mediaeditor_activate_layer_n1(void);
extern int utc_mediaeditor_activate_layer_n2(void);
extern int utc_mediaeditor_deactivate_layer_p(void);
extern int utc_mediaeditor_deactivate_layer_n1(void);
extern int utc_mediaeditor_deactivate_layer_n2(void);
extern int utc_mediaeditor_get_layer_priority_p(void);
extern int utc_mediaeditor_get_layer_priority_n1(void);
extern int utc_mediaeditor_get_layer_priority_n2(void);
extern int utc_mediaeditor_get_layer_priority_n3(void);
extern int utc_mediaeditor_get_layer_lowest_priority_p(void);
extern int utc_mediaeditor_get_layer_lowest_priority_n1(void);
extern int utc_mediaeditor_get_layer_lowest_priority_n2(void);
extern int utc_mediaeditor_get_layer_lowest_priority_n3(void);
extern int utc_mediaeditor_get_layer_id_p(void);
extern int utc_mediaeditor_get_layer_id_n1(void);
extern int utc_mediaeditor_get_layer_id_n2(void);
extern int utc_mediaeditor_get_layer_id_n3(void);
extern int utc_mediaeditor_set_layer_priority_changed_cb_p(void);
extern int utc_mediaeditor_set_layer_priority_changed_cb_n1(void);
extern int utc_mediaeditor_set_layer_priority_changed_cb_n2(void);
extern int utc_mediaeditor_unset_layer_priority_changed_cb_p(void);
extern int utc_mediaeditor_unset_layer_priority_changed_cb_n(void);
extern int utc_mediaeditor_add_clip_p(void);
extern int utc_mediaeditor_add_clip_n1(void);
extern int utc_mediaeditor_add_clip_n2(void);
extern int utc_mediaeditor_add_clip_n3(void);
extern int utc_mediaeditor_remove_clip_p(void);
extern int utc_mediaeditor_remove_clip_n1(void);
extern int utc_mediaeditor_remove_clip_n2(void);
extern int utc_mediaeditor_split_clip_p(void);
extern int utc_mediaeditor_split_clip_n1(void);
extern int utc_mediaeditor_split_clip_n2(void);
extern int utc_mediaeditor_group_clip_p(void);
extern int utc_mediaeditor_group_clip_n1(void);
extern int utc_mediaeditor_group_clip_n2(void);
extern int utc_mediaeditor_ungroup_clip_p(void);
extern int utc_mediaeditor_ungroup_clip_n1(void);
extern int utc_mediaeditor_ungroup_clip_n2(void);
extern int utc_mediaeditor_move_clip_layer_p(void);
extern int utc_mediaeditor_move_clip_layer_n1(void);
extern int utc_mediaeditor_move_clip_layer_n2(void);
extern int utc_mediaeditor_get_clip_start_p(void);
extern int utc_mediaeditor_get_clip_start_n1(void);
extern int utc_mediaeditor_get_clip_start_n2(void);
extern int utc_mediaeditor_get_clip_start_n3(void);
extern int utc_mediaeditor_set_clip_start_p(void);
extern int utc_mediaeditor_set_clip_start_n1(void);
extern int utc_mediaeditor_set_clip_start_n2(void);
extern int utc_mediaeditor_get_clip_duration_p(void);
extern int utc_mediaeditor_get_clip_duration_n1(void);
extern int utc_mediaeditor_get_clip_duration_n2(void);
extern int utc_mediaeditor_get_clip_duration_n3(void);
extern int utc_mediaeditor_set_clip_duration_p(void);
extern int utc_mediaeditor_set_clip_duration_n1(void);
extern int utc_mediaeditor_set_clip_duration_n2(void);
extern int utc_mediaeditor_get_clip_in_point_p(void);
extern int utc_mediaeditor_get_clip_in_point_n1(void);
extern int utc_mediaeditor_get_clip_in_point_n2(void);
extern int utc_mediaeditor_get_clip_in_point_n3(void);
extern int utc_mediaeditor_set_clip_in_point_p(void);
extern int utc_mediaeditor_set_clip_in_point_n1(void);
extern int utc_mediaeditor_set_clip_in_point_n2(void);
extern int utc_mediaeditor_get_clip_resolution_p(void);
extern int utc_mediaeditor_get_clip_resolution_n1(void);
extern int utc_mediaeditor_get_clip_resolution_n2(void);
extern int utc_mediaeditor_get_clip_resolution_n3(void);
extern int utc_mediaeditor_get_clip_resolution_n4(void);
extern int utc_mediaeditor_set_clip_resolution_p(void);
extern int utc_mediaeditor_set_clip_resolution_n1(void);
extern int utc_mediaeditor_set_clip_resolution_n2(void);
extern int utc_mediaeditor_set_clip_resolution_n3(void);
extern int utc_mediaeditor_get_clip_volume_p(void);
extern int utc_mediaeditor_get_clip_volume_n1(void);
extern int utc_mediaeditor_get_clip_volume_n2(void);
extern int utc_mediaeditor_get_clip_volume_n3(void);
extern int utc_mediaeditor_set_clip_volume_p(void);
extern int utc_mediaeditor_set_clip_volume_n1(void);
extern int utc_mediaeditor_set_clip_volume_n2(void);
extern int utc_mediaeditor_add_transition_p(void);
extern int utc_mediaeditor_add_transition_n1(void);
extern int utc_mediaeditor_add_transition_n2(void);
extern int utc_mediaeditor_add_transition_n3(void);
extern int utc_mediaeditor_add_effect_p(void);
extern int utc_mediaeditor_add_effect_n1(void);
extern int utc_mediaeditor_add_effect_n2(void);
extern int utc_mediaeditor_add_effect_n3(void);
extern int utc_mediaeditor_remove_effect_p(void);
extern int utc_mediaeditor_remove_effect_n1(void);
extern int utc_mediaeditor_remove_effect_n2(void);
extern int utc_mediaeditor_create_project_p(void);
extern int utc_mediaeditor_create_project_n1(void);
extern int utc_mediaeditor_create_project_n2(void);
extern int utc_mediaeditor_load_project_p(void);
extern int utc_mediaeditor_load_project_n1(void);
extern int utc_mediaeditor_load_project_n2(void);
extern int utc_mediaeditor_save_project_p(void);
extern int utc_mediaeditor_save_project_n1(void);
extern int utc_mediaeditor_save_project_n2(void);
extern int utc_mediaeditor_set_error_cb_p(void);
extern int utc_mediaeditor_set_error_cb_n1(void);
extern int utc_mediaeditor_set_error_cb_n2(void);
extern int utc_mediaeditor_unset_error_cb_p(void);
extern int utc_mediaeditor_unset_error_cb_n1(void);
extern int utc_mediaeditor_unset_error_cb_n2(void);
extern int utc_mediaeditor_set_state_changed_cb_p(void);
extern int utc_mediaeditor_set_state_changed_cb_n1(void);
extern int utc_mediaeditor_set_state_changed_cb_n2(void);
extern int utc_mediaeditor_unset_state_changed_cb_p(void);
extern int utc_mediaeditor_unset_state_changed_cb_n1(void);
extern int utc_mediaeditor_unset_state_changed_cb_n2(void);

testcase tc_array[] = {
    {"utc_mediaeditor_create_p",utc_mediaeditor_create_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_create_n",utc_mediaeditor_create_n,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_destroy_p",utc_mediaeditor_destroy_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_destroy_n",utc_mediaeditor_destroy_n,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_display_p",utc_mediaeditor_set_display_p,utc_mediaeditor_startup_create_win,utc_mediaeditor_cleanup_destroy_win},
    {"utc_mediaeditor_set_display_n1",utc_mediaeditor_set_display_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_display_n2",utc_mediaeditor_set_display_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_display_n3",utc_mediaeditor_set_display_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_state_p",utc_mediaeditor_get_state_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_state_n1",utc_mediaeditor_get_state_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_state_n2",utc_mediaeditor_get_state_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_start_render_p",utc_mediaeditor_start_render_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_start_render_n1",utc_mediaeditor_start_render_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_start_render_n2",utc_mediaeditor_start_render_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_start_render_n3",utc_mediaeditor_start_render_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_start_render_n4",utc_mediaeditor_start_render_n4,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_cancel_render_p",utc_mediaeditor_cancel_render_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_cancel_render_n1",utc_mediaeditor_cancel_render_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_cancel_render_n2",utc_mediaeditor_cancel_render_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_start_preview_p",utc_mediaeditor_start_preview_p,utc_mediaeditor_startup_create_win,utc_mediaeditor_cleanup_destroy_win},
    {"utc_mediaeditor_start_preview_n",utc_mediaeditor_start_preview_n,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_stop_preview_p",utc_mediaeditor_stop_preview_p,utc_mediaeditor_startup_create_win,utc_mediaeditor_cleanup_destroy_win},
    {"utc_mediaeditor_stop_preview_n1",utc_mediaeditor_stop_preview_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_stop_preview_n2",utc_mediaeditor_stop_preview_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_layer_p",utc_mediaeditor_add_layer_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_layer_n1",utc_mediaeditor_add_layer_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_layer_n2",utc_mediaeditor_add_layer_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_remove_layer_p",utc_mediaeditor_remove_layer_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_remove_layer_n1",utc_mediaeditor_remove_layer_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_remove_layer_n2",utc_mediaeditor_remove_layer_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_move_layer_p",utc_mediaeditor_move_layer_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_move_layer_n1",utc_mediaeditor_move_layer_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_move_layer_n2",utc_mediaeditor_move_layer_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_activate_layer_p",utc_mediaeditor_activate_layer_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_activate_layer_n1",utc_mediaeditor_activate_layer_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_activate_layer_n2",utc_mediaeditor_activate_layer_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_deactivate_layer_p",utc_mediaeditor_deactivate_layer_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_deactivate_layer_n1",utc_mediaeditor_deactivate_layer_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_deactivate_layer_n2",utc_mediaeditor_deactivate_layer_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_layer_priority_p",utc_mediaeditor_get_layer_priority_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_layer_priority_n1",utc_mediaeditor_get_layer_priority_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_layer_priority_n2",utc_mediaeditor_get_layer_priority_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_layer_priority_n3",utc_mediaeditor_get_layer_priority_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_layer_lowest_priority_p",utc_mediaeditor_get_layer_lowest_priority_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_layer_lowest_priority_n1",utc_mediaeditor_get_layer_lowest_priority_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_layer_lowest_priority_n2",utc_mediaeditor_get_layer_lowest_priority_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_layer_lowest_priority_n3",utc_mediaeditor_get_layer_lowest_priority_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_layer_id_p",utc_mediaeditor_get_layer_id_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_layer_id_n1",utc_mediaeditor_get_layer_id_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_layer_id_n2",utc_mediaeditor_get_layer_id_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_layer_id_n3",utc_mediaeditor_get_layer_id_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_layer_priority_changed_cb_p",utc_mediaeditor_set_layer_priority_changed_cb_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_layer_priority_changed_cb_n1",utc_mediaeditor_set_layer_priority_changed_cb_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_layer_priority_changed_cb_n2",utc_mediaeditor_set_layer_priority_changed_cb_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_unset_layer_priority_changed_cb_p",utc_mediaeditor_unset_layer_priority_changed_cb_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_unset_layer_priority_changed_cb_n",utc_mediaeditor_unset_layer_priority_changed_cb_n,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_clip_p",utc_mediaeditor_add_clip_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_clip_n1",utc_mediaeditor_add_clip_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_clip_n2",utc_mediaeditor_add_clip_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_clip_n3",utc_mediaeditor_add_clip_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_remove_clip_p",utc_mediaeditor_remove_clip_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_remove_clip_n1",utc_mediaeditor_remove_clip_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_remove_clip_n2",utc_mediaeditor_remove_clip_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_split_clip_p",utc_mediaeditor_split_clip_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_split_clip_n1",utc_mediaeditor_split_clip_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_split_clip_n2",utc_mediaeditor_split_clip_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_group_clip_p",utc_mediaeditor_group_clip_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_group_clip_n1",utc_mediaeditor_group_clip_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_group_clip_n2",utc_mediaeditor_group_clip_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_ungroup_clip_p",utc_mediaeditor_ungroup_clip_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_ungroup_clip_n1",utc_mediaeditor_ungroup_clip_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_ungroup_clip_n2",utc_mediaeditor_ungroup_clip_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_move_clip_layer_p",utc_mediaeditor_move_clip_layer_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_move_clip_layer_n1",utc_mediaeditor_move_clip_layer_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_move_clip_layer_n2",utc_mediaeditor_move_clip_layer_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_start_p",utc_mediaeditor_get_clip_start_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_start_n1",utc_mediaeditor_get_clip_start_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_start_n2",utc_mediaeditor_get_clip_start_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_start_n3",utc_mediaeditor_get_clip_start_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_start_p",utc_mediaeditor_set_clip_start_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_start_n1",utc_mediaeditor_set_clip_start_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_start_n2",utc_mediaeditor_set_clip_start_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_duration_p",utc_mediaeditor_get_clip_duration_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_duration_n1",utc_mediaeditor_get_clip_duration_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_duration_n2",utc_mediaeditor_get_clip_duration_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_duration_n3",utc_mediaeditor_get_clip_duration_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_duration_p",utc_mediaeditor_set_clip_duration_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_duration_n1",utc_mediaeditor_set_clip_duration_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_duration_n2",utc_mediaeditor_set_clip_duration_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_in_point_p",utc_mediaeditor_get_clip_in_point_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_in_point_n1",utc_mediaeditor_get_clip_in_point_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_in_point_n2",utc_mediaeditor_get_clip_in_point_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_in_point_n3",utc_mediaeditor_get_clip_in_point_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_in_point_p",utc_mediaeditor_set_clip_in_point_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_in_point_n1",utc_mediaeditor_set_clip_in_point_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_in_point_n2",utc_mediaeditor_set_clip_in_point_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_resolution_p",utc_mediaeditor_get_clip_resolution_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_resolution_n1",utc_mediaeditor_get_clip_resolution_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_resolution_n2",utc_mediaeditor_get_clip_resolution_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_resolution_n3",utc_mediaeditor_get_clip_resolution_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_resolution_n4",utc_mediaeditor_get_clip_resolution_n4,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_resolution_p",utc_mediaeditor_set_clip_resolution_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_resolution_n1",utc_mediaeditor_set_clip_resolution_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_resolution_n2",utc_mediaeditor_set_clip_resolution_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_resolution_n3",utc_mediaeditor_set_clip_resolution_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_volume_p",utc_mediaeditor_get_clip_volume_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_volume_n1",utc_mediaeditor_get_clip_volume_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_volume_n2",utc_mediaeditor_get_clip_volume_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_get_clip_volume_n3",utc_mediaeditor_get_clip_volume_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_volume_p",utc_mediaeditor_set_clip_volume_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_volume_n1",utc_mediaeditor_set_clip_volume_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_clip_volume_n2",utc_mediaeditor_set_clip_volume_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_transition_p",utc_mediaeditor_add_transition_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_transition_n1",utc_mediaeditor_add_transition_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_transition_n2",utc_mediaeditor_add_transition_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_transition_n3",utc_mediaeditor_add_transition_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_effect_p",utc_mediaeditor_add_effect_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_effect_n1",utc_mediaeditor_add_effect_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_effect_n2",utc_mediaeditor_add_effect_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_add_effect_n3",utc_mediaeditor_add_effect_n3,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_remove_effect_p",utc_mediaeditor_remove_effect_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_remove_effect_n1",utc_mediaeditor_remove_effect_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_remove_effect_n2",utc_mediaeditor_remove_effect_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_create_project_p",utc_mediaeditor_create_project_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_create_project_n1",utc_mediaeditor_create_project_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_create_project_n2",utc_mediaeditor_create_project_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_load_project_p",utc_mediaeditor_load_project_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_load_project_n1",utc_mediaeditor_load_project_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_load_project_n2",utc_mediaeditor_load_project_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_save_project_p",utc_mediaeditor_save_project_p,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_save_project_n1",utc_mediaeditor_save_project_n1,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_save_project_n2",utc_mediaeditor_save_project_n2,utc_mediaeditor_startup,utc_mediaeditor_cleanup},
    {"utc_mediaeditor_set_error_cb_p",utc_mediaeditor_set_error_cb_p,utc_mediaeditor_startup_callback,utc_mediaeditor_cleanup_callback},
    {"utc_mediaeditor_set_error_cb_n1",utc_mediaeditor_set_error_cb_n1,utc_mediaeditor_startup_callback,utc_mediaeditor_cleanup_callback},
    {"utc_mediaeditor_set_error_cb_n2",utc_mediaeditor_set_error_cb_n2,utc_mediaeditor_startup_callback,utc_mediaeditor_cleanup_callback},
    {"utc_mediaeditor_unset_error_cb_p",utc_mediaeditor_unset_error_cb_p,utc_mediaeditor_startup_callback,utc_mediaeditor_cleanup_callback},
    {"utc_mediaeditor_unset_error_cb_n1",utc_mediaeditor_unset_error_cb_n1,utc_mediaeditor_startup_callback,utc_mediaeditor_cleanup_callback},
    {"utc_mediaeditor_unset_error_cb_n2",utc_mediaeditor_unset_error_cb_n2,utc_mediaeditor_startup_callback,utc_mediaeditor_cleanup_callback},
    {"utc_mediaeditor_set_state_changed_cb_p",utc_mediaeditor_set_state_changed_cb_p,utc_mediaeditor_startup_callback,utc_mediaeditor_cleanup_callback},
    {"utc_mediaeditor_set_state_changed_cb_n1",utc_mediaeditor_set_state_changed_cb_n1,utc_mediaeditor_startup_callback,utc_mediaeditor_cleanup_callback},
    {"utc_mediaeditor_set_state_changed_cb_n2",utc_mediaeditor_set_state_changed_cb_n2,utc_mediaeditor_startup_callback,utc_mediaeditor_cleanup_callback},
    {"utc_mediaeditor_unset_state_changed_cb_p",utc_mediaeditor_unset_state_changed_cb_p,utc_mediaeditor_startup_callback,utc_mediaeditor_cleanup_callback},
    {"utc_mediaeditor_unset_state_changed_cb_n1",utc_mediaeditor_unset_state_changed_cb_n1,utc_mediaeditor_startup_callback,utc_mediaeditor_cleanup_callback},
    {"utc_mediaeditor_unset_state_changed_cb_n2",utc_mediaeditor_unset_state_changed_cb_n2,utc_mediaeditor_startup_callback,utc_mediaeditor_cleanup_callback},
    {NULL, NULL}
};

#endif // __TCT_MEDIAEDITOR-NATIVE_H__
