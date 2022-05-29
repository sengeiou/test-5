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

static Eina_Bool loadURL(const char* url)
{
    return ewk_view_url_set(test_view.webview, url);
}

static void loadFinished(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
}

static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
    isLoadSucceed = EINA_FALSE;
}

/**
 * @function		utc_webkit2_ewk_view_back_forward_list_get_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_back_forward_list_get_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function		utc_webkit2_ewk_view_back_forward_list_get_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_back_forward_list_get_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_back_forward_list_get_p
 * @since_tizen		2.3
 * @description		Gets the back forward list associated with this view
 * @scenario        Create Webkit View\n
 *                  Set Content\n
 *                  Call the API\n
 *                  Retrieves the BackForward List and validate	
 */
int utc_webkit2_ewk_view_back_forward_list_get_p(void)
{
    assert(loadURL(EWK_VIEW_BACK_FORWARD_HTML_FILE));
    utc_webkit2_main_loop_begin();
    assert(isLoadSucceed);

    Ewk_Back_Forward_List* backForwardList = ewk_view_back_forward_list_get(test_view.webview);
    assert(backForwardList);

    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_back_forward_list_get_n
 * @since_tizen		2.3
 * @description		Gets the back forward list associated with this view
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_back_forward_list_get_n(void)
{
    assert_eq(ewk_view_back_forward_list_get(NULL), EINA_FALSE);

    return 0;
}
