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

#define URL ("file:///zzxxccvv.html/")

static int errorCode = 0;

static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    Ewk_Error* ewkError = (Ewk_Error*)event_info;
    errorCode = ewk_error_code_get(ewkError);
    utc_webkit2_main_loop_quit();
}

static void loadFinished(void* data, Evas_Object* webview, void* arg)
{
    utc_webkit2_main_loop_quit();
}

/**
 * @function		utc_webkit2_ewk_error_code_get_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_error_code_get_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
}

/**
 * @function		utc_webkit2_ewk_error_code_get_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_error_code_get_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_error_code_get_p
 * @since_tizen		2.3
 * @description		Query failing URL for load error
 * @scenario		Load Invalid file to invoke load error callback\n
 *			Call ewk_error_code_get and validate the result
 */
int utc_webkit2_ewk_error_code_get_p(void)
{
    Eina_Bool result = ewk_view_url_set(test_view.webview, URL);
    assert_neq(result, 0);
    utc_webkit2_main_loop_begin();
    assert_eq(errorCode, EWK_ERROR_CODE_FAILED_FILE_IO);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_error_code_get_n
 * @since_tizen		2.3
 * @description		Query failing URL for load error
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_error_code_get_n(void)
{
    assert_eq(ewk_error_code_get(NULL), EWK_ERROR_CODE_UNKNOWN);
    return 0;
}
