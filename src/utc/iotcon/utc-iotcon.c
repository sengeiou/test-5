/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <glib.h>
#include <system_info.h>
#include <iotcon.h>

#include "utc-iotcon-common.h"

enum {
	FIND_RESOURCE_N,
	FIND_RESOURCE_P,
	GET_TIMEOUT_N,
	GET_TIMEOUT_P,
	SET_TIMEOUT_N,
	SET_TIMEOUT_P,
	POLLING_GET_INTERVAL_N,
	POLLING_GET_INTERVAL_P,
	POLLING_SET_INTERVAL_N,
	POLLING_SET_INTERVAL_P,
	POLLING_INVOKE_N,
	POLLING_INVOKE_P
};

static int g_timeout_count;
static bool g_result;
static bool g_found;
static bool g_feature;
static GMainLoop *g_loop;

/* ### server side ### */
static iotcon_resource_h g_light_resource;

static gboolean _main_loop_quit_idle(gpointer p)
{
	FN_CALL;
	g_main_loop_quit(g_loop);
	return G_SOURCE_REMOVE;
}

static void _main_loop_quit(bool result)
{
	ICUTC_INFO("result = %d", result);
	g_result = result;
	g_idle_add(_main_loop_quit_idle, NULL);
}

static void _request_handler(iotcon_resource_h resource, iotcon_request_h request,
		void *user_data)
{
	FN_CALL;
}

static void _destroy_resource()
{
	if (g_light_resource) {
		iotcon_resource_destroy(g_light_resource);
		g_light_resource = NULL;
	}
}

static int _create_resource(int tc_index)
{
	int ret;
	iotcon_resource_types_h light_types;
	iotcon_resource_interfaces_h light_ifaces;

	ret = iotcon_resource_types_create(&light_types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_add(light_types, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(light_types);
		return 1;
	}

	ret = iotcon_resource_interfaces_create(&light_ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(light_types);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(light_ifaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(light_ifaces);
		iotcon_resource_types_destroy(light_types);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(light_ifaces, IOTCON_INTERFACE_BATCH);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(light_ifaces);
		iotcon_resource_types_destroy(light_types);
		return 1;
	}

	ret = iotcon_resource_create(LIGHT_RESOURCE_URI,
			light_types,
			light_ifaces,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			_request_handler,
			(void *)tc_index,
			&g_light_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(light_ifaces);
		iotcon_resource_types_destroy(light_types);
		return 1;
	}

	iotcon_resource_interfaces_destroy(light_ifaces);
	iotcon_resource_types_destroy(light_types);

	return 0;
}

static bool _found_resource(iotcon_remote_resource_h resource, iotcon_error_e err,
		void *user_data)
{
	FN_CALL;
	int ret;
	iotcon_query_h query;

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX) {
		g_timeout_count++;

		ret = iotcon_query_create(&query);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_create() Fail(%d)", ret);
			_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_query_set_resource_type(query, LIGHT_RESOURCE_TYPE);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_set_resource_type() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP |IOTCON_CONNECTIVITY_PREFER_UDP,
				query, _found_resource, user_data);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_find_resource() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_query_destroy(query);

		return IOTCON_FUNC_STOP;
	} else if (IOTCON_ERROR_NONE != err) {
		_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	if (g_found)
		return IOTCON_FUNC_STOP;
	g_found = true;

	_main_loop_quit(true);
	return IOTCON_FUNC_STOP;
}

static int _handle_async(int tc_index)
{
	FN_CALL;
	int ret;
	iotcon_query_h query;

	g_loop = g_main_loop_new(NULL, FALSE);

	ret = _create_resource(tc_index);
	if (0 != ret) {
		ICUTC_ERR("_create_resource() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_query_create(&query);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_create() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_query_set_resource_type(query, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_set_resource_type() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}

	ret = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP |IOTCON_CONNECTIVITY_PREFER_UDP,
			query, _found_resource, (void *)tc_index);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_find_resource() Fail(%d)", ret);
		return 1;
	}
	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	_destroy_resource();

	if (true == g_result)
		return 0;
	else
		return 1;
}
/* ##################################################### */

/**
 * @function      utc_iotcon_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_startup(void)
{
	int ret;
	char *path;

	g_found = false;
	g_timeout_count = 0;
	g_feature = false;

	icutc_check_wifi_state();

	ret = system_info_get_platform_bool("http://tizen.org/feature/iot.ocf", &g_feature);
	if (SYSTEM_INFO_ERROR_NONE != ret) {
		ICUTC_ERR("system_info_get_platform_bool() Fail(%d)", ret);
		return;
	}

	ret = icutc_get_svr_db_path(&path);
	if (0 != ret) {
		ICUTC_ERR("icutc_get_svr_db_path() Fail(%d)", ret);
		return;
	}

	ICUTC_INFO("path : %s", path);
	ret = iotcon_initialize(path);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_initialize() Fail(%d)", ret);
		free(path);
		return;
	}
	free(path);
}

/**
 * @function		utc_iotcon_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_cleanup(void)
{
	if (true == g_feature)
		iotcon_deinitialize();
}

/**
 * @testcase      utc_iotcon_set_timeout_n
 * @since_tizen   3.0
 * @description   Test fail setting timeout with invalid parameter.
 */
int utc_iotcon_set_timeout_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_set_timeout(-1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_set_timeout(-1);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_set_timeout(3601);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_set_timeout_p
 * @since_tizen   3.0
 * @description   Test setting timeout.
 */
int utc_iotcon_set_timeout_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_set_timeout(1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_set_timeout(1);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_set_timeout(60);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

/**
 * @testcase      utc_iotcon_get_timeout_n
 * @since_tizen   3.0
 * @description   Test fail getting timeout with invalid parameter.
 */
int utc_iotcon_get_timeout_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_get_timeout(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_get_timeout(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase      utc_iotcon_get_timeout_p
 * @since_tizen   3.0
 * @description   Test getting timeout.
 */
int utc_iotcon_get_timeout_p(void)
{
	int ret;
	int timeout_seconds;

	if (false == g_feature) {
		ret = iotcon_get_timeout(&timeout_seconds);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_set_timeout(10);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_get_timeout(&timeout_seconds);
	ICUTC_ASSERT_EQ(timeout_seconds, 10);

	return 0;
}


static void cb1(const char *pin, void *user_data)
{
}

static void cb2(const char *pin, void *user_data)
{
}

/**
 * @testcase      utc_iotcon_add_generated_pin_cb_n
 * @since_tizen   3.0
 * @description   Test iotcon_add_generated_pin_cb
 */
int utc_iotcon_add_generated_pin_cb_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_add_generated_pin_cb(NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_add_generated_pin_cb(NULL, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase      utc_iotcon_add_generated_pin_cb_p
 * @since_tizen   3.0
 * @description   Test iotcon_add_generated_pin_cb
 */
int utc_iotcon_add_generated_pin_cb_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_add_generated_pin_cb(cb1, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_add_generated_pin_cb(cb1, NULL);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remove_generated_pin_cb_n
 * @since_tizen   3.0
 * @description   Test iotcon_remove_generated_pin_cb
 */
int utc_iotcon_remove_generated_pin_cb_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remove_generated_pin_cb(cb2);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	iotcon_add_generated_pin_cb(cb1, NULL);
	ret = iotcon_remove_generated_pin_cb(cb2);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NO_DATA);
	return 0;
}

/**
 * @testcase      utc_iotcon_remove_generated_pin_cb_p
 * @since_tizen   3.0
 * @description   Test iotcon_remove_generated_pin_cb
 */
int utc_iotcon_remove_generated_pin_cb_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remove_generated_pin_cb(cb1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	iotcon_add_generated_pin_cb(cb1, NULL);
	ret = iotcon_remove_generated_pin_cb(cb1);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_find_resource_n
 * @since_tizen   3.0
 * @description   Test fail finding resource with invalid parameter.
 */
int utc_iotcon_find_resource_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP |IOTCON_CONNECTIVITY_PREFER_UDP,
				NULL, NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	/* cb is NULL */
	ret = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP |IOTCON_CONNECTIVITY_PREFER_UDP,
			NULL, NULL, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_find_resource_p
 * @since_tizen   3.0
 * @description   Test finding resource.
 */
int utc_iotcon_find_resource_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP |IOTCON_CONNECTIVITY_PREFER_UDP,
				NULL, _found_resource, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _handle_async(FIND_RESOURCE_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_polling_get_interval_p
 * @since_tizen   3.0
 * @description   Test get polling interval of iotcon
 */
int utc_iotcon_polling_get_interval_p(void)
{
	int ret;
	int interval;

	if (false == g_feature) {
		ret = iotcon_polling_get_interval(&interval);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_polling_get_interval(&interval);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

/**
 * @testcase      utc_iotcon_polling_get_interval_n
 * @since_tizen   3.0
 * @description   Test fail get polling interval of iotcon
 */
int utc_iotcon_polling_get_interval_n(void)
{
	int ret;
	int interval;

	if (false == g_feature) {
		ret = iotcon_polling_get_interval(&interval);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_polling_get_interval(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_polling_set_interval_p
 * @since_tizen   3.0
 * @description   Test set polling interval of iotcon
 */
int utc_iotcon_polling_set_interval_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_polling_set_interval(100);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_polling_set_interval(100);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

/**
 * @testcase      utc_iotcon_polling_set_interval_n
 * @since_tizen   3.0
 * @description   Test fail set polling interval of iotcon
 */
int utc_iotcon_polling_set_interval_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_polling_set_interval(100);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_polling_set_interval(0);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_polling_invoke_p
 * @since_tizen   3.0
 * @description   Test invoke polling
 */
int utc_iotcon_polling_invoke_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_polling_invoke();
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_polling_invoke();
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

/**
 * @testcase      utc_iotcon_polling_invoke_n
 * @since_tizen   3.0
 * @description   Test fail invoke polling
 */
int utc_iotcon_polling_invoke_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_polling_invoke();
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_polling_invoke();
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

/**
 * @testcase      utc_iotcon_set_device_name_n
 * @since_tizen   3.0
 * @description   Test fail setting device name.
 */
int utc_iotcon_set_device_name_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_set_device_name("device_name");
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_set_device_name(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_set_device_name_p
 * @since_tizen   3.0
 * @description   Test setting device name.
 */
int utc_iotcon_set_device_name_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_set_device_name("device_name");
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_set_device_name("device_name");
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

