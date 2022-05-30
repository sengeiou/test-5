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
    if (!ewk_view_url_set(test_view.webview, url))
        isLoadSucceed = EINA_FALSE;
}

/* Callback for load finished */
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
 * @function		utc_webkit2_ewk_view_stop_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_stop_startup(void)
{
    utc_webkit2_ewk_test_init();

    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function		utc_webkit2_ewk_view_stop_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_stop_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_stop_p
 * @since_tizen		2.3
 * @description		Asks the main frame to stop loading
 * @scenario        Create Webkit View\n
 *                  Set URL\n
 *                  Check Set URL result in callback\n
 *                  Stop loading the view
 */
int utc_webkit2_ewk_view_stop_p(void)
{
    loadURL(COMMON_SAMPLE_HTML_FILE);
    utc_webkit2_main_loop_begin();
    assert_eq(isLoadSucceed, EINA_TRUE);

    Eina_Bool result = ewk_view_stop(test_view.webview);
    assert_neq(result, EINA_FALSE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_stop_n
 * @since_tizen		2.3
 * @description		Asks the main frame to stop loading
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_stop_n(void)
{
    Eina_Bool result = ewk_view_stop(NULL);
    assert_eq(result, EINA_FALSE);
    return 0;
}
