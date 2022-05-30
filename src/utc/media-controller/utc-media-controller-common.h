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

#ifndef _UTC_MEDIA_CONTROLLER_COMMON_H_
#define _UTC_MEDIA_CONTROLLER_COMMON_H_

#include "assert.h"
#include <media_controller_server.h>
#include <media_controller_client.h>
#include <glib.h>
#include <unistd.h>
#include <string.h>
#include <bundle.h>

#define G_META_INT_VAL 15
#define G_META_W 320
#define G_META_H 240


//& set: MediaControllerCommon

//Add global variables here
typedef struct _tc_user_data {
	char *name;
	char *request_id;
	gboolean result;
	mc_result_code_e result_code;
} tc_user_data;

//Add const values here
static const char *g_mc_test_appname = "org.tizen.media-controller-native-utc";

static const mc_playback_states_e g_mc_test_playback_state = MC_PLAYBACK_STATE_STOPPED;
static const mc_playback_action_e g_mc_test_playback_action = MC_PLAYBACK_ACTION_STOP;
static const unsigned long long g_mc_test_playback_position = 9999;

static const char *g_mc_test_metadata[] = {
	"media_title",
	"media_artist",
	"media_album",
	"media_author",
	"media_genre",
	"200",
	"media_date",
	"media_copyright",
	"media_description",
	"media_track_num 3/10",
	"media_picture_path",
	"media_season",
	"media_episode",
};

static const mc_shuffle_mode_e g_mc_test_shuffle_mode = MC_SHUFFLE_MODE_OFF;
static const mc_repeat_mode_e g_mc_test_repeat_mode = MC_REPEAT_MODE_ONE_MEDIA;

static const mc_playlist_update_mode_e g_mc_test_playlist_mode = MC_PLAYLIST_UPDATED;
static const char *g_mc_test_playlist_name = "test_playlist";
static const char *g_mc_test_playlist_idx = "1";
static const char *g_mc_test_playlist_index = "3";
static const char *g_mc_test_playlist_metadata[] = {
	"title_1",
	"artist_1",
	"album_1",
	"author_1",
	"genre_1",
	"duration_1",
	"date_1",
	"copyright_1",
	"destription_1",
	"track_num_1",
	"picture_1",
	"season_1",
	"episode_1",
};

static const char *g_mc_test_cmd = "test_cmd";
static const char *g_mc_test_event = "test_event";
static const mc_result_code_e g_mc_test_result_code = MC_RESULT_CODE_SUCCESS;
static const unsigned int g_mc_test_result_codes[] = {
	MC_RESULT_CODE_SUCCESS,
	MC_RESULT_CODE_ALREADY_DONE,
	MC_RESULT_CODE_ABORTED,
	MC_RESULT_CODE_TIMEOUT,
	MC_RESULT_CODE_NETWORK_FAILED,
	MC_RESULT_CODE_NO_ACCOUNT,
	MC_RESULT_CODE_UNKNOWN,
};
static const unsigned int g_mc_test_result_codes_cnt = (unsigned int)(sizeof(g_mc_test_result_codes) / sizeof(unsigned int));

static const mc_content_type_e g_mc_test_content_type = MC_CONTENT_TYPE_MUSIC;
static const mc_content_age_rating_e g_mc_test_age_rating = MC_CONTENT_RATING_18_PLUS;
static const char *g_mc_test_icon_path = "test.jpg";
static const mc_ability_support_e g_mc_test_ability = MC_ABILITY_SUPPORTED_YES;
static const mc_ability_support_e g_mc_test_ability_n = MC_ABILITY_SUPPORTED_NO;

static const char *g_mc_test_keywords[] = {
	"test_keyword",
	"test_title",
	"test_artist",
	"test_album",
	"test_genre",
	"test_time_place_occasion",
};

//Add foreach callback function declarations here
bool _mc_activated_server_cb(const char *server_name, void *user_data);
bool _mc_activated_client_cb(const char *client_name, void *user_data);
bool _mc_subscribed_server_cb(const char *server_name, void *user_data);
bool _mc_playlist_list_cb(mc_playlist_h playlist, void *user_data);
bool _mc_search_condition_cb(mc_content_type_e content_type, mc_search_category_e category, const char *search_keyword, bundle *data, void *user_data);
bool _mc_playlist_item_cb(const char *index, mc_metadata_h meta, void *user_data);

//Add callback function declarations here
void _mc_server_playback_position_cmd_received_cb(const char* client_name, const char *request_id, unsigned long long position, void *user_data);
void _mc_server_shuffle_mode_cmd_received_cb(const char* client_name, const char *request_id, mc_shuffle_mode_e mode, void *user_data);
void _mc_server_repeat_mode_cmd_received_cb(const char* client_name, const char *request_id, mc_repeat_mode_e mode, void *user_data);
void _mc_server_playback_action_cmd_received_cb(const char* client_name, const char *request_id, mc_playback_action_e action, void *user_data);
void _mc_server_playlist_cmd_received_cb(const char* client_name, const char *request_id, const char *playlist_name, const char *index, mc_playback_action_e action, unsigned long long position, void *user_data);
void _mc_server_custom_cmd_received_cb(const char* client_name, const char *request_id, const char *command, bundle *data, void *user_data);
void _mc_server_event_reply_received_cb(const char *client_name, const char *request_id, int result_code, bundle *data, void *user_data);
void _mc_server_search_cmd_received_cb(const char *client_name, const char *request_id, mc_search_h search, void *user_data);
void _mc_server_enable_cmd_received_cb(const char *client_name, const char *request_id, bool enable, void *user_data);
void _mc_server_display_mode_cmd_received_cb(const char *client_name, const char *request_id, mc_display_mode_e display_mode, void *user_data);
void _mc_server_display_rotation_cmd_received_cb(const char *client_name, const char *request_id, mc_display_rotation_e display_rotation, void *user_data);
void _mc_client_server_state_updated_cb(const char *server_name, mc_server_state_e state, void *user_data);
void _mc_client_playback_updated_cb(const char *server_name, mc_playback_h playback, void *user_data);
void _mc_client_metadata_updated_cb(const char *server_name, mc_metadata_h metadata, void *user_data);
void _mc_client_shuffle_mode_updated_cb(const char *server_name, mc_shuffle_mode_e mode, void *user_data);
void _mc_client_repeat_mode_updated_cb(const char *server_name, mc_repeat_mode_e mode, void *user_data);
void _mc_client_playback_ability_updated_cb(const char *server_name, mc_playback_ability_h ability, void *user_data);
void _mc_client_shuffle_ability_updated_cb(const char *server_name, mc_ability_support_e support, void *user_data);
void _mc_client_repeat_ability_updated_cb(const char *server_name, mc_ability_support_e support, void *user_data);
void _mc_client_ability_updated_cb(const char *server_name, mc_ability_e ability, mc_ability_support_e support, void *user_data);
void _mc_client_playlist_updated_cb(const char *server_name, mc_playlist_update_mode_e mode, const char *playlist_name, mc_playlist_h playlist, void *user_data);
void _mc_client_cmd_reply_received_cb(const char *server_name, const char *request_id, int result_code, bundle *data, void *user_data);
void _mc_client_custom_event_received_cb(const char *server_name, const char *request_id, const char *event, bundle *data, void *user_data);
void _mc_client_bool_attribute_updated_cb(const char *server_name, bool enabled, void *user_data);
void _mc_client_display_mode_updated_cb(const char *server_name, mc_display_mode_e mode, void *user_data);
void _mc_client_display_rotation_updated_cb(const char *server_name, mc_display_rotation_e rotation, void *user_data);
void _mc_client_display_mode_ability_updated_cb(const char *server_name, unsigned int supported_modes, void *user_data);
void _mc_client_display_rotation_ability_updated_cb(const char *server_name, unsigned int supported_rotations, void *user_data);


//Add helper function declarations here
gboolean wait_for_async(void);
gboolean _mc_get_display_mode_ability(unsigned int supported_modes);
gboolean _mc_get_display_rotation_ability(unsigned int supported_rotations);
void _mc_release_tc_user_data(tc_user_data *user_data);

int _mc_register_ability(mc_server_h mc_server);
int _mc_register_playlist(mc_server_h mc_server, mc_playlist_h *playlist);
int _mc_register_metadata(mc_server_h mc_server);
int _mc_verify_metadata(mc_metadata_h metadata);

#endif /* _UTC_MEDIA_CONTROLLER_COMMON_H_ */
