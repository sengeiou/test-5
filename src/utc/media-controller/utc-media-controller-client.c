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


//& set: MediaControllerClient
static mc_server_h g_mc_server = NULL;
static mc_client_h g_mc_client = NULL;
static char *g_mc_server_name = NULL;
static char *g_mc_client_name = NULL;

static mc_server_state_e g_mc_server_state = MC_SERVER_STATE_NONE;
static mc_search_h g_mc_search = NULL;

static char *g_request_id = NULL;
static tc_user_data g_mc_custom_data = {NULL, NULL, FALSE};
static tc_user_data g_mc_reply_data = {NULL, NULL, FALSE};

static mc_error_e startup_ret = MEDIA_CONTROLLER_ERROR_NONE;

/**
 * @function		utc_mc_client_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_mc_client_startup(void)
{
	mc_error_e ret = MEDIA_CONTROLLER_ERROR_NONE;

	// start client app
	ret = mc_client_create(&g_mc_client);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE)
	{
		FPRINTF("[%s:%d] mc_client_create failed (code: %d)\\n", __FILE__, __LINE__, ret);
		startup_ret = ret;
		return;
	}

	g_request_id = NULL;

	return;
}

static int __launch_mc_server(void)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_create(&g_mc_server);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_create failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_set_playback_state(g_mc_server, MC_PLAYBACK_STATE_PLAYING);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_state failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_update_playback_info(g_mc_server);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_update_playback_info failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_client_get_latest_server_info failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	return MEDIA_CONTROLLER_ERROR_NONE;
}

static int __update_mc_server_info(mc_playback_h *playback)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_server_set_playback_state(g_mc_server, MC_PLAYBACK_STATE_PAUSED);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_state failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_set_playback_position(g_mc_server, 12345);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_position failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_set_playback_content_type(g_mc_server, MC_CONTENT_TYPE_OTHER);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_content_type failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_set_content_age_rating(g_mc_server, MC_CONTENT_RATING_7_PLUS);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_content_age_rating failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_set_playlist_item_info(g_mc_server, g_mc_test_playlist_name, g_mc_test_playlist_index);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playlist_item_info failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_server_update_playback_info(g_mc_server);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_update_playback_info failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	ret = mc_client_get_server_playback_info(g_mc_client, g_mc_server_name, playback);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_client_get_server_playback_info failed (code: %d)\\n", __FILE__, __LINE__, ret);
		return ret;
	}

	return MEDIA_CONTROLLER_ERROR_NONE;
}

/**
 * @function		utc_mc_client_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_mc_client_cleanup(void)
{
	if (g_mc_server) {
		mc_server_destroy(g_mc_server);
		g_mc_server = NULL;
	}

	mc_client_destroy(g_mc_client);
	g_mc_client = NULL;

	g_free(g_mc_server_name);
	g_mc_server_name = NULL;

	g_free(g_mc_client_name);
	g_mc_client_name = NULL;

	g_free(g_request_id);
	g_request_id = NULL;

	if (g_mc_search) {
		mc_search_destroy(g_mc_search);
		g_mc_search = NULL;
	}

	_mc_release_tc_user_data(&g_mc_custom_data);
	_mc_release_tc_user_data(&g_mc_reply_data);

	return;
}

/**
 * @testcase		utc_mc_client_create_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_create()
 */
int utc_mc_client_create_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_destroy(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	g_mc_client = NULL;

	ret = mc_client_create(&g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_create_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_create()
 */
int utc_mc_client_create_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_destroy(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	g_mc_client = NULL;

	ret = mc_client_create(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase		utc_mc_client_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_destroy()
 */
int utc_mc_client_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_destroy(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	g_mc_client = NULL;

	return 0;
}


/**
 * @testcase		utc_mc_client_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_destroy()
 */
int utc_mc_client_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_destroy(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_server_updated_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_set_server_updated_cb()
 */
int utc_mc_client_set_server_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_server_updated_cb(g_mc_client, _mc_client_server_state_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_destroy(g_mc_server);
	g_mc_server = NULL;
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_server_updated_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_set_server_updated_cb()
 */
int utc_mc_client_set_server_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_server_updated_cb(NULL, _mc_client_server_state_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_server_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_server_updated_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_unset_server_updated_cb()
 */
int utc_mc_client_unset_server_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_server_updated_cb(g_mc_client, _mc_client_server_state_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_server_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_unset_server_updated_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_unset_server_updated_cb()
 */
int utc_mc_client_unset_server_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_server_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_playback_updated_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_set_playback_updated_cb()
 */
int utc_mc_client_set_playback_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_playback_updated_cb(g_mc_client, _mc_client_playback_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_set_playback_updated_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_set_playback_updated_cb()
 */
int utc_mc_client_set_playback_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_playback_updated_cb(NULL, _mc_client_playback_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_playback_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_playback_updated_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_unset_playback_updated_cb()
 */
int utc_mc_client_unset_playback_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_playback_updated_cb(g_mc_client, _mc_client_playback_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_playback_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_unset_playback_updated_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_unset_playback_updated_cb()
 */
int utc_mc_client_unset_playback_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_playback_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_metadata_updated_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_set_metadata_updated_cb()
 */
int utc_mc_client_set_metadata_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_metadata_updated_cb(g_mc_client, _mc_client_metadata_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_register_metadata(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_metadata_updated_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_set_metadata_updated_cb()
 */
int utc_mc_client_set_metadata_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_metadata_updated_cb(NULL, _mc_client_metadata_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_metadata_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_metadata_updated_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_unset_metadata_updated_cb()
 */
int utc_mc_client_unset_metadata_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_metadata_updated_cb(g_mc_client, _mc_client_metadata_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_metadata_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_unset_metadata_updated_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_unset_metadata_updated_cb()
 */
int utc_mc_client_unset_metadata_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_metadata_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_shuffle_mode_updated_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_set_shuffle_mode_updated_cb()
 */
int utc_mc_client_set_shuffle_mode_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_shuffle_mode_updated_cb(g_mc_client, _mc_client_shuffle_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_set_shuffle_mode_updated_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_set_shuffle_mode_updated_cb()
 */
int utc_mc_client_set_shuffle_mode_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_shuffle_mode_updated_cb(NULL, _mc_client_shuffle_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_shuffle_mode_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_shuffle_mode_updated_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_unset_shuffle_mode_updated_cb()
 */
int utc_mc_client_unset_shuffle_mode_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_shuffle_mode_updated_cb(g_mc_client, _mc_client_shuffle_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_shuffle_mode_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_unset_shuffle_mode_updated_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_unset_shuffle_mode_updated_cb()
 */
int utc_mc_client_unset_shuffle_mode_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_shuffle_mode_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_repeat_mode_updated_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_set_repeat_mode_updated_cb()
 */
int utc_mc_client_set_repeat_mode_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_repeat_mode_updated_cb(g_mc_client, _mc_client_repeat_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_set_repeat_mode_updated_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_set_repeat_mode_updated_cb()
 */
int utc_mc_client_set_repeat_mode_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_repeat_mode_updated_cb(NULL, _mc_client_repeat_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_repeat_mode_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_repeat_mode_updated_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_unset_repeat_mode_updated_cb()
 */
int utc_mc_client_unset_repeat_mode_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_repeat_mode_updated_cb(g_mc_client, _mc_client_repeat_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_repeat_mode_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_unset_repeat_mode_updated_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_unset_repeat_mode_updated_cb()
 */
int utc_mc_client_unset_repeat_mode_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_repeat_mode_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_playback_ability_updated_cb_p
 * @since_tizen		5.0
 * @description		Positive test case of utc_mc_client_set_playback_ability_updated_cb()
 */
int utc_mc_client_set_playback_ability_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_playback_ability_updated_cb(g_mc_client, _mc_client_playback_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_set_playback_ability_updated_cb_n
 * @since_tizen		5.0
 * @description		Negative test case of utc_mc_client_set_playback_ability_updated_cb()
 */
int utc_mc_client_set_playback_ability_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_playback_ability_updated_cb(NULL, _mc_client_playback_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_playback_ability_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_playback_ability_updated_cb_p
 * @since_tizen		5.0
 * @description		Positive test case of utc_mc_client_unset_playback_ability_updated_cb()
 */
int utc_mc_client_unset_playback_ability_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_playback_ability_updated_cb(g_mc_client, _mc_client_playback_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_playback_ability_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_unset_playback_ability_updated_cb_n
 * @since_tizen		5.0
 * @description		Negative test case of utc_mc_client_unset_playback_ability_updated_cb()
 */
int utc_mc_client_unset_playback_ability_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_playback_ability_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_shuffle_ability_updated_cb_p
 * @since_tizen		5.0
 * @description		Positive test case of utc_mc_client_set_shuffle_ability_updated_cb()
 */
int utc_mc_client_set_shuffle_ability_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_shuffle_ability_updated_cb(g_mc_client, _mc_client_shuffle_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_set_shuffle_ability_updated_cb_n
 * @since_tizen		5.0
 * @description		Negative test case of utc_mc_client_set_shuffle_ability_updated_cb()
 */
int utc_mc_client_set_shuffle_ability_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_shuffle_ability_updated_cb(NULL, _mc_client_shuffle_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_shuffle_ability_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_shuffle_ability_updated_cb_p
 * @since_tizen		5.0
 * @description		Positive test case of utc_mc_client_unset_shuffle_ability_updated_cb()
 */
int utc_mc_client_unset_shuffle_ability_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_shuffle_ability_updated_cb(g_mc_client, _mc_client_shuffle_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_shuffle_ability_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_unset_shuffle_ability_updated_cb_n
 * @since_tizen		5.0
 * @description		Negative test case of utc_mc_client_unset_shuffle_ability_updated_cb()
 */
int utc_mc_client_unset_shuffle_ability_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_shuffle_ability_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_repeat_ability_updated_cb_p
 * @since_tizen		5.0
 * @description		Positive test case of utc_mc_client_set_repeat_ability_updated_cb()
 */
int utc_mc_client_set_repeat_ability_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_repeat_ability_updated_cb(g_mc_client, _mc_client_repeat_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_repeat_ability_updated_cb_n
 * @since_tizen		5.0
 * @description		Negative test case of utc_mc_client_set_repeat_ability_updated_cb()
 */
int utc_mc_client_set_repeat_ability_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_repeat_ability_updated_cb(NULL, _mc_client_repeat_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_repeat_ability_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_repeat_ability_updated_cb_p
 * @since_tizen		5.0
 * @description		Positive test case of utc_mc_client_unset_repeat_ability_updated_cb()
 */
int utc_mc_client_unset_repeat_ability_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_repeat_ability_updated_cb(g_mc_client, _mc_client_repeat_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_repeat_ability_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_unset_repeat_ability_updated_cb_n
 * @since_tizen		5.0
 * @description		Negative test case of utc_mc_client_unset_repeat_ability_updated_cb()
 */
int utc_mc_client_unset_repeat_ability_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_repeat_ability_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_ability_support_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of utc_mc_client_set_ability_support_updated_cb()
 */
int utc_mc_client_set_ability_support_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_ability_support_updated_cb(g_mc_client, _mc_client_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_ability_support_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of utc_mc_client_set_ability_support_updated_cb()
 */
int utc_mc_client_set_ability_support_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_ability_support_updated_cb(NULL, _mc_client_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_ability_support_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_ability_support_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of utc_mc_client_unset_ability_support_updated_cb()
 */
int utc_mc_client_unset_ability_support_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_ability_support_updated_cb(g_mc_client, _mc_client_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_ability_support_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_unset_ability_support_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of utc_mc_client_unset_ability_support_updated_cb()
 */
int utc_mc_client_unset_ability_support_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_ability_support_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_display_mode_ability_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_set_display_mode_ability_updated_cb()
 */
int utc_mc_client_set_display_mode_ability_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_display_mode_ability_updated_cb(g_mc_client, _mc_client_display_mode_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_display_mode_ability_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_set_display_mode_ability_updated_cb()
 */
int utc_mc_client_set_display_mode_ability_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_display_mode_ability_updated_cb(NULL, _mc_client_display_mode_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_display_mode_ability_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_display_mode_ability_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_unset_display_mode_ability_updated_cb()
 */
int utc_mc_client_unset_display_mode_ability_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_display_mode_ability_updated_cb(g_mc_client, _mc_client_display_mode_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_ability_support_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_display_mode_ability_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_unset_display_mode_ability_updated_cb()
 */
int utc_mc_client_unset_display_mode_ability_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_ability_support_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_display_rotation_ability_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_set_display_rotation_ability_updated_cb()
 */
int utc_mc_client_set_display_rotation_ability_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_display_rotation_ability_updated_cb(g_mc_client, _mc_client_display_rotation_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_display_rotation_ability_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_set_display_rotation_ability_updated_cb()
 */
int utc_mc_client_set_display_rotation_ability_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_display_rotation_ability_updated_cb(NULL, _mc_client_display_rotation_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_display_rotation_ability_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_display_rotation_ability_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_unset_display_rotation_ability_updated_cb()
 */
int utc_mc_client_unset_display_rotation_ability_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_display_rotation_ability_updated_cb(g_mc_client, _mc_client_display_rotation_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_display_rotation_ability_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_display_rotation_ability_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_unset_display_rotation_ability_updated_cb()
 */
int utc_mc_client_unset_display_rotation_ability_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_display_rotation_ability_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_playlist_updated_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_set_playlist_updated_cb()
 */
int utc_mc_client_set_playlist_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_playlist_updated_cb(g_mc_client, _mc_client_playlist_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_playlist_updated_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_set_playlist_updated_cb()
 */
int utc_mc_client_set_playlist_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_playlist_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_playlist_updated_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_unset_playlist_updated_cb()
 */
int utc_mc_client_unset_playlist_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_playlist_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_playlist_updated_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_unset_playlist_updated_cb()
 */
int utc_mc_client_unset_playlist_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_playlist_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_cmd_reply_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_set_cmd_reply_received_cb()
 */
int utc_mc_client_set_cmd_reply_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_CLIENT_CUSTOM, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_cmd_reply_received_cb(g_mc_client, _mc_client_cmd_reply_received_cb, &g_mc_reply_data);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_custom_cmd_received_cb(g_mc_server, _mc_server_custom_cmd_received_cb, &g_mc_custom_data);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_custom_cmd(g_mc_client, g_mc_server_name, g_mc_test_cmd, NULL, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	assert_eq(g_mc_custom_data.result, TRUE);
	assert_eq(strcmp(g_mc_custom_data.name, g_mc_test_appname), 0);
	assert_eq(strcmp(g_mc_custom_data.request_id, g_request_id), 0);

	ret = mc_server_send_cmd_reply(g_mc_server, g_mc_custom_data.name, g_mc_custom_data.request_id, g_mc_test_result_code, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	assert_eq(g_mc_reply_data.result, TRUE);
	assert_eq(strcmp(g_mc_reply_data.name, g_mc_test_appname), 0);
	assert_eq(strcmp(g_mc_reply_data.request_id, g_request_id), 0);

	return 0;
}


/**
 * @testcase		utc_mc_client_set_cmd_reply_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_set_cmd_reply_received_cb()
 */
int utc_mc_client_set_cmd_reply_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_cmd_reply_received_cb(NULL, _mc_client_cmd_reply_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_cmd_reply_received_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_cmd_reply_received_cb_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_unset_cmd_reply_received_cb()
 */
int utc_mc_client_unset_cmd_reply_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_cmd_reply_received_cb(g_mc_client, _mc_client_cmd_reply_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_cmd_reply_received_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_unset_cmd_reply_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_unset_cmd_reply_received_cb()
 */
int utc_mc_client_unset_cmd_reply_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_cmd_reply_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_subtitles_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_set_subtitles_updated_cb()
 */
int utc_mc_client_set_subtitles_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_subtitles_updated_cb(g_mc_client, _mc_client_bool_attribute_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_subtitles_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_set_subtitles_updated_cb()
 */
int utc_mc_client_set_subtitles_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_subtitles_updated_cb(NULL, _mc_client_bool_attribute_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_subtitles_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_subtitles_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_unset_subtitles_updated_cb()
 */
int utc_mc_client_unset_subtitles_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_subtitles_updated_cb(g_mc_client, _mc_client_bool_attribute_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_subtitles_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_subtitles_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_unset_subtitles_updated_cb()
 */
int utc_mc_client_unset_subtitles_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_subtitles_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_360_mode_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_set_360_mode_updated_cb()
 */
int utc_mc_client_set_360_mode_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_360_mode_updated_cb(g_mc_client, _mc_client_bool_attribute_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_360_mode_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_set_360_mode_updated_cb()
 */
int utc_mc_client_set_360_mode_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_360_mode_updated_cb(NULL, _mc_client_bool_attribute_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_360_mode_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_360_mode_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_unset_360_mode_updated_cb()
 */
int utc_mc_client_unset_360_mode_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_360_mode_updated_cb(g_mc_client, _mc_client_bool_attribute_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_360_mode_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_360_mode_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_unset_360_mode_updated_cb()
 */
int utc_mc_client_unset_360_mode_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_360_mode_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_display_mode_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_set_display_mode_updated_cb()
 */
int utc_mc_client_set_display_mode_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_display_mode_updated_cb(g_mc_client, _mc_client_display_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_display_mode_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_set_display_mode_updated_cb()
 */
int utc_mc_client_set_display_mode_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_display_mode_updated_cb(NULL, _mc_client_display_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_display_mode_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_display_mode_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_unset_display_mode_updated_cb()
 */
int utc_mc_client_unset_display_mode_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_display_mode_updated_cb(g_mc_client, _mc_client_display_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_display_mode_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_display_mode_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_unset_display_mode_updated_cb()
 */
int utc_mc_client_unset_display_mode_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_display_mode_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_display_rotation_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_set_display_rotation_updated_cb()
 */
int utc_mc_client_set_display_rotation_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_display_rotation_updated_cb(g_mc_client, _mc_client_display_rotation_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_display_rotation_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_set_display_rotation_updated_cb()
 */
int utc_mc_client_set_display_rotation_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_display_rotation_updated_cb(NULL, _mc_client_display_rotation_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_display_rotation_updated_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_display_rotation_updated_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_unset_display_rotation_updated_cb()
 */
int utc_mc_client_unset_display_rotation_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_display_rotation_updated_cb(g_mc_client, _mc_client_display_rotation_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_display_rotation_updated_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_display_rotation_updated_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_unset_display_rotation_updated_cb()
 */
int utc_mc_client_unset_display_rotation_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_display_rotation_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_playback_state_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_get_playback_state()
 */
int utc_mc_client_get_playback_state_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;
	mc_playback_states_e playback_state = MC_PLAYBACK_STATE_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = __update_mc_server_info(&playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_playback_state(playback_info, &playback_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(playback_state, MC_PLAYBACK_STATE_PAUSED);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_get_playback_state_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_get_playback_state()
 */
int utc_mc_client_get_playback_state_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;
	mc_playback_states_e playback_state = MC_PLAYBACK_STATE_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = __update_mc_server_info(&playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_playback_state(NULL, &playback_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_playback_state(playback_info, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_playback_position_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_get_playback_position()
 */
int utc_mc_client_get_playback_position_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;
	unsigned long long playback_position = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = __update_mc_server_info(&playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_playback_position(playback_info, &playback_position);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(playback_position, 12345);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_mc_client_get_playback_position_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_get_playback_position()
 */
int utc_mc_client_get_playback_position_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;
	unsigned long long playback_position = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = __update_mc_server_info(&playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_playback_position(NULL, &playback_position);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_playback_position(playback_info, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_playback_content_type_p
 * @since_tizen		5.0
 * @description		Positive test case of utc_mc_client_get_playback_content_type()
 */
int utc_mc_client_get_playback_content_type_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;
	mc_content_type_e content_type = MC_CONTENT_TYPE_UNDECIDED;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = __update_mc_server_info(&playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_playback_content_type(playback_info, &content_type);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(content_type, MC_CONTENT_TYPE_OTHER);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_playback_content_type_n
 * @since_tizen		5.0
 * @description		Negative test case of utc_mc_client_get_playback_content_type()
 */
int utc_mc_client_get_playback_content_type_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;
	mc_content_type_e index = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = __update_mc_server_info(&playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_playback_content_type(NULL, &index);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_playback_content_type(playback_info, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_age_rating_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_client_get_age_rating()
 */
int utc_mc_client_get_age_rating_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;
	mc_content_age_rating_e age_rating = MC_CONTENT_RATING_ALL;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = __update_mc_server_info(&playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_age_rating(playback_info, &age_rating);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(age_rating, MC_CONTENT_RATING_7_PLUS);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_age_rating_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_client_get_age_rating()
 */
int utc_mc_client_get_age_rating_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;
	mc_content_age_rating_e age_rating = MC_CONTENT_RATING_ALL;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = __update_mc_server_info(&playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_age_rating(NULL, &age_rating);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_age_rating(playback_info, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_playlist_item_index_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_get_playlist_item_index()
 */
int utc_mc_client_get_playlist_item_index_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;
	char * index = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = __update_mc_server_info(&playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_playlist_item_index(playback_info, &index);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(strcmp(index, g_mc_test_playlist_index), 0);

	if (index != NULL)
		free(index);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_playlist_item_index_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_get_playlist_item_index()
 */
int utc_mc_client_get_playlist_item_index_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;
	char * index = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = __update_mc_server_info(&playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_playlist_item_index(NULL, &index);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_playlist_item_index(playback_info, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_playlist_item_info_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_client_get_playlist_item_info()
 */
int utc_mc_client_get_playlist_item_info_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;
	char *playlist_name = NULL;
	char *index = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = __update_mc_server_info(&playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_playlist_item_info(playback_info, &playlist_name, &index);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(strcmp(playlist_name, g_mc_test_playlist_name), 0);
	assert_eq(strcmp(index, g_mc_test_playlist_index), 0);

	if (index != NULL)
		free(index);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_playlist_item_info_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_client_get_playlist_item_info()
 */
int utc_mc_client_get_playlist_item_info_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;
	char *playlist_name = NULL;
	char *index = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = __update_mc_server_info(&playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_playlist_item_info(NULL, &playlist_name, &index);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_playlist_item_info(playback_info, NULL, &index);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_playlist_item_info(playback_info, &playlist_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_destroy_playback_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_destroy_playback()
 */
int utc_mc_client_destroy_playback_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = __update_mc_server_info(&playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_destroy_playback_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_destroy_playback()
 */
int utc_mc_client_destroy_playback_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_destroy_playback(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_latest_server_info_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_get_latest_server_info()
 */
int utc_mc_client_get_latest_server_info_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_neq(g_mc_server_name, NULL);
	assert_eq(g_mc_server_state, MC_SERVER_STATE_ACTIVATE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_latest_server_info_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_get_latest_server_info()
 */
int utc_mc_client_get_latest_server_info_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_get_latest_server_info(NULL, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_latest_server_info(g_mc_client, NULL, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_playback_info_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_get_server_playback_info()
 */
int utc_mc_client_get_server_playback_info_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_playback_info(g_mc_client, g_mc_server_name, &playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_destroy_playback(playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_playback_info_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_get_server_playback_info()
 */
int utc_mc_client_get_server_playback_info_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h playback_info = NULL;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_playback_info(NULL, g_mc_server_name, &playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_playback_info(g_mc_client, NULL, &playback_info);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_playback_info(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_metadata_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_get_server_metadata()
 */
int utc_mc_client_get_server_metadata_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_metadata_h metadata = NULL;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_register_metadata(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_metadata(g_mc_client, g_mc_server_name, &metadata);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_verify_metadata(metadata);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_metadata_destroy(metadata);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_metadata_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_get_server_metadata()
 */
int utc_mc_client_get_server_metadata_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_metadata_h metadata = NULL;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_metadata(NULL, g_mc_server_name, &metadata);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_metadata(g_mc_client, NULL, &metadata);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_metadata(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_shuffle_mode_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_get_server_shuffle_mode()
 */
int utc_mc_client_get_server_shuffle_mode_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_shuffle_mode_e shuffle_mode = MC_SHUFFLE_MODE_ON;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_shuffle_mode(g_mc_server, MC_SHUFFLE_MODE_OFF);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_shuffle_mode(g_mc_client, g_mc_server_name, &shuffle_mode);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(shuffle_mode, MC_SHUFFLE_MODE_OFF);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_shuffle_mode_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_get_server_shuffle_mode()
 */
int utc_mc_client_get_server_shuffle_mode_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_shuffle_mode_e shuffle_mode = MC_SHUFFLE_MODE_ON;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_shuffle_mode(NULL, g_mc_server_name, &shuffle_mode);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_shuffle_mode(g_mc_client, NULL, &shuffle_mode);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_shuffle_mode(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_repeat_mode_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_get_server_repeat_mode()
 */
int utc_mc_client_get_server_repeat_mode_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_repeat_mode_e repeat_mode = MC_REPEAT_MODE_ON;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_repeat_mode(g_mc_server, MC_SHUFFLE_MODE_OFF);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_repeat_mode(g_mc_client, g_mc_server_name, &repeat_mode);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(repeat_mode, MC_SHUFFLE_MODE_OFF);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_repeat_mode_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_get_server_repeat_mode()
 */
int utc_mc_client_get_server_repeat_mode_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_repeat_mode_e repeat_mode = MC_REPEAT_MODE_ON;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_repeat_mode(NULL, g_mc_server_name, &repeat_mode);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_repeat_mode(g_mc_client, NULL, &repeat_mode);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_repeat_mode(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_icon_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_client_get_server_icon()
 */
int utc_mc_client_get_server_icon_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *icon_path = NULL;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_icon(g_mc_server, g_mc_test_icon_path);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_icon(g_mc_client, g_mc_server_name, &icon_path);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(strcmp(icon_path, g_mc_test_icon_path), 0);

	if (icon_path)
		free(icon_path);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_icon_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_client_get_server_icon()
 */
int utc_mc_client_get_server_icon_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *icon_path = NULL;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_icon(NULL, g_mc_server_name, &icon_path);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_icon(g_mc_client, NULL, &icon_path);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_icon(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	if (icon_path)
		free(icon_path);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_playback_ability_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_client_get_server_playback_ability()
 */
int utc_mc_client_get_server_playback_ability_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_ability_h ability = NULL;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_register_ability(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_playback_ability(g_mc_client, g_mc_server_name, &ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_neq(ability, NULL);

	mc_playback_ability_destroy(ability);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_playback_ability_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_client_get_server_playback_ability()
 */
int utc_mc_client_get_server_playback_ability_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_ability_h ability = NULL;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_playback_ability(NULL, g_mc_server_name, &ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_playback_ability(g_mc_client, NULL, &ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_playback_ability(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_shuffle_ability_support_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_client_get_server_shuffle_ability_support()
 */
int utc_mc_client_get_server_shuffle_ability_support_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_ability_support_e supported = MC_ABILITY_SUPPORTED_UNDECIDED;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_SHUFFLE, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_shuffle_ability_support(g_mc_client, g_mc_server_name, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(supported, g_mc_test_ability);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_shuffle_ability_support_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_client_get_server_shuffle_ability_support()
 */
int utc_mc_client_get_server_shuffle_ability_support_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_ability_support_e supported = MC_ABILITY_SUPPORTED_UNDECIDED;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_shuffle_ability_support(NULL, g_mc_server_name, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_shuffle_ability_support(g_mc_client, NULL, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_shuffle_ability_support(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_repeat_ability_support_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_client_get_server_repeat_ability_support()
 */
int utc_mc_client_get_server_repeat_ability_support_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_ability_support_e supported = MC_ABILITY_SUPPORTED_UNDECIDED;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_REPEAT, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_repeat_ability_support(g_mc_client, g_mc_server_name, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(supported, g_mc_test_ability);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_repeat_ability_support_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_client_get_server_repeat_ability_support()
 */
int utc_mc_client_get_server_repeat_ability_support_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_ability_support_e supported = MC_ABILITY_SUPPORTED_UNDECIDED;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_repeat_ability_support(NULL, g_mc_server_name, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_repeat_ability_support(g_mc_client, NULL, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_repeat_ability_support(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_ability_support_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_get_server_ability_support()
 */
int utc_mc_client_get_server_ability_support_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_ability_support_e supported = MC_ABILITY_SUPPORTED_UNDECIDED;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_SHUFFLE, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_REPEAT, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_PLAYBACK_POSITION, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_PLAYLIST, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_CLIENT_CUSTOM, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_SEARCH, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_ability_support(g_mc_client, g_mc_server_name, MC_ABILITY_SHUFFLE, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(supported, g_mc_test_ability);

	ret = mc_client_get_server_ability_support(g_mc_client, g_mc_server_name, MC_ABILITY_REPEAT, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(supported, g_mc_test_ability);

	ret = mc_client_get_server_ability_support(g_mc_client, g_mc_server_name, MC_ABILITY_PLAYBACK_POSITION, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(supported, g_mc_test_ability);

	ret = mc_client_get_server_ability_support(g_mc_client, g_mc_server_name, MC_ABILITY_PLAYLIST, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(supported, g_mc_test_ability);

	ret = mc_client_get_server_ability_support(g_mc_client, g_mc_server_name, MC_ABILITY_CLIENT_CUSTOM, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(supported, g_mc_test_ability);

	ret = mc_client_get_server_ability_support(g_mc_client, g_mc_server_name, MC_ABILITY_SEARCH, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(supported, g_mc_test_ability);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_ability_support_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_get_server_ability_support()
 */
int utc_mc_client_get_server_ability_support_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_ability_support_e supported = MC_ABILITY_SUPPORTED_UNDECIDED;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_ability_support(NULL, g_mc_server_name, MC_ABILITY_SHUFFLE, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_ability_support(g_mc_client, NULL, MC_ABILITY_SHUFFLE, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_ability_support(g_mc_client, g_mc_server_name, MC_ABILITY_SHUFFLE, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_ability_support(g_mc_client, g_mc_server_name, -1, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_subtitles_enabled_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_get_server_subtitles_enabled()
 */
int utc_mc_client_get_server_subtitles_enabled_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	bool b_value = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_subtitles_enabled(g_mc_server, false);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_subtitles_enabled(g_mc_client, g_mc_server_name, &b_value);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	assert_eq(b_value, false);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_subtitles_enabled_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_get_server_subtitles_enabled()
 */
int utc_mc_client_get_server_subtitles_enabled_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	bool b_value = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_subtitles_enabled(NULL, g_mc_server_name, &b_value);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_subtitles_enabled(g_mc_client, NULL, &b_value);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_subtitles_enabled(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_360_mode_enabled_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_get_server_360_mode_enabled()
 */
int utc_mc_client_get_server_360_mode_enabled_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	bool b_value = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_360_mode_enabled(g_mc_server, false);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_360_mode_enabled(g_mc_client, g_mc_server_name, &b_value);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	assert_eq(b_value, false);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_360_mode_enabled_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_get_server_360_mode_enabled()
 */
int utc_mc_client_get_server_360_mode_enabled_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	bool b_value = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_360_mode_enabled(NULL, g_mc_server_name, &b_value);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_360_mode_enabled(g_mc_client, NULL, &b_value);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_360_mode_enabled(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_display_mode_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_get_server_display_mode()
 */
int utc_mc_client_get_server_display_mode_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_display_mode_e mode = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_display_mode(g_mc_server, MC_DISPLAY_MODE_ORIGIN_SIZE);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_display_mode(g_mc_client, g_mc_server_name, &mode);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	assert_eq(mode, MC_DISPLAY_MODE_ORIGIN_SIZE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_display_mode_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_get_server_display_mode()
 */
int utc_mc_client_get_server_display_mode_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_display_mode_e mode = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_display_mode(NULL, g_mc_server_name, &mode);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_display_mode(g_mc_client, NULL, &mode);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_display_mode(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_display_rotation_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_get_server_display_rotation()
 */
int utc_mc_client_get_server_display_rotation_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_display_rotation_e rotation = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_update_display_rotation(g_mc_server, MC_DISPLAY_ROTATION_180);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_display_rotation(g_mc_client, g_mc_server_name, &rotation);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	assert_eq(rotation, MC_DISPLAY_ROTATION_180);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_display_rotation_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_get_server_display_rotation()
 */
int utc_mc_client_get_server_display_rotation_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_display_rotation_e rotation = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_display_rotation(NULL, g_mc_server_name, &rotation);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_display_rotation(g_mc_client, NULL, &rotation);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_display_rotation(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_display_mode_ability_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_get_server_display_mode_ability()
 */
int utc_mc_client_get_server_display_mode_ability_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int display_ability = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_display_mode_ability(g_mc_server,
		MC_DISPLAY_MODE_LETTER_BOX | MC_DISPLAY_MODE_ORIGIN_SIZE | MC_DISPLAY_MODE_FULL_SCREEN | MC_DISPLAY_MODE_CROPPED_FULL, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_display_mode_ability(g_mc_client, g_mc_server_name, &display_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_get_display_mode_ability(display_ability);
	assert_eq(ret, TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_display_mode_ability_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_get_server_display_mode_ability()
 */
int utc_mc_client_get_server_display_mode_ability_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int display_ability = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_display_mode_ability(NULL, g_mc_server_name, &display_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_display_mode_ability(g_mc_client, NULL, &display_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_display_mode_ability(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_display_rotation_ability_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_get_server_display_rotation_ability()
 */
int utc_mc_client_get_server_display_rotation_ability_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int display_ability = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_display_rotation_ability(g_mc_server,
		MC_DISPLAY_ROTATION_NONE | MC_DISPLAY_ROTATION_90 | MC_DISPLAY_ROTATION_180 | MC_DISPLAY_ROTATION_270, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_display_rotation_ability(g_mc_client, g_mc_server_name, &display_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_get_display_rotation_ability(display_ability);
	assert_eq(ret, TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_get_server_display_rotation_ability_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_get_server_display_rotation_ability()
 */
int utc_mc_client_get_server_display_rotation_ability_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int display_ability = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_display_rotation_ability(NULL, g_mc_server_name, &display_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_display_rotation_ability(g_mc_client, NULL, &display_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_get_server_display_rotation_ability(g_mc_client, g_mc_server_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_foreach_server_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_foreach_server()
 */
int utc_mc_client_foreach_server_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_foreach_server(g_mc_client, _mc_activated_server_cb, &g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_neq(g_mc_server_name, NULL);

	return 0;
}

/**
 * @testcase		utc_mc_client_foreach_server_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_foreach_server()
 */
int utc_mc_client_foreach_server_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_foreach_server(NULL, _mc_activated_server_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_foreach_server(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_playback_action_cmd_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_send_playback_action_cmd()
 */
int utc_mc_client_send_playback_action_cmd_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_action_e playback_action = MC_PLAYBACK_ACTION_STOP;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playback_action_cmd_received_cb(g_mc_server, _mc_server_playback_action_cmd_received_cb, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_playback_action_cmd(g_mc_client, g_mc_server_name, playback_action, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_playback_action_cmd_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_send_playback_action_cmd()
 */
int utc_mc_client_send_playback_action_cmd_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_playback_action_cmd(NULL, g_mc_server_name, MC_PLAYBACK_ACTION_STOP, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_playback_action_cmd(g_mc_client, NULL, MC_PLAYBACK_ACTION_STOP, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_playback_action_cmd(g_mc_client, g_mc_server_name, MC_PLAYBACK_ACTION_PLAY-1, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_playback_position_cmd_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_send_playback_position_cmd()
 */
int utc_mc_client_send_playback_position_cmd_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_PLAYBACK_POSITION, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playback_position_cmd_received_cb(g_mc_server, _mc_server_playback_position_cmd_received_cb, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_playback_position_cmd(g_mc_client, g_mc_server_name, g_mc_test_playback_position, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_playback_position_cmd_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_send_playback_position_cmd()
 */
int utc_mc_client_send_playback_position_cmd_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_PLAYBACK_POSITION, g_mc_test_ability_n);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_playback_position_cmd(NULL, g_mc_server_name, g_mc_test_playback_position, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_playback_position_cmd(g_mc_client, NULL, g_mc_test_playback_position, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_playback_position_cmd(g_mc_client, g_mc_server_name, g_mc_test_playback_position, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_ABILITY_LIMITED_BY_SERVER_APP);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_shuffle_mode_cmd_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_send_shuffle_mode_cmd()
 */
int utc_mc_client_send_shuffle_mode_cmd_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_SHUFFLE, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_shuffle_mode_cmd_received_cb(g_mc_server, _mc_server_shuffle_mode_cmd_received_cb, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_shuffle_mode_cmd(g_mc_client, g_mc_server_name, g_mc_test_shuffle_mode, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_shuffle_mode_cmd_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_send_shuffle_mode_cmd()
 */
int utc_mc_client_send_shuffle_mode_cmd_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_SHUFFLE, g_mc_test_ability_n);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_shuffle_mode_cmd(NULL, g_mc_server_name, g_mc_test_shuffle_mode, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_shuffle_mode_cmd(g_mc_client, NULL, g_mc_test_shuffle_mode, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_shuffle_mode_cmd(g_mc_client, g_mc_server_name, -1, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_shuffle_mode_cmd(g_mc_client, g_mc_server_name, MC_SHUFFLE_MODE_OFF, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_ABILITY_LIMITED_BY_SERVER_APP);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_repeat_mode_cmd_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_send_repeat_mode_cmd()
 */
int utc_mc_client_send_repeat_mode_cmd_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_REPEAT, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_repeat_mode_cmd_received_cb(g_mc_server, _mc_server_repeat_mode_cmd_received_cb, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_repeat_mode_cmd(g_mc_client, g_mc_server_name, g_mc_test_repeat_mode, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_repeat_mode_cmd_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_send_repeat_mode_cmd()
 */
int utc_mc_client_send_repeat_mode_cmd_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_REPEAT, g_mc_test_ability_n);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_repeat_mode_cmd(NULL, g_mc_server_name, g_mc_test_repeat_mode, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_repeat_mode_cmd(g_mc_client, NULL, g_mc_test_repeat_mode, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_repeat_mode_cmd(g_mc_client, g_mc_server_name, -1, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_repeat_mode_cmd(g_mc_client, g_mc_server_name, MC_REPEAT_MODE_ONE_MEDIA, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_ABILITY_LIMITED_BY_SERVER_APP);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_playlist_cmd_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_send_playlist_cmd()
 */
int utc_mc_client_send_playlist_cmd_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_PLAYLIST, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_playlist_cmd_received_cb(g_mc_server, _mc_server_playlist_cmd_received_cb, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_playlist_cmd(g_mc_client, g_mc_server_name, g_mc_test_playlist_name, g_mc_test_playlist_index, g_mc_test_playback_action, g_mc_test_playback_position, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_playlist_cmd_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_send_playlist_cmd()
 */
int utc_mc_client_send_playlist_cmd_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_PLAYLIST, g_mc_test_ability_n);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_playlist_cmd(NULL, g_mc_server_name, g_mc_test_playlist_name, g_mc_test_playlist_index, g_mc_test_playback_action, g_mc_test_playback_position, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_playlist_cmd(g_mc_client, NULL, g_mc_test_playlist_name, g_mc_test_playlist_index, g_mc_test_playback_action, g_mc_test_playback_position, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_playlist_cmd(g_mc_client, g_mc_server_name, NULL, g_mc_test_playlist_index, g_mc_test_playback_action, g_mc_test_playback_position, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_playlist_cmd(g_mc_client, g_mc_server_name, NULL, g_mc_test_playlist_index, -1, g_mc_test_playback_position, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_playlist_cmd(g_mc_client, g_mc_server_name, g_mc_test_playlist_name, g_mc_test_playlist_index, g_mc_test_playback_action, g_mc_test_playback_position, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_ABILITY_LIMITED_BY_SERVER_APP);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_custom_cmd_p
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_send_custom_cmd()
 */
int utc_mc_client_send_custom_cmd_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_CLIENT_CUSTOM, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_custom_cmd_received_cb(g_mc_server, _mc_server_custom_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_custom_cmd(g_mc_client, g_mc_server_name, g_mc_test_cmd, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_custom_cmd_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_send_custom_cmd()
 */
int utc_mc_client_send_custom_cmd_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_CLIENT_CUSTOM, g_mc_test_ability_n);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_custom_cmd(NULL, g_mc_server_name, g_mc_test_cmd, NULL, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_custom_cmd(g_mc_client, NULL, g_mc_test_cmd, NULL, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_custom_cmd(g_mc_client, g_mc_server_name, g_mc_test_cmd, NULL, &g_request_id);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_ABILITY_LIMITED_BY_SERVER_APP);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_search_cmd_p
 * @since_tizen		5.0
 * @description		Negative test case of mc_client_send_search_cmd()
 */
int utc_mc_client_send_search_cmd_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_search_h get_search = NULL;
	gboolean cb_result = FALSE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_SEARCH, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_search_cmd_received_cb(g_mc_server, _mc_server_search_cmd_received_cb, &get_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_create(&g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_TITLE, g_mc_test_keywords[MC_SEARCH_TITLE], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_ARTIST, g_mc_test_keywords[MC_SEARCH_ARTIST], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_ALBUM, g_mc_test_keywords[MC_SEARCH_ALBUM], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_GENRE, g_mc_test_keywords[MC_SEARCH_GENRE], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_search_cmd(g_mc_client, g_mc_server_name, g_mc_search, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	/* check the search result */
	assert_neq(get_search, NULL);
	ret = mc_search_foreach_condition(get_search, _mc_search_condition_cb, &cb_result);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(cb_result, TRUE);

	ret = mc_search_destroy(get_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_destroy(g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	g_mc_search = NULL;

	return 0;
}

/**
 * @testcase		utc_mc_client_send_search_cmd_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_client_send_search_cmd()
 */
int utc_mc_client_send_search_cmd_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_SEARCH, g_mc_test_ability_n);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_create(&g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_search_cmd(NULL, g_mc_server_name, g_mc_search, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_search_cmd(g_mc_client, NULL, g_mc_search, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_search_cmd(g_mc_client, g_mc_server_name, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_ABILITY_LIMITED_BY_SERVER_APP);

	ret = mc_search_destroy(g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	g_mc_search = NULL;

	return 0;
}

/**
 * @testcase		utc_mc_client_send_subtitles_cmd_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_send_subtitles_cmd()
 */
int utc_mc_client_send_subtitles_cmd_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_SUBTITLES, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_subtitles_cmd_received_cb(g_mc_server, _mc_server_enable_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_subtitles_cmd(g_mc_client, g_mc_server_name, true, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_subtitles_cmd_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_send_subtitles_cmd()
 */
int utc_mc_client_send_subtitles_cmd_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_SUBTITLES, g_mc_test_ability_n);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_subtitles_cmd(NULL, g_mc_server_name, true, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_subtitles_cmd(g_mc_client, NULL, true, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	//default is MC_ABILITY_SUPPORTED_NO
	ret = mc_client_send_subtitles_cmd(g_mc_client, g_mc_server_name, true, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_ABILITY_LIMITED_BY_SERVER_APP);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_360_mode_cmd_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_send_360_mode_cmd()
 */
int utc_mc_client_send_360_mode_cmd_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_360_MODE, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_360_mode_cmd_received_cb(g_mc_server, _mc_server_enable_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_360_mode_cmd(g_mc_client, g_mc_server_name, true, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_360_mode_cmd_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_send_360_mode_cmd()
 */
int utc_mc_client_send_360_mode_cmd_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_ability_support(g_mc_server, MC_ABILITY_360_MODE, g_mc_test_ability_n);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_360_mode_cmd(NULL, g_mc_server_name, true, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_360_mode_cmd(g_mc_client, NULL, true, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	//default is MC_ABILITY_SUPPORTED_NO
	ret = mc_client_send_360_mode_cmd(g_mc_client, g_mc_server_name, true, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_ABILITY_LIMITED_BY_SERVER_APP);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_display_mode_cmd_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_send_display_mode_cmd()
 */
int utc_mc_client_send_display_mode_cmd_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_display_mode_ability(g_mc_server,
		MC_DISPLAY_MODE_LETTER_BOX | MC_DISPLAY_MODE_ORIGIN_SIZE | MC_DISPLAY_MODE_FULL_SCREEN | MC_DISPLAY_MODE_CROPPED_FULL, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_display_mode_cmd_received_cb(g_mc_server, _mc_server_display_mode_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_display_mode_cmd(g_mc_client, g_mc_server_name, MC_DISPLAY_MODE_FULL_SCREEN, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_display_mode_cmd_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_send_display_mode_cmd()
 */
int utc_mc_client_send_display_mode_cmd_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_display_mode_ability(g_mc_server,
		MC_DISPLAY_MODE_LETTER_BOX | MC_DISPLAY_MODE_ORIGIN_SIZE | MC_DISPLAY_MODE_FULL_SCREEN | MC_DISPLAY_MODE_CROPPED_FULL, g_mc_test_ability_n);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_display_mode_cmd(NULL, g_mc_server_name, MC_DISPLAY_MODE_FULL_SCREEN, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_display_mode_cmd(g_mc_client, NULL, MC_DISPLAY_MODE_FULL_SCREEN, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_display_mode_cmd(g_mc_client, g_mc_server_name, -1, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	//default is MC_ABILITY_SUPPORTED_NO
	ret = mc_client_send_display_mode_cmd(g_mc_client, g_mc_server_name, MC_DISPLAY_MODE_FULL_SCREEN, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_ABILITY_LIMITED_BY_SERVER_APP);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_display_rotation_cmd_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_client_send_display_rotation_cmd()
 */
int utc_mc_client_send_display_rotation_cmd_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_display_rotation_ability(g_mc_server,
		MC_DISPLAY_ROTATION_NONE | MC_DISPLAY_ROTATION_90 | MC_DISPLAY_ROTATION_180 | MC_DISPLAY_ROTATION_270, g_mc_test_ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_display_rotation_cmd_received_cb(g_mc_server, _mc_server_display_rotation_cmd_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_display_rotation_cmd(g_mc_client, g_mc_server_name, MC_DISPLAY_ROTATION_270, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(wait_for_async(), TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_display_rotation_cmd_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_client_send_display_rotation_cmd()
 */
int utc_mc_client_send_display_rotation_cmd_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_display_rotation_ability(g_mc_server,
		MC_DISPLAY_ROTATION_NONE | MC_DISPLAY_ROTATION_90 | MC_DISPLAY_ROTATION_180 | MC_DISPLAY_ROTATION_270, g_mc_test_ability_n);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_send_display_rotation_cmd(NULL, g_mc_server_name, MC_DISPLAY_ROTATION_270, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_display_rotation_cmd(g_mc_client, NULL, MC_DISPLAY_ROTATION_270, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_display_rotation_cmd(g_mc_client, g_mc_server_name, -1, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	//default is MC_ABILITY_SUPPORTED_NO
	ret = mc_client_send_display_rotation_cmd(g_mc_client, g_mc_server_name, MC_DISPLAY_ROTATION_270, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_ABILITY_LIMITED_BY_SERVER_APP);

	return 0;
}

/**
 * @testcase		utc_mc_client_subscribe_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_subscribe()
 */
int utc_mc_client_subscribe_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_playback_updated_cb(g_mc_client, _mc_client_playback_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_PLAYBACK, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_metadata_updated_cb(g_mc_client, _mc_client_metadata_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_METADATA, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_shuffle_mode_updated_cb(g_mc_client, _mc_client_shuffle_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_SHUFFLE_MODE, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_repeat_mode_updated_cb(g_mc_client, _mc_client_repeat_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_REPEAT_MODE, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_playlist_updated_cb(g_mc_client, _mc_client_playlist_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_PLAYLIST, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_server_updated_cb(g_mc_client, _mc_client_server_state_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_SERVER_STATE, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_ability_support_updated_cb(g_mc_client, _mc_client_ability_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_ABILITY_SUPPORT, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_subscribe_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_subscribe()
 */
int utc_mc_client_subscribe_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_subscribe(NULL, MC_SUBSCRIPTION_TYPE_PLAYBACK, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_PLAYBACK, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_REPEAT_MODE + 1, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unsubscribe_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_unsubscribe()
 */
int utc_mc_client_unsubscribe_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_playback_updated_cb(g_mc_client, _mc_client_playback_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_PLAYBACK, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unsubscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_PLAYBACK, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_metadata_updated_cb(g_mc_client, _mc_client_metadata_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_METADATA, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unsubscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_METADATA, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_shuffle_mode_updated_cb(g_mc_client, _mc_client_shuffle_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_SHUFFLE_MODE, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unsubscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_SHUFFLE_MODE, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_repeat_mode_updated_cb(g_mc_client, _mc_client_repeat_mode_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_REPEAT_MODE, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unsubscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_REPEAT_MODE, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_playlist_updated_cb(g_mc_client, _mc_client_playlist_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_PLAYLIST, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unsubscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_PLAYLIST, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_server_updated_cb(g_mc_client, _mc_client_server_state_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_SERVER_STATE, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unsubscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_SERVER_STATE, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_unsubscribe_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_unsubscribe()
 */
int utc_mc_client_unsubscribe_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_playback_updated_cb(g_mc_client, _mc_client_playback_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_PLAYBACK, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unsubscribe(NULL, MC_SUBSCRIPTION_TYPE_PLAYBACK, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_unsubscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_PLAYBACK, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_REPEAT_MODE + 1, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_foreach_server_subscribed_p
 * @since_tizen		2.4
 * @description		Positive test case of mc_client_foreach_server_subscribed()
 */
int utc_mc_client_foreach_server_subscribed_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_playback_updated_cb(g_mc_client, _mc_client_playback_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_PLAYBACK, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_foreach_server_subscribed(g_mc_client, MC_SUBSCRIPTION_TYPE_PLAYBACK, _mc_subscribed_server_cb, &g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_neq(g_mc_server_name, NULL);

	return 0;
}

/**
 * @testcase		utc_mc_client_foreach_server_subscribed_n
 * @since_tizen		2.4
 * @description		Negative test case of mc_client_foreach_server_subscribed()
 */
int utc_mc_client_foreach_server_subscribed_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_playback_updated_cb(g_mc_client, _mc_client_playback_updated_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_subscribe(g_mc_client, MC_SUBSCRIPTION_TYPE_PLAYBACK, g_mc_server_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_foreach_server_subscribed(NULL, MC_SUBSCRIPTION_TYPE_PLAYBACK, _mc_subscribed_server_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_foreach_server_subscribed(g_mc_client, MC_SUBSCRIPTION_TYPE_PLAYBACK, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_foreach_server_playlist_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_foreach_server_playlist()
 */
int utc_mc_client_foreach_server_playlist_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;
	gboolean cb_result = FALSE;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_foreach_server_playlist(g_mc_client, g_mc_server_name, _mc_playlist_list_cb, &cb_result);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	assert_eq(cb_result, TRUE);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_foreach_server_playlist_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_foreach_server_playlist()
 */
int utc_mc_client_foreach_server_playlist_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_foreach_server_playlist(g_mc_client, g_mc_server_name, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_custom_event_received_cb_p
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_set_custom_event_received_cb()
 */
int utc_mc_client_set_custom_event_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_custom_event_received_cb(g_mc_client, _mc_client_custom_event_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_custom_event_received_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_set_custom_event_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_set_custom_event_received_cb()
 */
int utc_mc_client_set_custom_event_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_custom_event_received_cb(NULL, _mc_client_custom_event_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_set_custom_event_received_cb(g_mc_client, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_custom_event_received_cb_p
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_unset_custom_event_received_cb()
 */
int utc_mc_client_unset_custom_event_received_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_set_custom_event_received_cb(g_mc_client, _mc_client_custom_event_received_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_unset_custom_event_received_cb(g_mc_client);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_client_unset_custom_event_received_cb_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_unset_custom_event_received_cb()
 */
int utc_mc_client_unset_custom_event_received_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_unset_custom_event_received_cb(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_client_send_event_reply_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_client_send_event_reply()
 */
int utc_mc_client_send_event_reply_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int idx = 0;

	ret = __launch_mc_server();
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_set_custom_event_received_cb(g_mc_client, _mc_client_custom_event_received_cb, &g_mc_custom_data);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_set_event_reply_received_cb(g_mc_server, _mc_server_event_reply_received_cb, &g_mc_reply_data);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_server_foreach_client(g_mc_server, _mc_activated_client_cb, &g_mc_client_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_neq(g_mc_client_name, NULL);

	for (idx = 0; idx < g_mc_test_result_codes_cnt; idx++) {
		ret = mc_server_send_custom_event(g_mc_server, g_mc_client_name, g_mc_test_event, NULL, &g_request_id);
		assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
		assert_eq(wait_for_async(), TRUE);

		assert_eq(g_mc_custom_data.result, TRUE);
		assert_eq(strcmp(g_mc_custom_data.name, g_mc_test_appname), 0);
		assert_eq(strcmp(g_mc_custom_data.request_id, g_request_id), 0);

		ret = mc_client_send_event_reply(g_mc_client, g_mc_custom_data.name, g_mc_custom_data.request_id, g_mc_test_result_codes[idx], NULL);
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
 * @testcase		utc_mc_client_send_event_reply_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_client_send_event_reply()
 */
int utc_mc_client_send_event_reply_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_client_send_event_reply(NULL, g_mc_test_appname, g_request_id, 0, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_event_reply(g_mc_client, NULL, g_request_id, 0, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_client_send_event_reply(g_mc_client, g_mc_test_appname, NULL, 0, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}
