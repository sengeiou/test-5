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
#define TEXTCONTENT "This is Plain Text"

/**
 * @function		utc_webkit2_ewk_view_contents_set_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_contents_set_func_startup(void)
{
    utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_view_contents_set_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_contents_set_func_cleanup(void)
{
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_contents_set_p
 * @since_tizen		2.3
 * @description		Requests loading the given content on the view object
 * @scenario        Create Webkit View\n
 *                  Call the target API
 */
int utc_webkit2_ewk_view_contents_set_p(void)
{
    Eina_Bool results = ewk_view_contents_set(test_view.webview, TEXTCONTENT, 20, 0, 0, 0);
    assert_eq(results, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_contents_set_n
 * @since_tizen		2.3
 * @description		Requests loading the given content on the view object
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_contents_set_n(void)
{
    assert_eq(ewk_view_contents_set(NULL, TEXTCONTENT, 0, 0, 0, 0), EINA_FALSE);
    return 0;
}
