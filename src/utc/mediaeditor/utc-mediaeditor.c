/*
 * Copyright (c) 2022 Samsung Electronics Co., Ltd All Rights Reserved
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

#include "assert.h"
#include <glib.h>
#include <dlog.h>
#include <Elementary.h>
#include <media_editor.h>
#include <system_info.h>
#include <pthread.h>

#define API_NAMESPACE "[MEDIAEDITOR]"
#define TIMEOUT_MS 60000
#define GET_DISPLAY(x) (void*)(x)

#define DISPLAY_FEATURE "http://tizen.org/feature/display"
#define EXPECTED_RET(V) ((__check_display_feature()) ? V : MEDIAEDITOR_ERROR_NOT_SUPPORTED)

static GMainLoop *g_mainloop_render = NULL;
static GMainLoop *g_mainloop_state = NULL;
static GMainLoop *g_mainloop_project = NULL;
static int g_timeout_id = 0;
static Evas_Object *g_win = NULL;
static Evas_Object *g_eo = NULL;

static char* g_audio_clip_filename = "audio.mp3";
static char* g_audio_clip_path = NULL;
static char* g_video_clip_filename = "video.mp4";
static char* g_video_clip_path = NULL;
static char* g_render_filename = "output.mp4";
static char* g_render_path = NULL;
static char* g_project_new_filename = "project_new.xges";
static char* g_project_new_path = NULL;
static char* g_project_load_filename = "project_load.xges";
static char* g_project_load_path = NULL;
static mediaeditor_state_e g_target_state = MEDIAEDITOR_STATE_IDLE;

static mediaeditor_h g_mediaeditor = NULL;

pthread_t g_thread_id;
gboolean g_exit = FALSE;

static bool __check_display_feature()
{
    bool supported = false;

    if (system_info_get_platform_bool(DISPLAY_FEATURE, &supported) != SYSTEM_INFO_ERROR_NONE) {
        dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d], failed to get feature[%s]", __FUNCTION__, __LINE__, DISPLAY_FEATURE);
        return false;
    }

    if (!supported) {
        dlog_print(DLOG_ERROR, "NativeTCT", "feature[%s] is not supported", DISPLAY_FEATURE);
        return false;
    }

    return true;
}

static gboolean __timeout_func(gpointer data)
{
    dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] g_main_loop_quit()", __FUNCTION__, __LINE__);

    g_main_loop_quit((GMainLoop *)data);
    return FALSE;
}

static void __quit_mainloop(GMainLoop *mainloop)
{
    dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] g_main_loop_quit()", __FUNCTION__, __LINE__);

    if (g_timeout_id > 0) {
        g_source_remove(g_timeout_id);
        g_timeout_id = 0;
    }

    if (mainloop != NULL) {
        g_main_loop_quit(mainloop);
    }
}

static void __run_mainloop(GMainLoop **mainloop)
{
    *mainloop = g_main_loop_new(NULL, FALSE);

    g_timeout_id = g_timeout_add(TIMEOUT_MS, __timeout_func, *mainloop);

    dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] call g_main_loop_run()", __FUNCTION__, __LINE__);

    g_main_loop_run(*mainloop);

    dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] quit g_main_loop_run()", __FUNCTION__, __LINE__);

    g_main_loop_unref(*mainloop);
    *mainloop = NULL;
}

static void __win_del(void *data, Evas_Object *obj, void *event)
{
    elm_exit();
}

static void __create_window()
{
    int w = 0;
    int h = 0;

    if (!__check_display_feature())
        return;

    g_win = elm_win_util_standard_add("mediaeditor_utc", "mediaeditor_utc");
    if (g_win) {
        elm_win_borderless_set(g_win, EINA_TRUE);
        evas_object_smart_callback_add(g_win, "delete,request", __win_del, NULL);
        elm_win_screen_size_get(g_win, NULL, NULL, &w, &h);
        evas_object_resize(g_win, w, h);
        elm_win_autodel_set(g_win, EINA_TRUE);
    }

    g_eo = evas_object_image_add(evas_object_evas_get(g_win));

    dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d] g_win[%p] g_eo[%p]", __FUNCTION__, __LINE__, g_win, g_eo);
}

static void __destroy_window()
{
    dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d] g_win[%p] g_eo[%p]", __FUNCTION__, __LINE__, g_win, g_eo);

    if (g_win) {
        evas_object_del(g_win);
        g_win = NULL;
    }

    if (g_eo) {
        evas_object_del(g_eo);
        g_eo = NULL;
    }
}

static void __mediaeditor_render_completed_cb(void *user_data)
{
    dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d]", __FUNCTION__, __LINE__);

    __quit_mainloop(g_mainloop_render);
}

static void __mediaeditor_project_loaded_cb(void *user_data)
{
    dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d]", __FUNCTION__, __LINE__);

    __quit_mainloop(g_mainloop_project);
}

static void __mediaeditor_state_changed_cb(mediaeditor_state_e previous, mediaeditor_state_e current, void *user_data)
{
    dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d], previous state[%d], current state[%d]", __FUNCTION__, __LINE__, previous, current);

    if (g_target_state == current) {
        __quit_mainloop(g_mainloop_state);
    }
}

static void __mediaeditor_layer_priority_changed_cb(mediaeditor_layer_info_s *layer_infos, unsigned int size, void *user_data)
{
    dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d]", __FUNCTION__, __LINE__);

    if (layer_infos == NULL) {
        dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d], layer_infos is null", __FUNCTION__, __LINE__);
        return;
    }

    for (unsigned int i = 0 ; i < size ; i++) {
        dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d], layer id[%d], layer priority[%d]",
            __FUNCTION__, __LINE__, layer_infos[i].id, layer_infos[i].priority);
    }
}

/**
 * @function    utc_mediaeditor_startup
 * @description Should be called before a test
 */
void utc_mediaeditor_startup(void)
{
    int ret = mediaeditor_create(&g_mediaeditor);
    if (ret != MEDIAEDITOR_ERROR_NONE) {
        fprintf(stderr, "mediaeditor_create() is failed");
        return;
    }

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    if (true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE)) {
        PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);

        unsigned int size_of_path = strlen(pszValue) + strlen(g_audio_clip_filename) + 11;
        g_audio_clip_path = (char*)malloc(size_of_path);
        snprintf(g_audio_clip_path, size_of_path, "%s/res/%s", pszValue, g_audio_clip_filename);

        size_of_path = strlen(pszValue) + strlen(g_video_clip_filename) + 11;
        g_video_clip_path = (char*)malloc(size_of_path);
        snprintf(g_video_clip_path, size_of_path, "%s/res/%s", pszValue, g_video_clip_filename);

        size_of_path = strlen(pszValue) + strlen(g_render_filename) + 11;
        g_render_path = (char*)malloc(size_of_path);
        snprintf(g_render_path, size_of_path, "%s/res/%s", pszValue, g_render_filename);

        size_of_path = strlen(pszValue) + strlen(g_project_new_filename) + 11;
        g_project_new_path = (char*)malloc(size_of_path);
        snprintf(g_project_new_path, size_of_path, "%s/res/%s", pszValue, g_project_new_filename);

        size_of_path = strlen(pszValue) + strlen(g_project_load_filename) + 11;
        g_project_load_path = (char*)malloc(size_of_path);
        snprintf(g_project_load_path, size_of_path, "%s/res/%s", pszValue, g_project_load_filename);
    } else {
        PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
    }
}

/**
 * @function    utc_mediaeditor_cleanup
 * @description Should be called after a test
 */
void utc_mediaeditor_cleanup(void)
{
    if (g_audio_clip_path) {
        free(g_audio_clip_path);
        g_audio_clip_path = NULL;
    }

    if (g_video_clip_path) {
        free(g_video_clip_path);
        g_video_clip_path = NULL;
    }

    if (g_render_path) {
        free(g_render_path);
        g_render_path = NULL;
    }

    if (g_project_new_path) {
        free(g_project_new_path);
        g_project_new_path = NULL;
    }

    if (g_project_load_path) {
        free(g_project_load_path);
        g_project_load_path = NULL;
    }

    if (g_mediaeditor) {
        int ret = mediaeditor_destroy(g_mediaeditor);
        if (ret != MEDIAEDITOR_ERROR_NONE) {
            fprintf(stderr, "mediaeditor_destroy() is failed");
            return;
        }
    }
}

/**
 * @function    utc_mediaeditor_startup_create_win
 * @description Should be called before a test using a window
 */
void utc_mediaeditor_startup_create_win(void)
{
    __create_window();

    utc_mediaeditor_startup();
}

/**
 * @function    utc_mediaeditor_cleanup_destroy_win
 * @description Should be called after the test using a window
 */
void utc_mediaeditor_cleanup_destroy_win(void)
{
    __destroy_window();

    utc_mediaeditor_cleanup();
}

/**
 * @testcase    utc_mediaeditor_create_p
 * @since_tizen 7.0
 * @description Creates a mediaeditor handle
 */
int utc_mediaeditor_create_p(void)
{
    mediaeditor_h mediaeditor = NULL;

    int ret = mediaeditor_create(&mediaeditor);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_destroy(mediaeditor);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_create_n
 * @since_tizen 7.0
 * @description Creates a mediaeditor handle\n
 *              - Pass a invalid parameter
 */
int utc_mediaeditor_create_n(void)
{
    int ret = mediaeditor_create(NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_destroy_p
 * @since_tizen 7.0
 * @description Destroys the mediaeditor handle\n
 *              - Create a mediaeditor handle\n
 *              - Pass the mediaeditor handle to destroy
 */
int utc_mediaeditor_destroy_p(void)
{
    mediaeditor_h mediaeditor = NULL;

    int ret = mediaeditor_create(&mediaeditor);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_destroy(mediaeditor);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_destroy_n
 * @since_tizen 7.0
 * @description Destroys the mediaeditor handle\n
 *              - Pass the null mediaeditor handle
 */
int utc_mediaeditor_destroy_n(void)
{
    int ret = mediaeditor_destroy(NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_display_p
 * @since_tizen 7.0
 * @description Sets display\n
 *              - Pass evas object
 */
int utc_mediaeditor_set_display_p(void)
{
    int ret = mediaeditor_set_display(g_mediaeditor, MEDIAEDITOR_DISPLAY_TYPE_EVAS, GET_DISPLAY(g_eo));
    assert_eq(ret, EXPECTED_RET(MEDIAEDITOR_ERROR_NONE));

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_display_n1
 * @since_tizen 7.0
 * @description Sets display\n
 *              - Pass the null mediaeditor handle
 */
int utc_mediaeditor_set_display_n1(void)
{
    int ret = mediaeditor_set_display(NULL, MEDIAEDITOR_DISPLAY_TYPE_EVAS, GET_DISPLAY(g_eo));
    assert_eq(ret, EXPECTED_RET(MEDIAEDITOR_ERROR_INVALID_PARAMETER));

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_display_n2
 * @since_tizen 7.0
 * @description Sets display\n
 *              - Pass null display handle
 */
int utc_mediaeditor_set_display_n2(void)
{
    int ret = mediaeditor_set_display(g_mediaeditor, MEDIAEDITOR_DISPLAY_TYPE_EVAS, NULL);
    assert_eq(ret, EXPECTED_RET(MEDIAEDITOR_ERROR_INVALID_PARAMETER));

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_display_n3
 * @since_tizen 7.0
 * @description Sets display\n
 *              - Pass invalid display type
 */
int utc_mediaeditor_set_display_n3(void)
{
    int ret = mediaeditor_set_display(g_mediaeditor, MEDIAEDITOR_DISPLAY_TYPE_NONE + 1, NULL);
    assert_eq(ret, EXPECTED_RET(MEDIAEDITOR_ERROR_INVALID_PARAMETER));

    ret = mediaeditor_set_display(g_mediaeditor, MEDIAEDITOR_DISPLAY_TYPE_OVERLAY - 1, NULL);
    assert_eq(ret, EXPECTED_RET(MEDIAEDITOR_ERROR_INVALID_PARAMETER));

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_state_p
 * @since_tizen 7.0
 * @description Gets the mediaeditor state\n
 *              - Get state of the handle
 */
int utc_mediaeditor_get_state_p(void)
{
    mediaeditor_state_e state = MEDIAEDITOR_STATE_IDLE;

    int ret = mediaeditor_get_state(g_mediaeditor, &state);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(state, MEDIAEDITOR_STATE_IDLE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_state_n1
 * @since_tizen 7.0
 * @description Gets the mediaeditor state\n
 *              - Pass null parameter
 */
int utc_mediaeditor_get_state_n1(void)
{
    int ret = mediaeditor_get_state(g_mediaeditor, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_state_n2
 * @since_tizen 7.0
 * @description Gets the mediaeditor state\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_get_state_n2(void)
{
    mediaeditor_state_e state = MEDIAEDITOR_STATE_IDLE;

    int ret = mediaeditor_get_state(NULL, &state);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_start_render_p
 * @since_tizen 7.0
 * @description Starts rendering\n
 *              - Adds layer and clip\n
 *              - Starts rendering
 */
int utc_mediaeditor_start_render_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 10;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_start_render(g_mediaeditor, g_render_path, __mediaeditor_render_completed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    /* Wait to receive render completed callback */
    __run_mainloop(&g_mainloop_render);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_start_render_n1
 * @since_tizen 7.0
 * @description Starts rendering\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_start_render_n1(void)
{
    int ret = mediaeditor_start_render(NULL, g_render_path, __mediaeditor_render_completed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_start_render_n2
 * @since_tizen 7.0
 * @description Starts rendering\n
 *              - Pass null path parameter
 */
int utc_mediaeditor_start_render_n2(void)
{
    int ret = mediaeditor_start_render(g_mediaeditor, NULL, __mediaeditor_render_completed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_start_render_n3
 * @since_tizen 7.0
 * @description Starts rendering\n
 *              - Pass null callback parameter
 */
int utc_mediaeditor_start_render_n3(void)
{
    int ret = mediaeditor_start_render(g_mediaeditor, g_render_path, NULL, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_start_render_n4
 * @since_tizen 7.0
 * @description Starts rendering\n
 *              - Start rendering without adding clip
 */
int utc_mediaeditor_start_render_n4(void)
{
    int ret = mediaeditor_start_render(g_mediaeditor, g_render_path, __mediaeditor_render_completed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_OPERATION);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_cancel_render_p
 * @since_tizen 7.0
 * @description Cancels rendering\n
 *              - Start rendering\n
 *              - Cancel rendering
 */
int utc_mediaeditor_cancel_render_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 10000;
    unsigned int in_point = 0;

    int ret = mediaeditor_set_state_changed_cb(g_mediaeditor, __mediaeditor_state_changed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    g_target_state = MEDIAEDITOR_STATE_RENDERING;

    ret = mediaeditor_start_render(g_mediaeditor, g_render_path, __mediaeditor_render_completed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    /* Wait state transition : IDLE -> RENDERING */
     __run_mainloop(&g_mainloop_state);

    ret = mediaeditor_cancel_render(g_mediaeditor);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_cancel_render_n1
 * @since_tizen 7.0
 * @description Cancels rendering\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_cancel_render_n1(void)
{
    int ret = mediaeditor_cancel_render(NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_cancel_render_n2
 * @since_tizen 7.0
 * @description Cancels rendering\n
 *              - Cancel rendering in invalid state
 */
int utc_mediaeditor_cancel_render_n2(void)
{
    int ret = mediaeditor_cancel_render(g_mediaeditor);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_start_preview_p
 * @since_tizen 7.0
 * @description Starts preview\n
 *              - Set diaplay\n
 *              - Add a layer and a clip\n
 *              - Start and stop preview
 */
int utc_mediaeditor_start_preview_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;

    int ret = mediaeditor_set_state_changed_cb(g_mediaeditor, __mediaeditor_state_changed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_set_display(g_mediaeditor, MEDIAEDITOR_DISPLAY_TYPE_EVAS, GET_DISPLAY(g_eo));
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, 0, 5000, 0, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    g_target_state = MEDIAEDITOR_STATE_PREVIEW;

    ret = mediaeditor_start_preview(g_mediaeditor);
    assert_eq(ret, EXPECTED_RET(MEDIAEDITOR_ERROR_NONE));

    /* Wait state transition : IDLE -> PREVIEW */
    __run_mainloop(&g_mainloop_state);

    ret = mediaeditor_stop_preview(g_mediaeditor);
    assert_eq(ret, EXPECTED_RET(MEDIAEDITOR_ERROR_NONE));

    return 0;
}

/**
 * @testcase    utc_mediaeditor_start_preview_n
 * @since_tizen 7.0
 * @description Starts preview\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_start_preview_n(void)
{
    int ret = mediaeditor_start_preview(NULL);
    assert_eq(ret, EXPECTED_RET(MEDIAEDITOR_ERROR_INVALID_PARAMETER));

    return 0;
}

/**
 * @testcase    utc_mediaeditor_stop_preview_p
 * @since_tizen 7.0
 * @description Stops preview\n
 *              - Set error callback\n
 *              - Set display type and handle\n
 *              - Add a layer and a clip\n
 *              - Start preview\n
 *              - Wait preview is started and stop preview
 */
int utc_mediaeditor_stop_preview_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;

    int ret = mediaeditor_set_state_changed_cb(g_mediaeditor, __mediaeditor_state_changed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_set_display(g_mediaeditor, MEDIAEDITOR_DISPLAY_TYPE_EVAS, GET_DISPLAY(g_eo));
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(ret, EXPECTED_RET(MEDIAEDITOR_ERROR_NONE));

    ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, 0, 5000, 0, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    g_target_state = MEDIAEDITOR_STATE_PREVIEW;

    ret = mediaeditor_start_preview(g_mediaeditor);
    assert_eq(ret, EXPECTED_RET(MEDIAEDITOR_ERROR_NONE));

    /* Wait changing state to PREVIEW */
    __run_mainloop(&g_mainloop_state);

    ret = mediaeditor_stop_preview(g_mediaeditor);
    assert_eq(ret, EXPECTED_RET(MEDIAEDITOR_ERROR_NONE));

    return 0;
}

/**
 * @testcase    utc_mediaeditor_stop_preview_n1
 * @since_tizen 7.0
 * @description Stops preview\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_stop_preview_n1(void)
{
    int ret = mediaeditor_stop_preview(NULL);
    assert_eq(ret, EXPECTED_RET(MEDIAEDITOR_ERROR_INVALID_PARAMETER));

    return 0;
}

/**
 * @testcase    utc_mediaeditor_stop_preview_n2
 * @since_tizen 7.0
 * @description Stops preview\n
 *              - Stop preview in invalid state
 */
int utc_mediaeditor_stop_preview_n2(void)
{
    int ret = mediaeditor_stop_preview(g_mediaeditor);
    assert_eq(ret, EXPECTED_RET(MEDIAEDITOR_ERROR_INVALID_STATE));

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_layer_p
 * @since_tizen 7.0
 * @description Adds layer\n
 *              - Add a layer
 */
int utc_mediaeditor_add_layer_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_layer_n1
 * @since_tizen 7.0
 * @description Adds layer\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_add_layer_n1(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;

    int ret = mediaeditor_add_layer(NULL, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_layer_n2
 * @since_tizen 7.0
 * @description Adds layer\n
 *              - Add a layer\n
 *              - Pass null layer parameter
 */
int utc_mediaeditor_add_layer_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, NULL, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_remove_layer_p
 * @since_tizen 7.0
 * @description Removes layer\n
 *              - Add a layer and remove it
 */
int utc_mediaeditor_remove_layer_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_remove_layer(g_mediaeditor, layer_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_remove_layer_n1
 * @since_tizen 7.0
 * @description Removes layer\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_remove_layer_n1(void)
{
    unsigned int layer_priority = 0;

    int ret = mediaeditor_remove_layer(NULL, layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_remove_layer_n2
 * @since_tizen 7.0
 * @description Removes layer\n
 *              - Removes invalid layer
 */
int utc_mediaeditor_remove_layer_n2(void)
{
    unsigned int layer_priority = 0;

    int ret = mediaeditor_remove_layer(g_mediaeditor, layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_move_layer_p
 * @since_tizen 7.0
 * @description Removes layer\n
 *              - Add 2 layers\n
 *              - Move layer to existing layer priority
 */
int utc_mediaeditor_move_layer_p(void)
{
    unsigned int layer_id1 = 0;
    unsigned int layer_id2 = 0;
    unsigned int layer_priority1 = 0;
    unsigned int layer_priority2 = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id1, &layer_priority1);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_layer(g_mediaeditor, &layer_id2, &layer_priority2);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_move_layer(g_mediaeditor, layer_id1, layer_priority2);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_move_layer_n1
 * @since_tizen 7.0
 * @description Removes layer\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_move_layer_n1(void)
{
    int ret = mediaeditor_move_layer(NULL, 0, 1);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_move_layer_n2
 * @since_tizen 7.0
 * @description Removes layer\n
 *              - Move invalid layer
 */
int utc_mediaeditor_move_layer_n2(void)
{
    unsigned int layer_id = 1;
    unsigned int layer_priority = 1;

    int ret = mediaeditor_move_layer(g_mediaeditor, layer_id, layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_activate_layer_p
 * @since_tizen 7.0
 * @description Activates layer\n
 *              - Add a layer and activate it
 */
int utc_mediaeditor_activate_layer_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_activate_layer(g_mediaeditor, layer_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_activate_layer_n1
 * @since_tizen 7.0
 * @description Activates layer\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_activate_layer_n1(void)
{
    unsigned int layer_priority = 0;

    int ret = mediaeditor_activate_layer(NULL, layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_activate_layer_n2
 * @since_tizen 7.0
 * @description Activates layer\n
 *              - Activate invalid layer
 */
int utc_mediaeditor_activate_layer_n2(void)
{
    unsigned int layer_priority = 0;

    int ret = mediaeditor_activate_layer(g_mediaeditor, layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_deactivate_layer_p
 * @since_tizen 7.0
 * @description Deactivates layer\n
 *              - Add a layer and deactivate it
 */
int utc_mediaeditor_deactivate_layer_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_deactivate_layer(g_mediaeditor, layer_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_deactivate_layer_n1
 * @since_tizen 7.0
 * @description Deactivates layer\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_deactivate_layer_n1(void)
{
    unsigned int layer_priority = 0;

    int ret = mediaeditor_deactivate_layer(NULL, layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_deactivate_layer_n2
 * @since_tizen 7.0
 * @description Deactivates layer\n
 *              - Deactivate invalid layer
 */
int utc_mediaeditor_deactivate_layer_n2(void)
{
    unsigned int layer_priority = 0;

    int ret = mediaeditor_deactivate_layer(g_mediaeditor, layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_layer_priority_p
 * @since_tizen 7.0
 * @description Gets the layer priority\n
 *              - Add a layer\n
 *              - Get layer priority
 */
int utc_mediaeditor_get_layer_priority_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_layer_priority(g_mediaeditor, layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_layer_priority_n1
 * @since_tizen 7.0
 * @description Gets the layer priority\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_get_layer_priority_n1(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;

    int ret = mediaeditor_get_layer_priority(NULL, layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_layer_priority_n2
 * @since_tizen 7.0
 * @description Gets the layer priority\n
 *              - Add a layer\n
 *              - Pass null layer priority parameter
 */
int utc_mediaeditor_get_layer_priority_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_layer_priority(g_mediaeditor, layer_id, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_layer_priority_n3
 * @since_tizen 7.0
 * @description Gets the layer priority\n
 *              - Pass invalid layer id
 */
int utc_mediaeditor_get_layer_priority_n3(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;

    int ret = mediaeditor_get_layer_priority(g_mediaeditor, layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_layer_lowest_priority_p
 * @since_tizen 7.0
 * @description Gets the layer lowest priority\n
 *              - Add the first layer\n
 *              - Get layer lowest priority and compare it with the first layer\n
 *              - Add the second layer\n
 *              - Get layer lowest priority and compare it with the second layer
 */
int utc_mediaeditor_get_layer_lowest_priority_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int layer_lowest_priority = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_layer_lowest_priority(g_mediaeditor, &layer_lowest_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(layer_lowest_priority, 0);

    ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_layer_lowest_priority(g_mediaeditor, &layer_lowest_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(layer_lowest_priority, 1);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_layer_lowest_priority_n1
 * @since_tizen 7.0
 * @description Gets the layer lowest priority\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_get_layer_lowest_priority_n1(void)
{
    unsigned int layer_priority = 0;

    int ret = mediaeditor_get_layer_lowest_priority(NULL, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_layer_lowest_priority_n2
 * @since_tizen 7.0
 * @description Gets the layer lowest priority\n
 *              - Pass null layer lowest priority parameter
 */
int utc_mediaeditor_get_layer_lowest_priority_n2(void)
{
    int ret = mediaeditor_get_layer_lowest_priority(g_mediaeditor, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_layer_lowest_riority_n3
 * @since_tizen 7.0
 * @description Gets the layer lowest priority\n
 *              - Get layer lowest priority without adding a layer
 */
int utc_mediaeditor_get_layer_lowest_priority_n3(void)
{
    unsigned int layer_priority = 0;

    int ret = mediaeditor_get_layer_lowest_priority(g_mediaeditor, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_OPERATION);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_layer_id_p
 * @since_tizen 7.0
 * @description Gets the layer id\n
 *              - Add 2 layers\n
 *              - Get layer id
 */
int utc_mediaeditor_get_layer_id_p(void)
{
    unsigned int layer_id1 = 0;
    unsigned int layer_id2 = 0;
    unsigned int get_layer_id = 0;
    unsigned int layer_priority1 = 0;
    unsigned int layer_priority2 = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id1, &layer_priority1);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_layer(g_mediaeditor, &layer_id2, &layer_priority2);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_layer_id(g_mediaeditor, layer_priority2, &get_layer_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(get_layer_id, layer_id2);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_layer_id_n1
 * @since_tizen 7.0
 * @description Gets the layer id\n
 *              - Add 2 layers\n
 *              - Get layer id
 */
int utc_mediaeditor_get_layer_id_n1(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;

    int ret = mediaeditor_get_layer_id(NULL, layer_priority, &layer_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_layer_id_n2
 * @since_tizen 7.0
 * @description Gets the layer id\n
 *              - Add a layer\n
 *              - Pass null layer id parameter
 */
int utc_mediaeditor_get_layer_id_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_layer_id(g_mediaeditor, layer_priority, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_layer_id_n3
 * @since_tizen 7.0
 * @description Gets the layer id\n
 *              - Add a layer\n
 *              - Get layer lowest priority
 */
int utc_mediaeditor_get_layer_id_n3(void)
{
    unsigned int layer_id = 0;
    unsigned int get_layer_id = 0;
    unsigned int layer_priority = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_layer_id(g_mediaeditor, 10, &get_layer_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_layer_priority_changed_cb_p
 * @since_tizen 7.0
 * @description Set layer priority changed callback\n
 *              - Set layer priority changed callback
 */
int utc_mediaeditor_set_layer_priority_changed_cb_p(void)
{
    int ret = mediaeditor_set_layer_priority_changed_cb(g_mediaeditor, __mediaeditor_layer_priority_changed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_layer_priority_changed_cb_n1
 * @since_tizen 7.0
 * @description Set layer priority changed callback\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_set_layer_priority_changed_cb_n1(void)
{
    int ret = mediaeditor_set_layer_priority_changed_cb(NULL, __mediaeditor_layer_priority_changed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_layer_priority_changed_cb_n2
 * @since_tizen 7.0
 * @description Set layer priority changed callback\n
 *              - Pass null callback parameter
 */
int utc_mediaeditor_set_layer_priority_changed_cb_n2(void)
{
    int ret = mediaeditor_set_layer_priority_changed_cb(g_mediaeditor, NULL, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_unset_layer_priority_changed_cb_p
 * @since_tizen 7.0
 * @description Unset layer priority changed callback\n
 *              - Set layer priority changed callback and unset it
 */
int utc_mediaeditor_unset_layer_priority_changed_cb_p(void)
{
    int ret = mediaeditor_set_layer_priority_changed_cb(g_mediaeditor, __mediaeditor_layer_priority_changed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_unset_layer_priority_changed_cb(g_mediaeditor);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_unset_layer_priority_changed_cb_n
 * @since_tizen 7.0
 * @description Unset layer priority changed callback\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_unset_layer_priority_changed_cb_n(void)
{
    int ret = mediaeditor_unset_layer_priority_changed_cb(NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_clip_p
 * @since_tizen 7.0
 * @description Adds clip\n
 *              - Add a layer and a clip
 */
int utc_mediaeditor_add_clip_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_clip_n1
 * @since_tizen 7.0
 * @description Adds clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_add_clip_n1(void)
{
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_clip(NULL, g_video_clip_path, layer_priority, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_clip_n2
 * @since_tizen 7.0
 * @description Adds clip\n
 *              - Pass null path
 */
int utc_mediaeditor_add_clip_n2(void)
{
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_clip(g_mediaeditor, NULL, layer_priority, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_clip_n3
 * @since_tizen 7.0
 * @description Adds clip\n
 *              - Adds clip with invalid layer priority
 */
int utc_mediaeditor_add_clip_n3(void)
{
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_priority, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_remove_clip_p
 * @since_tizen 7.0
 * @description Removes clip\n
 *              - Add a layer and a clip\n
 *              - Remove clip
 */
int utc_mediaeditor_remove_clip_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_remove_clip(g_mediaeditor, clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_remove_clip_n1
 * @since_tizen 7.0
 * @description Removes clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_remove_clip_n1(void)
{
    unsigned int clip_id = 0;

    int ret = mediaeditor_remove_clip(NULL, clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_remove_clip_2
 * @since_tizen 7.0
 * @description Removes clip\n\
 *              - Add a layer\n
 *              - Remove invalid clip
 */
int utc_mediaeditor_remove_clip_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_remove_clip(g_mediaeditor, clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_split_clip_p
 * @since_tizen 7.0
 * @description Splits clip\n
 *              - Add a layer and a clip\n
 *              - Split clip
 */
int utc_mediaeditor_split_clip_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int split_clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_split_clip(g_mediaeditor, clip_id, duration / 2, &split_clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_split_clip_n1
 * @since_tizen 7.0
 * @description Splits clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_split_clip_n1(void)
{
    unsigned int clip_id = 0;
    unsigned int split_clip_id = 0;

    int ret = mediaeditor_split_clip(NULL, clip_id, 100, &split_clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_split_clip_n2
 * @since_tizen 7.0
 * @description Splits clip\n
 *              - Add a layer\n
 *              - Split invalid clip
 */
int utc_mediaeditor_split_clip_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int split_clip_id = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_split_clip(g_mediaeditor, clip_id, 50, &split_clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_group_clip_p
 * @since_tizen 7.0
 * @description Groups clip\n
 *              - Add a layer and 2 clips\n
 *              - Group clips
 */
int utc_mediaeditor_group_clip_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_ids[2] = { 0 };
    unsigned int group_id = 0;
    unsigned int start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_ids[0]);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start + duration, duration, in_point, &clip_ids[1]);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_group_clip(g_mediaeditor, clip_ids, 2, &group_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_group_clip_n1
 * @since_tizen 7.0
 * @description Groups clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_group_clip_n1(void)
{
    unsigned int clip_ids[2] = { 0 };
    unsigned int group_id = 0;

    int ret = mediaeditor_group_clip(NULL, clip_ids, 2, &group_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_group_clip_n2
 * @since_tizen 7.0
 * @description Groups clip\n
 *              - Add a layer and a clip\n
 *              - Group clip
 */
int utc_mediaeditor_group_clip_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_ids[2] = { 0 };
    unsigned int group_id = 0;
    unsigned int start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_ids[0]);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_group_clip(g_mediaeditor, clip_ids, 2, &group_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_ungroup_clip_p
 * @since_tizen 7.0
 * @description Ungroups clip\n
 *              - Add a layer and 2 clips\n
 *              - Group clips and ungroup it
 */
int utc_mediaeditor_ungroup_clip_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_ids[2] = { 0 };
    unsigned int *ungrouped_clip_ids;
    unsigned int ungrouped_clip_size = 0;
    unsigned int group_id = 0;
    unsigned int start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_ids[0]);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start + duration, duration, in_point, &clip_ids[1]);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_group_clip(g_mediaeditor, clip_ids, 2, &group_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_ungroup_clip(g_mediaeditor, group_id, &ungrouped_clip_ids, &ungrouped_clip_size);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(ungrouped_clip_size, 2);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_ungroup_clip_n1
 * @since_tizen 7.0
 * @description Ungroups clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_ungroup_clip_n1(void)
{
    unsigned int *ungrouped_clip_ids;
    unsigned int ungrouped_clip_size = 0;
    unsigned int group_id = 0;

    int ret = mediaeditor_ungroup_clip(NULL, group_id, &ungrouped_clip_ids, &ungrouped_clip_size);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_ungroup_clip_n2
 * @since_tizen 7.0
 * @description Ungroups clip\n
 *              - Add a layer and 2 clips\n
 *              - Group clips\n
 *              - Ungroup invalid group id
 */
int utc_mediaeditor_ungroup_clip_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_ids[2] = { 0 };
    unsigned int *ungrouped_clip_ids;
    unsigned int ungrouped_clip_size = 0;
    unsigned int group_id = 0;
    unsigned int start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_ids[0]);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start + duration, duration, in_point, &clip_ids[1]);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_group_clip(g_mediaeditor, clip_ids, 2, &group_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_ungroup_clip(g_mediaeditor, group_id + 1, &ungrouped_clip_ids, &ungrouped_clip_size);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_move_clip_layer_p
 * @since_tizen 7.0
 * @description Moves the layer of clip\n
 *              - Add 2 layers and a clip\n
 *              - Move clip layer
 */
int utc_mediaeditor_move_clip_layer_p(void)
{
    unsigned int layer_id1 = 0;
    unsigned int layer_id2 = 0;
    unsigned int layer_priority1 = 0;
    unsigned int layer_priority2 = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id1, &layer_priority1);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_layer(g_mediaeditor, &layer_id2, &layer_priority2);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id1, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_move_clip_layer(g_mediaeditor, clip_id, layer_priority2);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_move_clip_layer_n1
 * @since_tizen 7.0
 * @description Moves the layer of clip
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_move_clip_layer_n1(void)
{
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;

    int ret = mediaeditor_move_clip_layer(NULL, clip_id, layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_move_clip_layer_n2
 * @since_tizen 7.0
 * @description Moves the layer of clip\n
 *              - Add a layer
 *              - Move invalid clip
 */
int utc_mediaeditor_move_clip_layer_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_move_clip_layer(g_mediaeditor, clip_id, layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_start_p
 * @since_tizen 7.0
 * @description Gets the starting position of clip\n
 *              - Add a layer and a clip
 *              - Get clip start value
 */
int utc_mediaeditor_get_clip_start_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int get_start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_start(g_mediaeditor, clip_id, &get_start);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(get_start, start);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_start_n1
 * @since_tizen 7.0
 * @description Gets the starting position of clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_get_clip_start_n1(void)
{
    unsigned int clip_id = 0;
    unsigned int get_start = 0;

    int ret = mediaeditor_get_clip_start(NULL, clip_id, &get_start);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_start_n2
 * @since_tizen 7.0
 * @description Gets the starting position of clip\n
 *              - Add a layer and a clip\n
 *              - Get start value with null start parameter
 */
int utc_mediaeditor_get_clip_start_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_start(g_mediaeditor, clip_id, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_start_n3
 * @since_tizen 7.0
 * @description Gets the starting position of clip\n
 *              - Add a layer\n
 *              - Get start value with invalid clip id
 */
int utc_mediaeditor_get_clip_start_n3(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int get_start = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_start(g_mediaeditor, clip_id, &get_start);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_start_p
 * @since_tizen 7.0
 * @description Sets the starting position of clip\n
 *              - Add a layer and a clip\n
 *              - Set clip start value and get it
 */
int utc_mediaeditor_set_clip_start_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int set_start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_set_clip_start(g_mediaeditor, clip_id, set_start);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_start(g_mediaeditor, clip_id, &start);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(set_start, start);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_start_n1
 * @since_tizen 7.0
 * @description Sets the starting position of clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_set_clip_start_n1(void)
{
    unsigned int clip_id = 0;
    unsigned int start = 0;

    int ret = mediaeditor_set_clip_start(NULL, clip_id, start);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_start_n2
 * @since_tizen 7.0
 * @description Sets the starting position of clip\n
 *              - Add a layer\n
 *              - Set start value with invalid clip id
 */
int utc_mediaeditor_set_clip_start_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_set_clip_start(g_mediaeditor, clip_id, start);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_duration_p
 * @since_tizen 7.0
 * @description Gets the duration of clip\n
 *              - Add a layer and a clip\n
 *              - Get clip duration value
 */
int utc_mediaeditor_get_clip_duration_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int duration = 100;
    unsigned int get_duration = 0;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_duration(g_mediaeditor, clip_id, &get_duration);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(get_duration, duration);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_duration_n1
 * @since_tizen 7.0
 * @description Gets the duration of clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_get_clip_duration_n1(void)
{
    unsigned int clip_id = 0;
    unsigned int get_duration = 0;

    int ret = mediaeditor_get_clip_duration(NULL, clip_id, &get_duration);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_duration_n2
 * @since_tizen 7.0
 * @description Gets the duration of clip\n
 *              - Add a layer and a clip\n
 *              - Get duration value with null duration parameter
 */
int utc_mediaeditor_get_clip_duration_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_duration(g_mediaeditor, clip_id, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_duration_n3
 * @since_tizen 7.0
 * @description Gets the duration of clip\n
 *              - Add a layer\n
 *              - Get duration value with invalid clip id
 */
int utc_mediaeditor_get_clip_duration_n3(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int get_duration = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_duration(g_mediaeditor, clip_id, &get_duration);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_duration_p
 * @since_tizen 7.0
 * @description Sets the duration of clip\n
 *              - Add a layer and a clip\n
 *              - Set duration value and get it
 */
int utc_mediaeditor_set_clip_duration_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int duration = 100;
    unsigned int set_duration = 200;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_set_clip_duration(g_mediaeditor, clip_id, set_duration);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_duration(g_mediaeditor, clip_id, &duration);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(set_duration, duration);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_duration_n1
 * @since_tizen 7.0
 * @description Sets the duration of clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_set_clip_duration_n1(void)
{
    unsigned int clip_id = 0;
    unsigned int set_duration = 100;

    int ret = mediaeditor_set_clip_duration(NULL, clip_id, set_duration);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_duration_n2
 * @since_tizen 7.0
 * @description Sets the duration of clip\n
 *              - Add a layer\n
 *              - Sets duration value with invalid clip id
 */
int utc_mediaeditor_set_clip_duration_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int duration = 100;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_set_clip_duration(g_mediaeditor, clip_id, duration);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_in_point_p
 * @since_tizen 7.0
 * @description Gets the in_point of clip\n
 *              - Add a layer and a clip\n
 *              - Get clip in_pint value
 */
int utc_mediaeditor_get_clip_in_point_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int duration = 100;
    unsigned int in_point = 100;
    unsigned int get_in_point = 10;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_in_point(g_mediaeditor, clip_id, &get_in_point);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(get_in_point, in_point);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_in_point_n1
 * @since_tizen 7.0
 * @description Gets the in_point of clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_get_clip_in_point_n1(void)
{
    unsigned int clip_id = 0;
    unsigned int get_in_point = 0;

    int ret = mediaeditor_get_clip_in_point(NULL, clip_id, &get_in_point);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_in_point_n2
 * @since_tizen 7.0
 * @description Gets the in_point of clip\n
 *              - Add a layer and a clip\n
 *              - Get in_point value with null in_point parameter
 */
int utc_mediaeditor_get_clip_in_point_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_in_point(g_mediaeditor, clip_id, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_in_point_n3
 * @since_tizen 7.0
 * @description Gets the in_point of clip\n
 *              - Add a layer\n
 *              - Gets in_point value with invalid clip id
 */
int utc_mediaeditor_get_clip_in_point_n3(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int get_in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_in_point(g_mediaeditor, clip_id, &get_in_point);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_in_point_p
 * @since_tizen 7.0
 * @description Sets the in_point of clip\n
 *              - Add a layer and a clip\n
 *              - Set in_point value and get it
 */
int utc_mediaeditor_set_clip_in_point_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int duration = 100;
    unsigned int in_point = 100;
    unsigned int set_in_point = 200;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_set_clip_in_point(g_mediaeditor, clip_id, set_in_point);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_in_point(g_mediaeditor, clip_id, &in_point);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(set_in_point, in_point);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_in_point_n1
 * @since_tizen 7.0
 * @description Sets the in_point of clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_set_clip_in_point_n1(void)
{
    unsigned int clip_id = 0;
    unsigned int set_in_point = 100;

    int ret = mediaeditor_set_clip_in_point(NULL, clip_id, set_in_point);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_in_point_n2
 * @since_tizen 7.0
 * @description Sets the in_point of clip\n
 *              - Add a layer\n
 *              - Sets in_point value with invalid clip id
 */
int utc_mediaeditor_set_clip_in_point_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int in_point = 100;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_set_clip_in_point(g_mediaeditor, clip_id, in_point);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_resolution_p
 * @since_tizen 7.0
 * @description Gets the resolution of clip\n
 *              - Add a layer and a clip\n
 *              - Get resolution value
 */
int utc_mediaeditor_get_clip_resolution_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int duration = 100;
    unsigned int in_point = 100;
    unsigned int width = 0;
    unsigned int height = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_resolution(g_mediaeditor, clip_id, &width, &height);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_resolution_n1
 * @since_tizen 7.0
 * @description Gets the resolution of clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_get_clip_resolution_n1(void)
{
    unsigned int clip_id = 0;
    unsigned int width = 0;
    unsigned int height = 0;

    int ret = mediaeditor_get_clip_resolution(NULL, clip_id, &width, &height);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_resolution_n2
 * @since_tizen 7.0
 * @description Gets the resolution of clip\n
 *              - Add a layer and a clip\n
 *              - Get resolution value with null parameter
 */
int utc_mediaeditor_get_clip_resolution_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int duration = 100;
    unsigned int in_point = 0;
    unsigned int width = 0;
    unsigned int height = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_resolution(g_mediaeditor, clip_id, NULL, &height);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    ret = mediaeditor_get_clip_resolution(g_mediaeditor, clip_id, &width, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_resolution_n3
 * @since_tizen 7.0
 * @description Gets the resolution of clip\n
 *              - Add a layer\n
 *              - Get resolution value with invalid clip id
 */
int utc_mediaeditor_get_clip_resolution_n3(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int width = 0;
    unsigned int height = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_resolution(g_mediaeditor, clip_id, &width, &height);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_resolution_n4
 * @since_tizen 7.0
 * @description Gets the resolution of clip\n
 *              - Add a layer and a clip\n
 *              - Get resolution with audio clip
 */
int utc_mediaeditor_get_clip_resolution_n4(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 100;
    unsigned int width = 0;
    unsigned int height = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_audio_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_resolution(g_mediaeditor, clip_id, &width, &height);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_OPERATION);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_resolution_p
 * @since_tizen 7.0
 * @description Sets the resolution of clip\n
 *              - Add a layer and a clip\n
 *              - Set resolution value and get it
 */
int utc_mediaeditor_set_clip_resolution_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int duration = 100;
    unsigned int in_point = 100;
    unsigned int set_width = 320;
    unsigned int set_height = 160;
    unsigned int get_width = 0;
    unsigned int get_height = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_set_clip_resolution(g_mediaeditor, clip_id, set_width, set_height);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_resolution(g_mediaeditor, clip_id, &get_width, &get_height);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(set_width, get_width);
    assert_eq(set_height, get_height);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_resolution_n1
 * @since_tizen 7.0
 * @description Sets the resolution of clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_set_clip_resolution_n1(void)
{
    unsigned int clip_id = 0;
    unsigned int width = 320;
    unsigned int height = 160;

    int ret = mediaeditor_set_clip_resolution(NULL, clip_id, width, height);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_resolution_n2
 * @since_tizen 7.0
 * @description Sets the resolution of clip\n
 *              - Set resolution with invalid clip id
 */
int utc_mediaeditor_set_clip_resolution_n2(void)
{
    unsigned int clip_id = 0;
    unsigned int width = 320;
    unsigned int height = 160;

    int ret = mediaeditor_set_clip_resolution(g_mediaeditor, clip_id, width, height);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_resolution_n3
 * @since_tizen 7.0
 * @description Sets the resolution of clip\n
 *              - Add a layer and a clip\n
 *              - Set resolution value with audio clip
 */
int utc_mediaeditor_set_clip_resolution_n3(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 100;
    unsigned int in_point = 100;
    unsigned int set_width = 320;
    unsigned int set_height = 160;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_audio_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_set_clip_resolution(g_mediaeditor, clip_id, set_width, set_height);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_OPERATION);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_volume_p
 * @since_tizen 7.0
 * @description Gets the volume of clip\n
 *              - Add a layer and a clip\n
 *              - Get volume value
 */
int utc_mediaeditor_get_clip_volume_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int duration = 100;
    unsigned int in_point = 100;
    double volume = 0.0;
    double default_volume = 1.0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_volume(g_mediaeditor, clip_id, &volume);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(volume, default_volume);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_volume_n1
 * @since_tizen 7.0
 * @description Gets the volume of clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_get_clip_volume_n1(void)
{
    unsigned int clip_id = 0;
    double volume = 0.0;

    int ret = mediaeditor_get_clip_volume(NULL, clip_id, &volume);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_volume_n2
 * @since_tizen 7.0
 * @description Gets the volume of clip\n
 *              - Add a layer and a clip\n
 *              - Gets volume value with null volume parameter
 */
int utc_mediaeditor_get_clip_volume_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int duration = 100;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_volume(g_mediaeditor, clip_id, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_get_clip_volume_n3
 * @since_tizen 7.0
 * @description Gets the volume of clip\n
 *              - Add a layer\n
 *              - Gets volume with invalid clip id
 */
int utc_mediaeditor_get_clip_volume_n3(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    double volume = 0.0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_volume(g_mediaeditor, clip_id, &volume);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_volume_p
 * @since_tizen 7.0
 * @description Sets the volume of clip\n
 *              - Add a layer and a clip\n
 *              - Get default volume value and check it\n
 *              - Set volume value and get it, check it
 */
int utc_mediaeditor_set_clip_volume_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 10;
    unsigned int duration = 100;
    unsigned int in_point = 100;
    double set_volume = 0.5;
    double get_volume = 0.0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_set_clip_volume(g_mediaeditor, clip_id, set_volume);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_get_clip_volume(g_mediaeditor, clip_id, &get_volume);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);
    assert_eq(get_volume, set_volume);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_volume_n1
 * @since_tizen 7.0
 * @description Sets the volume of clip\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_set_clip_volume_n1(void)
{
    unsigned int clip_id = 0;
    double volume = 1.0;

    int ret = mediaeditor_set_clip_volume(NULL, clip_id, volume);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_clip_volume_n2
 * @since_tizen 7.0
 * @description Sets the volume of clip\n
 *              - Sets volume value with invalid clip id
 */
int utc_mediaeditor_set_clip_volume_n2(void)
{
    unsigned int clip_id = 0;
    double volume = 1.0;

    int ret = mediaeditor_set_clip_volume(g_mediaeditor, clip_id, volume);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_transition_p
 * @since_tizen 7.0
 * @description Adds transition\n
 *              - Add a layer and 2 clips\n
 *              - Add transition
 */
int utc_mediaeditor_add_transition_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 200;
    unsigned int in_point = 0;
    unsigned int transition_start = 0;
    unsigned int transition_duration = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start + (duration / 2), duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    transition_start = start + (duration / 2);
    transition_duration = duration / 2;

    ret = mediaeditor_add_transition(g_mediaeditor, MEDIAEDITOR_TRANSITION_TYPE_CROSSFADE, layer_id, transition_start, transition_duration);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_transition_n1
 * @since_tizen 7.0
 * @description Adds transition\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_add_transition_n1(void)
{
    unsigned int layer_priority = 0;
    unsigned int transition_start = 0;
    unsigned int transition_duration = 100;

    int ret = mediaeditor_add_transition(NULL, MEDIAEDITOR_TRANSITION_TYPE_CROSSFADE, layer_priority, transition_start, transition_duration);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_transition_n2
 * @since_tizen 7.0
 * @description Adds transition\n
 *              - Add a layer and 2 clips\n
 *              - Pass invalid type parameter
 */
int utc_mediaeditor_add_transition_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 200;
    unsigned int in_point = 0;
    unsigned int transition_start = 0;
    unsigned int transition_duration = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start + (duration / 2), duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    transition_start = start + (duration / 2);
    transition_duration = duration / 2;

    ret = mediaeditor_add_transition(g_mediaeditor, MEDIAEDITOR_TRANSITION_TYPE_CROSSFADE + 1, layer_priority, transition_start, transition_duration);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    ret = mediaeditor_add_transition(g_mediaeditor, MEDIAEDITOR_TRANSITION_TYPE_NONE - 1, layer_priority, transition_start, transition_duration);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_transition_n3
 * @since_tizen 7.0
 * @description Adds transition\n
 *              - Pass invalid layer priority
 */
int utc_mediaeditor_add_transition_n3(void)
{
    unsigned int layer_priority = 0;
    unsigned int start = 0;
    unsigned int duration = 200;
    unsigned int transition_start = 0;
    unsigned int transition_duration = 0;

    transition_start = start + (duration / 2);
    transition_duration = duration / 2;

    int ret = mediaeditor_add_transition(g_mediaeditor, MEDIAEDITOR_TRANSITION_TYPE_CROSSFADE, layer_priority, transition_start, transition_duration);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_effect_p
 * @since_tizen 7.0
 * @description Adds effect\n
 *              - Add a layer and a clip\n
 *              - Add a effect
 */
int utc_mediaeditor_add_effect_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int effect_id = 0;
    unsigned int start = 0;
    unsigned int duration = 200;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_effect(g_mediaeditor, MEDIAEDITOR_EFFECT_VIDEO_TYPE_AGINGTV, layer_id, start, duration, &effect_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_effect_n1
 * @since_tizen 7.0
 * @description Adds effect\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_add_effect_n1(void)
{
    unsigned int layer_priority = 0;
    unsigned int effect_id = 0;
    unsigned int start = 0;
    unsigned int duration = 200;

    int ret = mediaeditor_add_effect(NULL, MEDIAEDITOR_EFFECT_VIDEO_TYPE_AGINGTV, layer_priority, start, duration, &effect_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_effect_n2
 * @since_tizen 7.0
 * @description Adds effect\n
 *              - Add a layer\n
 *              - Pass invalid type parameter
 */
int utc_mediaeditor_add_effect_n2(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int effect_id = 0;
    unsigned int start = 0;
    unsigned int duration = 200;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_effect(g_mediaeditor, MEDIAEDITOR_EFFECT_AUDIO_TYPE_ECHO + 1, layer_id, start, duration, &effect_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    ret = mediaeditor_add_effect(g_mediaeditor, MEDIAEDITOR_EFFECT_TYPE_NONE - 1, layer_id, start, duration, &effect_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_add_effect_n3
 * @since_tizen 7.0
 * @description Adds effect\n
 *              - Add a clip\n
 *              - Pass invalid layer id
 */
int utc_mediaeditor_add_effect_n3(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int effect_id = 0;
    unsigned int start = 0;
    unsigned int duration = 200;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_effect(g_mediaeditor, MEDIAEDITOR_EFFECT_VIDEO_TYPE_AGINGTV, layer_id + 1, start, duration, &effect_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_remove_effect_p
 * @since_tizen 7.0
 * @description Removes effect\n
 *              - Add a layer and a clip\n
 *              - Add a effect and remove it
 */
int utc_mediaeditor_remove_effect_p(void)
{
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int effect_id = 0;
    unsigned int start = 0;
    unsigned int duration = 200;
    unsigned int in_point = 0;

    int ret = mediaeditor_add_layer(g_mediaeditor, &layer_id, &layer_priority);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_clip(g_mediaeditor, g_video_clip_path, layer_id, start, duration, in_point, &clip_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_add_effect(g_mediaeditor, MEDIAEDITOR_EFFECT_VIDEO_TYPE_AGINGTV, layer_id, start, duration, &effect_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_remove_effect(g_mediaeditor, effect_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_remove_effect_n1
 * @since_tizen 7.0
 * @description Removes effect\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_remove_effect_n1(void)
{
    unsigned int effect_id = 0;

    int ret = mediaeditor_remove_effect(NULL, effect_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_remove_effect_n2
 * @since_tizen 7.0
 * @description Removes effect\n
 *              - Pass invalid effect_id
 */
int utc_mediaeditor_remove_effect_n2(void)
{
    unsigned int effect_id = 0;

    int ret = mediaeditor_remove_effect(g_mediaeditor, effect_id);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_create_project_p
 * @since_tizen 7.0
 * @description Creates project\n
 *              - Create a project
 */
int utc_mediaeditor_create_project_p(void)
{
    int ret = mediaeditor_create_project(g_mediaeditor, g_project_new_path);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_create_project_n1
 * @since_tizen 7.0
 * @description Creates project\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_create_project_n1(void)
{
    int ret = mediaeditor_create_project(NULL, g_project_new_path);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_create_project_n2
 * @since_tizen 7.0
 * @description Creates project\n
 *              - Pass null path parameter
 */
int utc_mediaeditor_create_project_n2(void)
{
    int ret = mediaeditor_create_project(g_mediaeditor, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_load_project_p
 * @since_tizen 7.0
 * @description Loads project\n
 *              - Load a project
 */
int utc_mediaeditor_load_project_p(void)
{
    int ret = mediaeditor_load_project(g_mediaeditor, g_project_load_path, __mediaeditor_project_loaded_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    __run_mainloop(&g_mainloop_project);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_load_project_n1
 * @since_tizen 7.0
 * @description Loads project\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_load_project_n1(void)
{
    int ret = mediaeditor_load_project(NULL, g_project_load_path, __mediaeditor_project_loaded_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_load_project_n2
 * @since_tizen 7.0
 * @description Loads project\n
 *              - Load a project with null path parameter
 */
int utc_mediaeditor_load_project_n2(void)
{
    int ret = mediaeditor_load_project(g_mediaeditor, NULL, __mediaeditor_project_loaded_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_save_project_p
 * @since_tizen 7.0
 * @description Saves project\n
 *              - Create a project and save it
 */
int utc_mediaeditor_save_project_p(void)
{
    int ret = mediaeditor_create_project(g_mediaeditor, g_project_new_path);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_save_project(g_mediaeditor);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_save_project_n1
 * @since_tizen 7.0
 * @description Saves project\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_save_project_n1(void)
{
    int ret = mediaeditor_save_project(NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_save_project_n2
 * @since_tizen 7.0
 * @description Saves project\n
 *              - Saves project which is not loaded or created before
 */
int utc_mediaeditor_save_project_n2(void)
{
    int ret = mediaeditor_save_project(g_mediaeditor);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_OPERATION);

    return 0;
}
