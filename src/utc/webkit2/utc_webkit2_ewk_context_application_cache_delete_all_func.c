/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
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
 * */

#include <stdio.h>
#include "assert.h"
#include "utc_webkit2_ewk.h"

#define SAMPLE_HTML_FILE "http://www.chromium.org"

static Eina_Bool isLoadSucceed = EINA_TRUE;

static void loadURL(const char* url)
{
    Eina_Bool result = ewk_view_url_set(test_view.webview, url);

    if (!result)
        isLoadSucceed = EINA_FALSE;
}

static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
    isLoadSucceed = EINA_FALSE;
}
static void loadFinished(void* data, Evas_Object* eObject, void* dataFinished)
{
    isLoadSucceed = EINA_TRUE;
    utc_webkit2_main_loop_quit();
}

/* Startup and cleanup functions */
/**
 * @function		utc_webkit2_ewk_context_application_cache_delete_all_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_context_application_cache_delete_all_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function		utc_webkit2_ewk_context_application_cache_delete_all_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_context_application_cache_delete_all_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_context_application_cache_delete_all_p
 * @since_tizen		2.4
 * @description		Request for deleting all web application caches
 * @scenario		ewk_view_context_get\n
 *			ewk_context_application_cache_delete_all
 */
int utc_webkit2_ewk_context_application_cache_delete_all_p(void)
{
    loadURL(SAMPLE_HTML_FILE);
    assert_eq(isLoadSucceed, EINA_TRUE);
    utc_webkit2_main_loop_begin();
    assert_eq(isLoadSucceed, EINA_TRUE);
    Eina_Bool result = ewk_context_application_cache_delete_all(ewk_view_context_get(test_view.webview));
    assert_eq(result, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_context_application_cache_delete_all_n
 * @since_tizen		2.4
 * @description		Request for deleting all web application caches
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_context_application_cache_delete_all_n(void)
{
    Eina_Bool result = ewk_context_application_cache_delete_all(NULL);
    assert_eq(result, EINA_FALSE);
    return 0;
}
