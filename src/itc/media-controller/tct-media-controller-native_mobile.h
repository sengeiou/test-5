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
#ifndef __TCT_MEDIA-CONTROLLER-NATIVE_H__
#define __TCT_MEDIA-CONTROLLER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_media_controller_server_startup(void);
extern void ITs_media_controller_server_cleanup(void);
extern void ITs_media_controller_client_startup(void);
extern void ITs_media_controller_client_cleanup(void);

extern int ITc_mc_server_create_destroy_p(void);
extern int ITc_mc_server_set_playback_state_p(void);
extern int ITc_mc_server_set_playback_position_p(void);
extern int ITc_mc_server_set_metadata_p(void);
extern int ITc_mc_server_update_playback_info_p(void);
extern int ITc_mc_server_update_metadata_p(void);
extern int ITc_mc_server_update_shuffle_mode_p(void);
extern int ITc_mc_server_update_repeat_mode_p(void);
extern int ITc_mc_server_set_unset_repeat_mode_cmd_received_cb_p(void);
extern int ITc_mc_server_set_unset_shufle_mode_cmd_received_cb_p(void);
extern int ITc_mc_server_set_unset_playback_position_cmd_received_cb_p(void);
extern int ITc_mc_server_set_unset_playlist_cmd_received_cb_p(void);
extern int ITc_mc_server_set_unset_custom_cmd_received_cb_p(void);
extern int ITc_mc_server_foreach_client_p(void);
extern int ITc_mc_server_set_unset_cb_send_custom_event_p(void);
extern int ITc_mc_server_send_cmd_reply_p(void);
extern int ITc_mc_server_add_item_to_playlist_p(void);
extern int ITc_mc_server_update_playlist_done_p(void);
extern int ITs_mc_client_create_destroy_p(void);
extern int ITs_mc_client_set_unset_server_updated_cb_p(void);
extern int ITs_mc_client_set_unset_playback_updated_cb_p(void);
extern int ITs_mc_client_set_unset_metadata_updated_cb_p(void);
extern int ITs_mc_client_set_unset_shuffle_mode_updated_cb_p(void);
extern int ITs_mc_client_set_unset_repeat_mode_updated_cb_p(void);
extern int ITc_mc_client_get_latest_server_info_p(void);
extern int ITc_mc_client_get_destroy_server_playback_info_p(void);
extern int ITc_mc_client_get_destroy_server_metadata_p(void);
extern int ITc_mc_client_get_server_shuffle_mode_p(void);
extern int ITc_mc_client_get_server_repeat_mode_p(void);
extern int ITc_mc_client_get_playback_state_p(void);
extern int ITc_mc_client_get_playback_position_p(void);
extern int ITs_mc_client_foreach_server_p(void);
extern int ITs_mc_client_send_playback_action_cmd_p(void);
extern int ITc_mc_client_subscribe_unsubscribe_p(void);
extern int ITc_mc_client_foreach_server_subscribed_p(void);
extern int ITc_mc_client_send_playback_position_cmd_p(void);
extern int ITc_mc_client_send_shuffle_mode_cmd_p(void);
extern int ITc_mc_client_send_repeat_mode_cmd_p(void);
extern int ITc_mc_client_send_playlist_cmd_p(void);
extern int ITc_mc_client_send_custom_cmd_p(void);
extern int ITc_mc_client_set_unset_cmd_reply_received_cb_p(void);
extern int ITc_mc_client_set_unset_cb_send_event_reply_p(void);
extern int ITc_mc_client_set_unset_playlist_updated_cb_p(void);
extern int ITc_mc_client_set_get_playlist_item_info_p(void);
extern int ITc_mc_playlist_get_name_p(void);
extern int ITc_mc_server_create_destroy_playlist_p(void);
extern int ITc_mc_server_create_update_add_delete_playlist_p(void);
extern int ITc_mc_playlist_foreach_item_p(void);
extern int ITc_mc_playlist_clone_and_destroy_p(void);
extern int ITc_mc_playlist_get_item_count_p(void);
extern int ITc_mc_playlist_get_playlist_count_p(void);
extern int ITc_mc_playlist_get_playlist_p(void);
extern int ITc_mc_playlist_foreach_playlist_p(void);
extern int ITc_mc_metadata_clone_p(void);
extern int ITc_mc_metadata_destroy_p(void);
extern int ITc_mc_metadata_get_p(void);
extern int ITc_mc_server_set_get_playback_content_type_p(void);
extern int ITc_mc_server_set_get_icon_p(void);
extern int ITc_mc_server_set_get_update_playback_ability_p(void);
extern int ITc_mc_client_set_unset_playback_ability_updated_cb_p(void);
extern int ITc_mc_playback_ability_clone_destroy_p(void);
extern int ITc_mc_playback_action_is_supported_p(void);
extern int ITc_mc_client_set_get_age_rating_p(void);
extern int ITc_mc_client_send_search_cmd_p(void);
extern int ITc_mc_search_create_clone_destroy_p(void);
extern int ITc_mc_search_set_condition_p(void);
extern int ITc_mc_search_foreach_condition_p(void);
extern int ITc_mc_server_set_unset_search_cmd_received_cb_p(void);
extern int ITc_mc_search_get_condition_count_p(void);
extern int ITc_mc_metadata_encode_decode_season_p(void);
extern int ITc_mc_metadata_encode_decode_episode_p(void);
extern int ITc_mc_metadata_encode_decode_resolution_p(void);
extern int ITc_mc_client_set_unset_ability_support_updated_cb_p(void);
extern int ITc_mc_client_get_server_ability_support_p(void);
extern int ITc_mc_client_set_unset_display_mode_ability_updated_cb_p(void);
extern int ITc_mc_client_set_unset_display_rotation_ability_updated_cb_p(void);
extern int ITc_mc_client_set_unset_subtitles_updated_cb_p(void);
extern int ITc_mc_client_set_unset_360_mode_updated_cb_p(void);
extern int ITc_mc_client_set_unset_display_mode_updated_cb_p(void);
extern int ITc_mc_client_set_unset_display_rotation_updated_cb_p(void);
extern int ITc_mc_client_get_server_subtitles_enabled_p(void);
extern int ITc_mc_client_get_server_360_mode_enabled_p(void);
extern int ITc_mc_client_get_server_display_mode_p(void);
extern int ITc_mc_client_get_server_display_rotation_p(void);
extern int ITc_mc_client_get_server_display_mode_ability_p(void);
extern int ITc_mc_client_get_server_display_rotation_ability_p(void);
extern int ITc_mc_client_send_subtitles_cmd_p(void);
extern int ITc_mc_client_send_360_mode_cmd_p(void);
extern int ITc_mc_client_send_display_mode_cmd_p(void);
extern int ITc_mc_client_send_display_rotation_cmd_p(void);
extern int ITc_mc_server_update_subtitles_enabled_p(void);
extern int ITc_mc_server_update_360_mode_enabled_p(void);
extern int ITc_mc_server_update_display_mode_p(void);
extern int ITc_mc_server_update_display_rotation_p(void);
extern int ITc_mc_server_set_unset_subtitles_cmd_received_cb_p(void);
extern int ITc_mc_server_set_unset_360_mode_cmd_received_cb_p(void);
extern int ITc_mc_server_set_unset_display_mode_cmd_received_cb_p(void);
extern int ITc_mc_server_set_unset_display_rotation_cmd_received_cb_p(void);
extern int ITc_mc_server_set_display_mode_ability_p(void);
extern int ITc_mc_server_set_display_rotation_ability_p(void);

testcase tc_array[] = {
	{"ITc_mc_server_create_destroy_p",ITc_mc_server_create_destroy_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_playback_state_p",ITc_mc_server_set_playback_state_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_playback_position_p",ITc_mc_server_set_playback_position_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_metadata_p",ITc_mc_server_set_metadata_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_update_playback_info_p",ITc_mc_server_update_playback_info_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_update_metadata_p",ITc_mc_server_update_metadata_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_update_shuffle_mode_p",ITc_mc_server_update_shuffle_mode_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_update_repeat_mode_p",ITc_mc_server_update_repeat_mode_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_unset_repeat_mode_cmd_received_cb_p",ITc_mc_server_set_unset_repeat_mode_cmd_received_cb_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_unset_shufle_mode_cmd_received_cb_p",ITc_mc_server_set_unset_shufle_mode_cmd_received_cb_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_unset_playback_position_cmd_received_cb_p",ITc_mc_server_set_unset_playback_position_cmd_received_cb_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_unset_playlist_cmd_received_cb_p",ITc_mc_server_set_unset_playlist_cmd_received_cb_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_unset_custom_cmd_received_cb_p",ITc_mc_server_set_unset_custom_cmd_received_cb_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_foreach_client_p",ITc_mc_server_foreach_client_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_unset_cb_send_custom_event_p",ITc_mc_server_set_unset_cb_send_custom_event_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_send_cmd_reply_p",ITc_mc_server_send_cmd_reply_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_add_item_to_playlist_p",ITc_mc_server_add_item_to_playlist_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_update_playlist_done_p",ITc_mc_server_update_playlist_done_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITs_mc_client_create_destroy_p",ITs_mc_client_create_destroy_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITs_mc_client_set_unset_server_updated_cb_p",ITs_mc_client_set_unset_server_updated_cb_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITs_mc_client_set_unset_playback_updated_cb_p",ITs_mc_client_set_unset_playback_updated_cb_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITs_mc_client_set_unset_metadata_updated_cb_p",ITs_mc_client_set_unset_metadata_updated_cb_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITs_mc_client_set_unset_shuffle_mode_updated_cb_p",ITs_mc_client_set_unset_shuffle_mode_updated_cb_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITs_mc_client_set_unset_repeat_mode_updated_cb_p",ITs_mc_client_set_unset_repeat_mode_updated_cb_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_latest_server_info_p",ITc_mc_client_get_latest_server_info_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_destroy_server_playback_info_p",ITc_mc_client_get_destroy_server_playback_info_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_destroy_server_metadata_p",ITc_mc_client_get_destroy_server_metadata_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_server_shuffle_mode_p",ITc_mc_client_get_server_shuffle_mode_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_server_repeat_mode_p",ITc_mc_client_get_server_repeat_mode_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_playback_state_p",ITc_mc_client_get_playback_state_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_playback_position_p",ITc_mc_client_get_playback_position_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITs_mc_client_foreach_server_p",ITs_mc_client_foreach_server_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITs_mc_client_send_playback_action_cmd_p",ITs_mc_client_send_playback_action_cmd_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_subscribe_unsubscribe_p",ITc_mc_client_subscribe_unsubscribe_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_foreach_server_subscribed_p",ITc_mc_client_foreach_server_subscribed_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_send_playback_position_cmd_p",ITc_mc_client_send_playback_position_cmd_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_send_shuffle_mode_cmd_p",ITc_mc_client_send_shuffle_mode_cmd_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_send_repeat_mode_cmd_p",ITc_mc_client_send_repeat_mode_cmd_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_send_playlist_cmd_p",ITc_mc_client_send_playlist_cmd_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_send_custom_cmd_p",ITc_mc_client_send_custom_cmd_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_set_unset_cmd_reply_received_cb_p",ITc_mc_client_set_unset_cmd_reply_received_cb_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_set_unset_cb_send_event_reply_p",ITc_mc_client_set_unset_cb_send_event_reply_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_set_unset_playlist_updated_cb_p",ITc_mc_client_set_unset_playlist_updated_cb_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_set_get_playlist_item_info_p",ITc_mc_client_set_get_playlist_item_info_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_playlist_get_name_p",ITc_mc_playlist_get_name_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_server_create_destroy_playlist_p",ITc_mc_server_create_destroy_playlist_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_server_create_update_add_delete_playlist_p",ITc_mc_server_create_update_add_delete_playlist_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_playlist_foreach_item_p",ITc_mc_playlist_foreach_item_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_playlist_clone_and_destroy_p",ITc_mc_playlist_clone_and_destroy_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_playlist_get_item_count_p",ITc_mc_playlist_get_item_count_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_playlist_get_playlist_count_p",ITc_mc_playlist_get_playlist_count_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_playlist_get_playlist_p",ITc_mc_playlist_get_playlist_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_playlist_foreach_playlist_p",ITc_mc_playlist_foreach_playlist_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_metadata_clone_p",ITc_mc_metadata_clone_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_metadata_destroy_p",ITc_mc_metadata_destroy_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_metadata_get_p",ITc_mc_metadata_get_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_server_set_get_playback_content_type_p",ITc_mc_server_set_get_playback_content_type_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_get_icon_p",ITc_mc_server_set_get_icon_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_get_update_playback_ability_p",ITc_mc_server_set_get_update_playback_ability_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_client_set_unset_playback_ability_updated_cb_p",ITc_mc_client_set_unset_playback_ability_updated_cb_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_playback_ability_clone_destroy_p",ITc_mc_playback_ability_clone_destroy_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_playback_action_is_supported_p",ITc_mc_playback_action_is_supported_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_set_get_age_rating_p",ITc_mc_client_set_get_age_rating_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_send_search_cmd_p",ITc_mc_client_send_search_cmd_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_search_create_clone_destroy_p",ITc_mc_search_create_clone_destroy_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_search_set_condition_p",ITc_mc_search_set_condition_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_search_foreach_condition_p",ITc_mc_search_foreach_condition_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_server_set_unset_search_cmd_received_cb_p",ITc_mc_server_set_unset_search_cmd_received_cb_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_search_get_condition_count_p", ITc_mc_search_get_condition_count_p, ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_metadata_encode_decode_season_p",ITc_mc_metadata_encode_decode_season_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_metadata_encode_decode_episode_p",ITc_mc_metadata_encode_decode_episode_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_metadata_encode_decode_resolution_p",ITc_mc_metadata_encode_decode_resolution_p,ITs_media_controller_server_startup,ITs_media_controller_server_cleanup},
	{"ITc_mc_client_set_unset_ability_support_updated_cb_p",ITc_mc_client_set_unset_ability_support_updated_cb_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_server_ability_support_p",ITc_mc_client_get_server_ability_support_p,ITs_media_controller_client_startup,ITs_media_controller_client_cleanup},
	{"ITc_mc_client_set_unset_display_mode_ability_updated_cb_p", ITc_mc_client_set_unset_display_mode_ability_updated_cb_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_set_unset_display_rotation_ability_updated_cb_p", ITc_mc_client_set_unset_display_rotation_ability_updated_cb_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_set_unset_subtitles_updated_cb_p", ITc_mc_client_set_unset_subtitles_updated_cb_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_set_unset_360_mode_updated_cb_p", ITc_mc_client_set_unset_360_mode_updated_cb_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_set_unset_display_mode_updated_cb_p", ITc_mc_client_set_unset_display_mode_updated_cb_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_set_unset_display_rotation_updated_cb_p", ITc_mc_client_set_unset_display_rotation_updated_cb_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_server_subtitles_enabled_p", ITc_mc_client_get_server_subtitles_enabled_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_server_360_mode_enabled_p", ITc_mc_client_get_server_360_mode_enabled_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_server_display_mode_p", ITc_mc_client_get_server_display_mode_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_server_display_rotation_p", ITc_mc_client_get_server_display_rotation_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_server_display_mode_ability_p", ITc_mc_client_get_server_display_mode_ability_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_get_server_display_rotation_ability_p", ITc_mc_client_get_server_display_rotation_ability_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_send_subtitles_cmd_p", ITc_mc_client_send_subtitles_cmd_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_send_360_mode_cmd_p", ITc_mc_client_send_360_mode_cmd_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_send_display_mode_cmd_p", ITc_mc_client_send_display_mode_cmd_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_client_send_display_rotation_cmd_p", ITc_mc_client_send_display_rotation_cmd_p, ITs_media_controller_client_startup, ITs_media_controller_client_cleanup},
	{"ITc_mc_server_update_subtitles_enabled_p", ITc_mc_server_update_subtitles_enabled_p, ITs_media_controller_server_startup, ITs_media_controller_server_cleanup},
	{"ITc_mc_server_update_360_mode_enabled_p", ITc_mc_server_update_360_mode_enabled_p, ITs_media_controller_server_startup, ITs_media_controller_server_cleanup},
	{"ITc_mc_server_update_display_mode_p", ITc_mc_server_update_display_mode_p, ITs_media_controller_server_startup, ITs_media_controller_server_cleanup},
	{"ITc_mc_server_update_display_rotation_p", ITc_mc_server_update_display_rotation_p, ITs_media_controller_server_startup, ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_unset_subtitles_cmd_received_cb_p", ITc_mc_server_set_unset_subtitles_cmd_received_cb_p, ITs_media_controller_server_startup, ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_unset_360_mode_cmd_received_cb_p", ITc_mc_server_set_unset_360_mode_cmd_received_cb_p, ITs_media_controller_server_startup, ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_unset_display_mode_cmd_received_cb_p", ITc_mc_server_set_unset_display_mode_cmd_received_cb_p, ITs_media_controller_server_startup, ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_unset_display_rotation_cmd_received_cb_p", ITc_mc_server_set_unset_display_rotation_cmd_received_cb_p, ITs_media_controller_server_startup, ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_display_mode_ability_p", ITc_mc_server_set_display_mode_ability_p, ITs_media_controller_server_startup, ITs_media_controller_server_cleanup},
	{"ITc_mc_server_set_display_rotation_ability_p", ITc_mc_server_set_display_rotation_ability_p, ITs_media_controller_server_startup, ITs_media_controller_server_cleanup},

	{NULL, NULL}
};

#endif // __TCT_MEDIA-CONTROLLER-NATIVE_H__
