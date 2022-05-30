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
#include "ewk_settings.h"

#define SET_DEFAULT_ENCODING "utf-8"

/* Startup and cleanup functions */
/**
 * @function		utc_webkit2_ewk_settings_default_text_encoding_name_set_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_settings_default_text_encoding_name_set_func_startup(void)
{
    utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_settings_default_text_encoding_name_set_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_settings_default_text_encoding_name_set_func_cleanup(void)
{
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_settings_default_text_encoding_name_set_p
 * @since_tizen		2.3
 * @description 		Sets default text encoding name
 * @scenario			Set Value\n
 *					Retrieve value\n
 *					Validate the set and get values
 */
int utc_webkit2_ewk_settings_default_text_encoding_name_set_p(void)
{
    Ewk_Settings* settings = ewk_view_settings_get(test_view.webview);
    Eina_Bool result = ewk_settings_default_text_encoding_name_set(settings, SET_DEFAULT_ENCODING);
    assert_eq(result, EINA_TRUE);

    const char* defaultEncoding = NULL;
    defaultEncoding = ewk_settings_default_text_encoding_name_get(settings);
    Eina_Bool hasDefaultEncodingString = EINA_FALSE;
    if (strcmp(defaultEncoding, SET_DEFAULT_ENCODING))
        hasDefaultEncodingString = EINA_TRUE;
    assert_eq(hasDefaultEncodingString , EINA_FALSE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_settings_default_text_encoding_name_set_n
 * @since_tizen		2.3
 * @description		Sets default text encoding name
 * @scenario			Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_settings_default_text_encoding_name_set_n(void)
{
    Eina_Bool result = ewk_settings_default_text_encoding_name_set(NULL, SET_DEFAULT_ENCODING);
    assert_eq(result, EINA_FALSE);

    Ewk_Settings* settings = ewk_view_settings_get(test_view.webview);
    result = ewk_settings_default_text_encoding_name_set(settings, NULL);
    assert_eq(result, EINA_FALSE);
    return 0;
}
