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
#include <system_info.h>
#include <iotcon.h>
#include "utc-iotcon-common.h"

//& set: Iotcon

static int g_timeout_count;
static bool g_feature;
static bool g_found;
static bool g_result;
static GMainLoop *g_loop;
static iotcon_resource_h g_light_resource;
static iotcon_presence_h g_presence;


enum {
	PRESENCE_RESPONSE_GET_CONNECTIVITY_TYPE,
	PRESENCE_RESPONSE_GET_HOST_ADDRESS,
	PRESENCE_RESPONSE_GET_RESOURCE_TYPE,
	PRESENCE_RESPONSE_GET_RESULT,
	PRESENCE_RESPONSE_GET_TRIGGER,
};

/**
 * @function      utc_iotcon_presence_response_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_presence_response_startup(void)
{
	int ret;
	char *path;

	g_feature = false;
	g_found = false;
	g_timeout_count = 0;

	icutc_check_wifi_state();

	icutc_get_client_ipv4_address();

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

	ret = iotcon_start_presence(ICUTC_PRESENCE_INTERVAL);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_start_presence() Fail(%d)", ret);
		iotcon_deinitialize();
		return;
	}
}

/**
 * @function      utc_iotcon_presence_response_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_presence_response_cleanup(void)
{
	icutc_free_client_ipv4_address();

	if (true == g_feature) {
		iotcon_stop_presence();
		iotcon_deinitialize();
	}
}

static void _request_handler(iotcon_resource_h resource, iotcon_request_h request,
		void *user_data)
{
	FN_CALL;
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

static void _destroy_resource()
{
	if (g_light_resource) {
		iotcon_resource_destroy(g_light_resource);
		g_light_resource = NULL;
	}
}

static gboolean _presence_response_main_loop_quit_idle(gpointer p)
{
	FN_CALL;
	g_main_loop_quit(g_loop);
	return G_SOURCE_REMOVE;
}

static void _presence_response_main_loop_quit(bool result)
{
	ICUTC_INFO("result = %d", result);
	g_result = result;
	g_idle_add(_presence_response_main_loop_quit_idle, NULL);
}

static void _presence_response_presence_cb(iotcon_presence_h presence,
		iotcon_error_e err, iotcon_presence_response_h response, void *user_data)
{
	FN_CALL;
	int ret;
	int tc_index = GPOINTER_TO_INT(user_data);
	iotcon_connectivity_type_e conn_type;
	char *host_address;
	char *resource_type;
	iotcon_presence_result_e result;
	iotcon_presence_trigger_e trigger;

	if (IOTCON_ERROR_NONE != err)
		return;

	switch (tc_index) {
	case PRESENCE_RESPONSE_GET_CONNECTIVITY_TYPE:
		ret = iotcon_presence_response_get_connectivity_type(response, &conn_type);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_presence_response_get_connectivity_type() Fail(%d)", ret);
			_presence_response_main_loop_quit(false);
		}
		_presence_response_main_loop_quit(true);
		return;
	case PRESENCE_RESPONSE_GET_HOST_ADDRESS:
		ret = iotcon_presence_response_get_host_address(response, &host_address);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_presence_response_get_host_address() Fail(%d)", ret);
			_presence_response_main_loop_quit(false);
		}
		_presence_response_main_loop_quit(true);
		return;
	case PRESENCE_RESPONSE_GET_RESOURCE_TYPE:
		ret = iotcon_presence_response_get_resource_type(response, &resource_type);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_presence_response_get_resource_type() Fail(%d)", ret);
			_presence_response_main_loop_quit(false);
		}
		_presence_response_main_loop_quit(true);
		return;
	case PRESENCE_RESPONSE_GET_RESULT:
		ret = iotcon_presence_response_get_result(response, &result);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_presence_response_get_result() Fail(%d)", ret);
			_presence_response_main_loop_quit(false);
		}
		_presence_response_main_loop_quit(true);
		return;
	case PRESENCE_RESPONSE_GET_TRIGGER:
		ret = iotcon_presence_response_get_trigger(response, &trigger);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_presence_response_get_trigger() Fail(%d)", ret);
			_presence_response_main_loop_quit(false);
		}
		_presence_response_main_loop_quit(true);
		return;
	default:
		ICUTC_ERR("Invalid tc_index(%d)", tc_index);
		_presence_response_main_loop_quit(false);
		return;
	}
}

static gboolean _presence_response_update_resource(gpointer p)
{
	FN_CALL;
	iotcon_resource_bind_interface(g_light_resource, IOTCON_INTERFACE_BATCH);
	return G_SOURCE_REMOVE;
}


static bool _found_resource(iotcon_remote_resource_h resource, iotcon_error_e err,
		void *user_data)
{
	FN_CALL;
	int ret;
	char *host_address;
	iotcon_query_h query;
	iotcon_connectivity_type_e conn_type;

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX) {
		g_timeout_count++;

		ret = iotcon_query_create(&query);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_create() Fail(%d)", ret);
			_presence_response_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_query_set_resource_type(query, LIGHT_RESOURCE_TYPE);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_set_resource_type() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_presence_response_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY,
				query, _found_resource, user_data);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_find_resource() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_presence_response_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_query_destroy(query);

		return IOTCON_FUNC_STOP;
	} else if (IOTCON_ERROR_NONE != err) {
		_presence_response_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	if (g_found)
		return IOTCON_FUNC_STOP;

	g_found = true;

	iotcon_remote_resource_get_host_address(resource, &host_address);
	ICUTC_INFO("expected host_address[%s], found host_address[%s]", g_ipv4_address, host_address);

	if (strstr(host_address, g_ipv4_address) == NULL) { // targeted resource, BUT wrong device, so skip this resource and try again
		g_found = false;
		return IOTCON_FUNC_CONTINUE;
	}

	iotcon_remote_resource_get_connectivity_type(resource, &conn_type);

	ret = iotcon_add_presence_cb(host_address, conn_type, LIGHT_RESOURCE_TYPE,
			_presence_response_presence_cb, user_data, &g_presence);

	g_idle_add(_presence_response_update_resource, NULL);

	return IOTCON_FUNC_STOP;
}


static int _handle_presence_response_async(int tc_index)
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


	ret = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY,
			query, _found_resource, GINT_TO_POINTER(tc_index));
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_find_resource() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}
	iotcon_query_destroy(query);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	_destroy_resource();

	if (true == g_result)
		return 0;
	else
		return 1;
}

/**
 * @testcase      utc_iotcon_presence_response_get_result_p
 * @since_tizen   3.0
 * @description   Test getting result of presence response.
 */
int utc_iotcon_presence_response_get_result_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_presence_response_get_result(NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _handle_presence_response_async(PRESENCE_RESPONSE_GET_RESULT);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_response_get_trigger_p
 * @since_tizen   3.0
 * @description   Test getting trigger of presence response.
 */
int utc_iotcon_presence_response_get_trigger_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_presence_response_get_trigger(NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _handle_presence_response_async(PRESENCE_RESPONSE_GET_TRIGGER);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_response_get_connectivity_type_p
 * @since_tizen   3.0
 * @description   Test getting connectivity type of presence response.
 */
int utc_iotcon_presence_response_get_connectivity_type_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_presence_response_get_connectivity_type(NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _handle_presence_response_async(PRESENCE_RESPONSE_GET_CONNECTIVITY_TYPE);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_response_get_resource_type_p
 * @since_tizen   3.0
 * @description   Test getting resource type of presence response.
 */
int utc_iotcon_presence_response_get_resource_type_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_presence_response_get_resource_type(NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _handle_presence_response_async(PRESENCE_RESPONSE_GET_RESOURCE_TYPE);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}


/**
 * @testcase      utc_iotcon_presence_response_get_host_address_p
 * @since_tizen   3.0
 * @description   Test getting host address of presence response.
 */
int utc_iotcon_presence_response_get_host_address_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_presence_response_get_host_address(NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _handle_presence_response_async(PRESENCE_RESPONSE_GET_HOST_ADDRESS);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

