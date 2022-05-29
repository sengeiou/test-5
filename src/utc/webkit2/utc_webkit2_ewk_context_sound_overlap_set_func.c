//
// Copyright (c) 2017 Samsung Electronics Co., Ltd.
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

/* Startup and cleanup functions */
/**
 * @function		utc_webkit2_ewk_context_sound_overlap_set_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_webkit2_ewk_context_sound_overlap_set_func_startup(void)
{
    utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_context_sound_overlap_set_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_webkit2_ewk_context_sound_overlap_set_func_cleanup(void)
{
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_context_sound_overlap_set_p
 * @since_tizen		2.3
 * @description		Checking whether cache model is set to EINA_TRUE.
 * @scenario		Call ewk_context_sound_overlap_set to set\n
 *			Call ewk_context_sound_overlap_get to get the value\n
 *			Validate the get value
 */
int utc_webkit2_ewk_context_sound_overlap_set_p(void)
{
    Eina_Bool result = ewk_context_sound_overlap_set(ewk_view_context_get(test_view.webview), EINA_TRUE);
    assert_eq(result, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_context_sound_overlap_set_p1
 * @since_tizen		2.3
 * @description		Checking whether cache model is set to EINA_FALSE.
 * @scenario		Call ewk_context_sound_overlap_set to set\n
 *			Call ewk_context_sound_overlap_get to get the value\n
 *			Validate the get value
 */
int utc_webkit2_ewk_context_sound_overlap_set_p1(void)
{
    Eina_Bool result = ewk_context_sound_overlap_set(ewk_view_context_get(test_view.webview), EINA_FALSE);
    assert_eq(result, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_context_sound_overlap_set_n
 * @since_tizen		2.3
 * @description		Checking whether function works properly in case of NULL of a context.
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_context_sound_overlap_set_n(void)
{
    Eina_Bool result = ewk_context_sound_overlap_set(NULL, EINA_TRUE);
    assert_eq(result, EINA_FALSE);

    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_context_sound_overlap_set_n1
 * @since_tizen		2.3
 * @description		Checking whether function works properly in case of NULL of a context.
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_context_sound_overlap_set_n1(void)
{
    Eina_Bool result = ewk_context_sound_overlap_set(NULL, EINA_FALSE);
    assert_eq(result, EINA_FALSE);
    return 0;
}
