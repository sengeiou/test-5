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
#include "utc_webkit2_ewk.h"
#include "assert.h"

#define SAMPLE_HTML_FILE "http://www.samsung.com/pl/home/"
#define TITLE_HTML "ewk_view_html_string_load"
#define TITLE_URI "http://www.samsung.com/pl/home/"

static Eina_Bool isLoadSucceed = EINA_TRUE;

static void loadURL(const char* url)
{
    if (!ewk_view_url_set(test_view.webview, url))
        isLoadSucceed = EINA_FALSE;
}

static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
    isLoadSucceed = EINA_FALSE;
}

static void loadFinished(void* data, Evas_Object* eObject, void* dataFinished)
{
    utc_webkit2_main_loop_quit();
}

/**
 * @function		utc_webkit2_ewk_view_html_string_load_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_html_string_load_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function		utc_webkit2_ewk_view_html_string_load_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_html_string_load_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_html_string_load_p
 * @since_tizen		2.3
 * @description		To test ewk_view_html_string_load
 * @scenario        Create Webkit View\n
 *					Call ewk_view_html_string_load\n
 *					Call the ewk_view_title_get API\n
 *                  Retrieves the value and validate	
 */
int utc_webkit2_ewk_view_html_string_load_p(void)
{
    Eina_Bool result = EINA_FALSE;
    loadURL("<html><head><title>ewk_view_html_string_load</title></head></html>");
    assert_eq(isLoadSucceed, EINA_TRUE);
    utc_webkit2_main_loop_begin();

    result = ewk_view_html_string_load(test_view.webview, "<html><head><title>ewk_view_html_string_load</title></head></html>", NULL, NULL);
    assert_eq(result, EINA_TRUE);

    if (!strcmp(ewk_view_title_get(test_view.webview), TITLE_HTML))
        result = EINA_FALSE;
    assert_eq(result, EINA_TRUE);

    result = ewk_view_html_string_load(test_view.webview, "<html><body onload='document.title=document.URL'></body></html>", SAMPLE_HTML_FILE, NULL);
    assert_eq(result, EINA_TRUE);

    if (!strcmp(ewk_view_title_get(test_view.webview), TITLE_URI))
        result = EINA_FALSE;
    assert_eq(result, EINA_TRUE);

    result = ewk_view_html_string_load(test_view.webview, "<html><body></body></html>", NULL, SAMPLE_HTML_FILE);
    assert_eq(result, EINA_TRUE);

    if (!strcmp(ewk_view_title_get(test_view.webview), TITLE_URI))
        result = EINA_FALSE;
    assert_eq(result, EINA_TRUE);

    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_html_string_load_n
 * @since_tizen		2.3
 * @description		To test ewk_view_html_string_load
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_html_string_load_n(void)
{
    Eina_Bool result = EINA_FALSE;
    result = ewk_view_html_string_load(NULL, "<html></html>", NULL, NULL);
    assert_eq(result, EINA_FALSE);

    result = ewk_view_html_string_load(test_view.webview, NULL, NULL, NULL);
    assert_eq(result, EINA_FALSE);

    return 0;
}
