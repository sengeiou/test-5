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
#include <stdlib.h>
#include <string.h>

#include <system_info.h>

#include <shortcut_manager.h>

//& set: Shortcut

#define SHORTCUT_FEATURE "http://tizen.org/feature/shortcut"
static bool is_supported = false;

void utc_shortcut_startup(void)
{
	is_supported = false;
	system_info_get_platform_bool(SHORTCUT_FEATURE, &is_supported);
}

static int response_cb(int ret, void *data)
{
    return 0;
}

/**
 * @testcase		utc_shortcut_add_to_home_n
 * @since_tizen		2.3
 * @description		Negative test case of shortcut_add_to_home()
 */
int utc_shortcut_add_to_home_n(void)
{
    int ret;

    ret = shortcut_add_to_home(NULL, -1, NULL, NULL, 1, NULL, NULL);
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_shortcut_add_to_home_p
 * @since_tizen		2.3
 * @description		Positive test case of shortcut_add_to_home()
 */
int utc_shortcut_add_to_home_p(void)
{
    int ret;

    ret = shortcut_add_to_home(NULL, LAUNCH_BY_APP, NULL, NULL, 0, response_cb, NULL);
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_shortcut_add_to_home_widget_n
 * @since_tizen		2.3
 * @description		Negative test case of shortcut_add_to_home_widget()
 */
int utc_shortcut_add_to_home_widget_n(void)
{
    int ret;

    ret = shortcut_add_to_home_widget(NULL, -1, NULL, NULL, -1.0f, 0, response_cb, NULL);
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_shortcut_add_to_home_widget_p
 * @since_tizen		2.4
 * @description		Positive test case of shortcut_add_to_home_widget()
 */
int utc_shortcut_add_to_home_widget_p(void)
{
    int ret;

    ret = shortcut_add_to_home_widget("org.tizen.message", WIDGET_SIZE_1x1, NULL, NULL, -1.0f, 0, response_cb, NULL);
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_shortcut_remove_from_home_n
 * @since_tizen		3.0
 * @description		Negative test case of shortcut_remove_from_home()
 */
int utc_shortcut_remove_from_home_n(void)
{
    int ret;

    ret = shortcut_remove_from_home(NULL, response_cb, NULL);
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_shortcut_remove_from_home_p
 * @since_tizen		3.0
 * @description		Positive test case of shortcut_remove_from_home()
 */
int utc_shortcut_remove_from_home_p(void)
{
    int ret;

    ret = shortcut_remove_from_home("", response_cb, NULL);
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_NONE);

    return 0;
}

int _request_cb(const char *package_name, const char *name, int type, const char *content_info, const char *icon, int pid, double period, int allow_duplicate, void *data)
{
	fprintf(stderr, "_request_cb");
	return SHORTCUT_ERROR_NONE;
}

int _remove_cb(const char *package_name, const char *name, int sender_pid, void *user_data)
{
	fprintf(stderr, "_remove_cb");
	return SHORTCUT_ERROR_NONE;
}

/**
 * @testcase		utc_shortcut_set_request_cb_n
 * @since_tizen		2.3
 * @description		Negative test case of shortcut_set_request_cb()
 */
int utc_shortcut_set_request_cb_n(void)
{
    int ret;

    ret = shortcut_set_request_cb(NULL, "temp");
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_shortcut_set_request_cb_p
 * @since_tizen		2.3
 * @description		Positive test case of shortcut_set_request_cb()
 */
int utc_shortcut_set_request_cb_p(void)
{
    int ret;

    ret = shortcut_set_request_cb(_request_cb, "temp");
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_shortcut_set_remove_cb_n
 * @since_tizen		3.0
 * @description		Negative test case of shortcut_set_remove_cb()
 */
int utc_shortcut_set_remove_cb_n(void)
{
    int ret;

    ret = shortcut_set_remove_cb(NULL, "temp");
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_shortcut_set_remove_cb_p
 * @since_tizen		3.0
 * @description		Positive test case of shortcut_set_remove_cb()
 */
int utc_shortcut_set_remove_cb_p(void)
{
    int ret;

    ret = shortcut_set_remove_cb(_remove_cb, "temp");
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_shortcut_unset_request_cb_n
 * @since_tizen		3.0
 * @description		Negative test case of shortcut_unset_request_cb()
 */
int utc_shortcut_unset_request_cb_n(void)
{
    int ret;

    ret = shortcut_set_request_cb(NULL, "temp");
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_INVALID_PARAMETER);

    shortcut_unset_request_cb();
    if (!is_supported)
        assert_eq(get_last_result(), SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(get_last_result(), SHORTCUT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_shortcut_unset_request_cb_p
 * @since_tizen		3.0
 * @description		Positive test case of shortcut_unset_request_cb()
 */
int utc_shortcut_unset_request_cb_p(void)
{
    int ret;

    ret = shortcut_set_request_cb(_request_cb, "temp");
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_NONE);

    shortcut_unset_request_cb();
    if (!is_supported)
        assert_eq(get_last_result(), SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(get_last_result(), SHORTCUT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_shortcut_unset_remove_cb_n
 * @since_tizen		3.0
 * @description		Negative test case of shortcut_unset_remove_cb()
 */
int utc_shortcut_unset_remove_cb_n(void)
{
    int ret;

    ret = shortcut_set_remove_cb(NULL, "temp");
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_INVALID_PARAMETER);

    shortcut_unset_remove_cb();
    if (!is_supported)
        assert_eq(get_last_result(), SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(get_last_result(), SHORTCUT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_shortcut_unset_remove_cb_p
 * @since_tizen		3.0
 * @description		Positive test case of shortcut_unset_remove_cb()
 */
int utc_shortcut_unset_remove_cb_p(void)
{
    int ret;

    ret = shortcut_set_remove_cb(_remove_cb, "temp");
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_NONE);

    shortcut_unset_remove_cb();
    if (!is_supported)
        assert_eq(get_last_result(), SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(get_last_result(), SHORTCUT_ERROR_NONE);
    return 0;
}

int list_cb(const char *package_name, const char *icon, const char *name, const char *extra_key, const char *extra_data, void *user_data)
{
	return SHORTCUT_ERROR_NONE;
}

/**
 * @testcase		utc_shortcut_get_list_n
 * @since_tizen		2.3
 * @description		Negative test case of shortcut_get_list()
 */
int utc_shortcut_get_list_n(void)
{
    int ret;

    ret = shortcut_get_list(NULL, NULL, NULL);
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_shortcut_get_list_p
 * @since_tizen		2.3
 * @description		Positive test case of shortcut_get_list()
 */
int utc_shortcut_get_list_p(void)
{
    int ret;

    ret = shortcut_get_list("org.tizen.message", list_cb, NULL);
    if (!is_supported)
        assert_eq(ret, SHORTCUT_ERROR_NOT_SUPPORTED);
    else
        assert_eq(ret, SHORTCUT_ERROR_NONE);

    return 0;
}
