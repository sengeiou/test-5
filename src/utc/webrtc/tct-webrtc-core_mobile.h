/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd All Rights Reserved
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

#ifndef __TCT_WEBRTC-NATIVE_H__
#define __TCT_WEBRTC-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_media_webrtc_startup_create_win(void);
extern void utc_media_webrtc_cleanup_destroy_win(void);

extern int utc_media_webrtc_create_p(void);
extern int utc_media_webrtc_create_n(void);
extern int utc_media_webrtc_destroy_p(void);
extern int utc_media_webrtc_destroy_n(void);
extern int utc_media_webrtc_start_p(void);
extern int utc_media_webrtc_start_n1(void);
extern int utc_media_webrtc_start_n2(void);
extern int utc_media_webrtc_stop_p(void);
extern int utc_media_webrtc_stop_n1(void);
extern int utc_media_webrtc_stop_n2(void);
extern int utc_media_webrtc_get_state_p(void);
extern int utc_media_webrtc_get_state_n1(void);
extern int utc_media_webrtc_get_state_n2(void);
extern int utc_media_webrtc_add_media_source_p(void);
extern int utc_media_webrtc_add_media_source_n1(void);
extern int utc_media_webrtc_add_media_source_n2(void);
extern int utc_media_webrtc_remove_media_source_p(void);
extern int utc_media_webrtc_remove_media_source_n1(void);
extern int utc_media_webrtc_remove_media_source_n2(void);
extern int utc_media_webrtc_media_source_set_transceiver_direction_p(void);
extern int utc_media_webrtc_media_source_set_transceiver_direction_n(void);
extern int utc_media_webrtc_media_source_get_transceiver_direction_p(void);
extern int utc_media_webrtc_media_source_get_transceiver_direction_n(void);
extern int utc_media_webrtc_media_source_set_pause_p(void);
extern int utc_media_webrtc_media_source_set_pause_n(void);
extern int utc_media_webrtc_media_source_get_pause_p(void);
extern int utc_media_webrtc_media_source_get_pause_n(void);
extern int utc_media_webrtc_media_source_set_mute_p(void);
extern int utc_media_webrtc_media_source_set_mute_n(void);
extern int utc_media_webrtc_media_source_get_mute_p(void);
extern int utc_media_webrtc_media_source_get_mute_n(void);
extern int utc_media_webrtc_media_source_set_video_resolution_p(void);
extern int utc_media_webrtc_media_source_set_video_resolution_n1(void);
extern int utc_media_webrtc_media_source_set_video_resolution_n2(void);
extern int utc_media_webrtc_media_source_get_video_resolution_p(void);
extern int utc_media_webrtc_media_source_get_video_resolution_n1(void);
extern int utc_media_webrtc_media_source_get_video_resolution_n2(void);
extern int utc_media_webrtc_media_source_set_video_framerate_p(void);
extern int utc_media_webrtc_media_source_set_video_framerate_n1(void);
extern int utc_media_webrtc_media_source_set_video_framerate_n2(void);
extern int utc_media_webrtc_media_source_get_video_framerate_p(void);
extern int utc_media_webrtc_media_source_get_video_framerate_n1(void);
extern int utc_media_webrtc_media_source_get_video_framerate_n2(void);
extern int utc_media_webrtc_mic_source_set_sound_stream_info_p(void);
extern int utc_media_webrtc_mic_source_set_sound_stream_info_n1(void);
extern int utc_media_webrtc_mic_source_set_sound_stream_info_n2(void);
extern int utc_media_webrtc_media_packet_source_set_format_p(void);
extern int utc_media_webrtc_media_packet_source_set_format_n(void);
extern int utc_media_webrtc_media_packet_source_push_packet_p(void);
extern int utc_media_webrtc_media_packet_source_push_packet_n1(void);
extern int utc_media_webrtc_media_packet_source_push_packet_n2(void);
extern int utc_media_webrtc_media_packet_source_push_packet_n3(void);
extern int utc_media_webrtc_file_source_set_path_p(void);
extern int utc_media_webrtc_file_source_set_path_n1(void);
extern int utc_media_webrtc_file_source_set_path_n2(void);
extern int utc_media_webrtc_file_source_set_looping_p(void);
extern int utc_media_webrtc_file_source_set_looping_n(void);
extern int utc_media_webrtc_file_source_get_looping_p(void);
extern int utc_media_webrtc_file_source_get_looping_n1(void);
extern int utc_media_webrtc_file_source_get_looping_n2(void);
extern int utc_media_webrtc_media_source_set_audio_loopback_p(void);
extern int utc_media_webrtc_media_source_set_audio_loopback_n1(void);
extern int utc_media_webrtc_media_source_set_audio_loopback_n2(void);
extern int utc_media_webrtc_media_source_set_audio_loopback_n3(void);
extern int utc_media_webrtc_media_source_unset_audio_loopback_p(void);
extern int utc_media_webrtc_media_source_unset_audio_loopback_n1(void);
extern int utc_media_webrtc_media_source_unset_audio_loopback_n2(void);
extern int utc_media_webrtc_media_source_set_video_loopback_p(void);
extern int utc_media_webrtc_media_source_set_video_loopback_n1(void);
extern int utc_media_webrtc_media_source_set_video_loopback_n2(void);
extern int utc_media_webrtc_media_source_set_video_loopback_n3(void);
extern int utc_media_webrtc_media_source_unset_video_loopback_p(void);
extern int utc_media_webrtc_media_source_unset_video_loopback_n1(void);
extern int utc_media_webrtc_media_source_unset_video_loopback_n2(void);
extern int utc_media_webrtc_set_sound_stream_info_n(void);
extern int utc_media_webrtc_set_display_n(void);
extern int utc_media_webrtc_set_display_mode_p(void);
extern int utc_media_webrtc_set_display_mode_n(void);
extern int utc_media_webrtc_get_display_mode_p(void);
extern int utc_media_webrtc_get_display_mode_n(void);
extern int utc_media_webrtc_set_display_visible_p(void);
extern int utc_media_webrtc_set_display_visible_n(void);
extern int utc_media_webrtc_get_display_visible_p(void);
extern int utc_media_webrtc_get_display_visible_n(void);
extern int utc_media_webrtc_set_stun_server_p(void);
extern int utc_media_webrtc_set_stun_server_n1(void);
extern int utc_media_webrtc_set_stun_server_n2(void);
extern int utc_media_webrtc_get_stun_server_p(void);
extern int utc_media_webrtc_get_stun_server_n(void);
extern int utc_media_webrtc_add_turn_server_p(void);
extern int utc_media_webrtc_add_turn_server_n1(void);
extern int utc_media_webrtc_add_turn_server_n2(void);
extern int utc_media_webrtc_create_offer_p(void);
extern int utc_media_webrtc_create_offer_n1(void);
extern int utc_media_webrtc_create_offer_n2(void);
extern int utc_media_webrtc_create_answer_p(void);
extern int utc_media_webrtc_create_answer_n1(void);
extern int utc_media_webrtc_create_answer_n2(void);
extern int utc_media_webrtc_create_answer_n3(void);
extern int utc_media_webrtc_create_offer_async_p(void);
extern int utc_media_webrtc_create_offer_async_n1(void);
extern int utc_media_webrtc_create_offer_async_n2(void);
extern int utc_media_webrtc_create_answer_async_p(void);
extern int utc_media_webrtc_create_answer_async_n1(void);
extern int utc_media_webrtc_create_answer_async_n2(void);
extern int utc_media_webrtc_create_answer_async_n3(void);
extern int utc_media_webrtc_set_local_description_p(void);
extern int utc_media_webrtc_set_local_description_n(void);
extern int utc_media_webrtc_set_remote_description_p(void);
extern int utc_media_webrtc_set_remote_description_n(void);
extern int utc_media_webrtc_add_ice_candidate_p(void);
extern int utc_media_webrtc_add_ice_candidate_n1(void);
extern int utc_media_webrtc_add_ice_candidate_n2(void);
extern int utc_media_webrtc_foreach_turn_server_p(void);
extern int utc_media_webrtc_foreach_turn_server_n(void);
extern int utc_media_webrtc_set_bundle_policy_p(void);
extern int utc_media_webrtc_set_bundle_policy_n(void);
extern int utc_media_webrtc_get_bundle_policy_p(void);
extern int utc_media_webrtc_get_bundle_policy_n(void);
extern int utc_media_webrtc_set_ice_transport_policy_p(void);
extern int utc_media_webrtc_set_ice_transport_policy_n(void);
extern int utc_media_webrtc_get_ice_transport_policy_p(void);
extern int utc_media_webrtc_get_ice_transport_policy_n(void);
extern int utc_media_webrtc_get_peer_connection_state_p(void);
extern int utc_media_webrtc_get_peer_connection_state_n(void);
extern int utc_media_webrtc_get_signaling_state_p(void);
extern int utc_media_webrtc_get_signaling_state_n(void);
extern int utc_media_webrtc_get_ice_gathering_state_p(void);
extern int utc_media_webrtc_get_ice_gathering_state_n(void);
extern int utc_media_webrtc_get_ice_connection_state_p(void);
extern int utc_media_webrtc_get_ice_connection_state_n(void);
extern int utc_media_webrtc_create_data_channel_p(void);
extern int utc_media_webrtc_create_data_channel_n(void);
extern int utc_media_webrtc_destroy_data_channel_p(void);
extern int utc_media_webrtc_destroy_data_channel_n(void);
extern int utc_media_webrtc_data_channel_get_label_p(void);
extern int utc_media_webrtc_data_channel_get_label_n(void);
extern int utc_media_webrtc_data_channel_send_string_p(void);
extern int utc_media_webrtc_data_channel_send_string_n(void);
extern int utc_media_webrtc_data_channel_send_bytes_p(void);
extern int utc_media_webrtc_data_channel_send_bytes_n(void);
extern int utc_media_webrtc_get_data_p(void);
extern int utc_media_webrtc_get_data_n(void);
extern int utc_media_webrtc_data_channel_get_buffered_amount_p(void);
extern int utc_media_webrtc_data_channel_get_buffered_amount_n(void);
extern int utc_media_webrtc_data_channel_set_buffered_amount_low_cb_p(void);
extern int utc_media_webrtc_data_channel_set_buffered_amount_low_cb_n(void);
extern int utc_media_webrtc_data_channel_get_buffered_amount_low_threshold_p(void);
extern int utc_media_webrtc_data_channel_get_buffered_amount_low_threshold_n(void);
extern int utc_media_webrtc_data_channel_unset_buffered_amount_low_cb_p(void);
extern int utc_media_webrtc_data_channel_unset_buffered_amount_low_cb_n(void);
extern int utc_media_webrtc_set_state_changed_cb_p(void);
extern int utc_media_webrtc_set_state_changed_cb_n(void);
extern int utc_media_webrtc_unset_state_changed_cb_p(void);
extern int utc_media_webrtc_unset_state_changed_cb_n(void);
extern int utc_media_webrtc_set_error_cb_p(void);
extern int utc_media_webrtc_set_error_cb_n(void);
extern int utc_media_webrtc_unset_error_cb_p(void);
extern int utc_media_webrtc_unset_error_cb_n(void);
extern int utc_media_webrtc_set_ice_candidate_cb_p(void);
extern int utc_media_webrtc_set_ice_candidate_cb_n(void);
extern int utc_media_webrtc_unset_ice_candidate_cb_p(void);
extern int utc_media_webrtc_unset_ice_candidate_cb_n(void);
extern int utc_media_webrtc_set_negotiation_needed_cb_p(void);
extern int utc_media_webrtc_set_negotiation_needed_cb_n(void);
extern int utc_media_webrtc_unset_negotiation_needed_cb_p(void);
extern int utc_media_webrtc_unset_negotiation_needed_cb_n(void);
extern int utc_media_webrtc_set_peer_connection_state_change_cb_p(void);
extern int utc_media_webrtc_set_peer_connection_state_change_cb_n(void);
extern int utc_media_webrtc_unset_peer_connection_state_change_cb_p(void);
extern int utc_media_webrtc_unset_peer_connection_state_change_cb_n(void);
extern int utc_media_webrtc_set_signaling_state_change_cb_p(void);
extern int utc_media_webrtc_set_signaling_state_change_cb_n(void);
extern int utc_media_webrtc_unset_signaling_state_change_cb_p(void);
extern int utc_media_webrtc_unset_signaling_state_change_cb_n(void);
extern int utc_media_webrtc_set_ice_gathering_state_change_cb_p(void);
extern int utc_media_webrtc_set_ice_gathering_state_change_cb_n(void);
extern int utc_media_webrtc_unset_ice_gathering_state_change_cb_p(void);
extern int utc_media_webrtc_unset_ice_gathering_state_change_cb_n(void);
extern int utc_media_webrtc_set_ice_connection_state_change_cb_p(void);
extern int utc_media_webrtc_set_ice_connection_state_change_cb_n(void);
extern int utc_media_webrtc_unset_ice_connection_state_change_cb_p(void);
extern int utc_media_webrtc_unset_ice_connection_state_change_cb_n(void);
extern int utc_media_webrtc_set_track_added_cb_p(void);
extern int utc_media_webrtc_set_track_added_cb_n(void);
extern int utc_media_webrtc_unset_track_added_cb_p(void);
extern int utc_media_webrtc_unset_track_added_cb_n(void);
extern int utc_media_webrtc_set_encoded_audio_frame_cb_p(void);
extern int utc_media_webrtc_set_encoded_audio_frame_cb_n(void);
extern int utc_media_webrtc_unset_encoded_audio_frame_cb_p(void);
extern int utc_media_webrtc_unset_encoded_audio_frame_cb_n(void);
extern int utc_media_webrtc_set_encoded_video_frame_cb_p(void);
extern int utc_media_webrtc_set_encoded_video_frame_cb_n(void);
extern int utc_media_webrtc_unset_encoded_video_frame_cb_p(void);
extern int utc_media_webrtc_unset_encoded_video_frame_cb_n(void);
extern int utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_p(void);
extern int utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_n1(void);
extern int utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_n2(void);
extern int utc_media_webrtc_media_packet_source_unset_buffer_state_changed_cb_p(void);
extern int utc_media_webrtc_media_packet_source_unset_buffer_state_changed_cb_n(void);
extern int utc_media_webrtc_set_data_channel_cb_p(void);
extern int utc_media_webrtc_set_data_channel_cb_n(void);
extern int utc_media_webrtc_unset_data_channel_cb_p(void);
extern int utc_media_webrtc_unset_data_channel_cb_n(void);
extern int utc_media_webrtc_data_channel_set_open_cb_p(void);
extern int utc_media_webrtc_data_channel_set_open_cb_n(void);
extern int utc_media_webrtc_data_channel_unset_open_cb_p(void);
extern int utc_media_webrtc_data_channel_unset_open_cb_n(void);
extern int utc_media_webrtc_data_channel_set_message_cb_p(void);
extern int utc_media_webrtc_data_channel_set_message_cb_n(void);
extern int utc_media_webrtc_data_channel_unset_message_cb_p(void);
extern int utc_media_webrtc_data_channel_unset_message_cb_n(void);
extern int utc_media_webrtc_data_channel_set_error_cb_p(void);
extern int utc_media_webrtc_data_channel_set_error_cb_n(void);
extern int utc_media_webrtc_data_channel_unset_error_cb_p(void);
extern int utc_media_webrtc_data_channel_unset_error_cb_n(void);
extern int utc_media_webrtc_data_channel_set_close_cb_p(void);
extern int utc_media_webrtc_data_channel_set_close_cb_n(void);
extern int utc_media_webrtc_data_channel_unset_close_cb_p(void);
extern int utc_media_webrtc_data_channel_unset_close_cb_n(void);
extern int utc_media_webrtc_foreach_stats_p(void);
extern int utc_media_webrtc_foreach_stats_n(void);

testcase tc_array[] = {
	{"utc_media_webrtc_create_p",utc_media_webrtc_create_p,NULL,NULL},
	{"utc_media_webrtc_create_n",utc_media_webrtc_create_n,NULL,NULL},
	{"utc_media_webrtc_destroy_p",utc_media_webrtc_destroy_p,NULL,NULL},
	{"utc_media_webrtc_destroy_n",utc_media_webrtc_destroy_n,NULL,NULL},
	{"utc_media_webrtc_start_p",utc_media_webrtc_start_p,NULL,NULL},
	{"utc_media_webrtc_start_n1",utc_media_webrtc_start_n1,NULL,NULL},
	{"utc_media_webrtc_start_n2",utc_media_webrtc_start_n2,NULL,NULL},
	{"utc_media_webrtc_stop_p",utc_media_webrtc_stop_p,NULL,NULL},
	{"utc_media_webrtc_stop_n1",utc_media_webrtc_stop_n1,NULL,NULL},
	{"utc_media_webrtc_stop_n2",utc_media_webrtc_stop_n2,NULL,NULL},
	{"utc_media_webrtc_get_state_p",utc_media_webrtc_get_state_p,NULL,NULL},
	{"utc_media_webrtc_get_state_n1",utc_media_webrtc_get_state_n1,NULL,NULL},
	{"utc_media_webrtc_get_state_n2",utc_media_webrtc_get_state_n2,NULL,NULL},
	{"utc_media_webrtc_add_media_source_p",utc_media_webrtc_add_media_source_p,NULL,NULL},
	{"utc_media_webrtc_add_media_source_n1",utc_media_webrtc_add_media_source_n1,NULL,NULL},
	{"utc_media_webrtc_add_media_source_n2",utc_media_webrtc_add_media_source_n2,NULL,NULL},
	{"utc_media_webrtc_remove_media_source_p",utc_media_webrtc_remove_media_source_p,NULL,NULL},
	{"utc_media_webrtc_remove_media_source_n1",utc_media_webrtc_remove_media_source_n1,NULL,NULL},
	{"utc_media_webrtc_remove_media_source_n2",utc_media_webrtc_remove_media_source_n2,NULL,NULL},
	{"utc_media_webrtc_media_source_set_transceiver_direction_p",utc_media_webrtc_media_source_set_transceiver_direction_p,NULL,NULL},
	{"utc_media_webrtc_media_source_set_transceiver_direction_n",utc_media_webrtc_media_source_set_transceiver_direction_n,NULL,NULL},
	{"utc_media_webrtc_media_source_get_transceiver_direction_p",utc_media_webrtc_media_source_get_transceiver_direction_p,NULL,NULL},
	{"utc_media_webrtc_media_source_get_transceiver_direction_n",utc_media_webrtc_media_source_get_transceiver_direction_n,NULL,NULL},
	{"utc_media_webrtc_media_source_set_pause_p",utc_media_webrtc_media_source_set_pause_p,NULL,NULL},
	{"utc_media_webrtc_media_source_set_pause_n",utc_media_webrtc_media_source_set_pause_n,NULL,NULL},
	{"utc_media_webrtc_media_source_get_pause_p",utc_media_webrtc_media_source_get_pause_p,NULL,NULL},
	{"utc_media_webrtc_media_source_get_pause_n",utc_media_webrtc_media_source_get_pause_n,NULL,NULL},
	{"utc_media_webrtc_media_source_set_mute_p",utc_media_webrtc_media_source_set_mute_p,NULL,NULL},
	{"utc_media_webrtc_media_source_set_mute_n",utc_media_webrtc_media_source_set_mute_n,NULL,NULL},
	{"utc_media_webrtc_media_source_get_mute_p",utc_media_webrtc_media_source_get_mute_p,NULL,NULL},
	{"utc_media_webrtc_media_source_get_mute_n",utc_media_webrtc_media_source_get_mute_n,NULL,NULL},
	{"utc_media_webrtc_media_source_set_video_resolution_p",utc_media_webrtc_media_source_set_video_resolution_p,NULL,NULL},
	{"utc_media_webrtc_media_source_set_video_resolution_n1",utc_media_webrtc_media_source_set_video_resolution_n1,NULL,NULL},
	{"utc_media_webrtc_media_source_set_video_resolution_n2",utc_media_webrtc_media_source_set_video_resolution_n2,NULL,NULL},
	{"utc_media_webrtc_media_source_get_video_resolution_p",utc_media_webrtc_media_source_get_video_resolution_p,NULL,NULL},
	{"utc_media_webrtc_media_source_get_video_resolution_n1",utc_media_webrtc_media_source_get_video_resolution_n1,NULL,NULL},
	{"utc_media_webrtc_media_source_get_video_resolution_n2",utc_media_webrtc_media_source_get_video_resolution_n2,NULL,NULL},
	{"utc_media_webrtc_media_source_set_video_framerate_p",utc_media_webrtc_media_source_set_video_framerate_p,NULL,NULL},
	{"utc_media_webrtc_media_source_set_video_framerate_n1",utc_media_webrtc_media_source_set_video_framerate_n1,NULL,NULL},
	{"utc_media_webrtc_media_source_set_video_framerate_n2",utc_media_webrtc_media_source_set_video_framerate_n2,NULL,NULL},
	{"utc_media_webrtc_media_source_get_video_framerate_p",utc_media_webrtc_media_source_get_video_framerate_p,NULL,NULL},
	{"utc_media_webrtc_media_source_get_video_framerate_n1",utc_media_webrtc_media_source_get_video_framerate_n1,NULL,NULL},
	{"utc_media_webrtc_media_source_get_video_framerate_n2",utc_media_webrtc_media_source_get_video_framerate_n2,NULL,NULL},
	{"utc_media_webrtc_mic_source_set_sound_stream_info_p",utc_media_webrtc_mic_source_set_sound_stream_info_p,NULL,NULL},
	{"utc_media_webrtc_mic_source_set_sound_stream_info_n1",utc_media_webrtc_mic_source_set_sound_stream_info_n1,NULL,NULL},
	{"utc_media_webrtc_mic_source_set_sound_stream_info_n2",utc_media_webrtc_mic_source_set_sound_stream_info_n2,NULL,NULL},
	{"utc_media_webrtc_media_packet_source_set_format_p",utc_media_webrtc_media_packet_source_set_format_p,NULL,NULL},
	{"utc_media_webrtc_media_packet_source_set_format_n",utc_media_webrtc_media_packet_source_set_format_n,NULL,NULL},
	{"utc_media_webrtc_media_packet_source_push_packet_p",utc_media_webrtc_media_packet_source_push_packet_p,NULL,NULL},
	{"utc_media_webrtc_media_packet_source_push_packet_n1",utc_media_webrtc_media_packet_source_push_packet_n1,NULL,NULL},
	{"utc_media_webrtc_media_packet_source_push_packet_n2",utc_media_webrtc_media_packet_source_push_packet_n2,NULL,NULL},
	{"utc_media_webrtc_media_packet_source_push_packet_n3",utc_media_webrtc_media_packet_source_push_packet_n3,NULL,NULL},
	{"utc_media_webrtc_file_source_set_path_p",utc_media_webrtc_file_source_set_path_p,NULL,NULL},
	{"utc_media_webrtc_file_source_set_path_n1",utc_media_webrtc_file_source_set_path_n1,NULL,NULL},
	{"utc_media_webrtc_file_source_set_path_n2",utc_media_webrtc_file_source_set_path_n2,NULL,NULL},
	{"utc_media_webrtc_file_source_set_looping_p",utc_media_webrtc_file_source_set_looping_p,NULL,NULL},
	{"utc_media_webrtc_file_source_set_looping_n",utc_media_webrtc_file_source_set_looping_n,NULL,NULL},
	{"utc_media_webrtc_file_source_get_looping_p",utc_media_webrtc_file_source_get_looping_p,NULL,NULL},
	{"utc_media_webrtc_file_source_get_looping_n1",utc_media_webrtc_file_source_get_looping_n1,NULL,NULL},
	{"utc_media_webrtc_file_source_get_looping_n2",utc_media_webrtc_file_source_get_looping_n2,NULL,NULL},
	{"utc_media_webrtc_media_source_set_audio_loopback_p",utc_media_webrtc_media_source_set_audio_loopback_p,NULL,NULL},
	{"utc_media_webrtc_media_source_set_audio_loopback_n1",utc_media_webrtc_media_source_set_audio_loopback_n1,NULL,NULL},
	{"utc_media_webrtc_media_source_set_audio_loopback_n2",utc_media_webrtc_media_source_set_audio_loopback_n2,NULL,NULL},
	{"utc_media_webrtc_media_source_set_audio_loopback_n3",utc_media_webrtc_media_source_set_audio_loopback_n3,NULL,NULL},
	{"utc_media_webrtc_media_source_unset_audio_loopback_p",utc_media_webrtc_media_source_unset_audio_loopback_p,NULL,NULL},
	{"utc_media_webrtc_media_source_unset_audio_loopback_n1",utc_media_webrtc_media_source_unset_audio_loopback_n1,NULL,NULL},
	{"utc_media_webrtc_media_source_unset_audio_loopback_n2",utc_media_webrtc_media_source_unset_audio_loopback_n2,NULL,NULL},
	{"utc_media_webrtc_media_source_set_video_loopback_p",utc_media_webrtc_media_source_set_video_loopback_p,utc_media_webrtc_startup_create_win,utc_media_webrtc_cleanup_destroy_win},
	{"utc_media_webrtc_media_source_set_video_loopback_n1",utc_media_webrtc_media_source_set_video_loopback_n1,NULL,NULL},
	{"utc_media_webrtc_media_source_set_video_loopback_n2",utc_media_webrtc_media_source_set_video_loopback_n2,NULL,NULL},
	{"utc_media_webrtc_media_source_set_video_loopback_n3",utc_media_webrtc_media_source_set_video_loopback_n3,NULL,NULL},
	{"utc_media_webrtc_media_source_unset_video_loopback_p",utc_media_webrtc_media_source_unset_video_loopback_p,utc_media_webrtc_startup_create_win,utc_media_webrtc_cleanup_destroy_win},
	{"utc_media_webrtc_media_source_unset_video_loopback_n1",utc_media_webrtc_media_source_unset_video_loopback_n1,NULL,NULL},
	{"utc_media_webrtc_media_source_unset_video_loopback_n2",utc_media_webrtc_media_source_unset_video_loopback_n2,NULL,NULL},
	{"utc_media_webrtc_set_sound_stream_info_n",utc_media_webrtc_set_sound_stream_info_n,NULL,NULL},
	{"utc_media_webrtc_set_display_n",utc_media_webrtc_set_display_n,NULL,NULL},
	{"utc_media_webrtc_set_display_mode_p",utc_media_webrtc_set_display_mode_p,utc_media_webrtc_startup_create_win,utc_media_webrtc_cleanup_destroy_win},
	{"utc_media_webrtc_set_display_mode_n",utc_media_webrtc_set_display_mode_n,NULL,NULL},
	{"utc_media_webrtc_get_display_mode_p",utc_media_webrtc_get_display_mode_p,utc_media_webrtc_startup_create_win,utc_media_webrtc_cleanup_destroy_win},
	{"utc_media_webrtc_get_display_mode_n",utc_media_webrtc_get_display_mode_n,NULL,NULL},
	{"utc_media_webrtc_set_display_visible_p",utc_media_webrtc_set_display_visible_p,utc_media_webrtc_startup_create_win,utc_media_webrtc_cleanup_destroy_win},
	{"utc_media_webrtc_set_display_visible_n",utc_media_webrtc_set_display_visible_n,NULL,NULL},
	{"utc_media_webrtc_get_display_visible_p",utc_media_webrtc_get_display_visible_p,utc_media_webrtc_startup_create_win,utc_media_webrtc_cleanup_destroy_win},
	{"utc_media_webrtc_get_display_visible_n",utc_media_webrtc_get_display_visible_n,NULL,NULL},
	{"utc_media_webrtc_set_stun_server_p",utc_media_webrtc_set_stun_server_p,NULL,NULL},
	{"utc_media_webrtc_set_stun_server_n1",utc_media_webrtc_set_stun_server_n1,NULL,NULL},
	{"utc_media_webrtc_set_stun_server_n2",utc_media_webrtc_set_stun_server_n2,NULL,NULL},
	{"utc_media_webrtc_get_stun_server_p",utc_media_webrtc_get_stun_server_p,NULL,NULL},
	{"utc_media_webrtc_get_stun_server_n",utc_media_webrtc_get_stun_server_n,NULL,NULL},
	{"utc_media_webrtc_add_turn_server_p",utc_media_webrtc_add_turn_server_p,NULL,NULL},
	{"utc_media_webrtc_add_turn_server_n1",utc_media_webrtc_add_turn_server_n1,NULL,NULL},
	{"utc_media_webrtc_add_turn_server_n2",utc_media_webrtc_add_turn_server_n2,NULL,NULL},
	{"utc_media_webrtc_foreach_turn_server_p",utc_media_webrtc_foreach_turn_server_p,NULL,NULL},
	{"utc_media_webrtc_foreach_turn_server_n",utc_media_webrtc_foreach_turn_server_n,NULL,NULL},
	{"utc_media_webrtc_set_bundle_policy_p",utc_media_webrtc_set_bundle_policy_p,NULL,NULL},
	{"utc_media_webrtc_set_bundle_policy_n",utc_media_webrtc_set_bundle_policy_n,NULL,NULL},
	{"utc_media_webrtc_get_bundle_policy_p",utc_media_webrtc_get_bundle_policy_p,NULL,NULL},
	{"utc_media_webrtc_get_bundle_policy_n",utc_media_webrtc_get_bundle_policy_n,NULL,NULL},
	{"utc_media_webrtc_set_ice_transport_policy_p",utc_media_webrtc_set_ice_transport_policy_p,NULL,NULL},
	{"utc_media_webrtc_set_ice_transport_policy_n",utc_media_webrtc_set_ice_transport_policy_n,NULL,NULL},
	{"utc_media_webrtc_get_ice_transport_policy_p",utc_media_webrtc_get_ice_transport_policy_p,NULL,NULL},
	{"utc_media_webrtc_get_ice_transport_policy_n",utc_media_webrtc_get_ice_transport_policy_n,NULL,NULL},
	{"utc_media_webrtc_create_offer_p",utc_media_webrtc_create_offer_p,NULL,NULL},
	{"utc_media_webrtc_create_offer_n1",utc_media_webrtc_create_offer_n1,NULL,NULL},
	{"utc_media_webrtc_create_offer_n2",utc_media_webrtc_create_offer_n2,NULL,NULL},
	{"utc_media_webrtc_create_answer_p",utc_media_webrtc_create_answer_p,NULL,NULL},
	{"utc_media_webrtc_create_answer_n1",utc_media_webrtc_create_answer_n1,NULL,NULL},
	{"utc_media_webrtc_create_answer_n2",utc_media_webrtc_create_answer_n2,NULL,NULL},
	{"utc_media_webrtc_create_answer_n3",utc_media_webrtc_create_answer_n3,NULL,NULL},
	{"utc_media_webrtc_create_offer_async_p",utc_media_webrtc_create_offer_async_p,NULL,NULL},
	{"utc_media_webrtc_create_offer_async_n1",utc_media_webrtc_create_offer_async_n1,NULL,NULL},
	{"utc_media_webrtc_create_offer_async_n2",utc_media_webrtc_create_offer_async_n2,NULL,NULL},
	{"utc_media_webrtc_create_answer_async_p",utc_media_webrtc_create_answer_async_p,NULL,NULL},
	{"utc_media_webrtc_create_answer_async_n1",utc_media_webrtc_create_answer_async_n1,NULL,NULL},
	{"utc_media_webrtc_create_answer_async_n2",utc_media_webrtc_create_answer_async_n2,NULL,NULL},
	{"utc_media_webrtc_create_answer_async_n3",utc_media_webrtc_create_answer_async_n3,NULL,NULL},
	{"utc_media_webrtc_set_local_description_p",utc_media_webrtc_set_local_description_p,NULL,NULL},
	{"utc_media_webrtc_set_local_description_n",utc_media_webrtc_set_local_description_n,NULL,NULL},
	{"utc_media_webrtc_set_remote_description_p",utc_media_webrtc_set_remote_description_p,NULL,NULL},
	{"utc_media_webrtc_set_remote_description_n",utc_media_webrtc_set_remote_description_n,NULL,NULL},
	{"utc_media_webrtc_add_ice_candidate_p",utc_media_webrtc_add_ice_candidate_p,NULL,NULL},
	{"utc_media_webrtc_add_ice_candidate_n1",utc_media_webrtc_add_ice_candidate_n1,NULL,NULL},
	{"utc_media_webrtc_add_ice_candidate_n2",utc_media_webrtc_add_ice_candidate_n2,NULL,NULL},
	{"utc_media_webrtc_get_peer_connection_state_p",utc_media_webrtc_get_peer_connection_state_p,NULL,NULL},
	{"utc_media_webrtc_get_peer_connection_state_n",utc_media_webrtc_get_peer_connection_state_n,NULL,NULL},
	{"utc_media_webrtc_get_signaling_state_p",utc_media_webrtc_get_signaling_state_p,NULL,NULL},
	{"utc_media_webrtc_get_signaling_state_n",utc_media_webrtc_get_signaling_state_n,NULL,NULL},
	{"utc_media_webrtc_get_ice_gathering_state_p",utc_media_webrtc_get_ice_gathering_state_p,NULL,NULL},
	{"utc_media_webrtc_get_ice_gathering_state_n",utc_media_webrtc_get_ice_gathering_state_n,NULL,NULL},
	{"utc_media_webrtc_get_ice_connection_state_p",utc_media_webrtc_get_ice_connection_state_p,NULL,NULL},
	{"utc_media_webrtc_get_ice_connection_state_n",utc_media_webrtc_get_ice_connection_state_n,NULL,NULL},
	{"utc_media_webrtc_create_data_channel_p",utc_media_webrtc_create_data_channel_p,NULL,NULL},
	{"utc_media_webrtc_create_data_channel_n",utc_media_webrtc_create_data_channel_n,NULL,NULL},
	{"utc_media_webrtc_destroy_data_channel_p",utc_media_webrtc_destroy_data_channel_p,NULL,NULL},
	{"utc_media_webrtc_destroy_data_channel_n",utc_media_webrtc_destroy_data_channel_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_get_label_p",utc_media_webrtc_data_channel_get_label_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_get_label_n",utc_media_webrtc_data_channel_get_label_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_send_string_p",utc_media_webrtc_data_channel_send_string_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_send_string_n",utc_media_webrtc_data_channel_send_string_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_send_bytes_p",utc_media_webrtc_data_channel_send_bytes_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_send_bytes_n",utc_media_webrtc_data_channel_send_bytes_n,NULL,NULL},
	{"utc_media_webrtc_get_data_p",utc_media_webrtc_get_data_p,NULL,NULL},
	{"utc_media_webrtc_get_data_n",utc_media_webrtc_get_data_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_get_buffered_amount_p",utc_media_webrtc_data_channel_get_buffered_amount_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_get_buffered_amount_n",utc_media_webrtc_data_channel_get_buffered_amount_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_set_buffered_amount_low_cb_p",utc_media_webrtc_data_channel_set_buffered_amount_low_cb_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_set_buffered_amount_low_cb_n",utc_media_webrtc_data_channel_set_buffered_amount_low_cb_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_get_buffered_amount_low_threshold_p",utc_media_webrtc_data_channel_get_buffered_amount_low_threshold_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_get_buffered_amount_low_threshold_n",utc_media_webrtc_data_channel_get_buffered_amount_low_threshold_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_unset_buffered_amount_low_cb_p",utc_media_webrtc_data_channel_unset_buffered_amount_low_cb_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_unset_buffered_amount_low_cb_n",utc_media_webrtc_data_channel_unset_buffered_amount_low_cb_n,NULL,NULL},
	{"utc_media_webrtc_set_state_changed_cb_p",utc_media_webrtc_set_state_changed_cb_p,NULL,NULL},
	{"utc_media_webrtc_set_state_changed_cb_n",utc_media_webrtc_set_state_changed_cb_n,NULL,NULL},
	{"utc_media_webrtc_unset_state_changed_cb_p",utc_media_webrtc_unset_state_changed_cb_p,NULL,NULL},
	{"utc_media_webrtc_unset_state_changed_cb_n",utc_media_webrtc_unset_state_changed_cb_n,NULL,NULL},
	{"utc_media_webrtc_set_error_cb_p",utc_media_webrtc_set_error_cb_p,NULL,NULL},
	{"utc_media_webrtc_set_error_cb_n",utc_media_webrtc_set_error_cb_n,NULL,NULL},
	{"utc_media_webrtc_unset_error_cb_p",utc_media_webrtc_unset_error_cb_p,NULL,NULL},
	{"utc_media_webrtc_unset_error_cb_n",utc_media_webrtc_unset_error_cb_n,NULL,NULL},
	{"utc_media_webrtc_set_ice_candidate_cb_p",utc_media_webrtc_set_ice_candidate_cb_p,NULL,NULL},
	{"utc_media_webrtc_set_ice_candidate_cb_n",utc_media_webrtc_set_ice_candidate_cb_n,NULL,NULL},
	{"utc_media_webrtc_unset_ice_candidate_cb_p",utc_media_webrtc_unset_ice_candidate_cb_p,NULL,NULL},
	{"utc_media_webrtc_unset_ice_candidate_cb_n",utc_media_webrtc_unset_ice_candidate_cb_n,NULL,NULL},
	{"utc_media_webrtc_set_negotiation_needed_cb_p",utc_media_webrtc_set_negotiation_needed_cb_p,NULL,NULL},
	{"utc_media_webrtc_set_negotiation_needed_cb_n",utc_media_webrtc_set_negotiation_needed_cb_n,NULL,NULL},
	{"utc_media_webrtc_unset_negotiation_needed_cb_p",utc_media_webrtc_unset_negotiation_needed_cb_p,NULL,NULL},
	{"utc_media_webrtc_unset_negotiation_needed_cb_n",utc_media_webrtc_unset_negotiation_needed_cb_n,NULL,NULL},
	{"utc_media_webrtc_set_peer_connection_state_change_cb_p",utc_media_webrtc_set_peer_connection_state_change_cb_p,NULL,NULL},
	{"utc_media_webrtc_set_peer_connection_state_change_cb_n",utc_media_webrtc_set_peer_connection_state_change_cb_n,NULL,NULL},
	{"utc_media_webrtc_unset_peer_connection_state_change_cb_p",utc_media_webrtc_unset_peer_connection_state_change_cb_p,NULL,NULL},
	{"utc_media_webrtc_unset_peer_connection_state_change_cb_n",utc_media_webrtc_unset_peer_connection_state_change_cb_n,NULL,NULL},
	{"utc_media_webrtc_set_signaling_state_change_cb_p",utc_media_webrtc_set_signaling_state_change_cb_p,NULL,NULL},
	{"utc_media_webrtc_set_signaling_state_change_cb_n",utc_media_webrtc_set_signaling_state_change_cb_n,NULL,NULL},
	{"utc_media_webrtc_unset_signaling_state_change_cb_p",utc_media_webrtc_unset_signaling_state_change_cb_p,NULL,NULL},
	{"utc_media_webrtc_unset_signaling_state_change_cb_n",utc_media_webrtc_unset_signaling_state_change_cb_n,NULL,NULL},
	{"utc_media_webrtc_set_ice_gathering_state_change_cb_p",utc_media_webrtc_set_ice_gathering_state_change_cb_p,NULL,NULL},
	{"utc_media_webrtc_set_ice_gathering_state_change_cb_n",utc_media_webrtc_set_ice_gathering_state_change_cb_n,NULL,NULL},
	{"utc_media_webrtc_unset_ice_gathering_state_change_cb_p",utc_media_webrtc_unset_ice_gathering_state_change_cb_p,NULL,NULL},
	{"utc_media_webrtc_unset_ice_gathering_state_change_cb_n",utc_media_webrtc_unset_ice_gathering_state_change_cb_n,NULL,NULL},
	{"utc_media_webrtc_set_ice_connection_state_change_cb_p",utc_media_webrtc_set_ice_connection_state_change_cb_p,NULL,NULL},
	{"utc_media_webrtc_set_ice_connection_state_change_cb_n",utc_media_webrtc_set_ice_connection_state_change_cb_n,NULL,NULL},
	{"utc_media_webrtc_unset_ice_connection_state_change_cb_p",utc_media_webrtc_unset_ice_connection_state_change_cb_p,NULL,NULL},
	{"utc_media_webrtc_unset_ice_connection_state_change_cb_n",utc_media_webrtc_unset_ice_connection_state_change_cb_n,NULL,NULL},
	{"utc_media_webrtc_set_track_added_cb_p",utc_media_webrtc_set_track_added_cb_p,NULL,NULL},
	{"utc_media_webrtc_set_track_added_cb_n",utc_media_webrtc_set_track_added_cb_n,NULL,NULL},
	{"utc_media_webrtc_unset_track_added_cb_p",utc_media_webrtc_unset_track_added_cb_p,NULL,NULL},
	{"utc_media_webrtc_unset_track_added_cb_n",utc_media_webrtc_unset_track_added_cb_n,NULL,NULL},
	{"utc_media_webrtc_set_encoded_audio_frame_cb_p",utc_media_webrtc_set_encoded_audio_frame_cb_p,NULL,NULL},
	{"utc_media_webrtc_set_encoded_audio_frame_cb_n",utc_media_webrtc_set_encoded_audio_frame_cb_n,NULL,NULL},
	{"utc_media_webrtc_unset_encoded_audio_frame_cb_p",utc_media_webrtc_unset_encoded_audio_frame_cb_p,NULL,NULL},
	{"utc_media_webrtc_unset_encoded_audio_frame_cb_n",utc_media_webrtc_unset_encoded_audio_frame_cb_n,NULL,NULL},
	{"utc_media_webrtc_set_encoded_video_frame_cb_p",utc_media_webrtc_set_encoded_video_frame_cb_p,NULL,NULL},
	{"utc_media_webrtc_set_encoded_video_frame_cb_n",utc_media_webrtc_set_encoded_video_frame_cb_n,NULL,NULL},
	{"utc_media_webrtc_unset_encoded_video_frame_cb_p",utc_media_webrtc_unset_encoded_video_frame_cb_p,NULL,NULL},
	{"utc_media_webrtc_unset_encoded_video_frame_cb_n",utc_media_webrtc_unset_encoded_video_frame_cb_n,NULL,NULL},
	{"utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_p",utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_p,NULL,NULL},
	{"utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_n1",utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_n1,NULL,NULL},
	{"utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_n2",utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_n2,NULL,NULL},
	{"utc_media_webrtc_media_packet_source_unset_buffer_state_changed_cb_p",utc_media_webrtc_media_packet_source_unset_buffer_state_changed_cb_p,NULL,NULL},
	{"utc_media_webrtc_media_packet_source_unset_buffer_state_changed_cb_n",utc_media_webrtc_media_packet_source_unset_buffer_state_changed_cb_n,NULL,NULL},
	{"utc_media_webrtc_set_data_channel_cb_p",utc_media_webrtc_set_data_channel_cb_p,NULL,NULL},
	{"utc_media_webrtc_set_data_channel_cb_n",utc_media_webrtc_set_data_channel_cb_n,NULL,NULL},
	{"utc_media_webrtc_unset_data_channel_cb_p",utc_media_webrtc_unset_data_channel_cb_p,NULL,NULL},
	{"utc_media_webrtc_unset_data_channel_cb_n",utc_media_webrtc_unset_data_channel_cb_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_set_open_cb_p",utc_media_webrtc_data_channel_set_open_cb_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_set_open_cb_n",utc_media_webrtc_data_channel_set_open_cb_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_unset_open_cb_p",utc_media_webrtc_data_channel_unset_open_cb_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_unset_open_cb_n",utc_media_webrtc_data_channel_unset_open_cb_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_set_message_cb_p",utc_media_webrtc_data_channel_set_message_cb_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_set_message_cb_n",utc_media_webrtc_data_channel_set_message_cb_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_unset_message_cb_p",utc_media_webrtc_data_channel_unset_message_cb_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_unset_message_cb_n",utc_media_webrtc_data_channel_unset_message_cb_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_set_error_cb_p",utc_media_webrtc_data_channel_set_error_cb_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_set_error_cb_n",utc_media_webrtc_data_channel_set_error_cb_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_unset_error_cb_p",utc_media_webrtc_data_channel_unset_error_cb_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_unset_error_cb_n",utc_media_webrtc_data_channel_unset_error_cb_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_set_close_cb_p",utc_media_webrtc_data_channel_set_close_cb_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_set_close_cb_n",utc_media_webrtc_data_channel_set_close_cb_n,NULL,NULL},
	{"utc_media_webrtc_data_channel_unset_close_cb_p",utc_media_webrtc_data_channel_unset_close_cb_p,NULL,NULL},
	{"utc_media_webrtc_data_channel_unset_close_cb_n",utc_media_webrtc_data_channel_unset_close_cb_n,NULL,NULL},
	{"utc_media_webrtc_foreach_stats_p",utc_media_webrtc_foreach_stats_p,NULL,NULL},
	{"utc_media_webrtc_foreach_stats_n",utc_media_webrtc_foreach_stats_n,NULL,NULL},
	{NULL, NULL}
};

#endif // __TCT_WEBRTC-NATIVE_H__
