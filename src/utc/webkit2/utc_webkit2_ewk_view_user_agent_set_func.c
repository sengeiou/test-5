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

#ifndef NULL
#define NULL    0x0
#endif

#define USER_AGENT_STRING "Mozilla/5.0 (Unknown; Linux armv7l **TEST*TEST**) AppleWebKit/534.16+ (KHTML, like Gecko) Version/5.0 Safari/534.16+"
#define TEST_STRING "**TEST*TEST**"
#define TEST_NULL_WEBVIEW "Test NULL WebView"

/**
 * @function		utc_webkit2_ewk_view_user_agent_set_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_user_agent_set_func_startup(void)
{
    utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_view_user_agent_set_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_user_agent_set_func_cleanup(void)
{
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_user_agent_set_p
 * @since_tizen		2.3
 * @description		Set the user agent of the page	
 * @scenario		Create Webkit View\n
 *                  Set Value\n
 *                  Retrieve value\n
 *                  Validate the set and get values
 */
int utc_webkit2_ewk_view_user_agent_set_p(void)
{
    Eina_Bool result = EINA_TRUE;

    ewk_view_user_agent_set(test_view.webview, USER_AGENT_STRING);
    const char* userAgent = ewk_view_user_agent_get(test_view.webview);
    char* strString = strstr(userAgent, TEST_STRING);

    if (strncmp(strString, TEST_STRING, strlen(TEST_STRING)))
        result = EINA_FALSE;

    assert_eq(result, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_user_agent_set_n
 * @since_tizen		2.3
 * @description		Set the user agent of the page
 * @scenario		Check operation entered incorrect parameter	
 */
int utc_webkit2_ewk_view_user_agent_set_n(void)
{
    Eina_Bool result = EINA_TRUE;
    ewk_view_user_agent_set(test_view.webview, "");
    const char* userAgent = ewk_view_user_agent_get(test_view.webview);
    if (!userAgent)
        result = EINA_FALSE;

    assert_eq(result, EINA_TRUE);
    return 0;
}
