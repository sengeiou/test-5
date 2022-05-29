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

/**
 * @function		utc_webkit2_ewk_settings_auto_fitting_get_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_webkit2_ewk_settings_auto_fitting_get_func_startup(void)
{
    utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_settings_auto_fitting_get_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_webkit2_ewk_settings_auto_fitting_get_func_cleanup(void)
{
     utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_settings_auto_fitting_get_p
 * @since_tizen		2.3
 * @description 	Returns the auto-fit status
 * @scenario		Set Value\n
 *			Retrieve value\n
 *			Validate the set and get values
 */
int utc_webkit2_ewk_settings_auto_fitting_get_p(void)
{
     Ewk_Settings* settings = ewk_view_settings_get(test_view.webview);
     ewk_settings_auto_fitting_set(settings, EINA_TRUE);
     assert_eq(ewk_settings_auto_fitting_get(settings), EINA_TRUE);
     return 0;
}

/**
 * @testcase		utc_webkit2_ewk_settings_auto_fitting_get_p1
 * @since_tizen		2.3
 * @description 	Returns the auto-fit status
 * @scenario		Set Value\n
 *			Retrieve value\n
 *			Validate the set and get values
 */
int utc_webkit2_ewk_settings_auto_fitting_get_p1(void)
{
     Ewk_Settings* settings = ewk_view_settings_get(test_view.webview);
     ewk_settings_auto_fitting_set(settings, EINA_FALSE);
     assert_eq(ewk_settings_auto_fitting_get(settings), EINA_FALSE);
     return 0;
}

/**
 * @testcase		utc_webkit2_ewk_settings_auto_fitting_get_n
 * @since_tizen		2.3
 * @description		Returns the auto-fit status
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_settings_auto_fitting_get_n(void)
{
    assert_eq(ewk_settings_auto_fitting_get(NULL), EINA_FALSE);
    return 0;
}
