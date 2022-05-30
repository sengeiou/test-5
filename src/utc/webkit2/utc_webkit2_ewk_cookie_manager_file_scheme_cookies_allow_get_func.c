//
// Copyright (c) 2016 Samsung Electronics Co., Ltd.
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

/**
 * @function        utc_webkit2_ewk_cookie_manager_file_scheme_cookies_allow_get_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_webkit2_ewk_cookie_manager_file_scheme_cookies_allow_get_startup(void)
{
    utc_webkit2_ewk_test_init();
}

/**
 * @function        utc_webkit2_ewk_cookie_manager_file_scheme_cookies_allow_get_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_webkit2_ewk_cookie_manager_file_scheme_cookies_allow_get_cleanup(void)
{
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase        utc_webkit2_ewk_cookie_manager_file_scheme_cookies_allow_get_p
 * @since_tizen     3.0
 * @description     Get policy for the cookie acceptance for file scheme URLs
 * @scenario        Set policy\n
 *          Check policy in callback\n
 *          compare the value
 */
int utc_webkit2_ewk_cookie_manager_file_scheme_cookies_allow_get_p(void)
{
    Ewk_Cookie_Manager* cookieManager = ewk_context_cookie_manager_get(ewk_view_context_get(test_view.webview));
    ewk_cookie_manager_file_scheme_cookies_allow_set(cookieManager, EINA_TRUE);
    eventLoopWait(3.0);
    Eina_Bool result = ewk_cookie_manager_file_scheme_cookies_allow_get(cookieManager);
    assert_eq(result, EINA_TRUE);

    ewk_cookie_manager_file_scheme_cookies_allow_set(cookieManager, EINA_FALSE);
    eventLoopWait(3.0);
    result = ewk_cookie_manager_file_scheme_cookies_allow_get(cookieManager);
    assert_eq(result, EINA_FALSE);
    return 0;
}

/**
 * @testcase        utc_webkit2_ewk_cookie_manager_file_scheme_cookies_allow_get_n
 * @since_tizen     3.0
 * @description     Get policy for the cookie acceptance for file scheme URLs
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_cookie_manager_file_scheme_cookies_allow_get_n(void)
{
    assert_eq(ewk_cookie_manager_file_scheme_cookies_allow_get(NULL), EINA_FALSE);
    return 0;
}
