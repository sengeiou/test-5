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
 * @function		utc_webkit2_ewk_autofill_profile_new_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_autofill_profile_new_func_startup(void)
{
    utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_autofill_profile_new_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_autofill_profile_new_func_cleanup(void)
{
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_autofill_profile_new_func_p
 * @since_tizen		2.4
 * @description		To Create autofill profile
 * @scenario		ewk_autofill_profile_new
 */
int utc_webkit2_ewk_autofill_profile_new_p(void)
{
    Ewk_Autofill_Profile* profile = ewk_autofill_profile_new();
    assert_neq(profile, NULL);
    return 0;
}

/* Requset form WEB DEV team, Delete API Test.
Delete : utc_webkit2_ewk_autofill_profile_new_func_n */
