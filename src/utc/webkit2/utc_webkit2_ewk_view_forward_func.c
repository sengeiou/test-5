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
#include <stdio.h>
#include "assert.h"
#include "utc_webkit2_ewk.h"

static Eina_Bool isLoadSucceed = EINA_TRUE;

/* Load specified url */
static Eina_Bool loadURL(const char* url)
{
    return ewk_view_url_set(test_view.webview, url);
}

/* Callback for load finished */
static void loadFinished(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
}

/* Callback for load error */
static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
    isLoadSucceed = EINA_FALSE;
}

/* Startup function */
/**
 * @function		utc_webkit2_ewk_view_forward_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_forward_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/* Cleanup function */
/**
 * @function		utc_webkit2_ewk_view_forward_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_forward_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_forward_p
 * @since_tizen		2.3
 * @description		Asks the main frame to navigate forward in history
 * @scenario        Create Webkit View\n
 *                  Set URL\n
 *                  Check Set URL result in callback\n
 *                  Navigate back and Call target API
 */
int utc_webkit2_ewk_view_forward_p(void)
{
    assert(loadURL(COMMON_SAMPLE_HTML_FILE));
    utc_webkit2_main_loop_begin();
    assert(isLoadSucceed);

    assert(loadURL(COMMON_SAMPLE1_HTML_FILE));
    utc_webkit2_main_loop_begin();
    assert(isLoadSucceed);

    if (ewk_view_back(test_view.webview))
        utc_webkit2_main_loop_begin();

    Eina_Bool forwardResult = ewk_view_forward(test_view.webview);
    if (forwardResult)
        utc_webkit2_main_loop_begin();

    assert_eq(forwardResult, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_forward_n
 * @since_tizen		2.3
 * @description		 Asks the main frame to navigate forward in history
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_forward_n(void)
{
    Eina_Bool result = ewk_view_forward(NULL);
    assert_eq(result, EINA_FALSE);
    return 0;
}
