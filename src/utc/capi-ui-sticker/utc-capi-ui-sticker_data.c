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
#include <stdbool.h>
#include <system_info.h>
#include <sticker_data.h>
#include <sticker_provider.h>

#define STICKER_FEATURE "tizen.org/feature/ui_service.sticker"

static bool sticker_supported = false;
static bool callback_result = false;
static sticker_data_h g_dh = NULL;
static sticker_provider_h g_ph = NULL;

static void foreach_keyword_cb(const char *keyword, void *user_data)
{
    callback_result = true;
}

/**
 * @function		utc_capi_ui_sticker_data_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_ui_sticker_data_startup(void)
{
    if (!system_info_get_platform_bool(STICKER_FEATURE, &sticker_supported)) {
        if (sticker_supported != true)
            fprintf(stderr, "This device is not support Sticker API.\n");
    }

    if (sticker_supported == true) {
        sticker_data_create(&g_dh);
        sticker_data_set_uri(g_dh, STICKER_DATA_URI_WEB_RESOURCE, "www.samsung.com");
        sticker_data_add_keyword(g_dh, "smile");
        sticker_data_add_keyword(g_dh, "face");
        sticker_data_add_keyword(g_dh, "cute");
        sticker_data_set_group_name(g_dh, "tizen");
        sticker_data_set_thumbnail(g_dh, "/res/test.png");
        sticker_data_set_description(g_dh, "TCT Test");
        sticker_data_set_display_type(g_dh, STICKER_DATA_DISP_WALLPAPER);
    }
}

/**
 * @function		utc_capi_ui_sticker_data_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_ui_sticker_data_cleanup(void)
{
    if (sticker_supported == true) {
        sticker_data_destroy(g_dh);
        g_dh = NULL;
    }
}


/**
 * @testcase        utc_sticker_data_create_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that creates sticker data handle.
 */
int utc_sticker_data_create_p(void)
{
    sticker_data_h data_handle = NULL;
    int ret = sticker_data_create(&data_handle);
    if (sticker_supported == true) {
        assert_eq(ret, STICKER_ERROR_NONE);
        sticker_data_destroy(data_handle);
        data_handle = NULL;
    } else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_data_create_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that creates sticker data handle.
 */
int utc_sticker_data_create_n(void)
{
    int ret = sticker_data_create(NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_destroy_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that destroys sticker data handle.
 */
int utc_sticker_data_destroy_p(void)
{
    sticker_data_h data_handle = NULL;
    int ret = sticker_data_create(&data_handle);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    ret = sticker_data_destroy(data_handle);
    data_handle = NULL;
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_destroy_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that destroys sticker data handle.
 */
int utc_sticker_data_destroy_n(void)
{
    int ret = sticker_data_destroy(NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_clone_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that clones sticker data.
 */
int utc_sticker_data_clone_p(void)
{
    sticker_data_h clone = NULL;
    int ret = sticker_data_clone(g_dh, &clone);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    ret = sticker_data_destroy(clone);
    clone = NULL;

    return 0;
}

/**
 * @testcase        utc_sticker_data_clone_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that clones sticker data.
 */
int utc_sticker_data_clone_n(void)
{
    int ret = sticker_data_clone(NULL, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_app_id_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets application id of sticker data.
 */
int utc_sticker_data_get_app_id_p(void)
{
    char *app_id = NULL;
    int ret = sticker_data_get_app_id(g_dh, &app_id);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    if (app_id) {
        free(app_id);
        app_id = NULL;
    }

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_app_id_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets application id of sticker data.
 */
int utc_sticker_data_get_app_id_n(void)
{
    char *app_id = NULL;
    int ret = sticker_data_get_app_id(NULL, &app_id);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_set_uri_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets uri of sticker data.
 */
int utc_sticker_data_set_uri_p(void)
{
    int ret = sticker_data_set_uri(g_dh, STICKER_DATA_URI_WEB_RESOURCE, "www.tizen.org");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_set_uri_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets uri of sticker data.
 */
int utc_sticker_data_set_uri_n(void)
{
    int ret = sticker_data_set_uri(NULL, STICKER_DATA_URI_WEB_RESOURCE, "www.tizen.org");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_set_uri_n2
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets uri of sticker data.
 */
int utc_sticker_data_set_uri_n2(void)
{
    int ret = sticker_data_set_uri(g_dh, STICKER_DATA_URI_LOCAL_PATH, "/aaa/bbb/ccc.png");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_uri_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets uri of sticker data.
 */
int utc_sticker_data_get_uri_p(void)
{
    sticker_data_uri_type_e type;
    char *uri = NULL;

    int ret = sticker_data_get_uri(g_dh, &type, &uri);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    if (uri) {
        free(uri);
        uri = NULL;
    }

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_uri_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets uri of sticker data.
 */
int utc_sticker_data_get_uri_n(void)
{
    int ret = sticker_data_get_uri(g_dh, NULL, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_foreach_keyword_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieves all keywords of sticker data.
 */
int utc_sticker_data_foreach_keyword_p(void)
{
    callback_result = false;
    int ret = sticker_data_foreach_keyword(g_dh, foreach_keyword_cb, NULL);
    if (sticker_supported == true) {
        assert_eq(callback_result, true);
        assert_eq(ret, STICKER_ERROR_NONE);
    } else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_data_foreach_keyword_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieves all keywords of sticker data.
 */
int utc_sticker_data_foreach_keyword_n(void)
{
    int ret = sticker_data_foreach_keyword(g_dh, NULL, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_add_keyword_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that adds keyword of sticker data.
 */
int utc_sticker_data_add_keyword_p(void)
{
    int ret = sticker_data_add_keyword(g_dh, "test");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_add_keyword_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that adds keyword of sticker data.
 */
int utc_sticker_data_add_keyword_n(void)
{
    int ret = sticker_data_add_keyword(g_dh, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_add_keyword_n2
 * @since_tizen     5.5
 * @description     Negative UTC of the function that adds keyword of sticker data.
 */
int utc_sticker_data_add_keyword_n2(void)
{
    int ret = sticker_data_add_keyword(g_dh, "smile");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_remove_keyword_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that removes keyword of sticker data.
 */
int utc_sticker_data_remove_keyword_p(void)
{
    int ret = sticker_data_remove_keyword(g_dh, "face");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_remove_keyword_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that removes keyword of sticker data.
 */
int utc_sticker_data_remove_keyword_n(void)
{
    int ret = sticker_data_remove_keyword(g_dh, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_remove_keyword_n2
 * @since_tizen     5.5
 * @description     Negative UTC of the function that removes keyword of sticker data.
 */
int utc_sticker_data_remove_keyword_n2(void)
{
    int ret = sticker_data_remove_keyword(g_dh, "test");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_set_group_name_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets group name of sticker data.
 */
int utc_sticker_data_set_group_name_p(void)
{
    int ret = sticker_data_set_group_name(g_dh, "samsung");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_set_group_name_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets group name of sticker data.
 */
int utc_sticker_data_set_group_name_n(void)
{
    int ret = sticker_data_set_group_name(g_dh, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_group_name_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets group name of sticker data.
 */
int utc_sticker_data_get_group_name_p(void)
{
    char *group = NULL;
    int ret = sticker_data_get_group_name(g_dh, &group);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    if (group) {
        free(group);
        group = NULL;
    }

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_group_name_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets group name of sticker data.
 */
int utc_sticker_data_get_group_name_n(void)
{
    int ret = sticker_data_get_group_name(g_dh, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_set_thumbnail_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets thumbnail of sticker data.
 */
int utc_sticker_data_set_thumbnail_p(void)
{
    int ret = sticker_data_set_thumbnail(g_dh, "/res/test.png");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_set_thumbnail_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets thumbnail of sticker data.
 */
int utc_sticker_data_set_thumbnail_n(void)
{
    int ret = sticker_data_set_thumbnail(g_dh, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_set_thumbnail_n2
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets thumbnail of sticker data.
 */
int utc_sticker_data_set_thumbnail_n2(void)
{
    int ret = sticker_data_set_thumbnail(g_dh, "/aaa/bbb/ccc.png");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_thumbnail_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets thumbnail of sticker data.
 */
int utc_sticker_data_get_thumbnail_p(void)
{
    char *thumbnail = NULL;
    int ret = sticker_data_get_thumbnail(g_dh, &thumbnail);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    if (thumbnail) {
        free(thumbnail);
        thumbnail = NULL;
    }

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_thumbnail_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets thumbnail of sticker data.
 */
int utc_sticker_data_get_thumbnail_n(void)
{
    int ret = sticker_data_get_thumbnail(g_dh, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_set_description_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets description of sticker data.
 */
int utc_sticker_data_set_description_p(void)
{
    int ret = sticker_data_set_description(g_dh, "capi-ui-sticker TCT Test");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_set_description_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets description of sticker data.
 */
int utc_sticker_data_set_description_n(void)
{
    int ret = sticker_data_set_description(g_dh, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_description_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets description of sticker data.
 */
int utc_sticker_data_get_description_p(void)
{
    char *description = NULL;
    int ret = sticker_data_get_description(g_dh, &description);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    if (description) {
        free(description);
        description = NULL;
    }

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_description_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets description of sticker data.
 */
int utc_sticker_data_get_description_n(void)
{
    int ret = sticker_data_get_description(g_dh, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_date_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets last updated date.
 */
int utc_sticker_data_get_date_p(void)
{
    char *date = NULL;
    int ret = sticker_data_get_date(g_dh, &date);
    if (sticker_supported == true)
        assert_neq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    if (date) {
        free(date);
        date = NULL;
    }

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_date_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets last updated date.
 */
int utc_sticker_data_get_date_n(void)
{
    int ret = sticker_data_get_date(g_dh, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_set_display_type_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets display type of sticker data.
 */
int utc_sticker_data_set_display_type_p(void)
{
    int ret = sticker_data_set_display_type(g_dh, STICKER_DATA_DISP_EMOJI);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_set_display_type_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets display type of sticker data.
 */
int utc_sticker_data_set_display_type_n(void)
{
    int ret = sticker_data_set_display_type(g_dh, 100);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_display_type_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets display type of sticker data.
 */
int utc_sticker_data_get_display_type_p(void)
{
    sticker_data_display_type_e disp_type;
    int ret = sticker_data_get_display_type(g_dh, &disp_type);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_display_type_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets display type of sticker data.
 */
int utc_sticker_data_get_display_type_n(void)
{
    int ret = sticker_data_get_display_type(g_dh, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_handle_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets the sticker data handle using URI.
 */
int utc_sticker_data_get_handle_p(void)
{
    sticker_data_h tmp_handle = NULL;
    sticker_provider_create(&g_ph);
    sticker_provider_insert_data(g_ph, g_dh);
    int ret = sticker_data_get_handle("www.samsung.com", &tmp_handle);
    sticker_provider_delete_data(g_ph, tmp_handle);
    sticker_provider_destroy(g_ph);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_handle_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets the sticker data handle using URI.
 */
int utc_sticker_data_get_handle_n(void)
{
    sticker_data_h tmp_handle = NULL;
    int ret = sticker_data_get_handle("", &tmp_handle);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_data_get_handle_n2
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets the sticker data handle using URI.
 */
int utc_sticker_data_get_handle_n2(void)
{
    sticker_data_h tmp_handle = NULL;
    int ret = sticker_data_get_handle("www.invalid.com", &tmp_handle);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NO_SUCH_FILE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}