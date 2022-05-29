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
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net_connection.h>
#include <system_info.h>
#include <http.h>
#include <dlog.h>

#define FREE_RESOURCE(var)\
	if (var != NULL) {\
		g_free(var);\
		var = NULL;\
	}

#define INVALID_URL "http://www."

http_session_h session = NULL;
http_transaction_h transaction = NULL;

static GMainLoop *g_pMainLoop;
static int g_CallbackRet = HTTP_ERROR_NONE;
static bool is_init = false;
#ifdef WEARABLE
static bool g_internet_supported = true;
#endif
static bool g_use_proxy = false;

void __transaction_header_cb(http_transaction_h transaction, char *header, size_t header_len, void *user_data)
{
}

void __transaction_body_cb(http_transaction_h transaction, char *body, size_t size, size_t nmemb, void *user_data)
{
}

void __transaction_write_cb(http_transaction_h transaction, int recommended_chunk_size, void *user_data)
{
}

void __transaction_completed_cb(http_transaction_h transaction, void *user_data)
{
	int ret;
	http_status_code_e status_code = 0;
	char *status_text;
	http_version_e version;

	ret = http_transaction_response_get_status_code(transaction, &status_code);
	ret = http_transaction_response_get_status_text(transaction, &status_text);
	ret = http_transaction_response_get_version(transaction, &version);

	if (status_code < HTTP_STATUS_BAD_REQUEST)
		g_CallbackRet = HTTP_ERROR_NONE;
	else
		g_CallbackRet = HTTP_ERROR_OPERATION_FAILED;

	if (g_pMainLoop)
		g_main_loop_quit(g_pMainLoop);
}

void __transaction_aborted_cb(http_transaction_h transaction, int reason, void *user_data)
{
	g_CallbackRet = reason;

	if (g_pMainLoop)
		g_main_loop_quit(g_pMainLoop);
}

void __transaction_progress_cb(http_transaction_h transaction, double download_total, double download_now, double upload_total, double upload_now, void *user_data)
{
}

void _register_callbacks(http_transaction_h transaction)
{
	http_transaction_set_received_header_cb(transaction, __transaction_header_cb, NULL);
	http_transaction_set_received_body_cb(transaction, __transaction_body_cb, NULL);
	http_transaction_set_uploaded_cb(transaction, __transaction_write_cb, NULL);
	http_transaction_set_completed_cb(transaction, __transaction_completed_cb, NULL);
	http_transaction_set_aborted_cb(transaction, __transaction_aborted_cb, NULL);
}

void _get_proxy_info(void)
{
	connection_h connection = NULL;
	char *proxy_addr = NULL;

	if (connection_create(&connection) < 0)
		return;

	if (connection_get_proxy(connection, CONNECTION_ADDRESS_FAMILY_IPV4, &proxy_addr) < 0)
		return;

	if (proxy_addr) {
		g_use_proxy = true;
		free(proxy_addr);
	}
}

/**
 * @function		utc_network_http_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_http_startup(void)
{
	int ret;

#ifdef WEARABLE
	system_info_get_platform_bool("http://tizen.org/feature/network.internet", &g_internet_supported);
#endif
	_get_proxy_info();

	if (!is_init) {
		ret = http_init();
		if (ret != HTTP_ERROR_NONE)
			fprintf(stderr, "http_init() error at %s:%d\n", __FILE__, __LINE__);

		is_init = true;
	}

	ret = http_session_create(HTTP_SESSION_MODE_NORMAL, &session);
	if (ret != HTTP_ERROR_NONE)
		fprintf(stderr, "http_session_create() error at %s:%d\n", __FILE__, __LINE__);

	if (transaction == NULL) {
		ret = http_session_open_transaction(session, HTTP_METHOD_GET, &transaction);
		if (ret != HTTP_ERROR_NONE)
			fprintf(stderr, "http_session_open_transaction() error at %s:%d\n", __FILE__, __LINE__);
		_register_callbacks(transaction);
	}
}

/**
 * @function		utc_network_http_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_http_cleanup(void)
{
	if (transaction) {
		http_transaction_destroy(transaction);
		transaction = NULL;
	}

	if (session) {
		http_session_destroy(session);
		session = NULL;
	}
}

/**
 * @testcas			utc_http_init_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Initializes the HTTP module.
 * @scenario		Invoking http_init  with invalid parameter.
 */
int utc_http_init_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_init();
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif
	ret = http_init();
	assert_eq(ret, TIZEN_ERROR_INVALID_OPERATION);
	return 0;
}

/**
 * @testcase		utc_http_init_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Initializes the HTTP module.
 * @scenario		Invoking http_init with valid parameter.
 */
int utc_http_init_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_init();
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif
	ret = http_deinit();
	assert_eq(ret, TIZEN_ERROR_NONE);
	ret = http_init();
	assert_eq(ret, TIZEN_ERROR_NONE);

	return 0;
}
/**
 * @testcase		utc_http_sesssion_create_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Creates the Http session handle.
 * @scenario		Invoking http_session_create with valid parameter.
 */
int utc_http_session_create_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_session_create(HTTP_SESSION_MODE_NORMAL, &session);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif
	if (transaction) {
		ret = http_transaction_destroy(transaction);
		assert_eq(ret, HTTP_ERROR_NONE);
		transaction = NULL;
	}

	if (session) {
		ret = http_session_destroy(session);
		assert_eq(ret, HTTP_ERROR_NONE);
		session = NULL;
	}

	ret = http_session_create(HTTP_SESSION_MODE_NORMAL, &session);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (session) {
		ret = http_session_destroy(session);
		assert_eq(ret, HTTP_ERROR_NONE);
		session = NULL;
	}

	ret = http_session_create(HTTP_SESSION_MODE_PIPELINING, &session);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_http_session_create_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Creates the Http session handle..
 * @scenario		Invoking http_session_create with invalid parameter.
 */
int utc_http_session_create_n(void)
{
	int ret;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_session_create(HTTP_SESSION_MODE_NORMAL, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_session_create(HTTP_SESSION_MODE_NORMAL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_session_destroy_n
 * @since_tizen     3.0
 * @type			Negative
 * @description		Destroys the Http session handle.
 * @scenario		Invoking http_session_destroy with invalid parameter.
 */
int utc_http_session_destroy_n(void)
{
	int ret;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_session_destroy(NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_session_destroy(NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_session_destroy_p
 * @since_tizen     3.0
 * @type			Negative
 * @description		Destroys the Http session handle.
 * @scenario		Invoking http_session_destroy with valid parameter.
 */
int utc_http_session_destroy_p(void)
{
	int ret;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_session_destroy(NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_destroy(transaction);
	assert_eq(ret, HTTP_ERROR_NONE);
	transaction = NULL;

	ret = http_session_destroy(session);
	session = NULL;
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_session_set_auto_redirection_n
 * @since_tizen     3.0
 * @type			Negative
 * @description		Sets the value to redirect the HTTP request automatically.
 * @scenario		Invoking http_session_set_auto_redirection with invalid parameter.
 */
int utc_http_session_set_auto_redirection_n(void)
{
	int ret;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_session_set_auto_redirection(NULL, true);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_session_set_auto_redirection(NULL, true);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_session_set_auto_redirection_p
 * @since_tizen     3.0
 * @type			Positive
 * @description		Sets the value to redirect the HTTP request automatically.
 * @scenario		Invoking http_session_set_auto_redirection with valid parameter.
 */
int utc_http_session_set_auto_redirection_p(void)
{
	int ret;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_session_set_auto_redirection(session, true);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_session_set_auto_redirection(session, true);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_session_get_auto_redirection_n
 * @since_tizen     3.0
 * @type			Negative
 * @description		Gets the auto redirection for the HTTP request.
 * @scenario		Invoking http_session_get_auto_redirection with invalid parametner.
 */
int utc_http_session_get_auto_redirection_n(void)
{
	int ret;
	bool auto_redirect;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_session_get_auto_redirection(session, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_session_get_auto_redirection(NULL, &auto_redirect);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_session_get_auto_redirection(session, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_session_get_auto_redirection(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_session_get_auto_redirection_n
 * @since_tizen     3.0
 * @type			Positive
 * @description		Gets the auto redirection for the HTTP request.
 * @scenario		Invoking http_session_get_auto_redirection with valid parametner.
 */
int utc_http_session_get_auto_redirection_p(void)
{
	int ret;
	bool auto_redirect;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_session_get_auto_redirection(session, &auto_redirect);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_session_get_auto_redirection(session, &auto_redirect);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_session_get_active_transaction_count_n
 * @since_tizen     3.0
 * @type			Negative
 * @description		Gets the number of active transactions in the current session.
 * @scenario		Invoking http_seession_get_active_transaction_count with invalid parameter.
 */
int utc_http_session_get_active_transaction_count_n(void)
{
	int ret;
	int cnt;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_session_get_active_transaction_count(session, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_session_get_active_transaction_count(session, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_session_get_active_transaction_count(NULL, &cnt);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_session_get_active_transaction_count(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_session_get_active_transaction_count_p
 * @since_tizen     3.0
 * @type			Positve
 * @description		Gets the number of active transactions in the current session.
 * @scenario		Invoking http_seession_get_active_transaction_count with valid parameter.
 */
int utc_http_session_get_active_transaction_count_p(void)
{
	int ret;
	int cnt;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_session_get_active_transaction_count(session, &cnt);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_session_get_active_transaction_count(session, &cnt);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_session_get_max_transaction_count_n
 * @since_tizen     3.0
 * @type			Negative
 * @description		Gets the maximum number of transactions for the current session.
 * @scenario		Invoking http_session_get_mac_transaction_count with invalid parameter.
 */
int utc_http_session_get_max_transaction_count_n(void)
{
	int ret, cnt;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_session_get_max_transaction_count(session, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_session_get_max_transaction_count(session, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_session_get_max_transaction_count(NULL, &cnt);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_session_get_max_transaction_count(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_session_get_max_transaction_count_p
 * @since_tizen     3.0
 * @type			Positive
 * @description		Gets the maximum number of transactions for the current session.
 * @scenario		Invoking http_session_get_mac_transaction_count with valid parameter.
 */
int utc_http_session_get_max_transaction_count_p(void)
{
	int ret;
	int cnt;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_session_get_max_transaction_count(session, &cnt);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_session_get_max_transaction_count(session, &cnt);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}


/**
 * @testcase        utc_http_session_open_transaction_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Opens Http transaction from the Http Session.
 * @scenario		Invoking http_session_open_transaction with invalid parameter.
 */
int utc_http_session_open_transaction_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_session_open_transaction(NULL, HTTP_METHOD_GET, &transaction);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_session_open_transaction(NULL, HTTP_METHOD_GET, &transaction);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_session_open_transaction_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Opens Http transaction from the Http Session.
 * @scenario		Invoking http_session_open_transaction with valid parameter.
 */
int utc_http_session_open_transaction_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_session_open_transaction(session, HTTP_METHOD_GET, &transaction);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	if (transaction) {
		ret = http_transaction_destroy(transaction);
		transaction = NULL;
	}
	ret = http_session_open_transaction(session, HTTP_METHOD_GET, &transaction);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (transaction) {
		ret = http_transaction_destroy(transaction);
		transaction = NULL;
	}
	ret = http_session_open_transaction(session, HTTP_METHOD_OPTIONS, &transaction);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (transaction) {
		ret = http_transaction_destroy(transaction);
		transaction = NULL;
	}
	ret = http_session_open_transaction(session, HTTP_METHOD_HEAD, &transaction);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (transaction) {
		ret = http_transaction_destroy(transaction);
		transaction = NULL;
	}
	ret = http_session_open_transaction(session, HTTP_METHOD_DELETE, &transaction);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (transaction) {
		ret = http_transaction_destroy(transaction);
		transaction = NULL;
	}
	ret = http_session_open_transaction(session, HTTP_METHOD_TRACE, &transaction);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (transaction) {
		ret = http_transaction_destroy(transaction);
		transaction = NULL;
	}
	ret = http_session_open_transaction(session, HTTP_METHOD_POST, &transaction);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (transaction) {
		ret = http_transaction_destroy(transaction);
		transaction = NULL;
	}
	ret = http_session_open_transaction(session, HTTP_METHOD_PUT, &transaction);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (transaction) {
		ret = http_transaction_destroy(transaction);
		transaction = NULL;
	}
	ret = http_session_open_transaction(session, HTTP_METHOD_CONNECT, &transaction);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_destroy_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Closes the http transaction handle.
 * @scenario		Invoking http_transaction_destroy with invalid parameter.
 */
int utc_http_transaction_destroy_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_destroy(NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_destroy(NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_http_transaction_destroy_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Closes the http transaction handle.
 * @scenario		Invoking http_transaction_destroy with valid parameter.
 */
int utc_http_transaction_destroy_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_destroy(transaction);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_destroy(transaction);
	transaction = NULL;
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_progress_cb_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Registers the progress callbacks.
 * @scenario		Invoking http_transaction_set_progress_cb with invalid parameter.
 */
int utc_http_transaction_set_progress_cb_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_set_progress_cb(NULL, __transaction_progress_cb, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_progress_cb(NULL, __transaction_progress_cb, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_set_progress_cb(transaction, NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_progress_cb_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Registers the progress callbacks.
 * @scenario		Invoking http_transaction_set_progress_cb with valid parameter.
 */
int utc_http_transaction_set_progress_cb_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_set_progress_cb(transaction, __transaction_progress_cb, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_progress_cb(transaction, __transaction_progress_cb, NULL);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_received_header_cb_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Registers callback called when receive header.
 * @scenario		Invoking http_transaction_set_received_header_cb with invalid parameter.
 */
int utc_http_transaction_set_received_header_cb_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_received_header_cb(NULL, (http_transaction_header_cb)__transaction_header_cb, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_received_header_cb(NULL, (http_transaction_header_cb)__transaction_header_cb, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_set_received_header_cb(transaction, NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_http_transaction_set_received_header_cb_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Registers callback called when receive header.
 * @scenario		Invoking http_transaction_set_received_header_cb with valid parameter.
 */
int utc_http_transaction_set_received_header_cb_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_received_header_cb(transaction, __transaction_header_cb, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_received_header_cb(transaction, __transaction_header_cb, NULL);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_received_body_cb_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Registers callback called when receive body.
 * @scenario		Invoking http_transaction_set_received_body_cb with invalid parameter.
 */
int utc_http_transaction_set_received_body_cb_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_set_received_body_cb(NULL, __transaction_body_cb, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_received_body_cb(NULL, __transaction_body_cb, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_set_received_body_cb(transaction, NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_http_transaction_set_received_body_cb_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Registers callback called when receive body.
 * @scenario		Invoking http_transaction_set_received_body_cb with valid parameter.
 */
int utc_http_transaction_set_received_body_cb_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_set_received_body_cb(transaction, __transaction_body_cb, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_received_body_cb(transaction, __transaction_body_cb, NULL);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}



/**
 * @testcase        utc_http_transaction_set_uploaded_cb_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Registers callback called when write data.
 * @scenario		Invoking http_transaction_set_uploaded_cb with invalid parameter.
 */
int utc_http_transaction_set_uploaded_cb_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_set_uploaded_cb(NULL, __transaction_write_cb, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_uploaded_cb(NULL, __transaction_write_cb, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_set_uploaded_cb(transaction, NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_http_transaction_set_uploaded_cb_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Registers callback called when write data.
 * @scenario		Invoking http_transaction_set_uploaded_cb with valid parameter.
 */
int utc_http_transaction_set_uploaded_cb_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_set_uploaded_cb(transaction, __transaction_write_cb, NULL);

		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_uploaded_cb(transaction, __transaction_write_cb, NULL);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_completed_cb_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Registers callback called when transaction is completed.
 * @scenario		Invoking http_transaction_set_completed_cb with invalid parameter.
 */
int utc_http_transaction_set_completed_cb_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_set_completed_cb(NULL, __transaction_completed_cb, NULL);

		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_completed_cb(NULL, __transaction_completed_cb, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_set_completed_cb(transaction, NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_http_transaction_set_completed_cb_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Registers callback called when transaction is completed.
 * @scenario		Invoking http_transaction_set_completed_cb with valid parameter.
 */
int utc_http_transaction_set_completed_cb_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_set_completed_cb(transaction, __transaction_completed_cb, NULL);

		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_completed_cb(transaction, __transaction_completed_cb, NULL);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_aborted_cb_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Registers callback called when transaction is aborted.
 * @scenario		Invoking http_transaction_set_aborted_cb with invalid parameter.
 */
int utc_http_transaction_set_aborted_cb_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_set_aborted_cb(NULL, __transaction_aborted_cb, NULL);

		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_aborted_cb(NULL, __transaction_aborted_cb, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_set_aborted_cb(transaction, NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_set_aborted_cb(NULL, NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_aborted_cb_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Registers callback called when transaction is aborted.
 * @scenario		Invoking http_transaction_set_aborted_cb with valid parameter.
 */
int utc_http_transaction_set_aborted_cb_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_set_aborted_cb(transaction, __transaction_aborted_cb, NULL);

		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_aborted_cb(transaction, __transaction_aborted_cb, NULL);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_timeout_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Sets the timeout in seconds that is the timeout for waiting the transaction.
 * @scenario		Invoking http_transaction_set_timeout with invalid parameter.
 */
int utc_http_transaction_set_timeout_n(void)
{
	int ret;
	int timeout = 10;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_timeout(NULL, timeout);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_timeout(NULL, timeout);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_timeout_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Sets the timeout in seconds that is the timeout for waiting the transaction.
 * @scenario		Invoking http_transaction_set_timeout with valid parameter.
 */
int utc_http_transaction_set_timeout_p(void)
{
	int ret;
	int timeout = 10;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_timeout(transaction, timeout);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_timeout(transaction, timeout);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_get_timeout_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets the time out in seconds for the transaction.
 * @scenario		Invoking http_transaction_get_timeout with invalid parameter.
 */
int utc_http_transaction_get_timeout_n(void)
{
	int ret;
	int timeout;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_get_timeout(NULL, &timeout);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_get_timeout(NULL, &timeout);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_get_timeout_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Gets the time out in seconds for the transaction.
 * @scenario		Invoking http_transaction_get_timeout with valid parameter.
 */
int utc_http_transaction_get_timeout_p(void)
{
	int ret;
	int timeout;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_get_timeout(transaction, &timeout);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_get_timeout(transaction, &timeout);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_interface_name_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Sets the interface name.
 * @scenario		Invoking http_transaction_set_interface_name with invalid parameter.
 */
int utc_http_transaction_set_interface_name_n(void)
{
	int ret;
	const char interface_name[10] = "wlan0";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_interface_name(transaction, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_interface_name(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_set_interface_name(NULL, interface_name);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_set_interface_name(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_interface_name_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Sets the interface name.
 * @scenario		Invoking http_transaction_set_interface_name with valid parameter.
 */
int utc_http_transaction_set_interface_name_p(void)
{
	int ret;
	const char interface_name[10] = "wlan0";
#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_set_interface_name(transaction, interface_name);

		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_interface_name(transaction, interface_name);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_get_interface_name_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets the interface name.
 * @scenario		Invoking http_transaction_get_interface_name with invalid parameter.
 */
int utc_http_transaction_get_interface_name_n(void)
{
	int ret;
	char *interface_name = NULL;
#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_get_interface_name(NULL, &interface_name);

		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_get_interface_name(NULL, &interface_name);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_get_interface_name_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Gets the interface name.
 * @scenario		Invoking http_transaction_get_interface_name with valid parameter.
 */
int utc_http_transaction_get_interface_name_p(void)
{
	int ret;
	char *interface_name;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_get_interface_name(transaction, &interface_name);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_interface_name(transaction, "test");
	assert_eq(ret, HTTP_ERROR_NONE);
	ret = http_transaction_get_interface_name(transaction, &interface_name);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (interface_name)
		free(interface_name);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_ready_to_write_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Sets ready to write event for a transaction.
 * @scenario		Invoking http_transaction_set_ready_to_write with invalid parameter.
 */
int utc_http_transaction_set_ready_to_write_n(void)
{
	int ret;
	bool ready = true;
#ifdef WEARABLE
	if (g_internet_supported == false) {
	ret = http_transaction_set_ready_to_write(NULL, ready);

		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_ready_to_write(NULL, ready);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_ready_to_write_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Sets ready to write event for a transaction.
 * @scenario		Invoking http_transaction_set_ready_to_write with valid parameter.
 */
int utc_http_transaction_set_ready_to_write_p(void)
{
	int ret;
	bool ready = true;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_ready_to_write(transaction, ready);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_ready_to_write(transaction, ready);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_get_server_certificate_verification_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets the flag to verify a server certificate.
 * @scenario		Invoking http_transaction_get_server_certificate_verification with invalid parameter.
 */
int utc_http_transaction_get_server_certificate_verification_n(void)
{
	int ret;
	bool verify;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_get_server_certificate_verification(NULL, &verify);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_get_server_certificate_verification(NULL, &verify);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_get_server_certificate_verification_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Gets the flag to verify a server certificate.
 * @scenario		Invoking http_transaction_get_server_certificate_verification with valid parameter.
 */
int utc_http_transaction_get_server_certificate_verification_p(void)
{
	int ret;
	bool verify;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_get_server_certificate_verification(transaction, &verify);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_get_server_certificate_verification(transaction, &verify);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_server_certificate_verification_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Sets the flag to verify a server certificate.
 * @scenario		Invoking http_transaction_set_server_certificate_verification with invalid parameter.
 */
int utc_http_transaction_set_server_certificate_verification_n(void)
{
	int ret;
	bool verify = false;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_server_certificate_verification(NULL, verify);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_server_certificate_verification(NULL, verify);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_server_certificate_verification_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Sets the flag to verify a server certificate.
 * @scenario		Invoking http_transaction_set_server_certificate_verification with valid parameter.
 */
int utc_http_transaction_set_server_certificate_verification_p(void)
{
	int ret;
	bool verify = false;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_server_certificate_verification(transaction, verify);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_server_certificate_verification(transaction, verify);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_session_destroy_all_transactions_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Destroys all transaction.
 * @scenario		Invoking http_session_destroy_all_transactions with invalid parameter.
 */
int utc_http_session_destroy_all_transactions_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_session_destroy_all_transactions(NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_session_destroy_all_transactions(NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_session_destroy_all_transactions_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Destroys all transaction.
 * @scenario		Invoking http_session_destroy_all_transactions with valid parameter.
 */
int utc_http_session_destroy_all_transactions_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_session_destroy_all_transactions(session);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_session_destroy_all_transactions(session);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (transaction)
		transaction = NULL;

	return 0;
}

/**
 * @testcase        utc_http_transaction_header_add_field_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Adds a named field to header.
 * @scenario		Invoking http_transaction_header_add_field with invalid parameter.
 */
int utc_http_transaction_header_add_field_n(void)
{
	int ret;
	const char field[20] = "Content-Length";
	const char value[10] = "10";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_header_add_field(transaction, field, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_header_add_field(transaction, field, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_header_add_field(transaction, NULL, value);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_header_add_field(NULL, field, value);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_header_add_field(NULL, NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_header_add_field_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Adds a named field to header.
 * @scenario		Invoking http_transaction_header_add_field with valid parameter.
 */
int utc_http_transaction_header_add_field_p(void)
{
	int ret;
	const char field[20] = "Content-Length";
	const char value[10] = "10";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_header_add_field(transaction, field, value);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_header_add_field(transaction, field, value);
	assert_eq(ret, HTTP_ERROR_NONE);
	return 0;
}

/**
 * @testcase        utc_http_transaction_header_remove_field_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Removes the named field from header.
 * @scenario		Invoking http_transaction_header_remove_field with invalid parameter.
 */
int utc_http_transaction_header_remove_field_n(void)
{
	int ret;
	const char field[20] = "Content-Length";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_header_remove_field(transaction, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_header_remove_field(transaction, field);
	assert_eq(ret, HTTP_ERROR_INVALID_OPERATION);
	ret = http_transaction_header_remove_field(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_header_remove_field(NULL, field);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_header_remove_field(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);


	return 0;
}

/**
 * @testcase        utc_http_transaction_header_remove_field_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Removes the named field from header.
 * @scenario		Invoking http_transaction_header_remove_field with valid parameter.
 */
int utc_http_transaction_header_remove_field_p(void)
{
	int ret;
	const char field[20] = "Content-Length";
	const char value[10] = "10";

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_header_add_field(transaction , field, value);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_header_add_field(transaction , field, value);
	assert_eq(ret, HTTP_ERROR_NONE);
	ret = http_transaction_header_remove_field(transaction, field);
	assert_eq(ret, HTTP_ERROR_NONE);
	return 0;
}

/**
 * @testcase        utc_http_transaction_header_get_field_value_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets the Http Header Field value from custom header.
 * @scenario		Invoking http_transaction_header_get_field_value with invalid parameter.
 */
int utc_http_transaction_header_get_field_value_n(void)
{
	int ret;
	const char field[20] = "Content-Length";
	char *value;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_header_get_field_value(NULL, field, &value);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_header_get_field_value(NULL, field, &value);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_header_get_field_value(transaction, NULL, &value);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_header_get_field_value(NULL, NULL, &value);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_header_get_field_value_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Gets the Http Header Field value from custom header.
 * @scenario		Invoking http_transaction_header_get_field_value with valid parameter.
 */
int utc_http_transaction_header_get_field_value_p(void)
{
	int ret;
	const char field[20] = "Content-Length";
	char *value;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_header_add_field(transaction, field, "10");
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_header_add_field(transaction, field, "10");
	assert_eq(ret, HTTP_ERROR_NONE);
	ret = http_transaction_header_get_field_value(transaction, field, &value);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (value)
		free(value);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_set_method_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Sets an HTTP method of the request header.
 * @scenario		Invoking http_transaction_request_set_method with invalid parameter.
 */
int utc_http_transaction_request_set_method_n(void)
{
	int ret;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_method(NULL, HTTP_METHOD_GET);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_method(NULL, HTTP_METHOD_GET);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_set_method_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Sets an HTTP method of the request header.
 * @scenario		Invoking http_transaction_request_set_method with valid parameter.
 */
int utc_http_transaction_request_set_method_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_method(transaction, HTTP_METHOD_GET);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_method(transaction, HTTP_METHOD_GET);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_get_method_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets the Http method from request header.
 * @scenario		Invoking http_transaction_request_get_method with invalid parameter.
 */
int utc_http_transaction_request_get_method_n(void)
{
	int ret;
	http_method_e method;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_get_method(transaction, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_get_method(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_get_method(NULL, &method);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_get_method(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_get_method_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Gets the Http method from request header.
 * @scenario		Invoking http_transaction_request_get_method with valid parameter.
 */
int utc_http_transaction_request_get_method_p(void)
{
	int ret;
	http_method_e method;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_get_method(transaction, &method);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_get_method(transaction, &method);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_set_version_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Sets an HTTP version of the request header.
 * @scenario		Invoking http_transaction_request_set_version with invalid parameter.
 */
int utc_http_transaction_request_set_version_n(void)
{
	int ret;
	http_version_e version = HTTP_VERSION_1_1;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_version(NULL, version);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_version(NULL, version);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_set_version_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Sets an HTTP version of the request header.
 * @scenario		Invoking http_transaction_request_set_version with valid parameter.
 */
int utc_http_transaction_request_set_version_p(void)
{
	int ret;
	http_version_e version = HTTP_VERSION_1_1;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_version(transaction, version);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_version(transaction, version);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_get_version_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets the Http version from request header.
 * @scenario		Invoking http_transaction_request_get_version with invalid parameter.
 */
int utc_http_transaction_request_get_version_n(void)
{
	int ret;
	http_version_e version;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_get_version(transaction, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_get_version(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_get_version(NULL, &version);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_get_version(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_get_version_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Gets the Http version from request header.
 * @scenario		Invoking http_transaction_request_get_version with valid parameter.
 */
int utc_http_transaction_request_get_version_p(void)
{
	int ret;
	http_version_e version;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_get_version(transaction, &version);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_get_version(transaction, &version);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_set_uri_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Sets a URI of the request header.
 * @scenario		Invoking http_transaction_request_set_uri with invalid parameter.
 */
int utc_http_transaction_request_set_uri_n(void)
{
	int ret;
	const char host_uri[100] = "http://www.tizen.org";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_uri(transaction, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_uri(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_set_uri(NULL, host_uri);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_set_uri(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_set_uri_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Sets a URI of the request header.
 * @scenario		Invoking http_transaction_request_set_uri with valid parameter.
 */
int utc_http_transaction_request_set_uri_p(void)
{
	int ret;
	const char host_uri[100] = "http://www.tizen.org";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_uri(transaction, host_uri);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_uri(transaction, host_uri);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_get_uri_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets the uri.
 * @scenario		Invoking http_transaction_request_get_uri with invalid parameter.
 */
int utc_http_transaction_request_get_uri_n(void)
{
	int ret;
	char *host_uri;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_get_uri(transaction, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_get_uri(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_get_uri(NULL, &host_uri);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_get_uri(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_get_uri_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Gets the uri.
 * @scenario		Invoking http_transaction_request_get_uri with valid parameter.
 */
int utc_http_transaction_request_get_uri_p(void)
{
	int ret;
	char *host_uri;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_uri(transaction, "http://www.tizen.org");
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_uri(transaction, "http://www.tizen.org");
	assert_eq(ret, HTTP_ERROR_NONE);
	ret = http_transaction_request_get_uri(transaction, &host_uri);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (host_uri)
		free(host_uri);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_set_accept_encoding_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Sets the Accept-Encoding header field of HttpRequest.
 * @scenario		Invoking http_transaction_request_set_accept_encoding with invalid parameter.
 */
int utc_http_transaction_request_set_accept_encoding_n(void)
{
	int ret;
	const char encoding[100] = "gzip, deflate";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_accept_encoding(transaction, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_accept_encoding(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_set_accept_encoding(NULL, encoding);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_set_accept_encoding(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);



	return 0;
}

/**
 * @testcase        utc_http_transaction_request_set_accept_encoding_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Sets the Accept-Encoding header field of HttpRequest.
 * @scenario		Invoking http_transaction_request_set_accept_encoding with valid parameter.
 */
int utc_http_transaction_request_set_accept_encoding_p(void)
{
	int ret;
	const char encoding[100] = "gzip, deflate";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_accept_encoding(transaction, encoding);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_accept_encoding(transaction, encoding);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_get_accept_encoding_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets the Accept-Encoding header field of HttpRequest.
 * @scenario		Invoking http_transaction_request_get_accept_encoding with invalid parameter.
 */
int utc_http_transaction_request_get_accept_encoding_n(void)
{
	int ret;
	char *encoding;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_get_accept_encoding(transaction, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_get_accept_encoding(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_get_accept_encoding(NULL, &encoding);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_get_accept_encoding(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_get_accept_encoding_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Gets the Accept-Encoding header field of HttpRequest.
 * @scenario		Invoking http_transaction_request_get_accept_encoding with valid parameter.
 */
int utc_http_transaction_request_get_accept_encoding_p(void)
{
	int ret;
	char *encoding;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_accept_encoding(transaction, "gzip, deflate");
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_accept_encoding(transaction, "gzip, deflate");
	assert_eq(ret, HTTP_ERROR_NONE);
	ret = http_transaction_request_get_accept_encoding(transaction, &encoding);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (encoding)
		free(encoding);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_set_cookie_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Sets a cookie in the HTTP request.
 * @scenario		Invoking http_transaction_request_set_cookie with invalid parameter.
 */
int utc_http_transaction_request_set_cookie_n(void)
{
	int ret;
	const char cookie[100] = "tool=tizen; fun=yes;";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_cookie(transaction, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_cookie(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_set_cookie(NULL, cookie);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_set_cookie(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_set_cookie_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Sets a cookie in the HTTP request.
 * @scenario		Invoking http_transaction_request_set_cookie with valid parameter.
 */
int utc_http_transaction_request_set_cookie_p(void)
{
	int ret;
	const char cookie[100] = "tool=tizen; fun=yes;";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_cookie(transaction, cookie);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_cookie(transaction, cookie);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_get_cookie_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets a cookie in the HTT request.
 * @scenario		Invoking http_transaction_request_get_cookie with invalid parameter.
 */
int utc_http_transaction_request_get_cookie_n(void)
{
	int ret;
	char *cookie;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_get_cookie(transaction, &cookie);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_get_cookie(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_get_cookie(NULL, &cookie);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_get_cookie(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);


	return 0;
}

/**
 * @testcase        utc_http_transaction_request_get_cookie_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Gets a cookie in the HTT request.
 * @scenario		Invoking http_transaction_request_get_cookie with valid parameter.
 */
int utc_http_transaction_request_get_cookie_p(void)
{
	int ret;
	char *cookie;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_get_cookie(transaction, &cookie);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_cookie(transaction, "tool=tizen; fun=yes;");
	assert_eq(ret, HTTP_ERROR_NONE);
	ret = http_transaction_request_get_cookie(transaction, &cookie);
	assert_eq(ret, HTTP_ERROR_NONE);

	if (cookie)
		free(cookie);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_write_body_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Writes the request message body.
 * @scenario		Invoking http_transaction_request_write_body with invalid parameter.
 */
int utc_http_transaction_request_write_body_n(void)
{
	int ret;
	const char body[100] = "data";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_write_body(transaction, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_write_body(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_write_body(NULL, body);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_write_body(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_write_body_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Writes the request message body.
 * @scenario		Invoking http_transaction_request_write_body with valid parameter.
 */
int utc_http_transaction_request_write_body_p(void)
{
	int ret;
	const char body[100] = "data";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_write_body(transaction, body);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_write_body(transaction, body);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_set_upload_file_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Sets the file path for uploading.
 * @scenario		Invoking http_transaction_request_set_uploaded_file with invalid parameter.
 */
int utc_http_transaction_request_set_upload_file_n(void)
{
	int ret;
	const char file_path[100] = "/usr/apps/core-http-tests/shared/res/test.txt";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_upload_file(transaction, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_upload_file(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_set_upload_file(NULL, file_path);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_request_set_upload_file(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_request_set_upload_file_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Sets the file path for uploading.
 * @scenario		Invoking http_transaction_request_set_upload_file with valid parameter.
 */
int utc_http_transaction_request_set_upload_file_p(void)
{
	int ret;
	const char file_path[100] = "/usr/apps/core-http-tests/shared/res/test.txt";
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_upload_file(transaction, file_path);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_upload_file(transaction, file_path);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_http_transaction_set_http_auth_scheme_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Sets an HTTP authentication scheme.
 * @scenario		Invoking http_transaction_set_http_auth_scheme with invalid parameter.
 */
int utc_http_transaction_set_http_auth_scheme_n(void)
{
	int ret;
	http_auth_scheme_e auth_scheme = HTTP_AUTH_WWW_BASIC;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_http_auth_scheme(NULL, auth_scheme);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_http_auth_scheme(NULL, auth_scheme);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_http_transaction_set_http_auth_scheme_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Sets an HTTP authentication scheme.
 * @scenario		Invoking http_transaction_set_http_auth_scheme with valid parameter.
 */
int utc_http_transaction_set_http_auth_scheme_p(void)
{
	int ret;
	http_auth_scheme_e auth_scheme = HTTP_AUTH_WWW_BASIC;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_http_auth_scheme(transaction, auth_scheme);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_http_auth_scheme(transaction, auth_scheme);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_http_transaction_get_http_auth_scheme_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets the HTTP authentication scheme.
 * @scenario		Invoking http_transaction_get_http_auth_scheme with invalid parameter.
 */
int utc_http_transaction_get_http_auth_scheme_n(void)
{
	int ret;
	http_auth_scheme_e auth_scheme;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_get_http_auth_scheme(NULL, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_get_http_auth_scheme(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_get_http_auth_scheme(NULL, &auth_scheme);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_get_http_auth_scheme(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_http_transaction_get_http_auth_scheme_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Gets the HTTP authentication scheme.
 * @scenario		Invoking http_transaction_get_http_auth_scheme with valid parameter.
 */
int utc_http_transaction_get_http_auth_scheme_p(void)
{
	int ret;
	http_auth_scheme_e auth_scheme;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_get_http_auth_scheme(transaction, &auth_scheme);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_http_auth_scheme(transaction, HTTP_AUTH_WWW_BASIC);
	assert_eq(ret, HTTP_ERROR_NONE);
	ret = http_transaction_get_http_auth_scheme(transaction, &auth_scheme);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_http_transaction_set_credentials_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Sets an HTTP credentials.
 * @scenario		Invoking http_transaction_set_credentials with invalid parameter.
 */
int utc_http_transaction_set_credentials_n(void)
{
	int ret;
	const char user_name[10] = "tizen";
	const char password[10] = "q1w2e3r4";

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_credentials(NULL, NULL, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_credentials(transaction, user_name, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_set_credentials(transaction, NULL, password);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_set_credentials(NULL, user_name, password);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_set_credentials(NULL, NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_http_transaction_set_credentials_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Sets an HTTP credentials.
 * @scenario		Invoking http_transaction_set_credentials  with valid parameter.
 */
int utc_http_transaction_set_credentials_p(void)
{
	int ret;
	const char user_name[10] = "tizen";
	const char password[10] = "q1w2e3r4";

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_credentials(transaction, user_name, password);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif
	ret = http_transaction_set_credentials(transaction, user_name, password);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_http_transaction_get_credentials_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets the username & password for the http credential.
 * @scenario		Invoking http_transaction_get_credentials with invalid parameter.
 */
int utc_http_transaction_get_credentials_n(void)
{
	int ret;
	char *user_name = NULL;
	char *password = NULL;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_get_credentials(NULL, NULL, NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_credentials(transaction, "tizen", "q1w2e3r4");
	assert_eq(ret, HTTP_ERROR_NONE);
	ret = http_transaction_get_credentials(transaction, &user_name, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_get_credentials(transaction, NULL, &password);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_get_credentials(NULL, &user_name, &password);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_get_credentials(NULL, NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	g_free(user_name);
	user_name = NULL;

	g_free(password);
	password = NULL;

	return 0;
}

/**
 * @testcase		utc_http_transaction_get_credentials_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Gets the username & password for the http credential.
 * @scenario		Invoking http_transaction_get_credentials with valid parameter.
 */
int utc_http_transaction_get_credentials_p(void)
{
	int ret;
	char *user_name = NULL;
	char *password = NULL;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_get_credentials(transaction, &user_name, &password);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif
	ret = http_transaction_set_credentials(transaction, "tizen", "q1w2e3r4");
	assert_eq(ret, HTTP_ERROR_NONE);
	ret = http_transaction_get_credentials(transaction, &user_name, &password);
	assert_eq(ret, HTTP_ERROR_NONE);

	g_free(user_name);
	user_name = NULL;

	g_free(password);
	password = NULL;

	return 0;
}

/**
 * @testcase		utc_http_transaction_open_authentication_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Opens HTTP transaction with authentication information.
 * @scenario		Invoking http_transaction_open_authentication with invalid parameter.
 */
int utc_http_transaction_open_authentication_n(void)
{
	int ret;
	http_transaction_h http_auth_transaction;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_open_authentication(NULL, &http_auth_transaction);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_open_authentication(NULL, &http_auth_transaction);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_http_transaction_open_authentication_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Opens HTTP transaction with authentication information.
 * @scenario		Invoking http_transaction_open_authentication with valid parameter.
 */
int utc_http_transaction_open_authentication_p(void)
{
	int ret;
	http_transaction_h http_auth_transaction;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_open_authentication(transaction, &http_auth_transaction);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_open_authentication(transaction, &http_auth_transaction);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_resume_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Resumes the transaction.
 * @scenario		Invoking http_transaction_resume with invalid parameter.
 */
int utc_http_transaction_resume_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_resume(NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif
	ret = http_transaction_resume(NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_pause_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Pauses the transaction.
 * @scenario		Invoking http_transaction_pause with invalid parameter.
 */
int utc_http_transaction_pause_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_pause(NULL, HTTP_PAUSE_ALL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif
	ret = http_transaction_pause(NULL, HTTP_PAUSE_ALL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_cancel_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Cancels the transaction.
 * @scenario		Invoking http_transaction_cancel with invalid parameter.
 */
int utc_http_transaction_cancel_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_cancel(NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif
	ret = http_transaction_cancel(NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_response_get_status_text_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets the HTTP status text from HTTP Response.
 * @scenario		Invoking http_transaction_response_get_status_text with invalid parameter.
 */
int utc_http_transaction_response_get_status_text_n(void)
{
	int ret;
	char *status_text;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_response_get_status_text(NULL, &status_text);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif
	ret = http_transaction_response_get_status_text(NULL, &status_text);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_response_get_status_text(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_response_get_status_text(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_response_get_version_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets the HTTP version from HTTP Response.
 * @scenario		Invoking http_transaction_response_get_version with invalid parameter.
 */
int utc_http_transaction_response_get_version_n(void)
{
	int ret;
	http_version_e version;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_response_get_version(NULL, &version);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif
	ret = http_transaction_response_get_version(NULL, &version);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_response_get_version(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_response_get_version(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_get_realm_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Gets the HTTP authentication realm.
 * @scenario		Invoking http_transaction_get_realm with invalid parameter.
 */
int utc_http_transaction_get_realm_n(void)
{
	int ret;
	char *realm;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_get_realm(NULL, &realm);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif
	ret = http_transaction_get_realm(NULL, &realm);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_get_realm(transaction, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);
	ret = http_transaction_get_realm(NULL, NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_deinit_n
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Deinitializes the Http module.
 * @scenario		Invoking http_deinit with invalid parameter.
 */
int utc_http_deinit_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_deinit();
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_deinit();
	is_init = false;
	ret = http_deinit();
	assert_eq(ret, HTTP_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase        utc_http_deinit_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Deinitializes the Http module.
 * @scenario		Invoking http_deinit with valid parameter.
 */
int utc_http_deinit_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_deinit();
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_deinit();
	assert_eq(ret, HTTP_ERROR_NONE);
	is_init = false;

	return 0;
}

/**
 * @testcase        utc_http_transaction_submit_n1
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Submits the Http request.
 * @scenario		Invoking http_transaction_submit with invalid parameter.
 */
int utc_http_transaction_submit_n1(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_submit(NULL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_submit(NULL);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_submit_n2
 * @since_tizen     3.0
 * @type	        Negative
 * @description		Submits the Http request.
 * @scenario		Invoking http_transaction_submit with invalid URL.
 */
int utc_http_transaction_submit_n2(void)
{
	int ret;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_uri(transaction, INVALID_URL);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_uri(transaction, INVALID_URL);
	assert_eq(ret, HTTP_ERROR_NONE);

	ret = http_transaction_submit(transaction);
	g_pMainLoop = g_main_loop_new(NULL, false);
	g_main_loop_run(g_pMainLoop);
	g_pMainLoop = NULL;

	if (g_use_proxy) {
		// proxy server might not return response when URL isn't valid.
		if (g_CallbackRet == HTTP_ERROR_OPERATION_FAILED
				|| g_CallbackRet == HTTP_ERROR_COULDNT_RESOLVE_HOST)
			return 0;
		else
			return 1;
	} else {
		assert_eq(g_CallbackRet, HTTP_ERROR_COULDNT_RESOLVE_HOST);
	}

	return 0;
}

/**
 * @testcase        utc_http_transaction_submit_p
 * @since_tizen     3.0
 * @type	        Positive
 * @description		Submits the Http request.
 * @scenario		Invoking http_transaction_submit with valid parameter.
 */
int utc_http_transaction_submit_p(void)
{
	int ret;
	const char uri[100] = "http://www.tizen.org";
	const char field[20] = "User-Agent";
	const char value[20] = "tizen";

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_request_set_uri(transaction, uri);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_request_set_uri(transaction, uri);
	assert_eq(ret, HTTP_ERROR_NONE);

	ret = http_transaction_header_add_field(transaction , field, value);
	assert_eq(ret, HTTP_ERROR_NONE);

	ret = http_transaction_submit(transaction);
	g_pMainLoop = g_main_loop_new(NULL, false);
	g_main_loop_run(g_pMainLoop);
	g_pMainLoop = NULL;

	assert_eq(g_CallbackRet, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_tcp_fastopen_n
 * @since_tizen     5.0
 * @type	        Negative
 * @description		Sets the flag to allow TCP Fast Open.
 * @scenario		Invoking http_transaction_set_tcp_fastopen with invalid parameter.
 */
int utc_http_transaction_set_tcp_fastopen_n(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_tcp_fastopen(NULL, true);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_tcp_fastopen(NULL, true);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_set_tcp_fastopen_p
 * @since_tizen     5.0
 * @type	        Positive
 * @description		Sets the flag to allow TCP Fast Open.
 * @scenario		Invoking http_transaction_set_tcp_fastopen with valid parameter.
 */
int utc_http_transaction_set_tcp_fastopen_p(void)
{
	int ret;

#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_tcp_fastopen(transaction, true);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_tcp_fastopen(transaction, true);
	assert_eq(ret, HTTP_ERROR_NONE);
	ret = http_transaction_set_tcp_fastopen(transaction, false);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_http_transaction_get_tcp_fastopen_n
 * @since_tizen     5.0
 * @type	        Negative
 * @description		Gets the flag to allow TCP Fast Open.
 * @scenario		Invoking http_transaction_get_tcp_fastopen with invalid parameter.
 */
int utc_http_transaction_get_tcp_fastopen_n(void)
{
	int ret;
	bool is_enable;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_tcp_fastopen(NULL, &is_enable);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_tcp_fastopen(NULL, &is_enable);
	assert_eq(ret, HTTP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_http_transaction_get_tcp_fastopen_p
 * @since_tizen     5.0
 * @type	        Positive
 * @description		Gets the flag to allow TCP Fast Open.
 * @scenario		Invoking http_transaction_get_tcp_fastopen with valid parameter.
 */
int utc_http_transaction_get_tcp_fastopen_p(void)
{
	int ret;
	bool is_enable;
#ifdef WEARABLE
	if (g_internet_supported == false) {
		ret = http_transaction_set_tcp_fastopen(transaction, &is_enable);
		assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);
		return 0;
	}
#endif

	ret = http_transaction_set_tcp_fastopen(transaction, &is_enable);
	assert_eq(ret, HTTP_ERROR_NONE);

	return 0;
}
