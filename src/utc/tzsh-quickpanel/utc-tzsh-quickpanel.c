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
#include <tzsh_quickpanel.h>
#include <Elementary.h>

/* It is a workaround for implicit declaration error. This API will be public since 5.5 */
EAPI int elm_win_aux_hint_add(Evas_Object *obj, const char *hint, const char *val);

static Evas_Object* g_win;
static int g_init;

static int _initialize(void);

/**
 * @function       utc_tzsh_quickpanel_startup
 * @description    Called before each test
 * @parameter      NA
 * @return         NA
 */
void utc_tzsh_quickpanel_startup(void)
{
    _initialize();
}


/**
 * @function       utc_tzsh_quickpanel_cleanup
 * @description    Called after each test
 * @parameter      NA
 * @return         NA
 */
void utc_tzsh_quickpanel_cleanup(void)
{
}


static void _win_del(void *data, Evas_Object *obj, void *event)
{
    elm_exit();
}


/* This function should be called by FIRST test case */
static int _initialize(void)
{
    if (g_init) return 0;

    Evas_Object *conform = NULL;

    elm_init(0, NULL);

    g_win = elm_win_add(NULL, "tzsh_quickpanel test", ELM_WIN_BASIC);
    assert(g_win);

    elm_win_title_set(g_win, "tzsh_quickpanel test");
    evas_object_smart_callback_add(g_win, "delete,request", _win_del, NULL);

    elm_win_conformant_set(g_win, EINA_TRUE);

    /* Conformant */
    conform = elm_conformant_add(g_win);
    evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(g_win, conform);
    evas_object_show(conform);

    elm_win_indicator_mode_set(g_win, ELM_WIN_INDICATOR_SHOW);
    elm_win_indicator_opacity_set(g_win, ELM_WIN_INDICATOR_TRANSPARENT);

    /* do not use buffer_flush and deiconify_approve */
    elm_win_aux_hint_add(g_win, "wm.policy.win.iconify.buffer.flush", "0");
    elm_win_aux_hint_add(g_win, "wm.policy.win.deiconify.update", "0");

    evas_object_show(g_win);

	g_init = 1;

    return 0;
}


/* This function should be called by LAST test case */
static void _finalize(void)
{
    g_init = 0;
    evas_object_del(g_win);
    elm_shutdown();
}


/**
 * @testcase       utc_tzsh_create_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_create()
 */
int utc_tzsh_create_n1(void)
{
    tzsh_h tzsh = NULL;
    int err_result = 0;

    tzsh = tzsh_create(100);
    assert_eq(tzsh, NULL);

    err_result = get_last_result();
    assert_eq(err_result, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_create_p1
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_create()
 */
int utc_tzsh_create_p1(void)
{
    tzsh_h tzsh = NULL;

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_UNKNOWN);
    assert_neq(tzsh, NULL);

    // cleanup resource
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_destroy_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_destroy()
 */
int utc_tzsh_destroy_n1(void)
{
    int ret;

    ret = tzsh_destroy(NULL);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_destroy_p1
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_destroy()
 */
int utc_tzsh_destroy_p1(void)
{
    tzsh_h tzsh = NULL;
    int ret;

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_UNKNOWN);
    assert_neq(tzsh, NULL);

    ret = tzsh_destroy(tzsh);
	assert_eq(ret, TZSH_ERROR_NONE);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_create_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_create()
 */
int utc_tzsh_quickpanel_create_n1(void)
{
    tzsh_quickpanel_h qp = NULL;
    int err_result = 0;

    qp = tzsh_quickpanel_create(NULL, 0);
    assert_eq(qp, NULL);

    err_result = get_last_result();
    assert_eq(err_result, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_create_p1
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_create()
 */
int utc_tzsh_quickpanel_create_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_create_with_type_n1
 * @since_tizen    5.5
 * @description    Negative test case of tzsh_quickpanel_create_with_type()
 */
int utc_tzsh_quickpanel_create_with_type_n1(void)
{
    tzsh_quickpanel_h qp = NULL;
    int err_result = 0;

    qp = tzsh_quickpanel_create_with_type(NULL, 0, TZSH_QUICKPANEL_TYPE_UNKNOWN);
    assert_eq(qp, NULL);

    err_result = get_last_result();
    assert_eq(err_result, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_create_with_type_n2
 * @since_tizen    6.0
 * @description    Negative test case of tzsh_quickpanel_create_with_type()
 */
int utc_tzsh_quickpanel_create_with_type_n2(void)
{
    tzsh_quickpanel_h qp = NULL;
    tzsh_quickpanel_type_e qp_type = TZSH_QUICKPANEL_TYPE_UNKNOWN;
    int err_result = 0;
    int ret = -1;

    qp = tzsh_quickpanel_create_with_type(NULL, 0, -1);
    assert_eq(qp, NULL);

    err_result = get_last_result();
    assert_eq(err_result, TZSH_ERROR_INVALID_PARAMETER);

    ret = tzsh_quickpanel_type_get(qp, &qp_type);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);
    assert_neq(qp_type, TZSH_QUICKPANEL_TYPE_APPS_MENU);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_create_with_type_p1
 * @since_tizen    5.5
 * @description    Positive test case of tzsh_quickpanel_create_with_type()
 */
int utc_tzsh_quickpanel_create_with_type_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create_with_type(tzsh, tzwin, TZSH_QUICKPANEL_TYPE_SYSTEM_DEFAULT);
    assert_neq(qp, NULL);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_create_with_type_p2
 * @since_tizen    6.0
 * @description    Positive test case of tzsh_quickpanel_create_with_type()
 */
int utc_tzsh_quickpanel_create_with_type_p2(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_quickpanel_type_e qp_type = TZSH_QUICKPANEL_TYPE_UNKNOWN;
    tzsh_window tzwin = 0;
    int ret = -1;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create_with_type(tzsh, tzwin, TZSH_QUICKPANEL_TYPE_APPS_MENU);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_type_get(qp, &qp_type);
    assert_eq(qp_type, TZSH_QUICKPANEL_TYPE_APPS_MENU);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_destroy_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_destroy()
 */
int utc_tzsh_quickpanel_destroy_n1(void)
{
    int ret;

    ret = tzsh_quickpanel_destroy(NULL);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_destroy_p1
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_destroy()
 */
int utc_tzsh_quickpanel_destroy_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_destroy(qp);
    assert_eq(ret, TZSH_ERROR_NONE);

    ret = tzsh_destroy(tzsh);
    assert_eq(ret, TZSH_ERROR_NONE);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_destroy_p2
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_destroy()
 */
int utc_tzsh_quickpanel_destroy_p2(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    ret = tzsh_destroy(tzsh);
    assert_eq(ret, TZSH_ERROR_NONE);

    ret = tzsh_quickpanel_destroy(qp);
    assert_eq(ret, TZSH_ERROR_NONE);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_show_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_show()
 */
int utc_tzsh_quickpanel_show_n1(void)
{
    int ret;

    ret = tzsh_quickpanel_show(NULL);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_show_p1
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_show()
 */
int utc_tzsh_quickpanel_show_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret = -1;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_show(qp);
    if (ret != TZSH_ERROR_NO_SERVICE)
        assert_eq(ret, TZSH_ERROR_NONE);
    else
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);

    usleep(2000000);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_hide_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_hide()
 */
int utc_tzsh_quickpanel_hide_n1(void)
{
    int ret;

    ret = tzsh_quickpanel_hide(NULL);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_hide_p1
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_hide()
 */
int utc_tzsh_quickpanel_hide_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret = -1;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_hide(qp);
    if (ret != TZSH_ERROR_NO_SERVICE)
        assert_eq(ret, TZSH_ERROR_NONE);
    else
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);

    usleep(2000000);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_scrollable_set_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_scrollable_set()
 */
int utc_tzsh_quickpanel_scrollable_set_n1(void)
{
    int ret = -1;

    ret = tzsh_quickpanel_scrollable_set(NULL, true);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_scrollable_set_p1
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_scrollable_set()
 */
int utc_tzsh_quickpanel_scrollable_set_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret = -1;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_scrollable_set(qp, true);
    assert_eq(ret, TZSH_ERROR_NONE);

    ret = tzsh_quickpanel_scrollable_set(qp, false);
    assert_eq(ret, TZSH_ERROR_NONE);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_scrollable_get_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_scrollable_get()
 */
int utc_tzsh_quickpanel_scrollable_get_n1(void)
{
    int ret;
    tzsh_quickpanel_state_scrollable_e scrollable;

    ret = tzsh_quickpanel_scrollable_get(NULL, &scrollable);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_scrollable_get_p1
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_scrollable_get()
 */
int utc_tzsh_quickpanel_scrollable_get_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret = -1;
    tzsh_quickpanel_state_scrollable_e scrollable;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_scrollable_set(qp, true);
    assert_eq(ret, TZSH_ERROR_NONE);

    ret = tzsh_quickpanel_scrollable_get(qp, &scrollable);
    if (ret != TZSH_ERROR_NO_SERVICE)
    {
        assert_eq(ret, TZSH_ERROR_NONE);
        assert_eq(scrollable, TZSH_QUICKPANEL_STATE_SCROLLABLE_SET);
    }
    else
    {
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);
    }

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_scrollable_get_p2
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_scrollable_get()
 */
int utc_tzsh_quickpanel_scrollable_get_p2(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret = -1;
    tzsh_quickpanel_state_scrollable_e state;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_scrollable_set(qp, false);
    assert_eq(ret, TZSH_ERROR_NONE);

    ret = tzsh_quickpanel_scrollable_get(qp, &state);
    if (ret != TZSH_ERROR_NO_SERVICE)
    {
        assert_eq(ret, TZSH_ERROR_NONE);
        assert_eq(state, TZSH_QUICKPANEL_STATE_SCROLLABLE_UNSET);
    }
    else
    {
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);
    }

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_scrollable_state_set_n1
 * @since_tizen    5.5
 * @description    Negative test case of tzsh_quickpanel_scrollable_state_set()
 */
int utc_tzsh_quickpanel_scrollable_state_set_n1(void)
{
    int ret = -1;

    ret = tzsh_quickpanel_scrollable_state_set(NULL, TZSH_QUICKPANEL_STATE_SCROLLABLE_SET);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_scrollable_state_set_p1
 * @since_tizen    5.5
 * @description    Positive test case of tzsh_quickpanel_scrollable_state_set()
 */
int utc_tzsh_quickpanel_scrollable_state_set_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret = -1;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_scrollable_state_set(qp, TZSH_QUICKPANEL_STATE_SCROLLABLE_SET);
    if (ret != TZSH_ERROR_NO_SERVICE)
        assert_eq(ret, TZSH_ERROR_NONE);
    else
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);

    ret = tzsh_quickpanel_scrollable_state_set(qp, TZSH_QUICKPANEL_STATE_SCROLLABLE_UNSET);
    if (ret != TZSH_ERROR_NO_SERVICE)
        assert_eq(ret, TZSH_ERROR_NONE);
    else
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);

    ret = tzsh_quickpanel_scrollable_state_set(qp, TZSH_QUICKPANEL_STATE_SCROLLABLE_RETAIN);
    if (ret != TZSH_ERROR_NO_SERVICE)
        assert_eq(ret, TZSH_ERROR_NONE);
    else
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_scrollable_state_get_n1
 * @since_tizen    5.5
 * @description    Negative test case of tzsh_quickpanel_scrollable_state_get()
 */
int utc_tzsh_quickpanel_scrollable_state_get_n1(void)
{
    int ret;
    tzsh_quickpanel_state_scrollable_e scrollable;

    ret = tzsh_quickpanel_scrollable_state_get(NULL, &scrollable);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_scrollable_state_get_p1
 * @since_tizen    5.5
 * @description    Positive test case of tzsh_quickpanel_scrollable_state_get()
 */
int utc_tzsh_quickpanel_scrollable_state_get_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret = -1;
    tzsh_quickpanel_state_scrollable_e scrollable;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_scrollable_state_set(qp, TZSH_QUICKPANEL_STATE_SCROLLABLE_SET);
    if (ret != TZSH_ERROR_NO_SERVICE)
        assert_eq(ret, TZSH_ERROR_NONE);
    else
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);

    ret = tzsh_quickpanel_scrollable_state_get(qp, &scrollable);
    if (ret != TZSH_ERROR_NO_SERVICE)
    {
        assert_eq(ret, TZSH_ERROR_NONE);
        assert_eq(scrollable, TZSH_QUICKPANEL_STATE_SCROLLABLE_SET);
    }
    else
    {
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);
    }

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_scrollable_state_get_p2
 * @since_tizen    5.5
 * @description    Positive test case of tzsh_quickpanel_scrollable_state_get()
 */
int utc_tzsh_quickpanel_scrollable_state_get_p2(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret = -1;
    tzsh_quickpanel_state_scrollable_e state;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_scrollable_state_set(qp, TZSH_QUICKPANEL_STATE_SCROLLABLE_UNSET);
    if (ret != TZSH_ERROR_NO_SERVICE)
        assert_eq(ret, TZSH_ERROR_NONE);
    else
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);

    ret = tzsh_quickpanel_scrollable_state_get(qp, &state);
    if (ret != TZSH_ERROR_NO_SERVICE)
    {
        assert_eq(ret, TZSH_ERROR_NONE);
        assert_eq(state, TZSH_QUICKPANEL_STATE_SCROLLABLE_UNSET);
    }
    else
    {
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);
    }

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_visible_get_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_visible_get()
 */
int utc_tzsh_quickpanel_visible_get_n1(void)
{
    int ret;
    tzsh_quickpanel_state_visible_e visible;

    ret = tzsh_quickpanel_visible_get(NULL, &visible);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_visible_get_n2
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_visible_get()
 */
int utc_tzsh_quickpanel_visible_get_n2(void)
{
    int ret;

    ret = tzsh_quickpanel_visible_get(NULL, NULL);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_visible_get_p1
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_visible_get()
 */
int utc_tzsh_quickpanel_visible_get_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret = -1;
    tzsh_quickpanel_state_visible_e state;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_visible_get(qp, &state);
    if (ret != TZSH_ERROR_NO_SERVICE)
    {
        assert_eq(ret, TZSH_ERROR_NONE);
        assert_eq(state, TZSH_QUICKPANEL_STATE_VISIBLE_HIDDEN);
    }
    else
    {
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);
    }

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_visible_get_p2
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_visible_get()
 */
int utc_tzsh_quickpanel_visible_get_p2(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret = -1;
    tzsh_quickpanel_state_visible_e state;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_show(qp);
    if (ret != TZSH_ERROR_NO_SERVICE)
        assert_eq(ret, TZSH_ERROR_NONE);
    else
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);

    usleep(2000000);

    ret = tzsh_quickpanel_visible_get(qp, &state);
    if (ret != TZSH_ERROR_NO_SERVICE)
    {
        assert_eq(ret, TZSH_ERROR_NONE);
        assert_eq(state, TZSH_QUICKPANEL_STATE_VISIBLE_SHOWN);
    }
    else
    {
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);
    }

    tzsh_quickpanel_hide(qp);
    usleep(2000000);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_orientation_get_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_orientation_get()
 */
int utc_tzsh_quickpanel_orientation_get_n1(void)
{
    int ret;

    ret = tzsh_quickpanel_orientation_get(NULL, NULL);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_orientation_get_p1
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_orientation_get()
 */
int utc_tzsh_quickpanel_orientation_get_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret = -1;
    tzsh_quickpanel_state_orientation_e state;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_orientation_get(qp, &state);
    if (ret != TZSH_ERROR_NO_SERVICE)
    {
        assert_eq(ret, TZSH_ERROR_NONE);
        assert_eq(state, TZSH_QUICKPANEL_STATE_ORIENTATION_0);
    }
    else
    {
        assert_eq(ret, TZSH_ERROR_NO_SERVICE);
    }

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


static void
_cb_vis_changed(int type, tzsh_quickpanel_event_info_h ev_info, void *data)
{
   tzsh_quickpanel_state_visible_e state;

   if (type != TZSH_QUICKPANEL_EVENT_VISIBLE) return;

   tzsh_quickpanel_event_visible_get(ev_info, &state);
}


/**
 * @testcase       utc_tzsh_quickpanel_event_handler_add_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_event_handler_add()
 */
int utc_tzsh_quickpanel_event_handler_add_n1(void)
{
    tzsh_quickpanel_event_handler_h handler;
    int err_result = 0;

    handler = tzsh_quickpanel_event_handler_add(NULL, TZSH_QUICKPANEL_EVENT_VISIBLE, _cb_vis_changed, NULL);
    assert_eq(handler, NULL);
	
    err_result = get_last_result();
    assert_eq(err_result, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_event_handler_add_n2
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_event_handler_add()
 */
int utc_tzsh_quickpanel_event_handler_add_n2(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    tzsh_quickpanel_event_handler_h handler;
    int err_result = 0;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    handler = tzsh_quickpanel_event_handler_add(qp, 123456, _cb_vis_changed, NULL);
    assert_eq(handler, NULL);

    err_result = get_last_result();
    assert_eq(err_result, TZSH_ERROR_INVALID_PARAMETER);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_event_handler_add_p1
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_event_handler_add()
 */
int utc_tzsh_quickpanel_event_handler_add_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    tzsh_quickpanel_event_handler_h handler;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    handler = tzsh_quickpanel_event_handler_add(qp, TZSH_QUICKPANEL_EVENT_VISIBLE, _cb_vis_changed, NULL);
    assert_neq(handler, NULL);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


static void
_cb_orientation_changed(int type, tzsh_quickpanel_event_info_h ev_info, void *data)
{
   tzsh_quickpanel_state_orientation_e state;

   if (type != TZSH_QUICKPANEL_EVENT_ORIENTATION) return;

   tzsh_quickpanel_event_orientation_get(ev_info, &state);
}


/**
 * @testcase       utc_tzsh_quickpanel_event_handler_add_p2
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_event_handler_add()
 */
int utc_tzsh_quickpanel_event_handler_add_p2(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    tzsh_quickpanel_event_handler_h handler;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    handler = tzsh_quickpanel_event_handler_add(qp, TZSH_QUICKPANEL_EVENT_ORIENTATION, _cb_orientation_changed, NULL);
    assert_neq(handler, NULL);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_event_handler_del_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_event_handler_del()
 */
int utc_tzsh_quickpanel_event_handler_del_n1(void)
{
    int ret;

    ret = tzsh_quickpanel_event_handler_del(NULL, NULL);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_event_handler_del_p1
 * @since_tizen    3.0
 * @description    Positive test case of tzsh_quickpanel_event_handler_del()
 */
int utc_tzsh_quickpanel_event_handler_del_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret = -1;
    tzsh_quickpanel_event_handler_h handler;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create(tzsh, tzwin);
    assert_neq(qp, NULL);

    handler = tzsh_quickpanel_event_handler_add(qp, TZSH_QUICKPANEL_EVENT_VISIBLE, _cb_vis_changed, NULL);
    assert_neq(handler, NULL);

    ret = tzsh_quickpanel_event_handler_del(qp, handler);
    assert_eq(ret, TZSH_ERROR_NONE);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_event_visible_get_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_event_visible_get()
 */
int utc_tzsh_quickpanel_event_visible_get_n1(void)
{
    int ret;
    tzsh_quickpanel_state_visible_e state;

    ret = tzsh_quickpanel_event_visible_get(NULL, &state);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_event_orientation_get_n1
 * @since_tizen    3.0
 * @description    Negative test case of tzsh_quickpanel_event_orientation_get()
 */
int utc_tzsh_quickpanel_event_orientation_get_n1(void)
{
    int ret;
    tzsh_quickpanel_state_orientation_e state;

    ret = tzsh_quickpanel_event_orientation_get(NULL, &state);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_type_get_n1
 * @since_tizen    5.5
 * @description    Negative test case of tzsh_quickpanel_type_get()
 */
int utc_tzsh_quickpanel_type_get_n1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_window tzwin = 0;
    int ret = -1;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create_with_type(tzsh, tzwin, TZSH_QUICKPANEL_TYPE_SYSTEM_DEFAULT);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_type_get(NULL, NULL);
    assert_eq(ret, TZSH_ERROR_INVALID_PARAMETER);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}


/**
 * @testcase       utc_tzsh_quickpanel_type_get_p1
 * @since_tizen    5.5
 * @description    Positive test case of tzsh_quickpanel_type_get()
 */
int utc_tzsh_quickpanel_type_get_p1(void)
{
    tzsh_h tzsh = NULL;
    tzsh_quickpanel_h qp = NULL;
    tzsh_quickpanel_type_e qp_type = TZSH_QUICKPANEL_TYPE_UNKNOWN;
    tzsh_window tzwin = 0;
    int ret = -1;

    tzwin = elm_win_window_id_get(g_win);

    tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
    assert_neq(tzsh, NULL);

    qp = tzsh_quickpanel_create_with_type(tzsh, tzwin, TZSH_QUICKPANEL_TYPE_SYSTEM_DEFAULT);
    assert_neq(qp, NULL);

    ret = tzsh_quickpanel_type_get(qp, &qp_type);
    assert_neq(ret, TZSH_ERROR_INVALID_PARAMETER);
    assert_eq(qp_type, TZSH_QUICKPANEL_TYPE_SYSTEM_DEFAULT);

    // cleanup resource
    tzsh_quickpanel_destroy(qp);
    tzsh_destroy(tzsh);

    return 0;
}
