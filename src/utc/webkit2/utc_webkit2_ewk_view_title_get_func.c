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

#define TITLE "Testing Sample Page"

static Eina_Bool isLoadSucceed = EINA_TRUE;

static void loadURL(const char* url)
{
    if (!ewk_view_url_set(test_view.webview, url))
        isLoadSucceed = EINA_FALSE;
}

/*Callback for load finished */
static void loadFinished(void *data, Evas_Object *webview, void *arg)
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

/* Startup and cleanup functions */
/**
 * @function		utc_webkit2_ewk_view_title_get_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_title_get_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function		utc_webkit2_ewk_view_title_get_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_title_get_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_title_get_p
 * @since_tizen		2.3
 * @description		Gets the current title of the main frame
 * @scenario 		Create Webkit View\n
 *                  Set Content\n
 *                  Call the API\n
 *                  Retrieves the value and validate
 */
int utc_webkit2_ewk_view_title_get_p(void)
{
    loadURL(COMMON_SAMPLE_HTML_FILE);
    utc_webkit2_main_loop_begin();
    assert_eq(isLoadSucceed, EINA_TRUE);

    Eina_Bool result = EINA_FALSE;
	if (!strcmp(ewk_view_title_get(test_view.webview), TITLE))
    	result = EINA_TRUE;
    assert_neq(result, EINA_FALSE);

	return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_title_get_n
 * @since_tizen		2.3
 * @description		Gets the current title of the main frame
 * @scenario        Check operation entered incorrect parameter	
 */
int utc_webkit2_ewk_view_title_get_n(void)
{
    const char* title = ewk_view_title_get(NULL);
    assert_eq(title, NULL);

    return 0;
}
