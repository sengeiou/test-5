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
static Eina_Bool exitLoop = EINA_FALSE;
static Eina_Bool testResult = EINA_FALSE;

/* Load specified url */
static Eina_Bool loadURL(const char* url)
{
    return ewk_view_url_set(test_view.webview, url);
}

/* Callback for load finished */
static void loadFinished(void* data, Evas_Object* webview, void* event_info)
{
    if (exitLoop)
        utc_webkit2_main_loop_quit();
    exitLoop = EINA_TRUE;
}

/* Callback for load error */
static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
    isLoadSucceed = EINA_FALSE;
}

static void contentsSizeChanged(void* data, Evas_Object* webview, void* event_info)
{
    if (exitLoop)
        ecore_main_loop_quit();
    exitLoop = EINA_TRUE;

    Evas_Coord width = 0;
    Evas_Coord height = 0;

    testResult = ewk_view_contents_size_get(test_view.webview, &width, &height);

    if (width == 0 || height == 0)
        testResult = EINA_FALSE;
}

/* Startup function */
/**
 * @function		utc_webkit2_ewk_view_contents_size_get_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_contents_size_get_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
    evas_object_smart_callback_add(test_view.webview, "contents,size,changed", contentsSizeChanged, NULL);
}

/* Cleanup function */
/**
 * @function		utc_webkit2_ewk_view_contents_size_get_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_contents_size_get_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    evas_object_smart_callback_del(test_view.webview, "contents,size,changed", contentsSizeChanged);
    utc_webkit2_ewk_test_end();

}

/**
 * @testcase		utc_webkit2_ewk_view_contents_size_get_p
 * @since_tizen		2.3
 * @description		Gets the last known content size
 * @scenario        Create Webkit View\n
 *                  Set URL\n
 *                  Check Set URL result in callback\n
 *                  Call the target API
 */
int utc_webkit2_ewk_view_contents_size_get_p(void)
{
    assert(loadURL(COMMON_SAMPLE_HTML_FILE));
    utc_webkit2_main_loop_begin();
    assert(isLoadSucceed);
    assert(testResult);

    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_contents_size_get_n
 * @since_tizen		2.3
 * @description		Gets the last known content size
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_contents_size_get_n(void)
{
    Evas_Coord width = 0;
    Evas_Coord height = 0;

    Eina_Bool result = ewk_view_contents_size_get(NULL, &width, &height);
    assert_eq(result, EINA_FALSE);
    return 0;
}
