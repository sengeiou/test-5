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
    utc_webkit2_main_loop_quit();
}

/**
 * @function		utc_webkit2_ewk_back_forward_list_item_ref_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_back_forward_list_item_ref_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function		utc_webkit2_ewk_back_forward_list_item_ref_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_back_forward_list_item_ref_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_back_forward_list_item_ref_p
 * @since_tizen		2.3
 * @description		Increases the reference count of the item in the BackForward list
 * @scenario		Set URL\n
 *			Check Set URL result in callback\n
 *			Retrieves the BackForward List\n
 *			Retrieves the BackForwardList item
 *			References and dereference the BackForwardList item
 */
int utc_webkit2_ewk_back_forward_list_item_ref_p(void)
{
    loadURL(COMMON_SAMPLE_HTML_FILE);
    assert_eq(isLoadSucceed, EINA_TRUE);
    utc_webkit2_main_loop_begin();
    Ewk_Back_Forward_List *list = ewk_view_back_forward_list_get(test_view.webview);
    Ewk_Back_Forward_List_Item *item = ewk_back_forward_list_item_ref(ewk_back_forward_list_current_item_get(list));
    assert_neq(item, 0);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_back_forward_list_item_ref_n
 * @since_tizen		2.3
 * @description		Increases the reference count of the item in the BackForward list
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_back_forward_list_item_ref_n(void)
{
    Ewk_Back_Forward_List_Item *item = ewk_back_forward_list_item_ref(NULL);
    assert_eq(item,0);
    return 0;
}