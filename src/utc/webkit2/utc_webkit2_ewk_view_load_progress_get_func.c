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

static const double professComplete = 1.0;
static const double invalidLoad = -1.0;
static Eina_Bool isLoadSucceed = EINA_TRUE;

/* Callback for load error */
static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
    isLoadSucceed = EINA_FALSE;
}
static void loadProgress(void *data, Evas_Object *webview, void *arg)
{
   ecore_main_loop_quit();
}
static void loadFinished(void *data, Evas_Object *webview, void *arg)
{
    ecore_main_loop_quit();
}

/**
 * @function		utc_webkit2_ewk_view_load_progress_get_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_load_progress_get_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,progress", loadProgress, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function		utc_webkit2_ewk_view_load_progress_get_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_load_progress_get_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_load_progress_get_p
 * @since_tizen		2.3
 * @description		Gets the progress status for loading in the main frame	
 * @scenario        ewk_view_load_progress_get
 */
int utc_webkit2_ewk_view_load_progress_get_p(void)
{
    Eina_Bool result = EINA_FALSE;
    double value = ewk_view_load_progress_get(test_view.webview);
     if (value == 0)
        result = EINA_TRUE;
    assert_eq(result, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_load_progress_get_p1
 * @since_tizen		2.3
 * @description		Gets the progress status for loading in the main frame
 * @scenario        Create Webkit View\n
 *                  Set Content\n
 *                  Call the API\n
 *                  Retrieves the value and validate\n
 */
int utc_webkit2_ewk_view_load_progress_get_p1(void)
{
    double value = 1.0;
    Eina_Bool result = EINA_FALSE;
    char* fullPath = COMMON_SAMPLE_HTML_FILE;
    ewk_view_url_set(test_view.webview, fullPath);

    utc_webkit2_main_loop_begin();
    assert(isLoadSucceed);
    value = ewk_view_load_progress_get(test_view.webview);
    if (value <= professComplete)
        result = EINA_TRUE;
    assert_eq(result, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_load_progress_get_n
 * @since_tizen		2.3
 * @description		Gets the progress status for loading in the main frame
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_load_progress_get_n(void)
{
    double value = -1.0;
    Eina_Bool result = EINA_FALSE;
    value = ewk_view_load_progress_get(NULL);
    if (value == invalidLoad)
        result = EINA_TRUE;
    assert_eq(result, EINA_TRUE);
    return 0;
}
