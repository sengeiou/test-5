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
#include "utc_webkit2_ewk.h"
#include "assert.h"

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
 * @function		utc_webkit2_ewk_back_forward_list_n_forward_items_copy_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_back_forward_list_n_forward_items_copy_func_startup(void)
{
   utc_webkit2_ewk_test_init();
   evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
   evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function		utc_webkit2_ewk_back_forward_list_n_forward_items_copy_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_back_forward_list_n_forward_items_copy_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_back_forward_list_n_forward_items_copy_p
 * @since_tizen		2.3
 * @description		Copies the BackForward list from forward items
 * @scenario		Set URL\n
 *			Check Set URL result in callback\n
 *			Retrieves the BackForward List\n
 *			Copies the BackForwardList item
 */
int utc_webkit2_ewk_back_forward_list_n_forward_items_copy_p(void)
{
    Eina_Bool result = EINA_FALSE;
    loadURL(COMMON_SAMPLE_HTML_FILE);
    assert_eq(isLoadSucceed, EINA_TRUE);
    utc_webkit2_main_loop_begin();

    loadURL(COMMON_SAMPLE1_HTML_FILE);
    assert_eq(isLoadSucceed, EINA_TRUE);
    utc_webkit2_main_loop_begin();

    loadURL(COMMON_SAMPLE2_HTML_FILE);
    assert_eq(isLoadSucceed, EINA_TRUE);
    utc_webkit2_main_loop_begin();

    ewk_view_back(test_view.webview);
    assert_eq(isLoadSucceed, EINA_TRUE);
    utc_webkit2_main_loop_begin();

    ewk_view_back(test_view.webview);
    assert_eq(isLoadSucceed, EINA_TRUE);
    utc_webkit2_main_loop_begin();

    Ewk_Back_Forward_List* list = ewk_view_back_forward_list_get(test_view.webview);
    Eina_List* copyForwardList = ewk_back_forward_list_n_forward_items_copy(list, 1);

    assert_neq(copyForwardList, 0);
    assert_eq(eina_list_count(copyForwardList), 1);

    Ewk_Back_Forward_List_Item* item = eina_list_nth(copyForwardList, 0);
    assert_neq(item, 0);

    if (strcmp(ewk_back_forward_list_item_url_get(item), COMMON_SAMPLE1_HTML_FILE))
        result = EINA_TRUE;
    if (strcmp(ewk_back_forward_list_item_title_get(item), "Testing Sample Page 1"))
        result = EINA_TRUE;
    if (strcmp(ewk_back_forward_list_item_original_url_get(item), COMMON_SAMPLE1_HTML_FILE))
        result = EINA_TRUE;
    assert_eq(result , EINA_FALSE);

    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_back_forward_list_n_forward_items_copy_n
 * @since_tizen		2.3
 * @description		Copies the BackForward list from forward items
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_back_forward_list_n_forward_items_copy_n(void)
{
    Eina_List* copyForwardList = ewk_back_forward_list_n_forward_items_copy(NULL, 0);
    assert_eq(copyForwardList, 0);
    return 0;
}
