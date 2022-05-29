//
// Copyright (c) 2020 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "tct_common.h"
#include "utc-media-controller-common.h"


//& set: MediaControllerServer
static mc_server_h g_mc_server = NULL;
static mc_client_h g_mc_client = NULL;
static char *g_mc_server_name = NULL;
static char *g_mc_client_name = NULL;

static mc_server_state_e g_mc_server_state = MC_SERVER_STATE_NONE;

static char *g_request_id = NULL;
static tc_user_data g_mc_custom_data = {NULL, NULL, FALSE};
static tc_user_data g_mc_reply_data = {NULL, NULL, FALSE};

static mc_error_e startup_ret = MEDIA_CONTROLLER_ERROR_NONE;

/**
 * @function		utc_mc_server_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_mc_server_startup(void)
{
	mc_error_e ret = MEDIA_CONTROLLER_ERROR_NONE;

	// start server app
	ret = mc_server_create(&g_mc_server);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE)
	{
		FPRINTF("[%s:%d] mc_server_create failed (code: %d)\\n", __FILE__, __LINE__, ret);
		startup_ret = ret;
		return;
	}

	g_request_id = NULL;

	return;
}

/**
 * @function		utc_mc_server_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_mc_server_cleanup(void)
{
	mc_server_destroy(g_mc_server);
	g_mc_server = NULL;

	if (g_mc_client)
		mc_client_destroy(g_mc_client);
	g_mc_client = NULL;

	g_free(g_mc_server_name);
	g_mc_server_name = NULL;

	g_free(g_mc_client_name);
	g_mc_client_name = NULL;

	g_free(g_request_id);
	g_request_id = NULL;

	_mc_release_tc_user_data(&g_mc_custom_data);
	_mc_release_tc_user_data(&g_mc_reply_data);

	return;
}

/**
 * @testcase		utc_mc_server_create_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_server_create()
 */
int utc_mc_server_create_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_destroy(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	g_mc_server = NULL;

	ret = mc_server_create(&g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mc_server_create_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_server_create()
 */
int utc_mc_server_create_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_create(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase		utc_mc_server_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_server_destroy()
 */
int utc_mc_server_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_destroy(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	g_mc_server = NULL;

	return 0;
}


/**
 * @testcase		utc_mc_server_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_server_destroy()
 */
int utc_mc_server_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_destroy(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playback_state_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_server_set_playback_state()
 */
int utc_mc_server_set_playback_state_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	const mc_playback_states_e playback_state = MC_PLAYBACK_STATE_PLAYING;

	ret = mc_server_set_playback_state(g_mc_server, playback_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_server_set_playback_state_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_server_set_playback_state()
 */
int utc_mc_server_set_playback_state_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	const mc_playback_states_e playback_state = MC_PLAYBACK_STATE_NONE-1;

	ret = mc_server_set_playback_state(NULL, playback_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_playback_state(g_mc_server, playback_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playback_position_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_server_set_playback_position()
 */
int utc_mc_server_set_playback_position_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned long long playback_position = 1000;

	ret = mc_server_set_playback_position(g_mc_server, playback_position);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_server_set_playback_position_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_server_set_playback_position()
 */
int utc_mc_server_set_playback_position_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned long long playback_position = 1000;

	ret = mc_server_set_playback_position(NULL, playback_position);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playback_content_type_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_server_set_playback_content_type()
 */
int utc_mc_server_set_playback_content_type_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_content_type(g_mc_server, g_mc_test_content_type);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playback_content_type_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_server_set_playback_content_type()
 */
int utc_mc_server_set_playback_content_type_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_content_type(NULL, g_mc_test_content_type);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_playback_content_type(g_mc_server, -1);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_content_age_rating_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_server_set_content_age_rating()
 */
int utc_mc_server_set_content_age_rating_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_content_age_rating(g_mc_server, g_mc_test_age_rating);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_content_age_rating_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_server_set_playback_content_type()
 */
int utc_mc_server_set_content_age_rating_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_content_age_rating(NULL, g_mc_test_age_rating);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_content_age_rating(g_mc_server, -1);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playlist_item_index_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_set_playlist_item_index()
 */
int utc_mc_server_set_playlist_item_index_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playlist_item_index(g_mc_server, g_mc_test_playlist_index);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playlist_item_index_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_set_playlist_item_index()
 */
int utc_mc_server_set_playlist_item_index_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playlist_item_index(NULL, g_mc_test_playlist_index);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_playlist_item_index(g_mc_server, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playlist_item_info_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_server_set_playlist_item_info()
 */
int utc_mc_server_set_playlist_item_info_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playlist_item_info(g_mc_server, g_mc_test_playlist_name, g_mc_test_playlist_index);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playlist_item_info_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_server_set_playlist_item_info()
 */
int utc_mc_server_set_playlist_item_info_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playlist_item_info(NULL, g_mc_test_playlist_name, g_mc_test_playlist_index);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_playlist_item_info(g_mc_server, NULL, g_mc_test_playlist_index);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_playlist_item_info(g_mc_server, g_mc_test_playlist_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_metadata_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_server_set_metadata()
 */
int utc_mc_server_set_metadata_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	const mc_meta_e metadata_attr = MC_META_MEDIA_TITLE;
	const char *metadata_value = "title";

	ret = mc_server_set_metadata(g_mc_server, metadata_attr, metadata_value);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_server_set_metadata_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_server_set_metadata()
 */
int utc_mc_server_set_metadata_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	const mc_meta_e metadata_attr = MC_META_MEDIA_TITLE;
	const char *metadata_value = "title";

	ret = mc_server_set_metadata(NULL, metadata_attr, metadata_value);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_metadata(g_mc_server, MC_META_MEDIA_TITLE-1, metadata_value);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_icon_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_server_set_icon()
 */
int utc_mc_server_set_icon_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_icon(g_mc_server, g_mc_test_icon_path);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_icon_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_server_set_icon()
 */
int utc_mc_server_set_icon_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_icon(NULL, g_mc_test_icon_path);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playback_ability_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_server_set_playback_ability()
 */
int utc_mc_server_set_playback_ability_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_ability(g_mc_server, MC_PLAYBACK_ACTION_PLAY, MC_ABILITY_SUPPORTED_YES);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playback_ability(g_mc_server, MC_PLAYBACK_ACTION_PAUSE, MC_ABILITY_SUPPORTED_NO);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playback_ability(g_mc_server, MC_PLAYBACK_ACTION_STOP, MC_ABILITY_SUPPORTED_YES);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playback_ability(g_mc_server, MC_PLAYBACK_ACTION_NEXT, MC_ABILITY_SUPPORTED_NO);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playback_ability(g_mc_server, MC_PLAYBACK_ACTION_PREV, MC_ABILITY_SUPPORTED_YES);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playback_ability(g_mc_server, MC_PLAYBACK_ACTION_FAST_FORWARD, MC_ABILITY_SUPPORTED_NO);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playback_ability(g_mc_server, MC_PLAYBACK_ACTION_REWIND, MC_ABILITY_SUPPORTED_YES);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playback_ability(g_mc_server, MC_PLAYBACK_ACTION_TOGGLE_PLAY_PAUSE, MC_ABILITY_SUPPORTED_NO);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playback_ability_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_server_set_playback_ability()
 */
int utc_mc_server_set_playback_ability_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_ability(NULL, MC_PLAYBACK_ACTION_PLAY, MC_ABILITY_SUPPORTED_YES);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_playback_ability(g_mc_server, -1, MC_ABILITY_SUPPORTED_YES);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_playback_ability(g_mc_server, MC_PLAYBACK_ACTION_PLAY, -1);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_playback_ability(g_mc_server, MC_PLAYBACK_ACTION_PLAY, MC_ABILITY_SUPPORTED_UNDECIDED);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_playback_ability_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_server_update_playback_ability()
 */
int utc_mc_server_update_playback_ability_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_register_ability(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_playback_ability_updated_cb(g_mc_client, _mc_client_playback_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_playback_ability(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_playback_ability_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_server_update_playback_ability()
 */
int utc_mc_server_update_playback_ability_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_update_playback_ability(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_shuffle_ability_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_server_set_shuffle_ability()
 */
int utc_mc_server_set_shuffle_ability_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_shuffle_ability_updated_cb(g_mc_client, _mc_client_shuffle_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_shuffle_ability(g_mc_server, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_shuffle_ability_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_server_set_shuffle_ability()
 */
int utc_mc_server_set_shuffle_ability_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_shuffle_ability(NULL, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_shuffle_ability(g_mc_server, -1);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_repeat_ability_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_server_set_repeat_ability()
 */
int utc_mc_server_set_repeat_ability_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_repeat_ability_updated_cb(g_mc_client, _mc_client_repeat_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_repeat_ability(g_mc_server, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_repeat_ability_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_server_set_repeat_ability()
 */
int utc_mc_server_set_repeat_ability_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_repeat_ability(NULL, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_repeat_ability(g_mc_server, -1);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_ability_support_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_set_ability_support()
 */
int utc_mc_server_set_ability_support_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int i = 0;
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_ability_support_updated_cb(g_mc_client, _mc_client_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	for (i = 0; i <= MC_ABILITY_SEARCH; i++) {
		ret = mc_server_set_ability_support(g_mc_server, i, g_mc_test_ability);
		assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
		assert_eq(wait_for_async(), TRUE);
	}

	return 0;
}

/**
 * @testcase		utc_mc_server_set_ability_support_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_set_ability_support()
 */
int utc_mc_server_set_ability_support_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_ability_support(NULL, MC_ABILITY_SHUFFLE, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_SHUFFLE, MC_ABILITY_SUPPORTED_UNDECIDED);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_playback_info_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_server_update_playback_info()
 */
int utc_mc_server_update_playback_info_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_playback_updated_cb(g_mc_client, _mc_client_playback_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playback_state(g_mc_server, g_mc_test_playback_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playback_position(g_mc_server, g_mc_test_playback_position);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playback_content_type(g_mc_server, g_mc_test_content_type);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_content_age_rating(g_mc_server, g_mc_test_age_rating);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playlist_item_info(g_mc_server, g_mc_test_playlist_name, g_mc_test_playlist_index);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_playback_info(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_playback_info_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_server_update_playback_info()
 */
int utc_mc_server_update_playback_info_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_update_playback_info(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_metadata_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_server_update_metadata()
 */
int utc_mc_server_update_metadata_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_metadata_updated_cb(g_mc_client, _mc_client_metadata_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_register_metadata(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_metadata_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_server_update_metadata()
 */
int utc_mc_server_update_metadata_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_update_metadata(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_shuffle_mode_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_server_update_shuffle_mode()
 */
int utc_mc_server_update_shuffle_mode_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_shuffle_mode_updated_cb(g_mc_client, _mc_client_shuffle_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_shuffle_mode(g_mc_server, g_mc_test_shuffle_mode);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_shuffle_mode_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_server_update_shuffle_mode()
 */
int utc_mc_server_update_shuffle_mode_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_update_shuffle_mode(NULL, g_mc_test_shuffle_mode);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_update_shuffle_mode(g_mc_server, -1);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_repeat_mode_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_server_update_repeat_mode()
 */
int utc_mc_server_update_repeat_mode_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_repeat_mode_updated_cb(g_mc_client, _mc_client_repeat_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_repeat_mode(g_mc_server, g_mc_test_repeat_mode);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_repeat_mode_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_server_update_repeat_mode()
 */
int utc_mc_server_update_repeat_mode_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_update_repeat_mode(NULL, g_mc_test_repeat_mode);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_update_repeat_mode(g_mc_server, -1);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_subtitles_enabled_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_update_subtitles_enabled()
 */
int utc_mc_server_update_subtitles_enabled_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_subtitles_updated_cb(g_mc_client, _mc_client_bool_attribute_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_subtitles_enabled(g_mc_server, true);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_subtitles_enabled_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_update_subtitles_enabled()
 */
int utc_mc_server_update_subtitles_enabled_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_update_subtitles_enabled(NULL, true);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_360_mode_enabled_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_update_360_mode_enabled()
 */
int utc_mc_server_update_360_mode_enabled_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_360_mode_updated_cb(g_mc_client, _mc_client_bool_attribute_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_360_mode_enabled(g_mc_server, true);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;;
}

/**
 * @testcase		utc_mc_server_update_360_mode_enabled_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_update_360_mode_enabled()
 */
int utc_mc_server_update_360_mode_enabled_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_update_360_mode_enabled(NULL, true);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_display_mode_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_update_display_mode()
 */
int utc_mc_server_update_display_mode_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_display_mode_updated_cb(g_mc_client, _mc_client_display_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_display_mode(g_mc_server, MC_DISPLAY_MODE_FULL_SCREEN);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_display_mode_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_update_display_mode()
 */
int utc_mc_server_update_display_mode_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_update_display_mode(NULL, MC_DISPLAY_MODE_FULL_SCREEN);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_display_rotation_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_update_display_rotation()
 */
int utc_mc_server_update_display_rotation_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_display_rotation_updated_cb(g_mc_client, _mc_client_display_rotation_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_display_rotation(g_mc_server, MC_DISPLAY_ROTATION_270);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);


	return 0;
}

/**
 * @testcase		utc_mc_server_update_display_rotation_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_update_display_rotation()
 */
int utc_mc_server_update_display_rotation_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_update_display_rotation(NULL, MC_DISPLAY_ROTATION_270);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playback_position_cmd_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_set_playback_position_cmd_received_cb()
 */
int utc_mc_server_set_playback_position_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_position_cmd_received_cb(g_mc_server, _mc_server_playback_position_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playback_position_cmd_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_set_playback_position_cmd_received_cb()
 */
int utc_mc_server_set_playback_position_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_position_cmd_received_cb(NULL, _mc_server_playback_position_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_playback_position_cmd_received_cb(g_mc_server, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_playback_position_cmd_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_unset_playback_position_cmd_received_cb()
 */
int utc_mc_server_unset_playback_position_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_position_cmd_received_cb(g_mc_server, _mc_server_playback_position_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_playback_position_cmd_received_cb(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_playback_position_cmd_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_unset_playback_position_cmd_received_cb()
 */
int utc_mc_server_unset_playback_position_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_position_cmd_received_cb(g_mc_server, _mc_server_playback_position_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_playback_position_cmd_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_shuffle_mode_cmd_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_set_shuffle_mode_cmd_received_cb()
 */
int utc_mc_server_set_shuffle_mode_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_shuffle_mode_cmd_received_cb(g_mc_server, _mc_server_shuffle_mode_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_shuffle_mode_cmd_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_set_shuffle_mode_cmd_received_cb()
 */
int utc_mc_server_set_shuffle_mode_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_shuffle_mode_cmd_received_cb(NULL, _mc_server_shuffle_mode_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_shuffle_mode_cmd_received_cb(g_mc_server, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_shuffle_mode_cmd_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_unset_shuffle_mode_cmd_received_cb()
 */
int utc_mc_server_unset_shuffle_mode_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_shuffle_mode_cmd_received_cb(g_mc_server, _mc_server_shuffle_mode_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_shuffle_mode_cmd_received_cb(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_shuffle_mode_cmd_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_unset_shuffle_mode_cmd_received_cb()
 */
int utc_mc_server_unset_shuffle_mode_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_shuffle_mode_cmd_received_cb(g_mc_server, _mc_server_shuffle_mode_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_shuffle_mode_cmd_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_repeat_mode_cmd_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_set_repeat_mode_cmd_received_cb()
 */
int utc_mc_server_set_repeat_mode_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_repeat_mode_cmd_received_cb(g_mc_server, _mc_server_repeat_mode_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_repeat_mode_cmd_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_set_repeat_mode_cmd_received_cb()
 */
int utc_mc_server_set_repeat_mode_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_repeat_mode_cmd_received_cb(NULL, _mc_server_repeat_mode_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_repeat_mode_cmd_received_cb(g_mc_server, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_repeat_mode_cmd_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_unset_repeat_mode_cmd_received_cb()
 */
int utc_mc_server_unset_repeat_mode_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_repeat_mode_cmd_received_cb(g_mc_server, _mc_server_repeat_mode_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_repeat_mode_cmd_received_cb(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_repeat_mode_cmd_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_unset_repeat_mode_cmd_received_cb()
 */
int utc_mc_server_unset_repeat_mode_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_repeat_mode_cmd_received_cb(g_mc_server, _mc_server_repeat_mode_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_repeat_mode_cmd_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playback_action_cmd_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_set_playback_action_cmd_received_cb()
 */
int utc_mc_server_set_playback_action_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_action_cmd_received_cb(g_mc_server, _mc_server_playback_action_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playback_action_cmd_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_set_playback_action_cmd_received_cb()
 */
int utc_mc_server_set_playback_action_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_action_cmd_received_cb(NULL, _mc_server_playback_action_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_playback_action_cmd_received_cb(g_mc_server, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_playback_action_cmd_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_unset_playback_action_cmd_received_cb()
 */
int utc_mc_server_unset_playback_action_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_action_cmd_received_cb(g_mc_server, _mc_server_playback_action_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_playback_action_cmd_received_cb(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_playback_action_cmd_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_unset_playback_action_received_cb()
 */
int utc_mc_server_unset_playback_action_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_action_cmd_received_cb(g_mc_server, _mc_server_playback_action_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_playback_action_cmd_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playlist_cmd_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_set_playlist_cmd_received_cb()
 */
int utc_mc_server_set_playlist_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playlist_cmd_received_cb(g_mc_server, _mc_server_playlist_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_playlist_cmd_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_set_playlist_cmd_received_cb()
 */
int utc_mc_server_set_playlist_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playlist_cmd_received_cb(NULL, _mc_server_playlist_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_playlist_cmd_received_cb(g_mc_server, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_playlist_cmd_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_unset_playlist_cmd_received_cb()
 */
int utc_mc_server_unset_playlist_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playlist_cmd_received_cb(g_mc_server, _mc_server_playlist_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_playlist_cmd_received_cb(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_playlist_cmd_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_unset_playlist_cmd_received_cb()
 */
int utc_mc_server_unset_playlist_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playlist_cmd_received_cb(g_mc_server, _mc_server_playlist_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_playlist_cmd_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_custom_cmd_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_set_custom_cmd_received_cb()
 */
int utc_mc_server_set_custom_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_custom_cmd_received_cb(g_mc_server, _mc_server_custom_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_custom_cmd_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_set_custom_cmd_received_cb()
 */
int utc_mc_server_set_custom_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_custom_cmd_received_cb(NULL, _mc_server_custom_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_custom_cmd_received_cb(g_mc_server, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_custom_cmd_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_unset_custom_cmd_received_cb()
 */
int utc_mc_server_unset_custom_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_custom_cmd_received_cb(g_mc_server, _mc_server_custom_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_custom_cmd_received_cb(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_custom_cmd_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_unset_custom_cmd_received_cb()
 */
int utc_mc_server_unset_custom_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_custom_cmd_received_cb(g_mc_server, _mc_server_custom_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_custom_cmd_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_subtitles_cmd_received_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_set_subtitles_cmd_received_cb()
 */
int utc_mc_server_set_subtitles_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_subtitles_cmd_received_cb(g_mc_server, _mc_server_enable_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_subtitles_cmd_received_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_set_subtitles_cmd_received_cb()
 */
int utc_mc_server_set_subtitles_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_subtitles_cmd_received_cb(g_mc_server, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_subtitles_cmd_received_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_unset_subtitles_cmd_received_cb()
 */
int utc_mc_server_unset_subtitles_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_subtitles_cmd_received_cb(g_mc_server, _mc_server_enable_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_subtitles_cmd_received_cb(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_subtitles_cmd_received_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_unset_subtitles_cmd_received_cb()
 */
int utc_mc_server_unset_subtitles_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_subtitles_cmd_received_cb(g_mc_server, _mc_server_enable_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_subtitles_cmd_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_360_mode_cmd_received_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_set_360_mode_cmd_received_cb()
 */
int utc_mc_server_set_360_mode_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_360_mode_cmd_received_cb(g_mc_server, _mc_server_enable_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_360_mode_cmd_received_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_set_360_mode_cmd_received_cb()
 */
int utc_mc_server_set_360_mode_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_360_mode_cmd_received_cb(g_mc_server, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_360_mode_cmd_received_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_unset_360_mode_cmd_received_cb()
 */
int utc_mc_server_unset_360_mode_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_360_mode_cmd_received_cb(g_mc_server, _mc_server_enable_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_360_mode_cmd_received_cb(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_360_mode_cmd_received_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_unset_360_mode_cmd_received_cb()
 */
int utc_mc_server_unset_360_mode_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_360_mode_cmd_received_cb(g_mc_server, _mc_server_enable_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_360_mode_cmd_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_display_mode_cmd_received_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_set_display_mode_cmd_received_cb()
 */
int utc_mc_server_set_display_mode_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_display_mode_cmd_received_cb(g_mc_server, _mc_server_display_mode_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_display_mode_cmd_received_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_set_display_mode_cmd_received_cb()
 */
int utc_mc_server_set_display_mode_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_display_mode_cmd_received_cb(g_mc_server, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_display_mode_cmd_received_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_unset_display_mode_cmd_received_cb()
 */
int utc_mc_server_unset_display_mode_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_display_mode_cmd_received_cb(g_mc_server, _mc_server_display_mode_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_display_mode_cmd_received_cb(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_display_mode_cmd_received_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_unset_display_mode_cmd_received_cb()
 */
int utc_mc_server_unset_display_mode_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_display_mode_cmd_received_cb(g_mc_server, _mc_server_display_mode_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_display_mode_cmd_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_display_rotation_cmd_received_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_set_display_rotation_cmd_received_cb()
 */
int utc_mc_server_set_display_rotation_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_display_rotation_cmd_received_cb(g_mc_server, _mc_server_display_rotation_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_display_rotation_cmd_received_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_set_display_rotation_cmd_received_cb()
 */
int utc_mc_server_set_display_rotation_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_display_rotation_cmd_received_cb(g_mc_server, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_display_rotation_cmd_received_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_unset_display_rotation_cmd_received_cb()
 */
int utc_mc_server_unset_display_rotation_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_display_rotation_cmd_received_cb(g_mc_server, _mc_server_display_rotation_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_display_rotation_cmd_received_cb(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_display_rotation_cmd_received_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_unset_display_rotation_cmd_received_cb()
 */
int utc_mc_server_unset_display_rotation_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_display_rotation_cmd_received_cb(g_mc_server, _mc_server_display_rotation_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_display_rotation_cmd_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_display_mode_ability_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_set_display_mode_ability()
 */
int utc_mc_server_set_display_mode_ability_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_display_mode_ability(g_mc_server,
		MC_DISPLAY_MODE_LETTER_BOX | MC_DISPLAY_MODE_ORIGIN_SIZE | MC_DISPLAY_MODE_FULL_SCREEN | MC_DISPLAY_MODE_CROPPED_FULL, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_display_mode_ability_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_set_display_mode_ability()
 */
int utc_mc_server_set_display_mode_ability_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_display_mode_ability(NULL,
		MC_DISPLAY_MODE_LETTER_BOX | MC_DISPLAY_MODE_ORIGIN_SIZE | MC_DISPLAY_MODE_FULL_SCREEN | MC_DISPLAY_MODE_CROPPED_FULL, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_display_mode_ability(g_mc_server,
		MC_DISPLAY_MODE_LETTER_BOX | MC_DISPLAY_MODE_ORIGIN_SIZE | MC_DISPLAY_MODE_FULL_SCREEN | MC_DISPLAY_MODE_CROPPED_FULL, -1);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_display_rotation_ability_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_server_set_display_rotation_ability()
 */
int utc_mc_server_set_display_rotation_ability_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	ret = mc_server_set_display_rotation_ability(g_mc_server,
		MC_DISPLAY_ROTATION_NONE | MC_DISPLAY_ROTATION_90 | MC_DISPLAY_ROTATION_180 | MC_DISPLAY_ROTATION_270, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_display_rotation_ability_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_server_set_display_rotation_ability()
 */
int utc_mc_server_set_display_rotation_ability_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_display_rotation_ability(NULL,
		MC_DISPLAY_ROTATION_NONE | MC_DISPLAY_ROTATION_90 | MC_DISPLAY_ROTATION_180 | MC_DISPLAY_ROTATION_270, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_display_rotation_ability(g_mc_server,
		MC_DISPLAY_ROTATION_NONE | MC_DISPLAY_ROTATION_90 | MC_DISPLAY_ROTATION_180 | MC_DISPLAY_ROTATION_270, -1);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_send_cmd_reply_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_send_cmd_reply()
 */
int utc_mc_server_send_cmd_reply_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int idx = 0;

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_CLIENT_CUSTOM, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playback_state(g_mc_server, MC_PLAYBACK_STATE_PLAYING);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_playback_info(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_cmd_reply_received_cb(g_mc_client, _mc_client_cmd_reply_received_cb, &g_mc_reply_data);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_custom_cmd_received_cb(g_mc_server, _mc_server_custom_cmd_received_cb, &g_mc_custom_data);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	for (idx = 0; idx < g_mc_test_result_codes_cnt; idx++) {
		ret = mc_client_send_custom_cmd(g_mc_client, g_mc_server_name, g_mc_test_cmd, NULL, &g_request_id);
		assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
		assert_eq(wait_for_async(), TRUE);

		assert_eq(g_mc_custom_data.result, TRUE);
		assert_eq(strcmp(g_mc_custom_data.name, g_mc_test_appname), 0);
		assert_eq(strcmp(g_mc_custom_data.request_id, g_request_id), 0);

		ret = mc_server_send_cmd_reply(g_mc_server, g_mc_custom_data.name, g_mc_custom_data.request_id, g_mc_test_result_codes[idx], NULL);
		assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
		assert_eq(wait_for_async(), TRUE);

		assert_eq(g_mc_reply_data.result, TRUE);
		assert_eq(g_mc_reply_data.result_code, g_mc_test_result_codes[idx]);
		assert_eq(strcmp(g_mc_reply_data.name, g_mc_test_appname), 0);
		assert_eq(strcmp(g_mc_reply_data.request_id, g_request_id), 0);

		/* release allocated memory for loop */
		_mc_release_tc_user_data(&g_mc_custom_data);
		_mc_release_tc_user_data(&g_mc_reply_data);
		g_free(g_request_id);
		g_request_id = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_mc_server_send_cmd_reply_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_send_cmd_reply()
 */
int utc_mc_server_send_cmd_reply_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_send_cmd_reply(NULL, g_mc_test_appname, g_request_id, g_mc_test_result_code, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_send_cmd_reply(g_mc_server, NULL, g_request_id, g_mc_test_result_code, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_send_cmd_reply(g_mc_server, g_mc_test_appname, NULL, g_mc_test_result_code, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_create_playlist_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_create_playlist()
 */
int utc_mc_server_create_playlist_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = mc_server_create_playlist(g_mc_server, g_mc_test_playlist_name, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_create_playlist_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_create_playlist()
 */
int utc_mc_server_create_playlist_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_create_playlist(g_mc_server, g_mc_test_playlist_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_add_item_to_playlist_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_add_item_to_playlist()
 */
int utc_mc_server_add_item_to_playlist_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = mc_server_create_playlist(g_mc_server, g_mc_test_playlist_name, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_TITLE, g_mc_test_playlist_metadata[0]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_ARTIST, g_mc_test_playlist_metadata[1]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_ALBUM, g_mc_test_playlist_metadata[2]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_AUTHOR, g_mc_test_playlist_metadata[3]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_GENRE, g_mc_test_playlist_metadata[4]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_DURATION, g_mc_test_playlist_metadata[5]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_DATE, g_mc_test_playlist_metadata[6]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_COPYRIGHT, g_mc_test_playlist_metadata[7]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_DESCRIPTION, g_mc_test_playlist_metadata[8]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_TRACK_NUM, g_mc_test_playlist_metadata[9]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_PICTURE, g_mc_test_playlist_metadata[10]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, "2", MC_META_MEDIA_TITLE, "title_2");
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_add_item_to_playlist_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_add_item_to_playlist()
 */
int utc_mc_server_add_item_to_playlist_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = mc_server_create_playlist(g_mc_server, g_mc_test_playlist_name, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, NULL, MC_META_MEDIA_TITLE, g_mc_test_playlist_metadata[0]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_playlist_done_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_update_playlist_done()
 */
int utc_mc_server_update_playlist_done_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_playlist_updated_cb(g_mc_client, _mc_client_playlist_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_create_playlist(g_mc_server, g_mc_test_playlist_name, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_playlist_done(g_mc_server, playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_TITLE, g_mc_test_playlist_metadata[0]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_ARTIST, g_mc_test_playlist_metadata[1]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_ALBUM, g_mc_test_playlist_metadata[2]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_AUTHOR, g_mc_test_playlist_metadata[3]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_GENRE, g_mc_test_playlist_metadata[4]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_DURATION, g_mc_test_playlist_metadata[5]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_DATE, g_mc_test_playlist_metadata[6]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_COPYRIGHT, g_mc_test_playlist_metadata[7]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_DESCRIPTION, g_mc_test_playlist_metadata[8]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_TRACK_NUM, g_mc_test_playlist_metadata[9]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	ret = mc_server_add_item_to_playlist(g_mc_server, playlist, g_mc_test_playlist_idx, MC_META_MEDIA_PICTURE, g_mc_test_playlist_metadata[10]);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_playlist_done(g_mc_server, playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	assert_eq(wait_for_async(), TRUE);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_update_playlist_done_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_update_playlist_done()
 */
int utc_mc_server_update_playlist_done_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = mc_server_create_playlist(g_mc_server, g_mc_test_playlist_name, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_playlist_done(g_mc_server, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_delete_playlist_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_delete_playlist()
 */
int utc_mc_server_delete_playlist_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_delete_playlist(g_mc_server, playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_delete_playlist_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_delete_playlist()
 */
int utc_mc_server_delete_playlist_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = mc_server_create_playlist(g_mc_server, g_mc_test_playlist_name, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_delete_playlist(g_mc_server, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_foreach_playlist_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_foreach_playlist()
 */
int utc_mc_server_foreach_playlist_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;
	gboolean cb_result = FALSE;

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_foreach_playlist(g_mc_server, _mc_playlist_list_cb, &cb_result);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	assert_eq(cb_result, TRUE);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_foreach_playlist_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_foreach_playlist()
 */
int utc_mc_server_foreach_playlist_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = mc_server_create_playlist(g_mc_server, g_mc_test_playlist_name, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_foreach_playlist(g_mc_server, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_foreach_client_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_foreach_client()
 */
int utc_mc_server_foreach_client_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_foreach_client(g_mc_client, _mc_activated_client_cb, &g_mc_client_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_neq(g_mc_client_name, NULL);

	return 0;
}

/**
 * @testcase		utc_mc_server_foreach_client_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_foreach_client()
 */
int utc_mc_server_foreach_client_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_foreach_client(NULL, _mc_activated_client_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_foreach_client(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_event_reply_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_set_event_reply_received_cb()
 */
int utc_mc_server_set_event_reply_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_event_reply_received_cb(g_mc_server, _mc_server_event_reply_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_event_reply_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_set_event_reply_received_cb()
 */
int utc_mc_server_set_event_reply_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_event_reply_received_cb(NULL, _mc_server_event_reply_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_event_reply_received_cb(g_mc_server, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_event_reply_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_server_unset_event_reply_received_cb()
 */
int utc_mc_server_unset_event_reply_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_event_reply_received_cb(g_mc_server, _mc_server_event_reply_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_event_reply_received_cb(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_event_reply_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_unset_event_reply_received_cb()
 */
int utc_mc_server_unset_event_reply_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_unset_event_reply_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_send_custom_event_p
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_send_custom_event()
 */
int utc_mc_server_send_custom_event_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_custom_event_received_cb(g_mc_client, _mc_client_custom_event_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_foreach_client(g_mc_server, _mc_activated_client_cb, &g_mc_client_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_neq(g_mc_client_name, NULL);

	ret = mc_server_send_custom_event(g_mc_server, g_mc_client_name, g_mc_test_event, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	ret = mc_client_unset_custom_event_received_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_send_custom_event_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_server_send_custom_event()
 */
int utc_mc_server_send_custom_event_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_send_custom_event(NULL, NULL, g_mc_test_event, NULL, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_send_custom_event(g_mc_server, NULL, g_mc_test_event, NULL, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_search_cmd_received_cb_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_server_set_search_cmd_received_cb()
 */
int utc_mc_server_set_search_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_search_cmd_received_cb(g_mc_server, _mc_server_search_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_set_search_cmd_received_cb_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_server_set_search_cmd_received_cb()
 */
int utc_mc_server_set_search_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_search_cmd_received_cb(NULL, _mc_server_search_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_server_set_search_cmd_received_cb(g_mc_server, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_search_cmd_received_cb_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_server_unset_search_cmd_received_cb()
 */
int utc_mc_server_unset_search_cmd_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_search_cmd_received_cb(g_mc_server, _mc_server_search_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_search_cmd_received_cb(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_server_unset_search_cmd_received_cb_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_server_unset_search_cmd_received_cb()
 */
int utc_mc_server_unset_search_cmd_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_search_cmd_received_cb(g_mc_server, _mc_server_search_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_unset_search_cmd_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}
