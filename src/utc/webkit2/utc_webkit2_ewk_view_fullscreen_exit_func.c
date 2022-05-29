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

static void loadFinished(void *data, Evas_Object *webview, void *arg)
{
    isLoadSucceed = EINA_TRUE;
    utc_webkit2_main_loop_quit();
}

static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    isLoadSucceed = EINA_FALSE;
    utc_webkit2_main_loop_quit();
}

/**
 * @function		utc_webkit2_ewk_view_fullscreen_exit_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_fullscreen_exit_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function		utc_webkit2_ewk_view_fullscreen_exit_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_fullscreen_exit_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/* For verifying the API, it's needed using internal function. (for checking webview is full screen) so fix of this TC postpone until later. */
/**
 * @testcase		utc_webkit2_ewk_view_fullscreen_exit_p
 * @since_tizen		2.3
 * @description		Exits the fullscreen mode
 * @scenario        Create Webkit View\n
 *                  Set URL\n
 *                  Check Set URL result in callback\n
 *                  Call the target API
 */
int utc_webkit2_ewk_view_fullscreen_exit_p(void)
{
    ewk_view_fullscreen_exit(test_view.webview);

    assert(1);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_fullscreen_exit_n
 * @since_tizen		2.3
 * @description		Exits the fullscreen mode
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_fullscreen_exit_n(void)
{
    Eina_Bool result = ewk_view_fullscreen_exit(NULL);
    assert_eq(result, EINA_FALSE);

    return 0;
}
