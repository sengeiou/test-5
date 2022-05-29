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

#define TEXT1 "apple"
#define TEXT2 "mango"

static Eina_Bool isLoadSucceed = EINA_TRUE;
static int matchCount;

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

static void onTextFound(void* userData, Evas_Object* webview, void* eventInfo)
{
    int* result = (int*)userData;
    int* matchCount = (int*)eventInfo;
    *result = *matchCount;
}

/* Startup function */
/**
 * @function		utc_webkit2_ewk_view_text_find_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_text_find_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
    evas_object_smart_callback_add(test_view.webview, "text,found", onTextFound, &matchCount);
}

/* Cleanup function */
/**
 * @function		utc_webkit2_ewk_view_text_find_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_text_find_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    evas_object_smart_callback_del(test_view.webview, "text,found", onTextFound);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_text_find_p
 * @since_tizen		2.3
 * @description		Searches and highlights the given string in the document
 * @scenario		Create Webkit View\n
 *                  Set URL\n
 *                  Check Set URL result in callback\n
 *                  Call the target API
 */
int utc_webkit2_ewk_view_text_find_p(void)
{
    matchCount = -1;
    loadURL(EWK_VIEW_TEXT_FIND_HTML_FILE);
    utc_webkit2_main_loop_begin();
	assert_eq(isLoadSucceed, EINA_TRUE);

    ewk_view_text_find(test_view.webview, TEXT1, EWK_FIND_OPTIONS_SHOW_OVERLAY, 100);
    while (matchCount < 0)
        ecore_main_loop_iterate();

    assert_eq(matchCount, 3);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_text_find_n
 * @since_tizen		2.3
 * @description		Searches and highlights the given string in the document
 * @scenario        Check operation entered incorrect parameter	
 */
int utc_webkit2_ewk_view_text_find_n(void)
{
    matchCount = -1;
    loadURL(EWK_VIEW_TEXT_FIND_HTML_FILE);
    utc_webkit2_main_loop_begin();
    assert_eq(isLoadSucceed, EINA_TRUE);
    ewk_view_text_find(test_view.webview, TEXT2, EWK_FIND_OPTIONS_SHOW_OVERLAY, 100);

    while (matchCount < 0)
        ecore_main_loop_iterate();

    assert_eq(matchCount, 0);
    return 0;
}
