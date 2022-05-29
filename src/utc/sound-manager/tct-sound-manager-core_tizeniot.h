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
#ifndef __TCT_SOUND-MANAGER-NATIVE_H__
#define __TCT_SOUND-MANAGER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"


extern int utc_media_sound_manager_get_max_volume_p1(void);
extern int utc_media_sound_manager_get_max_volume_p2(void);
extern int utc_media_sound_manager_get_max_volume_p3(void);
extern int utc_media_sound_manager_get_max_volume_p4(void);
extern int utc_media_sound_manager_get_max_volume_n(void);
extern int utc_media_sound_manager_set_volume_p(void);
extern int utc_media_sound_manager_set_volume_n1(void);
extern int utc_media_sound_manager_set_volume_n2(void);
extern int utc_media_sound_manager_get_volume_p(void);
extern int utc_media_sound_manager_get_volume_n1(void);
extern int utc_media_sound_manager_get_volume_n2(void);
extern int utc_media_sound_manager_get_current_sound_type_p(void);
extern int utc_media_sound_manager_get_current_sound_type_n(void);
extern int utc_sound_manager_get_device_list_p(void);
extern int utc_sound_manager_get_device_list_n(void);
extern int utc_sound_manager_get_next_device_p(void);
extern int utc_sound_manager_get_next_device_n(void);
extern int utc_sound_manager_get_prev_device_p(void);
extern int utc_sound_manager_get_prev_device_n(void);
extern int utc_sound_manager_get_device_type_p(void);
extern int utc_sound_manager_get_device_type_n(void);
extern int utc_sound_manager_get_device_io_direction_p(void);
extern int utc_sound_manager_get_device_io_direction_n(void);
extern int utc_sound_manager_get_device_id_p(void);
extern int utc_sound_manager_get_device_id_n(void);
extern int utc_sound_manager_get_device_name_p(void);
extern int utc_sound_manager_get_device_name_n(void);
extern int utc_sound_manager_is_device_running_p(void);
extern int utc_sound_manager_is_device_running_n(void);
extern int utc_sound_manager_get_device_state_p(void);
extern int utc_sound_manager_get_device_state_n(void);
extern int utc_sound_manager_free_device_list_p(void);
extern int utc_sound_manager_free_device_list_n(void);
extern int utc_sound_manager_get_supported_sample_formats_p(void);
extern int utc_sound_manager_get_supported_sample_formats_n1(void);
extern int utc_sound_manager_get_supported_sample_formats_n2(void);
extern int utc_sound_manager_get_sample_format_p(void);
extern int utc_sound_manager_get_sample_format_n(void);
extern int utc_sound_manager_set_sample_format_p(void);
extern int utc_sound_manager_set_sample_format_n(void);
extern int utc_sound_manager_get_supported_sample_rates_p(void);
extern int utc_sound_manager_get_supported_sample_rates_n(void);
extern int utc_sound_manager_get_sample_rate_p(void);
extern int utc_sound_manager_get_sample_rate_n(void);
extern int utc_sound_manager_set_sample_rate_p(void);
extern int utc_sound_manager_set_sample_rate_n(void);
extern int utc_sound_manager_get_media_stream_only_p(void);
extern int utc_sound_manager_get_media_stream_only_n(void);
extern int utc_sound_manager_set_media_stream_only_p(void);
extern int utc_sound_manager_set_media_stream_only_n(void);
extern int utc_sound_manager_get_avoid_resampling_p(void);
extern int utc_sound_manager_get_avoid_resampling_n(void);
extern int utc_sound_manager_set_avoid_resampling_p(void);
extern int utc_sound_manager_set_avoid_resampling_n(void);
extern int utc_sound_manager_create_stream_information_p(void);
extern int utc_sound_manager_create_stream_information_n(void);
extern int utc_sound_manager_destroy_stream_information_p(void);
extern int utc_sound_manager_destroy_stream_information_n(void);
extern int utc_sound_manager_add_device_for_stream_routing_p(void);
extern int utc_sound_manager_add_device_for_stream_routing_n1(void);
extern int utc_sound_manager_add_device_for_stream_routing_n2(void);
extern int utc_sound_manager_add_device_for_stream_routing_n3(void);
extern int utc_sound_manager_remove_device_for_stream_routing_p(void);
extern int utc_sound_manager_remove_device_for_stream_routing_n(void);
extern int utc_sound_manager_remove_all_devices_for_stream_routing_p(void);
extern int utc_sound_manager_remove_all_devices_for_stream_routing_n(void);
extern int utc_sound_manager_apply_stream_routing_p(void);
extern int utc_sound_manager_apply_stream_routing_n(void);
extern int utc_sound_manager_set_stream_preferred_device_p(void);
extern int utc_sound_manager_set_stream_preferred_device_n(void);
extern int utc_sound_manager_get_stream_preferred_device_p(void);
extern int utc_sound_manager_get_stream_preferred_device_n(void);
extern int utc_sound_manager_acquire_focus_p(void);
extern int utc_sound_manager_acquire_focus_n1(void);
extern int utc_sound_manager_acquire_focus_n2(void);
extern int utc_sound_manager_release_focus_p(void);
extern int utc_sound_manager_release_focus_n1(void);
extern int utc_sound_manager_release_focus_n2(void);
extern int utc_sound_manager_acquire_focus_all_p(void);
extern int utc_sound_manager_acquire_focus_all_n1(void);
extern int utc_sound_manager_acquire_focus_all_n2(void);
extern int utc_sound_manager_release_focus_all_p(void);
extern int utc_sound_manager_release_focus_all_n(void);
extern int utc_sound_manager_deliver_focus_p(void);
extern int utc_sound_manager_deliver_focus_n(void);
extern int utc_sound_manager_get_focus_state_p(void);
extern int utc_sound_manager_get_focus_state_n(void);
extern int utc_sound_manager_set_focus_reacquisition_p(void);
extern int utc_sound_manager_set_focus_reacquisition_n(void);
extern int utc_sound_manager_get_focus_reacquisition_p(void);
extern int utc_sound_manager_get_focus_reacquisition_n(void);
extern int utc_sound_manager_get_sound_type_p1(void);
extern int utc_sound_manager_get_sound_type_p2(void);
extern int utc_sound_manager_get_sound_type_p3(void);
extern int utc_sound_manager_get_sound_type_p4(void);
extern int utc_sound_manager_get_sound_type_n(void);
extern int utc_media_sound_manager_get_current_playback_focus_p1(void);
extern int utc_media_sound_manager_get_current_playback_focus_p2(void);
extern int utc_media_sound_manager_get_current_playback_focus_p3(void);
extern int utc_media_sound_manager_get_current_playback_focus_n(void);
extern int utc_media_sound_manager_get_current_recording_focus_p1(void);
extern int utc_media_sound_manager_get_current_recording_focus_p2(void);
extern int utc_media_sound_manager_get_current_recording_focus_p3(void);
extern int utc_media_sound_manager_get_current_recording_focus_n(void);
extern int utc_media_sound_manager_is_stream_on_device_p(void);
extern int utc_media_sound_manager_is_stream_on_device_n(void);
extern int utc_media_sound_manager_get_current_media_playback_device_type_p(void);
extern int utc_media_sound_manager_get_current_media_playback_device_type_n(void);
extern int utc_media_sound_manager_add_volume_changed_cb_p(void);
extern int utc_media_sound_manager_add_volume_changed_cb_n(void);
extern int utc_media_sound_manager_remove_volume_changed_cb_p(void);
extern int utc_media_sound_manager_remove_volume_changed_cb_n(void);
extern int utc_media_sound_manager_add_device_connection_changed_cb_p(void);
extern int utc_media_sound_manager_add_device_connection_changed_cb_n(void);
extern int utc_media_sound_manager_remove_device_connection_changed_cb_p(void);
extern int utc_media_sound_manager_remove_device_connection_changed_cb_n(void);
extern int utc_media_sound_manager_add_device_running_changed_cb_p(void);
extern int utc_media_sound_manager_add_device_running_changed_cb_n(void);
extern int utc_media_sound_manager_remove_device_running_changed_cb_p(void);
extern int utc_media_sound_manager_remove_device_running_changed_cb_n(void);
extern int utc_media_sound_manager_add_device_state_changed_cb_p(void);
extern int utc_media_sound_manager_add_device_state_changed_cb_n(void);
extern int utc_media_sound_manager_remove_device_state_changed_cb_p(void);
extern int utc_media_sound_manager_remove_device_state_changed_cb_n(void);
extern int utc_media_sound_manager_add_focus_state_watch_cb_p(void);
extern int utc_media_sound_manager_add_focus_state_watch_cb_n(void);
extern int utc_media_sound_manager_remove_focus_state_watch_cb_p(void);
extern int utc_media_sound_manager_remove_focus_state_watch_cb_n(void);
extern int utc_media_sound_manager_create_stream_ducking_p(void);
extern int utc_media_sound_manager_create_stream_ducking_n(void);
extern int utc_media_sound_manager_is_ducked_p(void);
extern int utc_media_sound_manager_is_ducked_n(void);
extern int utc_media_sound_manager_activate_ducking_p(void);
extern int utc_media_sound_manager_activate_ducking_n(void);
extern int utc_media_sound_manager_deactivate_ducking_p(void);
extern int utc_media_sound_manager_deactivate_ducking_n(void);
extern int utc_media_sound_manager_destroy_stream_ducking_p(void);
extern int utc_media_sound_manager_destroy_stream_ducking_n(void);

testcase tc_array[] = {
	{"utc_media_sound_manager_get_max_volume_p1",utc_media_sound_manager_get_max_volume_p1,NULL,NULL},
	{"utc_media_sound_manager_get_max_volume_p2",utc_media_sound_manager_get_max_volume_p2,NULL,NULL},
	{"utc_media_sound_manager_get_max_volume_p3",utc_media_sound_manager_get_max_volume_p3,NULL,NULL},
	{"utc_media_sound_manager_get_max_volume_p4",utc_media_sound_manager_get_max_volume_p4,NULL,NULL},
	{"utc_media_sound_manager_get_max_volume_n",utc_media_sound_manager_get_max_volume_n,NULL,NULL},
	{"utc_media_sound_manager_set_volume_p",utc_media_sound_manager_set_volume_p,NULL,NULL},
	{"utc_media_sound_manager_set_volume_n1",utc_media_sound_manager_set_volume_n1,NULL,NULL},
	{"utc_media_sound_manager_set_volume_n2",utc_media_sound_manager_set_volume_n2,NULL,NULL},
	{"utc_media_sound_manager_get_volume_p",utc_media_sound_manager_get_volume_p,NULL,NULL},
	{"utc_media_sound_manager_get_volume_n1",utc_media_sound_manager_get_volume_n1,NULL,NULL},
	{"utc_media_sound_manager_get_volume_n2",utc_media_sound_manager_get_volume_n2,NULL,NULL},
	{"utc_media_sound_manager_get_current_sound_type_p",utc_media_sound_manager_get_current_sound_type_p,NULL,NULL},
	{"utc_media_sound_manager_get_current_sound_type_n",utc_media_sound_manager_get_current_sound_type_n,NULL,NULL},
	{"utc_sound_manager_get_device_list_p",utc_sound_manager_get_device_list_p,NULL,NULL},
	{"utc_sound_manager_get_device_list_n",utc_sound_manager_get_device_list_n,NULL,NULL},
	{"utc_sound_manager_get_next_device_p",utc_sound_manager_get_next_device_p,NULL,NULL},
	{"utc_sound_manager_get_next_device_n",utc_sound_manager_get_next_device_n,NULL,NULL},
	{"utc_sound_manager_get_prev_device_p",utc_sound_manager_get_prev_device_p,NULL,NULL},
	{"utc_sound_manager_get_prev_device_n",utc_sound_manager_get_prev_device_n,NULL,NULL},
	{"utc_sound_manager_get_device_type_p",utc_sound_manager_get_device_type_p,NULL,NULL},
	{"utc_sound_manager_get_device_type_n",utc_sound_manager_get_device_type_n,NULL,NULL},
	{"utc_sound_manager_get_device_io_direction_p",utc_sound_manager_get_device_io_direction_p,NULL,NULL},
	{"utc_sound_manager_get_device_io_direction_n",utc_sound_manager_get_device_io_direction_n,NULL,NULL},
	{"utc_sound_manager_get_device_id_p",utc_sound_manager_get_device_id_p,NULL,NULL},
	{"utc_sound_manager_get_device_id_n",utc_sound_manager_get_device_id_n,NULL,NULL},
	{"utc_sound_manager_get_device_name_p",utc_sound_manager_get_device_name_p,NULL,NULL},
	{"utc_sound_manager_get_device_name_n",utc_sound_manager_get_device_name_n,NULL,NULL},
	{"utc_sound_manager_is_device_running_p",utc_sound_manager_is_device_running_p,NULL,NULL},
	{"utc_sound_manager_is_device_running_n",utc_sound_manager_is_device_running_n,NULL,NULL},
	{"utc_sound_manager_get_device_state_p",utc_sound_manager_get_device_state_p,NULL,NULL},
	{"utc_sound_manager_get_device_state_n",utc_sound_manager_get_device_state_n,NULL,NULL},
	{"utc_sound_manager_free_device_list_p",utc_sound_manager_free_device_list_p,NULL,NULL},
	{"utc_sound_manager_free_device_list_n",utc_sound_manager_free_device_list_n,NULL,NULL},
	{"utc_sound_manager_get_supported_sample_formats_p",utc_sound_manager_get_supported_sample_formats_p,NULL,NULL},
	{"utc_sound_manager_get_supported_sample_formats_n1",utc_sound_manager_get_supported_sample_formats_n1,NULL,NULL},
	{"utc_sound_manager_get_supported_sample_formats_n2",utc_sound_manager_get_supported_sample_formats_n2,NULL,NULL},
	{"utc_sound_manager_get_sample_format_p",utc_sound_manager_get_sample_format_p,NULL,NULL},
	{"utc_sound_manager_get_sample_format_n",utc_sound_manager_get_sample_format_n,NULL,NULL},
	{"utc_sound_manager_set_sample_format_p",utc_sound_manager_set_sample_format_p,NULL,NULL},
	{"utc_sound_manager_set_sample_format_n",utc_sound_manager_set_sample_format_n,NULL,NULL},
	{"utc_sound_manager_get_supported_sample_rates_p",utc_sound_manager_get_supported_sample_rates_p,NULL,NULL},
	{"utc_sound_manager_get_supported_sample_rates_n",utc_sound_manager_get_supported_sample_rates_n,NULL,NULL},
	{"utc_sound_manager_get_sample_rate_p",utc_sound_manager_get_sample_rate_p,NULL,NULL},
	{"utc_sound_manager_get_sample_rate_n",utc_sound_manager_get_sample_rate_n,NULL,NULL},
	{"utc_sound_manager_set_sample_rate_p",utc_sound_manager_set_sample_rate_p,NULL,NULL},
	{"utc_sound_manager_set_sample_rate_n",utc_sound_manager_set_sample_rate_n,NULL,NULL},
	{"utc_sound_manager_get_media_stream_only_p",utc_sound_manager_get_media_stream_only_p,NULL,NULL},
	{"utc_sound_manager_get_media_stream_only_n",utc_sound_manager_get_media_stream_only_n,NULL,NULL},
	{"utc_sound_manager_set_media_stream_only_p",utc_sound_manager_set_media_stream_only_p,NULL,NULL},
	{"utc_sound_manager_set_media_stream_only_n",utc_sound_manager_set_media_stream_only_n,NULL,NULL},
	{"utc_sound_manager_get_avoid_resampling_p",utc_sound_manager_get_avoid_resampling_p,NULL,NULL},
	{"utc_sound_manager_get_avoid_resampling_n",utc_sound_manager_get_avoid_resampling_n,NULL,NULL},
	{"utc_sound_manager_set_avoid_resampling_p",utc_sound_manager_set_avoid_resampling_p,NULL,NULL},
	{"utc_sound_manager_set_avoid_resampling_n",utc_sound_manager_set_avoid_resampling_n,NULL,NULL},
	{"utc_sound_manager_create_stream_information_p",utc_sound_manager_create_stream_information_p,NULL,NULL},
	{"utc_sound_manager_create_stream_information_n",utc_sound_manager_create_stream_information_n,NULL,NULL},
	{"utc_sound_manager_destroy_stream_information_p",utc_sound_manager_destroy_stream_information_p,NULL,NULL},
	{"utc_sound_manager_destroy_stream_information_n",utc_sound_manager_destroy_stream_information_n,NULL,NULL},
	{"utc_sound_manager_add_device_for_stream_routing_p",utc_sound_manager_add_device_for_stream_routing_p,NULL,NULL},
	{"utc_sound_manager_add_device_for_stream_routing_n1",utc_sound_manager_add_device_for_stream_routing_n1,NULL,NULL},
	{"utc_sound_manager_add_device_for_stream_routing_n2",utc_sound_manager_add_device_for_stream_routing_n2,NULL,NULL},
	{"utc_sound_manager_add_device_for_stream_routing_n3",utc_sound_manager_add_device_for_stream_routing_n3,NULL,NULL},
	{"utc_sound_manager_remove_device_for_stream_routing_p",utc_sound_manager_remove_device_for_stream_routing_p,NULL,NULL},
	{"utc_sound_manager_remove_device_for_stream_routing_n",utc_sound_manager_remove_device_for_stream_routing_n,NULL,NULL},
	{"utc_sound_manager_remove_all_devices_for_stream_routing_p",utc_sound_manager_remove_all_devices_for_stream_routing_p,NULL,NULL},
	{"utc_sound_manager_remove_all_devices_for_stream_routing_n",utc_sound_manager_remove_all_devices_for_stream_routing_n,NULL,NULL},
	{"utc_sound_manager_apply_stream_routing_p",utc_sound_manager_apply_stream_routing_p,NULL,NULL},
	{"utc_sound_manager_apply_stream_routing_n",utc_sound_manager_apply_stream_routing_n,NULL,NULL},
	{"utc_sound_manager_set_stream_preferred_device_p",utc_sound_manager_set_stream_preferred_device_p,NULL,NULL},
	{"utc_sound_manager_set_stream_preferred_device_n",utc_sound_manager_set_stream_preferred_device_n,NULL,NULL},
	{"utc_sound_manager_get_stream_preferred_device_p",utc_sound_manager_get_stream_preferred_device_p,NULL,NULL},
	{"utc_sound_manager_get_stream_preferred_device_n",utc_sound_manager_get_stream_preferred_device_n,NULL,NULL},
	{"utc_sound_manager_acquire_focus_p",utc_sound_manager_acquire_focus_p,NULL,NULL},
	{"utc_sound_manager_acquire_focus_n1",utc_sound_manager_acquire_focus_n1,NULL,NULL},
	{"utc_sound_manager_acquire_focus_n2",utc_sound_manager_acquire_focus_n2,NULL,NULL},
	{"utc_sound_manager_release_focus_p",utc_sound_manager_release_focus_p,NULL,NULL},
	{"utc_sound_manager_release_focus_n1",utc_sound_manager_release_focus_n1,NULL,NULL},
	{"utc_sound_manager_release_focus_n2",utc_sound_manager_release_focus_n2,NULL,NULL},
	{"utc_sound_manager_acquire_focus_all_p",utc_sound_manager_acquire_focus_all_p,NULL,NULL},
	{"utc_sound_manager_acquire_focus_all_n1",utc_sound_manager_acquire_focus_all_n1,NULL,NULL},
	{"utc_sound_manager_acquire_focus_all_n2",utc_sound_manager_acquire_focus_all_n2,NULL,NULL},
	{"utc_sound_manager_release_focus_all_p",utc_sound_manager_release_focus_all_p,NULL,NULL},
	{"utc_sound_manager_release_focus_all_n",utc_sound_manager_release_focus_all_n,NULL,NULL},
	{"utc_sound_manager_deliver_focus_p",utc_sound_manager_deliver_focus_p,NULL,NULL},
	{"utc_sound_manager_deliver_focus_n",utc_sound_manager_deliver_focus_n,NULL,NULL},
	{"utc_sound_manager_get_focus_state_p",utc_sound_manager_get_focus_state_p,NULL,NULL},
	{"utc_sound_manager_get_focus_state_n",utc_sound_manager_get_focus_state_n,NULL,NULL},
	{"utc_sound_manager_set_focus_reacquisition_p",utc_sound_manager_set_focus_reacquisition_p,NULL,NULL},
	{"utc_sound_manager_set_focus_reacquisition_n",utc_sound_manager_set_focus_reacquisition_n,NULL,NULL},
	{"utc_sound_manager_get_focus_reacquisition_p",utc_sound_manager_get_focus_reacquisition_p,NULL,NULL},
	{"utc_sound_manager_get_focus_reacquisition_n",utc_sound_manager_get_focus_reacquisition_n,NULL,NULL},
	{"utc_sound_manager_get_sound_type_p1",utc_sound_manager_get_sound_type_p1,NULL,NULL},
	{"utc_sound_manager_get_sound_type_p2",utc_sound_manager_get_sound_type_p2,NULL,NULL},
	{"utc_sound_manager_get_sound_type_p3",utc_sound_manager_get_sound_type_p3,NULL,NULL},
	{"utc_sound_manager_get_sound_type_p4",utc_sound_manager_get_sound_type_p4,NULL,NULL},
	{"utc_sound_manager_get_sound_type_n",utc_sound_manager_get_sound_type_n,NULL,NULL},
	{"utc_media_sound_manager_get_current_playback_focus_p1",utc_media_sound_manager_get_current_playback_focus_p1,NULL,NULL},
	{"utc_media_sound_manager_get_current_playback_focus_p2",utc_media_sound_manager_get_current_playback_focus_p2,NULL,NULL},
	{"utc_media_sound_manager_get_current_playback_focus_p3",utc_media_sound_manager_get_current_playback_focus_p3,NULL,NULL},
	{"utc_media_sound_manager_get_current_playback_focus_n",utc_media_sound_manager_get_current_playback_focus_n,NULL,NULL},
	{"utc_media_sound_manager_get_current_recording_focus_p1",utc_media_sound_manager_get_current_recording_focus_p1,NULL,NULL},
	{"utc_media_sound_manager_get_current_recording_focus_p2",utc_media_sound_manager_get_current_recording_focus_p2,NULL,NULL},
	{"utc_media_sound_manager_get_current_recording_focus_p3",utc_media_sound_manager_get_current_recording_focus_p3,NULL,NULL},
	{"utc_media_sound_manager_get_current_recording_focus_n",utc_media_sound_manager_get_current_recording_focus_n,NULL,NULL},
	{"utc_media_sound_manager_is_stream_on_device_p",utc_media_sound_manager_is_stream_on_device_p,NULL,NULL},
	{"utc_media_sound_manager_is_stream_on_device_n",utc_media_sound_manager_is_stream_on_device_n,NULL,NULL},
	{"utc_media_sound_manager_get_current_media_playback_device_type_p",utc_media_sound_manager_get_current_media_playback_device_type_p,NULL,NULL},
	{"utc_media_sound_manager_get_current_media_playback_device_type_n",utc_media_sound_manager_get_current_media_playback_device_type_n,NULL,NULL},
	{"utc_media_sound_manager_add_volume_changed_cb_p",utc_media_sound_manager_add_volume_changed_cb_p,NULL,NULL},
	{"utc_media_sound_manager_add_volume_changed_cb_n",utc_media_sound_manager_add_volume_changed_cb_n,NULL,NULL},
	{"utc_media_sound_manager_remove_volume_changed_cb_p",utc_media_sound_manager_remove_volume_changed_cb_p,NULL,NULL},
	{"utc_media_sound_manager_remove_volume_changed_cb_n",utc_media_sound_manager_remove_volume_changed_cb_n,NULL,NULL},
	{"utc_media_sound_manager_add_device_connection_changed_cb_p",utc_media_sound_manager_add_device_connection_changed_cb_p,NULL,NULL},
	{"utc_media_sound_manager_add_device_connection_changed_cb_n",utc_media_sound_manager_add_device_connection_changed_cb_n,NULL,NULL},
	{"utc_media_sound_manager_remove_device_connection_changed_cb_p",utc_media_sound_manager_remove_device_connection_changed_cb_p,NULL,NULL},
	{"utc_media_sound_manager_remove_device_connection_changed_cb_n",utc_media_sound_manager_remove_device_connection_changed_cb_n,NULL,NULL},
	{"utc_media_sound_manager_add_device_running_changed_cb_p",utc_media_sound_manager_add_device_running_changed_cb_p,NULL,NULL},
	{"utc_media_sound_manager_add_device_running_changed_cb_n",utc_media_sound_manager_add_device_running_changed_cb_n,NULL,NULL},
	{"utc_media_sound_manager_remove_device_running_changed_cb_p",utc_media_sound_manager_remove_device_running_changed_cb_p,NULL,NULL},
	{"utc_media_sound_manager_remove_device_running_changed_cb_n",utc_media_sound_manager_remove_device_running_changed_cb_n,NULL,NULL},
	{"utc_media_sound_manager_add_device_state_changed_cb_p",utc_media_sound_manager_add_device_state_changed_cb_p,NULL,NULL},
	{"utc_media_sound_manager_add_device_state_changed_cb_n",utc_media_sound_manager_add_device_state_changed_cb_n,NULL,NULL},
	{"utc_media_sound_manager_remove_device_state_changed_cb_p",utc_media_sound_manager_remove_device_state_changed_cb_p,NULL,NULL},
	{"utc_media_sound_manager_remove_device_state_changed_cb_n",utc_media_sound_manager_remove_device_state_changed_cb_n,NULL,NULL},
	{"utc_media_sound_manager_add_focus_state_watch_cb_p",utc_media_sound_manager_add_focus_state_watch_cb_p,NULL,NULL},
	{"utc_media_sound_manager_add_focus_state_watch_cb_n",utc_media_sound_manager_add_focus_state_watch_cb_n,NULL,NULL},
	{"utc_media_sound_manager_remove_focus_state_watch_cb_p",utc_media_sound_manager_remove_focus_state_watch_cb_p,NULL,NULL},
	{"utc_media_sound_manager_remove_focus_state_watch_cb_n",utc_media_sound_manager_remove_focus_state_watch_cb_n,NULL,NULL},
	{"utc_media_sound_manager_create_stream_ducking_p",utc_media_sound_manager_create_stream_ducking_p,NULL,NULL},
	{"utc_media_sound_manager_create_stream_ducking_n",utc_media_sound_manager_create_stream_ducking_n,NULL,NULL},
	{"utc_media_sound_manager_is_ducked_p",utc_media_sound_manager_is_ducked_p,NULL,NULL},
	{"utc_media_sound_manager_is_ducked_n",utc_media_sound_manager_is_ducked_n,NULL,NULL},
	{"utc_media_sound_manager_activate_ducking_p",utc_media_sound_manager_activate_ducking_p,NULL,NULL},
	{"utc_media_sound_manager_activate_ducking_n",utc_media_sound_manager_activate_ducking_n,NULL,NULL},
	{"utc_media_sound_manager_deactivate_ducking_p",utc_media_sound_manager_deactivate_ducking_p,NULL,NULL},
	{"utc_media_sound_manager_deactivate_ducking_n",utc_media_sound_manager_deactivate_ducking_n,NULL,NULL},
	{"utc_media_sound_manager_destroy_stream_ducking_p",utc_media_sound_manager_destroy_stream_ducking_p,NULL,NULL},
	{"utc_media_sound_manager_destroy_stream_ducking_n",utc_media_sound_manager_destroy_stream_ducking_n,NULL,NULL},
	{NULL, NULL}
};

#endif // __TCT_SOUND-MANAGER-NATIVE_H__
