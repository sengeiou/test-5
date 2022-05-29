/* Copyright (c) 2014 Samsung Electronics Co., Ltd.

   Licensed under the Apache License, Version 2.0 (the License);
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "utc_webkit2_ewk.h"
#include "assert.h"

static Eina_Bool isLoadSucceed = EINA_TRUE;

static void loadURL(const char* url)
{
    if (!ewk_view_url_set(test_view.webview, url))
        isLoadSucceed = EINA_FALSE;
}

/*Callback for load finished */
static void loadFinished(void *data, Evas_Object *webview, void *arg)
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

/**
 * @function		utc_webkit2_ewk_view_text_selection_clear_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_text_selection_clear_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function		utc_webkit2_ewk_view_text_selection_clear_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_text_selection_clear_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_text_selection_clear_p
 * @since_tizen		2.3
 * @description		To clear selected text
 * @scenario   		ewk_view_url_set\n
 *                  ewk_view_text_selection_text_get\n
 *                  ewk_view_text_selection_clear
 */
int utc_webkit2_ewk_view_text_selection_clear_p(void)
{
    loadURL(EWK_VIEW_TEXT_SELECTION_HTML_FILE);
    utc_webkit2_main_loop_begin();
    assert_eq(isLoadSucceed, EINA_TRUE);

    const char* selectedText = ewk_view_text_selection_text_get(test_view.webview);
    assert_neq(strlen(selectedText), 0);

    ewk_view_text_selection_clear(test_view.webview);
    selectedText = ewk_view_text_selection_text_get(test_view.webview);
    assert_eq(strlen(selectedText), 0);

    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_text_selection_clear_n
 * @since_tizen		2.3
 * @description		To clear selected text
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_text_selection_clear_n(void)
{
    Eina_Bool result = ewk_view_text_selection_clear(NULL);
    assert_eq(result, EINA_FALSE);
    return 0;
}
