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

#define SAMPLE_HTML_FILE "http://www.chromium.org"

static Eina_Bool isLoadSucceed = EINA_TRUE;
static Eina_Bool result = EINA_FALSE;

static void get_policy_decision_cb(void* data, Evas_Object* webview, void* event_info)
{
    Ewk_Policy_Decision* policy = (Ewk_Policy_Decision*)event_info;
    if (ewk_policy_decision_navigation_type_get(policy) == EWK_POLICY_NAVIGATION_TYPE_LINK_CLICKED
        || ewk_policy_decision_navigation_type_get(policy) == EWK_POLICY_NAVIGATION_TYPE_FORM_SUBMITTED
        || ewk_policy_decision_navigation_type_get(policy) == EWK_POLICY_NAVIGATION_TYPE_BACK_FORWARD
        || ewk_policy_decision_navigation_type_get(policy) == EWK_POLICY_NAVIGATION_TYPE_RELOAD
        || ewk_policy_decision_navigation_type_get(policy) == EWK_POLICY_NAVIGATION_TYPE_FORM_RESUBMITTED
        || ewk_policy_decision_navigation_type_get(policy) == EWK_POLICY_NAVIGATION_TYPE_OTHER)
        result = EINA_TRUE;
}

static void loadURL(const char* url)
{
    if (!ewk_view_url_set(test_view.webview, url))
        isLoadSucceed = EINA_FALSE;
}

/* Callback for load finished */
static void loadFinished(void* data, Evas_Object* webview, void* arg)
{
    isLoadSucceed = EINA_TRUE;
    utc_webkit2_main_loop_quit();
}

/* Callback for load error */
static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    result = EINA_FALSE;
    utc_webkit2_main_loop_quit();
    isLoadSucceed = EINA_FALSE;
}

/* Startup and cleanup functions */
/**
 * @function		utc_webkit2_ewk_policy_decision_navigation_type_get_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_policy_decision_navigation_type_get_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
    evas_object_smart_callback_add(test_view.webview,"policy,navigation,decide", get_policy_decision_cb, NULL);

}

/**
 * @function		utc_webkit2_ewk_policy_decision_navigation_type_get_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_policy_decision_navigation_type_get_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    evas_object_smart_callback_del(test_view.webview, "policy,navigation,decide", NULL);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_policy_decision_navigation_type_get_p
 * @since_tizen		2.3
 * @description		Returns a navigation type from Policy Decision object
 * @scenario		Call ewk_policy_decision_navigation_type_get in callback
 */
int utc_webkit2_ewk_policy_decision_navigation_type_get_p(void)
{
    loadURL(SAMPLE_HTML_FILE);
    assert_eq(isLoadSucceed, EINA_TRUE);
    utc_webkit2_main_loop_begin();
    assert_eq(result, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_policy_decision_navigation_type_get_n
 * @since_tizen		2.3
 * @description		Returns a navigation type from Policy Decision object
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_policy_decision_navigation_type_get_n(void)
{
    assert_eq(ewk_policy_decision_navigation_type_get(NULL), EWK_POLICY_NAVIGATION_TYPE_OTHER);
    return 0;
}
