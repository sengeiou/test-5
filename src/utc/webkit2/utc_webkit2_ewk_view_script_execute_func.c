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

#define TEST_JS_SCRIPT "document.getElementById('getParaContent').innerHTML"
static Eina_Bool isLoadSucceed = EINA_TRUE;
static Eina_Bool isScriptExcutionFinished = EINA_TRUE;

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

static void scriptExecutionFinished(Evas_Object* webview, const char* result_value, void* data)
{
    utc_webkit2_main_loop_quit();

    if (strcmp(result_value, "test content"))
        isScriptExcutionFinished = EINA_FALSE;
}

/**
 * @function		utc_webkit2_ewk_view_script_execute_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_script_execute_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/* Cleanup function */
/**
 * @function		utc_webkit2_ewk_view_script_execute_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_script_execute_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_script_execute_p
 * @since_tizen		2.3
 * @description		Requests the execution of given script
 * @scenario        Create Webkit View\n
 *                  Set URL\n
 *                  Check Set URL result in callback\n
 *                  Call the target API	
 */
int utc_webkit2_ewk_view_script_execute_p(void)
{
    assert(loadURL(COMMON_SAMPLE_HTML_FILE));
    utc_webkit2_main_loop_begin();
    assert(isLoadSucceed);

    Eina_Bool result = ewk_view_script_execute(test_view.webview, TEST_JS_SCRIPT, scriptExecutionFinished, NULL);
    utc_webkit2_main_loop_begin();
    assert(isScriptExcutionFinished);

    assert_eq(result, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_script_execute_n
 * @since_tizen		2.3
 * @description     Requests the execution of given script
 * @scenario        Create Webkit View\n
 *                  Set URL\n
 *                  Check Set URL result in callback\n
 *                  Call the target API 
 */
int utc_webkit2_ewk_view_script_execute_n(void)
{
    Eina_Bool result = ewk_view_script_execute(NULL, TEST_JS_SCRIPT, scriptExecutionFinished, NULL);
    assert_eq(result, EINA_FALSE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_script_execute_n1
 * @since_tizen		2.3
 * @description		Requests the execution of given script
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_script_execute_n1(void)
{
    Eina_Bool result = ewk_view_script_execute(test_view.webview, NULL, scriptExecutionFinished , NULL);
    assert_eq(result, EINA_FALSE);
    return 0;
}
