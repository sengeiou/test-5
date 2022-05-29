//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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


//& set: MediaController
static mc_server_h g_mc_server = NULL;
static mc_client_h g_mc_client = NULL;
static char *g_mc_server_name = NULL;

static mc_server_state_e g_mc_server_state = MC_SERVER_STATE_NONE;
static mc_search_h g_mc_search = NULL;

static mc_error_e startup_ret = MEDIA_CONTROLLER_ERROR_NONE;

/**
 * @function		utc_mc_playlist_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_mc_playlist_startup(void)
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

	// initialize server data, it will be removed by destroying server when test finish
	ret = mc_server_set_playback_state(g_mc_server, MC_PLAYBACK_STATE_PLAYING);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_state failed (code: %d)\\n", __FILE__, __LINE__, ret);
		startup_ret = ret;
		return;
	}

	ret = mc_server_set_playlist_item_info(g_mc_server, g_mc_test_playlist_name, g_mc_test_playlist_index);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playlist_item_info failed (code: %d)\\n", __FILE__, __LINE__, ret);
		startup_ret = ret;
		return;
	}

	ret = mc_server_update_playback_info(g_mc_server);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_update_playback_info failed (code: %d)\\n", __FILE__, __LINE__, ret);
		startup_ret = ret;
		return;
	}

	// start client app
	ret = mc_client_create(&g_mc_client);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE)
	{
		FPRINTF("[%s:%d] mc_client_create failed (code: %d)\\n", __FILE__, __LINE__, ret);
		startup_ret = ret;
		return;
	}

	return;
}


/**
 * @function		utc_mc_playlist_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_mc_playlist_cleanup(void)
{
	mc_server_destroy(g_mc_server);
	g_mc_server = NULL;

	mc_client_destroy(g_mc_client);
	g_mc_client = NULL;

	g_free(g_mc_server_name);
	g_mc_server_name = NULL;

	return;
}

/**
 * @testcase		utc_mc_playlist_get_name_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_playlist_get_name()
 */
int utc_mc_playlist_get_name_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;
	char *playlist_name = NULL;
	bool check_val = FALSE;

	ret = mc_server_create_playlist(g_mc_server, g_mc_test_playlist_name, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_get_name(playlist, &playlist_name);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	if (playlist_name != NULL) {
		if (strcmp(g_mc_test_playlist_name, playlist_name) == 0)
			check_val = TRUE;

		free(playlist_name);
	}

	assert_eq(check_val, TRUE);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_get_name_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_playlist_get_name()
 */
int utc_mc_playlist_get_name_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = mc_server_create_playlist(g_mc_server, g_mc_test_playlist_name, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_get_name(playlist, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_get_playlist_count_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_playlist_get_playlist_count()
 */
int utc_mc_playlist_get_playlist_count_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;
	int _cnt = 0;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_get_playlist_count(g_mc_server_name, &_cnt);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(_cnt, 1);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_get_playlist_count_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_playlist_get_playlist_count()
 */
int utc_mc_playlist_get_playlist_count_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;
	int _cnt = 0;

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_get_playlist_count(g_mc_server_name, &_cnt);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_foreach_playlist_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_playlist_foreach_playlist()
 */
int utc_mc_playlist_foreach_playlist_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;
	gboolean cb_result = FALSE;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_foreach_playlist(g_mc_server_name, _mc_playlist_list_cb, &cb_result);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	assert_eq(cb_result, TRUE);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_foreach_playlist_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_playlist_foreach_playlist()
 */
int utc_mc_playlist_foreach_playlist_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_foreach_playlist(g_mc_server_name, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_get_item_count_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_playlist_get_item_count()
 */
int utc_mc_playlist_get_item_count_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;
	int _cnt = 0;

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_get_item_count(playlist, &_cnt);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(_cnt, 1);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_get_item_count_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_playlist_get_item_count()
 */
int utc_mc_playlist_get_item_count_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_get_item_count(playlist, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_foreach_item_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_playlist_foreach_item()
 */
int utc_mc_playlist_foreach_item_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;
	gboolean cb_result = FALSE;

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_foreach_item(playlist, _mc_playlist_item_cb, &cb_result);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	assert_eq(cb_result, TRUE);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_foreach_item_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_playlist_foreach_item()
 */
int utc_mc_playlist_foreach_item_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_foreach_item(playlist, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_get_playlist_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_playlist_get_playlist()
 */
int utc_mc_playlist_get_playlist_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;
	mc_playlist_h playlist_1 = NULL;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_get_playlist(g_mc_server_name, g_mc_test_playlist_name, &playlist_1);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_destroy(playlist_1);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_get_playlist_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_playlist_get_playlist()
 */
int utc_mc_playlist_get_playlist_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_get_playlist(g_mc_server_name, g_mc_test_playlist_name, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_clone_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_playlist_clone()
 */
int utc_mc_playlist_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;
	mc_playlist_h playlist_dst = NULL;

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_clone(playlist, &playlist_dst);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_destroy(playlist_dst);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_clone_p
 * @since_tizen		4.0
 * @description		Negative test case of mc_playlist_clone()
 */
int utc_mc_playlist_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_clone(playlist, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_destroy_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_playlist_destroy()
 */
int utc_mc_playlist_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_destroy(playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playlist_destroy_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_playlist_destroy()
 */
int utc_mc_playlist_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);

	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h playlist = NULL;

	ret = _mc_register_playlist(g_mc_server, &playlist);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playlist_destroy(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function		utc_mc_metadata_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_mc_metadata_startup(void)
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

	// initialize server data, it will be removed by destroying server when test finish
	ret = mc_server_set_playback_state(g_mc_server, MC_PLAYBACK_STATE_PLAYING);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_state failed (code: %d)\\n", __FILE__, __LINE__, ret);
		startup_ret = ret;
		return;
	}

	ret = mc_server_update_playback_info(g_mc_server);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_update_playback_info failed (code: %d)\\n", __FILE__, __LINE__, ret);
		startup_ret = ret;
		return;
	}

	// start client app
	ret = mc_client_create(&g_mc_client);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE)
	{
		FPRINTF("[%s:%d] mc_client_create failed (code: %d)\\n", __FILE__, __LINE__, ret);
		startup_ret = ret;
		return;
	}

	return;
}

/**
 * @function		utc_mc_metadata_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_mc_metadata_cleanup(void)
{
	mc_server_destroy(g_mc_server);
	g_mc_server = NULL;

	mc_client_destroy(g_mc_client);
	g_mc_client = NULL;

	g_free(g_mc_server_name);
	g_mc_server_name = NULL;

	return;
}

/**
 * @testcase		utc_mc_metadata_clone_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_metadata_clone()
 */
int utc_mc_metadata_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_metadata_h metadata = NULL;
	mc_metadata_h metadata_dst = NULL;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_register_metadata(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_metadata(g_mc_client, g_mc_server_name, &metadata);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_metadata_clone(metadata, &metadata_dst);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_verify_metadata(metadata_dst);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_metadata_destroy(metadata);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_metadata_destroy(metadata_dst);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_metadata_clone_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_metadata_clone()
 */
int utc_mc_metadata_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_metadata_h metadata = NULL;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_metadata(g_mc_client, g_mc_server_name, &metadata);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_metadata_clone(metadata, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_metadata_destroy(metadata);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_metadata_destroy_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_metadata_destroy()
 */
int utc_mc_metadata_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_metadata_h metadata = NULL;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = _mc_register_metadata(g_mc_server);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_metadata(g_mc_client, g_mc_server_name, &metadata);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_metadata_destroy(metadata);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_metadata_destroy_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_metadata_destroy()
 */
int utc_mc_metadata_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_metadata_destroy(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_metadata_get_p
 * @since_tizen		4.0
 * @description		Positive test case of mc_metadata_get()
 */
int utc_mc_metadata_get_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_metadata_h metadata = NULL;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
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
 * @testcase		utc_mc_metadata_get_n
 * @since_tizen		4.0
 * @description		Negative test case of mc_metadata_get()
 */
int utc_mc_metadata_get_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_metadata_h metadata = NULL;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_metadata(g_mc_client, g_mc_server_name, &metadata);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_metadata_get(metadata, MC_META_MEDIA_TITLE, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_metadata_destroy(metadata);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase			utc_mc_metadata_encode_season_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_metadata_encode_season()
 */
int utc_mc_metadata_encode_season_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *encoded_meta = NULL;

	ret = mc_metadata_encode_season(G_META_INT_VAL, g_mc_test_metadata[MC_META_MEDIA_SEASON], &encoded_meta);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase			utc_mc_metadata_encode_season_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_metadata_encode_season()
 */
int utc_mc_metadata_encode_season_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_metadata_encode_season(G_META_INT_VAL, g_mc_test_metadata[MC_META_MEDIA_SEASON], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase			utc_mc_metadata_encode_episode_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_metadata_encode_episode()
 */
int utc_mc_metadata_encode_episode_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *encoded_meta = NULL;

	ret = mc_metadata_encode_episode(G_META_INT_VAL, g_mc_test_metadata[MC_META_MEDIA_EPISODE], &encoded_meta);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase			utc_mc_metadata_encode_episode_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_metadata_encode_episode()
 */
int utc_mc_metadata_encode_episode_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_metadata_encode_episode(G_META_INT_VAL, g_mc_test_metadata[MC_META_MEDIA_EPISODE], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase			utc_mc_metadata_encode_resolution_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_metadata_encode_resolution()
 */
int utc_mc_metadata_encode_resolution_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *encoded_meta = NULL;

	ret = mc_metadata_encode_resolution(G_META_W, G_META_H, &encoded_meta);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase			utc_mc_metadata_encode_resolution_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_metadata_encode_resolution()
 */
int utc_mc_metadata_encode_resolution_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_metadata_encode_resolution(G_META_W, G_META_H, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase			utc_mc_metadata_decode_season_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_metadata_decode_season()
 */
int utc_mc_metadata_decode_season_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *encoded_meta = NULL;
	int int_val = 0;
	char *str_val = NULL;

	ret = mc_metadata_encode_season(G_META_INT_VAL, g_mc_test_metadata[MC_META_MEDIA_SEASON], &encoded_meta);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_metadata_decode_season(encoded_meta, &int_val, &str_val);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_neq(str_val, NULL);
	assert_eq(int_val, G_META_INT_VAL);
	assert_eq(strcmp(g_mc_test_metadata[MC_META_MEDIA_SEASON], str_val), 0);

	free(str_val);

	return 0;
}

/**
 * @testcase			utc_mc_metadata_decode_season_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_metadata_decode_season()
 */
int utc_mc_metadata_decode_season_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *encoded_meta = NULL;
	char *str_val = NULL;

	ret = mc_metadata_encode_season(G_META_INT_VAL, g_mc_test_metadata[MC_META_MEDIA_SEASON], &encoded_meta);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_metadata_decode_season(encoded_meta, NULL, &str_val);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase			utc_mc_metadata_decode_episode_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_metadata_decode_episode()
 */
int utc_mc_metadata_decode_episode_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *encoded_meta = NULL;
	int int_val = 0;
	char *str_val = NULL;

	ret = mc_metadata_encode_episode(G_META_INT_VAL, g_mc_test_metadata[MC_META_MEDIA_EPISODE], &encoded_meta);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_metadata_decode_episode(encoded_meta, &int_val, &str_val);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_neq(str_val, NULL);
	assert_eq(int_val, G_META_INT_VAL);
	assert_eq(strcmp(g_mc_test_metadata[MC_META_MEDIA_EPISODE], str_val), 0);

	free(str_val);

	return 0;
}

/**
 * @testcase			utc_mc_metadata_decode_episode_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_metadata_decode_episode()
 */
int utc_mc_metadata_decode_episode_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *encoded_meta = NULL;
	char *str_val = NULL;

	ret = mc_metadata_encode_episode(G_META_INT_VAL, g_mc_test_metadata[MC_META_MEDIA_EPISODE], &encoded_meta);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_metadata_decode_episode(encoded_meta, NULL, &str_val);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase			utc_mc_metadata_decode_resolution_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_metadata_decode_resolution()
 */
int utc_mc_metadata_decode_resolution_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *encoded_meta = NULL;
	unsigned int width = 0;
	unsigned int height = 0;

	ret = mc_metadata_encode_resolution(G_META_W, G_META_H, &encoded_meta);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_metadata_decode_resolution(encoded_meta, &width, &height);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(width, G_META_W);
	assert_eq(height, G_META_H);

	return 0;
}

/**
 * @testcase			utc_mc_metadata_decode_resolution_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_metadata_decode_resolution()
 */
int utc_mc_metadata_decode_resolution_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	char *encoded_meta = NULL;

	ret = mc_metadata_encode_resolution(G_META_W, G_META_H, &encoded_meta);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_metadata_decode_resolution(encoded_meta, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function		utc_media_controller_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_mc_playback_ability_startup(void)
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

	// initialize server data, it will be removed by destroying server when test finish
	ret = mc_server_set_playback_state(g_mc_server, MC_PLAYBACK_STATE_PLAYING);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] mc_server_set_playback_state failed (code: %d)\\n", __FILE__, __LINE__, ret);
		startup_ret = ret;
		return;
	}

	ret = _mc_register_ability(g_mc_server);
	if ( ret != MEDIA_CONTROLLER_ERROR_NONE) {
		FPRINTF("[%s:%d] _mc_register_ability failed (code: %d)\\n", __FILE__, __LINE__, ret);
		startup_ret = ret;
		return;
	}

	// start client app
	ret = mc_client_create(&g_mc_client);
	if (ret != MEDIA_CONTROLLER_ERROR_NONE)
	{
		FPRINTF("[%s:%d] mc_client_create failed (code: %d)\\n", __FILE__, __LINE__, ret);
		startup_ret = ret;
		return;
	}

	return;
}


/**
 * @function		utc_media_controller_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_mc_playback_ability_cleanup(void)
{
	mc_server_destroy(g_mc_server);
	g_mc_server = NULL;

	mc_client_destroy(g_mc_client);
	g_mc_client = NULL;

	g_free(g_mc_server_name);
	g_mc_server_name = NULL;

	return;
}

/**
 * @testcase		utc_mc_playback_ability_clone_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_playback_ability_clone()
 */
int utc_mc_playback_ability_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_ability_h ability = NULL;
	mc_playback_ability_h ability_dst = NULL;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_playback_ability(g_mc_client, g_mc_server_name, &ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playback_ability_clone(ability, &ability_dst);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playback_ability_destroy(ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playback_ability_destroy(ability_dst);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playback_ability_clone_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_playback_ability_clone()
 */
int utc_mc_playback_ability_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_ability_h ability = NULL;
	mc_playback_ability_h ability_dst = NULL;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_playback_ability(g_mc_client, g_mc_server_name, &ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playback_ability_clone(NULL, &ability_dst);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playback_ability_clone(ability, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playback_ability_destroy(ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playback_ability_destroy_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_playback_ability_destroy()
 */
int utc_mc_playback_ability_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_ability_h ability = NULL;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_playback_ability(g_mc_client, g_mc_server_name, &ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playback_ability_destroy(ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playback_ability_destroy_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_playback_ability_destroy()
 */
int utc_mc_playback_ability_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_playback_ability_destroy(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_playback_action_is_supported_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_playback_ability_get()
 */
int utc_mc_playback_action_is_supported_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_ability_h ability = NULL;
	mc_ability_support_e supported = MC_ABILITY_SUPPORTED_UNDECIDED;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_playback_ability(g_mc_client, g_mc_server_name, &ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playback_action_is_supported(ability, MC_PLAYBACK_ACTION_PLAY, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(supported, g_mc_test_ability);

	ret = mc_playback_ability_destroy(ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_playback_action_is_supported_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_playback_ability_get()
 */
int utc_mc_playback_action_is_supported_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTROLLER_ERROR_NONE);
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_ability_h ability = NULL;
	mc_ability_support_e supported = MC_ABILITY_SUPPORTED_UNDECIDED;

	ret = mc_client_get_latest_server_info(g_mc_client, &g_mc_server_name, &g_mc_server_state);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_client_get_server_playback_ability(g_mc_client, g_mc_server_name, &ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_playback_action_is_supported(NULL, MC_PLAYBACK_ACTION_PLAY, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playback_action_is_supported(ability, -1, &supported);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playback_action_is_supported(ability, MC_PLAYBACK_ACTION_PLAY, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_playback_ability_destroy(ability);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @function		utc_mc_search_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_mc_search_startup(void)
{
	// do nothing...

	return;
}


/**
 * @function		utc_mc_search_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_mc_search_cleanup(void)
{
	if (g_mc_search)
		mc_search_destroy(g_mc_search);

	g_mc_search = NULL;

	return;
}

/**
 * @testcase		utc_mc_search_create_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_search_create()
 */
int utc_mc_search_create_p(void)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_search_create(&g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_search_create_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_search_create()
 */
int utc_mc_search_create_n(void)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_search_create(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_search_set_condition_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_search_set_condition()
 */
int utc_mc_search_set_condition_p(void)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_search_create(&g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_NO_CATEGORY, g_mc_test_keywords[MC_SEARCH_NO_CATEGORY], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_TITLE, g_mc_test_keywords[MC_SEARCH_TITLE], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_ARTIST, g_mc_test_keywords[MC_SEARCH_ARTIST], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_ALBUM, g_mc_test_keywords[MC_SEARCH_ALBUM], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_GENRE, g_mc_test_keywords[MC_SEARCH_GENRE], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_TPO, g_mc_test_keywords[MC_SEARCH_TPO], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_search_set_condition_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_search_set_condition()
 */
int utc_mc_search_set_condition_n(void)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_search_create(&g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(NULL, g_mc_test_content_type, MC_SEARCH_NO_CATEGORY, g_mc_test_keywords[MC_SEARCH_NO_CATEGORY], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_search_set_condition(g_mc_search, -1, MC_SEARCH_NO_CATEGORY, g_mc_test_keywords[MC_SEARCH_NO_CATEGORY], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, -1, g_mc_test_keywords[MC_SEARCH_NO_CATEGORY], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_TITLE, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_search_get_condition_count_p
 * @since_tizen		5.5
 * @description		Positive test case of mc_search_get_condition_count()
 */
int utc_mc_search_get_condition_count_p(void)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	int _cnt = 0;

	ret = mc_search_create(&g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_NO_CATEGORY, g_mc_test_keywords[MC_SEARCH_NO_CATEGORY], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_TITLE, g_mc_test_keywords[MC_SEARCH_TITLE], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_ARTIST, g_mc_test_keywords[MC_SEARCH_ARTIST], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_ALBUM, g_mc_test_keywords[MC_SEARCH_ALBUM], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_GENRE, g_mc_test_keywords[MC_SEARCH_GENRE], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_TPO, g_mc_test_keywords[MC_SEARCH_TPO], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_get_condition_count(g_mc_search, &_cnt);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(_cnt, 6);

	return 0;
}

/**
 * @testcase		utc_mc_search_get_condition_count_n
 * @since_tizen		5.5
 * @description		Negative test case of mc_search_get_condition_count()
 */
int utc_mc_search_get_condition_count_n(void)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_search_create(&g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_get_condition_count(g_mc_search, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_search_foreach_condition_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_search_foreach_condition()
 */
int utc_mc_search_foreach_condition_p(void)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	gboolean cb_result = FALSE;

	ret = mc_search_create(&g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_NO_CATEGORY, g_mc_test_keywords[MC_SEARCH_NO_CATEGORY], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_TITLE, g_mc_test_keywords[MC_SEARCH_TITLE], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_ARTIST, g_mc_test_keywords[MC_SEARCH_ARTIST], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_ALBUM, g_mc_test_keywords[MC_SEARCH_ALBUM], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_GENRE, g_mc_test_keywords[MC_SEARCH_GENRE], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_set_condition(g_mc_search, g_mc_test_content_type, MC_SEARCH_TPO, g_mc_test_keywords[MC_SEARCH_TPO], NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_foreach_condition(g_mc_search, _mc_search_condition_cb, &cb_result);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	assert_eq(cb_result, TRUE);

	return 0;
}

/**
 * @testcase		utc_mc_search_foreach_condition_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_search_foreach_condition()
 */
int utc_mc_search_foreach_condition_n(void)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_search_create(&g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_foreach_condition(NULL, _mc_search_condition_cb, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_search_foreach_condition(g_mc_search, NULL, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mc_search_clone_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_search_clone()
 */
int utc_mc_search_clone_p(void)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_search_h search_dst = NULL;

	ret = mc_search_create(&g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_clone(g_mc_search, &search_dst);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_destroy(search_dst);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mc_search_clone_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_search_clone()
 */
int utc_mc_search_clone_n(void)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;
	mc_search_h search_dst = NULL;

	ret = mc_search_create(&g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_clone(NULL, &search_dst);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	ret = mc_search_clone(g_mc_search, NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase		utc_mc_search_destroy_p
 * @since_tizen		5.0
 * @description		Positive test case of mc_search_destroy()
 */
int utc_mc_search_destroy_p(void)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_search_create(&g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);

	ret = mc_search_destroy(g_mc_search);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_NONE);
	g_mc_search = NULL;

	return 0;
}

/**
 * @testcase		utc_mc_search_destroy_n
 * @since_tizen		5.0
 * @description		Negative test case of mc_search_destroy()
 */
int utc_mc_search_destroy_n(void)
{
	int ret = MEDIA_CONTROLLER_ERROR_NONE;

	ret = mc_search_destroy(NULL);
	assert_eq(ret, MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER);

	return 0;
}
