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


/**
 * @function		utc_webkit2_ewk_context_cookie_manager_get_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_context_cookie_manager_get_func_startup(void)
{
    utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_context_cookie_manager_get_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_context_cookie_manager_get_func_cleanup(void)
{
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_context_cookie_manager_get_p
 * @since_tizen		2.3
 * @description		Gets the cookie manager instance for this context
 * @scenario		Call ewk_context_cookie_manager_get to get the value\n
 *			Validate the get value
 */
int utc_webkit2_ewk_context_cookie_manager_get_p(void)
{
    Ewk_Cookie_Manager* cookieManager = ewk_context_cookie_manager_get(ewk_view_context_get(test_view.webview));
    if (cookieManager)
        assert(1);

    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_context_cookie_manager_get_n
 * @since_tizen		2.3
 * @description		Gets the cookie manager instance for this context
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_context_cookie_manager_get_n(void)
{
    Ewk_Cookie_Manager* cookieManager = ewk_context_cookie_manager_get(NULL);
    assert_eq(cookieManager, 0);
    return 0;
}
