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
#include <media/sound_manager.h>
#include <glib.h>
#include <Elementary.h>
#include <Ecore_Wayland2.h>
#include <Ecore_Evas.h>
#include <storage.h>
#include "tct_common.h"

#define API_NAMESPACE           "[PLAYER_DISPLAY]"
#define RETRY_COUNT_FOR_CONTENT 11

static char* media="test.mp4";
static char* media_360="test_360.mp4";
static char* media_drc = "test_drc.ts";

static char* media_path=NULL;
static char* media_360_path=NULL;
static char* media_drc_path = NULL;

static player_h player;
static bool _is_broken = false;
static bool _is_pass = false;

static GMainLoop *g_mainloop = NULL;
static Evas_Object *g_win = NULL;
static Evas_Object *g_eo = NULL;

static gboolean timeout_func(gpointer data)
{
    PRINT_UTC_LOG("[Line : %d][%s] waited 5 seconds\\n", __LINE__, API_NAMESPACE);
    g_main_loop_quit((GMainLoop *) data);
    return FALSE;
}

static void wait_for_async()
{
    GMainContext *context = g_main_context_new();
    GSource *source = g_timeout_source_new(5000);

    /* attach source to context */
    g_source_attach (source, context);

    g_mainloop = g_main_loop_new(context, FALSE);

    /* set the callback for this source */
    g_source_set_callback (source, timeout_func, g_mainloop, NULL);

    g_main_loop_run(g_mainloop);

    /* after attaching with the GSource, destroy() is needed */
    g_source_destroy(source);

    /* unref the last reference we got for GSource */
    g_source_unref(source);

    /* main loop should be destroyed before unref the context */
    g_main_loop_unref(g_mainloop);
    g_main_context_unref(context);
}

static void win_del(void *data, Evas_Object *obj, void *event)
{
    elm_exit();
}

static void destroy_window()
{
    if (g_win) {
        evas_object_del(g_win);
        g_win = NULL;
    }

    if (g_eo) {
        evas_object_del(g_eo);
        g_eo = NULL;
    }
}

void create_evas_window()
{
	destroy_window();	/* destroy window in case the clean_up is not called */

	Evas *evas = NULL;
	int w = 0;
	int h = 0;

	/* use gl backend */
	elm_config_accel_preference_set("3d");

	/* create window */
	g_win = elm_win_util_standard_add("player_display_tc", "player_display_tc");
	if (g_win) {
		elm_win_borderless_set(g_win, EINA_TRUE);
		evas_object_smart_callback_add(g_win, "delete, request", win_del, NULL);
		elm_win_screen_size_get(g_win, NULL, NULL, &w, &h);
		evas_object_resize(g_win, w, h);
		elm_win_autodel_set(g_win, EINA_TRUE);
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] fail to create window\\n", __LINE__, API_NAMESPACE);
	}

	evas = evas_object_evas_get(g_win);
	if (!evas) {
		FPRINTF("[Line: %d][%s] fail to get evas", __LINE__, API_NAMESPACE);
		return;
	}

	g_eo = evas_object_image_add(evas);

	evas_object_image_size_set(g_eo, 500, 500);
	evas_object_image_fill_set(g_eo, 0, 0, 500, 500);
	evas_object_resize(g_eo, 500, 500);

	elm_win_activate(g_win);
	evas_object_show(g_win);
}

static void create_window()
{
    int w = 0;
    int h = 0;

    destroy_window();	/* destroy window in case the clean_up is not called */

    g_win = elm_win_util_standard_add("player_display_tc", "player_display_tc");
    if (g_win) {
        elm_win_borderless_set(g_win, EINA_TRUE);
        evas_object_smart_callback_add(g_win, "delete, request", win_del, NULL);
        elm_win_screen_size_get(g_win, NULL, NULL, &w, &h);
        evas_object_resize(g_win, w, h);
        elm_win_autodel_set(g_win, EINA_TRUE);
    } else {
        PRINT_UTC_LOG("[Line : %d][%s] fail to create window\\n", __LINE__, API_NAMESPACE);
    }
}

static bool _check_spherical_feature(void)
{
#define FEATURE_NAME_OPENGL "http://tizen.org/feature/opengles.version.2_0"
#define FEATURE_NAME_SPHERICAL_VIDEO "http://tizen.org/feature/multimedia.player.spherical_video"

	bool opengl_feature = false;
	bool spherical_video_feature = false;

	system_info_get_platform_bool(FEATURE_NAME_OPENGL, &opengl_feature);
	system_info_get_platform_bool(FEATURE_NAME_SPHERICAL_VIDEO, &spherical_video_feature);

	if (opengl_feature && spherical_video_feature)
		return true;

	PRINT_UTC_LOG("[Line : %d][%s] spherical feature not supportable %d %d.\\n", __LINE__, API_NAMESPACE, opengl_feature, spherical_video_feature);
	return false;
}

static void _video_stream_changed_callback (int width, int height, int fps, int bit_rate, void *user_data)
{
    if(width==320 && height==240)
        _is_pass = true;
}

/**
 * @function		utc_media_player_display_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_player_display_startup(void)
{
	elm_init(0, NULL);
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if (true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE))
	{
		unsigned int size_of_path = 0;

		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		size_of_path = strlen(pszValue) + strlen(media) + 11;
		media_path = (char*)malloc(size_of_path);
		snprintf(media_path, size_of_path, "%s/res/res/%s", pszValue, media);

		size_of_path = strlen(pszValue) + strlen(media_360) + 11;
		media_360_path = (char*)malloc(size_of_path);
		snprintf(media_360_path, size_of_path, "%s/res/res/%s", pszValue, media_360);

		size_of_path = strlen(pszValue) + strlen(media_drc) + 11;
		media_drc_path = (char*)malloc(size_of_path);
		snprintf(media_drc_path, size_of_path, "%s/res/res/%s", pszValue, media_drc);
	}
	else
	{
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	_is_broken = false;
	_is_pass = false;

	int ret = player_create(&player);
	if (PLAYER_ERROR_NONE != ret) {
		_is_broken = true;
		return;
	}

	ret = player_set_uri(player, media_path);
	if (PLAYER_ERROR_NONE != ret) {
		PRINT_UTC_LOG("[Line : %d][%s] player didn't set uri\\n", __LINE__, API_NAMESPACE);
		_is_broken = true;
	}
}

/**
 * @function		utc_media_player_display_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_player_display_cleanup(void)
{
    elm_shutdown();
    player_state_e state;

    player_get_state (player, &state);
    if (state == PLAYER_STATE_READY)
      player_unprepare(player);

    if(player){
        player_destroy(player);
        player = NULL;
    }

    if(media_path)
      free(media_path);

    if(media_360_path)
      free(media_360_path);

    if(media_drc_path)
      free(media_drc_path);

    media_path = media_360_path = media_drc_path = NULL;
    destroy_window();
}

static void player_video_capture_cb(unsigned char *data, int width, int height, unsigned int size, void *user_data)
{
    if(width==240 && height==320)
      _is_pass = true;
}

/**
 * @testcase		utc_media_player_get_video_size_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get video size
 */
int utc_media_player_get_video_size_p(void)
{
    assert(!_is_broken);
    player_state_e state;
    int width, height;
    create_window();

    player_get_state (player, &state);
    if (state == PLAYER_STATE_READY)
      player_unprepare(player);

    int ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);
    }

    int ret1 = player_start(player);
    assert_eq(ret1, PLAYER_ERROR_NONE);
    player_state_e cur_state;
    int ret2 = player_get_state(player, &cur_state);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert_eq(cur_state, PLAYER_STATE_PLAYING);

    int ret3 = player_get_video_size(player, &width, &height);
    assert_eq(ret3, PLAYER_ERROR_NONE);
    int ret4 = player_stop(player);
    assert_eq(ret4, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_get_video_size_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get video size
 */
int utc_media_player_get_video_size_n(void)
{
    int width, height;
    player_state_e cur_state;

    int ret2 = player_get_state(player, &cur_state);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert_eq(cur_state, PLAYER_STATE_IDLE);

    int ret3 = player_get_video_size(player, &width, &height);
    assert_eq(ret3, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_display_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set overlay display handle
 */
int utc_media_player_set_display_p(void)
{
    assert(!_is_broken);

    player_state_e state;

    player_get_state (player, &state);
    if (state == PLAYER_STATE_READY)
      player_unprepare(player);

    create_window();
    int ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);
    }

    return 0;
}

/**
 * @testcase		utc_media_player_set_display_p2
 * @since_tizen		3.0
 * @description		Positive test case to set evas display handle
 */
int utc_media_player_set_display_p2(void)
{
    assert(!_is_broken);

    player_state_e state;

    player_get_state (player, &state);
    if (state == PLAYER_STATE_READY)
      player_unprepare(player);

    create_evas_window();
    int ret = player_set_display(player, PLAYER_DISPLAY_TYPE_EVAS, g_eo);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);
    }

    return 0;
}


/**
  * @testcase           utc_media_player_set_display_p3
  * @since_tizen        6.5
  * @description        Positive test case to set overlay sync ui display handle
  */
int utc_media_player_set_display_p3(void)
{
    assert(!_is_broken);

    player_state_e state;
    const char *exported_shell_handle = NULL;

    player_get_state (player, &state);
    if (state == PLAYER_STATE_READY)
      player_unprepare(player);

    create_window();

    Ecore_Evas *ecore_evas = ecore_evas_ecore_evas_get(evas_object_evas_get(g_win));
    Ecore_Wl2_Window *ecore_wl2_win = ecore_evas_wayland2_window_get(ecore_evas);
    Ecore_Wl2_Subsurface *ecore_wl2_subsurface = ecore_wl2_subsurface_new(ecore_wl2_win);
    ecore_wl2_subsurface_export(ecore_wl2_subsurface);
    exported_shell_handle = ecore_wl2_subsurface_exported_surface_handle_get(ecore_wl2_subsurface);

    int ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY_SYNC_UI, GET_DISPLAY(exported_shell_handle));
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);
    }

    return 0;
}

/**
 * @testcase		utc_media_player_set_display_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set display handle
 */
int utc_media_player_set_display_n(void)
{
    int ret = player_set_display(NULL, PLAYER_DISPLAY_TYPE_NONE, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_display_n2
 * @since_tizen		2.3.1
 * @description		Negative test case to set display handle
 */
int utc_media_player_set_display_n2(void)
{
    int ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_capture_video_p
 * @since_tizen		2.3.1
 * @description		Positive test case to capture video
 */
int utc_media_player_capture_video_p(void)
{
    assert(!_is_broken);
    player_state_e state;

    player_get_state (player, &state);
    if (state == PLAYER_STATE_READY)
      player_unprepare(player);

    create_window();

    int ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret0 = player_prepare(player);
    assert_eq(ret0, PLAYER_ERROR_NONE);

    int ret1 = player_start(player);
    assert_eq(ret1, PLAYER_ERROR_NONE);
    player_state_e cur_state;
    int ret2 = player_get_state(player, &cur_state);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert_eq(cur_state, PLAYER_STATE_PLAYING);

    int ret3 = player_capture_video(player, player_video_capture_cb, NULL);
    assert_eq(ret3, PLAYER_ERROR_NONE);
    wait_for_async();
    assert(_is_pass);
    _is_pass = false;

    int ret4 = player_stop(player);
    assert_eq(ret4, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_capture_video_n
 * @since_tizen		2.3.1
 * @description		Negative test case to capture video
 */
int utc_media_player_capture_video_n(void)
{
    int ret = player_capture_video(NULL, player_video_capture_cb, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_capture_video_n2
 * @since_tizen		2.3.1
 * @description		Negative test case to capture video
 */
int utc_media_player_capture_video_n2(void)
{
    player_state_e state;

    player_get_state (player, &state);
    if (state == PLAYER_STATE_READY)
      player_unprepare(player);

    create_window();

    int ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_capture_video(player, player_video_capture_cb, NULL);
    assert_eq(ret2, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase		utc_media_player_get_video_stream_info_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get video stream info
 */
int utc_media_player_get_video_stream_info_p(void)
{
    assert(!_is_broken);

    player_state_e state;

    player_get_state (player, &state);
    if (state == PLAYER_STATE_READY)
      player_unprepare(player);

    create_window();

    int ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);
    }

    int ret1 = player_start(player);
    assert_eq(ret1, PLAYER_ERROR_NONE);

    int fps = 0, bit_rate = 0;
    int ret2 = player_get_video_stream_info(player, &fps, &bit_rate);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    int ret3 = player_stop(player);
    assert_eq(ret3, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_get_video_stream_info_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get video stream info
 */
int utc_media_player_get_video_stream_info_n(void)
{
    int fps = 0, bit_rate = 0;

    int ret = player_get_video_stream_info(NULL, &fps, &bit_rate);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_get_video_stream_info_n2
 * @since_tizen		2.3.1
 * @description		Negative test case to get video stream info
 */
int utc_media_player_get_video_stream_info_n2(void)
{
    int fps = 0, bit_rate = 0;
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
      PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE)
      player_unprepare(player);

    ret = player_get_video_stream_info(player, &fps, &bit_rate);
    assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_audio_only_p
 * @since_tizen		4.0
 * @description		Positive test case to set audio_only
 */
int utc_media_player_set_audio_only_p(void)
{
    assert(!_is_broken);

    bool is = false;
    bool audio_only = false;
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state == PLAYER_STATE_READY)
      player_unprepare(player);

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);
    }

    ret = player_is_audio_only(player, &is);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_is_audio_only is failed\\n", __LINE__, API_NAMESPACE);
    }
    if(!is)
      audio_only = true;
    else
      audio_only = false;
    ret = player_set_audio_only(player, audio_only);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_is_audio_only(player, &is);
    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(is, audio_only);

    return 0;
}

/**
 * @testcase		utc_media_player_set_audio_only_n
 * @since_tizen		4.0
 * @description		Negative test case to set audio_only
 */
int utc_media_player_set_audio_only_n(void)
{
    bool audio_only = false;

    int ret = player_set_audio_only(NULL, audio_only);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_is_audio_only_p
 * @since_tizen		4.0
 * @description		Positive test case to get whether audio_only is on or not
 */
int utc_media_player_is_audio_only_p(void)
{
    assert(!_is_broken);
    bool audio_only = false;
    bool is = true;
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state == PLAYER_STATE_READY)
      player_unprepare(player);

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);
    }

    ret = player_set_audio_only(player, audio_only);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_is_audio_only(player, &is);
    assert_eq(ret, PLAYER_ERROR_NONE);
    assert(!is);

    return 0;
}

/**
 * @testcase		utc_media_player_is_audio_only_n
 * @since_tizen		4.0
 * @description		Negative test case to get whether audio_only is on or not
 */
int utc_media_player_is_audio_only_n(void)
{
    bool audio_only;

    int ret = player_is_audio_only(NULL, &audio_only);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_media_player_360_is_content_spherical_p
 * @since_tizen     5.0
 * @description     Positive test case to get content spherical information
 */
int utc_media_player_360_is_content_spherical_p(void)
{
    bool is_supportable = _check_spherical_feature();
    bool value = false;
    int ret = PLAYER_ERROR_NONE;

    assert(!_is_broken);

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_360_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_is_content_spherical(player, &value);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }
    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(value, true);

    return 0;
}


/**
 * @testcase        utc_media_player_360_is_content_spherical_n
 * @since_tizen     5.0
 * @description     Negative test case to get content spherical information
 */
int utc_media_player_360_is_content_spherical_n(void)
{
    bool is_supportable = _check_spherical_feature();
    bool value = false;
    int ret = PLAYER_ERROR_NONE;

    assert(!_is_broken);

    ret = player_360_is_content_spherical(player, &value);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }
    assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase      utc_media_player_360_set_get_enable_p
 * @since_tizen   5.0
 * @description   Positive test case to set/get enable 360 value
 */
int utc_media_player_360_set_get_enable_p(void)
{
    player_state_e state = PLAYER_STATE_IDLE;
    bool is_supportable = _check_spherical_feature();
    bool value = true;

    assert(!_is_broken);

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_360_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_set_enabled(player, false);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_is_enabled(player, &value);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }
    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(value, false);

    return 0;
}

/**
 * @testcase      utc_media_player_360_is_enabled_n
 * @since_tizen   5.0
 */
int utc_media_player_360_is_enabled_n(void)
{
    player_state_e state = PLAYER_STATE_IDLE;
    bool is_supportable = _check_spherical_feature();

    assert(!_is_broken);

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    ret = player_360_is_enabled(player, NULL);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }

    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase      utc_media_player_360_set_get_direction_of_view_p
 * @since_tizen   5.0
 * @description   Positive test case to set/get direction of view
 */
int utc_media_player_360_set_get_direction_of_view_p(void)
{
    player_state_e state = PLAYER_STATE_IDLE;
    bool is_supportable = _check_spherical_feature();
    float yaw = 0.0;
    float pitch = 0.0;

    assert(!_is_broken);

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_360_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_set_direction_of_view(player, 0.0, 0.0);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_get_direction_of_view(player, &yaw, &pitch);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }

    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(yaw, 0.0);
    assert_eq(pitch, 0.0);
    return 0;
}

/**
 * @testcase      utc_media_player_360_set_direction_of_view_n
 * @since_tizen   5.0
 * @description   Negative test case to set the direction of view
 */
int utc_media_player_360_set_direction_of_view_n(void)
{
    player_state_e state = PLAYER_STATE_IDLE;
    bool is_supportable = _check_spherical_feature();

    assert(!_is_broken);

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_360_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_set_direction_of_view(player, 10, 0.0);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase      utc_media_player_360_get_direction_of_view_n
 * @since_tizen   5.0
 * @description   Negative test case to get the direction of view
 */
int utc_media_player_360_get_direction_of_view_n(void)
{
    player_state_e state = PLAYER_STATE_IDLE;
    bool is_supportable = _check_spherical_feature();

    assert(!_is_broken);

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_360_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_get_direction_of_view(player, NULL, NULL);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase      utc_media_player_360_set_get_zoom_p
 * @since_tizen   5.0
 * @description   Positive test case to set/get zoom
 */
int utc_media_player_360_set_get_zoom_p(void)
{
    player_state_e state = PLAYER_STATE_IDLE;
    bool is_supportable = _check_spherical_feature();
    float level = 0.0;

    assert(!_is_broken);

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_360_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_set_zoom(player, 2.0);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_get_zoom(player, &level);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }
    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(level, 2.0);

    return 0;
}

/**
 * @testcase      utc_media_player_360_set_zoom_n
 * @since_tizen   5.0
 * @description   Negative test case to set zoom
 */
int utc_media_player_360_set_zoom_n(void)
{
    player_state_e state = PLAYER_STATE_IDLE;
    bool is_supportable = _check_spherical_feature();

    assert(!_is_broken);

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_360_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_set_zoom(player, 15);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }

    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase      utc_media_player_360_get_zoom_n
 * @since_tizen   5.0
 * @description   Negative test case to get zoom
 */
int utc_media_player_360_get_zoom_n(void)
{
    player_state_e state = PLAYER_STATE_IDLE;
    bool is_supportable = _check_spherical_feature();

    assert(!_is_broken);

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_360_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_get_zoom(player, NULL);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }

    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase      utc_media_player_360_set_get_field_of_view_p
 * @since_tizen   5.0
 * @description   Positive test case to set/get field of view
 */
int utc_media_player_360_set_get_field_of_view_p(void)
{
    player_state_e state = PLAYER_STATE_IDLE;
    bool is_supportable = _check_spherical_feature();
    int horizontal_degrees = 0;
    int vertical_degrees = 0;

    assert(!_is_broken);

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_360_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_set_field_of_view(player, 90, 60);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_get_field_of_view(player, &horizontal_degrees, &vertical_degrees);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }

    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(horizontal_degrees, 90);
    assert_eq(vertical_degrees, 60);
    return 0;
}

/**
 * @testcase      utc_media_player_360_set_field_of_view_n
 * @since_tizen   5.0
 * @description   Negative test case to set the field of view
 */
int utc_media_player_360_set_field_of_view_n(void)
{
    player_state_e state = PLAYER_STATE_IDLE;
    bool is_supportable = _check_spherical_feature();

    assert(!_is_broken);

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_360_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_set_field_of_view(player, 0, 0);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase      utc_media_player_360_get_field_of_view_n
 * @since_tizen   5.0
 * @description   Negative test case to get the field of view
 */
int utc_media_player_360_get_field_of_view_n(void)
{
    player_state_e state = PLAYER_STATE_IDLE;
    bool is_supportable = _check_spherical_feature();

    assert(!_is_broken);

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_360_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_get_field_of_view(player, NULL, NULL);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }

    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase      utc_media_player_360_set_zoom_with_field_of_view_p
 * @since_tizen   5.0
 * @description   Positive test case to set zoom with field of view
 */
int utc_media_player_360_set_zoom_with_field_of_view_p(void)
{
    player_state_e state = PLAYER_STATE_IDLE;
    bool is_supportable = _check_spherical_feature();
    float level = 0.0;
    int horizontal_degrees = 0;
    int vertical_degrees = 0;

    assert(!_is_broken);

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_360_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_set_zoom_with_field_of_view(player, 3.0, 120, 90);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_get_zoom(player, &level);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }

    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(level, 3.0);

    ret = player_360_get_field_of_view(player, &horizontal_degrees, &vertical_degrees);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }

    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(horizontal_degrees, 120);
    assert_eq(vertical_degrees, 90);
    return 0;
}

/**
 * @testcase      utc_media_player_360_set_zoom_with_field_of_view_n
 * @since_tizen   5.0
 * @description   Negative test case to set the zoom with field of view
 */
int utc_media_player_360_set_zoom_with_field_of_view_n(void)
{
    player_state_e state = PLAYER_STATE_IDLE;
    bool is_supportable = _check_spherical_feature();

    assert(!_is_broken);

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_360_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_360_set_zoom_with_field_of_view(player, 13.0, 30, 0);
    if (!is_supportable) {
        assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
        return 0;
    }
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);
    return 0;
}

int utc_media_player_set_video_roi_area_p(void)
{
	assert(!_is_broken);

	int ret = PLAYER_ERROR_NONE;
	player_state_e state;

	player_get_state (player, &state);
	if (state == PLAYER_STATE_READY)
		player_unprepare(player);

	create_window();

	ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_set_video_roi_area(player, 0.1, 0.1, 0.5, 0.5);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_prepare(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	return 0;
}

int utc_media_player_set_video_roi_area_n(void)
{
	assert(!_is_broken);

	int ret = PLAYER_ERROR_NONE;
	player_state_e state;

	player_get_state (player, &state);
	if (state == PLAYER_STATE_READY)
		player_unprepare(player);

	create_window();

	ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_set_video_roi_area(player, 0.3, 0.8, 1.0, 0.0);
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_media_player_get_video_roi_area_p(void)
{
	assert(!_is_broken);

	int ret = PLAYER_ERROR_NONE;
	double x = 0.1, y = 0.1, w = 0.5, h = 0.5;
	double x_ret = 0.0, y_ret = 0.0, w_ret = 0.0, h_ret = 0.0;
	player_state_e state;

	player_get_state (player, &state);
	if (state == PLAYER_STATE_READY)
		player_unprepare(player);

	create_window();

	ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_set_video_roi_area(player, x, y, w, h);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_prepare(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_get_video_roi_area(player, &x_ret, &y_ret, &w_ret, &h_ret);
	assert_eq(ret, PLAYER_ERROR_NONE);

	if (x != x_ret || y != y_ret || w != w_ret || h != h_ret) {
		PRINT_UTC_LOG("[Line : %d][%s] player_get_video_roi_area has wrong return\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

int utc_media_player_get_video_roi_area_n(void)
{
	assert(!_is_broken);

	int ret = PLAYER_ERROR_NONE;
	double x = 0.1, y = 0.1, w = 0.5, h = 0.5;
	double x_ret = 0.0, y_ret = 0.0, w_ret = 0.0;
	player_state_e state;

	player_get_state (player, &state);
	if (state == PLAYER_STATE_READY)
		player_unprepare(player);

	create_window();

	ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_set_video_roi_area(player, x, y, w, h);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_prepare(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_get_video_roi_area(player, &x_ret, &y_ret, &w_ret, NULL);
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_player_set_display_visible_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set display visible
 */
int utc_media_player_set_display_visible_p(void)
{
    assert(!_is_broken);
    bool is = false;

    int ret = player_set_display_visible(player, true);
    assert_eq(ret, PLAYER_ERROR_NONE);
    int ret2 = player_is_display_visible(player, &is);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert(is);

    return 0;
}

/**
 * @testcase		utc_media_player_set_display_visible_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set display visible
 */
int utc_media_player_set_display_visible_n(void)
{
    int ret = player_set_display_visible(NULL, true);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_is_display_visible_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get whether visible is on or not
 */
int utc_media_player_is_display_visible_p(void)
{
    assert(!_is_broken);
    bool is = false;

    int ret = player_set_display_visible(player, true);
    assert_eq(ret, PLAYER_ERROR_NONE);
    int ret2 = player_is_display_visible(player, &is);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert(is);

    return 0;
}

/**
 * @testcase		utc_media_player_is_display_visible_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get whether visible is on or not
 */
int utc_media_player_is_display_visible_n(void)
{
    int ret = player_is_display_visible(NULL, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_display_mode_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set display mode
 */
int utc_media_player_set_display_mode_p(void)
{
    assert(!_is_broken);
    player_display_mode_e mode;

    int ret = player_set_display_mode(player, PLAYER_DISPLAY_MODE_FULL_SCREEN);
    assert_eq(ret, PLAYER_ERROR_NONE);
    int ret2 = player_get_display_mode(player, &mode);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert_eq(mode, PLAYER_DISPLAY_MODE_FULL_SCREEN);

    return 0;
}

/**
 * @testcase		utc_media_player_set_display_mode_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set display mode
 */
int utc_media_player_set_display_mode_n(void)
{
    int ret = player_set_display_mode(NULL, PLAYER_DISPLAY_MODE_FULL_SCREEN);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_get_display_mode_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get display mode
 */
int utc_media_player_get_display_mode_p(void)
{
    assert(!_is_broken);
    player_display_mode_e mode;

    int ret = player_set_display_mode(player, PLAYER_DISPLAY_MODE_FULL_SCREEN);
    assert_eq(ret, PLAYER_ERROR_NONE);
    int ret2 = player_get_display_mode(player, &mode);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert_eq(mode, PLAYER_DISPLAY_MODE_FULL_SCREEN);

    return 0;
}

/**
 * @testcase		utc_media_player_get_display_mode_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get display mode
 */
int utc_media_player_get_display_mode_n(void)
{
	player_display_mode_e mode;

	int ret = player_get_display_mode(NULL, &mode);
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_player_set_display_roi_area_p
 * @since_tizen		3.0
 * @description		Positive test case to set display roi
 */
int utc_media_player_set_display_roi_area_p(void)
{
	assert(!_is_broken);
	player_display_mode_e mode;

	int ret = player_set_display_mode(player, PLAYER_DISPLAY_MODE_DST_ROI);
	assert_eq(ret, PLAYER_ERROR_NONE);
	int ret2 = player_get_display_mode(player, &mode);
	assert_eq(ret2, PLAYER_ERROR_NONE);
	assert_eq(mode, PLAYER_DISPLAY_MODE_DST_ROI);

	int ret3 = player_set_display_roi_area(player, 0, 0, 100, 100);
	assert_eq(ret3, PLAYER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_player_set_display_rotation_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set display rotation
 */
int utc_media_player_set_display_rotation_n(void)
{
    int ret = player_set_display_rotation(NULL, PLAYER_DISPLAY_ROTATION_90);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_get_display_rotation_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get display rotation
 */
int utc_media_player_get_display_rotation_p(void)
{
    assert(!_is_broken);
    player_display_rotation_e rotation;

    int ret = player_set_display_rotation(player, PLAYER_DISPLAY_ROTATION_90);
    assert_eq(ret, PLAYER_ERROR_NONE);
    int ret2 = player_get_display_rotation(player, &rotation);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert_eq(rotation, PLAYER_DISPLAY_ROTATION_90);

    return 0;
}
/**
 * @testcase		utc_media_player_set_display_roi_area_n
 * @since_tizen		3.0
 * @description		Negative test case to set display roi
 */
int utc_media_player_set_display_roi_area_n(void)
{
    int ret = player_set_display_roi_area(player, 0, 0, 0, 0);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase		utc_media_player_set_display_rotation_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set display rotation
 */
int utc_media_player_set_display_rotation_p(void)
{
    assert(!_is_broken);
    player_display_rotation_e rotation;

    int ret = player_set_display_rotation(player, PLAYER_DISPLAY_ROTATION_90);
    assert_eq(ret, PLAYER_ERROR_NONE);
    int ret2 = player_get_display_rotation(player, &rotation);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert_eq(rotation, PLAYER_DISPLAY_ROTATION_90);

    return 0;
}

/**
 * @testcase		utc_media_player_get_display_rotation_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get display rotation
 */
int utc_media_player_get_display_rotation_n(void)
{
    player_display_rotation_e rotation;

    int ret = player_get_display_rotation(NULL, &rotation);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase     utc_media_player_set_video_stream_changed_cb_p
 * @since_tizen  2.4
 * @description  Positive test case to set video stream changed callback
 */
int utc_media_player_set_video_stream_changed_cb_p(void)
{
	int repeat = 0;

	int ret = player_set_uri(player, media_drc_path);
	if (ret != PLAYER_ERROR_NONE)
		PRINT_UTC_LOG("[Line : %d][%s] player_set_uri is failed\\n", __LINE__, API_NAMESPACE);

	create_window();
	ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
	if (ret != PLAYER_ERROR_NONE) {
		PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
	}

	ret = player_set_video_stream_changed_cb(player, _video_stream_changed_callback, NULL);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_prepare(player);
	if (ret != PLAYER_ERROR_NONE)
		PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);

	ret = player_start(player);
	if (ret != PLAYER_ERROR_NONE)
		PRINT_UTC_LOG("[Line : %d][%s] player isn't started\\n", __LINE__, API_NAMESPACE);

	for (repeat = 0 ; repeat < RETRY_COUNT_FOR_CONTENT ; repeat++) {
		wait_for_async();
		if (_is_pass)
			break;
	}

	ret = player_stop(player);
	if (ret != PLAYER_ERROR_NONE)
		PRINT_UTC_LOG("[Line : %d][%s] player isn't stopped\\n", __LINE__, API_NAMESPACE);

	assert(_is_pass);
	_is_pass = false;

	return 0;
}

/**
 * @testcase     utc_media_player_set_video_stream_changed_cb_n
 * @since_tizen  2.4
 * @description  Negative test case to set video stream changed callback
 */
int utc_media_player_set_video_stream_changed_cb_n(void)
{
	int ret = player_set_video_stream_changed_cb(NULL, _video_stream_changed_callback, NULL);
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase     utc_media_player_set_video_stream_changed_cb_n2
 * @since_tizen  2.4
 * @description  Negative test case to set video stream changed callback
 */
int utc_media_player_set_video_stream_changed_cb_n2(void)
{
	int ret = player_set_uri(player, media_drc_path);
	if (PLAYER_ERROR_NONE != ret)
		PRINT_UTC_LOG("[Line : %d][%s] player_set_uri is failed\\n", __LINE__, API_NAMESPACE);

	create_window();
	ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
	if (PLAYER_ERROR_NONE != ret) {
		PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
	}
	ret = player_prepare(player);
	if (PLAYER_ERROR_NONE != ret)
		PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);

	ret = player_set_video_stream_changed_cb (player, _video_stream_changed_callback, NULL);
	assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

	return 0;
}

/**
 * @testcase     utc_media_player_unset_video_stream_changed_cb_p
 * @since_tizen  2.4
 * @description  Positive test case to unset video stream changed callback
 */
int utc_media_player_unset_video_stream_changed_cb_p(void)
{
	int ret = player_unset_video_stream_changed_cb(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	return 0;
}

/**
 * @testcase      utc_media_player_unset_video_stream_changed_cb_n
 * @since_tizen   2.4
 * @description   Negative test case to unset video stream changed callback
 */
int utc_media_player_unset_video_stream_changed_cb_n(void)
{
	int ret = player_unset_video_stream_changed_cb(NULL);
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	return 0;
}
