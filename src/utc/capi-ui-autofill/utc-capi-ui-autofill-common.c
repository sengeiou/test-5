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
#include <autofill_common.h>

//& set: CapiUi-autofill-common

static bool view_info_item_cb_result = false;
static bool save_view_info_item_cb_result = false;

static bool fill_response_group_cb_result = false;
static bool fill_response_item_cb_result = false;

static bool __view_info_item_cb(autofill_item_h item, void *user_data)
{
    view_info_item_cb_result = true;
    return true;
}

static bool fill_response_group_cb(autofill_fill_response_group_h group_h, void *user_data)
{
    fill_response_group_cb_result = true;
    return true;
}

static bool __save_view_info_item_cb(autofill_save_item_h item, void *user_data)
{
    save_view_info_item_cb_result = true;
    return true;
}

static bool fill_response_item_cb(autofill_fill_response_item_h item, void *user_data)
{
    fill_response_item_cb_result = true;
    return true;
}

/**
 * @function        utc_capi_ui_autofill_common_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_ui_autofill_common_startup(void)
{
}

/**
 * @function        utc_capi_ui_autofill_common_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_ui_autofill_common_cleanup(void)
{
}

/**
 * @testcase        utc_autofill_item_create_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that creates autofill item.
 */
int utc_autofill_item_create_p(void)
{
    autofill_item_h it_h;
    int ret = autofill_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);
    return 0;
}

/**
 * @testcase        utc_autofill_item_create_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that creates autofill item.
 */
int utc_autofill_item_create_n(void)
{
    int ret = autofill_item_create(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_item_destroy_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that destroys autofill item.
 */
int utc_autofill_item_destroy_p(void)
{
    autofill_item_h it_h = NULL;
    int ret = autofill_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_item_set_id(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_item_set_label(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_item_set_value(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_item_destroy(it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_item_destroy_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that destroys autofill item.
 */
int utc_autofill_item_destroy_n(void)
{
    int ret = autofill_item_destroy(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_item_clone_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that clones autofill item.
 */
int utc_autofill_item_clone_p(void)
{
    autofill_item_h it_h = NULL, clone_h;
    int ret = autofill_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_item_set_id(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_item_set_label(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_item_set_value(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_item_clone(it_h, &clone_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    autofill_item_destroy(it_h);
    autofill_item_destroy(clone_h);

    return 0;
}

/**
 * @testcase        utc_autofill_item_clone_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that clones autofill item.
 */
int utc_autofill_item_clone_n(void)
{
    int ret = autofill_item_clone(NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_item_set_autofill_hint_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets autofill hint in an autofill item.
 */
int utc_autofill_item_set_autofill_hint_p(void)
{
    autofill_item_h it_h = NULL;
    int ret = autofill_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_item_set_autofill_hint(it_h, AUTOFILL_HINT_NAME);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_item_set_autofill_hint_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets autofill hint in an autofill item.
 */
int utc_autofill_item_set_autofill_hint_n(void)
{
    int ret = autofill_item_set_autofill_hint(NULL, AUTOFILL_HINT_NAME);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_item_get_autofill_hint_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets autofill hint in an autofill item.
 */
int utc_autofill_item_get_autofill_hint_p(void)
{
    autofill_item_h it_h = NULL;
    autofill_hint_e autofill_hint;
    int ret = autofill_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_item_get_autofill_hint(it_h, &autofill_hint);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_item_get_autofill_hint_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets autofill hint in an autofill item.
 */
int utc_autofill_item_get_autofill_hint_n(void)
{
    autofill_hint_e autofill_hint;
    int ret = autofill_item_get_autofill_hint(NULL, &autofill_hint);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_item_set_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets autofill id in an autofill item.
 */
int utc_autofill_item_set_id_p(void)
{
    autofill_item_h it_h = NULL;
    int ret = autofill_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_item_set_id(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_item_set_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets autofill id in an autofill item.
 */
int utc_autofill_item_set_id_n(void)
{
    int ret = autofill_item_set_id(NULL, "test");
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_item_get_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets autofill id in an autofill item.
 */
int utc_autofill_item_get_id_p(void)
{
    autofill_item_h it_h = NULL;
    char *id = NULL;
    int ret = autofill_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_item_set_id(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_item_get_id(it_h, &id);

    autofill_item_destroy(it_h);

    assert(id);

    if (id)
        free(id);

    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_item_get_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets autofill id in an autofill item.
 */
int utc_autofill_item_get_id_n(void)
{
    char *id = NULL;
    int ret = autofill_item_get_id(NULL, &id);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_item_set_label_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets autofill label in an autofill item.
 */
int utc_autofill_item_set_label_p(void)
{
    autofill_item_h it_h = NULL;
    int ret = autofill_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_item_set_label(it_h, "test");

    autofill_item_destroy(it_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_item_set_label_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets autofill label in an autofill item.
 */
int utc_autofill_item_set_label_n(void)
{
    int ret = autofill_item_set_label(NULL, "test");
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_item_get_label_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets autofill label in an autofill item.
 */
int utc_autofill_item_get_label_p(void)
{
    autofill_item_h it_h = NULL;
    char *label = NULL;
    int ret = autofill_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_item_set_label(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_item_get_label(it_h, &label);

    autofill_item_destroy(it_h);

    assert(label);

    if (label)
        free(label);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_item_get_label_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets autofill label in an autofill item.
 */
int utc_autofill_item_get_label_n(void)
{
    char *label = NULL;
    int ret = autofill_item_get_label(NULL, &label);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_item_set_sensitive_data_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets whether sensitive data or not in an autofill item.
 */
int utc_autofill_item_set_sensitive_data_p(void)
{
    autofill_item_h it_h = NULL;
    int ret = autofill_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_item_set_sensitive_data(it_h, true);

    autofill_item_destroy(it_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_item_set_sensitive_data_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets whether sensitive data or not in an autofill item.
 */
int utc_autofill_item_set_sensitive_data_n(void)
{
    int ret = autofill_item_set_sensitive_data(NULL, true);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_item_get_sensitive_data_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets whether sensitive data or not in an autofill item.
 */
int utc_autofill_item_get_sensitive_data_p(void)
{
    autofill_item_h it_h = NULL;
    bool sensitive_data;
    int ret = autofill_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_item_get_sensitive_data(it_h, &sensitive_data);

    autofill_item_destroy(it_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_item_get_sensitive_data_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets whether sensitive data or not in an autofill item.
 */
int utc_autofill_item_get_sensitive_data_n(void)
{
    bool sensitive_data;
    int ret = autofill_item_get_sensitive_data(NULL, &sensitive_data);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_item_set_value_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets autofill value in an autofill item.
 */
int utc_autofill_item_set_value_p(void)
{
    autofill_item_h it_h = NULL;
    int ret = autofill_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_item_set_value(it_h, "test");
    autofill_item_destroy(it_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_item_set_value_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets autofill value in an autofill item.
 */
int utc_autofill_item_set_value_n(void)
{
    int ret = autofill_item_set_value(NULL, "test");
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_item_get_value_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets autofill value in an autofill item.
 */
int utc_autofill_item_get_value_p(void)
{
    autofill_item_h it_h = NULL;
    char *value = NULL;
    int ret = autofill_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_item_set_value(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_item_get_value(it_h, &value);

    if (value)
        free(value);

    autofill_item_destroy(it_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_item_get_value_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets autofill value in an autofill item.
 */
int utc_autofill_item_get_value_n(void)
{
    char *value = NULL;
    int ret = autofill_item_get_value(NULL, &value);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_view_info_create_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that creates autofill view information.
 */
int utc_autofill_view_info_create_p(void)
{
    autofill_view_info_h vi_h;
    int ret = autofill_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    autofill_view_info_destroy(vi_h);

    return 0;
}

/**
 * @testcase        utc_autofill_view_info_create_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that creates autofill view information.
 */
int utc_autofill_view_info_create_n(void)
{
    int ret = autofill_view_info_create(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_view_info_destroy_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that destroys autofill view information.
 */
int utc_autofill_view_info_destroy_p(void)
{
    autofill_view_info_h vi_h;
    int ret = autofill_view_info_create(&vi_h);
    assert(vi_h);

    ret = autofill_view_info_destroy(vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_view_info_destroy_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that destroys autofill view information.
 */
int utc_autofill_view_info_destroy_n(void)
{
    int ret = autofill_view_info_destroy(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_view_info_set_app_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets app id in autofill view information.
 */
int utc_autofill_view_info_set_app_id_p(void)
{
    autofill_view_info_h vi_h;
    int ret = autofill_view_info_create(&vi_h);
    assert(vi_h);

    ret = autofill_view_info_set_app_id(vi_h, "org.tizen.example");
    autofill_view_info_destroy(vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_view_info_set_app_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets app id in autofill view information.
 */
int utc_autofill_view_info_set_app_id_n(void)
{
    autofill_view_info_h vi_h;
    int ret = autofill_view_info_create(&vi_h);
    assert(vi_h);

    ret = autofill_view_info_set_app_id(vi_h, NULL);
    autofill_view_info_destroy(vi_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_view_info_get_app_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets app id in autofill view information.
 */
int utc_autofill_view_info_get_app_id_p(void)
{
    autofill_view_info_h vi_h;
    char *app_id = NULL;
    int ret = autofill_view_info_create(&vi_h);
    assert(vi_h);

    ret = autofill_view_info_set_app_id(vi_h, "org.tizen.example");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_view_info_get_app_id(vi_h, &app_id);
    assert(app_id);

    free(app_id);

    autofill_view_info_destroy(vi_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_view_info_get_app_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets app id in autofill view information.
 */
int utc_autofill_view_info_get_app_id_n(void)
{
    autofill_view_info_h vi_h;
    int ret = autofill_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_view_info_set_app_id(vi_h, "org.tizen.example");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_view_info_get_app_id(vi_h, NULL);
    autofill_view_info_destroy(vi_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_view_info_set_view_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets view id in autofill view information.
 */
int utc_autofill_view_info_set_view_id_p(void)
{
    autofill_view_info_h vi_h;
    int ret = autofill_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_view_info_set_view_id(vi_h, "login");
    autofill_view_info_destroy(vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_view_info_set_view_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets view id in autofill view information.
 */
int utc_autofill_view_info_set_view_id_n(void)
{
    autofill_view_info_h vi_h;
    int ret = autofill_view_info_create(&vi_h);
    assert(vi_h);

    ret = autofill_view_info_set_view_id(vi_h, NULL);
    autofill_view_info_destroy(vi_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_view_info_get_view_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets view id in autofill view information.
 */
int utc_autofill_view_info_get_view_id_p(void)
{
    autofill_view_info_h vi_h;
    char *view_id = NULL;
    int ret = autofill_view_info_create(&vi_h);
    assert(vi_h);

    ret = autofill_view_info_set_view_id(vi_h, "login");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_view_info_get_view_id(vi_h, &view_id);

    assert(view_id);

    free(view_id);

    autofill_view_info_destroy(vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_view_info_get_view_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets view id in autofill view information.
 */
int utc_autofill_view_info_get_view_id_n(void)
{
    autofill_view_info_h vi_h;
    int ret = autofill_view_info_create(&vi_h);
    assert(vi_h);

    ret = autofill_view_info_set_view_id(vi_h, "login");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_view_info_get_view_id(vi_h, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_view_info_add_item_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that adds autofill item
 */
int utc_autofill_view_info_add_item_p(void)
{
    autofill_item_h ai_h;
    autofill_view_info_h vi_h;
    int ret = autofill_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_item_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_view_info_add_item(vi_h, ai_h);

    autofill_view_info_destroy(vi_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_view_info_add_item_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that adds autofill item
 */
int utc_autofill_view_info_add_item_n(void)
{
    autofill_view_info_h vi_h;
    int ret = autofill_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_view_info_add_item(vi_h, NULL);
    autofill_view_info_destroy(vi_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_view_info_foreach_item_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieve autofill item in autofill view information.
 */
int utc_autofill_view_info_foreach_item_p(void)
{
    autofill_view_info_h vi_h;
    autofill_item_h it_h;

    view_info_item_cb_result = false;

    int ret = autofill_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    autofill_item_create(&it_h);
    autofill_item_set_autofill_hint(it_h, AUTOFILL_HINT_NAME);
    autofill_item_set_id(it_h, "name");
    autofill_item_set_label(it_h, "Myname");
    autofill_item_set_sensitive_data(it_h, true);

    autofill_view_info_add_item(vi_h, it_h);

    ret = autofill_view_info_foreach_item(vi_h, __view_info_item_cb, NULL);
    autofill_view_info_destroy(vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    assert_eq(view_info_item_cb_result, true);

    return 0;
}

/**
 * @testcase        utc_autofill_view_info_foreach_item_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieve autofill item in autofill view information.
 */
int utc_autofill_view_info_foreach_item_n(void)
{
    autofill_view_info_h vi_h;
    int ret = autofill_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_view_info_foreach_item(vi_h, NULL, NULL);
    autofill_view_info_destroy(vi_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

//auth info
/**
 * @testcase        utc_autofill_auth_info_create_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that creates autofill authentication information.
 */
int utc_autofill_auth_info_create_p(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_create_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that creates autofill authentication information.
 */
//& purpose: A purpose of a autofill_auth_info_create() negative TC.
int utc_autofill_auth_info_create_n(void)
{
    int ret = autofill_auth_info_create(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_destroy_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that destroys autofill authentication information.
 */
int utc_autofill_auth_info_destroy_p(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_destroy_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that destroys autofill authentication information.
 */
int utc_autofill_auth_info_destroy_n(void)
{
    int ret = autofill_auth_info_destroy(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_app_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets app id in autofill authentication information.
 */
int utc_autofill_auth_info_set_app_id_p(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_app_id(ai_h, "org.tizen.example");
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_app_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets app id in autofill authentication information.
 */
int utc_autofill_auth_info_set_app_id_n(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_app_id(ai_h, NULL);
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_app_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets app id in autofill authentication information.
 */
int utc_autofill_auth_info_get_app_id_p(void)
{
    autofill_auth_info_h ai_h;
    char *app_id = NULL;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_app_id(ai_h, "org.tizen.example");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_app_id(ai_h, &app_id);
    assert(app_id);

    free(app_id);

    autofill_auth_info_destroy(ai_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_app_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets app id in autofill authentication information.
 */
int utc_autofill_auth_info_get_app_id_n(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_app_id(ai_h, "org.tizen.example");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_app_id(ai_h, NULL);
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_view_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets view id in autofill authentication information.
 */
int utc_autofill_auth_info_set_view_id_p(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_view_id(ai_h, "login");
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_view_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets view id in autofill authentication information.
 */
int utc_autofill_auth_info_set_view_id_n(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_view_id(ai_h, NULL);
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_view_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets view id in autofill authentication information.
 */
int utc_autofill_auth_info_get_view_id_p(void)
{
    autofill_auth_info_h ai_h;
    char *view_id = NULL;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_view_id(ai_h, "login");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_view_id(ai_h, &view_id);
    assert(view_id);

    free(view_id);

    autofill_auth_info_destroy(ai_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_view_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets view id in autofill authentication information.
 */
int utc_autofill_auth_info_get_view_id_n(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_view_id(ai_h, "login");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_view_id(ai_h, NULL);

    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_autofill_data_present_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets whether autofill data presents or not in autofill authentication information.
 */
int utc_autofill_auth_info_set_autofill_data_present_p(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_autofill_data_present(ai_h, true);
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_autofill_data_present_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets whether autofill data presents or not in autofill authentication information.
 */
int utc_autofill_auth_info_set_autofill_data_present_n(void)
{
    int ret = autofill_auth_info_set_autofill_data_present(NULL, true);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_autofill_data_present_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets whether autofill data presents or not in autofill authentication information.
 */
int utc_autofill_auth_info_get_autofill_data_present_p(void)
{
    autofill_auth_info_h ai_h;
    bool autofill_data_present = false;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_autofill_data_present(ai_h, true);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_autofill_data_present(ai_h, &autofill_data_present);
    autofill_auth_info_destroy(ai_h);
    assert_eq(autofill_data_present, true);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_autofill_data_present_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets whether autofill data presents or not in autofill authentication information.
 */
int utc_autofill_auth_info_get_autofill_data_present_n(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_autofill_data_present(ai_h, true);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_autofill_data_present(ai_h, NULL);
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_authentication_needed_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets whether authentication is needed or not in autofill authentication information.
 */
int utc_autofill_auth_info_set_authentication_needed_p(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_authentication_needed(ai_h, true);
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_authentication_needed_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets whether authentication is needed or not in autofill authentication information.
 */
int utc_autofill_auth_info_set_authentication_needed_n(void)
{
    int ret = autofill_auth_info_set_authentication_needed(NULL, true);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_authentication_needed_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets whether authentication is needed or not in autofill authentication information.
 */
int utc_autofill_auth_info_get_authentication_needed_p(void)
{
    autofill_auth_info_h ai_h;
    bool authentication_needed = false;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_authentication_needed(ai_h, true);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_authentication_needed(ai_h, &authentication_needed);
    autofill_auth_info_destroy(ai_h);
    assert_eq(authentication_needed, true);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_authentication_needed_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets whether authentication is needed or not in autofill authentication information.
 */
int utc_autofill_auth_info_get_authentication_needed_n(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_authentication_needed(ai_h, true);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_authentication_needed(ai_h, NULL);
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_service_name_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets service name in autofill authentication information.
 */
int utc_autofill_auth_info_set_service_name_p(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_service_name(ai_h, "autofill");
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_service_name_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets service name in autofill authentication information.
 */
int utc_autofill_auth_info_set_service_name_n(void)
{
    int ret = autofill_auth_info_set_service_name(NULL, "autofill");
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_service_name_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets service name in autofill authentication information.
 */
int utc_autofill_auth_info_get_service_name_p(void)
{
    autofill_auth_info_h ai_h;
    char *service_name = NULL;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_service_name(ai_h, "autofill");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_service_name(ai_h, &service_name);
    autofill_auth_info_destroy(ai_h);
    assert(service_name);

    free(service_name);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_service_name_p
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets service name in autofill authentication information.
 */
int utc_autofill_auth_info_get_service_name_n(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_service_name(ai_h, "autofill");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_service_name(ai_h, NULL);
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_service_message_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets service message in autofill authentication information.
 */
int utc_autofill_auth_info_set_service_message_p(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_service_message(ai_h, "autofill");
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_service_message_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets service message in autofill authentication information.
 */
int utc_autofill_auth_info_set_service_message_n(void)
{
    int ret = autofill_auth_info_set_service_message(NULL, "autofill");
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_service_message_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets service message in autofill authentication information.
 */
int utc_autofill_auth_info_get_service_message_p(void)
{
    autofill_auth_info_h ai_h;
    char *service_message;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_service_message(ai_h, "autofill");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_service_message(ai_h, &service_message);
    autofill_auth_info_destroy(ai_h);
    assert(service_message);

    free(service_message);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_service_message_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets service message in autofill authentication information.
 */
int utc_autofill_auth_info_get_service_message_n(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_service_message(ai_h, "autofill");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_service_message(ai_h, NULL);
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_service_logo_image_path_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets service logo image path in autofill authentication information.
 */
int utc_autofill_auth_info_set_service_logo_image_path_p(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_service_logo_image_path(ai_h, "autofill");
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_service_logo_image_path_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets service logo image path in autofill authentication information.
 */
int utc_autofill_auth_info_set_service_logo_image_path_n(void)
{
    int ret = autofill_auth_info_set_service_logo_image_path(NULL, "autofill");
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_service_logo_image_path_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets service logo image path in autofill authentication information.
 */
int utc_autofill_auth_info_get_service_logo_image_path_p(void)
{
    autofill_auth_info_h ai_h;
    char *service_logo_image_path;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_service_logo_image_path(ai_h, "autofill");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_service_logo_image_path(ai_h, &service_logo_image_path);
    autofill_auth_info_destroy(ai_h);
    assert(service_logo_image_path);

    free(service_logo_image_path);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_get_service_logo_image_path_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets service logo image path in autofill authentication information.
 */
int utc_autofill_auth_info_get_service_logo_image_path_n(void)
{
    autofill_auth_info_h ai_h;
    int ret = autofill_auth_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_auth_info_set_service_logo_image_path(ai_h, "autofill");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_auth_info_get_service_logo_image_path(ai_h, NULL);
    autofill_auth_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

// fill response
/**
 * @testcase        utc_autofill_fill_response_create_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that creates autofill fill response.
 */
int utc_autofill_fill_response_create_p(void)
{
    autofill_fill_response_h fr_h;
    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);
    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_create_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that creates autofill fill response.
 */
int utc_autofill_fill_response_create_n(void)
{
    int ret = autofill_fill_response_create(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_create_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that destroys autofill fill response.
 */
int utc_autofill_fill_response_destroy_p(void)
{
    autofill_fill_response_h fr_h;
    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_destroy_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that destroys autofill fill response.
 */
int utc_autofill_fill_response_destroy_n(void)
{
    int ret = autofill_fill_response_destroy(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_set_app_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets app id in autofill fill response.
 */
int utc_autofill_fill_response_set_app_id_p(void)
{
    autofill_fill_response_h fr_h;
    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_set_app_id(fr_h, "org.tizen.example");
    autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_set_app_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets app id in autofill fill response.
 */
int utc_autofill_fill_response_set_app_id_n(void)
{
    autofill_fill_response_h fr_h;
    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_set_app_id(fr_h, NULL);
    autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_get_app_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets app id in autofill fill response.
 */
int utc_autofill_fill_response_get_app_id_p(void)
{
    autofill_fill_response_h fr_h;
    char *app_id = NULL;
    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_set_app_id(fr_h, "org.tizen.example");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_get_app_id(fr_h, &app_id);
    assert(app_id);

    free(app_id);

    autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_get_app_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets app id in autofill fill response.
 */
int utc_autofill_fill_response_get_app_id_n(void)
{
    autofill_fill_response_h fr_h;
    int ret = autofill_fill_response_create(&fr_h);
    assert(fr_h);

    ret = autofill_fill_response_set_app_id(fr_h, "org.tizen.example");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_get_app_id(fr_h, NULL);
    autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_set_view_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets view id in autofill fill response.
 */
int utc_autofill_fill_response_set_view_id_p(void)
{
    autofill_fill_response_h fr_h;
    int ret = autofill_fill_response_create(&fr_h);
    assert(fr_h);

    ret = autofill_fill_response_set_view_id(fr_h, "login");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_set_view_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets view id in autofill fill response.
 */
int utc_autofill_fill_response_set_view_id_n(void)
{
    autofill_fill_response_h fr_h;
    int ret = autofill_fill_response_create(&fr_h);
    assert(fr_h);

    ret = autofill_fill_response_set_view_id(fr_h, NULL);
    autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_get_view_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets view id in autofill fill response.
 */
int utc_autofill_fill_response_get_view_id_p(void)
{
    autofill_fill_response_h fr_h;
    char *view_id = NULL;
    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_set_view_id(fr_h, "login");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_get_view_id(fr_h, &view_id);
    autofill_fill_response_destroy(fr_h);
    assert(view_id);

    free(view_id);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_get_view_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets view id in autofill fill response.
 */
int utc_autofill_fill_response_get_view_id_n(void)
{
    autofill_fill_response_h fr_h;
    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_set_view_id(fr_h, "login");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_get_view_id(fr_h, NULL);
    autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_add_group_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that adds autofill group item in autofill fill response.
 */
int utc_autofill_fill_response_add_group_p(void)
{
    autofill_fill_response_h fr_h;
    autofill_fill_response_group_h res_group;

    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_group_create(&res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_add_group(fr_h, res_group);

    autofill_fill_response_group_destroy(res_group);

    autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_add_group_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that adds autofill group item in autofill fill response.
 */
int utc_autofill_fill_response_add_group_n(void)
{
    autofill_fill_response_h fr_h;
    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_add_group(fr_h, NULL);
    autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_foreach_group_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieves each autofill group item in autofill fill response.
 */
int utc_autofill_fill_response_foreach_group_p(void)
{
    autofill_fill_response_h fr_h;
    autofill_fill_response_group_h res_group;

    fill_response_group_cb_result = false;

    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_group_create(&res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    autofill_fill_response_add_group(fr_h, res_group);

    ret = autofill_fill_response_foreach_group(fr_h, fill_response_group_cb, NULL);

    autofill_fill_response_group_destroy(res_group);
    autofill_fill_response_destroy(fr_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    assert_eq(fill_response_group_cb_result, true);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_foreach_group_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieves each autofill group item in autofill fill response.
 */
int utc_autofill_fill_response_foreach_group_n(void)
{
    autofill_fill_response_h fr_h;
    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_foreach_group(fr_h, NULL, NULL);
    autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_get_group_count_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets the count of autofill group items in autofill fill response.
 */
int utc_autofill_fill_response_get_group_count_p(void)
{
    autofill_fill_response_h fr_h;
    autofill_fill_response_group_h res_group;
    int count = 0;

    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_group_create(&res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_add_group(fr_h, res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_get_group_count(fr_h, &count);
    autofill_fill_response_group_destroy(res_group);
    autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert_eq(count, 1);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_get_group_count_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets the count of autofill group items in autofill fill response.
 */
int utc_autofill_fill_response_get_group_count_n(void)
{
    autofill_fill_response_h fr_h;
    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_get_group_count(fr_h, NULL);
    autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_group_add_item_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that add autofill fill response item in autofill group item.
 */
int utc_autofill_fill_response_group_add_item_p(void)
{
    autofill_fill_response_h fr_h;
    autofill_fill_response_group_h res_group;
    autofill_fill_response_item_h res_it_h;

    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_group_create(&res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_add_group(fr_h, res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    /* item 1 */
    autofill_fill_response_item_create(&res_it_h);
    autofill_fill_response_item_set_id(res_it_h, "id");
    autofill_fill_response_item_set_presentation_text(res_it_h, "tester1");
    autofill_fill_response_item_set_value(res_it_h, "tester1");

    /* Add item in group */
    ret = autofill_fill_response_group_add_item(res_group, res_it_h);
    autofill_fill_response_group_destroy(res_group);
    autofill_fill_response_destroy(fr_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_group_add_item_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that add autofill fill response item in autofill group item.
 */
int utc_autofill_fill_response_group_add_item_n(void)
{
    autofill_fill_response_h fr_h;
    autofill_fill_response_group_h res_group;

    int ret = autofill_fill_response_create(&fr_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(fr_h);

    ret = autofill_fill_response_group_create(&res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_add_group(fr_h, res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    /* Add item in group */
    ret = autofill_fill_response_group_add_item(res_group, NULL);
    autofill_fill_response_group_destroy(res_group);
    autofill_fill_response_destroy(fr_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_group_create_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that add creates autofill fill response group.
 */
int utc_autofill_fill_response_group_create_p(void)
{
    autofill_fill_response_group_h res_group;
    int ret = autofill_fill_response_group_create(&res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_group_create_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that add creates autofill fill response group.
 */
int utc_autofill_fill_response_group_create_n(void)
{
    int ret = autofill_fill_response_group_create(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_group_destroy_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that add destroys autofill fill response group.
 */
int utc_autofill_fill_response_group_destroy_p(void)
{
    autofill_fill_response_group_h res_group;
    int ret = autofill_fill_response_group_create(&res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_group_destroy(res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_group_destroy_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that add destroys autofill fill response group.
 */
int utc_autofill_fill_response_group_destroy_n(void)
{
    int ret = autofill_fill_response_group_destroy(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_group_clone_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that clones autofill fill response group.
 */
int utc_autofill_fill_response_group_clone_p(void)
{
    autofill_fill_response_group_h res_group, res_clone_group;
    autofill_fill_response_item_h res_it_h;
    int ret;

    ret = autofill_fill_response_group_create(&res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    /* item 1 */
    autofill_fill_response_item_create(&res_it_h);
    autofill_fill_response_item_set_id(res_it_h, "id");
    autofill_fill_response_item_set_presentation_text(res_it_h, "tester1");
    autofill_fill_response_item_set_value(res_it_h, "tester1");

    /* Add item in group */
    ret = autofill_fill_response_group_add_item(res_group, res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_group_clone(res_group, &res_clone_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    autofill_fill_response_group_destroy(res_group);
    autofill_fill_response_group_destroy(res_clone_group);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_group_clone_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that clones autofill fill response group.
 */
int utc_autofill_fill_response_group_clone_n(void)
{
    int ret;
    ret = autofill_fill_response_group_clone(NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_group_foreach_item_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieve each autofill fill response item in autofill fill response group.
 */
int utc_autofill_fill_response_group_foreach_item_p(void)
{
    autofill_fill_response_group_h res_group;
    autofill_fill_response_item_h res_it_h;
    int ret;

    fill_response_item_cb_result = false;

    ret = autofill_fill_response_group_create(&res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    /* item 1 */
    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_id(res_it_h, "id");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_presentation_text(res_it_h, "tester1");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_value(res_it_h, "tester1");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    /* Add item in group */
    ret = autofill_fill_response_group_add_item(res_group, res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_group_foreach_item(res_group, fill_response_item_cb, NULL);
    autofill_fill_response_group_destroy(res_group);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    assert_eq(fill_response_item_cb_result, true);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_group_foreach_item_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieve each autofill fill response item in autofill fill response group.
 */
int utc_autofill_fill_response_group_foreach_item_n(void)
{
    int ret;
    ret = autofill_fill_response_group_foreach_item(NULL, NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_create_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that creates autofill save view information.
 */
int utc_autofill_save_view_info_create_p(void)
{
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);
    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_create_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that creates autofill save view information.
 */
int utc_autofill_save_view_info_create_n(void)
{
    int ret = autofill_save_view_info_create(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_destroy_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that destroys autofill save view information.
 */
int utc_autofill_save_view_info_destroy_p(void)
{
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_destroy(vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_destroy_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that destroys autofill save view information.
 */
int utc_autofill_save_view_info_destroy_n(void)
{
    int ret = autofill_save_view_info_destroy(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_set_app_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets app id in autofill save view information.
 */
int utc_autofill_save_view_info_set_app_id_p(void)
{
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_set_app_id(vi_h, "org.tizen.example");
    autofill_save_view_info_destroy(vi_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_set_app_id_p
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets app id in autofill save view information.
 */
int utc_autofill_save_view_info_set_app_id_n(void)
{
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_set_app_id(vi_h, NULL);
    autofill_save_view_info_destroy(vi_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_get_app_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets app id in autofill save view information.
 */
int utc_autofill_save_view_info_get_app_id_p(void)
{
    autofill_save_view_info_h vi_h;
    char *app_id = NULL;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_set_app_id(vi_h, "org.tizen.example");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_view_info_get_app_id(vi_h, &app_id);
    autofill_save_view_info_destroy(vi_h);
    assert(app_id);

    free(app_id);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_get_app_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets app id in autofill save view information.
 */
int utc_autofill_save_view_info_get_app_id_n(void)
{
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_set_app_id(vi_h, "org.tizen.example");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_view_info_get_app_id(vi_h, NULL);
    autofill_save_view_info_destroy(vi_h);

    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_set_view_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets view id in autofill save view information.
 */
int utc_autofill_save_view_info_set_view_id_p(void)
{
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_set_view_id(vi_h, "login");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    autofill_save_view_info_destroy(vi_h);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_set_view_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets view id in autofill save view information.
 */
int utc_autofill_save_view_info_set_view_id_n(void)
{
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_set_view_id(vi_h, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    autofill_save_view_info_destroy(vi_h);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_get_view_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets view id in autofill save view information.
 */
int utc_autofill_save_view_info_get_view_id_p(void)
{
    autofill_save_view_info_h vi_h;
    char *view_id = NULL;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_set_view_id(vi_h, "login");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_view_info_get_view_id(vi_h, &view_id);
    autofill_save_view_info_destroy(vi_h);
    assert(view_id);

    free(view_id);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_get_view_id_p
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets view id in autofill save view information.
 */
int utc_autofill_save_view_info_get_view_id_n(void)
{
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_set_view_id(vi_h, "login");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_view_info_get_view_id(vi_h, NULL);

    autofill_save_view_info_destroy(vi_h);

    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_set_view_title_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets view title in autofill save view information.
 */
int utc_autofill_save_view_info_set_view_title_p(void)
{
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_set_view_title(vi_h, "login");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    autofill_save_view_info_destroy(vi_h);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_set_view_title_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets view title in autofill save view information.
 */
int utc_autofill_save_view_info_set_view_title_n(void)
{
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_set_view_title(vi_h, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    autofill_save_view_info_destroy(vi_h);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_get_view_title_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets view title in autofill save view information.
 */
int utc_autofill_save_view_info_get_view_title_p(void)
{
    autofill_save_view_info_h vi_h;
    char *view_title = NULL;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_set_view_title(vi_h, "login");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_view_info_get_view_title(vi_h, &view_title);
    autofill_save_view_info_destroy(vi_h);
    assert(view_title);

    free(view_title);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_get_view_title_p
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets view title in autofill save view information.
 */
int utc_autofill_save_view_info_get_view_title_n(void)
{
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_set_view_title(vi_h, "login");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_view_info_get_view_title(vi_h, NULL);

    autofill_save_view_info_destroy(vi_h);

    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_add_item_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that adds autofill save item in autofill save view information.
 */
int utc_autofill_save_view_info_add_item_p(void)
{
    autofill_save_item_h si_h;
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_item_create(&si_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_view_info_add_item(vi_h, si_h);

    autofill_save_view_info_destroy(vi_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_add_item_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that adds autofill save item in autofill save view information.
 */
int utc_autofill_save_view_info_add_item_n(void)
{
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_add_item(vi_h, NULL);

    autofill_save_view_info_destroy(vi_h);

    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_foreach_item_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieves autofill save item in autofill save view information.
 */
int utc_autofill_save_view_info_foreach_item_p(void)
{
    autofill_save_view_info_h vi_h;
    autofill_save_item_h it_h;

    save_view_info_item_cb_result = false;

    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_save_item_set_id(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_item_set_label(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_item_set_value(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    autofill_save_view_info_add_item(vi_h, it_h);

    ret = autofill_save_view_info_foreach_item(vi_h, __save_view_info_item_cb, NULL);
    autofill_save_view_info_destroy(vi_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    assert_eq(save_view_info_item_cb_result, true);

    return 0;
}

/**
 * @testcase        utc_autofill_save_view_info_foreach_item_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieves autofill save item in autofill save view information.
 */
int utc_autofill_save_view_info_foreach_item_n(void)
{
    autofill_save_view_info_h vi_h;
    int ret = autofill_save_view_info_create(&vi_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(vi_h);

    ret = autofill_save_view_info_foreach_item(vi_h, NULL, NULL);
    autofill_save_view_info_destroy(vi_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_create_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that creates autofill fill response item.
 */
int utc_autofill_fill_response_item_create_p(void)
{
    autofill_fill_response_item_h res_it_h;
    int ret;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_create_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that creates autofill fill response item.
 */
int utc_autofill_fill_response_item_create_n(void)
{
    int ret;

    ret = autofill_fill_response_item_create(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_destroy_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that creates autofill fill response item.
 */
int utc_autofill_fill_response_item_destroy_p(void)
{
    int ret;
    autofill_fill_response_item_h res_it_h;
    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_destroy_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that creates autofill fill response item.
 */
int utc_autofill_fill_response_item_destroy_n(void)
{
    int ret;
    ret = autofill_fill_response_item_destroy(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_clone_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that clones autofill fill response item.
 */
int utc_autofill_fill_response_item_clone_p(void)
{
    autofill_fill_response_item_h res_it_h, res_clone_it_h;
    int ret;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_id(res_it_h, "id");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_presentation_text(res_it_h, "tester1");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_value(res_it_h, "tester1");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_clone(res_it_h, &res_clone_it_h);

    autofill_fill_response_item_destroy(res_it_h);
    autofill_fill_response_item_destroy(res_clone_it_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_clone_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that clones autofill fill response item.
 */
int utc_autofill_fill_response_item_clone_n(void)
{
    int ret;

    ret = autofill_fill_response_item_clone(NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_set_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets autofill id in autofill fill response item.
 */
int utc_autofill_fill_response_item_set_id_p(void)
{
    autofill_fill_response_item_h res_it_h;
    int ret;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_id(res_it_h, "id");
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_set_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets autofill id in autofill fill response item.
 */
int utc_autofill_fill_response_item_set_id_n(void)
{
    autofill_fill_response_item_h res_it_h;
    int ret;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_id(res_it_h, NULL);
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_get_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets autofill id in autofill fill response item.
 */
int utc_autofill_fill_response_item_get_id_p(void)
{
    char *id;
    int ret;
    autofill_fill_response_item_h res_it_h;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_id(res_it_h, "id");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_get_id(res_it_h, &id);
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = strcmp("id", id);
    if (id)
        free(id);

    assert_eq(ret, 0);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_get_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets autofill id in autofill fill response item.
 */
int utc_autofill_fill_response_item_get_id_n(void)
{
    int ret;
    autofill_fill_response_item_h res_it_h;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_get_id(res_it_h, NULL);
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_set_value_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets autofill value in autofill fill response item.
 */
int utc_autofill_fill_response_item_set_value_p(void)
{
    autofill_fill_response_item_h res_it_h;
    int ret;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_value(res_it_h, "test");
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_set_value_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets autofill value in autofill fill response item.
 */
int utc_autofill_fill_response_item_set_value_n(void)
{
    autofill_fill_response_item_h res_it_h;
    int ret;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_value(res_it_h, NULL);
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_get_value_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets autofill value in autofill fill response item.
 */
int utc_autofill_fill_response_item_get_value_p(void)
{
    char *value;
    int ret;
    autofill_fill_response_item_h res_it_h;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_value(res_it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_get_value(res_it_h, &value);
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = strcmp("test", value);
    if (value)
        free(value);

    assert_eq(ret, 0);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_get_value_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets autofill value in autofill fill response item.
 */
int utc_autofill_fill_response_item_get_value_n(void)
{
    int ret;
    autofill_fill_response_item_h res_it_h;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_get_value(res_it_h, NULL);
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_set_presentation_text_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets autofill presentation text in autofill fill response item.
 */
int utc_autofill_fill_response_item_set_presentation_text_p(void)
{
    autofill_fill_response_item_h res_it_h;
    int ret;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_presentation_text(res_it_h, "test");
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_set_presentation_text_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets autofill presentation text in autofill fill response item.
 */
int utc_autofill_fill_response_item_set_presentation_text_n(void)
{
    autofill_fill_response_item_h res_it_h;
    int ret;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_presentation_text(res_it_h, NULL);
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_get_presentation_text_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets autofill presentation text in autofill fill response item.
 */
int utc_autofill_fill_response_item_get_presentation_text_p(void)
{
    char *presentation_text;
    int ret;
    autofill_fill_response_item_h res_it_h;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_presentation_text(res_it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_get_presentation_text(res_it_h, &presentation_text);
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = strcmp("test", presentation_text);
    if (presentation_text)
        free(presentation_text);
    assert_eq(ret, 0);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_get_presentation_text_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets autofill presentation text in autofill fill response item.
 */
int utc_autofill_fill_response_item_get_presentation_text_n(void)
{
    int ret;
    autofill_fill_response_item_h res_it_h;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_get_presentation_text(res_it_h, NULL);
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_set_autofill_hint_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets autofill hint in autofill fill response item.
 */
int utc_autofill_fill_response_item_set_autofill_hint_p(void)
{
    autofill_fill_response_item_h res_it_h;
    int ret;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_set_autofill_hint(res_it_h, AUTOFILL_HINT_NAME);
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_set_autofill_hint_p
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets autofill hint in autofill fill response item.
 */
int utc_autofill_fill_response_item_set_autofill_hint_n(void)
{
    int ret;

    ret = autofill_fill_response_item_set_autofill_hint(NULL, AUTOFILL_HINT_NAME);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_get_autofill_hint_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets autofill hint in autofill fill response item.
 */
int utc_autofill_fill_response_item_get_autofill_hint_p(void)
{
    autofill_fill_response_item_h res_it_h;
    autofill_hint_e autofill_hint;
    int ret;

    ret = autofill_fill_response_item_create(&res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_fill_response_item_get_autofill_hint(res_it_h, &autofill_hint);
    autofill_fill_response_item_destroy(res_it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_item_get_autofill_hint_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets autofill hint in autofill fill response item.
 */
int utc_autofill_fill_response_item_get_autofill_hint_n(void)
{
    autofill_hint_e autofill_hint;
    int ret = autofill_fill_response_item_get_autofill_hint(NULL, &autofill_hint);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

// save info
/**
 * @testcase        utc_autofill_save_item_create_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that creates autofill save item.
 */
int utc_autofill_save_item_create_p(void)
{
    autofill_save_item_h it_h;
    int ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_create_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that creates autofill save item.
 */
int utc_autofill_save_item_create_n(void)
{
    int ret = autofill_save_item_create(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_destroy_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that destroys autofill save item.
 */
int utc_autofill_save_item_destroy_p(void)
{
    autofill_save_item_h it_h = NULL;
    int ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_save_item_set_id(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_item_set_label(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_item_set_value(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_item_destroy(it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_save_item_destroy_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that destroys autofill save item.
 */
int utc_autofill_save_item_destroy_n(void)
{
    int ret = autofill_save_item_destroy(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_clone_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that clones autofill save item.
 */
int utc_autofill_save_item_clone_p(void)
{
    autofill_save_item_h it_h = NULL, clone_h;
    int ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_save_item_set_id(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_item_set_label(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_item_set_value(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_item_clone(it_h, &clone_h);

    autofill_save_item_destroy(it_h);
    autofill_save_item_destroy(clone_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_save_item_clone_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that clones autofill save item.
 */
int utc_autofill_save_item_clone_n(void)
{
    int ret = autofill_save_item_clone(NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_set_autofill_hint_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets autofill hint in autofill save item.
 */
int utc_autofill_save_item_set_autofill_hint_p(void)
{
    autofill_save_item_h it_h = NULL;
    int ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_save_item_set_autofill_hint(it_h, AUTOFILL_HINT_NAME);
    autofill_save_item_destroy(it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_save_item_set_autofill_hint_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets autofill hint in autofill save item.
 */
int utc_autofill_save_item_set_autofill_hint_n(void)
{
    int ret = autofill_save_item_set_autofill_hint(NULL, AUTOFILL_HINT_NAME);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_get_autofill_hint_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets autofill hint in autofill save item.
 */
int utc_autofill_save_item_get_autofill_hint_p(void)
{
    autofill_save_item_h it_h = NULL;
    autofill_hint_e autofill_hint;
    int ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_save_item_get_autofill_hint(it_h, &autofill_hint);
    autofill_save_item_destroy(it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_get_autofill_hint_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets autofill hint in autofill save item.
 */
int utc_autofill_save_item_get_autofill_hint_n(void)
{
    autofill_hint_e autofill_hint;
    int ret = autofill_save_item_get_autofill_hint(NULL, &autofill_hint);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_set_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets autofill id in autofill save item.
 */
int utc_autofill_save_item_set_id_p(void)
{
    autofill_save_item_h it_h = NULL;
    int ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_save_item_set_id(it_h, "test");
    autofill_save_item_destroy(it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_set_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets autofill id in autofill save item.
 */
int utc_autofill_save_item_set_id_n(void)
{
    int ret = autofill_save_item_set_id(NULL, "test");
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_get_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets autofill id in autofill save item.
 */
int utc_autofill_save_item_get_id_p(void)
{
    autofill_save_item_h it_h = NULL;
    char *id = NULL;
    int ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_save_item_set_id(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_item_get_id(it_h, &id);
    autofill_save_item_destroy(it_h);

    assert(id);

    if (id)
        free(id);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_save_item_get_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets autofill id in autofill save item.
 */
int utc_autofill_save_item_get_id_n(void)
{
    char *id = NULL;
    int ret = autofill_save_item_get_id(NULL, &id);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_set_label_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets autofill label in autofill save item.
 */
int utc_autofill_save_item_set_label_p(void)
{
    autofill_save_item_h it_h = NULL;
    int ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_save_item_set_label(it_h, "test");
    autofill_save_item_destroy(it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_set_label_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets autofill label in autofill save item.
 */
int utc_autofill_save_item_set_label_n(void)
{
    int ret = autofill_save_item_set_label(NULL, "test");
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_get_label_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets autofill label in autofill save item.
 */
int utc_autofill_save_item_get_label_p(void)
{
    autofill_save_item_h it_h = NULL;
    char *label = NULL;
    int ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_save_item_set_label(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_item_get_label(it_h, &label);
    autofill_save_item_destroy(it_h);

    assert(label);

    if (label)
        free(label);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_save_item_get_label_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets autofill label in autofill save item.
 */
int utc_autofill_save_item_get_label_n(void)
{
    char *label = NULL;
    int ret = autofill_save_item_get_label(NULL, &label);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_set_sensitive_data_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets whether sensitive data or not in autofill save item.
 */
int utc_autofill_save_item_set_sensitive_data_p(void)
{
    autofill_save_item_h it_h = NULL;
    int ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_save_item_set_sensitive_data(it_h, true);
    autofill_save_item_destroy(it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_set_sensitive_data_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets whether sensitive data or not in autofill save item.
 */
int utc_autofill_save_item_set_sensitive_data_n(void)
{
    int ret = autofill_save_item_set_sensitive_data(NULL, true);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_get_sensitive_data_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets whether sensitive data or not in autofill save item.
 */
int utc_autofill_save_item_get_sensitive_data_p(void)
{
    autofill_save_item_h it_h = NULL;
    bool sensitive_data;
    int ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_save_item_get_sensitive_data(it_h, &sensitive_data);
    autofill_save_item_destroy(it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_get_sensitive_data_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets whether sensitive data or not in autofill save item.
 */
int utc_autofill_save_item_get_sensitive_data_n(void)
{
    bool sensitive_data;
    int ret = autofill_save_item_get_sensitive_data(NULL, &sensitive_data);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_set_value_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets autofill value in autofill save item.
 */
int utc_autofill_save_item_set_value_p(void)
{
    autofill_save_item_h it_h = NULL;
    int ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_save_item_set_value(it_h, "test");
    autofill_save_item_destroy(it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_set_value_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets autofill value in autofill save item.
 */
int utc_autofill_save_item_set_value_n(void)
{
    int ret = autofill_save_item_set_value(NULL, "test");
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_save_item_get_value_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets autofill value in autofill save item.
 */
int utc_autofill_save_item_get_value_p(void)
{
    autofill_save_item_h it_h = NULL;
    char *value = NULL;
    int ret = autofill_save_item_create(&it_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(it_h);

    ret = autofill_save_item_set_value(it_h, "test");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_save_item_get_value(it_h, &value);
    autofill_save_item_destroy(it_h);

    assert(value);

    if (value)
        free(value);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_save_item_get_value_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets autofill value in autofill save item.
 */
int utc_autofill_save_item_get_value_n(void)
{
    char *value = NULL;
    int ret = autofill_save_item_get_value(NULL, &value);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

//error info
/**
 * @testcase        utc_autofill_error_info_create_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that creates autofill error information.
 */
int utc_autofill_error_info_create_p(void)
{
    autofill_error_info_h ai_h;
    int ret = autofill_error_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);
    return 0;
}

/**
 * @testcase        utc_autofill_error_info_create_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that creates autofill error information.
 */
//& purpose: A purpose of a autofill_error_info_create() negative TC.
int utc_autofill_error_info_create_n(void)
{
    int ret = autofill_error_info_create(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_error_info_destroy_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that destroys autofill error information.
 */
int utc_autofill_error_info_destroy_p(void)
{
    autofill_error_info_h ai_h;
    int ret = autofill_error_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_error_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_error_info_destroy_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that destroys autofill error information.
 */
int utc_autofill_error_info_destroy_n(void)
{
    int ret = autofill_error_info_destroy(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_error_info_set_app_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets app id in autofill error information.
 */
int utc_autofill_error_info_set_app_id_p(void)
{
    autofill_error_info_h ai_h;
    int ret = autofill_error_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_error_info_set_app_id(ai_h, "org.tizen.example");
    autofill_error_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_error_info_set_app_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets app id in autofill error information.
 */
int utc_autofill_error_info_set_app_id_n(void)
{
    autofill_error_info_h ai_h;
    int ret = autofill_error_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_error_info_set_app_id(ai_h, NULL);
    autofill_error_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_error_info_get_app_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets app id in autofill error information.
 */
int utc_autofill_error_info_get_app_id_p(void)
{
    autofill_error_info_h ai_h;
    char *app_id = NULL;
    int ret = autofill_error_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_error_info_set_app_id(ai_h, "org.tizen.example");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_error_info_get_app_id(ai_h, &app_id);
    assert(app_id);

    free(app_id);

    autofill_error_info_destroy(ai_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_error_info_get_app_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets app id in autofill error information.
 */
int utc_autofill_error_info_get_app_id_n(void)
{
    autofill_error_info_h ai_h;
    int ret = autofill_error_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_error_info_set_app_id(ai_h, "org.tizen.example");
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_error_info_get_app_id(ai_h, NULL);
    autofill_error_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_error_info_set_error_code_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets whether authentication is needed or not in autofill error information.
 */
int utc_autofill_error_info_set_error_code_p(void)
{
    autofill_error_info_h ai_h;
    int ret = autofill_error_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_error_info_set_error_code(ai_h, AUTOFILL_ERROR_AUTHENTICATION_FAILED);
    autofill_error_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_autofill_error_info_set_error_code_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets whether authentication is needed or not in autofill error information.
 */
int utc_autofill_error_info_set_error_code_n(void)
{
    int ret = autofill_error_info_set_error_code(NULL, AUTOFILL_ERROR_AUTHENTICATION_FAILED);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_error_info_get_error_code_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets whether autofill data presents or not in autofill error information.
 */
int utc_autofill_error_info_get_error_code_p(void)
{
    autofill_error_info_h ai_h;
    int error_code = 0;
    int ret = autofill_error_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_error_info_set_error_code(ai_h, AUTOFILL_ERROR_AUTHENTICATION_FAILED);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_error_info_get_error_code(ai_h, &error_code);
    autofill_error_info_destroy(ai_h);
    assert_eq(error_code, AUTOFILL_ERROR_AUTHENTICATION_FAILED);

    return 0;
}

/**
 * @testcase        utc_autofill_error_info_get_error_code_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets whether autofill data presents or not in autofill error information.
 */
int utc_autofill_error_info_get_error_code_n(void)
{
    autofill_error_info_h ai_h;
    int ret = autofill_error_info_create(&ai_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert(ai_h);

    ret = autofill_error_info_set_error_code(ai_h, AUTOFILL_ERROR_AUTHENTICATION_FAILED);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_error_info_get_error_code(ai_h, NULL);
    autofill_error_info_destroy(ai_h);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}
