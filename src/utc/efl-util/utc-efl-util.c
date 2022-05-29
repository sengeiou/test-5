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
#include <efl_util.h>
#include <Elementary.h>

/**
 * @function		utc_efl_util_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_efl_util_startup(void)
{
    elm_init(0, NULL);
}

/**
 * @function		utc_efl_util_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_efl_util_cleanup(void)
{
    elm_shutdown();
}


static void _win_del(void *data, Evas_Object *obj, void *event)
{
    elm_exit();
}


static Evas_Object* _create_normal_win(const char *name)
{
    Evas_Object *eo = NULL;

    eo = elm_win_add(NULL, name, ELM_WIN_BASIC);
    if (eo)
    {
        elm_win_title_set(eo, name);
        elm_win_borderless_set(eo, EINA_TRUE);
        evas_object_smart_callback_add(eo, "delete,request",
                _win_del, NULL);
        elm_win_indicator_mode_set(eo, ELM_WIN_INDICATOR_SHOW);
    }

    return eo;
}


static Evas_Object* _create_notification_win(const char *name)
{
    Evas_Object *eo;

    eo = elm_win_add(NULL, name, ELM_WIN_NOTIFICATION);
    if (eo)
    {
        elm_win_title_set(eo, name);
        elm_win_borderless_set(eo, EINA_TRUE);
        evas_object_smart_callback_add(eo, "delete,request",
                _win_del, NULL);
        elm_win_indicator_mode_set(eo, ELM_WIN_INDICATOR_SHOW);
    }

    return eo;
}


static Evas_Object* _create_normal_alpha_win(const char *name)
{
    Evas_Object *eo = NULL;

    eo = elm_win_add(NULL, name, ELM_WIN_BASIC);
    if (eo)
    {
        elm_win_alpha_set(eo, EINA_TRUE);
        elm_win_title_set(eo, name);
        elm_win_borderless_set(eo, EINA_TRUE);
        evas_object_smart_callback_add(eo, "delete,request",
                _win_del, NULL);
        elm_win_indicator_mode_set(eo, ELM_WIN_INDICATOR_SHOW);
    }

    return eo;
}

/**
 * @testcase		utc_efl_util_set_notification_window_level_n1
 * @since_tizen		2.3
 * @description		to verify whether efl_util_set_notification_window_level
 *                  API can handle the error case a user sets the notification
 *                  level without window handle.
 */
int utc_efl_util_set_notification_window_level_n1(void)
{
    int ret = 0;

    ret = efl_util_set_notification_window_level(NULL,  EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM);

    assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_notification_window_level_n2
 * @since_tizen		2.3
 * @description		to verify whether efl_util_set_notification_window_level
 *                  API can handle the error case a user sets the notification
 *                  level with NORMAL window.
 */
int utc_efl_util_set_notification_window_level_n2(void)
{
    Evas_Object *win = NULL;
    int ret = 0;

    win = _create_normal_win("Normal window");
    assert(win);

    ret = efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM);
    assert_eq(ret, EFL_UTIL_ERROR_NOT_SUPPORTED_WINDOW_TYPE);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_notification_window_level_n3
 * @since_tizen		2.3
 * @description		to verify whether efl_util_set_notification_window_level
 *                  API can handle the error case a user sets the INVALID
 *                  notification level parameter.
 */
int utc_efl_util_set_notification_window_level_n3(void)
{
    Evas_Object *win = NULL;
    int ret = 0;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    ret = efl_util_set_notification_window_level(win, 100);
    assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_efl_util_get_notification_window_level_n1
 * @since_tizen		2.3
 * @description		to verify whether efl_util_get_notification_window_level
 *                  API can handle the error case a user requests
 *                  the notification level without window handle.
 */
int utc_efl_util_get_notification_window_level_n1(void)
{
    int ret = 0;
    efl_util_notification_level_e level = 0;

    ret = efl_util_get_notification_window_level(NULL, &level);
    assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase		utc_efl_util_get_notification_window_level_n2
 * @since_tizen		2.3
 * @description		to verify whether efl_util_get_notification_window_level
 *                  API can handle the error case a user requests the
 *                  notifiction level form NORMAL window.
 */
int utc_efl_util_get_notification_window_level_n2(void)
{
    Evas_Object *win = NULL;
    int ret = 0;
    efl_util_notification_level_e level = 0;

    win = _create_normal_win("Normal Type Window");
    assert(win);

    ret = efl_util_get_notification_window_level(win, &level);
    assert_eq(ret, EFL_UTIL_ERROR_NOT_SUPPORTED_WINDOW_TYPE);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_notification_window_level_p1
 * @since_tizen		2.3
 * @description		to verify whether efl_util_set_notification_window_level
 *                  API is working properly in the case a user sets the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT
 */
int utc_efl_util_set_notification_window_level_p1(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    ret = efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_notification_window_level_p2
 * @since_tizen		2.3
 * @description		to verify whether efl_util_set_notification_window_level
 *                  API is working properly in the case a user sets the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM
 */
int utc_efl_util_set_notification_window_level_p2(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    ret = efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    ret = efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_notification_window_level_p3
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_notification_window_level
 *                  API is working properly in the case a user sets the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_TOP
 */
int utc_efl_util_set_notification_window_level_p3(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    ret = efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_TOP);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_notification_window_level_p4
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_notification_window_level
 *                  API is working properly in the case a user sets the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_NONE
 */
int utc_efl_util_set_notification_window_level_p4(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    ret = efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_NONE);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_notification_window_level_p5
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_notification_window_level
 *                  API is working properly in the case a user sets the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT
 */
int utc_efl_util_set_notification_window_level_p5(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    ret = efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_notification_window_level_p6
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_notification_window_level
 *                  API is working properly in the case a user sets the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM
 */
int utc_efl_util_set_notification_window_level_p6(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    ret = efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_notification_window_level_p7
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_notification_window_level
 *                  API is working properly in the case a user sets the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_HIGH
 */
int utc_efl_util_set_notification_window_level_p7(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    ret = efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_HIGH);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_notification_window_level_p8
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_notification_window_level
 *                  API is working properly in the case a user sets the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_TOP
 */
int utc_efl_util_set_notification_window_level_p8(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    ret = efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_TOP);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_efl_util_get_notification_window_level_p1
 * @since_tizen		2.3
 * @description		to verify whether efl_util_get_notification_window_level
 *                  API is working properly in the case a user request the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT
 */
int utc_efl_util_get_notification_window_level_p1(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    efl_util_notification_level_e level = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT);
    evas_object_show(win);
    ret = efl_util_get_notification_window_level(win, &level);

    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(level, EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT);

    return 0;
}

/**
 * @testcase		utc_efl_util_get_notification_window_level_p2
 * @since_tizen		2.3
 * @description		to verify whether efl_util_get_notification_window_level
 *                  API is working properly in the case a user request the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM
 */
int utc_efl_util_get_notification_window_level_p2(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    efl_util_notification_level_e level = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT);
    evas_object_show(win);
    ret = efl_util_get_notification_window_level(win, &level);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(level, EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT);
    efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM);
    ret = efl_util_get_notification_window_level(win, &level);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(level, EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM);

    return 0;
}

/**
 * @testcase		utc_efl_util_get_notification_window_level_p3
 * @since_tizen		2.4
 * @description		to verify whether efl_util_get_notification_window_level
 *                  API is working properly in the case a user request the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_TOP
 */
int utc_efl_util_get_notification_window_level_p3(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    efl_util_notification_level_e level = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_TOP);
    evas_object_show(win);
    ret = efl_util_get_notification_window_level(win, &level);

    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(level, EFL_UTIL_NOTIFICATION_LEVEL_TOP);

    return 0;
}

/**
 * @testcase		utc_efl_util_get_notification_window_level_p4
 * @since_tizen		2.4
 * @description		to verify whether efl_util_get_notification_window_level
 *                  API is working properly in the case a user request the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_NONE
 */
int utc_efl_util_get_notification_window_level_p4(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    efl_util_notification_level_e level = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_NONE);
    evas_object_show(win);
    ret = efl_util_get_notification_window_level(win, &level);

    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(level, EFL_UTIL_NOTIFICATION_LEVEL_NONE);

    return 0;
}

/**
 * @testcase		utc_efl_util_get_notification_window_level_p5
 * @since_tizen		2.4
 * @description		to verify whether efl_util_get_notification_window_level
 *                  API is working properly in the case a user request the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT
 */
int utc_efl_util_get_notification_window_level_p5(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    efl_util_notification_level_e level = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT);
    evas_object_show(win);
    ret = efl_util_get_notification_window_level(win, &level);

    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(level, EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT);

    return 0;
}

/**
 * @testcase		utc_efl_util_get_notification_window_level_p6
 * @since_tizen		2.4
 * @description		to verify whether efl_util_get_notification_window_level
 *                  API is working properly in the case a user request the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM
 */
int utc_efl_util_get_notification_window_level_p6(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    efl_util_notification_level_e level = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM);
    evas_object_show(win);
    ret = efl_util_get_notification_window_level(win, &level);

    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(level, EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM);

    return 0;
}

/**
 * @testcase		utc_efl_util_get_notification_window_level_p7
 * @since_tizen		2.4
 * @description		to verify whether efl_util_get_notification_window_level
 *                  API is working properly in the case a user request the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_HIGH
 */
int utc_efl_util_get_notification_window_level_p7(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    efl_util_notification_level_e level = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_HIGH);
    evas_object_show(win);
    ret = efl_util_get_notification_window_level(win, &level);

    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(level, EFL_UTIL_NOTIFICATION_LEVEL_HIGH);

    return 0;
}

/**
 * @testcase		utc_efl_util_get_notification_window_level_p8
 * @since_tizen		2.4
 * @description		to verify whether efl_util_get_notification_window_level
 *                  API is working properly in the case a user request the
 *                  notification level EFL_UTIL_NOTIFICATION_LEVEL_TOP
 */
int utc_efl_util_get_notification_window_level_p8(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    efl_util_notification_level_e level = -1;

    win = _create_notification_win("Notification Type Window");
    assert(win);

    efl_util_set_notification_window_level(win, EFL_UTIL_NOTIFICATION_LEVEL_TOP);
    evas_object_show(win);
    ret = efl_util_get_notification_window_level(win, &level);

    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(level, EFL_UTIL_NOTIFICATION_LEVEL_TOP);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_window_opaque_state_p1
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_window_opaque_state API is
 *                  working properly.
 */
int utc_efl_util_set_window_opaque_state_p1(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_normal_alpha_win("Normal Alpha Window");
    assert(win);

    ret = efl_util_set_window_opaque_state(win, 0);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_window_opaque_state_p2
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_window_opaque_state API is
 *                  working properly.
 */
int utc_efl_util_set_window_opaque_state_p2(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_normal_alpha_win("Normal Alpha Window");
    assert(win);

    ret = efl_util_set_window_opaque_state(win, 1);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_window_opaque_state_n1
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_window_opaque_state API can
 *                  handle the error case a user set opaque state without window.
 */
int utc_efl_util_set_window_opaque_state_n1(void)
{
    int ret = -1;

    ret = efl_util_set_window_opaque_state(NULL, 1);
    assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_window_opaque_state_n2
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_window_opaque_state API can
 *                  handle the error case a user set opaque state with invalid
 *                  value.
 */
int utc_efl_util_set_window_opaque_state_n2(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_normal_alpha_win("Normal Alpha Window");
    assert(win);

    ret = efl_util_set_window_opaque_state(win, -1);
    assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_window_screen_mode_p1
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_window_screen_mode API is
 *                  working properly in the case a user sets the mode
 *                  EFL_UTIL_SCREEN_MODE_DEFAULT
 */
int utc_efl_util_set_window_screen_mode_p1(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_normal_win("Screen mode test");
    assert(win);

    ret = efl_util_set_window_screen_mode(win, EFL_UTIL_SCREEN_MODE_DEFAULT);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_window_screen_mode_p2
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_window_screen_mode API is
 *                  working properly in the case a user sets the mode
 *                  EFL_UTIL_SCREEN_MODE_ALWAYS_ON
 */
int utc_efl_util_set_window_screen_mode_p2(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_normal_win("Screen mode test");
    assert(win);

    ret = efl_util_set_window_screen_mode(win, EFL_UTIL_SCREEN_MODE_ALWAYS_ON);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_window_screen_mode_p3
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_window_screen_mode API is
 *                  working properly in the case a user changes the mode repeatedly
 *                  EFL_UTIL_SCREEN_MODE_ALWAYS_ON & EFL_UTIL_SCREEN_MODE_DEFAULT
 */
int utc_efl_util_set_window_screen_mode_p3(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    efl_util_screen_mode_e mode;

    win = _create_normal_win("Screen mode test");
    assert(win);

    ret = efl_util_set_window_screen_mode(win, EFL_UTIL_SCREEN_MODE_ALWAYS_ON);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    ret = efl_util_set_window_screen_mode(win, EFL_UTIL_SCREEN_MODE_DEFAULT);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    ret = efl_util_set_window_screen_mode(win, EFL_UTIL_SCREEN_MODE_ALWAYS_ON);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    ret = efl_util_set_window_screen_mode(win, EFL_UTIL_SCREEN_MODE_DEFAULT);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    ret = efl_util_get_window_screen_mode(win, &mode);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(mode, EFL_UTIL_SCREEN_MODE_DEFAULT);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_window_screen_mode_n1
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_window_screen_mode API can
 *                  handle the error case a user sets screen mode without window.
 */
int utc_efl_util_set_window_screen_mode_n1(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    ret = efl_util_set_window_screen_mode(win, EFL_UTIL_SCREEN_MODE_ALWAYS_ON);
    assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_efl_util_set_window_screen_mode_n2
 * @since_tizen		2.4
 * @description		to verify whether efl_util_set_window_screen_mode API can
 *                  handle the error case a user sets screen mode with invalid
 *                  value.
 */
int utc_efl_util_set_window_screen_mode_n2(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_normal_win("Screen mode test");
    assert(win);

    ret = efl_util_set_window_screen_mode(win, 3);
    assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_efl_util_get_window_screen_mode_p1
 * @since_tizen		2.4
 * @description		to verify whether efl_util_get_window_screen_mode API is
 *                  working properly in the case a user requests the mode
 *                  EFL_UTIL_SCREEN_MODE_DEFAULT
 */
int utc_efl_util_get_window_screen_mode_p1(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    efl_util_screen_mode_e mode;

    win = _create_normal_win("Screen mode test");
    assert(win);

    ret = efl_util_set_window_screen_mode(win, EFL_UTIL_SCREEN_MODE_DEFAULT);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    ret = efl_util_get_window_screen_mode(win, &mode);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(mode, EFL_UTIL_SCREEN_MODE_DEFAULT);

    return 0;
}

/**
 * @testcase		utc_efl_util_get_window_screen_mode_p2
 * @since_tizen		2.4
 * @description		to verify whether efl_util_get_window_screen_mode API is
 *                  working properly in the case a user requests the mode
 *                  EFL_UTIL_SCREEN_MODE_ALWAYS_ON
 */
int utc_efl_util_get_window_screen_mode_p2(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    efl_util_screen_mode_e mode;

    win = _create_normal_win("Screen mode test");
    assert(win);

    ret = efl_util_set_window_screen_mode(win, EFL_UTIL_SCREEN_MODE_ALWAYS_ON);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    ret = efl_util_get_window_screen_mode(win, &mode);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(mode, EFL_UTIL_SCREEN_MODE_ALWAYS_ON);

	return 0;
}

/**
 * @testcase		utc_efl_util_get_window_screen_mode_n1
 * @since_tizen		2.4
 * @description		to verify whether efl_util_get_window_screen_mode API can
 *                  handle the error case a user requests screen mode without
 *                  window.
 */
int utc_efl_util_get_window_screen_mode_n1(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    efl_util_screen_mode_e mode;

    ret = efl_util_get_window_screen_mode(win, &mode);
    assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_efl_util_get_window_screen_mode_n2
 * @since_tizen		2.4
 * @description		to verify whether efl_util_get_window_screen_mode API can
 *                  handle the error case a user requests screen mode without
 *                  setting the mode.
 */
int utc_efl_util_get_window_screen_mode_n2(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    efl_util_screen_mode_e mode;

    win = _create_normal_win("Screen mode test");
    assert(win);

    ret = efl_util_get_window_screen_mode(win, &mode);
    assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase       utc_efl_util_set_window_brightness_p1
 * @since_tizen    3.0
 * @description    to verify whether efl_util_set_window_brightness API is
 *                 working properly in the case a user sets the brightness to 50
 */
int utc_efl_util_set_window_brightness_p1(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_normal_win("Brightness test");
    assert(win);

    ret = efl_util_set_window_brightness(win, 50);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_efl_util_set_window_brightness_p2
 * @since_tizen    3.0
 * @description    to verify whether efl_util_set_window_brightness API is
 *                 working properly in the case a user sets the brightness to negative value(-1)
 */
int utc_efl_util_set_window_brightness_p2(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_normal_win("Brightness test");
    assert(win);

    ret = efl_util_set_window_brightness(win, -1);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_efl_util_set_window_brightness_n1
 * @since_tizen    3.0
 * @description    to verify whether efl_util_set_window_brightness API can
 *                 handle the error case a user sets the brightness without window.
 */
int utc_efl_util_set_window_brightness_n1(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    ret = efl_util_set_window_brightness(win, 60);
    assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase       utc_efl_util_set_window_brightness_n2
 * @since_tizen    3.0
 * @description    to verify whether efl_util_set_window_brightness API can
 *                 handle the error case a user sets the brightness with invalid
 *                 value.
 */
int utc_efl_util_set_window_brightness_n2(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_normal_win("Brightness test");
    assert(win);

    ret = efl_util_set_window_brightness(win, 1000);
    assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase       utc_efl_util_get_window_brightness_p1
 * @since_tizen    3.0
 * @description    to verify whether efl_util_get_window_brightness API is
 *                 working properly in the case a user requests the brightness to 70
 */
int utc_efl_util_get_window_brightness_p1(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    int brightness = -1;

    win = _create_normal_win("Brightness test");
    assert(win);

    ret = efl_util_set_window_brightness(win, 70);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    ret = efl_util_get_window_brightness(win, &brightness);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(brightness, 70);

    return 0;
}

/**
 * @testcase        utc_efl_util_get_window_brightness_p2
 * @since_tizen    3.0
 * @description    to verify whether efl_util_get_window_brightness API is
 *                 working properly in the case a user requests the brightness
 *                 to negative value(-1)
 */
int utc_efl_util_get_window_brightness_p2(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    int brightness = -1;

    win = _create_normal_win("Brightness test");
    assert(win);

    ret = efl_util_set_window_brightness(win, -1);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);

    ret = efl_util_get_window_brightness(win, &brightness);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(brightness, -1);

    return 0;
}

/**
 * @testcase       utc_efl_util_get_window_brightness_p3
 * @since_tizen    3.0
 * @description    to verify whether efl_util_get_window_brightness API is
 *                 working properly in the case a user doesn't set the brightness
 */
int utc_efl_util_get_window_brightness_p3(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    int brightness = -1;

    win = _create_normal_win("Brightness test");
    assert(win);

    ret = efl_util_get_window_brightness(win, &brightness);
    assert_eq(ret, EFL_UTIL_ERROR_NONE);
    assert_eq(brightness, -1);

    return 0;
}

/**
 * @testcase       utc_efl_util_get_window_brightness_n1
 * @since_tizen    3.0
 * @description    to verify whether efl_util_get_window_brightness API can
 *                 handle the error case a user requests the brightness without
 *                 window.
 */
int utc_efl_util_get_window_brightness_n1(void)
{
    Evas_Object *win = NULL;
    int ret = -1;
    int brightness = -1;

    ret = efl_util_get_window_brightness(win, &brightness);
    assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase       utc_efl_util_get_window_brightness_n2
 * @since_tizen    3.0
 * @description    to verify whether efl_util_get_window_brightness API can
 *                 handle the error case a user requests the brightness with NULL pointer
 */
int utc_efl_util_get_window_brightness_n2(void)
{
    Evas_Object *win = NULL;
    int ret = -1;

    win = _create_normal_win("Brightness test");
    assert(win);

    ret = efl_util_get_window_brightness(win, NULL);
    assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_initialize_p
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_initialize API is
 *                 working properly
 */
int utc_efl_util_gesture_initialize_p(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_deinitialize_p
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_deinitialize API is
 *                 working properly in the case a user requests the deinitialize to
 *                 the successfully initialized efl_util_gesture_h
 */
int utc_efl_util_gesture_deinitialize_p(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_deinitialize_n
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_deinitialize API can
 *                 handle the error case a user requests the deinitialize with NULL pointer
 */
int utc_efl_util_gesture_deinitialize_n(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	/* negative test : passing invalid efl_util_gesture_h handle */
	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_new_p1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_new API is
 *                 working properly in the case a user requests the new edge swipe
 *                 with one finger and top edge
 */
int utc_efl_util_gesture_edge_swipe_new_p1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	efl_util_gesture_edge_swipe_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_new_p2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_new API is
 *                 working properly in the case a user requests the new edge swipe
 *                 with two fingers and top edge
 */
int utc_efl_util_gesture_edge_swipe_new_p2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	efl_util_gesture_edge_swipe_new(h_gesture, 2, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_new_p3
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_new API is
 *                 working properly in the case a user requests the new edge swipe
 *                 with one finger and bottom edge
 */
int utc_efl_util_gesture_edge_swipe_new_p3(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	efl_util_gesture_edge_swipe_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_BOTTOM);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_new_p4
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_new API is
 *                 working properly in the case a user requests the new edge swipe
 *                 with one finger and left edge
 */
int utc_efl_util_gesture_edge_swipe_new_p4(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	efl_util_gesture_edge_swipe_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_LEFT);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_new_p5
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_new API is
 *                 working properly in the case a user requests the new edge swipe
 *                 with one finger and right edge
 */
int utc_efl_util_gesture_edge_swipe_new_p5(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	efl_util_gesture_edge_swipe_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_RIGHT);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_new_n1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_new API can
 *                 handle the error case a user requests the new edge swipe
 *                 with invalid efl_util_gesture_h
 */
int utc_efl_util_gesture_edge_swipe_new_n1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	/* negative test : passing invalid efl_util_gesture_h handle */
	efl_util_gesture_edge_swipe_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_new_n2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_new API can
 *                 handle the error case a user requests the new edge swipe
 *                 with none edge position
 */
int utc_efl_util_gesture_edge_swipe_new_n2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid efl_util_gesture_edge_e enum value */
	efl_util_gesture_edge_swipe_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_NONE);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_new_n3
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_new API can
 *                 handle the error case a user requests the new edge swipe
 *                 with invalid edge position
 */
int utc_efl_util_gesture_edge_swipe_new_n3(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid efl_util_gesture_edge_e enum value */
	efl_util_gesture_edge_swipe_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_LEFT+1);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_size_set_p1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_size_set API is
 *                 working properly in the case a user requests the set edge swipe size
 *                 with partial edge size 0 to 359
 */
int utc_efl_util_gesture_edge_swipe_size_set_p1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_swipe = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_swipe = efl_util_gesture_edge_swipe_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_edge_swipe_size_set(d_edge_swipe, EFL_UTIL_GESTURE_EDGE_SIZE_PARTIAL,0,359);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_edge_swipe_free(h_gesture, d_edge_swipe);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_size_set_n1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_size_set API can
 *                 handle the error case a user requests the set edge swipe size
 *                 with NULL efl_util_gesture_data
 */
int utc_efl_util_gesture_edge_swipe_size_set_n1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_data d_edge_swipe = NULL;

	/* negative test : passing invalid efl_util_gesture_data */
	ret = efl_util_gesture_edge_swipe_size_set(d_edge_swipe, EFL_UTIL_GESTURE_EDGE_SIZE_FULL,0,1);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_size_set_n2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_size_set API can
 *                 handle the error case a user requests the set edge swipe size
 *                 with invalid efl_util_gesture_data with different type
 */
int utc_efl_util_gesture_edge_swipe_size_set_n2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_drag = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_drag = efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid type of efl_util_gesture_data */
	/* expeced efl_util_gesture_data type : edge_swipe */
	/* given efl_util_gesture_data type : edge_drag */
	ret = efl_util_gesture_edge_swipe_size_set(d_edge_drag, EFL_UTIL_GESTURE_EDGE_SIZE_PARTIAL,0,100);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_edge_drag_free(h_gesture, d_edge_drag);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_size_set_n3
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_size_set API can
 *                 handle the error case a user requests the set edge swipe size
 *                 with invalid edge size type
 */
int utc_efl_util_gesture_edge_swipe_size_set_n3(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_swipe = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_swipe = efl_util_gesture_edge_swipe_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid efl_util_gesture_edge_size enum */
	/* expected enum : EFL_UTIL_GESTURE_EDGE_SIZE_PARTIAL */
	/* given enum : EFL_UTIL_GESTURE_EDGE_SIZE_FULL */
	ret = efl_util_gesture_edge_swipe_size_set(d_edge_swipe, EFL_UTIL_GESTURE_EDGE_SIZE_FULL,0,1);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_edge_swipe_free(h_gesture, d_edge_swipe);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_size_set_n4
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_size_set API can
 *                 handle the error case a user requests the set edge swipe size
 *                 with invalid edge size range
 */
int utc_efl_util_gesture_edge_swipe_size_set_n4(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_swipe = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_swipe = efl_util_gesture_edge_swipe_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid start_point, end_point parameters */
	/* expected enum : start_point < end_point */
	/* given enum : start_point >= end_point */
	ret = efl_util_gesture_edge_swipe_size_set(d_edge_swipe, EFL_UTIL_GESTURE_EDGE_SIZE_PARTIAL,5,1);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_edge_swipe_free(h_gesture, d_edge_swipe);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_free_p1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_free API is
 *                 working properly in the case a user to free a edge swipe data
 */
int utc_efl_util_gesture_edge_swipe_free_p1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_swipe = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_swipe = efl_util_gesture_edge_swipe_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_edge_swipe_free(h_gesture, d_edge_swipe);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_free_n1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_free API can
 *                 handle the error case a user requests to free a edge swipe data
 *                 with invalid efl_util_gesture_data
 */
int utc_efl_util_gesture_edge_swipe_free_n1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid efl_util_gesture_data handle */
	ret = efl_util_gesture_edge_swipe_free(h_gesture, NULL);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_swipe_free_n2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_swipe_free API can
 *                 handle the error case a user requests to free a edge swipe data
 *                 without gesture system initialize
 */
int utc_efl_util_gesture_edge_swipe_free_n2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;

	/* negative test : passing invalid efl_util_gesture_h handle */
	ret = efl_util_gesture_edge_swipe_free(NULL, NULL);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_new_p1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_new API is
 *                 working properly in the case a user requests the new edge drag
 *                 with one finger and top edge
 */
int utc_efl_util_gesture_edge_drag_new_p1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_drag = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_drag = efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_edge_drag_free(h_gesture, d_edge_drag);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_new_p2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_new API is
 *                 working properly in the case a user requests the new edge drag
 *                 with two fingers and top edge
 */
int utc_efl_util_gesture_edge_drag_new_p2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_drag = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_drag = efl_util_gesture_edge_drag_new(h_gesture, 2, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_edge_drag_free(h_gesture, d_edge_drag);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_new_p3
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_new API is
 *                 working properly in the case a user requests the new edge drag
 *                 with one finger and bottom edge
 */
int utc_efl_util_gesture_edge_drag_new_p3(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_drag = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_drag = efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_BOTTOM);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_edge_drag_free(h_gesture, d_edge_drag);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_new_p4
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_new API is
 *                 working properly in the case a user requests the new edge drag
 *                 with one finger and left edge
 */
int utc_efl_util_gesture_edge_drag_new_p4(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_drag = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_drag = efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_LEFT);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_edge_drag_free(h_gesture, d_edge_drag);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_new_p5
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_new API is
 *                 working properly in the case a user requests the new edge drag
 *                 with one finger and right edge
 */
int utc_efl_util_gesture_edge_drag_new_p5(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_drag = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_drag = efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_RIGHT);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_edge_drag_free(h_gesture, d_edge_drag);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_new_n1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_new API can
 *                 handle the error case a user requests the new edge drag
 *                 with NULL efl_util_gesture_h
 */
int utc_efl_util_gesture_edge_drag_new_n1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	/* negative test : passing invalid efl_util_gesture_h handle */
	efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_new_n2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_new API can
 *                 handle the error case a user requests the new edge drag
 *                 with none edge
 */
int utc_efl_util_gesture_edge_drag_new_n2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid efl_util_gesture_edge_e enum value */
	efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_NONE);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_new_n3
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_new API can
 *                 handle the error case a user requests the new edge drag
 *                 with invaild too low edge
 */
int utc_efl_util_gesture_edge_drag_new_n3(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid efl_util_gesture_edge_e enum value */
	efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_NONE-1);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_new_n4
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_new API can
 *                 handle the error case a user requests the new edge drag
 *                 with invaild too large edge
 */
int utc_efl_util_gesture_edge_drag_new_n4(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid efl_util_gesture_edge_e enum value */
	efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_LEFT+1);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_size_set_p1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_size_set API is
 *                 working properly in the case a user requests the set edge drag size
 *                 with partial edge size
 */
int utc_efl_util_gesture_edge_drag_size_set_p1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_drag = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_drag = efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_edge_drag_size_set(d_edge_drag, EFL_UTIL_GESTURE_EDGE_SIZE_PARTIAL,0,359);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_edge_drag_free(h_gesture, d_edge_drag);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_size_set_n1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_size_set API can
 *                 handle the error case a user requests the set edge drag size
 *                 with NULL efl_util_gesture_data
 */
int utc_efl_util_gesture_edge_drag_size_set_n1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_data d_edge_drag = NULL;

	/* negative test : passing invalid efl_util_gesture_data */
	ret = efl_util_gesture_edge_drag_size_set(d_edge_drag, EFL_UTIL_GESTURE_EDGE_SIZE_FULL,0,1);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_size_set_n2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_size_set API can
 *                 handle the error case a user requests the set edge drag size
 *                 with invalid efl_util_gesture_data with different type
 */
int utc_efl_util_gesture_edge_drag_size_set_n2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_swipe = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_swipe = efl_util_gesture_edge_swipe_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid type of efl_util_gesture_data */
	/* expeced efl_util_gesture_data type : edge_drag */
	/* given efl_util_gesture_data type : edge_swipe */
	ret = efl_util_gesture_edge_drag_size_set(d_edge_swipe, EFL_UTIL_GESTURE_EDGE_SIZE_PARTIAL,0,100);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_edge_swipe_free(h_gesture, d_edge_swipe);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_size_set_n3
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_size_set API can
 *                 handle the error case a user requests the set edge drag size
 *                 with invalid edge size type
 */
int utc_efl_util_gesture_edge_drag_size_set_n3(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_drag = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_drag = efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid efl_util_gesture_edge_size enum */
	/* expected enum : EFL_UTIL_GESTURE_EDGE_SIZE_PARTIAL */
	/* given enum : EFL_UTIL_GESTURE_EDGE_SIZE_FULL */
	ret = efl_util_gesture_edge_drag_size_set(d_edge_drag, EFL_UTIL_GESTURE_EDGE_SIZE_FULL,0,1);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_edge_drag_free(h_gesture, d_edge_drag);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_size_set_n4
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_size_set API can
 *                 handle the error case a user requests the set edge drag size
 *                 with invalid edge size range
 */
int utc_efl_util_gesture_edge_drag_size_set_n4(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_drag = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_drag = efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid start_point, end_point parameters */
	/* expected enum : start_point < end_point */
	/* given enum : start_point >= end_point */
	ret = efl_util_gesture_edge_drag_size_set(d_edge_drag, EFL_UTIL_GESTURE_EDGE_SIZE_PARTIAL,5,1);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_edge_drag_free(h_gesture, d_edge_drag);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_free_p1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_free API is
 *                 working properly in the case a user requests to free a edge drag data
 */
int utc_efl_util_gesture_edge_drag_free_p1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_drag = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_edge_drag = efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_edge_drag_free(h_gesture, d_edge_drag);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_free_n1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_free API can
 *                 handle the error case a user requests to free a edge drag data
 *                 with invalid efl_util_gesture_data
 */
int utc_efl_util_gesture_edge_drag_free_n1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid efl_util_gesture_data handle */
	ret = efl_util_gesture_edge_drag_free(h_gesture, NULL);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_edge_drag_free_n2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_edge_drag_free API can
 *                 handle the error case a user requests to free a edge drag data
 *                 without gesture system initialize
 */
int utc_efl_util_gesture_edge_drag_free_n2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;

	/* negative test : passing invalid efl_util_gesture_h handle */
	ret = efl_util_gesture_edge_drag_free(NULL, NULL);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_tap_new_p
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_tap_new API is
 *                 working properly in the case a user requests the new tap
 *                 with two fingers and double taps
 */
int utc_efl_util_gesture_tap_new_p(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_tap = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_tap = efl_util_gesture_tap_new(h_gesture, 2, 2);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_tap_free(h_gesture, d_tap);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_tap_new_n1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_tap_new API can
 *                 handle the error case a user requests the new tap
 *                 with NULL efl_util_gesture_h
 */
int utc_efl_util_gesture_tap_new_n1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	/* negative test : passing invalid efl_util_gesture_h */
	efl_util_gesture_tap_new(h_gesture, 2, 2);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_tap_new_n2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_tap_new API can
 *                 handle the error case a user requests the new tap
 *                 with invalid fingers
 */
int utc_efl_util_gesture_tap_new_n2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid fingers argument */
	/* expected : fingers > 1 */
	/* given : fingers <= 1 */
	efl_util_gesture_tap_new(h_gesture, 0, 2);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NOT_SUPPORTED);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_tap_new_n3
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_tap_new API can
 *                 handle the error case a user requests the new tap
 *                 with invalid repeats
 */
int utc_efl_util_gesture_tap_new_n3(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid fingers argument */
	/* expected : repeats > 1 */
	/* given : repeats <= 1 */
	efl_util_gesture_tap_new(h_gesture, 2, 1);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NOT_SUPPORTED);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_tap_free_p1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_tap_free API is
 *                 working properly in the case a user requests to free a tap data
 */
int utc_efl_util_gesture_tap_free_p1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_tap = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_tap = efl_util_gesture_tap_new(h_gesture, 2, 2);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_tap_free(h_gesture, d_tap);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_tap_free_n1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_tap_free API can
 *                 handle the error case a user requests to free a tap data
 *                 with invalid efl_util_gesture_data
 */
int utc_efl_util_gesture_tap_free_n1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid efl_util_gesture_data handle */
	ret = efl_util_gesture_tap_free(h_gesture, NULL);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_tap_free_n2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_tap_free API can
 *                 handle the error case a user requests to free a tap data
 *                 without gesture system initialize
 */
int utc_efl_util_gesture_tap_free_n2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;

	/* negative test : passing invalid efl_util_gesture_h handle */
	ret = efl_util_gesture_tap_free(NULL, NULL);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_palm_cover_new_p
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_palm_cover_new API is
 *                 working properly in the case a user requests the new palm cover
 *                 with valid efl_util_gesture_h
 */
int utc_efl_util_gesture_palm_cover_new_p(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_palm_cover = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_palm_cover = efl_util_gesture_palm_cover_new(h_gesture);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_palm_cover_free(h_gesture, d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_palm_cover_new_n
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_palm_cover_new API can
 *                 handle the error case a user requests the new palm cover
 *                 with NULL efl_util_gesture_h
 */
int utc_efl_util_gesture_palm_cover_new_n(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	/* negative test : passing invalid efl_util_gesture_h */
	efl_util_gesture_palm_cover_new(h_gesture);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_palm_cover_free_p1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_palm_cover_free API is
 *                 working properly in the case a user requests to free a palm_cover data
 */
int utc_efl_util_gesture_palm_cover_free_p1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_palm_cover = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_palm_cover = efl_util_gesture_palm_cover_new(h_gesture);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_palm_cover_free(h_gesture, d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_palm_cover_free_n1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_palm_cover_free API can
 *                 handle the error case a user requests to free a palm_cover data
 *                 with invalid efl_util_gesture_data
 */
int utc_efl_util_gesture_palm_cover_free_n1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid efl_util_gesture_data handle */
	ret = efl_util_gesture_palm_cover_free(h_gesture, NULL);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_palm_cover_free_n2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_palm_cover_free API can
 *                 handle the error case a user requests to free a palm_cover data
 *                 without gesture system initialize
 */
int utc_efl_util_gesture_palm_cover_free_n2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;

	/* negative test : passing invalid efl_util_gesture_h handle */
	ret = efl_util_gesture_palm_cover_free(NULL, NULL);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_select_p
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_select API is
 *                 working properly in the case a user requests the gesture select
 *                 with a palm cover gesture
 */
int utc_efl_util_gesture_select_p(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_palm_cover = NULL;
	Evas_Object *window = NULL;

	window = _create_normal_win("Gesture Window");
	assert(window);

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_palm_cover = efl_util_gesture_palm_cover_new(h_gesture);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_select(h_gesture, window, d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deselect(h_gesture, window, d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_palm_cover_free(h_gesture,d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	evas_object_del(window);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_select_n1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_select API can
 *                 handle the error case a user requests the gesture select
 *                 with NULL efl_util_gesture_h
 */
int utc_efl_util_gesture_select_n1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_palm_cover = NULL;
	Evas_Object *window = NULL;

	/* negative test : passing invalid efl_util_gesture_h */
	ret = efl_util_gesture_select(h_gesture, window, d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_select_n2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_select API can
 *                 handle the error case a user requests the gesture select
 *                 with NULL window
 */
int utc_efl_util_gesture_select_n2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_palm_cover = NULL;
	Evas_Object *window = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_palm_cover = efl_util_gesture_palm_cover_new(h_gesture);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid window */
	ret = efl_util_gesture_select(h_gesture, window, d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_palm_cover_free(h_gesture, d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_select_n3
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_select API can
 *                 handle the error case a user requests the gesture select
 *                 with NULL efl_util_gesture_data
 */
int utc_efl_util_gesture_select_n3(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_palm_cover = NULL;
	Evas_Object *window = NULL;

	window = _create_normal_win("Gesture Window");
	assert(window);

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid efl_util_gesture_data */
	ret = efl_util_gesture_select(h_gesture, window, d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	evas_object_del(window);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_select_n4
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_select API can
 *                 handle the error case a user requests the gesture select
 *                 with unsupported gesture type
 */
int utc_efl_util_gesture_select_n4(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_tap = NULL;
	Evas_Object *window = NULL;

	window = _create_normal_win("Gesture Window");
	assert(window);

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_tap = efl_util_gesture_tap_new(h_gesture, 2, 2);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing unsupported gesture type */
	ret = efl_util_gesture_select(h_gesture, window, d_tap);
	assert_eq(ret, EFL_UTIL_ERROR_NOT_SUPPORTED);

	ret = efl_util_gesture_tap_free(h_gesture, d_tap);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	evas_object_del(window);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_deselect_p
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_deselect API is
 *                 working properly in the case a user requests the gesture deselect
 *                 with a palm cover gesture
 */
int utc_efl_util_gesture_deselect_p(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_palm_cover = NULL;
	Evas_Object *window = NULL;

	window = _create_normal_win("Gesture Window");
	assert(window);

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_palm_cover = efl_util_gesture_palm_cover_new(h_gesture);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_select(h_gesture, window, d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deselect(h_gesture, window, d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_palm_cover_free(h_gesture,d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	evas_object_del(window);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_deselect_n1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_deselect API can
 *                 handle the error case a user requests the gesture select
 *                 with NULL efl_util_gesture_h
 */
int utc_efl_util_gesture_deselect_n1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_palm_cover = NULL;
	Evas_Object *window = NULL;

	/* negative test : passing invalid efl_util_gesture_h */
	ret = efl_util_gesture_deselect(h_gesture, window, d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_deselect_n2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_deselect API can
 *                 handle the error case a user requests the gesture select
 *                 with NULL window
 */
int utc_efl_util_gesture_deselect_n2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_palm_cover = NULL;
	Evas_Object *window = NULL;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_palm_cover = efl_util_gesture_palm_cover_new(h_gesture);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid window */
	ret = efl_util_gesture_deselect(h_gesture, window, d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_palm_cover_free(h_gesture,d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_deselect_n3
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_deselect API can
 *                 handle the error case a user requests the gesture select
 *                 with NULL efl_util_gesture_data
 */
int utc_efl_util_gesture_deselect_n3(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_palm_cover = NULL;
	Evas_Object *window = NULL;

	window = _create_normal_win("Gesture Window");
	assert(window);

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing invalid efl_util_gesture_data */
	ret = efl_util_gesture_deselect(h_gesture, window, d_palm_cover);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	evas_object_del(window);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_deselect_n4
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_deselect API can
 *                 handle the error case a user requests the gesture deselect
 *                 with unsupported gesture type
 */
int utc_efl_util_gesture_deselect_n4(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_tap = NULL;
	Evas_Object *window = NULL;

	window = _create_normal_win("Gesture Window");
	assert(window);

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	d_tap = efl_util_gesture_tap_new(h_gesture, 2, 2);
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	/* negative test : passing unsupported gesture type */
	ret = efl_util_gesture_deselect(h_gesture, window, d_tap);
	assert_eq(ret, EFL_UTIL_ERROR_NOT_SUPPORTED);

	ret = efl_util_gesture_tap_free(h_gesture, d_tap);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	evas_object_del(window);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_activate_set_on_window_p1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_activate_set_on_window API is
 *                 working properly in the case a user requests the activate
 *                 with edge swipe gesture
 */
int utc_efl_util_gesture_activate_set_on_window_p1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	Evas_Object *window = NULL;
	unsigned int type;

	window = _create_normal_win("Gesture Window");
	assert(window);

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	type = EFL_UTIL_GESTURE_TYPE_EDGE_SWIPE;
	ret = efl_util_gesture_activate_set_on_window(h_gesture, window, type, EINA_TRUE);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	evas_object_del(window);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_activate_set_on_window_p2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_activate_set_on_window API is
 *                 working properly in the case a user requests the deactivate
 *                 with edge swipe gesture
 */
int utc_efl_util_gesture_activate_set_on_window_p2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	Evas_Object *window = NULL;
	unsigned int type;

	window = _create_normal_win("Gesture Window");
	assert(window);

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	type = EFL_UTIL_GESTURE_TYPE_EDGE_SWIPE;
	ret = efl_util_gesture_activate_set_on_window(h_gesture, window, type, EINA_FALSE);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	evas_object_del(window);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_activate_set_on_window_p3
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_activate_set_on_window API is
 *                 working properly in the case a user requests the activate
 *                 with edge drag gesture
 */
int utc_efl_util_gesture_activate_set_on_window_p3(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	Evas_Object *window = NULL;
	unsigned int type;

	window = _create_normal_win("Gesture Window");
	assert(window);

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	type = EFL_UTIL_GESTURE_TYPE_EDGE_DRAG;
	ret = efl_util_gesture_activate_set_on_window(h_gesture, window, type, EINA_TRUE);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	evas_object_del(window);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_activate_set_on_window_p4
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_activate_set_on_window API is
 *                 working properly in the case a user requests the activate
 *                 with palm cover gesture
 */
int utc_efl_util_gesture_activate_set_on_window_p4(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	Evas_Object *window = NULL;
	unsigned int type;

	window = _create_normal_win("Gesture Window");
	assert(window);

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	type = EFL_UTIL_GESTURE_TYPE_PALM_COVER;
	ret = efl_util_gesture_activate_set_on_window(h_gesture, window, type, EINA_TRUE);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	evas_object_del(window);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_activate_set_on_window_p5
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_activate_set_on_window API is
 *                 working properly in the case a user requests the activate
 *                 with tap gesture
 */
int utc_efl_util_gesture_activate_set_on_window_p5(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	Evas_Object *window = NULL;
	unsigned int type;

	window = _create_normal_win("Gesture Window");
	assert(window);

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	type = EFL_UTIL_GESTURE_TYPE_TAP;
	ret = efl_util_gesture_activate_set_on_window(h_gesture, window, type, EINA_TRUE);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	evas_object_del(window);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_activate_set_on_window_n1
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_activate_set_on_window API can
 *                 handle the error case a user requests the gesture activate
 *                 with NULL efl_util_gesture_h
 */
int utc_efl_util_gesture_activate_set_on_window_n1(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	Evas_Object *window = NULL;
	unsigned int type;

	window = _create_normal_win("Gesture Window");
	assert(window);

	type = EFL_UTIL_GESTURE_TYPE_TAP;

	/* negative test : passing invalid efl_util_gesture_h */
	ret = efl_util_gesture_activate_set_on_window(h_gesture, window, type, EINA_TRUE);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	evas_object_del(window);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_activate_set_on_window_n2
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_activate_set_on_window API can
 *                 handle the error case a user requests the gesture activate
 *                 with invalid type of gestures
 */
int utc_efl_util_gesture_activate_set_on_window_n2(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	Evas_Object *window = NULL;
	unsigned int type;

	window = _create_normal_win("Gesture Window");
	assert(window);

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	type = EFL_UTIL_GESTURE_TYPE_NONE;

	/* negative test : passing invalid type of gesture */
	ret = efl_util_gesture_activate_set_on_window(h_gesture, window, type, EINA_TRUE);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	evas_object_del(window);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase	   utc_efl_util_gesture_activate_set_on_window_n3
 * @since_tizen	   4.0
 * @description    to verify whether efl_util_gesture_activate_set_on_window API can
 *                 handle the error case a user requests the gesture activate
 *                 with NULL window
 */
int utc_efl_util_gesture_activate_set_on_window_n3(void)
{
	int ret = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	Evas_Object *window = NULL;
	unsigned int type;

	h_gesture = efl_util_gesture_initialize();
	ret = get_last_result();
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	type = EFL_UTIL_GESTURE_TYPE_TAP;

	/* negative test : passing invalid window */
	ret = efl_util_gesture_activate_set_on_window(h_gesture, window, type, EINA_TRUE);
	assert_eq(ret, EFL_UTIL_ERROR_INVALID_PARAMETER);

	ret = efl_util_gesture_deinitialize(h_gesture);
	assert_eq(ret, EFL_UTIL_ERROR_NONE);

	return 0;
}

