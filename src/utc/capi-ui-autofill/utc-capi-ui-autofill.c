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
#include <autofill.h>
#include <glib.h>
#include <app_common.h>

//& set: CapiUi-autofill

#define VIEW_ID "login"

autofill_h g_autofill_h = NULL;

static GMainLoop *g_mainloop = NULL;
static char *g_app_id = NULL;
static bool g_connected = false;

static void connect_status_changed_cb(autofill_h ah, autofill_connection_status_e status, void* user_data)
{
    if (status == AUTOFILL_CONNECTION_STATUS_CONNECTED)
        g_connected = true;

    if (g_mainloop) {
        g_main_loop_quit(g_mainloop);
        g_mainloop = NULL;
    }
}

static void auth_info_cb(autofill_h ah, autofill_auth_info_h auth_info, void *user_data)
{

}

static void fill_response_cb(autofill_h ah, autofill_fill_response_h fill_response_h, void *user_data)
{

}

static void error_info_cb(autofill_h ah, autofill_error_info_h error_info, void *user_data)
{

}

/**
 * @function        utc_capi_ui_autofill_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_ui_autofill_startup(void)
{
    app_get_id(&g_app_id);
    autofill_create(&g_autofill_h);
}

/**
 * @function        utc_capi_ui_autofill_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_ui_autofill_cleanup(void)
{
    if (g_app_id) {
        free(g_app_id);
        g_app_id = NULL;
    }

    if (g_autofill_h) {
        autofill_destroy(g_autofill_h);
    }

    g_autofill_h = NULL;
}

/**
 * @function        utc_autofill_create_p
 * @description     Positive UTC of the function that creates autofill handle
 * @parameter       NA
 */
int utc_autofill_create_p(void)
{
    autofill_h ah = NULL;
    int ret = autofill_create(&ah);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @function        utc_autofill_create_n
 * @description     Negative UTC of the function that creates autofill handle
 * @parameter       NA
 */
int utc_autofill_create_n(void)
{
    int ret = autofill_create(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @function        utc_autofill_destroy_p
 * @description     Positive UTC of the function that destroys autofill handle
 * @parameter       NA
 */
int utc_autofill_destroy_p(void)
{
    autofill_h ah = NULL;
    int ret = autofill_create(&ah);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    ret = autofill_destroy(ah);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @function        utc_autofill_destroy_n
 * @description     Negative UTC of the function that destroys autofill handle
 * @parameter       NA
 */
int utc_autofill_destroy_n(void)
{
    int ret = autofill_destroy(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_connect_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that connects to autofill daemon.
 */
int utc_autofill_connect_p(void)
{
    g_connected = false;

    int ret = autofill_connect(g_autofill_h, connect_status_changed_cb, NULL);

    g_mainloop = g_main_loop_new(NULL, false);
    g_main_loop_run(g_mainloop);

    assert_eq(ret, AUTOFILL_ERROR_NONE);
    assert_eq(g_connected, true);

    return 0;
}

/**
 * @testcase        utc_autofill_connect_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that connects to autofill daemon.
 */
int utc_autofill_connect_n(void)
{
    int ret = autofill_connect(NULL, NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_request_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sends authentication information.
 */
int utc_autofill_auth_info_request_p(void)
{
    int ret = AUTOFILL_ERROR_NONE;
    autofill_view_info_h vi_h;
    autofill_item_h ai_h;

    ret = autofill_connect(g_autofill_h, connect_status_changed_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    g_mainloop = g_main_loop_new(NULL, false);
    g_main_loop_run(g_mainloop);

    autofill_view_info_create(&vi_h);
    if (g_app_id)
        autofill_view_info_set_app_id(vi_h, g_app_id);

    autofill_view_info_set_view_id(vi_h, VIEW_ID);

    // create autofill item
    autofill_item_create(&ai_h);
    autofill_item_set_autofill_hint(ai_h, AUTOFILL_HINT_NAME);
    autofill_item_set_id(ai_h, "id");
    autofill_item_set_label(ai_h, "label");
    autofill_item_set_sensitive_data(ai_h, false);

    autofill_view_info_add_item(vi_h, ai_h);

    ret = autofill_auth_info_request(g_autofill_h, vi_h);

    autofill_view_info_destroy(vi_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_request_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sends authentication information.
 */
int utc_autofill_auth_info_request_n(void)
{
    int ret = autofill_auth_info_request(NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_received_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets auth info received callback.
 */
int utc_autofill_auth_info_set_received_cb_p(void)
{
    int ret = autofill_auth_info_set_received_cb(g_autofill_h, auth_info_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_set_received_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets auth info received callback.
 */
int utc_autofill_auth_info_set_received_cb_n(void)
{
    int ret = autofill_auth_info_set_received_cb(NULL, auth_info_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_unset_received_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that unsets auth info received callback.
 */
int utc_autofill_auth_info_unset_received_cb_p(void)
{
    int ret = autofill_auth_info_unset_received_cb(g_autofill_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_auth_info_unset_received_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that unsets auth info received callback.
 */
int utc_autofill_auth_info_unset_received_cb_n(void)
{
    int ret = autofill_auth_info_unset_received_cb(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_error_info_set_received_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets error info received callback.
 */
int utc_autofill_error_info_set_received_cb_p(void)
{
    int ret = autofill_error_info_set_received_cb(g_autofill_h, error_info_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_error_info_set_received_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets error info received callback.
 */
int utc_autofill_error_info_set_received_cb_n(void)
{
    int ret = autofill_error_info_set_received_cb(NULL, error_info_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_error_info_unset_received_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that unsets error info received callback.
 */
int utc_autofill_error_info_unset_received_cb_p(void)
{
    int ret = autofill_error_info_unset_received_cb(g_autofill_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_error_info_unset_received_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that unsets error info received callback.
 */
int utc_autofill_error_info_unset_received_cb_n(void)
{
    int ret = autofill_error_info_unset_received_cb(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_request_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sends fill request.
 */
int utc_autofill_fill_request_p(void)
{
    int ret = AUTOFILL_ERROR_NONE;
    autofill_view_info_h vi_h;
    autofill_item_h ai_h;

    ret = autofill_connect(g_autofill_h, connect_status_changed_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    g_mainloop = g_main_loop_new(NULL, false);
    g_main_loop_run(g_mainloop);

    autofill_view_info_create(&vi_h);
    if (g_app_id)
        autofill_view_info_set_app_id(vi_h, g_app_id);

    autofill_view_info_set_view_id(vi_h, VIEW_ID);

    // create autofill item
    autofill_item_create(&ai_h);
    autofill_item_set_autofill_hint(ai_h, AUTOFILL_HINT_NAME);
    autofill_item_set_id(ai_h, "id");
    autofill_item_set_label(ai_h, "label");
    autofill_item_set_sensitive_data(ai_h, false);

    autofill_view_info_add_item(vi_h, ai_h);

    ret = autofill_fill_request(g_autofill_h, vi_h);

    autofill_view_info_destroy(vi_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_request_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sends fill request.
 */
int utc_autofill_fill_request_n(void)
{
    int ret = autofill_fill_request(NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_cancel_fill_request_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that cancels fill request.
 */
int utc_autofill_cancel_fill_request_p(void)
{
    int ret = AUTOFILL_ERROR_NONE;
    autofill_view_info_h vi_h;
    autofill_item_h ai_h;

    ret = autofill_connect(g_autofill_h, connect_status_changed_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    g_mainloop = g_main_loop_new(NULL, false);
    g_main_loop_run(g_mainloop);

    autofill_view_info_create(&vi_h);
    if (g_app_id)
        autofill_view_info_set_app_id(vi_h, g_app_id);

    autofill_view_info_set_view_id(vi_h, VIEW_ID);

    // create autofill item
    autofill_item_create(&ai_h);
    autofill_item_set_autofill_hint(ai_h, AUTOFILL_HINT_NAME);
    autofill_item_set_id(ai_h, "id");
    autofill_item_set_label(ai_h, "label");
    autofill_item_set_sensitive_data(ai_h, false);

    autofill_view_info_add_item(vi_h, ai_h);

    ret = autofill_cancel_fill_request(g_autofill_h, vi_h);

    autofill_view_info_destroy(vi_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_cancel_fill_request_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that cancels fill request.
 */
int utc_autofill_cancel_fill_request_n(void)
{
    int ret = autofill_cancel_fill_request(NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_set_received_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets fill response received callback.
 */
int utc_autofill_fill_response_set_received_cb_p(void)
{
    int ret = autofill_fill_response_set_received_cb(g_autofill_h, fill_response_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_set_received_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets fill response received callback.
 */
int utc_autofill_fill_response_set_received_cb_n(void)
{
    int ret = autofill_fill_response_set_received_cb(NULL, NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_unset_received_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that unsets fill response received callback.
 */
int utc_autofill_fill_response_unset_received_cb_p(void)
{
    int ret = autofill_fill_response_unset_received_cb(g_autofill_h);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_fill_response_unset_received_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that unsets fill response received callback.
 */
int utc_autofill_fill_response_unset_received_cb_n(void)
{
    int ret = autofill_fill_response_unset_received_cb(NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_commit_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sends commit for saving autofill data.
 */
int utc_autofill_commit_p(void)
{
    int ret = AUTOFILL_ERROR_NONE;
    autofill_save_view_info_h vi_h;
    autofill_save_item_h si_h;

    ret = autofill_connect(g_autofill_h, connect_status_changed_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    g_mainloop = g_main_loop_new(NULL, false);
    g_main_loop_run(g_mainloop);

    autofill_save_view_info_create(&vi_h);
    if (g_app_id)
        autofill_save_view_info_set_app_id(vi_h, g_app_id);

    autofill_save_view_info_set_view_id(vi_h, VIEW_ID);

    // create autofill item for save
    autofill_save_item_create(&si_h);
    autofill_save_item_set_autofill_hint(si_h, AUTOFILL_HINT_NAME);
    autofill_save_item_set_id(si_h, "id");
    autofill_save_item_set_label(si_h, "label");
    autofill_save_item_set_sensitive_data(si_h, false);
    autofill_save_item_set_value(si_h, "MyID");

    autofill_save_view_info_add_item(vi_h, si_h);

    ret = autofill_commit(g_autofill_h, vi_h);

    autofill_save_view_info_destroy(vi_h);

    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_commit_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sends commit for saving autofill data.
 */
int utc_autofill_commit_n(void)
{
    int ret = AUTOFILL_ERROR_NONE;

    ret = autofill_commit(NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}
