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
    printf("loadURL\n");
    Eina_Bool result =  ewk_view_url_set(test_view.webview, url);
    if (!result)
        isLoadSucceed = EINA_FALSE;
}

static void load_finished(void* data, Evas_Object* webview, void* event_info)
{
    printf("load_finished\n");
    isLoadSucceed = EINA_TRUE;
    utc_webkit2_main_loop_quit();
}

static void load_error(void* data, Evas_Object* webview, void* event_info)
{
    printf("load_error\n");
    isLoadSucceed = EINA_FALSE;
    utc_webkit2_main_loop_quit();
}

/* Startup and cleanup functions */
/**
 * @function		utc_webkit2_ewk_view_url_set_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_url_set_func_startup(void)
{
    utc_webkit2_ewk_test_init();

    evas_object_smart_callback_add(test_view.webview, "load,finished", load_finished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", load_error, NULL);
}

/**
 * @function		utc_webkit2_ewk_view_url_set_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_url_set_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", load_finished);
    evas_object_smart_callback_del(test_view.webview, "load,error", load_error);

    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_url_set_p
 * @since_tizen		2.3
 * @description		Asked to set the URL string to the view object
 * @scenario        Create Webkit View\n
 *                  Set URL\n
 *                  Check Set URL result in callback\n
 *                  Retrieves the URL
 */
int utc_webkit2_ewk_view_url_set_p(void)
{
    loadURL(COMMON_SAMPLE_HTML_FILE);
    utc_webkit2_main_loop_begin();
    assert_eq(isLoadSucceed, EINA_TRUE);

    Eina_Bool result = EINA_FALSE;
	if (!strcmp(ewk_view_url_get(test_view.webview), COMMON_SAMPLE_HTML_FILE))
        result = EINA_TRUE;
    assert_eq(result , EINA_TRUE);

	return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_url_set_n
 * @since_tizen		2.3
 * @description		Asked to set the URL string to the view object
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_url_set_n(void)
{
    Eina_Bool result = ewk_view_url_set(NULL, COMMON_SAMPLE_HTML_FILE);
    assert_neq(result, EINA_TRUE);

	return 0;
}
