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

static void getAcceptPolicyCallback(Ewk_Cookie_Accept_Policy policy, void* event_info)
{
    Ewk_Cookie_Accept_Policy* ret = (Ewk_Cookie_Accept_Policy*)event_info;
    *ret = policy;
    utc_webkit2_main_loop_quit();
}

static Ewk_Cookie_Accept_Policy getAcceptPolicy(Ewk_Cookie_Manager* manager)
{
    Ewk_Cookie_Accept_Policy policy = EWK_COOKIE_ACCEPT_POLICY_ALWAYS;
    ewk_cookie_manager_accept_policy_async_get(manager, getAcceptPolicyCallback, &policy);
    utc_webkit2_main_loop_begin();
    return policy;
}

/**
 * @function		utc_webkit2_ewk_cookie_manager_accept_policy_async_get_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_cookie_manager_accept_policy_async_get_startup(void)
{
    utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_cookie_manager_accept_policy_async_get_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_cookie_manager_accept_policy_async_get_cleanup(void)
{
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_cookie_manager_accept_policy_async_get_p
 * @since_tizen		2.3
 * @description		Get policy for the cookie acceptance policy manager
 * @scenario		Set policy\n
 *			Check policy in callback\n
 *			compare the value
 */
int utc_webkit2_ewk_cookie_manager_accept_policy_async_get_p(void)
{
    Ewk_Cookie_Manager* cookieManager = ewk_context_cookie_manager_get(ewk_view_context_get(test_view.webview));
    ewk_cookie_manager_accept_policy_set(cookieManager, EWK_COOKIE_ACCEPT_POLICY_NO_THIRD_PARTY);
    assert_eq(getAcceptPolicy(cookieManager), EWK_COOKIE_ACCEPT_POLICY_NO_THIRD_PARTY);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_cookie_manager_accept_policy_async_get_n
 * @since_tizen		2.3
 * @description		Get policy for the cookie acceptance policy manager
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_cookie_manager_accept_policy_async_get_n(void)
{
    ewk_cookie_manager_accept_policy_async_get(NULL, NULL, NULL);
    return 0;
}
