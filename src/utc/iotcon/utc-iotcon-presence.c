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
	PRESENCE_ADD_PRESENCE_CB_P,
	PRESENCE_ADD_PRESENCE_CB_N,
	PRESENCE_REMOVE_PRESENCE_CB_P,
	PRESENCE_REMOVE_PRESENCE_CB_N,
	PRESENCE_GET_HOST_ADDR_P,
	PRESENCE_GET_HOST_ADDR_N,
	PRESENCE_GET_CONN_TYPE_P,
	PRESENCE_GET_CONN_TYPE_N,
	PRESENCE_GET_RSRC_TYPE_P,
	PRESENCE_GET_RSRC_TYPE_N,
	PRESENCE_RESPONSE_GET_RESULT_P,
	PRESENCE_RESPONSE_GET_RESULT_N,
	PRESENCE_RESPONSE_GET_TRIGGER_P,
	PRESENCE_RESPONSE_GET_TRIGGER_N,
	PRESENCE_RESPONSE_GET_HOST_ADDR_P,
	PRESENCE_RESPONSE_GET_HOST_ADDR_N,
	PRESENCE_RESPONSE_GET_CONN_TYPE_P,
	PRESENCE_RESPONSE_GET_CONN_TYPE_N,
	PRESENCE_RESPONSE_GET_RSRC_TYPE_P,
	PRESENCE_RESPONSE_GET_RSRC_TYPE_N,
};

#define PRESENCE_LIGHT_RESOURCE_TYPE "core.light"
#define PRESENCE_LIGHT_RESOURCE_URI "/a/light"

static bool g_found;
static int g_timeout_count;
static bool g_result;
static bool g_feature;
static GMainLoop *g_loop;

/* ### server side ### */
static iotcon_resource_h g_light_resource;
static iotcon_presence_h g_presence;

static gboolean _presence_main_loop_quit_idle(gpointer p)
{
	FN_CALL;
	g_main_loop_quit(g_loop);
	return G_SOURCE_REMOVE;
}

static void _presence_main_loop_quit(bool result)
{
	ICUTC_INFO("result = %d", result);
	g_result = result;
	g_idle_add(_presence_main_loop_quit_idle, NULL);
}


static void _presence_request_handler(iotcon_resource_h resource,
		iotcon_request_h request, void *user_data)
{
	FN_CALL;
}

static void _presence_destroy_resource()
{
	if (g_light_resource) {
		iotcon_resource_destroy(g_light_resource);
		g_light_resource = NULL;
	}
}

static int _presence_create_resource(int tc_index)
{
	FN_CALL;
	int ret;
	iotcon_resource_types_h light_types;
	iotcon_resource_interfaces_h light_ifaces;

	ret = iotcon_resource_types_create(&light_types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_add(light_types, PRESENCE_LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(light_types);
		return ret;
	}

	ret = iotcon_resource_interfaces_create(&light_ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(light_types);
		return ret;
	}

	ret = iotcon_resource_interfaces_add(light_ifaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(light_ifaces);
		iotcon_resource_types_destroy(light_types);
		return ret;
	}

	ret = iotcon_resource_interfaces_add(light_ifaces, IOTCON_INTERFACE_BATCH);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(light_ifaces);
		iotcon_resource_types_destroy(light_types);
		return ret;
	}

	ret = iotcon_resource_create(PRESENCE_LIGHT_RESOURCE_URI, light_types,
			light_ifaces,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			_presence_request_handler,
			(void *)tc_index,
			&g_light_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(light_ifaces);
		iotcon_resource_types_destroy(light_types);
		return ret;
	}

	iotcon_resource_interfaces_destroy(light_ifaces);
	iotcon_resource_types_destroy(light_types);

	return 0;
}

static void _presence_handler(iotcon_presence_h presence, iotcon_error_e err,
		iotcon_presence_response_h response, void *user_data)
{
	FN_CALL;
}

static bool _presence_found_resource(iotcon_remote_resource_h resource,
		iotcon_error_e err, void *user_data)
{
	FN_CALL;
	int ret;
	iotcon_query_h query;
	iotcon_connectivity_type_e conn_type;
	char *host_address = NULL;
	char *presence_host_address;
	char *presence_resource_type;
	iotcon_connectivity_type_e presence_conn_type;
	int tc_index = (int)user_data;

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX) {
		g_timeout_count++;
		ret = iotcon_query_create(&query);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_create() Fail(%d)", ret);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_query_set_resource_type(query, LIGHT_RESOURCE_TYPE);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_set_resource_type() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY,
				query, _presence_found_resource, user_data);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_find_resource() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_query_destroy(query);

		return IOTCON_FUNC_STOP;
	} else if (IOTCON_ERROR_NONE != err) {
		_presence_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	if (g_found)
		return IOTCON_FUNC_STOP;
	g_found = true;

	ret = iotcon_remote_resource_get_host_address(resource, &host_address);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_get_host_address() Fail(%d)", ret);
		_presence_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	ICUTC_INFO("expected host_address[%s], found host_address[%s]", g_ipv4_address, host_address);

	if (strstr(host_address, g_ipv4_address) == NULL) { // targeted resource, BUT wrong device, so skip this resource and try again
		g_found = false;
		return IOTCON_FUNC_CONTINUE;
	}

	ret = iotcon_remote_resource_get_connectivity_type(resource, &conn_type);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_get_connectivity_type() Fail(%d)", ret);
		_presence_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	switch (tc_index) {
	case PRESENCE_ADD_PRESENCE_CB_P:
	case PRESENCE_REMOVE_PRESENCE_CB_P:
		ret = iotcon_add_presence_cb(host_address, conn_type,
				PRESENCE_LIGHT_RESOURCE_TYPE,	_presence_handler, (void *)tc_index, &g_presence);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_add_presence_cb() Fail(%d)", ret);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_remove_presence_cb(g_presence);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remove_presence_cb() Fail(%d)", ret);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_presence_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case PRESENCE_ADD_PRESENCE_CB_N:
		/* cb is NULL */
		ret = iotcon_add_presence_cb(host_address, conn_type,
				PRESENCE_LIGHT_RESOURCE_TYPE,	NULL, (void *)tc_index, &g_presence);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_add_presence_cb() Fail(%d)", ret);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		/* presence_handle is NULL */
		ret = iotcon_add_presence_cb(host_address, conn_type,
				PRESENCE_LIGHT_RESOURCE_TYPE,	_presence_handler, (void *)tc_index, NULL);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_add_presence_cb() Fail(%d)", ret);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_presence_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case PRESENCE_REMOVE_PRESENCE_CB_N:
		ret = iotcon_remove_presence_cb(NULL);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_remove_presence_cb() Fail(%d)", ret);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_presence_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case PRESENCE_GET_HOST_ADDR_P:
		ret = iotcon_add_presence_cb(host_address, conn_type,
				PRESENCE_LIGHT_RESOURCE_TYPE,	_presence_handler, (void *)tc_index, &g_presence);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_add_presence_cb() Fail(%d)", ret);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_presence_get_host_address(g_presence, &presence_host_address);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_presence_get_host_address() Fail(%d)", ret);
			iotcon_remove_presence_cb(g_presence);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_remove_presence_cb(g_presence);
		_presence_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case PRESENCE_GET_HOST_ADDR_N:
		ret = iotcon_add_presence_cb(host_address, conn_type,
				PRESENCE_LIGHT_RESOURCE_TYPE,	_presence_handler, (void *)tc_index, &g_presence);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_add_presence_cb() Fail(%d)", ret);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_presence_get_host_address(NULL, &presence_host_address);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_presence_get_host_address() Fail(%d)", ret);
			iotcon_remove_presence_cb(g_presence);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_presence_get_host_address(g_presence, NULL);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_presence_get_host_address() Fail(%d)", ret);
			iotcon_remove_presence_cb(g_presence);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_remove_presence_cb(g_presence);
		_presence_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case PRESENCE_GET_CONN_TYPE_P:
		ret = iotcon_add_presence_cb(host_address, conn_type,
				PRESENCE_LIGHT_RESOURCE_TYPE,	_presence_handler, (void *)tc_index, &g_presence);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_add_presence_cb() Fail(%d)", ret);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_presence_get_connectivity_type(g_presence, &presence_conn_type);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_presence_get_host_address() Fail(%d)", ret);
			iotcon_remove_presence_cb(g_presence);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_remove_presence_cb(g_presence);
		_presence_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case PRESENCE_GET_CONN_TYPE_N:
		ret = iotcon_add_presence_cb(host_address, conn_type,
				PRESENCE_LIGHT_RESOURCE_TYPE,	_presence_handler, (void *)tc_index, &g_presence);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_add_presence_cb() Fail(%d)", ret);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_presence_get_connectivity_type(NULL, &presence_conn_type);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_presence_get_host_address() Fail(%d)", ret);
			iotcon_remove_presence_cb(g_presence);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_presence_get_connectivity_type(g_presence, NULL);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_presence_get_host_address() Fail(%d)", ret);
			iotcon_remove_presence_cb(g_presence);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_remove_presence_cb(g_presence);
		_presence_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case PRESENCE_GET_RSRC_TYPE_P:
		ret = iotcon_add_presence_cb(host_address, conn_type,
				PRESENCE_LIGHT_RESOURCE_TYPE,	_presence_handler, (void *)tc_index, &g_presence);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_add_presence_cb() Fail(%d)", ret);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_presence_get_resource_type(g_presence, &presence_resource_type);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_presence_get_host_address() Fail(%d)", ret);
			iotcon_remove_presence_cb(g_presence);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_remove_presence_cb(g_presence);
		_presence_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case PRESENCE_GET_RSRC_TYPE_N:
		ret = iotcon_add_presence_cb(host_address, conn_type,
				PRESENCE_LIGHT_RESOURCE_TYPE,	_presence_handler, (void *)tc_index, &g_presence);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_add_presence_cb() Fail(%d)", ret);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_presence_get_resource_type(NULL, &presence_resource_type);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_presence_get_host_address() Fail(%d)", ret);
			iotcon_remove_presence_cb(g_presence);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_presence_get_resource_type(g_presence, NULL);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_presence_get_host_address() Fail(%d)", ret);
			iotcon_remove_presence_cb(g_presence);
			_presence_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_remove_presence_cb(g_presence);
		_presence_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	default:
		ICUTC_ERR("Invalid tc_index(%d)", tc_index);
		return IOTCON_FUNC_STOP;
	}
	return IOTCON_FUNC_STOP;
}

static int _presence_handle_async(int tc_index)
{
	FN_CALL;
	int ret;
	iotcon_query_h query;

	g_loop = g_main_loop_new(NULL, FALSE);

	ret = _presence_create_resource(tc_index);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_query_create(&query);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_create() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_query_set_resource_type(query, PRESENCE_LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_set_resource_type() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}

	ret = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY,
			query, _presence_found_resource, (void *)tc_index);

	iotcon_query_destroy(query);
	ICUTC_ASSERT_EQ(ret, 0);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	_presence_destroy_resource();

	if (true == g_result)
		return 0;
	return 1;
}
/* ##################################################### */

/**
 * @function      utc_iotcon_presence_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_presence_startup(void)
{
	int ret;
	char *path;

	g_found = false;
	g_timeout_count = 0;
	g_feature = false;

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
}

/**
 * @function      utc_iotcon_presence_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_presence_cleanup(void)
{
	icutc_free_client_ipv4_address();

	if (true == g_feature)
		iotcon_deinitialize();
}

/**
 * @testcase      utc_iotcon_add_presence_cb_n
 * @since_tizen   3.0
 * @description   Test fail adding presence callback with invalid parameter.
 */
int utc_iotcon_add_presence_cb_n(void)
{
	int ret;
	char *host_address = NULL;
	iotcon_connectivity_type_e conn_type = IOTCON_CONNECTIVITY_IP;

	if (false == g_feature) {
		ret = iotcon_add_presence_cb(host_address, conn_type,
				PRESENCE_LIGHT_RESOURCE_TYPE, _presence_handler, NULL, &g_presence);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _presence_handle_async(PRESENCE_ADD_PRESENCE_CB_N);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_add_presence_cb_p
 * @since_tizen   3.0
 * @description   Test adding presence callback.
 */
int utc_iotcon_add_presence_cb_p(void)
{
	int ret;
	char *host_address = NULL;
	iotcon_connectivity_type_e conn_type = IOTCON_CONNECTIVITY_IP;

	if (false == g_feature) {
		ret = iotcon_add_presence_cb(host_address, conn_type,
				PRESENCE_LIGHT_RESOURCE_TYPE, _presence_handler, NULL, &g_presence);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _presence_handle_async(PRESENCE_ADD_PRESENCE_CB_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_remove_presence_cb_n
 * @since_tizen   3.0
 * @description   Test fail removing presence callback with invalid parameter.
 */
int utc_iotcon_remove_presence_cb_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remove_presence_cb(g_presence);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _presence_handle_async(PRESENCE_REMOVE_PRESENCE_CB_N);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_remove_presence_cb_p
 * @since_tizen   3.0
 * @description   Test removing presence callback.
 */
int utc_iotcon_remove_presence_cb_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remove_presence_cb(g_presence);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _presence_handle_async(PRESENCE_REMOVE_PRESENCE_CB_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_get_host_address_n
 * @since_tizen   3.0
 * @description   Test fail getting host address from presence with invalid parameter.
 */
int utc_iotcon_presence_get_host_address_n(void)
{
	int ret;
	char *presence_host_address;

	if (false == g_feature) {
		ret = iotcon_presence_get_host_address(g_presence, &presence_host_address);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _presence_handle_async(PRESENCE_GET_HOST_ADDR_N);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_get_host_address_p
 * @since_tizen   3.0
 * @description   Test getting host address from presence.
 */
int utc_iotcon_presence_get_host_address_p(void)
{
	int ret;
	char *presence_host_address;

	if (false == g_feature) {
		ret = iotcon_presence_get_host_address(g_presence, &presence_host_address);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _presence_handle_async(PRESENCE_GET_HOST_ADDR_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_get_connectivity_type_n
 * @since_tizen   3.0
 * @description   Test fail getting connectivity type from presence with invalid parameter.
 */
int utc_iotcon_presence_get_connectivity_type_n(void)
{
	int ret;
	iotcon_connectivity_type_e presence_conn_type;

	if (false == g_feature) {
		ret = iotcon_presence_get_connectivity_type(g_presence, &presence_conn_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _presence_handle_async(PRESENCE_GET_CONN_TYPE_N);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_get_connectivity_type_p
 * @since_tizen   3.0
 * @description   Test getting connectivity type from presence.
 */
int utc_iotcon_presence_get_connectivity_type_p(void)
{
	int ret;
	iotcon_connectivity_type_e presence_conn_type;

	if (false == g_feature) {
		ret = iotcon_presence_get_connectivity_type(g_presence, &presence_conn_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _presence_handle_async(PRESENCE_GET_CONN_TYPE_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_get_resource_type_n
 * @since_tizen   3.0
 * @description   Test fail getting resource type from presence with invalid parameter.
 */
int utc_iotcon_presence_get_resource_type_n(void)
{
	int ret;
	char *presence_resource_type;

	if (false == g_feature) {
		ret = iotcon_presence_get_resource_type(g_presence, &presence_resource_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _presence_handle_async(PRESENCE_GET_RSRC_TYPE_N);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_get_resource_type_p
 * @since_tizen   3.0
 * @description   Test getting resource type from presence.
 */
int utc_iotcon_presence_get_resource_type_p(void)
{
	int ret;
	char *presence_resource_type;

	if (false == g_feature) {
		ret = iotcon_presence_get_resource_type(g_presence, &presence_resource_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _presence_handle_async(PRESENCE_GET_RSRC_TYPE_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_response_get_result_n
 * @since_tizen   3.0
 * @description   Test fail getting result from presence response with invalid parameter.
 */
int utc_iotcon_presence_response_get_result_n(void)
{
	int ret;
	iotcon_presence_result_e result;

	if (false == g_feature) {
		ret = iotcon_presence_response_get_result(NULL, &result);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_presence_response_get_result(NULL, &result);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_response_get_trigger_n
 * @since_tizen   3.0
 * @description   Test fail getting trigger from presence response with invalid parameter.
 */
int utc_iotcon_presence_response_get_trigger_n(void)
{
	int ret;
	iotcon_presence_trigger_e trigger;

	if (false == g_feature) {
		ret = iotcon_presence_response_get_trigger(NULL, &trigger);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_presence_response_get_trigger(NULL, &trigger);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_response_get_host_address_n
 * @since_tizen   3.0
 * @description   Test fail getting host address from presence response with invalid parameter.
 */
int utc_iotcon_presence_response_get_host_address_n(void)
{
	int ret;
	char *host_address;

	if (false == g_feature) {
		ret = iotcon_presence_response_get_host_address(NULL, &host_address);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_presence_response_get_host_address(NULL, &host_address);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_response_get_connectivity_type_n
 * @since_tizen   3.0
 * @description   Test fail getting connectivity type from presence response with invalid parameter.
 */
int utc_iotcon_presence_response_get_connectivity_type_n(void)
{
	int ret;
	iotcon_connectivity_type_e conn_type;

	if (false == g_feature) {
		ret = iotcon_presence_response_get_connectivity_type(NULL, &conn_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_presence_response_get_connectivity_type(NULL, &conn_type);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_response_get_resource_type_n
 * @since_tizen   3.0
 * @description   Test fail getting resource type from presence response with invalid parameter.
 */
int utc_iotcon_presence_response_get_resource_type_n(void)
{
	int ret;
	char *resource_type;

	if (false == g_feature) {
		ret = iotcon_presence_response_get_resource_type(NULL, &resource_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_presence_response_get_resource_type(NULL, &resource_type);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_start_presence_p
 * @since_tizen   3.0
 * @description   Test start presence.
 */
int utc_iotcon_presence_start_presence_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_start_presence(ICUTC_PRESENCE_INTERVAL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_start_presence(ICUTC_PRESENCE_INTERVAL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	iotcon_stop_presence();

	return 0;
}

/**
 * @testcase      utc_iotcon_presence_stop_presence_p
 * @since_tizen   3.0
 * @description   Test stop presence.
 */
int utc_iotcon_presence_stop_presence_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_stop_presence();
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_start_presence(ICUTC_PRESENCE_INTERVAL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_stop_presence();
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

