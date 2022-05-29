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

#define SET_DEFAULT_ENCODING "utf-8"

/* Startup and cleanup functions */
/**
 * @function		utc_webkit2_ewk_settings_default_text_encoding_name_get_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_settings_default_text_encoding_name_get_func_startup(void)
{
    utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_settings_default_text_encoding_name_get_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_settings_default_text_encoding_name_get_func_cleanup(void)
{
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_settings_default_text_encoding_name_get_p
 * @since_tizen		2.3
 * @description 		Gets default text encoding name
 * @scenario			Set Value\n
 *					Retrieve value\n
 *					Validate the set and get values
 */
int utc_webkit2_ewk_settings_default_text_encoding_name_get_p(void)
{
    Ewk_Settings* settings = ewk_view_settings_get(test_view.webview);
    const char* defaultEncoding = NULL;
    defaultEncoding = ewk_settings_default_text_encoding_name_get(settings);
    assert_neq(defaultEncoding, NULL);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_settings_default_text_encoding_name_get_p1
 * @since_tizen		2.3
 * @description 		Gets default text encoding name
 * @scenario			Set Value\n
 *					Retrieve value\n
 *					Validate the set and get values
 */
int utc_webkit2_ewk_settings_default_text_encoding_name_get_p1(void)
{
    Ewk_Settings* settings = ewk_view_settings_get(test_view.webview);
    Eina_Bool result = ewk_settings_default_text_encoding_name_set(settings, SET_DEFAULT_ENCODING);
    assert_eq(result,EINA_TRUE);

    const char* defaultEncoding = ewk_settings_default_text_encoding_name_get(settings);
    assert_neq(defaultEncoding, 0);

    Eina_Bool hasDefaultEncodingString = EINA_FALSE;
    if (strcmp(defaultEncoding, SET_DEFAULT_ENCODING))
       hasDefaultEncodingString = EINA_TRUE;
    assert_eq(hasDefaultEncodingString , EINA_FALSE);

    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_settings_default_text_encoding_name_get_n
 * @since_tizen		2.3
 * @description		Gets default text encoding name
 * @scenario			Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_settings_default_text_encoding_name_get_n(void)
{
    const char* defaultEncoding = NULL;
    defaultEncoding = ewk_settings_default_text_encoding_name_get(NULL);
    assert_eq(defaultEncoding, NULL);
    return 0;
}
