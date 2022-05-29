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
#include "assert.h"
#include <media/player.h>
#include <glib.h>
#include <storage.h>
#include <string.h>
#include "tct_common.h"

#define API_NAMESPACE			"[PLAYER]"

//& set: MediaPlayerLifecycle

#define INVALID_MEDIA_PATH "./invalid.mp7"
static char* media = "test.mp4";
static char* media_path = NULL;

static player_h g_player = NULL;
static bool _is_broken = false;

/**
 * @function		utc_media_player_lifecycle_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_player_lifecycle_startup(void)
{
    _is_broken = false;

    	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		unsigned int size_of_path = strlen(pszValue) + strlen(media) + 11;
        	media_path = (char *)malloc(size_of_path);
        	snprintf(media_path, size_of_path, "%s/res/res/%s", pszValue, media);
	}
	else
	{
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

    int ret = player_create(&g_player);
    if (ret == PLAYER_ERROR_NONE) {
        _is_broken = true;
    }

    ret = player_set_uri(g_player, media_path);
    if (ret == PLAYER_ERROR_NONE) {
        _is_broken = true;
    }
}

/**
 * @function		utc_media_player_lifecycle_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_player_lifecycle_cleanup(void)
{
    player_state_e state;
    int ret;
    if(g_player){
        ret = player_get_state (g_player, &state);
        if (PLAYER_ERROR_NONE != ret) {
          PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
        }
        if (state != PLAYER_STATE_IDLE){
          player_unprepare(g_player);
        }
        player_destroy(g_player);
        g_player = NULL;
    }

    if(media_path)
      free(media_path);
}

/**
 * @testcase		utc_media_player_create_p
 * @since_tizen		2.3.1
 * @description		Positive test case for creating player
 */
int utc_media_player_create_p(void)
{
    assert(_is_broken);
    player_state_e cur_state;

    int ret2 = player_get_state(g_player, &cur_state);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert_eq(cur_state, PLAYER_STATE_IDLE);

    return 0;
}

/**
 * @testcase		utc_media_player_create_n
 * @since_tizen		2.3.1
 * @description		Negative test case for creating player
 */
int utc_media_player_create_n(void)
{
    int ret;

    ret = player_create(NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_destroy_p
 * @since_tizen		2.3.1
 * @description		Positive test case for destroying player
 */
int utc_media_player_destroy_p(void)
{
    int ret;
    player_h g_player1 = NULL;

    ret = player_create(&g_player1);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_destroy(g_player1);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    g_player1 = NULL;

    return 0;
}

/**
 * @testcase		utc_media_player_destroy_n
 * @since_tizen		2.3.1
 * @description		Negative test case for destroying player
 */
int utc_media_player_destroy_n(void)
{
    int ret;

    ret = player_destroy(NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_pause_p
 * @since_tizen		2.3.1
 * @description		Positive test case to pause player
 */
int utc_media_player_pause_p(void)
{
    assert(_is_broken);
    player_state_e cur_state;

    int ret2 = player_prepare(g_player);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    int ret3 = player_start(g_player);
    assert_eq(ret3, PLAYER_ERROR_NONE);

    int ret4 = player_pause(g_player);
    assert_eq(ret4, PLAYER_ERROR_NONE);

    int ret5 = player_get_state(g_player, &cur_state);
    assert_eq(ret5, PLAYER_ERROR_NONE);
    assert_eq(cur_state, PLAYER_STATE_PAUSED);

    return 0;
}

/**
 * @testcase		utc_media_player_pause_n
 * @since_tizen		2.3.1
 * @description		Negative test case to pause player
 */
int utc_media_player_pause_n(void)
{
    int ret = player_pause(NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_prepare_p
 * @since_tizen		2.3.1
 * @description		Positive test case to prepare player
 */
int utc_media_player_prepare_p(void)
{
    assert(_is_broken);
    player_state_e cur_state;

    int ret = player_prepare(g_player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_get_state(g_player, &cur_state);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert_eq(cur_state, PLAYER_STATE_READY);

    return 0;
}

/**
 * @testcase		utc_media_player_prepare_n
 * @since_tizen		2.3.1
 * @description		Negative test case to prepare player
 */
int utc_media_player_prepare_n(void)
{
    int ret = player_prepare(NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_unprepare_p
 * @since_tizen		2.3.1
 * @description		Positive test case to unprepare player
 */
int utc_media_player_unprepare_p(void)
{
    assert(_is_broken);
    player_state_e cur_state;

    int ret = player_prepare(g_player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_unprepare(g_player);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    int ret3 = player_get_state(g_player, &cur_state);
    assert_eq(ret3, PLAYER_ERROR_NONE);
    assert_eq(cur_state, PLAYER_STATE_IDLE);

    return 0;
}

/**
 * @testcase		utc_media_player_unprepare_n
 * @since_tizen		2.3.1
 * @description		Negative test case to unprepare player
 */
int utc_media_player_unprepare_n(void)
{
    int ret = player_unprepare(NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_uri_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set uri
 */
int utc_media_player_set_uri_p(void)
{
    assert(_is_broken);

    int ret = player_set_uri(g_player, media_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_uri_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set uri
 */
int utc_media_player_set_uri_n(void)
{
    int ret = player_set_uri(NULL, media_path);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_start_p
 * @since_tizen		2.3.1
 * @description		Positive test case to start player
 */
int utc_media_player_start_p(void)
{
    assert(_is_broken);
    player_state_e cur_state;

    int ret = player_prepare(g_player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_start(g_player);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    int ret3 = player_get_state(g_player, &cur_state);
    assert_eq(ret3, PLAYER_ERROR_NONE);
    assert_eq(cur_state, PLAYER_STATE_PLAYING);

    int ret4 = player_stop(g_player);
    assert_eq(ret4, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_start_n
 * @since_tizen		2.3.1
 * @description		Negative test case to start player
 */
int utc_media_player_start_n(void)
{
    int ret = player_start(NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_stop_p
 * @since_tizen		2.3.1
 * @description		Positive test case to stop player
 */
int utc_media_player_stop_p(void)
{
    assert(_is_broken);
    player_state_e cur_state;

    int ret = player_prepare(g_player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_start(g_player);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    int ret3 = player_stop(g_player);
    assert_eq(ret3, PLAYER_ERROR_NONE);

    int ret4 = player_get_state(g_player, &cur_state);
    assert_eq(ret4, PLAYER_ERROR_NONE);
    assert_eq(cur_state, PLAYER_STATE_READY);

    return 0;
}

/**
 * @testcase		utc_media_player_stop_n
 * @since_tizen		2.3.1
 * @description		Negative test case to stop player
 */
int utc_media_player_stop_n(void)
{
    int ret = player_stop(NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}
