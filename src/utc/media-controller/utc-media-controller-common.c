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
#include "tct_common.h"
#include "utc-media-controller-common.h"

#define	TIMEOUT_SECONDS	5000


//& set: MediaControllerCommon


//Add helper function declarations here
static GMainLoop *g_mc_mainloop = NULL;
static gboolean g_async_result = FALSE;

gboolean timeout_func(gpointer data)
{
	FPRINTF("[%d:%s] invoked! Test case failed! \\n", __LINE__, __FUNCTION__);

	g_main_loop_quit((GMainLoop *) data);

	return FALSE;
}

void signal_async(gboolean async_result)
{
	g_async_result = async_result;

	if (g_mc_mainloop != NULL) {
		g_main_loop_quit(g_mc_mainloop);
	}
}

gboolean wait_for_async(void)
{
	int timeout_id = 0;
	g_mc_mainloop = g_main_loop_new(NULL, FALSE);

	// init
	g_async_result = FALSE;

	timeout_id = g_timeout_add(TIMEOUT_SECONDS, timeout_func, g_mc_mainloop);
	g_main_loop_run(g_mc_mainloop);
	g_source_remove(timeout_id);
	g_main_loop_unref(g_mc_mainloop);
	g_mc_mainloop = NULL;

	return g_async_result;
}

gboolean _mc_get_display_mode_ability(unsigned int supported_modes)
{
	if (!(supported_modes & MC_DISPLAY_MODE_LETTER_BOX)) {
		FPRINTF("[%d:%s] wrong supported mode [%d][%d]\\n", __LINE__, __FUNCTION__, supported_modes, MC_DISPLAY_MODE_LETTER_BOX);
		return FALSE;
	}

	if (!(supported_modes & MC_DISPLAY_MODE_ORIGIN_SIZE)) {
		FPRINTF("[%d:%s] wrong supported mode [%d][%d]\\n", __LINE__, __FUNCTION__, supported_modes, MC_DISPLAY_MODE_ORIGIN_SIZE);
		return FALSE;
	}

	if (!(supported_modes & MC_DISPLAY_MODE_FULL_SCREEN)) {
		FPRINTF("[%d:%s] wrong supported mode [%d][%d]\\n", __LINE__, __FUNCTION__, supported_modes, MC_DISPLAY_MODE_FULL_SCREEN);
		return FALSE;
	}

	if (!(supported_modes & MC_DISPLAY_MODE_CROPPED_FULL)) {
		FPRINTF("[%d:%s] wrong supported mode [%d][%d]\\n", __LINE__, __FUNCTION__, supported_modes, MC_DISPLAY_MODE_CROPPED_FULL);
		return FALSE;
	}

	return TRUE;
}

gboolean _mc_get_display_rotation_ability(unsigned int supported_rotations)
{
	if (!(supported_rotations & MC_DISPLAY_ROTATION_NONE)) {
		FPRINTF("[%d:%s] wrong supported rotation [%d][%d]\\n", __LINE__, __FUNCTION__, supported_rotations, MC_DISPLAY_ROTATION_NONE);
		return FALSE;
	}

	if (!(supported_rotations & MC_DISPLAY_ROTATION_90)) {
		FPRINTF("[%d:%s] wrong supported rotation [%d][%d]\\n", __LINE__, __FUNCTION__, supported_rotations, MC_DISPLAY_ROTATION_90);
		return FALSE;
	}

	if (!(supported_rotations & MC_DISPLAY_ROTATION_180)) {
		FPRINTF("[%d:%s] wrong supported rotation [%d][%d]\\n", __LINE__, __FUNCTION__, supported_rotations, MC_DISPLAY_ROTATION_180);
		return FALSE;
	}

	if (!(supported_rotations & MC_DISPLAY_ROTATION_270)) {
		FPRINTF("[%d:%s] wrong supported rotation [%d][%d]\\n", __LINE__, __FUNCTION__, supported_rotations, MC_DISPLAY_ROTATION_270);
		return FALSE;
	}

	return TRUE;
}

void _mc_release_tc_user_data(tc_user_data *user_data)
{
	if (!user_data)
		return;

	g_free(user_data->name);
	user_data->name = NULL;
	g_free(user_data->request_id);
	user_data->request_id = NULL;
}

int _mc_register_ability(mc_server_h mc_server)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_ability(mc_server, MC_PLAYBACK_ACTION_PLAY, MC_ABILITY_SUPPORTED_YES);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_ability failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_set_playback_ability(mc_server, MC_PLAYBACK_ACTION_PAUSE, MC_ABILITY_SUPPORTED_YES);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_ability failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_set_playback_ability(mc_server, MC_PLAYBACK_ACTION_STOP, MC_ABILITY_SUPPORTED_YES);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_ability failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_set_playback_ability(mc_server, MC_PLAYBACK_ACTION_NEXT, MC_ABILITY_SUPPORTED_YES);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_ability failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_set_playback_ability(mc_server, MC_PLAYBACK_ACTION_PREV, MC_ABILITY_SUPPORTED_YES);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_ability failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_set_playback_ability(mc_server, MC_PLAYBACK_ACTION_FAST_FORWARD, MC_ABILITY_SUPPORTED_YES);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_ability failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_set_playback_ability(mc_server, MC_PLAYBACK_ACTION_REWIND, MC_ABILITY_SUPPORTED_YES);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_ability failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_set_playback_ability(mc_server, MC_PLAYBACK_ACTION_TOGGLE_PLAY_PAUSE, MC_ABILITY_SUPPORTED_YES);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_ability failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_update_playback_ability(mc_server);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_update_playback_ability failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	return ret;
}

int _mc_register_playlist(mc_server_h mc_server, mc_playlist_h *playlist)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h _playlist = NULL;

	ret = mc_server_create_playlist(mc_server, g_mc_test_playlist_name, &_playlist);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_create_playlist failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_add_item_to_playlist(mc_server, _playlist, g_mc_test_playlist_idx, MC_META_MEDIA_TITLE, g_mc_test_playlist_metadata[0]);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_add_item_to_playlist failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_add_item_to_playlist(mc_server, _playlist, g_mc_test_playlist_idx, MC_META_MEDIA_ARTIST, g_mc_test_playlist_metadata[1]);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_add_item_to_playlist failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_add_item_to_playlist(mc_server, _playlist, g_mc_test_playlist_idx, MC_META_MEDIA_ALBUM, g_mc_test_playlist_metadata[2]);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_add_item_to_playlist failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_add_item_to_playlist(mc_server, _playlist, g_mc_test_playlist_idx, MC_META_MEDIA_AUTHOR, g_mc_test_playlist_metadata[3]);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_add_item_to_playlist failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_add_item_to_playlist(mc_server, _playlist, g_mc_test_playlist_idx, MC_META_MEDIA_GENRE, g_mc_test_playlist_metadata[4]);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_add_item_to_playlist failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_add_item_to_playlist(mc_server, _playlist, g_mc_test_playlist_idx, MC_META_MEDIA_DURATION, g_mc_test_playlist_metadata[5]);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_add_item_to_playlist failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_add_item_to_playlist(mc_server, _playlist, g_mc_test_playlist_idx, MC_META_MEDIA_DATE, g_mc_test_playlist_metadata[6]);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_add_item_to_playlist failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_add_item_to_playlist(mc_server, _playlist, g_mc_test_playlist_idx, MC_META_MEDIA_COPYRIGHT, g_mc_test_playlist_metadata[7]);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_add_item_to_playlist failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_add_item_to_playlist(mc_server, _playlist, g_mc_test_playlist_idx, MC_META_MEDIA_DESCRIPTION, g_mc_test_playlist_metadata[8]);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_add_item_to_playlist failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_add_item_to_playlist(mc_server, _playlist, g_mc_test_playlist_idx, MC_META_MEDIA_TRACK_NUM, g_mc_test_playlist_metadata[9]);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_add_item_to_playlist failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_add_item_to_playlist(mc_server, _playlist, g_mc_test_playlist_idx, MC_META_MEDIA_PICTURE, g_mc_test_playlist_metadata[10]);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_add_item_to_playlist failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_update_playlist_done(mc_server, _playlist);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_update_playlist_done failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	*playlist = _playlist;

	return MEDIA_CONTROLLER_ERROR_NONE;
}

int _mc_register_metadata(mc_server_h mc_server)
{
	mc_error_e ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *encoded_meta = NULL;
	int i = 0;

	for (i = MC_META_MEDIA_TITLE; i <= MC_META_MEDIA_PICTURE; i++)
		ret = mc_server_set_metadata(mc_server, i, g_mc_test_metadata[i]);

	ret = mc_metadata_encode_season(G_META_INT_VAL, g_mc_test_metadata[MC_META_MEDIA_SEASON], &encoded_meta);
	ret = mc_server_set_metadata(mc_server, MC_META_MEDIA_SEASON, encoded_meta);
	if (encoded_meta)
		free(encoded_meta);

	ret = mc_metadata_encode_episode(G_META_INT_VAL, g_mc_test_metadata[MC_META_MEDIA_EPISODE], &encoded_meta);
	ret = mc_server_set_metadata(mc_server, MC_META_MEDIA_EPISODE, encoded_meta);
	if (encoded_meta)
		free(encoded_meta);

	ret = mc_metadata_encode_resolution(G_META_W, G_META_H, &encoded_meta);
	ret = mc_server_set_metadata(mc_server, MC_META_MEDIA_RESOLUTION, encoded_meta);
	if (encoded_meta)
		free(encoded_meta);

	ret = mc_server_update_metadata(mc_server);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE)
		FPRINTF("[%s:%d] mc_server_update_metadata failed (code: %d)\\n", __FILE__, __LINE__, ret);

	return ret;
}

int _mc_verify_metadata(mc_metadata_h metadata)
{
	mc_error_e ret = MEDIA_CONTROLLER_ERROR_NONE;
	int i = 0;
	char *value = NULL;
	int int_val_1 = 0;
	int int_val_2 = 0;
	char *str_val = NULL;

	for (i = MC_META_MEDIA_TITLE; i <= MC_META_MEDIA_PICTURE; i++) {
		ret = mc_metadata_get(metadata, i, &value);
		if (ret != MEDIA_CONTROLLER_ERROR_NONE) {
			FPRINTF("[%s:%d] mc_metadata_get failed (code: %d)\\n", __FILE__, __LINE__, ret);
			return ret;
		}

		if (!value) {
			FPRINTF("[%s:%d] metadata mismatch! [%d] expect [%s] but NULL\\n", __FILE__, __LINE__, i, g_mc_test_metadata[i]);
			return MEDIA_CONTROLLER_ERROR_INVALID_OPERATION;
		}

		if (strcmp(value, g_mc_test_metadata[i]) != 0) {
			FPRINTF("[%s:%d] metadata mismatch! [%d] expect [%s] but [%s]\\n", __FILE__, __LINE__, i, g_mc_test_metadata[i], value);
			free(value);
			return MEDIA_CONTROLLER_ERROR_INVALID_OPERATION;
		}

		free(value);
	}

	for (i = MC_META_MEDIA_SEASON; i <= MC_META_MEDIA_RESOLUTION; i++) {
		ret = mc_metadata_get(metadata, i, &value);
		if (ret != MEDIA_CONTROLLER_ERROR_NONE) {
			FPRINTF("[%s:%d] mc_metadata_get failed (code: %d)\\n", __FILE__, __LINE__, ret);
			return ret;
		}

		if (!value) {
			FPRINTF("[%s:%d] metadata mismatch! [%d] expect [%s] but NULL\\n", __FILE__, __LINE__, i, g_mc_test_metadata[i]);
			return MEDIA_CONTROLLER_ERROR_INVALID_OPERATION;
		}

		if (i == MC_META_MEDIA_SEASON) {
			ret = mc_metadata_decode_season(value, &int_val_1, &str_val);
			if (ret != MEDIA_CONTROLLER_ERROR_NONE) {
				FPRINTF("[%s:%d] mc_metadata_decode_season failed (code: %d)\\n", __FILE__, __LINE__, ret);
				free(value);
				return ret;
			}

			if (!str_val) {
				FPRINTF("[%s:%d] metadata mismatch! [%d] expect [%s] but NULL\\n", __FILE__, __LINE__, i, g_mc_test_metadata[i]);
				free(value);
				return MEDIA_CONTROLLER_ERROR_INVALID_OPERATION;
			}

			if ((int_val_1 != G_META_INT_VAL) ||(strcmp(str_val, g_mc_test_metadata[i]) != 0)) {
				FPRINTF("[%s:%d] metadata mismatch! [%d] expect [%d][%s] but [%d][%s]\\n", __FILE__, __LINE__, i, G_META_INT_VAL, g_mc_test_metadata[i], int_val_1, str_val);
				free(value);
				free(str_val);
				return MEDIA_CONTROLLER_ERROR_INVALID_OPERATION;
			}

			free(str_val);
		} else if (i == MC_META_MEDIA_EPISODE) {
			ret = mc_metadata_decode_episode(value, &int_val_1, &str_val);
			if (ret != MEDIA_CONTROLLER_ERROR_NONE) {
				FPRINTF("[%s:%d] mc_metadata_decode_episode failed (code: %d)\\n", __FILE__, __LINE__, ret);
				free(value);
				return ret;
			}

			if (!str_val) {
				FPRINTF("[%s:%d] metadata mismatch! [%d] expect [%s] but NULL\\n", __FILE__, __LINE__, i, g_mc_test_metadata[i]);
				free(value);
				return MEDIA_CONTROLLER_ERROR_INVALID_OPERATION;
			}

			if ((int_val_1 != G_META_INT_VAL) ||(strcmp(str_val, g_mc_test_metadata[i]) != 0)) {
				FPRINTF("[%s:%d] metadata mismatch! [%d] expect [%d][%s] but [%d][%s]\\n", __FILE__, __LINE__, i, G_META_INT_VAL, g_mc_test_metadata[i], int_val_1, str_val);
				free(value);
				free(str_val);
				return MEDIA_CONTROLLER_ERROR_INVALID_OPERATION;
			}

			free(str_val);
		} else if (i == MC_META_MEDIA_RESOLUTION) {
			ret = mc_metadata_decode_resolution(value, (unsigned int *)&int_val_1, (unsigned int *)&int_val_2);
			if (ret != MEDIA_CONTROLLER_ERROR_NONE) {
				FPRINTF("[%s:%d] mc_metadata_decode_resolution failed (code: %d)\\n", __FILE__, __LINE__, ret);
				free(value);
				return ret;
			}

			if ((int_val_1 != G_META_W) ||(int_val_2 != G_META_H)) {
				FPRINTF("[%s:%d] metadata mismatch! [%d] expect [%d][%d] but [%d][%d]\\n", __FILE__, __LINE__, i, G_META_W, G_META_H, int_val_1, int_val_2);
				free(value);
				return MEDIA_CONTROLLER_ERROR_INVALID_OPERATION;
			}
		}

		free(value);
	}

	return MEDIA_CONTROLLER_ERROR_NONE;
}

//Add foreach callback function declarations here
bool _mc_activated_server_cb(const char *server_name, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);
	char **get_name = (char **)user_data;

	if(strcmp(server_name, g_mc_test_appname) == 0) {
		if(get_name != NULL)
			*get_name = g_strdup(server_name);

		return false;
	}

	return true;
}

bool _mc_activated_client_cb(const char *client_name, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);
	char **get_name = (char **)user_data;

	if(strcmp(client_name, g_mc_test_appname) == 0) {
		if(get_name != NULL)
			*get_name = g_strdup(client_name);

		return false;
	}

	return true;
}

bool _mc_subscribed_server_cb(const char *server_name, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);
	char **get_name = (char **)user_data;

	if(strcmp(server_name, g_mc_test_appname) == 0) {
		if (get_name != NULL)
			*get_name = g_strdup(server_name);
		return false;
	}

    return false;
}

bool _mc_playlist_list_cb(mc_playlist_h playlist, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *playlist_name = NULL;
	gboolean *result = (gboolean *)user_data;

	ret = mc_playlist_get_name(playlist, &playlist_name);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE)
		FPRINTF("[%d:%s] fail mc_playlist_get_name [%d]\\n", __LINE__, __FUNCTION__, ret);

	if(g_strcmp0(playlist_name, g_mc_test_playlist_name)) {
		FPRINTF("[%d:%s] wrong playlist name [%s][%s]\\n", __LINE__, __FUNCTION__, playlist_name, g_mc_test_playlist_name);
		free(playlist_name);
		*result = false;
		return false;
	}

	*result = true;

	return true;
}

bool _mc_search_condition_cb(mc_content_type_e content_type, mc_search_category_e category, const char *search_keyword, bundle *data, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	gboolean *result = (gboolean *)user_data;

	if (content_type != g_mc_test_content_type) {
		FPRINTF("[%d:%s] wrong content type [%d][%d]\\n", __LINE__, __FUNCTION__, content_type, g_mc_test_content_type);
		return false;
	}

	if (g_strcmp0(search_keyword, g_mc_test_keywords[category])) {
		FPRINTF("[%d:%s] wrong search keyword [%s][%s]\\n", __LINE__, __FUNCTION__, search_keyword, g_mc_test_keywords[category]);
		*result = false;
		return false;
	}

	*result = true;
	return true;
}

bool _mc_playlist_item_cb(const char *index, mc_metadata_h meta, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *value = NULL;
	gboolean *result = (gboolean *)user_data;

	if (index != NULL) {
		if(strcmp(index, g_mc_test_playlist_idx)) {
			FPRINTF("[%d:%s] wrong playlist index. expect [%s] but [%s]\\n", __LINE__, __FUNCTION__, g_mc_test_playlist_idx, index);
			return false;
		}

		ret = mc_metadata_get(meta, MC_META_MEDIA_TITLE, &value);
		if (ret != MEDIA_CONTROLLER_ERROR_NONE)
			FPRINTF("[%d:%s] fail mc_metadata_get [%d]\\n", __LINE__, __FUNCTION__, ret);

		if (value != NULL) {
			if(strcmp(value, g_mc_test_playlist_metadata[0])) {
				FPRINTF("[%d:%s] fail mc_metadata_get [%s]\\n", __LINE__, __FUNCTION__, value);
				free(value);
				return false;
			}
			free(value);
			*result = true;
		}
	} else {
		FPRINTF("[%d:%s] wrong index\\n", __LINE__, __FUNCTION__);
		return false;
	}

	return true;
}


//Add callback function declarations here
void _mc_server_playback_position_cmd_received_cb(const char* client_name, const char *request_id, unsigned long long position, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);
	char **_request_id = (char **)user_data;

	if (strcmp(client_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong client name [%s][%s]\\n", __LINE__, __FUNCTION__, client_name, g_mc_test_appname);
		return;
	}

	if(g_strcmp0(request_id, *_request_id)) {
		FPRINTF("[%d:%s] wrong request_ide [%s][%s]\\n", __LINE__, __FUNCTION__, request_id, *_request_id);
		signal_async(FALSE);
		return;
	}

	if (position != g_mc_test_playback_position) {
		FPRINTF("[%d:%s] wrong position [%llu][%llu]\\n", __LINE__, __FUNCTION__, position, g_mc_test_playback_position);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_server_shuffle_mode_cmd_received_cb(const char* client_name, const char *request_id, mc_shuffle_mode_e mode, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);
	char **_request_id = (char **)user_data;

	if (strcmp(client_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong client name [%s][%s]\\n", __LINE__, __FUNCTION__, client_name, g_mc_test_appname);
		return;
	}

	if(g_strcmp0(request_id, *_request_id)) {
		FPRINTF("[%d:%s] wrong request_ide [%s][%s]\\n", __LINE__, __FUNCTION__, request_id, *_request_id);
		signal_async(FALSE);
		return;
	}

	if (mode != g_mc_test_shuffle_mode) {
		FPRINTF("[%d:%s] wrong shuffle mode [%d]\\n", __LINE__, __FUNCTION__, mode);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_server_repeat_mode_cmd_received_cb(const char* client_name, const char *request_id, mc_repeat_mode_e mode, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);
	char **_request_id = (char **)user_data;

	if (strcmp(client_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong client name [%s][%s]\\n", __LINE__, __FUNCTION__, client_name, g_mc_test_appname);
		return;
	}

	if(g_strcmp0(request_id, *_request_id)) {
		FPRINTF("[%d:%s] wrong request_ide [%s][%s]\\n", __LINE__, __FUNCTION__, request_id, *_request_id);
		signal_async(FALSE);
		return;
	}

	if (mode != g_mc_test_repeat_mode) {
		FPRINTF("[%d:%s] wrong repeat mode [%d]\\n", __LINE__, __FUNCTION__, mode);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_server_playback_action_cmd_received_cb(const char* client_name, const char *request_id, mc_playback_action_e action, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);
	char **_request_id = (char **)user_data;

	if (strcmp(client_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong client name [%s][%s]\\n", __LINE__, __FUNCTION__, client_name, g_mc_test_appname);
		return;
	}

	if(g_strcmp0(request_id, *_request_id)) {
		FPRINTF("[%d:%s] wrong request_ide [%s][%s]\\n", __LINE__, __FUNCTION__, request_id, *_request_id);
		signal_async(FALSE);
		return;
	}

	if (action != g_mc_test_playback_action) {
		FPRINTF("[%d:%s] wrong action [%d]\\n", __LINE__, __FUNCTION__, action);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_server_playlist_cmd_received_cb(const char* client_name, const char *request_id, const char *playlist_name, const char *index, mc_playback_action_e action, unsigned long long position, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);
	char **_request_id = (char **)user_data;

	if (strcmp(client_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong client name [%s][%s]\\n", __LINE__, __FUNCTION__, client_name, g_mc_test_appname);
		return;
	}

	if(g_strcmp0(request_id, *_request_id)) {
		FPRINTF("[%d:%s] wrong request_ide [%s][%s]\\n", __LINE__, __FUNCTION__, request_id, *_request_id);
		signal_async(FALSE);
		return;
	}

	if (g_strcmp0(playlist_name, g_mc_test_playlist_name)) {
		FPRINTF("[%d:%s] wrong playlist name [%s][%s]\\n", __LINE__, __FUNCTION__, playlist_name, g_mc_test_playlist_name);
		signal_async(FALSE);
		return;
	}

	if (g_strcmp0(index, g_mc_test_playlist_index)) {
		FPRINTF("[%d:%s] wrong playlist index [%s][%s]\\n", __LINE__, __FUNCTION__, index, g_mc_test_playlist_index);
		signal_async(FALSE);
		return;
	}

	if (action != g_mc_test_playback_action) {
		FPRINTF("[%d:%s] wrong action [%d]\\n", __LINE__, __FUNCTION__, action);
		signal_async(FALSE);
		return;
	}

	if (position != g_mc_test_playback_position) {
		FPRINTF("[%d:%s] wrong action [%d]\\n", __LINE__, __FUNCTION__, action);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_server_custom_cmd_received_cb(const char* client_name, const char *request_id, const char *command, bundle *data, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	tc_user_data *_user_data = (tc_user_data *)user_data;

	if (strcmp(client_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong client name [%s][%s]\\n", __LINE__, __FUNCTION__, client_name, g_mc_test_appname);
		return;
	}

	if(g_strcmp0(command, g_mc_test_cmd)) {
		FPRINTF("[%d:%s] wrong command [%s][%s]\\n", __LINE__, __FUNCTION__, command, g_mc_test_cmd);
		signal_async(FALSE);
		return;
	}

	if (_user_data != NULL) {
		_user_data->result = TRUE;
		_user_data->name = g_strdup(client_name);
		_user_data->request_id = g_strdup(request_id);
		if (_user_data->name == NULL || _user_data->request_id == NULL)
			_user_data->result = FALSE;
	}

	signal_async(TRUE);
}

void _mc_server_event_reply_received_cb(const char *client_name, const char *request_id, int result_code, bundle *data, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	tc_user_data *_user_data = (tc_user_data *)user_data;

	if (strcmp(client_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong client name [%s][%s]\\n", __LINE__, __FUNCTION__, client_name, g_mc_test_appname);
		return;
	}

	if (_user_data != NULL) {
		_user_data->result = TRUE;
		_user_data->name = g_strdup(client_name);
		_user_data->request_id = g_strdup(request_id);
		_user_data->result_code = result_code;
		if (_user_data->name == NULL || _user_data->request_id == NULL)
			_user_data->result = FALSE;
	}

	signal_async(TRUE);
}

void _mc_server_search_cmd_received_cb(const char *client_name, const char *request_id, mc_search_h search, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if (strcmp(client_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong client name [%s][%s]\\n", __LINE__, __FUNCTION__, client_name, g_mc_test_appname);
		return;
	}

	if (search == NULL) {
		FPRINTF("[%d:%s] search is null\\n", __LINE__, __FUNCTION__);
		signal_async(FALSE);
		return;
	}

	mc_search_clone(search, (mc_search_h *)user_data);

	signal_async(TRUE);
}

void _mc_server_enable_cmd_received_cb(const char *client_name, const char *request_id, bool enable, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if (strcmp(client_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong client name [%s][%s]\\n", __LINE__, __FUNCTION__, client_name, g_mc_test_appname);
		return;
	}

	if (enable != true) {
		FPRINTF("[%d:%s] enable is not true\\n", __LINE__, __FUNCTION__);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_server_display_mode_cmd_received_cb(const char *client_name, const char *request_id, mc_display_mode_e display_mode, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if (strcmp(client_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong client name [%s][%s]\\n", __LINE__, __FUNCTION__, client_name, g_mc_test_appname);
		return;
	}

	if (display_mode != MC_DISPLAY_MODE_FULL_SCREEN) {
		FPRINTF("[%d:%s] wrong display mode [%d][%d]\\n", __LINE__, __FUNCTION__, display_mode, MC_DISPLAY_MODE_FULL_SCREEN);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_server_display_rotation_cmd_received_cb(const char *client_name, const char *request_id, mc_display_rotation_e display_rotation, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if (strcmp(client_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong client name [%s][%s]\\n", __LINE__, __FUNCTION__, client_name, g_mc_test_appname);
		return;
	}

	if (display_rotation != MC_DISPLAY_ROTATION_270) {
		FPRINTF("[%d:%s] wrong display mode [%d][%d]\\n", __LINE__, __FUNCTION__, display_rotation, MC_DISPLAY_ROTATION_270);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_client_server_state_updated_cb(const char *server_name, mc_server_state_e state, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if (state != MC_SERVER_STATE_DEACTIVATE) {
		FPRINTF("[%d:%s] wrong state [%d][%d]\\n", __LINE__, __FUNCTION__, state, MC_SERVER_STATE_DEACTIVATE);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_client_playback_updated_cb(const char *server_name, mc_playback_h playback, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_states_e state = MC_PLAYBACK_STATE_NONE;
	unsigned long long position = 0;
	mc_content_type_e content_type = MC_CONTENT_TYPE_UNDECIDED;
	mc_content_age_rating_e age_rating = MC_CONTENT_RATING_ALL;
	char *playlist_name = NULL;
	char *playlist_index = NULL;

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if (playback == NULL) {
		FPRINTF("[%d:%s] wrong playback handle\\n", __LINE__, __FUNCTION__);
		signal_async(FALSE);
		return;
	}

	ret = mc_client_get_playback_state(playback, &state);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE)
		FPRINTF("[%d:%s] fail mc_client_get_playback_state [%d]\\n", __LINE__, __FUNCTION__, ret);
	if (state != g_mc_test_playback_state) {
		FPRINTF("[%d:%s] wrong state [%d][%d]\\n", __LINE__, __FUNCTION__, state, g_mc_test_playback_state);
		signal_async(FALSE);
		return;
	}

	ret = mc_client_get_playback_position(playback, &position);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE)
		FPRINTF("[%d:%s] fail mc_client_get_playback_position [%d]\\n", __LINE__, __FUNCTION__, ret);
	if (position != g_mc_test_playback_position) {
		FPRINTF("[%d:%s] wrong position [%llu][%llu]\\n", __LINE__, __FUNCTION__, position, g_mc_test_playback_position);
		signal_async(FALSE);
		return;
	}

	ret = mc_client_get_playback_content_type(playback, &content_type);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE)
		FPRINTF("[%d:%s] fail mc_client_get_playback_content_type [%d]\\n", __LINE__, __FUNCTION__, ret);
	if (content_type != g_mc_test_content_type) {
		FPRINTF("[%d:%s] wrong content_type [%d][%d]\\n", __LINE__, __FUNCTION__, content_type, g_mc_test_content_type);
		signal_async(FALSE);
		return;
	}

	ret = mc_client_get_age_rating(playback, &age_rating);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE)
		FPRINTF("[%d:%s] fail mc_client_get_age_rating [%d]\\n", __LINE__, __FUNCTION__, ret);
	if (age_rating != g_mc_test_age_rating) {
		FPRINTF("[%d:%s] wrong age_rating [%d][%d]\\n", __LINE__, __FUNCTION__, age_rating, g_mc_test_age_rating);
		signal_async(FALSE);
		return;
	}

	ret = mc_client_get_playlist_item_info(playback, &playlist_name, &playlist_index);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE)
		FPRINTF("[%d:%s] fail mc_client_get_playlist_item_info [%d]\\n", __LINE__, __FUNCTION__, ret);
	if (g_strcmp0(playlist_name, g_mc_test_playlist_name)) {
		FPRINTF("[%d:%s] wrong playlist_name [%s][%s]\\n", __LINE__, __FUNCTION__, playlist_name, g_mc_test_playlist_name);
		signal_async(FALSE);
		return;
	}
	if (g_strcmp0(playlist_index, g_mc_test_playlist_index)) {
		FPRINTF("[%d:%s] wrong playlist_index [%s][%s]\\n", __LINE__, __FUNCTION__, playlist_index, g_mc_test_playlist_index);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_client_metadata_updated_cb(const char *server_name, mc_metadata_h metadata, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *value = NULL;

	signal_async(TRUE);

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if (metadata == NULL) {
		FPRINTF("[%d:%s] wrong meta handle\\n", __LINE__, __FUNCTION__);
		signal_async(FALSE);
		return;
	}

	ret = mc_metadata_get(metadata, MC_META_MEDIA_TITLE, &value);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE)
		FPRINTF("[%d:%s] fail mc_metadata_get [%d]\\n", __LINE__, __FUNCTION__, ret);

	if (value == NULL) {
		FPRINTF("[%d:%s] wrong metadata [%s]\\n", __LINE__, __FUNCTION__, value);
		signal_async(FALSE);
		return;
	}

	if (g_strcmp0(value, g_mc_test_metadata[0])) {
		FPRINTF("[%d:%s] wrong metadata [%s][%s]\\n", __LINE__, __FUNCTION__, value, g_mc_test_metadata[0]);
		free(value);
		signal_async(FALSE);
		return;
	}

	free(value);

	signal_async(TRUE);
}

void _mc_client_shuffle_mode_updated_cb(const char *server_name, mc_shuffle_mode_e mode, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if (mode != g_mc_test_shuffle_mode) {
		FPRINTF("[%d:%s] wrong shuffle_mode [%d][%d]\\n", __LINE__, __FUNCTION__, mode, g_mc_test_shuffle_mode);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_client_bool_attribute_updated_cb(const char *server_name, bool enabled, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if (enabled != true) {
		FPRINTF("[%d:%s] wrong attribute status [%d][%d]\\n", __LINE__, __FUNCTION__, enabled, false);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_client_display_mode_updated_cb(const char *server_name, mc_display_mode_e mode, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if (mode != MC_DISPLAY_MODE_FULL_SCREEN) {
		FPRINTF("[%d:%s] wrong display mode [%d][%d]\\n", __LINE__, __FUNCTION__, mode, MC_DISPLAY_MODE_FULL_SCREEN);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_client_display_rotation_updated_cb(const char *server_name, mc_display_rotation_e rotation, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if (rotation != MC_DISPLAY_ROTATION_270) {
		FPRINTF("[%d:%s] wrong display rotation [%d][%d]\\n", __LINE__, __FUNCTION__, rotation, MC_DISPLAY_ROTATION_270);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_client_repeat_mode_updated_cb(const char *server_name, mc_repeat_mode_e mode, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if (mode != g_mc_test_repeat_mode) {
		FPRINTF("[%d:%s] wrong mode [%d][%d]\\n", __LINE__, __FUNCTION__, mode, g_mc_test_repeat_mode);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_client_playback_ability_updated_cb(const char *server_name, mc_playback_ability_h ability, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);
	mc_ability_support_e supported = MC_ABILITY_SUPPORTED_UNDECIDED;

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if (ability == NULL) {
		FPRINTF("[%d:%s] ability is null\\n", __LINE__, __FUNCTION__);
		signal_async(FALSE);
		return;
	}

	mc_playback_action_is_supported(ability, g_mc_test_playback_action, &supported);
	if (supported != MC_ABILITY_SUPPORTED_YES) {
		FPRINTF("[%d:%s] wrong ability [%d][%d]\\n", __LINE__, __FUNCTION__, supported, MC_ABILITY_SUPPORTED_YES);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_client_shuffle_ability_updated_cb(const char *server_name, mc_ability_support_e support, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if (support != g_mc_test_ability) {
		FPRINTF("[%d:%s] wrong ability [%d][%d]\\n", __LINE__, __FUNCTION__, support, g_mc_test_ability);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_client_repeat_ability_updated_cb(const char *server_name, mc_ability_support_e support, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if (support != g_mc_test_ability) {
		FPRINTF("[%d:%s] wrong ability [%d][%d]\\n", __LINE__, __FUNCTION__, support, g_mc_test_ability);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_client_ability_updated_cb(const char *server_name, mc_ability_e ability, mc_ability_support_e support, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if (support != g_mc_test_ability) {
		FPRINTF("[%d:%s] wrong ability [%d][%d]\\n", __LINE__, __FUNCTION__, support, g_mc_test_ability);
		signal_async(FALSE);
		return;
	}

	signal_async(TRUE);
}

void _mc_client_playlist_updated_cb(const char *server_name, mc_playlist_update_mode_e mode, const char *playlist_name, mc_playlist_h playlist, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	gboolean cb_result = FALSE;

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if(strcmp(playlist_name, g_mc_test_playlist_name)) {
		FPRINTF("[%d:%s] wrong playlist name [%s][%s]\\n", __LINE__, __FUNCTION__, playlist_name, g_mc_test_playlist_name);
		signal_async(FALSE);
		return;
	}

	if ((mode != MC_PLAYLIST_UPDATED) && (mode != MC_PLAYLIST_REMOVED)) {
		FPRINTF("[%d:%s] wrong mode [%d]\\n", __LINE__, __FUNCTION__, mode);
		signal_async(FALSE);
		return;
	}

	if ((mode == MC_PLAYLIST_UPDATED) && (playlist == NULL)) {
		FPRINTF("[%d:%s] wrong playlist [%p]\\n", __LINE__, __FUNCTION__, playlist);
		signal_async(FALSE);
		return;
	}

	ret = mc_playlist_foreach_item(playlist, _mc_playlist_item_cb, &cb_result);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE)
		FPRINTF("[%d:%s] fail mc_playlist_foreach_item [%d]\\n", __LINE__, __FUNCTION__, ret);

	signal_async(cb_result);
}

void _mc_client_cmd_reply_received_cb(const char *server_name, const char *request_id, int result_code, bundle *data, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	tc_user_data *_user_data = (tc_user_data *)user_data;

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if (_user_data != NULL) {
		_user_data->result = TRUE;
		_user_data->name = g_strdup(server_name);
		_user_data->request_id = g_strdup(request_id);
		_user_data->result_code = result_code;
		if (_user_data->name == NULL || _user_data->request_id == NULL)
			_user_data->result = FALSE;
	}

	signal_async(TRUE);
}

void _mc_client_custom_event_received_cb(const char *server_name, const char *request_id, const char *event, bundle *data, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	tc_user_data *_user_data = (tc_user_data *)user_data;

	if(strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	if(g_strcmp0(event, g_mc_test_event)) {
		FPRINTF("[%d:%s] wrong event [%s][%s]\\n", __LINE__, __FUNCTION__, event, g_mc_test_event);
		signal_async(FALSE);
		return;
	}

	if (_user_data != NULL) {
		_user_data->result = TRUE;
		_user_data->name = g_strdup(server_name);
		_user_data->request_id = g_strdup(request_id);
		if (_user_data->name == NULL || _user_data->request_id == NULL)
			_user_data->result = FALSE;
	}

	signal_async(TRUE);
}

void _mc_client_display_mode_ability_updated_cb(const char *server_name, unsigned int supported_modes, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if (strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	signal_async(_mc_get_display_mode_ability(supported_modes));
}

void _mc_client_display_rotation_ability_updated_cb(const char *server_name, unsigned int supported_rotations, void *user_data)
{
	FPRINTF("[%d:%s] invoked\\n", __LINE__, __FUNCTION__);

	if (strcmp(server_name, g_mc_test_appname)) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\\n", __LINE__, __FUNCTION__, server_name, g_mc_test_appname);
		return;
	}

	signal_async(_mc_get_display_rotation_ability(supported_rotations));
}
