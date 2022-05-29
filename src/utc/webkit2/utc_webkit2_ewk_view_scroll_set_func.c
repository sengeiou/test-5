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
#include "utc_webkit2_ewk.h"

static Eina_Bool isLoadSucceed = EINA_TRUE;

static Eina_Bool loadURL(const char* url)
{
    return ewk_view_url_set(test_view.webview, url);
}

static void loadFinished(void* data, Evas_Object* eObject, void* dataFinished)
{
    utc_webkit2_main_loop_quit();
}

/* Callback for load error */
static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
    isLoadSucceed = EINA_FALSE;
}

/**
 * @function		utc_webkit2_ewk_view_scroll_set_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_scroll_set_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function		utc_webkit2_ewk_view_scroll_set_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_scroll_set_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

static Eina_Bool mainLoopQuit(void* data)
{
    utc_webkit2_main_loop_quit();
    return ECORE_CALLBACK_CANCEL;
}

/**
 * @testcase		utc_webkit2_ewk_view_scroll_set_p
 * @since_tizen		2.3
 * @description		Sets an absolute scroll position of the view
 * @scenario        Create Webkit View\n
 *                  Set Value\n
 *                  Retrieve value\n
 *                  Validate the set and return values
 */
int utc_webkit2_ewk_view_scroll_set_p(void)
{
    assert(loadURL(EWK_VIEW_SCROLL_HTML_FILE));
    utc_webkit2_main_loop_begin();
    assert(isLoadSucceed);

    int scrollOffset = 2;
    Eina_Bool result = EINA_FALSE;
    result = ewk_view_scroll_set(test_view.webview, scrollOffset, scrollOffset);
    assert_eq(result, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_scroll_set_p1
 * @since_tizen		2.3
 * @description     Sets an absolute scroll position of the view
 * @scenario        Create Webkit View\n
 *                  Set Value\n
 *                  Retrieve value\n
 *                  Validate the set and get values
 */
int utc_webkit2_ewk_view_scroll_set_p1(void)
{
    int scrollOffset = 28;
    int x = 0, y = 0;
    Eina_Bool result = EINA_FALSE;
    Eina_Bool finalCheck = EINA_FALSE;

    assert(loadURL(EWK_VIEW_SCROLL_HTML_FILE));
    utc_webkit2_main_loop_begin();
    assert(isLoadSucceed);

    result = ewk_view_scroll_set(test_view.webview, scrollOffset, scrollOffset);
    assert_eq(result, EINA_TRUE);

    ecore_timer_add(1.0f, mainLoopQuit, 0);
    utc_webkit2_main_loop_begin();

    if (ewk_view_scroll_pos_get(test_view.webview, &x, &y)) {
        if (x == scrollOffset && y == scrollOffset)
            finalCheck = EINA_TRUE;
    }
    assert_eq(finalCheck, EINA_TRUE);

    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_scroll_set_p2
 * @since_tizen		2.3
 * @description     Sets an absolute scroll position of the view
 * @scenario        Create Webkit View\n
 *                  Set Value\n
 *                  Retrieve value\n
 *                  Validate the set and get values
 */
int utc_webkit2_ewk_view_scroll_set_p2(void)
{
    int x = 0, y = 0;
    int scrollOffset = -12;
    Eina_Bool result = EINA_FALSE;
    Eina_Bool finalCheck = EINA_FALSE;

    assert(loadURL(EWK_VIEW_SCROLL_HTML_FILE));
    utc_webkit2_main_loop_begin();
    assert(isLoadSucceed);

    result = ewk_view_scroll_set(test_view.webview, scrollOffset, scrollOffset);
    assert_eq(result, EINA_TRUE);

    ecore_timer_add(1.0f, mainLoopQuit, 0);
    utc_webkit2_main_loop_begin();

    if (ewk_view_scroll_pos_get(test_view.webview, &x, &y)) {
        if (x == 0 && y == 0)
            finalCheck = EINA_TRUE;
    }
    assert_eq(finalCheck, EINA_TRUE);

    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_scroll_set_n
 * @since_tizen		2.3
 * @description		Sets an absolute scroll position of the view
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_scroll_set_n(void)
{
    assert_eq(ewk_view_scroll_set(NULL, 1916, 1993), EINA_FALSE);
    return 0;
}
