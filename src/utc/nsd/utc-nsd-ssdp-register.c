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
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <system_info.h>

//& set: Nsd-ssdp-register

static GMainLoop* g_loop = NULL;
static bool g_feature = true;

static void __registered_cb(ssdp_error_e result, ssdp_service_h ssdp_service, void *user_data)
{
	return;
}

/**
 * @function		utc_nsd_ssdp_register_startup
 * @since_tizen		3.0
 * @description		Initializes SSDP. Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_nsd_ssdp_register_startup(void)
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
 * @function		utc_nsd_ssdp_register_cleanup
 * @since_tizen		3.0
 * @description		Deinitialize SSDP. Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_nsd_ssdp_register_cleanup(void)
{
	if (g_feature == true) {
		ssdp_deinitialize();
		g_main_loop_unref(g_loop);
		g_loop = NULL;
	}
}

/**
 * @testcase		utc_nsd_ssdp_initialize_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Initialize SSDP.
 * @scenario		Initialize SSDP.
 *					Ensure no error
 */
int utc_nsd_ssdp_initialize_p(void)
{
	int ret = SSDP_ERROR_NONE;

	if (g_feature == false) {
		ret = ssdp_initialize();
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}
	ssdp_deinitialize();

	ret = ssdp_initialize();
	assert_eq(ret, SSDP_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_deinitialize_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Deinitialize SSDP.
 * @scenario		Deinitialize SSDP.
 *					Ensure no error
 */
int utc_nsd_ssdp_deinitialize_p(void)
{
	int ret = SSDP_ERROR_NONE;

	if (g_feature == false) {
		ret = ssdp_deinitialize();
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}
	ret = ssdp_deinitialize();
	assert_eq(ret, SSDP_ERROR_NONE);

	ssdp_initialize();

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_deinitialize_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_deinitialize before SSDP is initialized.
 * @scenario		Deinitialize SSDP and deinitialize again.
 *					Return value should be SSDP_ERROR_NOT_INITIALIZED.
 */
int utc_nsd_ssdp_deinitialize_n(void)
{
	int ret = SSDP_ERROR_NONE;

	if (g_feature == false) {
		ret = ssdp_deinitialize();
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}
	ssdp_deinitialize();

	ret = ssdp_deinitialize();
	assert_eq(ret, SSDP_ERROR_NOT_INITIALIZED);

	ssdp_initialize();

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_create_local_service_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Create a SSDP local service handle.
 * @scenario		Create and Destroy a SSDP local service handle.
 *					Ensure no error
 */
int utc_nsd_ssdp_create_local_service_p(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;

	if (g_feature == false) {
		ret = ssdp_create_local_service(NULL, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ssdp_create_local_service("upnp:rootdevice", &serv_id);
	assert_eq(ret, SSDP_ERROR_NONE);

	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_create_local_service_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_create_local_service by passing an invalid parameter.
 * @scenario		Pass NULL as a service handle parameter.
 *					Return value should be SSDP_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_ssdp_create_local_service_n(void)
{
	int ret = SSDP_ERROR_NONE;

	if (g_feature == false) {
		ret = ssdp_create_local_service(NULL, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ssdp_create_local_service("upnp:rootdevice", NULL);
	assert_eq(ret, SSDP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_destroy_local_service_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Destroy a SSDP local service handle.
 * @scenario		Create and Destroy a SSDP local service handle.
 *					Ensure no error
 */
int utc_nsd_ssdp_destroy_local_service_p(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;

	if (g_feature == false) {
		ret = ssdp_destroy_local_service(0);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ssdp_create_local_service("upnp:rootdevice", &serv_id);
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_destroy_local_service(serv_id);
	assert_eq(ret, SSDP_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_destroy_local_service_n
 * @since_tizen		3.0
 * @type			Negative	
 * @description		Verify ssdp_destroy_local_service by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be SSDP_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_ssdp_detroy_local_service_n(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;

	if (g_feature == false) {
		ret = ssdp_destroy_local_service(0);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ssdp_create_local_service("upnp:rootdevice", &serv_id);
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_destroy_local_service(serv_id + 1);
	assert_eq(ret, SSDP_ERROR_SERVICE_NOT_FOUND);

	ssdp_destroy_local_service(serv_id);

	return 0;

}

/**
 * @testcase		utc_nsd_ssdp_set_usn_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Set the USN of a SSDP local service.
 * @scenario		Create a SSDP local service and set the USN of the service.
 *					Ensure no error
 */
int utc_nsd_ssdp_set_usn_p(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;

	if (g_feature == false) {
		ret = ssdp_service_set_usn(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);

	ret = ssdp_service_set_usn(serv_id, "uuid:1234abce");
	assert_eq(ret, SSDP_ERROR_NONE);

	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_set_usn_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_service_set_usn by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be SSDP_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_ssdp_set_usn_n1(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;
	static ssdp_service_h other_serv_id;

	if (g_feature == false) {
		ret = ssdp_service_set_usn(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);

	ret = ssdp_service_set_usn(serv_id + 1, "uuid:1234abce");
	assert_eq(ret, SSDP_ERROR_SERVICE_NOT_FOUND);

	ssdp_destroy_local_service(other_serv_id);
	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_set_usn_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_service_set_usn by passing a duplicate USN.
 * @scenario		Create a SSDP service and set a USN.
 *					Create another SSDP service and set the same USN as that of the first SSDP service.
 *					Return value should be SSDP_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_ssdp_set_usn_n2(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;
	static ssdp_service_h other_serv_id;

	if (g_feature == false) {
		ret = ssdp_service_set_usn(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);
	ssdp_service_set_usn(serv_id, "uuid:1234abce");

	ssdp_create_local_service("upnp:rootdevice", &other_serv_id);
	ret = ssdp_service_set_usn(serv_id, "uuid:1234abce");
	assert_eq(ret, SSDP_ERROR_INVALID_PARAMETER);

	ssdp_destroy_local_service(other_serv_id);
	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_set_url_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Set the URL of a SSDP local service.
 * @scenario		Create a SSDP local service and set the URL of the service.
 *					Ensure no error
 */
int utc_nsd_ssdp_set_url_p(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;

	if (g_feature == false) {
		ret = ssdp_service_set_url(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);

	ret = ssdp_service_set_url(serv_id, "192.168.0.1");
	assert_eq(ret, SSDP_ERROR_NONE);

	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_set_url_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_service_set_url by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be SSDP_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_ssdp_set_url_n1(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;
	static ssdp_service_h other_serv_id;

	if (g_feature == false) {
		ret = ssdp_service_set_url(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);

	ret = ssdp_service_set_url(serv_id + 1, "192.168.0.1");
	assert_eq(ret, SSDP_ERROR_SERVICE_NOT_FOUND);

	ssdp_destroy_local_service(other_serv_id);
	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_set_url_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_service_set_usn by passing a duplicate URL.
 * @scenario		Create a SSDP service and set a URL.
 *					Create another SSDP service and set the same URL as that of the first SSDP service.
 *					Return value should be SSDP_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_ssdp_set_url_n2(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;
	static ssdp_service_h other_serv_id;

	if (g_feature == false) {
		ret = ssdp_service_set_url(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);
	ssdp_service_set_url(serv_id, "192.168.0.1");

	ssdp_create_local_service("upnp:rootdevice", &other_serv_id);
	ret = ssdp_service_set_url(serv_id, "192.168.0.1");
	assert_eq(ret, SSDP_ERROR_INVALID_PARAMETER);

	ssdp_destroy_local_service(other_serv_id);
	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_get_target_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Get the target of a SSDP service.
 * @scenario		Create a SSDP local service and get the target of a SSDP service.
 *					Ensure no error
 */
int utc_nsd_ssdp_get_target_p(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;
	char *target = NULL;

	if (g_feature == false) {
		ret = ssdp_service_get_target(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);

	ret = ssdp_service_get_target(serv_id, &target);
	assert_eq(ret, SSDP_ERROR_NONE);

	ssdp_destroy_local_service(serv_id);
	g_free(target);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_get_target_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_service_get_target by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be SSDP_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_ssdp_get_target_n1(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;
	char *target = NULL;

	if (g_feature == false) {
		ret = ssdp_service_get_target(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);

	ret = ssdp_service_get_target(serv_id + 1, &target);
	assert_eq(ret, SSDP_ERROR_SERVICE_NOT_FOUND);

	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_get_target_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_service_get_target by passing an invalid parameter.
 * @scenario		Pass NULL as a target parameter for getting the target of a SSDP service.
 *					Return value should be SSDP_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_ssdp_get_target_n2(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;

	if (g_feature == false) {
		ret = ssdp_service_get_target(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);

	ret = ssdp_service_get_target(serv_id, NULL);
	assert_eq(ret, SSDP_ERROR_INVALID_PARAMETER);

	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_get_usn_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Get the USN of a SSDP service.
 * @scenario		Create a SSDP local service and get the USN of a SSDP service.
 *					Ensure no error
 */
int utc_nsd_ssdp_get_usn_p(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;
	char *usn = NULL;

	if (g_feature == false) {
		ret = ssdp_service_get_usn(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);

	ret = ssdp_service_set_usn(serv_id, "uuid:1234abce");
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_service_get_usn(serv_id, &usn);
	assert_eq(ret, SSDP_ERROR_NONE);

	ssdp_destroy_local_service(serv_id);
	g_free(usn);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_get_usn_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_service_get_usn by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be SSDP_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_ssdp_get_usn_n1(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;
	char *usn = NULL;

	if (g_feature == false) {
		ret = ssdp_service_get_usn(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);

	ret = ssdp_service_get_usn(serv_id + 1, &usn);
	assert_eq(ret, SSDP_ERROR_SERVICE_NOT_FOUND);

	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_get_usn_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_service_get_usn by passing an invalid parameter
 * @scenario		Pass NULL as a target parameter for getting the USN of a SSDP service.
 *					Return value should be SSDP_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_ssdp_get_usn_n2(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;

	if (g_feature == false) {
		ret = ssdp_service_get_usn(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);

	ret = ssdp_service_get_usn(serv_id, NULL);
	assert_eq(ret, SSDP_ERROR_INVALID_PARAMETER);

	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_get_url_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Get the URL of a SSDP service.
 * @scenario		Create a SSDP local service and get the URL of a SSDP service.
 *					Ensure no error
 */
int utc_nsd_ssdp_get_url_p(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;
	char *url = NULL;

	if (g_feature == false) {
		ret = ssdp_service_get_url(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);

	ret = ssdp_service_set_url(serv_id, "192.168.0.1");
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_service_get_url(serv_id, &url);
	assert_eq(ret, SSDP_ERROR_NONE);

	ssdp_destroy_local_service(serv_id);
	g_free(url);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_get_url_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_service_get_url by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be SSDP_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_ssdp_get_url_n1(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;
	char *url = NULL;

	if (g_feature == false) {
		ret = ssdp_service_get_url(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);

	ret = ssdp_service_get_url(serv_id + 1, &url);
	assert_eq(ret, SSDP_ERROR_SERVICE_NOT_FOUND);

	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_get_url_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_service_get_url by passing an invalid parameter
 * @scenario		Pass NULL as a target parameter for getting the URL of a SSDP service.
 *					Return value should be SSDP_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_ssdp_get_url_n2(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;

	if (g_feature == false) {
		ret = ssdp_service_get_url(0, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);

	ret = ssdp_service_get_url(serv_id, NULL);
	assert_eq(ret, SSDP_ERROR_INVALID_PARAMETER);

	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_register_local_service_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Register a SSDP local service handle.
 * @scenario		Create a SSDP service and set a USN and a URL for the service.
 *					Register, Deregister and Destroy the SSDP service.
 *					Ensure no error
 */
int utc_nsd_ssdp_register_local_service_p(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;

	if (g_feature == false) {
		ret = ssdp_register_local_service(0, NULL, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ssdp_create_local_service("upnp:rootdevice", &serv_id);
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_service_set_usn(serv_id, "uuid:1234abce");
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_service_set_url(serv_id, "192.168.0.1");
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_register_local_service(serv_id, &__registered_cb, NULL);
	assert_eq(ret, SSDP_ERROR_NONE);

	ssdp_deregister_local_service(serv_id);
	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_register_local_service_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_register_local_service by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be SSDP_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_ssdp_register_local_service_n1(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;

	if (g_feature == false) {
		ret = ssdp_register_local_service(0, NULL, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ssdp_create_local_service("upnp:rootdevice", &serv_id);
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_service_set_usn(serv_id, "uuid:1234abce");
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_service_set_url(serv_id, "192.168.0.1");
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_register_local_service(serv_id + 1, &__registered_cb, NULL);
	assert_eq(ret, SSDP_ERROR_SERVICE_NOT_FOUND);

	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_register_local_service_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_register_local_service by registering the duplcate service
 * @scenario		Create and Register a SSDP service.
 *					Register the service already registered again.
 *					Return value should be SSDP_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_ssdp_register_local_service_n2(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;

	if (g_feature == false) {
		ret = ssdp_register_local_service(0, NULL, NULL);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ssdp_create_local_service("upnp:rootdevice", &serv_id);
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_service_set_usn(serv_id, "uuid:1234abce");
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_service_set_url(serv_id, "192.168.0.1");
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_register_local_service(serv_id, &__registered_cb, NULL);
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_register_local_service(serv_id, &__registered_cb, NULL);
	assert_eq(ret, SSDP_ERROR_INVALID_PARAMETER);

	ssdp_deregister_local_service(serv_id);
	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_deregister_local_service_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Deregister a SSDP local service handle.
 * @scenario		Create a SSDP service and Register
 *					Deregister and Destroy the SSDP service.
 *					Ensure no error
 */
int utc_nsd_ssdp_deregister_local_service_p(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;

	if (g_feature == false) {
		ret = ssdp_deregister_local_service(0);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ssdp_create_local_service("upnp:rootdevice", &serv_id);
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_service_set_usn(serv_id, "uuid:1234abce");
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_service_set_url(serv_id, "192.168.0.1");
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_register_local_service(serv_id, &__registered_cb, NULL);
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_deregister_local_service(serv_id);
	assert_eq(ret, SSDP_ERROR_NONE);

	ssdp_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_ssdp_deregister_local_service_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify ssdp_deregister_local_service by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be SSDP_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_ssdp_deregister_local_service_n(void)
{
	int ret = SSDP_ERROR_NONE;
	static ssdp_service_h serv_id;

	if (g_feature == false) {
		ret = ssdp_deregister_local_service(0);
		assert_eq(ret, SSDP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ssdp_create_local_service("upnp:rootdevice", &serv_id);
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_service_set_usn(serv_id, "uuid:1234abce");
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_service_set_url(serv_id, "192.168.0.1");
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_register_local_service(serv_id, &__registered_cb, NULL);
	assert_eq(ret, SSDP_ERROR_NONE);

	ret = ssdp_deregister_local_service(serv_id + 1);
	assert_eq(ret, SSDP_ERROR_SERVICE_NOT_FOUND);

	ssdp_deregister_local_service(serv_id);
	ssdp_destroy_local_service(serv_id);

	return 0;
}
