//
// Copyright (c) 2016 Samsung Electronics Co., Ltd.
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

/* Callback for load finished */
static void loadFinished(void* data, Evas_Object* webview, void* event_info)
{
    isLoadSucceed = EINA_TRUE;
    utc_webkit2_main_loop_quit();
}

/* Callback for load error */
static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    isLoadSucceed = EINA_FALSE;
    utc_webkit2_main_loop_quit();
}

/* Function called when timer expires */
static Eina_Bool mainLoopQuit(void* data)
{
    utc_webkit2_main_loop_quit();
    return EINA_FALSE;
}

/* Startup function */
/**
 * @function    utc_webkit2_ewk_view_focus_set_startup
 * @description Called before each test
 * @parameter   NA
 * @return      NA
 */
void utc_webkit2_ewk_view_focus_set_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/* Cleanup function */
/**
 * @function    utc_webkit2_ewk_view_focus_set_cleanup
 * @description Called after each test
 * @parameter   NA
 * @return      NA
 */
void utc_webkit2_ewk_view_focus_set_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase    utc_webkit2_ewk_view_focus_set_p
 * @since_tizen 3.0
 * @description Gets ewk view focus
 * @scenario    Create ewk view\n
 *              load url\n
 *              set EINA_TRUE value\n
 *              retrieve value\n
 *              validate the set and get values
 */
int utc_webkit2_ewk_view_focus_set_p(void)
{
    Eina_Bool result = ewk_view_url_set(test_view.webview,
                                        COMMON_SAMPLE_HTML_FILE);
    assert_eq(result, EINA_TRUE);
    utc_webkit2_main_loop_begin();
    assert_eq(isLoadSucceed, EINA_TRUE);

    result = ewk_view_focus_set(test_view.webview, EINA_TRUE);
    assert_eq(result, EINA_TRUE);
    ecore_timer_add(2.0f, mainLoopQuit, 0);
    utc_webkit2_main_loop_begin();
    Eina_Bool focus = ewk_view_focus_get(test_view.webview);
    assert_eq(focus, EINA_TRUE);
    return 0;
}

/**
 * @testcase    utc_webkit2_ewk_view_focus_set_p1
 * @since_tizen 3.0
 * @description Gets ewk view focus
 * @scenario    Create ewk view\n
 *              load url\n
 *              set EINA_FALSE value\n
 *              retrieve value\n
 *              validate the set and get values
 */
int utc_webkit2_ewk_view_focus_set_p1(void)
{
    Eina_Bool result = ewk_view_url_set(test_view.webview,
                                        COMMON_SAMPLE_HTML_FILE);
    assert_eq(result, EINA_TRUE);
    utc_webkit2_main_loop_begin();
    assert_eq(isLoadSucceed, EINA_TRUE);

    result = ewk_view_focus_set(test_view.webview, EINA_FALSE);
    assert_eq(result, EINA_TRUE);
    ecore_timer_add(2.0f, mainLoopQuit, 0);
    utc_webkit2_main_loop_begin();
    Eina_Bool focus = ewk_view_focus_get(test_view.webview);
    assert_eq(focus, EINA_FALSE);
    return 0;
}

/**
 * @testcase    utc_webkit2_ewk_view_focus_set_n
 * @since_tizen 3.0
 * @description Gets ewk view focus
 * @scenario    Check operation with incorrect parameter returns propoerly
 */
int utc_webkit2_ewk_view_focus_set_n(void)
{
    Eina_Bool result = ewk_view_focus_set(NULL, EINA_TRUE);
    assert_eq(result, EINA_FALSE);
    return 0;
}
