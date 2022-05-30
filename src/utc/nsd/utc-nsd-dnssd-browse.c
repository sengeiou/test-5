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
#include <dns-sd.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>

#include <system_info.h>
//& set: Nsd-dnssd-browse

static bool g_feature = true;

static void __found_cb(dnssd_service_state_e state, dnssd_service_h dnssd_service, void *user_data)
{
	return;
}

/**
 * @function		utc_nsd_dnssd_browse_startup
 * @since_tizen		3.0
 * @description		Initializes DNSSD. Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_nsd_dnssd_browse_startup(void)
{
	int ret = DNSSD_ERROR_NONE;
	ret = system_info_get_platform_bool("http://tizen.org/feature/network.service_discovery.dnssd", &g_feature);

	if (SYSTEM_INFO_ERROR_NONE != ret) {
		fprintf(stderr, "system_info_get_platform_bool() Fail(%d)\n", ret);
		return;
	}

	if (g_feature == true) {
		ret = dnssd_initialize();
		if (ret != DNSSD_ERROR_NONE) {
			fprintf(stderr, "dnssd_initialize() Fail(%d)", ret);
			return;
		}
	}
}

/**
 * @function		utc_nsd_dnssd_browse_cleanup
 * @since_tizen		3.0
 * @description		Deinitialize DNSSD. Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_nsd_dnssd_browse_cleanup(void)
{
	int ret = DNSSD_ERROR_NONE;

	if (g_feature == true) {
		ret = dnssd_deinitialize();
		if (ret != DNSSD_ERROR_NONE) {
			fprintf(stderr, "dnssd_deinitialize() Fail(%d)", ret);
			return;
		}
	}
}

/**
 * @testcase		utc_nsd_dnssd_start_browsing_service_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Start browsing DNSSD services
 * @scenario		Start browsing DNSSD services with a service type
 *					Ensure no error
 */
int utc_nsd_dnssd_start_browsing_service_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	dnssd_browser_h browser_id = 0;

	if (g_feature == false) {
		ret = dnssd_start_browsing_service(NULL, NULL, NULL, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = dnssd_start_browsing_service("_ftp._tcp", &browser_id, &__found_cb, NULL);
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_stop_browsing_service(browser_id);
	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_start_browsing_service_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_start_browsing_service by passing invalid browser handle
 * @scenario		Pass NULL as a browser handle
 *					Return value should be DNSSD_ERROR_INVALID_PARAMETER
 */
int utc_nsd_dnssd_start_browsing_service_n(void)
{
	int ret = DNSSD_ERROR_NONE;

	if (g_feature == false) {
		ret = dnssd_start_browsing_service(NULL, NULL, NULL, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = dnssd_start_browsing_service("_ftp._tcp", NULL, &__found_cb, NULL);
	assert_eq(ret, DNSSD_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_stop_browsing_service_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Stop browsing DNSSD services
 * @scenario		Start browsing DNSSD services with a service type
 *					Stop browsing with valid browser handle
 *					Ensure no error
 */
int utc_nsd_dnssd_stop_browsing_service_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	dnssd_browser_h browser_id = 0;

	if (g_feature == false) {
		ret = dnssd_stop_browsing_service(0);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = dnssd_start_browsing_service("_ftp._tcp", &browser_id, &__found_cb, NULL);
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_stop_browsing_service(browser_id);
	assert_eq(ret, DNSSD_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_stop_browsing_service_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_stop_browsing_service by passing invalid browser handle
 * @scenario		Start browsing DNSSD services with a service target
 *					Stop browsing by passing an invalid browser handle
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND
 */
int utc_nsd_dnssd_stop_browsing_service_n(void)
{
	int ret = DNSSD_ERROR_NONE;
	dnssd_browser_h browser_id = 0;

	if (g_feature == false) {
		ret = dnssd_stop_browsing_service(0);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = dnssd_start_browsing_service("_ftp._tcp", &browser_id, &__found_cb, NULL);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_stop_browsing_service(0);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	dnssd_stop_browsing_service(browser_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_service_get_ip_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_get_ip by passing invalid browser handle
 * @scenario		get IP address by invalid browser handle
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND
 */
int utc_nsd_dnssd_service_get_ip_n1(void)
{
	int ret = DNSSD_ERROR_NONE;
	dnssd_service_h service_id = 0;
	char *ip_v4_address = NULL;

	if (g_feature == false) {
		ret = dnssd_service_get_ip(service_id, NULL, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = dnssd_service_get_ip(service_id, &ip_v4_address, NULL);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_service_get_ip_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_get_ip by passing invalid parameter
 * @scenario		get IP address by invalid parameter
 *					Return value should be DNSSD_ERROR_INVALID_PARAMETER
 */
int utc_nsd_dnssd_service_get_ip_n2(void)
{
	int ret = DNSSD_ERROR_NONE;
	dnssd_service_h service_id = 0;

	if (g_feature == false) {
		ret = dnssd_service_get_ip(service_id, NULL, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = dnssd_service_get_ip(service_id, NULL, NULL);
	assert_eq(ret, DNSSD_ERROR_INVALID_PARAMETER);

	return 0;
}
