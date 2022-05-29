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

static Eina_Bool result = EINA_FALSE;

/**
 * @function		utc_webkit2_ewk_autofill_profile_data_get_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_autofill_profile_data_get_func_startup(void)
{
    utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_autofill_profile_data_get_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_autofill_profile_data_get_func_cleanup(void)
{
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_autofill_profile_data_get_p
 * @since_tizen		2.4
 * @description		To Get autofill profile data
 * @scenario		ewk_autofill_profile_new\n
 *			ewk_autofill_profile_data_set\n
 * 			ewk_autofill_profile_data_get\n
 *			ewk_autofill_profile_delete
 */
int utc_webkit2_ewk_autofill_profile_data_get_p(void)
{
    Ewk_Autofill_Profile* Profile = ewk_autofill_profile_new();
    assert_neq(Profile, NULL);

    ewk_autofill_profile_data_set(Profile, EWK_PROFILE_NAME, "MyProfile");
    const char* TEST_PROFILE_NAME = ewk_autofill_profile_data_get(Profile, EWK_PROFILE_NAME);

    if (!strcmp(TEST_PROFILE_NAME, "MyProfile"))
        result = EINA_TRUE;

    assert_eq(result, EINA_TRUE);

    ewk_autofill_profile_delete(Profile);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_autofill_profile_data_get_n
 * @since_tizen		2.4
 * @description		To Get autofill profile data
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_autofill_profile_data_get_n(void)
{
    Ewk_Autofill_Profile* Profile = ewk_autofill_profile_new();
    assert_neq(Profile, NULL);

    ewk_autofill_profile_data_set(Profile, EWK_PROFILE_NAME, NULL);
    const char* TEST_PROFILE_NAME = ewk_autofill_profile_data_get(Profile, EWK_PROFILE_NAME);

    if (!TEST_PROFILE_NAME)
        result = EINA_TRUE;

    assert_eq(result, EINA_TRUE);

    ewk_autofill_profile_delete(Profile);
    return 0;
}
