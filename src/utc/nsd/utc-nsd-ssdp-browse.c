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
#include <ssdp.h>
#include <stdlib.h>
#include <glib.h>
#include <system_info.h>

//& set: Nsd-ssdp-browse

static GMainLoop* g_loop = NULL;
static bool g_feature = true;

static void __found_cb(ssdp_service_state_e state, ssdp_service_h ssdp_service, void *user_data)
{
	return;
}

/**
 * @function		utc_nsd_ssdp_browse_startup
 * @since_tizen		3.0
 * @description		Initializes SSDP. Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_nsd_ssdp_browse_startup(void)
{
	int ret = SSDP_ERROR_NONE;
	ret = system_info_get_platform_bool("http://tizen.org/feature/network.service_discovery.ssdp", &g_feature);

	if (SYSTEM_INFO_ERROR_NONE != ret) {
		fprintf(stderr, "system_info_get_platform_bool() Fail(%d)\n", ret);
		return;
	}

	if (g_feature == true) {
		ret = ssdp_initialize();
		if (ret != SSDP_ERROR_NONE) {
			fprintf(stderr, "dnssd_initialize() Fail(%d)", ret);
			return;
		}
		g_loop = g_main_loop_new(NULL, FALSE);
	}
}

/**
 * @function		utc_nsd_ssdp_browse_cleanup
 * @since_tizen		3.0
 * @description		Deinitialize SSDP. Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_nsd_ssdp_browse_cleanup(void)
{
	if (g_feature == true) {
		ssdp_deinitialize();
		g_main_loop_unref(g_loop);
		g_loop = NULL;
	}
}

/**
 * @testcase		utc_nsd_ssdp_start_browsing_service_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Start browsing SSDP services
 * @scenario		Start browsing SSDP services with a service target
 *					Ensure no error
 */
int utc_nsd_ssdp_start_browsing_service_p(void)
{
	int ret = SSDP_ERROR_NONE;
	ssdp_browser_h browser_id = 0;

	if (g_feature == false) {
		ret = ssdp_start_browsing_service(NULL, NULL, NULL, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ssdp_start_browsing_service("upnp:rootdevice", &browser_id, &__found_cb, NULL);
	assert_eq(ret, SSDP_ERROR_NONE);

	ssdp_stop_browsing_service(browser_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_start_browsing_service_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_start_browsing_service by passing invalid browser handle
 * @scenario		Pass NULL as a browser handle
 *					Return value should be SSDP_ERROR_INVALID_PARAMETER
 */
int utc_nsd_ssdp_start_browsing_service_n(void)
{
	int ret = SSDP_ERROR_NONE;

	if (g_feature == false) {
		ret = ssdp_start_browsing_service(NULL, NULL, NULL, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ssdp_start_browsing_service("upnp:rootdevice", NULL, &__found_cb, NULL);
	assert_eq(ret, SSDP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_stop_browsing_service_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Stop browsing SSDP services
 * @scenario		Start browsing SSDP services with a service target
 *					Stop browsing with valid browser handle
 *					Ensure no error
 */
int utc_nsd_ssdp_stop_browsing_service_p(void)
{
	int ret = SSDP_ERROR_NONE;
	ssdp_browser_h browser_id = 0;

	if (g_feature == false) {
		ret = ssdp_stop_browsing_service(0);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ssdp_start_browsing_service("upnp:rootdevice", &browser_id, &__found_cb, NULL);
	assert_eq(ret, SSDP_ERROR_NONE);

	ssdp_stop_browsing_service(browser_id);
	assert_eq(ret, SSDP_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_stop_browsing_service_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_stop_browsing_service by passing invalid browser handle
 * @scenario		Start browsing SSDP services with a service target
 *					Stop browsing by passing an invalid browser handle
 *					Return value should be SSDP_ERROR_INVALID_PARAMETER
 */
int utc_nsd_ssdp_stop_browsing_service_n1(void)
{
	int ret = SSDP_ERROR_NONE;
	ssdp_browser_h browser_id = 0;

	if (g_feature == false) {
		ret = ssdp_stop_browsing_service(0);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ssdp_start_browsing_service("upnp:rootdevice", &browser_id, &__found_cb, NULL);
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_stop_browsing_service(0);
	assert_eq(ret, SSDP_ERROR_INVALID_PARAMETER);

	ssdp_stop_browsing_service(browser_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_stop_browsing_service_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_stop_browsing_service by passing invalid browser handle
 * @scenario		Start browsing SSDP services with a service target
 *					Stop browsing by passing an invalid browser handle which has not been created before
 *					Return value should be SSDP_SERVICE_NOT_FOUND
 */
int utc_nsd_ssdp_stop_browsing_service_n2(void)
{
	int ret = SSDP_ERROR_NONE;
	ssdp_browser_h browser_id = 0;

	if (g_feature == false) {
		ret = ssdp_stop_browsing_service(0);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ssdp_start_browsing_service("upnp:rootdevice", &browser_id, &__found_cb, NULL);
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_stop_browsing_service(browser_id + 1);
	assert_eq(ret, SSDP_ERROR_SERVICE_NOT_FOUND);

	ssdp_stop_browsing_service(browser_id);

	return 0;
}
