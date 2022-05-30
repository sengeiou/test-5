/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * */

#include <stdio.h>
#include "assert.h"
#include "utc_webkit2_ewk.h"
#include "tct-autofill-profile.h"

/* Startup and cleanup functions */
/**
 * @function		utc_webkit2_ewk_context_form_autofill_profile_get_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_context_form_autofill_profile_get_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    system("rm /usr/apps/core-webkit2-tests/data/.webkit/formDatabase/WebpageForms.db");
}

/**
 * @function		utc_webkit2_ewk_context_form_autofill_profile_get_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_context_form_autofill_profile_get_func_cleanup(void)
{
    system("rm /usr/apps/core-webkit2-tests/data/.webkit/formDatabase/WebpageForms.db");
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_context_form_autofill_profile_get_p
 * @since_tizen		2.4
 * @description		Gets the existing profile for given index
 * @scenario		ewk_view_settings_get\n
 *			ewk_settings_form_profile_data_enabled_set\n
 *			ewk_context_form_autofill_profile_get\n
 *			ewk_autofill_profile_delete
 */
int utc_webkit2_ewk_context_form_autofill_profile_get_p(void)
{
    Ewk_Settings* settings = ewk_view_settings_get(test_view.webview);
    Eina_Bool result = ewk_settings_form_profile_data_enabled_set(settings, EINA_TRUE);
    assert_neq(result, EINA_FALSE);

    Ewk_Autofill_Profile* profile1 = getTestEwkAutofillProfile();
    Ewk_Autofill_Profile* profile2 = ewk_context_form_autofill_profile_get(ewk_view_context_get(test_view.webview), TEST_AUTOFILL_PROFILE_ID);
    assert_neq(profile1, profile2);
    ewk_autofill_profile_delete(profile1);
    ewk_autofill_profile_delete(profile2);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_context_form_autofill_profile_get_n
 * @since_tizen		2.4
 * @description		Gets the existing profile for given index
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_context_form_autofill_profile_get_n(void)
{
    Ewk_Autofill_Profile* profile1 = getTestEwkAutofillProfile();
    Ewk_Autofill_Profile* profile2 = ewk_context_form_autofill_profile_get(NULL, TEST_AUTOFILL_PROFILE_ID);
    assert_neq(profile1, profile2);
    ewk_autofill_profile_delete(profile1);
    return 0;
}
