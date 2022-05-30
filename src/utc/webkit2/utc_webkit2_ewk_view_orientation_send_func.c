/* Copyright (c) 2014 Samsung Electronics Co., Ltd.

   Licensed under the Apache License, Version 2.0 (the License);
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "utc_webkit2_ewk.h"
#include "assert.h"

/**
 * @function		utc_webkit2_ewk_view_orientation_send_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_orientation_send_func_startup(void)
{
    utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_view_orientation_send_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_orientation_send_func_cleanup(void)
{
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_orientation_send_p
 * @since_tizen		2.3
 * @description		Sends the orientation of the device
 * @scenario        load test html\n
 *					ewk_view_orientation_send	
 */
int utc_webkit2_ewk_view_orientation_send_p(void)
{
    Eina_Bool result = ewk_view_url_set(test_view.webview, "file://ewk_view/orientation_test.html");
    assert_eq(result, EINA_TRUE);
    ewk_view_orientation_send(test_view.webview, 90);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_orientation_send_n
 * @since_tizen		2.3
 * @description		Sends the orientation of the device
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_orientation_send_n(void)
{
    Eina_Bool result = ewk_view_url_set(test_view.webview, "file://ewk_view/orientation_test.html");
    assert_eq(result, EINA_TRUE);
    ewk_view_orientation_send(test_view.webview, 22);
    return 0;
}
