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
#include <autofill_service.h>

#define APP_ID "org.tizen.autofill-test"
#define VIEW_ID "login"

//& set: CapiUi-autofill-service

static void auth_info_requested_cb(int context_id, autofill_view_info_h vi, void *user_data)
{

}

static void fill_requested_cb(int context_id, autofill_view_info_h vi, void *user_data)
{

}

static void cancel_fill_requested_cb(int context_id, autofill_view_info_h vi, void *user_data)
{

}

static void committed_cb(int context_id, autofill_save_view_info_h vi, void *user_data)
{

}

static void terminate_received_cb(void *user_data)
{

}

/**
 * @function        utc_capi_ui_autofill_service_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_ui_autofill_service_startup(void)
{
	autofill_service_initialize();
}

/**
 * @function        utc_capi_ui_autofill_service_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_ui_autofill_service_cleanup(void)
{
	autofill_service_deinitialize();
}

/**
 * @testcase        utc_autofill_service_initialize_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that initializes autofill service.
 */
int utc_autofill_service_initialize_p(void)
{
    autofill_service_deinitialize();

    int ret = autofill_service_initialize();
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_service_deinitialize_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that deinitializes autofill service.
 */
int utc_autofill_service_deinitialize_p(void)
{
    int ret = autofill_service_deinitialize();
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    autofill_service_initialize();

    return 0;
}

/**
 * @testcase        utc_autofill_service_set_auth_info_requested_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets authentication infomation request received callback.
 */
int utc_autofill_service_set_auth_info_requested_cb_p(void)
{
    int ret = autofill_service_set_auth_info_requested_cb(auth_info_requested_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_service_set_auth_info_requested_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets authentication infomation request received callback.
 */
int utc_autofill_service_set_auth_info_requested_cb_n(void)
{
    int ret = autofill_service_set_auth_info_requested_cb(NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_service_unset_auth_info_requested_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that unsets authentication infomation request received callback.
 */
int utc_autofill_service_unset_auth_info_requested_cb_p(void)
{
    int ret = autofill_service_unset_auth_info_requested_cb();
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_service_send_auth_info_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sends authentication information.
 */
int utc_autofill_service_send_auth_info_cb_n(void)
{
    autofill_auth_info_h auth_info;
    autofill_auth_info_create(&auth_info);
    autofill_auth_info_set_app_id(auth_info, APP_ID);
    autofill_auth_info_set_view_id(auth_info, VIEW_ID);

    autofill_auth_info_set_autofill_data_present(auth_info, true);
    autofill_auth_info_set_authentication_needed(auth_info, true);
    autofill_auth_info_set_service_name(auth_info, "Tizen autofill service");
    autofill_auth_info_set_service_message(auth_info, "Login with Tizen autofill service");
    autofill_auth_info_set_service_logo_image_path(auth_info, "/usr/app/org.tizen.autofill-service/logo.png");

    int ret = autofill_service_send_auth_info(0, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    autofill_auth_info_destroy(auth_info);

    return 0;
}

/**
 * @testcase        utc_autofill_service_set_fill_requested_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets fill request received callback.
 */
int utc_autofill_service_set_fill_requested_cb_p(void)
{
    int ret = autofill_service_set_fill_requested_cb(fill_requested_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_service_set_fill_requested_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets fill request received callback.
 */
int utc_autofill_service_set_fill_requested_cb_n(void)
{
    int ret = autofill_service_set_fill_requested_cb(NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_service_unset_fill_requested_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that unsets fill request received callback.
 */
int utc_autofill_service_unset_fill_requested_cb_p(void)
{
    int ret = autofill_service_unset_fill_requested_cb();
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_service_set_cancel_fill_requested_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets the callback for the cancelation of fill request.
 */
int utc_autofill_service_set_cancel_fill_requested_cb_p(void)
{
    int ret = autofill_service_set_cancel_fill_requested_cb(cancel_fill_requested_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_service_set_cancel_fill_requested_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets the callback for the cancelation of fill request.
 */
int utc_autofill_service_set_cancel_fill_requested_cb_n(void)
{
    int ret = autofill_service_set_cancel_fill_requested_cb(NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_service_unset_cancel_fill_requested_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that unsets fill request received callback.
 */
int utc_autofill_service_unset_cancel_fill_requested_cb_p(void)
{
    int ret = autofill_service_unset_cancel_fill_requested_cb();
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_service_send_fill_response_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sends fill response.
 */
int utc_autofill_service_send_fill_response_n(void)
{
    int ret = autofill_service_send_fill_response(0, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_service_send_error_info_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sends authentication information.
 */
int utc_autofill_service_send_error_info_cb_n(void)
{
    int ret = autofill_service_send_error_info(0, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_service_set_committed_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets commit callback.
 */
int utc_autofill_service_set_committed_cb_p(void)
{
    int ret = autofill_service_set_committed_cb(committed_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_service_set_committed_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets commit callback.
 */
int utc_autofill_service_set_committed_cb_n(void)
{
    int ret = autofill_service_set_committed_cb(NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_service_unset_committed_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that unsets commit callback.
 */
int utc_autofill_service_unset_committed_cb_p(void)
{
    int ret = autofill_service_unset_committed_cb();
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_service_set_terminate_received_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets terminate received callback.
 */
int utc_autofill_service_set_terminate_received_cb_p(void)
{
    int ret = autofill_service_set_terminate_received_cb(terminate_received_cb, NULL);
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_autofill_service_set_terminate_received_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets terminate received callback.
 */
int utc_autofill_service_set_terminate_received_cb_n(void)
{
    int ret = autofill_service_set_terminate_received_cb(NULL, NULL);
    assert_eq(ret, AUTOFILL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_autofill_service_unset_terminate_received_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that unsets terminate received callback.
 */
int utc_autofill_service_unset_terminate_received_cb_p(void)
{
    int ret = autofill_service_unset_terminate_received_cb();
    assert_eq(ret, AUTOFILL_ERROR_NONE);

    return 0;
}