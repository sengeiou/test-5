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

/* Load specified url */
static void loadURL(const char* url)
{
    Eina_Bool result = ewk_view_url_set(test_view.webview, url);

    if (!result)
        isLoadSucceed = EINA_FALSE;
}

/* Callback for load finished */
static void loadFinished(void* data, Evas_Object* webview, void* event_info)
{
    isLoadSucceed = EINA_TRUE;
    utc_webkit2_main_loop_quit();
}

/* Callback for load error */
static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
    isLoadSucceed = EINA_FALSE;
}

/* Function called when timer expires */
static Eina_Bool mainLoopQuit(void* data)
{
    utc_webkit2_main_loop_quit();
    return EINA_FALSE;
}

/* Startup function */
/**
 * @function		utc_webkit2_ewk_view_scale_get_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_scale_get_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/* Cleanup function */
/**
 * @function		utc_webkit2_ewk_view_scale_get_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_scale_get_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_scale_get_p
 * @since_tizen		2.3
 * @description	 	Gets scale factor for the page
 * @scenario        Create Webkit View\n
 *                  Set Value\n
 *                  Retrieve value\n
 *                  Validate the set and get values
 */
int utc_webkit2_ewk_view_scale_get_p(void)
{
    loadURL(COMMON_SAMPLE_HTML_FILE);
    assert_eq(isLoadSucceed, EINA_TRUE);
    utc_webkit2_main_loop_begin();

    double scaleFactor = 3.0;
    Evas_Coord centerX = 5;
    Evas_Coord centerY = 5;
    Eina_Bool result = ewk_view_scale_set(test_view.webview, scaleFactor, centerX, centerY);
    ecore_timer_add(2.0f, mainLoopQuit, 0);
    utc_webkit2_main_loop_begin();
    double getScaleFactor = ewk_view_scale_get(test_view.webview);

    if (scaleFactor != getScaleFactor)
        result = EINA_FALSE;

    assert_eq(result, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_scale_get_n
 * @since_tizen		2.3
 * @description		Gets scale factor for the page
 * @scenario        Check operation entered incorrect parameter	
 */
int utc_webkit2_ewk_view_scale_get_n(void)
{
    double getScaleFactor = ewk_view_scale_get(NULL);
    assert_eq(getScaleFactor, -1);
    return 0;
}
