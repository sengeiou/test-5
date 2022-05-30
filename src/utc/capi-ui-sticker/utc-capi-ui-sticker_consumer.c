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
#include <glib.h>
#include <stdbool.h>
#include <system_info.h>
#include <sticker_data.h>
#include <sticker_provider.h>
#include <sticker_consumer.h>

#define STICKER_FEATURE "tizen.org/feature/ui_service.sticker"

static bool sticker_supported = false;
static bool callback_result = false;
static sticker_data_h g_dh = NULL;
static sticker_provider_h g_ph = NULL;
static sticker_consumer_h g_ch = NULL;
GMainLoop *async_g_loop = NULL;

static void sticker_data_foreach_cb(sticker_data_h data_handle, void *user_data)
{
    callback_result = true;
}

static void group_list_foreach_cb(const char *group, void *user_data)
{
    callback_result = true;
}

static void keyword_list_foreach_cb(const char *keyword, void *user_data)
{
    callback_result = true;
}

static void event_cb(sticker_consumer_event_type_e event_type, sticker_data_h data_handle, void *user_data)
{
    callback_result = true;
}

static void foreach_to_check_del(sticker_data_h data_handle, void *user_data)
{
    sticker_provider_delete_data(g_ph, data_handle);
}

static gboolean timeout_func(gpointer data)
{
    g_main_loop_quit((GMainLoop *) data);
    return false;
}

static void wait_for_async()
{
    int t_id = 0;
    async_g_loop = g_main_loop_new(NULL, FALSE);
    t_id = g_timeout_add(5000, timeout_func, async_g_loop);
    g_main_loop_run(async_g_loop);
    g_source_remove(t_id);
    g_main_loop_unref(async_g_loop);
    async_g_loop = NULL;
}

static void group_image_list_foreach_cb(const char *group, sticker_data_uri_type_e type, const char *uri, void *user_data)
{
    callback_result = true;
}

/**
 * @function		utc_capi_ui_sticker_consumer_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_ui_sticker_consumer_startup(void)
{
    if (!system_info_get_platform_bool(STICKER_FEATURE, &sticker_supported)) {
        if (sticker_supported != true)
            fprintf(stderr, "This device is not support Sticker API.\n");
    }

    if (sticker_supported == true) {
        sticker_consumer_create(&g_ch);
        sticker_provider_create(&g_ph);
        sticker_data_create(&g_dh);
        sticker_data_set_uri(g_dh, STICKER_DATA_URI_WEB_RESOURCE, "www.samsung.com");
        sticker_data_add_keyword(g_dh, "smile");
        sticker_data_add_keyword(g_dh, "face");
        sticker_data_add_keyword(g_dh, "cute");
        sticker_data_set_group_name(g_dh, "tizen");
        sticker_data_set_thumbnail(g_dh, "/res/test.png");
        sticker_data_set_description(g_dh, "TCT Test");
        sticker_data_set_display_type(g_dh, STICKER_DATA_DISP_WALLPAPER);
        sticker_provider_insert_data(g_ph, g_dh);
        sticker_provider_set_group_image(g_ph, "tizen", STICKER_DATA_URI_WEB_RESOURCE, "www.valid.com/test/test.png");
    }
}

/**
 * @function		utc_capi_ui_sticker_consumer_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_ui_sticker_consumer_cleanup(void)
{
    if (sticker_supported == true) {
        int result;
        sticker_provider_data_foreach_all(g_ph, 0, 1000, &result, foreach_to_check_del, NULL);
        sticker_provider_destroy(g_ph);
        sticker_data_destroy(g_dh);
        sticker_consumer_destroy(g_ch);
        g_ph = NULL;
        g_dh = NULL;
        g_ch = NULL;
    }
}


/**
 * @testcase        utc_sticker_consumer_create_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that creates sticker consumer handle.
 */
int utc_sticker_consumer_create_p(void)
{
    sticker_consumer_h consumer_handle = NULL;
    int ret = sticker_consumer_create(&consumer_handle);
    if (sticker_supported == true) {
        assert_eq(ret, STICKER_ERROR_NONE);
        sticker_consumer_destroy(consumer_handle);
        consumer_handle = NULL;
    } else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_create_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that creates sticker consumer handle.
 */
int utc_sticker_consumer_create_n(void)
{
    int ret = sticker_consumer_create(NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_destroy_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that destroys sticker consumer handle.
 */
int utc_sticker_consumer_destroy_p(void)
{
    sticker_consumer_h consumer_handle = NULL;
    int ret = sticker_consumer_create(&consumer_handle);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    ret = sticker_consumer_destroy(consumer_handle);
    consumer_handle = NULL;
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_destroy_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that destroys sticker consumer handle.
 */
int utc_sticker_consumer_destroy_n(void)
{
    int ret = sticker_consumer_destroy(NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_data_foreach_all_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieves all sticker data.
 */
int utc_sticker_consumer_data_foreach_all_p(void)
{
    int result = 0;
    callback_result = false;
    int ret = sticker_consumer_data_foreach_all(g_ch, 0, 1000, &result, sticker_data_foreach_cb, NULL);
    if (sticker_supported == true) {
        assert_eq(callback_result, true);
        assert_eq(ret, STICKER_ERROR_NONE);
    }
    else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_data_foreach_all_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieves all sticker data.
 */
int utc_sticker_consumer_data_foreach_all_n(void)
{
    int result = 0;
    int ret = sticker_consumer_data_foreach_all(g_ch, -1, 0, &result, sticker_data_foreach_cb, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_data_foreach_by_keyword_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieves all sticker data using keyword.
 */
int utc_sticker_consumer_data_foreach_by_keyword_p(void)
{
    int result = 0;
    callback_result = false;
    int ret = sticker_consumer_data_foreach_by_keyword(g_ch, 0, 1000, &result, "cute", sticker_data_foreach_cb, NULL);
    if (sticker_supported == true) {
        assert_eq(callback_result, true);
        assert_eq(ret, STICKER_ERROR_NONE);
    }
    else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_data_foreach_by_keyword_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieves all sticker data using keyword.
 */
int utc_sticker_consumer_data_foreach_by_keyword_n(void)
{
    int result = 0;
    int ret = sticker_consumer_data_foreach_by_keyword(g_ch, -1, 0, &result, "cute", sticker_data_foreach_cb, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_data_foreach_by_group_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieves all sticker data using group.
 */
int utc_sticker_consumer_data_foreach_by_group_p(void)
{
    int result = 0;
    callback_result = false;
    int ret = sticker_consumer_data_foreach_by_group(g_ch, 0, 1000, &result, "tizen", sticker_data_foreach_cb, NULL);
    if (sticker_supported == true) {
        assert_eq(callback_result, true);
        assert_eq(ret, STICKER_ERROR_NONE);
    }
    else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_data_foreach_by_group_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieves all sticker data using group.
 */
int utc_sticker_consumer_data_foreach_by_group_n(void)
{
    int result = 0;
    int ret = sticker_consumer_data_foreach_by_group(g_ch, -1, 0, &result, "tizen", sticker_data_foreach_cb, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_data_foreach_by_type_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieves all sticker data using type.
 */
int utc_sticker_consumer_data_foreach_by_type_p(void)
{
    int result = 0;
    callback_result = false;
    int ret = sticker_consumer_data_foreach_by_type(g_ch, 0, 1000, &result, STICKER_DATA_URI_WEB_RESOURCE, sticker_data_foreach_cb, NULL);
    if (sticker_supported == true) {
        assert_eq(callback_result, true);
        assert_eq(ret, STICKER_ERROR_NONE);
    }
    else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_data_foreach_by_type_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieves all sticker data using type.
 */
int utc_sticker_consumer_data_foreach_by_type_n(void)
{
    int result = 0;
    int ret = sticker_consumer_data_foreach_by_type(g_ch, -1, 0, &result, STICKER_DATA_URI_WEB_RESOURCE, sticker_data_foreach_cb, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_group_list_foreach_all_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieves all group name.
 */
int utc_sticker_consumer_group_list_foreach_all_p(void)
{
    callback_result = false;
    int ret = sticker_consumer_group_list_foreach_all(g_ch, group_list_foreach_cb, NULL);
    if (sticker_supported == true) {
        assert_eq(callback_result, true);
        assert_eq(ret, STICKER_ERROR_NONE);
    }
    else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_group_list_foreach_all_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieves all group name.
 */
int utc_sticker_consumer_group_list_foreach_all_n(void)
{
    int ret = sticker_consumer_group_list_foreach_all(g_ch, NULL, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_keyword_list_foreach_all_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieves all keyword.
 */
int utc_sticker_consumer_keyword_list_foreach_all_p(void)
{
    callback_result = false;
    int ret = sticker_consumer_keyword_list_foreach_all(g_ch, keyword_list_foreach_cb, NULL);
    if (sticker_supported == true) {
        assert_eq(callback_result, true);
        assert_eq(ret, STICKER_ERROR_NONE);
    }
    else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_keyword_list_foreach_all_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieves all keyword.
 */
int utc_sticker_consumer_keyword_list_foreach_all_n(void)
{
    int ret = sticker_consumer_keyword_list_foreach_all(g_ch, NULL, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_data_foreach_by_display_type_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieves all sticker data using display type.
 */
int utc_sticker_consumer_data_foreach_by_display_type_p(void)
{
    int result = 0;
    callback_result = false;
    int ret = sticker_consumer_data_foreach_by_display_type(g_ch, 0, 1000, &result, STICKER_DATA_DISP_WALLPAPER, sticker_data_foreach_cb, NULL);
    if (sticker_supported == true) {
        assert_eq(callback_result, true);
        assert_eq(ret, STICKER_ERROR_NONE);
    }
    else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_data_foreach_by_display_type_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieves all sticker data using display type.
 */
int utc_sticker_consumer_data_foreach_by_display_type_n(void)
{
    int result = 0;
    int ret = sticker_consumer_data_foreach_by_display_type(g_ch, -1, 0, &result, STICKER_DATA_DISP_WALLPAPER, sticker_data_foreach_cb, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_group_list_foreach_by_display_type_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieves all group name using display type.
 */
int utc_sticker_consumer_group_list_foreach_by_display_type_p(void)
{
    callback_result = false;
    int ret = sticker_consumer_group_list_foreach_by_display_type(g_ch, STICKER_DATA_DISP_WALLPAPER, group_list_foreach_cb, NULL);
    if (sticker_supported == true) {
        assert_eq(callback_result, true);
        assert_eq(ret, STICKER_ERROR_NONE);
    }
    else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_group_list_foreach_by_display_type_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieves all group name using display type.
 */
int utc_sticker_consumer_group_list_foreach_by_display_type_n(void)
{
    int ret = sticker_consumer_group_list_foreach_by_display_type(g_ch, STICKER_DATA_DISP_WALLPAPER, NULL, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_add_recent_data_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that adds entry to recently used stickers list.
 */
int utc_sticker_consumer_add_recent_data_p(void)
{
    int ret = sticker_consumer_add_recent_data(g_ch, g_dh);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_add_recent_data_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that adds entry to recently used stickers list.
 */
int utc_sticker_consumer_add_recent_data_n(void)
{
    int ret = sticker_consumer_add_recent_data(g_ch, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_get_recent_data_list_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets recently used stickers list.
 */
int utc_sticker_consumer_get_recent_data_list_p(void)
{
    int result = 0;
    callback_result = false;
    sticker_consumer_add_recent_data(g_ch, g_dh);
    int ret = sticker_consumer_get_recent_data_list(g_ch, 1, &result, sticker_data_foreach_cb, NULL);
    if (sticker_supported == true) {
        assert_eq(callback_result, true);
        assert_eq(ret, STICKER_ERROR_NONE);
    }
    else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_get_recent_data_list_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets recently used stickers list.
 */
int utc_sticker_consumer_get_recent_data_list_n(void)
{
    int result = 0;
    int ret = sticker_consumer_get_recent_data_list(g_ch, 0, &result, sticker_data_foreach_cb, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_set_event_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that registers a event callback function.
 */
int utc_sticker_consumer_set_event_cb_p(void)
{
    callback_result = false;
    int ret = sticker_consumer_set_event_cb(g_ch, event_cb, NULL);
    if (sticker_supported == true) {
        assert_eq(ret, STICKER_ERROR_NONE);
    } else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
        return 0;
    }

    sticker_provider_delete_data(g_ph, g_dh);
    wait_for_async();
    assert_eq(callback_result, true);
    sticker_consumer_unset_event_cb(g_ch);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_set_event_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that registers a event callback function.
 */
int utc_sticker_consumer_set_event_cb_n(void)
{
    int ret = sticker_consumer_set_event_cb(g_ch, NULL, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_unset_event_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that unregisters a event callback function.
 */
int utc_sticker_consumer_unset_event_cb_p(void)
{
    sticker_consumer_set_event_cb(g_ch, event_cb, NULL);
    int ret = sticker_consumer_unset_event_cb(g_ch);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_unset_event_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that unregisters a event callback function.
 */
int utc_sticker_consumer_unset_event_cb_n(void)
{
    int ret = sticker_consumer_unset_event_cb(NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_group_image_list_foreach_all_p
 * @since_tizen     6.5
 * @description     Positive UTC of the function that retrieves images of all sticker groups.
 */
int utc_sticker_consumer_group_image_list_foreach_all_p(void)
{
    int result = 0;
    callback_result = false;
    int ret = sticker_consumer_group_image_list_foreach_all(g_ch, group_image_list_foreach_cb, NULL);
    if (sticker_supported == true) {
        assert_eq(callback_result, true);
        assert_eq(ret, STICKER_ERROR_NONE);
    }
    else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_consumer_group_image_list_foreach_all_n
 * @since_tizen     6.5
 * @description     Negative UTC of the function that retrieves images of all sticker groups.
 */
int utc_sticker_consumer_group_image_list_foreach_all_n(void)
{
    int ret = sticker_consumer_group_image_list_foreach_all(g_ch, NULL, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}