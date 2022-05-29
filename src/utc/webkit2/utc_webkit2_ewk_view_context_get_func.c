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

/* Startup and cleanup functions */
/**
 * @function		utc_webkit2_ewk_view_context_get_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_context_get_func_startup(void)
{
    utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_view_context_get_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_context_get_func_cleanup(void)
{
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_view_context_get_p
 * @since_tizen		2.3
 * @description		Gets Ewk context of the view
 * @scenario 		Call ewk_view_context_get API
 */
int utc_webkit2_ewk_view_context_get_p(void)
{
    Ewk_Context* context = ewk_view_context_get(test_view.webview);
    assert_neq(context, NULL);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_context_get_n
 * @since_tizen		2.3
 * @description		Gets Ewk context of the view
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_context_get_n(void)
{
    Ewk_Context* context = ewk_view_context_get(NULL);
    assert_eq(context, NULL);
    return 0;
}
