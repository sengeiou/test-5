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
 * @function		utc_webkit2_ewk_view_add_in_incognito_mode_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_add_in_incognito_mode_startup(void)
{
    elm_init(0, NULL);
    ewk_init();
    elm_config_accel_preference_set("opengl");
}

/**
 * @function		utc_webkit2_ewk_view_add_in_incognito_mode_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_view_add_in_incognito_mode_cleanup(void)
{
    /* Closing whole EWK */
    ewk_shutdown();
    elm_shutdown();
}

/**
 * @testcase		utc_webkit2_ewk_view_add_in_incognito_mode_p
 * @since_tizen		3.0
 * @description		Creates a new webkit EFL view object
 * @scenario        Create Webkit View\n
 *					Call ewk_view_add_in_incognito_mode API
 */
int utc_webkit2_ewk_view_add_in_incognito_mode_p(void)
{
    Eina_Bool result = EINA_FALSE;
    Evas_Object* window = elm_win_add(NULL, "TC Launcher", ELM_WIN_BASIC);
    elm_win_title_set(window, "TC Launcher");
    Evas* evas = evas_object_evas_get(window);

    /* Initialization of webview */
    Evas_Object* webview = ewk_view_add_in_incognito_mode(evas);

    if (webview)
        result = EINA_TRUE;

    evas_object_del(webview);
    evas_object_del(window);
    assert_eq(result, EINA_TRUE);
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_view_add_in_incognito_mode_n
 * @since_tizen		3.0
 * @description		Creates a new webkit EFL view object
 * @scenario        Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_view_add_in_incognito_mode_n(void)
{
    Evas_Object* webview = ewk_view_add_in_incognito_mode(NULL);
    assert_eq(webview, NULL);
    return 0;
}
