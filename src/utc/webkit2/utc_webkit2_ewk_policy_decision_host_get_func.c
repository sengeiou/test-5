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

static Eina_Bool result = EINA_FALSE;

static void load_finished(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
}

static void load_error(void* data, Evas_Object* webview, void* event_info)
{
    result = EINA_FALSE;
    utc_webkit2_main_loop_quit();
}

static void policy_navigation_decide(void* data, Evas_Object* webview, void* event_info)
{
    Ewk_Policy_Decision* policy_decision = (Ewk_Policy_Decision*)event_info;

    if (ewk_policy_decision_host_get(policy_decision))
        result = EINA_TRUE;
    else
        result = EINA_FALSE;

    utc_webkit2_main_loop_quit();
}

/* Startup and cleanup functions */
/**
 * @function		utc_webkit2_ewk_policy_decision_host_get_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_policy_decision_host_get_func_startup(void)
{
    utc_webkit2_ewk_test_init();

    evas_object_smart_callback_add(test_view.webview, "load,finished", load_finished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", load_error, NULL);
    evas_object_smart_callback_add(test_view.webview, "policy,navigation,decide", policy_navigation_decide, NULL);
}

/**
 * @function		utc_webkit2_ewk_policy_decision_host_get_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_policy_decision_host_get_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", load_finished);
    evas_object_smart_callback_del(test_view.webview, "load,error", load_error);
    evas_object_smart_callback_del(test_view.webview, "policy,navigation,decide", policy_navigation_decide);

    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_policy_decision_host_get_p
 * @since_tizen		2.3
 * @description		Returns Host from policy decision object
 * @scenario		Call ewk_policy_decision_host_get in callback
 */
int utc_webkit2_ewk_policy_decision_host_get_p(void)
{
    assert_neq(ewk_view_url_set(test_view.webview, "http://www.chromium.org"), 0);
    utc_webkit2_main_loop_begin();

    assert_eq(result, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_policy_decision_host_get_n
 * @since_tizen		2.3
 * @description		Returns Host from policy decision object
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_policy_decision_host_get_n(void)
{
    assert_eq(ewk_policy_decision_host_get(0), 0);
    return 0;
}
