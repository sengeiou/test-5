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

static void loadURL(const char* url)
{
    Eina_Bool result =  ewk_view_url_set(test_view.webview, url);
    if (!result)
        isLoadSucceed = EINA_FALSE;
}

static void loadFinished(void *data, Evas_Object *webview, void *arg)
{
    isLoadSucceed = EINA_TRUE;
    ecore_main_loop_quit();
}

static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
    isLoadSucceed = EINA_FALSE;
}
/* Startup and cleanup functions */
/**
 * @function		utc_webkit2_ewk_view_url_get_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_url_get_startup(void)
{
    utc_webkit2_ewk_test_init();

    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function		utc_webkit2_ewk_view_url_get_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_url_get_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);

    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_url_get_p
 * @since_tizen		2.3
 * @description		
 */
int utc_webkit2_ewk_view_url_get_p(void)
{
    loadURL(COMMON_SAMPLE_HTML_FILE);
    assert_eq(isLoadSucceed, EINA_TRUE);
    utc_webkit2_main_loop_begin();

    const char* currentUrl = ewk_view_url_get(test_view.webview);

	Eina_Bool result = EINA_FALSE;
    if (!strcmp(currentUrl, COMMON_SAMPLE_HTML_FILE))
    	result = EINA_TRUE;
    assert_eq(result , EINA_TRUE);

	return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_url_get_n
 * @since_tizen		2.3
 * @description		
 */
int utc_webkit2_ewk_view_url_get_n(void)
{
    const char* currentUrl = ewk_view_url_get(NULL);
    assert_eq(currentUrl ? EINA_TRUE : EINA_FALSE, EINA_FALSE);

	return 0;
}
