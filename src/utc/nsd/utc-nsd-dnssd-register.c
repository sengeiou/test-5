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
#include <string.h>

#include <system_info.h>
#include <dns-sd.h>

//& set: Nsd-dnssd-register

static GMainLoop* loop = NULL;
static bool registered_callback = false;
static bool g_feature = true;

static void __registered_cb(dnssd_error_e result,
		dnssd_service_h dnssd_service, void *user_data)
{
	return;
}

static gboolean register_timeout(gpointer data)
{
	registered_callback= false;
	g_main_loop_quit(loop);
	g_main_loop_unref(loop);
	loop = NULL;
	return FALSE;
}

static void dnssd_register_reply(dnssd_error_e result,
		dnssd_service_h local_service, void *user_data)
{
	if (result == DNSSD_ERROR_NONE) {
		registered_callback = true;
		g_main_loop_quit(loop);
		g_main_loop_unref(loop);
	}
}

static int wait_for_registered_callback(dnssd_service_h local_service)
{
	int timeout_testcase = 0;
	int ret;

	ret = dnssd_register_local_service(local_service, dnssd_register_reply, NULL);

	if (ret == DNSSD_ERROR_NONE)
	{
		loop = g_main_loop_new(NULL, FALSE);
		timeout_testcase = g_timeout_add(20000, register_timeout, loop);
		g_main_loop_run(loop);
		g_source_remove(timeout_testcase);

		if (!registered_callback)
		{
				ret = -1;
		}
	}
	return ret;
}

/**
 * @function		utc_nsd_dnssd_register_startup
 * @since_tizen		3.0
 * @description		Initializes DNSSD. Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_nsd_dnssd_register_startup(void)
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
 * @function		utc_nsd_dnssd_register_cleanup
 * @since_tizen		3.0
 * @description		Deinitialize DNSSD. Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_nsd_dnssd_register_cleanup(void)
{
	if (g_feature == true) {
		dnssd_deinitialize();
	}
}

/**
 * @testcase		utc_nsd_dnssd_initialize_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Initialize DNSSD.
 * @scenario		Initialize DNSSD.
 *					Ensure no error
 */
int utc_nsd_dnssd_initialize_p(void)
{
	int ret = DNSSD_ERROR_NONE;

	if (g_feature == false) {
		ret = dnssd_initialize();
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}
	dnssd_deinitialize();

	ret = dnssd_initialize();
	assert_eq(ret, DNSSD_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_deinitialize_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Deinitialize DNSSD.
 * @scenario		Deinitialize DNSSD.
 *					Ensure no error
 */
int utc_nsd_dnssd_deinitialize_p(void)
{
	int ret = DNSSD_ERROR_NONE;

	if (g_feature == false) {
		ret = dnssd_deinitialize();
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}
	ret = dnssd_deinitialize();
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_initialize();

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_deinitialize_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_deinitialize before DNSSD is initialized.
 * @scenario		Deinitialize DNSSD and deinitialize again.
 *					Return value should be DNSSD_ERROR_NOT_INITIALIZED.
 */
int utc_nsd_dnssd_deinitialize_n(void)
{
	int ret = DNSSD_ERROR_NONE;

	if (g_feature == false) {
		ret = dnssd_deinitialize();
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}
	dnssd_deinitialize();

	ret = dnssd_deinitialize();
	assert_eq(ret, DNSSD_ERROR_NOT_INITIALIZED);

	dnssd_initialize();

	return 0;
}


/**
 * @testcase		utc_nsd_dnssd_create_local_service_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Create a DNSSD local service handle.
 * @scenario		Create and Destroy a DNSSD local service handle.
 *					Ensure no error
 */
int utc_nsd_dnssd_create_local_service_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_create_local_service(NULL, 0);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_create_local_service_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_create_local_service by passing an invalid parameter.
 * @scenario		Pass NULL as a service handle parameter.
 *					Return value should be DNSSD_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_dnssd_create_local_service_n(void)
{
	int ret = DNSSD_ERROR_NONE;

	if (g_feature == false) {
		ret = dnssd_create_local_service(NULL, 0);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = dnssd_create_local_service("_ftp._tcp", NULL);
	assert_eq(ret, DNSSD_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_destroy_local_service_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Destroy a DNSSD local service handle.
 * @scenario		Create and Destroy a DNSSD local service handle.
 *					Ensure no error
 */
int utc_nsd_dnssd_destroy_local_service_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_destroy_local_service(0);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_destroy_local_service(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_destroy_local_service_n
 * @since_tizen		3.0
 * @type			Negative	
 * @description		Verify dnssd_destroy_local_service by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_detroy_local_service_n(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_destroy_local_service(0);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_destroy_local_service(serv_id + 1);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	dnssd_destroy_local_service(serv_id);

	return 0;

}
/**
 * @testcase		utc_nsd_dnssd_set_name_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Set the service name of a DNSSD local service.
 * @scenario		Create a DNSSD local service and set the service name of the service.
 *					Ensure no error
 */
int utc_nsd_dnssd_set_name_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_service_set_name(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);

	ret = dnssd_service_set_name(serv_id, "test-ftp");
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_set_name_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_set_name by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_set_name_n1(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_service_set_name(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);

	ret = dnssd_service_set_name(serv_id + 1, "test-ftp");
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_set_name_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_set_name by passing invalid service name.
 * @scenario		Create a DNSSD service and set a service name.
 *					Create another DNSSD service and set the same service name as NULL.
 *					Return value should be DNSSD_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_dnssd_set_name_n2(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_service_set_name(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	ret = dnssd_service_set_name(serv_id, NULL);
	assert_eq(ret, DNSSD_ERROR_INVALID_PARAMETER);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_set_port_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Set the port number of a DNSSD local service.
 * @scenario		Create a DNSSD local service and set the port number of the service.
 *					Ensure no error
 */
int utc_nsd_dnssd_set_port_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_service_set_port(0, 0);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_set_port_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_set_port by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_set_port_n1(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_service_set_port(0, 0);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);

	ret = dnssd_service_set_port(serv_id + 1, 1234);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_set_port_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_set_port by passing an invalid port number
 * @scenario		Create a DNSSD service and set a port number as an invalid value.
 *					Return value should be DNSSD_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_dnssd_set_port_n2(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_service_set_port(0, 0);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	ret = dnssd_service_set_port(serv_id, -1234);
	assert_eq(ret, DNSSD_ERROR_INVALID_PARAMETER);

	dnssd_destroy_local_service(serv_id);
	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_set_record_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Verify dnssd_service_set_record by setting dns resource record
 * @scenario		Create a DNSSD service and set a dns resource record.
 *					Ensure no error.
 */
int utc_nsd_dnssd_set_record_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char buff[32] = {0,};
	char *value = "http://www.tizen.org";

	if (g_feature == false) {
		ret = dnssd_service_set_record(0, 0, 0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_name(serv_id, "Tizen");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = wait_for_registered_callback(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	g_strlcpy(buff + 1, value, sizeof(buff));
	buff[0] = strlen(value);

	ret = dnssd_service_set_record(serv_id, 16, buff[0] + 1, (void *)buff);
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_service_unset_record(serv_id, 16);
	dnssd_deregister_local_service(serv_id);
	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_set_record_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_set_record by setting dns resource record
 * @scenario		Create a DNSSD service and pass invalid service ID.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_set_record_n(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char buff[32] = {0,};
	char *value = "http://www.tizen.org";

	if (g_feature == false) {
		ret = dnssd_service_set_record(0, 0, 0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_name(serv_id, "Tizen");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = wait_for_registered_callback(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	g_strlcpy(buff + 1, value, sizeof(buff));
	buff[0] = strlen(value);

	ret = dnssd_service_set_record(serv_id + 1, 16, buff[0], (void *)buff);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	dnssd_service_unset_record(serv_id, 16);
	dnssd_deregister_local_service(serv_id);
	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_unset_record_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Verify dnssd_service_unset_record by removing dns resource record
 * @scenario		Unset DNS resource record after creating & setting a dns resource record.
 *					Ensure no error.
 */
int utc_nsd_dnssd_unset_record_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char buff[32] = {0,};
	char *value = "http://www.tizen.org";

	if (g_feature == false) {
		ret = dnssd_service_unset_record(0, 0);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_name(serv_id, "Tizen");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = wait_for_registered_callback(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	g_strlcpy(buff + 1, value, sizeof(buff));
	buff[0] = strlen(value);

	ret = dnssd_service_set_record(serv_id, 16, buff[0] + 1, (void *)buff);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_unset_record(serv_id, 16);
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_deregister_local_service(serv_id);
	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_unset_record_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_set_record by setting dns resource record
 * @scenario		Create a DNSSD service, set resource record and pass invalid service ID.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_unset_record_n(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char buff[32] = {0,};
	char *value = "http://www.tizen.org";

	if (g_feature == false) {
		ret = dnssd_service_unset_record(0, 0);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_name(serv_id, "Tizen");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = wait_for_registered_callback(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	g_strlcpy(buff + 1, value, sizeof(buff));
	buff[0] = strlen(value);

	ret = dnssd_service_set_record(serv_id, 16, buff[0] + 1, (void *)buff);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_unset_record(serv_id + 1, 16);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	dnssd_service_unset_record(serv_id, 16);
	dnssd_deregister_local_service(serv_id);
	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_add_txt_record_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Verify dnssd_add_txt_record by setting txt record
 * @scenario		Create a DNSSD service and set a dns txt record.
 *					Ensure no error.
 */
int utc_nsd_dnssd_add_txt_record_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char *key = "path";
	char *value = "http://www.tizen.org";

	if (g_feature == false) {
		ret = dnssd_service_add_txt_record(0, NULL, 0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_name(serv_id, "Tizen");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = wait_for_registered_callback(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_add_txt_record(serv_id, key, strlen(value), value);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_remove_txt_record(serv_id, key);

	dnssd_deregister_local_service(serv_id);
	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_add_txt_record_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd__add_txt_record by setting txt record
 * @scenario		Create a DNSSD service and pass invalid service ID.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_add_txt_record_n1(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char *key = "path";
	char *value = "http://www.tizen.org";

	if (g_feature == false) {
		ret = dnssd_service_add_txt_record(0, NULL, 0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_name(serv_id, "Tizen");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = wait_for_registered_callback(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_add_txt_record(serv_id + 1, key, strlen(value), value);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	dnssd_deregister_local_service(serv_id);
	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_add_txt_record_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_add_txt_record by setting txt record
 * @scenario		Create a DNSSD service and pass NULL key and NULL value.
 *					Return value should be DNSSD_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_dnssd_add_txt_record_n2(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_service_add_txt_record(0, NULL, 0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_name(serv_id, "Tizen");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = wait_for_registered_callback(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_add_txt_record(serv_id, NULL, 0, NULL);
	assert_eq(ret, DNSSD_ERROR_INVALID_PARAMETER);

	dnssd_deregister_local_service(serv_id);
	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_get_all_txt_record_p
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_get_all_txt_record
 * @scenario		Get txt resource record after creating & setting a txt record.
 *					Ensure no error.
 */
int utc_nsd_dnssd_get_all_txt_record_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char *key = "path";
	char *value = "http://www.tizen.org";
	void *txt_record = NULL;
	unsigned short length = 0;

	if (g_feature == false) {
		ret = dnssd_service_get_all_txt_record(0, NULL, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_name(serv_id, "Tizen");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = wait_for_registered_callback(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_add_txt_record(serv_id, key, strlen(value), value);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_get_all_txt_record(serv_id, &length, &txt_record);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_remove_txt_record(serv_id, key);

	dnssd_deregister_local_service(serv_id);
	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_get_all_txt_record_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_get_all_txt_record
 * @scenario		Get txt resource record with invalid service ID after creating & setting a txt record.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_get_all_txt_record_n1(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char *key = "path";
	void *txt_record = NULL;
	unsigned short length = 0;

	if (g_feature == false) {
		ret = dnssd_service_get_all_txt_record(0, NULL, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_get_all_txt_record(serv_id + 1, &length, &txt_record);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	ret = dnssd_service_remove_txt_record(serv_id, key);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_get_all_txt_record_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_get_all_txt_record
 * @scenario		Get txt resource record with NULL key after creating & setting a txt record.
 *					Return value should be DNSSD_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_dnssd_get_all_txt_record_n2(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char *key = "path";
	char *value = "http://www.tizen.org";
	unsigned short length = 0;

	if (g_feature == false) {
		ret = dnssd_service_get_all_txt_record(0, NULL, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_add_txt_record(serv_id, key, strlen(value), value);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_get_all_txt_record(serv_id, &length, NULL);
	assert_eq(ret, DNSSD_ERROR_INVALID_PARAMETER);

	ret = dnssd_service_remove_txt_record(serv_id, key);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_remove_txt_record_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Verify dnssd_service_remove_txt_record by removing txt record
 * @scenario		Unset DNS txt record after creating & setting a txt record.
 *					Ensure no error.
 */
int utc_nsd_dnssd_remove_txt_record_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char *key = "path";
	char *value = "http://www.tizen.org";

	if (g_feature == false) {
		ret = dnssd_service_remove_txt_record(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_name(serv_id, "Tizen");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = wait_for_registered_callback(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_add_txt_record(serv_id, key, strlen(value), value);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_remove_txt_record(serv_id, key);
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_deregister_local_service(serv_id);
	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_remove_txt_record_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_remove_unset_txt_record by removing txt record
 * @scenario		Unset DNS resource record with invalid service ID after creating & setting a txt record.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_remove_txt_record_n1(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char *key = "path";
	char *value = "http://www.tizen.org";

	if (g_feature == false) {
		ret = dnssd_service_remove_txt_record(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_name(serv_id, "Tizen");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = wait_for_registered_callback(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_add_txt_record(serv_id, key, strlen(value), value);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_remove_txt_record(serv_id + 1, key);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	dnssd_service_remove_txt_record(serv_id, NULL);
	dnssd_deregister_local_service(serv_id);
	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_remove_txt_record_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_remove_unset_txt_record by removing txt record
 * @scenario		Unset DNS resource record with NULL key after creating & setting a txt record.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_remove_txt_record_n2(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char *key = "path";
	char *value = "http://www.tizen.org";

	if (g_feature == false) {
		ret = dnssd_service_remove_txt_record(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_name(serv_id, "Tizen");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = wait_for_registered_callback(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_add_txt_record(serv_id, key, strlen(value), value);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_remove_txt_record(serv_id, NULL);
	assert_eq(ret, DNSSD_ERROR_INVALID_PARAMETER);

	dnssd_service_remove_txt_record(serv_id, NULL);
	dnssd_deregister_local_service(serv_id);
	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_get_type_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Get the type of a DNSSD service.
 * @scenario		Create a DNSSD local service and get the type of a DNSSD service.
 *					Ensure no error
 */
int utc_nsd_dnssd_get_type_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char *type = NULL;

	if (g_feature == false) {
		ret = dnssd_service_get_type(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);

	ret = dnssd_service_get_type(serv_id, &type);
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_destroy_local_service(serv_id);
	g_free(type);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_get_type_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_get_type by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_get_type_n1(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char *type = NULL;

	if (g_feature == false) {
		ret = dnssd_service_get_type(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);

	ret = dnssd_service_get_type(serv_id + 1, &type);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_get_type_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_get_type by passing an invalid parameter.
 * @scenario		Pass NULL as a service_type parameter for getting the type of a DNSSD service.
 *					Return value should be DNSSD_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_dnssd_get_type_n2(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_service_get_type(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	ret = dnssd_service_get_type(serv_id, NULL);
	assert_eq(ret, DNSSD_ERROR_INVALID_PARAMETER);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_get_name_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Get the service name of a DNSSD service.
 * @scenario		Create a DNSSD local service and get the service name of a DNSSD service.
 *					Ensure no error
 */
int utc_nsd_dnssd_get_name_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char *name = NULL;

	if (g_feature == false) {
		ret = dnssd_service_get_name(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);

	ret = dnssd_service_set_name(serv_id, "test-ftp");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_get_name(serv_id, &name);
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_destroy_local_service(serv_id);
	g_free(name);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_get_name_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_get_name by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_get_name_n1(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	char *name = NULL;

	if (g_feature == false) {
		ret = dnssd_service_get_name(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);

	ret = dnssd_service_get_name(serv_id + 1, &name);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_get_name_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_get_name by passing an invalid parameter
 * @scenario		Pass NULL as a target parameter for getting the service name of a DNSSD service.
 *					Return value should be DNSSD_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_dnssd_get_name_n2(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_service_get_name(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	ret = dnssd_service_get_name(serv_id, NULL);
	assert_eq(ret, DNSSD_ERROR_INVALID_PARAMETER);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_get_port_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Get the port number of a DNSSD service.
 * @scenario		Create a DNSSD local service and get the port number of a DNSSD service.
 *					Ensure no error
 */
int utc_nsd_dnssd_get_port_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	int port = 0;

	if (g_feature == false) {
		ret = dnssd_service_get_port(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_get_port(serv_id, &port);
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_get_port_n1
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_get_port by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_get_port_n1(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;
	int port = 0;

	if (g_feature == false) {
		ret = dnssd_service_get_port(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);

	ret = dnssd_service_get_port(serv_id + 1, &port);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	dnssd_destroy_local_service(serv_id);

	return 0;
}


/**
 * @testcase		utc_nsd_dnssd_get_port_n2
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_service_get_port by passing an invalid parameter
 * @scenario		Pass NULL as a target parameter for getting the port number of a DNSSD service.
 *					Return value should be DNSSD_ERROR_INVALID_PARAMETER.
 */
int utc_nsd_dnssd_get_port_n2(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_service_get_port(0, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	ret = dnssd_service_get_port(serv_id, NULL);
	assert_eq(ret, DNSSD_ERROR_INVALID_PARAMETER);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_register_local_service_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Register a DNSSD local service handle.
 * @scenario		Create a DNSSD service and set a service name and a port number for the service.
 *					Register, Deregister and Destroy the DNSSD service.
 *					Ensure no error
 */
int utc_nsd_dnssd_register_local_service_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_register_local_service(0, NULL, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_name(serv_id, "Tizen");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_register_local_service(serv_id, &__registered_cb, NULL);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = wait_for_registered_callback(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_deregister_local_service(serv_id);
	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_register_local_service_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_register_local_service by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_register_local_service_n(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_register_local_service(0, NULL, NULL);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);

	ret = dnssd_register_local_service(serv_id + 1, &__registered_cb, NULL);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_deregister_local_service_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Deregister a DNSSD local service handle.
 * @scenario		Create a DNSSD service and Register
 *					Deregister and Destroy the DNSSD service.
 *					Ensure no error
 */
int utc_nsd_dnssd_deregister_local_service_p(void)
{
	int ret = DNSSD_ERROR_NONE;
	static dnssd_service_h serv_id;

	if (g_feature == false) {
		ret = dnssd_deregister_local_service(0);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	dnssd_create_local_service("_ftp._tcp", &serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_name(serv_id, "Tizen");
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_service_set_port(serv_id, 12345);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_register_local_service(serv_id, &__registered_cb, NULL);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = wait_for_registered_callback(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	ret = dnssd_deregister_local_service(serv_id);
	assert_eq(ret, DNSSD_ERROR_NONE);

	dnssd_destroy_local_service(serv_id);

	return 0;
}

/**
 * @testcase		utc_nsd_dnssd_deregister_local_service_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify dnssd_deregister_local_service by passing invalid service handle.
 * @scenario		Pass an invalid service handle which has not been created before.
 *					Return value should be DNSSD_ERROR_SERVICE_NOT_FOUND.
 */
int utc_nsd_dnssd_deregister_local_service_n(void)
{
	int ret = DNSSD_ERROR_NONE;

	if (g_feature == false) {
		ret = dnssd_deregister_local_service(0);
		assert_eq(ret, DNSSD_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = dnssd_deregister_local_service(0);
	assert_eq(ret, DNSSD_ERROR_SERVICE_NOT_FOUND);

	return 0;
}
