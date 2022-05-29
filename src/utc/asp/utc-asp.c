//
// Copyright (c) 2017 Samsung Electronics Co., Ltd.
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
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <asp.h>
#include <system_info.h>

#include "assert.h"
static bool g_asp_supported = false;

void utc_seek_search_result_cb(int error_code,
                               asp_seek_service_h seek_service,
                               const char *service_mac,
                               unsigned int adv_id,
                               asp_wps_type_e config_method,
                               const char *instance_name,
                               const char *service_info,
                               int info_size,
                               unsigned char status,
                               void *user_data)
{
	return;
}

void utc_advert_status_changed_cb(asp_advert_service_h adv_service,
                                  asp_service_status_e status,
                                  asp_advert_status_reason_e reason,
                                  void *user_data)
{
	return;
}

void utc_session_request_cb(int error_code,
                            asp_advert_service_h adv_service,
                            asp_session_h session,
                            const char *device_name,
                            const char *info,
                            int info_size,
                            bool get_network_config_pin,
                            const char *network_config_pin,
                            void *user_data)
{
	return;
}

void utc_session_config_request_cb(int error_code,
                                   asp_session_h session,
                                   bool get_pin,
                                   const char *config_pin,
                                   void *user_data)
{
	return;
}

void utc_session_connect_status_cb(int error_code,
                                   asp_session_h session,
                                   asp_connect_status_e status,
                                   const char *deferred_resp,
                                   int resp_size,
                                   void *user_data)
{
	return;
}

void utc_session_status_cb(int error_code,
                           asp_session_h session,
                           asp_session_state_e state,
                           const char *additional_info,
                           void *user_data)
{
	return;
}

void utc_session_port_status_cb(int error_code,
                                asp_session_h session,
                                const char *ip_address,
                                int port,
                                int proto,
                                asp_port_status_e status,
                                void *user_data)
{
	return;
}

//& set: Asp

/**
 * @function		utc_asp_startup
 * @since_tizen		4.0
 * @description		Initializes ASP.Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_asp_startup(void)
{
	system_info_get_platform_bool("http://tizen.org/feature/network.asp", &g_asp_supported);
	asp_initialize();
}

/**
 * @function		utc_asp_cleanup
 * @since_tizen		4.0
 * @description		Deinitializes ASP.Called after each test.
 * @parameter		NA
 * @return			NA
 */
void utc_asp_cleanup(void)
{
	asp_deinitialize();
}


/**
 * @testcase		utc_asp_initialize_p
 * @since_tizen		4.0
 * @type			Positive
 * @description		Initializes ASP library.
 * @scenario		Initialize ASP. If alreay initialized, deinitialize and initialize again.
 */
int utc_asp_initialize_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_initialize();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_initialize();
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_initialize_n
 * @since_tizen		4.0
 * @type			Negative
 * @description		Initializes ASP library.
 * @scenario		Initialize ASP consecutively.Ensure return value should be ASP_ERROR_ALREADY_INITIALIZED.
 */
int utc_asp_initialize_n(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_initialize();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_initialize();
	assert_eq(ret, ASP_ERROR_ALREADY_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_deinitialize_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Deinitializes ASP.
 * @scenario		Deinitialize ASP and ensure ASP is Deinitialized properly.Ensure no error.
 */
int utc_asp_deinitialize_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_deinitialize();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_deinitialize();
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_deinitialize_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_deinitialize by calling it twice.
 * @scenario		Deinitialize ASP repeatedly and ensure no unexpected behaviour.
 *					Ensure ASP_ERROR_NOT_INITIALIZED error is reported
 */
int utc_asp_deinitialize_n(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_deinitialize();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_deinitialize();
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}


/**
 * @testcase		utc_asp_seek_set_search_result_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Register seek_search_result_cb.
 * @scenario		Register seek_search_result_cb and ensure no error.
 */
int utc_asp_seek_set_search_result_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_seek_set_search_result_cb(utc_seek_search_result_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_set_search_result_cb(utc_seek_search_result_cb, NULL);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_seek_set_search_result_cb_n1
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register NULL pointer in callback.
 * @scenario		Register NULL pointer in callback and ensure proper
 *			error is returned.
 */
int utc_asp_seek_set_search_result_cb_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_seek_set_search_result_cb(NULL, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_set_search_result_cb(NULL, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_seek_set_search_result_cb_n2
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register callback without initialize.
 * @scenario		Register callback without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_seek_set_search_result_cb_n2(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_seek_set_search_result_cb(utc_seek_search_result_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_seek_set_search_result_cb(utc_seek_search_result_cb, NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_seek_unset_search_result_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Deregister seek_search_result_cb.
 * @scenario		Deregister seek_search_result_cb and ensure no error.
 */
int utc_asp_seek_unset_search_result_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_seek_unset_search_result_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_unset_search_result_cb();
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_seek_unset_search_result_cb_n
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Deregister search_result_cb without initialize.
 * @scenario		Deregister search_result_cb without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_seek_unset_search_result_cb_n(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_seek_unset_search_result_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_seek_unset_search_result_cb();
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_status_changed_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Register advert_status_changed_cb.
 * @scenario		Register advert_status_changed_cb and ensure no error.
 */
int utc_asp_advert_set_status_changed_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_advert_set_status_changed_cb(utc_advert_status_changed_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_status_changed_cb(utc_advert_status_changed_cb, NULL);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_status_changed_cb_n1
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register NULL pointer in callback.
 * @scenario		Register NULL pointer in callback and ensure proper
 *			error is returned.
 */
int utc_asp_advert_set_status_changed_cb_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_advert_set_status_changed_cb(NULL, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_status_changed_cb(NULL, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_status_changed_cb_n2
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register callback without initialize.
 * @scenario		Register callback without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_advert_set_status_changed_cb_n2(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_advert_set_status_changed_cb(utc_advert_status_changed_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_set_status_changed_cb(utc_advert_status_changed_cb, NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_advert_unset_status_changed_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Deregister advertise_status_changed_cb.
 * @scenario		Deregister advertise_status_changed_cb and ensure no error.
 */
int utc_asp_advert_unset_status_changed_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_advert_unset_status_changed_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_unset_status_changed_cb();
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_unset_status_changed_cb_n
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Deregister advert_status_changed_cb without initialize.
 * @scenario		Deregister advert_status_changed_cb without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_advert_unset_status_changed_cb_n(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_advert_unset_status_changed_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_unset_status_changed_cb();
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_request_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Register session_request_cb.
 * @scenario		Register session_request_cb and ensure no error.
 */
int utc_asp_session_set_request_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_request_cb(utc_session_request_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_request_cb(utc_session_request_cb, NULL);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_request_cb_n1
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register NULL pointer in callback.
 * @scenario		Register NULL pointer in callback and ensure proper
 *			error is returned.
 */
int utc_asp_session_set_request_cb_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_request_cb(NULL, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_request_cb(NULL, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_request_cb_n2
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register callback without initialize.
 * @scenario		Register callback without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_session_set_request_cb_n2(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_request_cb(utc_session_request_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_set_request_cb(utc_session_request_cb, NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_unset_request_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Deregister session_request_cb.
 * @scenario		Deregister session_request_cb and ensure no error.
 */
int utc_asp_session_unset_request_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_unset_request_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_unset_request_cb();
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_unset_request_cb_n
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Deregister session_request_cb without initialize.
 * @scenario		Deregister session_request_cb without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_session_unset_request_cb_n(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_unset_request_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_unset_request_cb();
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_config_request_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Register session_config_request_cb.
 * @scenario		Register session_config_request_cb and ensure no error.
 */
int utc_asp_session_set_config_request_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_config_request_cb(utc_session_config_request_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_config_request_cb(utc_session_config_request_cb, NULL);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_config_request_cb_n1
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register NULL pointer in callback.
 * @scenario		Register NULL pointer in callback and ensure proper
 *			error is returned.
 */
int utc_asp_session_set_config_request_cb_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_config_request_cb(NULL, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_config_request_cb(NULL, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_config_request_cb_n2
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register callback without initialize.
 * @scenario		Register callback without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_session_set_config_request_cb_n2(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_config_request_cb(utc_session_config_request_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_set_config_request_cb(utc_session_config_request_cb, NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_unset_config_request_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Deregister session_config_request_cb.
 * @scenario		Deregister session_config_request_cb and ensure no error.
 */
int utc_asp_session_unset_config_request_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_unset_config_request_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_unset_config_request_cb();
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_unset_config_request_cb_n
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Deregister session_config_request_cb without initialize.
 * @scenario		Deregister session_config_request_cb without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_session_unset_config_request_cb_n(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_unset_config_request_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_unset_config_request_cb();
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_connect_status_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Register session_connect_status_cb.
 * @scenario		Register session_connect_status_cb and ensure no error.
 */
int utc_asp_session_set_connect_status_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_connect_status_cb(utc_session_connect_status_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_connect_status_cb(utc_session_connect_status_cb, NULL);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_connect_status_cb_n1
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register NULL pointer in callback.
 * @scenario		Register NULL pointer in callback and ensure proper
 *			error is returned.
 */
int utc_asp_session_set_connect_status_cb_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_connect_status_cb(NULL, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_connect_status_cb(NULL, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_connect_status_cb_n2
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register callback without initialize.
 * @scenario		Register callback without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_session_set_connect_status_cb_n2(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_connect_status_cb(utc_session_connect_status_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_set_connect_status_cb(utc_session_connect_status_cb, NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_unset_connect_status_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Deregister connect_status_cb.
 * @scenario		Deregister connect_status_cb and ensure no error.
 */
int utc_asp_session_unset_connect_status_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_unset_connect_status_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_unset_connect_status_cb();
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_unset_connect_status_cb_n
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Deregister connect_status_cb without initialize.
 * @scenario		Deregister connect_status_cb without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_session_unset_connect_status_cb_n(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_unset_connect_status_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_unset_connect_status_cb();
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_status_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Register session_status_cb.
 * @scenario		Register session_status_cb and ensure no error.
 */
int utc_asp_session_set_status_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_status_cb(utc_session_status_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_status_cb(utc_session_status_cb, NULL);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_status_cb_n1
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register NULL pointer in callback.
 * @scenario		Register NULL pointer in callback and ensure proper
 *			error is returned.
 */
int utc_asp_session_set_status_cb_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_status_cb(NULL, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_status_cb(NULL, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_status_cb_n2
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register callback without initialize.
 * @scenario		Register callback without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_session_set_status_cb_n2(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_status_cb(utc_session_status_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_set_status_cb(utc_session_status_cb, NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_unset_status_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Deregister session_status_cb.
 * @scenario		Deregister session_status_cb and ensure no error.
 */
int utc_asp_session_unset_status_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_unset_status_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_unset_status_cb();
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_unset_status_cb_n
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Deregister session_status_cb without initialize.
 * @scenario		Deregister session_status_cb without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_session_unset_status_cb_n(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_unset_status_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_unset_status_cb();
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_port_status_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Register port_status_cb.
 * @scenario		Register port_status_cb and ensure no error.
 */
int utc_asp_session_set_port_status_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_port_status_cb(utc_session_port_status_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_port_status_cb(utc_session_port_status_cb, NULL);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_port_status_cb_n1
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register NULL pointer in callback.
 * @scenario		Register NULL pointer in callback and ensure proper
 *			error is returned.
 */
int utc_asp_session_set_port_status_cb_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_port_status_cb(NULL, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_port_status_cb(NULL, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_port_status_cb_n2
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Register callback without initialize.
 * @scenario		Register callback without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_session_set_port_status_cb_n2(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_port_status_cb(utc_session_port_status_cb, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_set_port_status_cb(utc_session_port_status_cb, NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_unset_port_status_cb_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description 	Deregister port_status_cb.
 * @scenario		Deregister port_status_cb and ensure no error.
 */
int utc_asp_session_unset_port_status_cb_p(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_unset_port_status_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_unset_port_status_cb();
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_unset_port_status_cb_n
 * @since_tizen 	4.0
 * @type		Negative
 * @description 	Deregister port_status_cb without initialize.
 * @scenario		Deregister port_status_cb without initialize and ensure proper
 *			error is returned.
 */
int utc_asp_session_unset_port_status_cb_n(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_unset_port_status_cb();
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_unset_port_status_cb();
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}


/**
 * @function		utc_asp_advert_create_p
 * @since_tizen		4.0
 * @description		Creates the Description of a service to be advertised
 * @scenario		Initialize the ASP & create the advertise handler.
 */
int utc_asp_advert_create_p(void)
{
	int ret = ASP_ERROR_NONE;
	asp_advert_service_h local_advert = NULL;
	char *instance_name = "SinkDisplay";

	if(g_asp_supported == false) {
		ret = asp_advert_create(instance_name, &local_advert);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_create(instance_name, &local_advert);
	assert_eq(ret, ASP_ERROR_NONE);

	asp_advert_destroy(local_advert);

	return 0;

}

/**
 * @function		utc_asp_advert_create_n1
 * @since_tizen		4.0
 * @description		Verify asp_advert_create() by passing the Null pointer in handler
 * @scenario		Call the asp_advert_create()function by passing Null pointer
 *					and ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int  utc_asp_advert_create_n1(void)
{
	int ret = ASP_ERROR_NONE;
	char *instance_name = "SinkDisplay";

	if(g_asp_supported == false) {
		ret = asp_advert_create(instance_name, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_create(instance_name, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_create_n2
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify asp_advert_create() without initialize the ASP
 * @scenario		Call the asp_advert_create()function without initialize the ASP
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_create_n2(void)
{
	int ret = ASP_ERROR_NONE;
	asp_advert_service_h local_advert = NULL;
	char *instance_name = "SinkDisplay";

	if(g_asp_supported == false) {
		ret = asp_advert_create(instance_name, &local_advert);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_create(instance_name, &local_advert);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @function		utc_asp_advert_destroy_p
 * @since_tizen		4.0
 * @type			Positive
 * @description		Destroys the Description of a service to be advertised
 * @scenario		Initialize the ASP, create the Session handler & then destroy the session.
 */
int  utc_asp_advert_destroy_p(void)
{
	int ret = ASP_ERROR_NONE;
	asp_advert_service_h local_advert = NULL;
	char *instance_name = "SinkDisplay";

	if(g_asp_supported == false) {
		ret = asp_advert_destroy(local_advert);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_create(instance_name, &local_advert);
	assert_eq(ret, ASP_ERROR_NONE);

	ret = asp_advert_destroy(local_advert);
	assert_eq(ret, ASP_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_asp_advert_destroy_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_destroy() without initialize the ASP
 * @scenario		Call the asp_advert_destroy()function without initialize the ASP
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_destroy_n1(void)
{
	int ret = ASP_ERROR_NONE;
	asp_advert_service_h local_advert = NULL;

	if(g_asp_supported == false) {
		ret = asp_advert_destroy(local_advert);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();

	ret = asp_advert_destroy(local_advert);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_advert_destroy_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_destory_advertise_handle() with NULL handler
 * @scenario		Call the asp_destory_advertise_handle()function with NULL handler
 *					and ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_destroy_n2(void)
{
	int ret = ASP_ERROR_NONE;
	asp_advert_service_h local_advert = NULL;

	if(g_asp_supported == false) {
		ret = asp_advert_destroy(local_advert);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_destroy(local_advert);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}


/**
 * @testcase		utc_asp_advert_destroy_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_destroy by calling it twice.
 * @scenario		Destroy the advertise handler repeatedly and ensure no unexpected behaviour.
 *					Ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported
 */
int  utc_asp_advert_destroy_n3(void)
{
	int ret = ASP_ERROR_NONE;
	asp_advert_service_h local_advert = NULL;
	char *instance_name = "SinkDisplay";

	if(g_asp_supported == false) {
		ret = asp_advert_destroy(local_advert);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_create(instance_name, &local_advert);
	assert_eq(ret, ASP_ERROR_NONE);

	ret = asp_advert_destroy(local_advert);
	assert_eq(ret, ASP_ERROR_NONE);

	ret = asp_advert_destroy(local_advert);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);

	return 0;
}

/**
 * @function		utc_asp_seek_create_p
 * @since_tizen		4.0
 * @description		Creates the local Application Service Platform(ASP) seek handler
 * @scenario		Initialize the ASP & create the seek handler.
 */
int  utc_asp_seek_create_p(void)
{
	asp_seek_service_h local_seek = NULL;
	char *service_type = "Display";
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_seek_create(service_type, &local_seek);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}
	ret = asp_seek_create(service_type, &local_seek);
	assert_eq(ret, ASP_ERROR_NONE);

	asp_seek_destroy(local_seek);

	return 0;
}

/**
 * @testcase		utc_asp_seek_create_n1
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify asp_seek_create() without initialize the ASP
 * @scenario		Call the asp_seek_create()function without initialize the ASP
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_seek_create_n1(void)
{
	asp_seek_service_h local_seek = NULL;
	int ret = ASP_ERROR_NONE;
	char *service_type = "Display";

	if(g_asp_supported == false) {
		ret = asp_seek_create(service_type, &local_seek);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();

	ret = asp_seek_create(service_type, &local_seek);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}


/**
 * @function		utc_asp_seek_create_n2
 * @since_tizen		4.0
 * @description		Verify asp_seek_create() by passing the Service type as NULL
 * @scenario		Call the asp_seek_create()function by passing Null address
 *					and ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int  utc_asp_seek_create_n2(void)
{
	asp_seek_service_h local_seek = NULL;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_seek_create(NULL, &local_seek);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_create(NULL, &local_seek);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @function		utc_asp_seek_create_n3
 * @since_tizen		4.0
 * @description		Verify asp_seek_create() by passing the Null pointer in handler
 * @scenario		Call the asp_seek_create()function by passing Null pointer
 *					and ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int  utc_asp_seek_create_n3(void)
{
	int ret = ASP_ERROR_NONE;
	char *service_type = "Display";

	if(g_asp_supported == false) {
		ret = asp_seek_create(service_type, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_create(service_type, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @function		utc_asp_seek_destroy_p
 * @since_tizen		4.0
 * @type			Positive
 * @description		Destroys the Description of a service to be advertised
 * @scenario		Initialize the ASP, create the seek handler & then destroy the seek handle.
 */
int  utc_asp_seek_destroy_p(void)
{
	asp_seek_service_h local_seek = NULL;
	char *service_type = "Display";
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_seek_create(service_type, &local_seek);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_create(service_type, &local_seek);
	assert_eq(ret, ASP_ERROR_NONE);

	asp_seek_destroy(local_seek);
	assert_eq(ret, ASP_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_asp_destroy_seek_handle_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_seek_destroy() without initialize the ASP
 * @scenario		Call the asp_seek_destroy()function without initialize the ASP
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_seek_destroy_n1(void)
{
	asp_seek_service_h local_seek = NULL;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_seek_destroy(local_seek);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_seek_destroy(local_seek);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_destroy_seek_handle_n2
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify asp_seek_destroy() with NULL handler
 * @scenario		Destroy the seek handler  with NULL handler.
 *					Ensure ASP_ERROR_INVALID_PARAMETER error is reported
 */
int  utc_asp_seek_destroy_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_seek_destroy(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_destroy(NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_seek_destroy_n3
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify asp_destroy_seek_handle by calling it twice.
 * @scenario		Destroy the seek handler repeatedly and ensure no unexpected behaviour.
 *					Ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported
 */
int  utc_asp_seek_destroy_n3(void)
{
	asp_seek_service_h local_seek = NULL;
	char *service_type = "Display";
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_seek_destroy(local_seek);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_create(service_type, &local_seek);
	assert_eq(ret, ASP_ERROR_NONE);

	ret = asp_seek_destroy(local_seek);
	assert_eq(ret, ASP_ERROR_NONE);

	ret = asp_seek_destroy(local_seek);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @function		utc_asp_session_create_p
 * @since_tizen		4.0
 * @description		Creates the local Application Service Platform(ASP) session handler
 * @scenario		Initialize the ASP & create the Session handler.
 */
int  utc_asp_session_create_p(void)
{
	asp_session_h local_session = NULL;
	char *session_mac = "00:11:22:33:44:55";
	int adv_id = 0x01;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_create(session_mac, adv_id, &local_session);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_create(session_mac, adv_id, &local_session);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;

}

/**
 * @testcase		utc_asp_session_create_n1
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify asp_session_create() without initialize the ASP
 * @scenario		Call the asp_session_create()function without initialize the ASP
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_create_n1(void)
{
	asp_session_h local_session = NULL;
	char *session_mac = "00:11:22:33:44:55";
	int adv_id = 0x01;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_create(session_mac, adv_id, &local_session);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_create(session_mac, adv_id, &local_session);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @function		utc_asp_session_create_n2
 * @since_tizen		4.0
 * @description		Verify asp_session_create() by passing the Null address
 * @scenario		Call the asp_session_create()function by passing Null address
 *					and ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_create_n2(void)
{
	asp_session_h local_session = NULL;
	char *session_mac = NULL;
	int adv_id = 0x01;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_create(session_mac, adv_id, &local_session);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_create(session_mac, adv_id, &local_session);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @function		utc_asp_session_create_n3
 * @since_tizen		4.0
 * @description		Verify asp_session_create() by passing the zero in adv_id
 * @scenario		Call the asp_session_create()function by passing invalid value
 *					and ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_create_n3(void)
{
	asp_session_h local_session = NULL;
	char *session_mac = "00:11:22:33:44:55";
	int adv_id = 0;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_create(session_mac, adv_id, &local_session);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_create(session_mac, adv_id, &local_session);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @function		utc_asp_session_create_n4
 * @since_tizen		4.0
 * @description		Verify asp_session_create() by passing the Null pointer in handler
 * @scenario		Call the asp_session_create()function by passing Null pointer
 *					and ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_create_n4(void)
{
	char *session_mac = "00:11:22:33:44:55";
	int adv_id = 0x01;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_create(session_mac, adv_id, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_create(session_mac, adv_id, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @function		utc_asp_session_destroy_p
 * @since_tizen		4.0
 * @type			Positive
 * @description		Destroys the local Application Service Platform(ASP) session handler
 * @scenario		Initialize the ASP, create the Session handler & then destroy the session.
 */
int  utc_asp_session_destroy_p(void)
{
	asp_session_h local_session = NULL;
	char *session_mac = "00:11:22:33:44:55";
	int adv_id = 0x01;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_destroy(local_session);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_create(session_mac, adv_id, &local_session);
	assert_eq(ret, ASP_ERROR_NONE);

	ret = asp_session_destroy(local_session);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_destroy_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_destroy_session_handler() without initialize the ASP
 * @scenario		Call the asp_destroy_session_handler()function without initialize the ASP
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_destroy_n1(void)
{
	asp_session_h local_session = NULL;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_destroy(local_session);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_destroy(local_session);
    assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
    return 0;
}

/**
 * @testcase		utc_asp_session_destroy_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_destroy_session_handler() with NULL
 * @scenario		Call the asp_destroy_session_handler()function with NULL
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_destroy_n2(void)
{
	asp_session_h local_session = NULL;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_destroy(local_session);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_destroy(local_session);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_destroy_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_destroy_session_handler by calling it twice.
 * @scenario		Destroy the session handler repeatedly and ensure no unexpected behavior.
 *					Ensure ASP_ERROR_OPERATION_FAILED error is reported
 */
int  utc_asp_session_destroy_n3(void)
{
	asp_session_h local_session = NULL;
	char *session_mac = "00:11:22:33:44:55";
	int adv_id = 0x01;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_destroy(local_session);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_create(session_mac, adv_id, &local_session);
	assert_eq(ret, ASP_ERROR_NONE);

	asp_session_destroy(local_session);
	assert_eq(ret, ASP_ERROR_NONE);

	ret = asp_session_destroy(local_session);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);

	return 0;
}

/**
 * @testcase		utc_asp_advert_set_service_type_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_service_type() without initialize
 * @scenario		Call the asp_advert_set_service_type() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_set_service_type_n(void)
{
	char *service_type = "Display";
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_set_service_type(NULL, service_type);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_set_service_type(NULL, service_type);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_auto_accept_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_auto_accept() without initialize
 * @scenario		Call the asp_advert_set_auto_accept() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_set_auto_accept_n(void)
{
	bool auto_accept = false;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_set_auto_accept(NULL, auto_accept);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_set_auto_accept(NULL, auto_accept);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_advert_add_info_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_discovery_tech() without initialize
 * @scenario		Call the asp_advert_set_discovery_tech() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_add_info_n(void)
{
	char *key = "<hdcp,mode>";
	char *value = "<2,dual>";
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_add_info(NULL, key, value);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_add_info(NULL, key, value);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_get_info_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_get_info() without initialize
 * @scenario		Call the asp_advert_get_info() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_get_info_n(void)
{
	char *key = "<hdcp,mode>";
	char *value = NULL;
	int length;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_get_info(NULL, key, &length, &value);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_get_info(NULL, key, &length, &value);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_remove_info_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_remove_info() without initialize
 * @scenario		Call the asp_advert_remove_info() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_remove_info_n(void)
{
	char *key = "<hdcp,mode>";
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_remove_info(NULL, key);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_remove_info(NULL, key);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_status_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_status() without initialize
 * @scenario		Call the asp_advert_set_status() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_set_status_n(void)
{
	unsigned char status = 0;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_set_status(NULL, status);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_set_status(NULL, status);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_discovery_tech_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_discovery_tech() without initialize
 * @scenario		Call the asp_advert_set_discovery_tech() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_set_discovery_tech_n(void)
{
	int tech = ASP_DISCOVERY_TECH_P2P;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_set_discovery_tech(NULL, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_set_discovery_tech(NULL, tech);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_preferred_connection_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_preferred_connection() without initialize
 * @scenario		Call the asp_advert_set_preferred_connection() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_set_preferred_connection_n(void)
{
	int preferred_connection = 1;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_set_preferred_connection(NULL, preferred_connection);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_set_preferred_connection(NULL, preferred_connection);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_role_scheme_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_p2p_role_scheme() without initialize
 * @scenario		Call the asp_advert_set_p2p_role_scheme() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_set_p2p_role_scheme_n(void)
{
	unsigned char role = 0;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_role_scheme(NULL, role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_set_p2p_role_scheme(NULL, role);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_advert_get_p2p_role_scheme_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_get_p2p_role_scheme() without initialize
 * @scenario		Call the asp_advert_get_p2p_role_scheme() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_get_p2p_role_scheme_n(void)
{
	asp_advert_p2p_role_scheme_e role = 0;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_get_p2p_role_scheme(NULL, &role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_get_p2p_role_scheme(NULL, &role);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_config_method_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_p2p_config_method() without initialize
 * @scenario		Call the asp_advert_set_p2p_config_method() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_set_p2p_config_method_n(void)
{
	unsigned int config_method = ASP_WPS_TYPE_NONE;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_config_method(NULL, config_method);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_set_p2p_config_method(NULL, config_method);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_advert_get_p2p_config_method_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_get_p2p_config_method() without initialize
 * @scenario		Call the asp_advert_get_p2p_config_method() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_get_p2p_config_method_n(void)
{
	unsigned int config_method = ASP_WPS_TYPE_NONE;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_get_p2p_config_method(NULL, &config_method);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_get_p2p_config_method(NULL, &config_method);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_response_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_p2p_response() without initialize
 * @scenario		Call the asp_advert_set_p2p_response() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_advert_set_p2p_response_n(void)
{
	char *service_rsp = "displayservice";
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_response(NULL, service_rsp, strlen(service_rsp));
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_set_p2p_response(NULL, service_rsp, strlen(service_rsp));
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_advert_start_advertising_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_start_advertising() without initialize
 * @scenario		Call the asp_advert_start_advertising() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int  utc_asp_advert_start_advertising_n(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_start_advertising(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_start_advertising(NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_asp_advert_stop_advertising_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_stop_advertising() without initialize
 * @scenario		Call the asp_advert_stop_advertising() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int  utc_asp_advert_stop_advertising_n(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_stop_advertising(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_stop_advertising(NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_asp_advert_change_service_status_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_change_service_status() without initialize
 * @scenario		Call the asp_advert_change_service_status() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int  utc_asp_advert_change_service_status_n(void)
{
	unsigned char status = 0;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_change_service_status(NULL, status);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_advert_change_service_status(NULL, status);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_asp_seek_add_info_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_seek_add_info() without initialize
 * @scenario		Call the asp_seek_add_info() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_seek_add_info_n(void)
{
	char *key = "hdcp=2,mode=dual";
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_seek_add_info(NULL, key);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_seek_add_info(NULL, key);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_seek_remove_info_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_seek_remove_info() without initialize
 * @scenario		Call the asp_seek_remove_info() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_seek_remove_info_n(void)
{
	char *key = "<hdcp,mode>";
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_seek_remove_info(NULL, key);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_seek_remove_info(NULL, key);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_seek_set_discovery_tech_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_seek_set_discovery_tech() without initialize
 * @scenario		Call the asp_seek_set_discovery_tech() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_seek_set_discovery_tech_n(void)
{
	int tech = ASP_DISCOVERY_TECH_P2P;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_seek_set_discovery_tech(NULL, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_seek_set_discovery_tech(NULL, tech);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_seek_set_preferred_connection_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_seek_set_preferred_connection() without initialize
 * @scenario		Call the asp_seek_set_preferred_connection() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_seek_set_preferred_connection_n(void)
{
	int preferred_connection = 1;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_seek_set_preferred_connection(NULL, preferred_connection);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_seek_set_preferred_connection(NULL, preferred_connection);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_seek_start_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_seek_start() without initialize
 * @scenario		Call the asp_seek_start() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int  utc_asp_seek_start_n(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_seek_start(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_seek_start(NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_asp_seek_stop_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_seek_stop() without initialize
 * @scenario		Call the asp_seek_stop() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int  utc_asp_seek_stop_n(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_seek_stop(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_seek_stop(NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_asp_session_get_mac_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_mac() without initialize
 * @scenario		Call the asp_session_get_mac() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_get_mac_n(void)
{
	char *sesion_mac = NULL;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_get_mac(NULL, &sesion_mac);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_get_mac(NULL, &sesion_mac);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_id_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_id() without initialize
 * @scenario		Call the asp_session_get_id() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_get_id_n(void)
{
	unsigned int sesion_id;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_get_id(NULL, &sesion_id);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_get_id(NULL, &sesion_id);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_info_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_set_info() without initialize
 * @scenario		Call the asp_session_set_info() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_set_info_n(void)
{
	char *service_info = "HDCP Enable";
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_set_info(NULL, service_info);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_set_info(NULL, service_info);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_info_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_info() without initialize
 * @scenario		Call the asp_session_get_info() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_get_info_n(void)
{
	char *service_info = NULL;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_get_info(NULL, &service_info);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_get_info(NULL, &service_info);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_p2p_role_scheme_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_set_p2p_role_scheme() without initialize
 * @scenario		Call the asp_session_set_p2p_role_scheme() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_set_p2p_role_scheme_n(void)
{
	int network_role = 1;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_set_p2p_role_scheme(NULL, network_role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_set_p2p_role_scheme(NULL, network_role);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_p2p_role_scheme_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_p2p_role_scheme() without initialize
 * @scenario		Call the asp_session_get_p2p_role_scheme() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_get_p2p_role_scheme_n(void)
{
	asp_advert_p2p_role_scheme_e network_role;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_get_p2p_role_scheme(NULL, &network_role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_get_p2p_role_scheme(NULL, &network_role);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_p2p_config_method_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_set_p2p_config_method() without initialize
 * @scenario		Call the asp_session_set_p2p_config_method() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_set_p2p_config_method_n(void)
{
	asp_wps_type_e network_config = ASP_WPS_TYPE_DEFAULT;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_set_p2p_config_method(NULL, network_config);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_set_p2p_config_method(NULL, network_config);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_destroy_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_p2p_config_method() without initialize
 * @scenario		Call the asp_session_get_p2p_config_method() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_get_p2p_config_method_n(void)
{
	asp_wps_type_e network_config = ASP_WPS_TYPE_DEFAULT;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_get_p2p_config_method(NULL, &network_config);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_get_p2p_config_method(NULL, &network_config);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_close_status_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_close_status() without initialize
 * @scenario		Call the asp_session_get_close_status() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_get_close_status_n(void)
{
	int close_status;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_get_close_status(NULL, &close_status);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_get_close_status(NULL, &close_status);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_connect_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_connect() without initialize
 * @scenario		Call the asp_session_connect() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_connect_n(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_connect(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_connect(NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_confirm_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_confirm() without initialize
 * @scenario		Call the asp_session_confirm() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_confirm_n(void)
{
	bool confirm = true;
	char *pin = "12345678";
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_confirm(NULL, confirm, pin);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_confirm(NULL, confirm, pin);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_handle_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_handle() without initialize
 * @scenario		Call the asp_session_get_handle() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_get_handle_n(void)
{
	unsigned int id = 1;
	char *mac_addr = "AA:BB:CC:DD:EE:FF";
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_get_handle(mac_addr, id, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_get_handle(mac_addr, id, NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_state_ready_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_set_state_ready() without initialize
 * @scenario		Call the asp_session_set_state_ready() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_set_state_ready_n(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_set_state_ready(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_set_state_ready(NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_close_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_close() without initialize
 * @scenario		Call the asp_session_close() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_close_n(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_close(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_close(NULL);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_bind_port_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_bind_port() without initialize
 * @scenario		Call the asp_session_bind_port() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_bind_port_n(void)
{
	char *ip = "192.168.0.1";
	int port = 12345;
	int proto = 80;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_bind_port(NULL, ip, port, proto);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_bind_port(NULL, ip, port, proto);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_asp_session_release_port_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_release_port() without initialize
 * @scenario		Call the asp_session_release_port() without initialize
 *					and ensure ASP_ERROR_NOT_INITIALIZED error is reported.
 */
int utc_asp_session_release_port_n(void)
{
	char *ip = "192.168.0.1";
	int port = 12345;
	int proto = 80;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_release_port(NULL, ip, port, proto);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	asp_deinitialize();
	ret = asp_session_release_port(NULL, ip, port, proto);
	assert_eq(ret, ASP_ERROR_NOT_INITIALIZED);
	return 0;
}
