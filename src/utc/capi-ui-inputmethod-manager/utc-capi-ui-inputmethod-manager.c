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
#include <string.h>
#include <inputmethod_manager.h>

//& set: CapiUi-inputmethod


/**
 * @function		utc_capi_ui_inputmethod_manager_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_ui_inputmethod_manager_startup(void)
{
}

/**
 * @function		utc_capi_ui_inputmethod_manager_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_ui_inputmethod_manager_cleanup(void)
{
}


//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_ime_manager_get_active_ime_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that checks which IME is the current activated (selected) IME.
 */
int utc_ime_manager_get_active_ime_p(void)
{
    char *appid = NULL;
    int ret = ime_manager_get_active_ime(&appid);
    if (appid) {
        printf("ime_manager_get_active_ime: appid=\"%s\"\n", appid);
        free(appid);
    }
    assert_eq(ret, IME_MANAGER_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_manager_is_ime_enabled_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that checks if the specific IME is enabled or disabled in the system keyboard setting.
 */
int utc_ime_manager_is_ime_enabled_p(void)
{
    bool enabled;
    char *appid = NULL;
    int ret;

    ret = ime_manager_get_active_ime(&appid);
    assert_eq(ret, IME_MANAGER_ERROR_NONE);
    assert(appid);
    if (appid) {
        ret = ime_manager_is_ime_enabled(appid, &enabled);
        printf("ime_manager_is_ime_enabled: appid=\"%s\", enabled=%d\n", appid, enabled);
        free(appid);
        assert_eq(ret, IME_MANAGER_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_ime_manager_show_ime_selector_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that requests to open the IME selector menu.
 */
int utc_ime_manager_show_ime_selector_p(void)
{
    int ret = ime_manager_show_ime_selector();
    assert_eq(ret, IME_MANAGER_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_manager_show_ime_list_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that requests to open the installed IME list menu.
 */
int utc_ime_manager_show_ime_list_p(void)
{
    int ret = ime_manager_show_ime_list();
    assert_eq(ret, IME_MANAGER_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_manager_get_enabled_ime_count_p
 * @since_tizen		3.0
 * @description		Positive UTC of the function that requests to gets the number of IMEs which are enabled (usable).
 */
int utc_ime_manager_get_enabled_ime_count_p(void)
{
    int count = ime_manager_get_enabled_ime_count();
    int ret = get_last_result();
    assert_eq(ret, IME_MANAGER_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_manager_prelaunch_ime_p
 * @since_tizen		5.0
 * @description		Positive UTC of the function that requests to pre-launch the IME in On-demand mode.
 */
int utc_ime_manager_prelaunch_ime_p(void)
{
    int ret = ime_manager_prelaunch_ime();
    assert_eq(ret, IME_MANAGER_ERROR_NONE);
    return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_ime_manager_get_active_ime_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that checks which IME is the current activated (selected) IME.
 */
int utc_ime_manager_get_active_ime_n(void)
{
    int ret = ime_manager_get_active_ime(NULL);
    assert_eq(ret, IME_MANAGER_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_manager_is_ime_enabled_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that checks if the specific IME is enabled or disabled in the system keyboard setting.
 */
int utc_ime_manager_is_ime_enabled_n(void)
{
    int ret = ime_manager_is_ime_enabled(NULL, NULL);
    assert_eq(ret, IME_MANAGER_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_manager_is_ime_enabled_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that checks if the specific IME is enabled or disabled in the system keyboard setting.
 */
int utc_ime_manager_is_ime_enabled_n2(void)
{
    const char *appid = "";
    bool enabled;
    int ret = ime_manager_is_ime_enabled(appid, &enabled);
    assert_eq(ret, IME_MANAGER_ERROR_OPERATION_FAILED);
    return 0;
}

/**
 * @testcase		utc_ime_manager_is_ime_enabled_n3
 * @since_tizen		2.4
 * @description		Negative UTC of the function that checks if the specific IME is enabled or disabled in the system keyboard setting.
 */
int utc_ime_manager_is_ime_enabled_n3(void)
{
    char *appid = NULL;
    bool enabled;
    int ret = ime_manager_get_active_ime(&appid);
    assert_eq(ret, IME_MANAGER_ERROR_NONE);
    assert(appid);

    ret = ime_manager_is_ime_enabled(appid, NULL);
    free(appid);
    assert_eq(ret, IME_MANAGER_ERROR_INVALID_PARAMETER);
    return 0;
}