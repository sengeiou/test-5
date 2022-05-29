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
#ifndef __TCT_WEBRTC_NATIVE_H__
#define __TCT_WEBRTC_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_webrtc_startup(void);
extern void ITs_webrtc_cleanup(void);
extern void ITs_webrtc_callback_startup(void);
extern void ITs_webrtc_callback_cleanup(void);

extern int ITc_webrtc_create_destroy_p(void);
extern int ITc_webrtc_start_stop_p(void);
extern int ITc_media_webrtc_get_state_p(void);
extern int ITc_media_webrtc_add_remove_media_source_p(void);
extern int ITc_media_webrtc_get_peer_connection_state_p(void);
extern int ITc_media_webrtc_get_signaling_state_p(void);
extern int ITc_media_webrtc_get_ice_gathering_state_p(void);
extern int ITc_media_webrtc_get_ice_connection_state_p(void);
extern int ITc_media_webrtc_media_source_set_get_transceiver_direction_p(void);
extern int ITc_media_webrtc_media_source_set_get_pause_p(void);
extern int ITc_media_webrtc_media_source_set_get_mute_p(void);
extern int ITc_media_webrtc_media_source_set_get_video_resolution_p(void);
extern int ITc_media_webrtc_mic_source_set_sound_stream_info_p(void);
extern int ITc_media_webrtc_media_packet_source_set_format_p(void);
extern int ITc_media_webrtc_media_packet_source_push_packet_p(void);
extern int ITc_media_webrtc_set_get_stun_server_p(void);
extern int ITc_media_webrtc_add_turn_server_p(void);
extern int ITc_media_webrtc_foreach_turn_server_p(void);
extern int ITc_media_webrtc_create_offer_answer_p(void);
extern int ITc_media_webrtc_set_local_description_p(void);
extern int ITc_media_webrtc_set_remote_description_p(void);
extern int ITc_media_webrtc_add_ice_candidate_p(void);
extern int ITc_media_webrtc_create_destroy_data_channel_p(void);
extern int ITc_media_webrtc_get_data_p(void);
extern int ITc_webrtc_data_channel_send_string_p(void);
extern int ITc_media_webrtc_set_unset_state_changed_cb_p(void);
extern int ITc_media_webrtc_set_unset_error_cb_p(void);
extern int ITc_media_webrtc_set_unset_ice_candidate_cb_p(void);
extern int ITc_media_webrtc_set_unset_negotiation_needed_cb_p(void);
extern int ITc_media_webrtc_set_unset_peer_connection_state_change_cb_p(void);
extern int ITc_media_webrtc_set_unset_signaling_state_change_cb_p(void);
extern int ITc_media_webrtc_set_unset_ice_gathering_state_change_cb_p(void);
extern int ITc_media_webrtc_set_unset_ice_connection_state_change_cb_p(void);
extern int ITc_media_webrtc_set_unset_encoded_audio_frame_cb_p(void);
extern int ITc_media_webrtc_set_unset_encoded_video_frame_cb_p(void);
extern int ITc_media_webrtc_media_packet_source_set_unset_buffer_state_changed_cb_p(void);
extern int ITc_media_webrtc_set_unset_data_channel_cb_p(void);
extern int ITc_media_webrtc_data_channel_set_unset_open_cb_p(void);
extern int ITc_media_webrtc_data_channel_set_unset_message_cb_p(void);
extern int ITc_media_webrtc_data_channel_set_unset_error_cb_p(void);
extern int ITc_media_webrtc_data_channel_set_unset_close_cb_p(void);
extern int ITc_webrtc_data_channel_get_label_p(void);
extern int ITc_webrtc_set_unset_track_added_cb_p(void);
extern int ITc_webrtc_data_channel_send_bytes_p(void);
extern int ITc_media_webrtc_create_offer_async_p(void);
extern int ITc_media_webrtc_create_answer_async_p(void);
extern int ITc_media_webrtc_media_source_set_audio_loopback_p(void);
extern int ITc_media_webrtc_media_source_set_video_loopback_p(void);
extern int ITc_media_webrtc_set_get_display_mode_p(void);
extern int ITc_media_webrtc_set_get_display_visible_p(void);
extern int ITc_media_webrtc_set_get_ice_transport_policy_p(void);
extern int ITc_media_webrtc_start_and_finish_negotiation_p(void);

testcase tc_array[] = {
    {"ITc_webrtc_create_destroy_p", ITc_webrtc_create_destroy_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_webrtc_start_stop_p", ITc_webrtc_start_stop_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_webrtc_data_channel_get_label_p", ITc_webrtc_data_channel_get_label_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_webrtc_data_channel_send_bytes_p", ITc_webrtc_data_channel_send_bytes_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_get_state_p",ITc_media_webrtc_get_state_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_create_offer_async_p", ITc_media_webrtc_create_offer_async_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_create_answer_async_p", ITc_media_webrtc_create_answer_async_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_add_remove_media_source_p",ITc_media_webrtc_add_remove_media_source_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_get_peer_connection_state_p",ITc_media_webrtc_get_peer_connection_state_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_get_signaling_state_p",ITc_media_webrtc_get_signaling_state_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_get_ice_gathering_state_p",ITc_media_webrtc_get_ice_gathering_state_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_get_ice_connection_state_p",ITc_media_webrtc_get_ice_connection_state_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_media_source_set_get_transceiver_direction_p",ITc_media_webrtc_media_source_set_get_transceiver_direction_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_media_source_set_get_pause_p",ITc_media_webrtc_media_source_set_get_pause_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_media_source_set_get_mute_p",ITc_media_webrtc_media_source_set_get_mute_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_media_source_set_get_video_resolution_p",ITc_media_webrtc_media_source_set_get_video_resolution_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_mic_source_set_sound_stream_info_p",ITc_media_webrtc_mic_source_set_sound_stream_info_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_media_packet_source_set_format_p",ITc_media_webrtc_media_packet_source_set_format_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_media_packet_source_push_packet_p",ITc_media_webrtc_media_packet_source_push_packet_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_media_source_set_audio_loopback_p",ITc_media_webrtc_media_source_set_audio_loopback_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_media_source_set_video_loopback_p",ITc_media_webrtc_media_source_set_video_loopback_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_set_get_display_mode_p",ITc_media_webrtc_set_get_display_mode_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_set_get_display_visible_p",ITc_media_webrtc_set_get_display_visible_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_set_get_ice_transport_policy_p",ITc_media_webrtc_set_get_ice_transport_policy_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_set_get_stun_server_p",ITc_media_webrtc_set_get_stun_server_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_add_turn_server_p",ITc_media_webrtc_add_turn_server_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_foreach_turn_server_p",ITc_media_webrtc_foreach_turn_server_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_create_offer_answer_p",ITc_media_webrtc_create_offer_answer_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_set_local_description_p",ITc_media_webrtc_set_local_description_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_set_remote_description_p",ITc_media_webrtc_set_remote_description_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_add_ice_candidate_p",ITc_media_webrtc_add_ice_candidate_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_create_destroy_data_channel_p",ITc_media_webrtc_create_destroy_data_channel_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_get_data_p",ITc_media_webrtc_get_data_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_webrtc_data_channel_send_string_p",ITc_webrtc_data_channel_send_string_p, ITs_webrtc_startup, ITs_webrtc_cleanup},
    {"ITc_media_webrtc_set_unset_state_changed_cb_p",ITc_media_webrtc_set_unset_state_changed_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_set_unset_error_cb_p",ITc_media_webrtc_set_unset_error_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_set_unset_ice_candidate_cb_p",ITc_media_webrtc_set_unset_ice_candidate_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_set_unset_negotiation_needed_cb_p",ITc_media_webrtc_set_unset_negotiation_needed_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_set_unset_peer_connection_state_change_cb_p",ITc_media_webrtc_set_unset_peer_connection_state_change_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_set_unset_signaling_state_change_cb_p",ITc_media_webrtc_set_unset_signaling_state_change_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_set_unset_ice_gathering_state_change_cb_p",ITc_media_webrtc_set_unset_ice_gathering_state_change_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_set_unset_ice_connection_state_change_cb_p",ITc_media_webrtc_set_unset_ice_connection_state_change_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_set_unset_encoded_audio_frame_cb_p",ITc_media_webrtc_set_unset_encoded_audio_frame_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_set_unset_encoded_video_frame_cb_p",ITc_media_webrtc_set_unset_encoded_video_frame_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_media_packet_source_set_unset_buffer_state_changed_cb_p",ITc_media_webrtc_media_packet_source_set_unset_buffer_state_changed_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_set_unset_data_channel_cb_p",ITc_media_webrtc_set_unset_data_channel_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_data_channel_set_unset_open_cb_p",ITc_media_webrtc_data_channel_set_unset_open_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_data_channel_set_unset_message_cb_p",ITc_media_webrtc_data_channel_set_unset_message_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_data_channel_set_unset_error_cb_p",ITc_media_webrtc_data_channel_set_unset_error_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_data_channel_set_unset_close_cb_p",ITc_media_webrtc_data_channel_set_unset_close_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_webrtc_set_unset_track_added_cb_p",ITc_webrtc_set_unset_track_added_cb_p,ITs_webrtc_callback_startup, ITs_webrtc_callback_cleanup},
    {"ITc_media_webrtc_start_and_finish_negotiation_p", ITc_media_webrtc_start_and_finish_negotiation_p, NULL, NULL},
    {NULL, NULL}
};

#endif // __TCT_WEBRTC_NATIVE_H__
