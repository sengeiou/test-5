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

#define STICKER_FEATURE "tizen.org/feature/ui_service.sticker"
#define TIMEOUT_CB 15000

GMainLoop *g_MainLoop;
int g_nTimeoutId;
static bool sticker_supported = false;
static bool callback_result = false;
static sticker_data_h g_dh = NULL;
static sticker_provider_h g_ph = NULL;

gboolean TimeoutFunction(gpointer data)
{
    GMainLoop *pMainLoop = NULL;
    pMainLoop = (GMainLoop *)data;
    if (pMainLoop != NULL)
        g_main_loop_quit(pMainLoop);

    return false;
}

#define RUN_POLLING_LOOP { \
    if (callback_result == false) { \
        g_MainLoop = g_main_loop_new(NULL, false); \
        g_nTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, g_MainLoop); \
        g_main_loop_run(g_MainLoop); \
        g_source_remove(g_nTimeoutId); \
        g_MainLoop = NULL; \
        g_nTimeoutId = 0; \
    } \
}

#define QUIT_GMAIN_LOOP { \
    if (g_MainLoop) { \
        g_main_loop_quit(g_MainLoop); \
        g_MainLoop = NULL; \
    } \
}

static void insert_finished_cb(sticker_error_e error, void *user_data)
{
    callback_result = true;
    QUIT_GMAIN_LOOP;
}

static void negative_insert_finished_cb(sticker_error_e error, void *user_data)
{
}

static void sticker_data_foreach_cb(sticker_data_h data_handle, void *user_data)
{
    callback_result = true;
}

static void foreach_to_check_del(sticker_data_h data_handle, void *user_data)
{
    sticker_provider_delete_data(g_ph, data_handle);
}

/**
 * @function		utc_capi_ui_sticker_provider_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_ui_sticker_provider_startup(void)
{
    if (!system_info_get_platform_bool(STICKER_FEATURE, &sticker_supported)) {
        if (sticker_supported != true)
            fprintf(stderr, "This device is not support Sticker API.\n");
    }

    if (sticker_supported == true) {
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
    }
}

/**
 * @function		utc_capi_ui_sticker_provider_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_ui_sticker_provider_cleanup(void)
{
    if (sticker_supported == true) {
        int result;
        sticker_provider_data_foreach_all(g_ph, 0, 1000, &result, foreach_to_check_del, NULL);
        sticker_provider_destroy(g_ph);
        sticker_data_destroy(g_dh);
        g_ph = NULL;
        g_dh = NULL;
    }
}


/**
 * @testcase        utc_sticker_provider_create_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that creates sticker provider handle.
 */
int utc_sticker_provider_create_p(void)
{
    sticker_provider_h provider_handle = NULL;
    int ret = sticker_provider_create(&provider_handle);
    if (sticker_supported == true) {
        assert_eq(ret, STICKER_ERROR_NONE);
        sticker_provider_destroy(provider_handle);
        provider_handle = NULL;
    } else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_provider_create_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that creates sticker provider handle.
 */
int utc_sticker_provider_create_n(void)
{
    int ret = sticker_provider_create(NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_destroy_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that destroys sticker provider handle.
 */
int utc_sticker_provider_destroy_p(void)
{
    sticker_provider_h provider_handle = NULL;
    int ret = sticker_provider_create(&provider_handle);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    ret = sticker_provider_destroy(provider_handle);
    provider_handle = NULL;
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_destroy_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that destroys sticker provider handle.
 */
int utc_sticker_provider_destroy_n(void)
{
    int ret = sticker_provider_destroy(NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_insert_data_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that inserts sticker data to database.
 */
int utc_sticker_provider_insert_data_p(void)
{
    int ret = sticker_provider_insert_data(g_ph, g_dh);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_insert_data_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that inserts sticker data to database.
 */
int utc_sticker_provider_insert_data_n(void)
{
    int ret = sticker_provider_insert_data(g_ph, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_insert_data_by_json_file_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that inserts sticker data by json file.
 */
int utc_sticker_provider_insert_data_by_json_file_p(void)
{
    char *json_path = "/res/test.json";
    callback_result = false;
    int ret = sticker_provider_insert_data_by_json_file(g_ph, json_path, insert_finished_cb, NULL);
    if (sticker_supported == true) {
        assert_eq(ret, STICKER_ERROR_NONE);
        RUN_POLLING_LOOP;
        assert_eq(callback_result, true);
    } else {
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_sticker_provider_insert_data_by_json_file_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that inserts sticker data by json file.
 */
int utc_sticker_provider_insert_data_by_json_file_n(void)
{
    int ret = sticker_provider_insert_data_by_json_file(g_ph, NULL, NULL, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_insert_data_by_json_file_n2
 * @since_tizen     5.5
 * @description     Negative UTC of the function that inserts sticker data by json file.
 */
int utc_sticker_provider_insert_data_by_json_file_n2(void)
{
    char *json_path = "/res/negative_test.json";
    int ret = sticker_provider_insert_data_by_json_file(g_ph, json_path, negative_insert_finished_cb, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_update_data_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that updates sticker data.
 */
int utc_sticker_provider_update_data_p(void)
{
    sticker_provider_insert_data(g_ph, g_dh);
    sticker_data_set_group_name(g_dh, "Samsung");
    int ret = sticker_provider_update_data(g_ph, g_dh);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_update_data_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that updates sticker data.
 */
int utc_sticker_provider_update_data_n(void)
{
    sticker_data_h temp_handle = NULL;
    sticker_data_create(&temp_handle);
    int ret = sticker_provider_update_data(g_ph, temp_handle);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    sticker_data_destroy(temp_handle);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_delete_data_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that deletes sticker data.
 */
int utc_sticker_provider_delete_data_p(void)
{
    sticker_provider_insert_data(g_ph, g_dh);
    int ret = sticker_provider_delete_data(g_ph, g_dh);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_delete_data_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that deletes sticker data.
 */
int utc_sticker_provider_delete_data_n(void)
{
    sticker_data_h temp_handle = NULL;
    sticker_data_create(&temp_handle);
    int ret = sticker_provider_delete_data(g_ph, temp_handle);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    sticker_data_destroy(temp_handle);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_get_sticker_count_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that gets the count of stickers stored by tct application.
 */
int utc_sticker_provider_get_sticker_count_p(void)
{
    int count = -1;
    int ret = sticker_provider_get_sticker_count(g_ph, &count);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_get_sticker_count_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that gets the count of stickers stored by tct application.
 */
int utc_sticker_provider_get_sticker_count_n(void)
{
    int ret = sticker_provider_get_sticker_count(g_ph, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_data_foreach_all_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that retrieves all sticker data stored by tct application.
 */
int utc_sticker_provider_data_foreach_all_p(void)
{
    int result = 0;
    callback_result = false;
    sticker_provider_insert_data(g_ph, g_dh);
    int ret = sticker_provider_data_foreach_all(g_ph, 0, 1000, &result, sticker_data_foreach_cb, NULL);
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
 * @testcase        utc_sticker_provider_data_foreach_all_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that retrieves all sticker data stored by tct application.
 */
int utc_sticker_provider_data_foreach_all_n(void)
{
    int result = 0;
    int ret = sticker_provider_data_foreach_all(g_ph, -1, 0, &result, sticker_data_foreach_cb, NULL);
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_delete_data_by_uri_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that deletes a sticker data using URI.
 */
int utc_sticker_provider_delete_data_by_uri_p(void)
{
    sticker_provider_insert_data(g_ph, g_dh);
    int ret = sticker_provider_delete_data_by_uri(g_ph, "www.samsung.com");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_delete_data_by_uri_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that deletes a sticker data using URI.
 */
int utc_sticker_provider_delete_data_by_uri_n(void)
{
    int ret = sticker_provider_delete_data_by_uri(NULL, "");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_delete_data_by_uri_n2
 * @since_tizen     5.5
 * @description     Negative UTC of the function that deletes a sticker data using URI.
 */
int utc_sticker_provider_delete_data_by_uri_n2(void)
{
    int ret = sticker_provider_delete_data_by_uri(g_ph, "www.invalid.com");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NO_SUCH_FILE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_set_group_image_p
 * @since_tizen     6.5
 * @description     Positive UTC of the function that sets group image.
 */
int utc_sticker_provider_set_group_image_p(void)
{
    sticker_provider_insert_data(g_ph, g_dh);
    int ret = sticker_provider_set_group_image(g_ph, "tizen", STICKER_DATA_URI_WEB_RESOURCE, "www.valid.com/test/image.png");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NONE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_set_group_image_n
 * @since_tizen     6.5
 * @description     Negative UTC of the function that sets group image.
 */
int utc_sticker_provider_set_group_image_n(void)
{
    int ret = sticker_provider_set_group_image(g_ph, "invalid", STICKER_DATA_URI_WEB_RESOURCE, "www.valid.com/test/image.png");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_INVALID_PARAMETER);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_sticker_provider_set_group_image_n2
 * @since_tizen     6.5
 * @description     Negative UTC of the function that sets group image.
 */
int utc_sticker_provider_set_group_image_n2(void)
{
    sticker_provider_insert_data(g_ph, g_dh);
    int ret = sticker_provider_set_group_image(g_ph, "tizen", STICKER_DATA_URI_LOCAL_PATH, "/test/test.png");
    if (sticker_supported == true)
        assert_eq(ret, STICKER_ERROR_NO_SUCH_FILE);
    else
        assert_eq(ret, STICKER_ERROR_NOT_SUPPORTED);

    return 0;
}