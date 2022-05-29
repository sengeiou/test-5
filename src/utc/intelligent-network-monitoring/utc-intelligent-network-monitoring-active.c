/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "utc-intelligent-network-monitoring-common.h"

/**
 * @function        utc_inm_active_startup
 * @since_tizen     5.5
 * @description     Initializes inm active test. Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_inm_active_startup(void)
{
	g_bFeatureInm = inm_check_feature_supported(FEATURE_INM);

	int ret = inm_initialize(&g_hInm);
	PRINT_RETURN("inm_initialize", ret);
	if (ret != INM_ERROR_NONE) {
		if (ret != INM_ERROR_NOT_SUPPORTED || !g_bFeatureInm) {
			FPRINTF("[%s:%d] Fail to initialize\\n", __FILE__, __LINE__);
			dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Fail to initialize", __FILE__, __LINE__);
		}
		return;
	}

	ret = inm_get_current_connection(g_hInm, &g_hConnection);
	if (ret != INM_ERROR_NONE) {
		FPRINTF("[%s:%d] Fail to get current profile or service\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Fail to get current profile or service", __FILE__, __LINE__);
		return;
	}

	if (g_bFeatureTelephony == false && g_bFeatureWifi == false
		&& g_bFeatureBttethering == false && g_bFeatureEthernet == false
		&& g_bFeatureInm == false) {
		g_bFeatureAllNotSupported = true;
		FPRINTF("[%s:%d] All feature is not supported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] all feature is not supported", __FILE__, __LINE__);
		return;
	}
}

/**
 * @function        utc_inm_active_cleanup
 * @since_tizen     5.5
 * @description     Deinitializes inm active test. Called after each test.
 * @parameter       NA
 * @return          NA
 */
void utc_inm_active_cleanup(void)
{
	int ret;

	ret = inm_connection_destroy(&g_hConnection);
	if (ret != INM_ERROR_NONE)
		FPRINTF("[%s:%d] Fail to destroy current profile or service\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Fail to destroy current profile or service", __FILE__, __LINE__);

	ret = inm_deinitialize(g_hInm);
	PRINT_RETURN("inm_deinitialize", ret);
}

/**
 * @testcase        utc_inm_arp_request_set_packet_interval_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Sets the ARP request packet interval.
 * @scenario        Sets the ARP request packet interval. Ensure no error.
 */
int utc_inm_arp_request_set_packet_interval_p(void)
{
	int ret = INM_ERROR_NONE;
	int interval = ARP_REQUEST_PACKET_INTERVAL;

	if (!g_bFeatureInm) {
		ret = inm_arp_request_set_packet_interval(g_hInm, interval);
		CHECK_RETURN("inm_arp_request_set_packet_interval", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_arp_request_set_packet_interval(g_hInm, interval);
	CHECK_RETURN("inm_arp_request_set_packet_interval", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_arp_request_set_packet_interval_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_arp_request_set_packet_interval by passing invalid parameters
 * @scenario        Pass invalid parameters and inm_arp_request_set_packet_interval() should be failed.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_arp_request_set_packet_interval_n(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_arp_request_set_packet_interval(g_hInm, 5);
		CHECK_RETURN("inm_arp_request_set_packet_interval", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_arp_request_set_packet_interval(g_hInm, 0);
	CHECK_RETURN("inm_arp_request_set_packet_interval", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_arp_request_set_packet_interval(NULL, 5);
	CHECK_RETURN("inm_arp_request_set_packet_interval", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

static inline int __get_original_interval(int *original_interval)
{
	int ret;
	ret = inm_arp_request_get_packet_interval(g_hInm, original_interval);

	return  (ret != INM_ERROR_NONE) ? -1 : 0;
}

static inline  int __set_original_interval(int original_interval)
{
	int ret;
	ret = inm_arp_request_set_packet_interval(g_hInm, original_interval);

	return  (ret != INM_ERROR_NONE) ? -1 : 0;
}

/**
 * @testcase        utc_inm_arp_request_get_packet_interval_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Gets the ARP request packet interval.
 * @scenario        Gets the ARP request packet interval. Ensure no error.
 */
int utc_inm_arp_request_get_packet_interval_p(void)
{
	int ret = INM_ERROR_NONE;
	int interval = ARP_REQUEST_PACKET_INTERVAL;
	int original_interval;

	if (!g_bFeatureInm) {
		ret = inm_arp_request_get_packet_interval(g_hInm, &interval);
		CHECK_RETURN("inm_arp_request_get_packet_interval", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (__get_original_interval(&original_interval) != 0) {
		FPRINTF("[%s:%d] Fail to get original interval\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Fail to get get original interval", __FILE__, __LINE__);
		return -1;
	}

	ret = inm_arp_request_set_packet_interval(g_hInm, original_interval + ARP_REQUEST_PACKET_INTERVAL);
	CHECK_RETURN("inm_arp_request_set_packet_interval", ret, INM_ERROR_NONE);

	ret = inm_arp_request_get_packet_interval(g_hInm, &interval);
	CHECK_RETURN("inm_arp_request_get_packet_interval", ret, INM_ERROR_NONE);

	IS_EQUAL("inm_arp_request_get_packet_interval",
			interval,
			original_interval + ARP_REQUEST_PACKET_INTERVAL);

	if (__set_original_interval(original_interval) != 0) {
		FPRINTF("[%s:%d] Fail to get original interval\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Fail to set get original interval", __FILE__, __LINE__);
		return -1;
	}

	return 0;
}

/**
 * @testcase        utc_inm_arp_request_get_packet_interval_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_arp_request_get_packet_interval by passing invalid parameters
 * @scenario        Pass invalid parameters and inm_arp_request_get_packet_interval() should be failed.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_arp_request_get_packet_interval_n(void)
{

	int ret = INM_ERROR_NONE;
	int interval = ARP_REQUEST_PACKET_INTERVAL;

	if (!g_bFeatureInm) {
		ret = inm_arp_request_get_packet_interval(g_hInm, &interval);
		CHECK_RETURN("inm_arp_request_get_packet_interval", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_arp_request_get_packet_interval(g_hInm, 0);
	CHECK_RETURN("inm_arp_request_get_packet_interval", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_arp_request_get_packet_interval(NULL, &interval);
	CHECK_RETURN("inm_arp_request_get_packet_interval", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

static inline int __init_arp_request()
{
	int ret;

	if (!g_hConnection) {
		FPRINTF("[%s:%d] Current profile or service doesn't exist\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Current profile or service doesn't exist", __FILE__, __LINE__);
		return -1;
	}

	ret = inm_connection_get_gateway_address(g_hConnection,
			INM_ADDRESS_FAMILY_IPV4,
			&arp_requested_ip_str);
	if (ret != INM_ERROR_NONE)  {
		FPRINTF("[%s:%d] Current profile or service doesn't have gateway address\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Current profile or service doesn't have gateway address", __FILE__, __LINE__);
		return -1;
	}

	g_arp_requested_ip_found = FALSE;

	return 0;
}

static inline void __deinit_arp_request()
{
	if (arp_requested_ip_str)
		free(arp_requested_ip_str);

	arp_requested_ip_str = NULL;
	return;
}

static void __inm_arp_request_ip_found_callback(bool found, const char *ip, void *user_data)
{
	if (g_strcmp0(ip, arp_requested_ip_str) == 0) {
		g_arp_requested_ip_found = found;
		FPRINTF("[%s:%d] ARP requested %s found\\n", __FILE__, __LINE__, ip);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] ARP requested %s found", __FILE__, __LINE__, ip);
		QUIT_GMAIN_LOOP();
	}
}

static gboolean __arp_request_timeout_cb(gpointer data)
{
	g_nTimeoutId = 0;
	QUIT_GMAIN_LOOP();

	return FALSE;
}

/**
 * @testcase        utc_inm_arp_request_start_stop_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Starts the ARP request to find a device with target IP.
 * @scenario        Finds the device with target IP. Ensure no error.
 */
int utc_inm_arp_request_start_stop_p(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_arp_request_start(g_hInm,
				DEFAULT_ARP_REQUEST_IP_STR,
				__inm_arp_request_ip_found_callback,
				NULL);
		CHECK_RETURN("inm_arp_request_start", ret, INM_ERROR_NOT_SUPPORTED);

		ret = inm_arp_request_stop(g_hInm,
				DEFAULT_ARP_REQUEST_IP_STR);
		CHECK_RETURN("inm_arp_request_stop", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (__init_arp_request() != 0)
		return -1;

	ret = inm_arp_request_start(g_hInm,
			arp_requested_ip_str,
			__inm_arp_request_ip_found_callback,
			NULL);
	CHECK_RETURN("inm_arp_request_start", ret, INM_ERROR_NONE);

	RUN_GMAIN_LOOP(__arp_request_timeout_cb, NULL);

	ret = inm_arp_request_stop(g_hInm,
			arp_requested_ip_str);
	CHECK_RETURN("inm_arp_request_stop", ret, INM_ERROR_NONE);

	__deinit_arp_request();
	if (!g_arp_requested_ip_found) {
		FPRINTF("[%s:%d] ARP requested IP not found\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] ARP requested IP not found", __FILE__, __LINE__);
		return -1;
	}

	return 0;
}

/**
 * @testcase        utc_inm_arp_request_start_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_arp_request_start by passing invalid parameters
 * @scenario        Pass invalid parameters and inm_arp_request_start() should be failed.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_arp_request_start_n(void)
{

	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_arp_request_start(g_hInm,
				DEFAULT_ARP_REQUEST_IP_STR,
				__inm_arp_request_ip_found_callback,
				NULL);
		CHECK_RETURN("inm_arp_request_start", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (__init_arp_request() != 0)
		return -1;

	ret = inm_arp_request_start(NULL,
			arp_requested_ip_str,
			__inm_arp_request_ip_found_callback,
			NULL);
	CHECK_RETURN("inm_arp_request_start", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_arp_request_start(g_hInm,
			NULL,
			__inm_arp_request_ip_found_callback,
			NULL);
	CHECK_RETURN("inm_arp_request_start", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_arp_request_start(g_hInm,
			arp_requested_ip_str,
			NULL,
			NULL);
	CHECK_RETURN("inm_arp_request_start", ret, INM_ERROR_INVALID_PARAMETER);

	__deinit_arp_request();

	return 0;
}

/**
 * @testcase        utc_inm_arp_request_stop_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_arp_request_stop by passing invalid parameters
 * @scenario        Pass invalid parameters and inm_arp_request_stop() should be failed.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_arp_request_stop_n(void)
{

	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_arp_request_stop(g_hInm,
				DEFAULT_ARP_REQUEST_IP_STR);
		CHECK_RETURN("inm_arp_request_stop", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (__init_arp_request() != 0)
		return -1;

	ret = inm_arp_request_stop(NULL,
			arp_requested_ip_str);
	CHECK_RETURN("inm_arp_request_stop", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_arp_request_stop(g_hInm,
			NULL);
	CHECK_RETURN("inm_arp_request_stop", ret, INM_ERROR_INVALID_PARAMETER);

	__deinit_arp_request();

	return 0;
}

/**
 * @testcase        utc_inm_arp_request_start_stop_n
 * @since_tizen     5.5
 * @type            Positive
 * @description     Starts the ARP request to find a device with invalid IP.
 * @scenario        Target IP is not found. Ensure no error.
 */
int utc_inm_arp_request_start_stop_n(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_arp_request_start(g_hInm,
				DEFAULT_ARP_REQUEST_IP_STR,
				__inm_arp_request_ip_found_callback,
				NULL);
		CHECK_RETURN("inm_arp_request_start", ret, INM_ERROR_NOT_SUPPORTED);

		ret = inm_arp_request_stop(g_hInm,
				DEFAULT_ARP_REQUEST_IP_STR);
		CHECK_RETURN("inm_arp_request_stop", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	g_arp_requested_ip_found = FALSE;
	arp_requested_ip_str = g_strdup(INVALID_ARP_REQUEST_IP_STR);
	ret = inm_arp_request_start(g_hInm,
			arp_requested_ip_str,
			__inm_arp_request_ip_found_callback,
			NULL);
	CHECK_RETURN("inm_arp_request_start", ret, INM_ERROR_NONE);

	RUN_GMAIN_LOOP(__arp_request_timeout_cb, NULL);

	ret = inm_arp_request_stop(g_hInm,
			arp_requested_ip_str);
	CHECK_RETURN("inm_arp_request_stop", ret, INM_ERROR_NONE);

	g_free(arp_requested_ip_str);
	if (g_arp_requested_ip_found) {
		FPRINTF("[%s:%d] ARP requested Invalid IP found\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] ARP requested Invalid IP found", __FILE__, __LINE__);
		return -1;
	}

	return 0;
}

static void __inm_default_gateway_found_callback(bool found, const char *ip, void *user_data)
{
	g_gateway_found = found;
	FPRINTF("[%s:%d] Gateway %s found\\n", __FILE__, __LINE__, ip);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Gateway %s found", __FILE__, __LINE__, ip);
	QUIT_GMAIN_LOOP();
}

static gboolean __gateway_timeout_cb(gpointer data)
{
	g_nTimeoutId = 0;
	QUIT_GMAIN_LOOP();

	return FALSE;
}

/**
 * @testcase        utc_inm_default_gateway_start_stop_checking_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Starts the ARP request to find a gateway.
 * @scenario        Finds the gateway. Ensure no error.
 */
int utc_inm_default_gateway_start_stop_checking_p(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_default_gateway_start_checking(g_hInm,
				0,
				__inm_default_gateway_found_callback,
				NULL);
		CHECK_RETURN("inm_default_gateway_start_checking", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	g_gateway_found = FALSE;
	ret = inm_default_gateway_start_checking(g_hInm,
			0,
			__inm_default_gateway_found_callback,
			NULL);
	CHECK_RETURN("inm_default_gateway_start_checking", ret, INM_ERROR_NONE);

	RUN_GMAIN_LOOP(__gateway_timeout_cb, NULL);

	ret = inm_default_gateway_stop_checking(g_hInm);
	CHECK_RETURN("inm_default_gateway_stop_checking", ret, INM_ERROR_NONE);

	if (!g_gateway_found) {
		FPRINTF("[%s:%d] Gateway IP not found\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Gateway IP not found", __FILE__, __LINE__);
		return -1;
	}

	return 0;
}

/**
 * @testcase        utc_inm_default_gateway_start_checking_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_default_gateway_start_checking by passing invalid parameters
 * @scenario        Pass invalid parameters and inm_default_gateway_start_checking() should be failed.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_default_gateway_start_checking_n(void)
{

	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_default_gateway_start_checking(g_hInm,
				0,
				__inm_default_gateway_found_callback,
				NULL);
		CHECK_RETURN("inm_default_gateway_start_checking", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_default_gateway_start_checking(NULL,
			0,
			__inm_default_gateway_found_callback,
			NULL);
	CHECK_RETURN("inm_default_gateway_start_checking", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_default_gateway_start_checking(g_hInm,
			0,
			NULL,
			NULL);
	CHECK_RETURN("inm_default_gateway_start_checking", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_default_gateway_stop_checking_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_default_gateway_stop_checking by passing invalid parameters
 * @scenario        Pass invalid parameters and inm_default_gateway_stop_checking() should be failed.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_default_gateway_stop_checking_n(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_default_gateway_stop_checking(g_hInm);
		CHECK_RETURN("inm_default_gateway_stop_checking", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_default_gateway_stop_checking(NULL);
	CHECK_RETURN("inm_default_gateway_stop_checking", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __inm_default_dns_lookup_result_callback(bool found, void *user_data)
{
	g_dns_lookup_finished = found;
	FPRINTF("[%s:%d] DNS lookup accomplished\\n", __FILE__, __LINE__);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] DNS lookup accomplished", __FILE__, __LINE__);
	QUIT_GMAIN_LOOP();
}

static gboolean __dns_lookup_timeout_cb(gpointer data)
{
	g_nTimeoutId = 0;
	QUIT_GMAIN_LOOP();

	return FALSE;
}

/**
 * @testcase        utc_inm_default_dns_lookup_check_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Checks the DNS lookup is available.
 * @scenario        DNS lookup is available. Ensure no error.
 */
int utc_inm_default_dns_lookup_check_p(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_default_dns_lookup_check(g_hInm,
				__inm_default_dns_lookup_result_callback,
				NULL);
		CHECK_RETURN("inm_default_dns_lookup_check", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	g_dns_lookup_finished = FALSE;
	ret = inm_default_dns_lookup_check(g_hInm,
			__inm_default_dns_lookup_result_callback,
			NULL);
	CHECK_RETURN("inm_default_dns_lookup_check", ret, INM_ERROR_NONE);

	RUN_GMAIN_LOOP(__dns_lookup_timeout_cb, NULL);

	if (!g_dns_lookup_finished) {
		FPRINTF("[%s:%d] DNS lookup is not finished\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] DNS lookup is not finished", __FILE__, __LINE__);
		return -1;
	}

	return 0;
}

/**
 * @testcase        utc_inm_default_dns_lookup_check_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_default_dns_lookup_check by passing invalid parameters
 * @scenario        Pass invalid parameters and inm_default_dns_lookup_check() should be failed.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_default_dns_lookup_check_n(void)
{

	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_default_dns_lookup_check(g_hInm,
				__inm_default_dns_lookup_result_callback,
				NULL);
		CHECK_RETURN("inm_default_dns_lookup_check", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_default_dns_lookup_check(g_hInm,
			NULL,
			NULL);
	CHECK_RETURN("inm_default_dns_lookup_check", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_default_dns_lookup_check(NULL,
			__inm_default_dns_lookup_result_callback,
			NULL);
	CHECK_RETURN("inm_default_dns_lookup_check", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_reachable_urls_add_remove_url_to_check_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Adds and removes the url to test reachability.
 * @scenario        Adds and removes the url to test reachability. Ensure no error.
 */
int utc_inm_reachable_urls_add_remove_url_to_check_p(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_reachable_urls_add_url_to_check(g_hInm, REACHABILITY_TEST_URL);
		CHECK_RETURN("inm_reachable_urls_add_url_to_check", ret, INM_ERROR_NOT_SUPPORTED);

		ret = inm_reachable_urls_remove_url_to_check(g_hInm, REACHABILITY_TEST_URL);
		CHECK_RETURN("inm_reachable_urls_remove_url_to_check", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_reachable_urls_add_url_to_check(g_hInm, REACHABILITY_TEST_URL);
	CHECK_RETURN("inm_reachable_urls_add_url_to_check", ret, INM_ERROR_NONE);

	ret = inm_reachable_urls_remove_url_to_check(g_hInm, REACHABILITY_TEST_URL);
	CHECK_RETURN("inm_reachable_urls_remove_url_to_check", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_reachable_urls_add_url_to_check_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_reachable_urls_add_url_to_check by passing invalid parameters
 * @scenario        Pass invalid parameters and inm_reachable_urls_add_url_to_check() should be failed.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_reachable_urls_add_url_to_check_n(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_reachable_urls_add_url_to_check(g_hInm, REACHABILITY_TEST_URL);
		CHECK_RETURN("inm_reachable_urls_add_url_to_check", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_reachable_urls_add_url_to_check(g_hInm, NULL);
	CHECK_RETURN("inm_reachable_urls_add_url_to_check", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_reachable_urls_add_url_to_check(NULL, REACHABILITY_TEST_URL);
	CHECK_RETURN("inm_reachable_urls_add_url_to_check", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_reachable_urls_remove_url_to_check_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_reachable_urls_remove_url_to_check by passing invalid parameters
 * @scenario        Pass invalid parameters and inm_reachable_urls_remove_url_to_check() should be failed.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_reachable_urls_remove_url_to_check_n(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_reachable_urls_remove_url_to_check(g_hInm, REACHABILITY_TEST_URL);
		CHECK_RETURN("inm_reachable_urls_remove_url_to_check", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_reachable_urls_remove_url_to_check(g_hInm, NULL);
	CHECK_RETURN("inm_reachable_urls_remove_url_to_check", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_reachable_urls_remove_url_to_check(NULL, REACHABILITY_TEST_URL);
	CHECK_RETURN("inm_reachable_urls_remove_url_to_check", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}
static inline char * __print_url_result(inm_reachable_urls_check_result_e err)
{
	switch (err) {
	case INM_REACHABLE_URL_CHECK_RESULT_SUCCESS:
		return "SUCCESS\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_MALFORMED_URL:
		return "MALFORMED_URL error\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_DNS_RESOLVE:
		return "DNS_RESOLVE error\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_TCP_CONNECT:
		return "TCP_CONNECT error\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_SSL:
		return "SSL error\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_HTTP:
		return "HTTP error\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_FILE_NOT_FOUND:
		return "FILE_NOT_FOUND error\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_UNKNOWN:
		return "UNKNOWN error\n";
	}
}

static void __inm_reachable_urls_check_result_default_callback(
		inm_reachable_urls_check_result_e result,
		const char *url,
		void *user_data)
{
	g_default_url_found = (result == INM_REACHABLE_URL_CHECK_RESULT_SUCCESS);
	FPRINTF("[%s:%d] %s %s\\n", __FILE__, __LINE__, url, __print_url_result(result));
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] %s %s\\n", __FILE__, __LINE__, url, __print_url_result(result));
	QUIT_GMAIN_LOOP();
}

static gboolean __reachable_urls_check_timeout_cb(gpointer data)
{
	g_nTimeoutId = 0;
	QUIT_GMAIN_LOOP();

	return FALSE;
}

/**
 * @testcase        utc_inm_reachable_default_urls_start_stop_checking_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Checks the default URL is reachable.
 * @scenario        URL is reachable. Ensure no error.
 */
int utc_inm_reachable_default_urls_start_stop_checking_p(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_reachable_urls_start_checking(g_hInm,
				INM_URL_LIST_TYPE_DEFAULT,
				__inm_reachable_urls_check_result_default_callback,
				NULL);
		CHECK_RETURN("inm_reachable_urls_start_checking", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	g_default_url_found = FALSE;
	ret = inm_reachable_urls_start_checking(g_hInm,
			INM_URL_LIST_TYPE_DEFAULT,
			__inm_reachable_urls_check_result_default_callback,
			NULL);
	CHECK_RETURN("inm_reachable_urls_start_checking", ret, INM_ERROR_NONE);

	RUN_GMAIN_LOOP(__reachable_urls_check_timeout_cb, NULL);

	ret = inm_reachable_urls_stop_checking(g_hInm,
			INM_URL_LIST_TYPE_DEFAULT);
	CHECK_RETURN("inm_reachable_urls_stop_checking", ret, INM_ERROR_NONE);

	if (!g_default_url_found) {
		FPRINTF("[%s:%d] Default URL is not reachable\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Default URL is not reachable", __FILE__, __LINE__);
		return -1;
	}

	return 0;
}

/**
 * @testcase        utc_inm_reachable_urls_start_checking_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_reachable_urls_start_checking by passing invalid parameters
 * @scenario        Pass invalid parameters and inm_reachable_urls_start_checking() should be failed.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_reachable_urls_start_checking_n(void)
{

	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_reachable_urls_start_checking(g_hInm,
				INM_URL_LIST_TYPE_DEFAULT,
				__inm_reachable_urls_check_result_default_callback,
				NULL);
		CHECK_RETURN("inm_reachable_urls_start_checking", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_reachable_urls_start_checking(NULL,
			INM_URL_LIST_TYPE_DEFAULT,
			__inm_reachable_urls_check_result_default_callback,
			NULL);
	CHECK_RETURN("inm_reachable_urls_start_checking", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_reachable_urls_start_checking(g_hInm,
			INM_URL_LIST_TYPE_DEFAULT,
			NULL,
			NULL);
	CHECK_RETURN("inm_reachable_urls_start_checking", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __inm_reachable_urls_check_result_user_requested_callback(
		inm_reachable_urls_check_result_e result,
		const char *url,
		void *user_data)
{
	g_user_requested_url_found = (result == INM_REACHABLE_URL_CHECK_RESULT_SUCCESS);
	FPRINTF("[%s:%d] %s %s\\n", __FILE__, __LINE__, url, __print_url_result(result));
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] %s %s\\n", __FILE__, __LINE__, url, __print_url_result(result));
	QUIT_GMAIN_LOOP();
}



static inline int __init_user_requested_url()
{
	int ret;

	ret = inm_reachable_urls_add_url_to_check(g_hInm, REACHABILITY_TEST_URL);
	if (ret != INM_ERROR_NONE)  {
		FPRINTF("[%s:%d] Failed to add user url\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Failed to add user url", __FILE__, __LINE__);
		return -1;
	}

	g_user_requested_url_found = FALSE;

	return 0;
}

static inline void __deinit_user_requested_url()
{
	int ret;

	ret = inm_reachable_urls_remove_url_to_check(g_hInm, REACHABILITY_TEST_URL);
	if (ret != INM_ERROR_NONE)  {
		FPRINTF("[%s:%d] Failed to remove user url\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Failed to remove user url", __FILE__, __LINE__);
	}

	return;
}

/**
 * @testcase        utc_inm_reachable_user_urls_start_stop_checking_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Checks the user requested URL is reachable.
 * @scenario        URL is reachable. Ensure no error.
 */
int utc_inm_reachable_user_urls_start_stop_checking_p(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_reachable_urls_start_checking(g_hInm,
				INM_URL_LIST_TYPE_USER,
				__inm_reachable_urls_check_result_user_requested_callback,
				NULL);
		CHECK_RETURN("inm_reachable_urls_start_checking", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (__init_user_requested_url() != 0)
		return -1;

	ret = inm_reachable_urls_start_checking(g_hInm,
			INM_URL_LIST_TYPE_USER,
			__inm_reachable_urls_check_result_user_requested_callback,
			NULL);
	CHECK_RETURN("inm_reachable_urls_start_checking", ret, INM_ERROR_NONE);

	RUN_GMAIN_LOOP(__reachable_urls_check_timeout_cb, NULL);

	ret = inm_reachable_urls_stop_checking(g_hInm,
			INM_URL_LIST_TYPE_USER);
	CHECK_RETURN("inm_reachable_urls_stop_checking", ret, INM_ERROR_NONE);

	__deinit_user_requested_url();

	if (!g_user_requested_url_found) {
		FPRINTF("[%s:%d] User requested URL is not reachable\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] requested URL is not reachable", __FILE__, __LINE__);
		return -1;
	}

	return 0;
}

/**
 * @testcase        utc_inm_reachable_urls_stop_checking_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_reachable_urls_stop_checking by passing invalid parameters
 * @scenario        Pass invalid parameters and inm_reachable_urls_stop_checking() should be failed.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_reachable_urls_stop_checking_n(void)
{

	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_reachable_urls_stop_checking(g_hInm,
				INM_URL_LIST_TYPE_DEFAULT);
		CHECK_RETURN("inm_reachable_urls_stop_checking", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_reachable_urls_stop_checking(NULL,
			INM_URL_LIST_TYPE_DEFAULT);
	CHECK_RETURN("inm_reachable_urls_stop_checking", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_reachable_urls_is_check_running_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Checking Url reachability is running.
 * @scenario        Checking Url reachability is running. Ensure no error.
 */
int utc_inm_reachable_urls_is_check_running_p(void)
{
	int ret = INM_ERROR_NONE;
	bool is_running = FALSE;

	if (!g_bFeatureInm) {
		ret = inm_reachable_urls_is_check_running(g_hInm,
				INM_URL_LIST_TYPE_DEFAULT,
				&is_running);
		CHECK_RETURN("inm_reachable_urls_is_check_running", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_reachable_urls_start_checking(g_hInm,
			INM_URL_LIST_TYPE_DEFAULT,
			__inm_reachable_urls_check_result_default_callback,
			NULL);
	PRINT_RETURN("inm_reachable_urls_start_checking", ret);

	ret = inm_reachable_urls_is_check_running(g_hInm,
			INM_URL_LIST_TYPE_DEFAULT,
			&is_running);
	CHECK_RETURN("inm_reachable_urls_is_check_running", ret, INM_ERROR_NONE);

	if (!is_running) {
		FPRINTF("[%s:%d] Url reachability is not running\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Url reachability is not running", __FILE__, __LINE__);
		return -1;
	}

	ret = inm_reachable_urls_stop_checking(g_hInm,
			INM_URL_LIST_TYPE_DEFAULT);
	PRINT_RETURN("inm_reachable_urls_stop_checking", ret);

	ret = inm_reachable_urls_is_check_running(g_hInm,
			INM_URL_LIST_TYPE_DEFAULT,
			&is_running);
	CHECK_RETURN("inm_reachable_urls_is_check_running", ret, INM_ERROR_NONE);
	if (ret != INM_ERROR_NOW_IN_PROGRESS && is_running) {
		FPRINTF("[%s:%d] Url reachability is running!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Url reachability is running!", __FILE__, __LINE__);
		return -1;
	}
	return 0;
}

/**
 * @testcase        utc_inm_reachable_urls_is_check_running_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_reachable_urls_is_check_running by passing invalid parameters
 * @scenario        Pass invalid parameters and inm_reachable_urls_is_check_running() should be failed.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_reachable_urls_is_check_running_n(void)
{

	int ret = INM_ERROR_NONE;
	bool is_running = FALSE;

	if (!g_bFeatureInm) {
		ret = inm_reachable_urls_is_check_running(g_hInm,
				INM_URL_LIST_TYPE_DEFAULT,
				&is_running);
		CHECK_RETURN("inm_reachable_urls_is_check_running", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}
	ret = inm_reachable_urls_is_check_running(NULL,
			INM_URL_LIST_TYPE_DEFAULT,
			&is_running);
	CHECK_RETURN("inm_reachable_urls_is_check_running", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_reachable_urls_is_check_running(g_hInm,
			INM_URL_LIST_TYPE_DEFAULT,
			NULL);
	CHECK_RETURN("inm_reachable_urls_is_check_running", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}
