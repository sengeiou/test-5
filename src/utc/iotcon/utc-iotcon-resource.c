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
	RESOURCE_BIND_CHILD_RESOURCE_P,
	RESOURCE_BIND_CHILD_RESOURCE_N,
	RESOURCE_BIND_INTERFACE_P,
	RESOURCE_BIND_INTERFACE_N,
	RESOURCE_BIND_TYPE_P,
	RESOURCE_BIND_TYPE_N,
	RESOURCE_CREATE_P,
	RESOURCE_CREATE_N,
	RESOURCE_DESTROY_P,
	RESOURCE_DESTROY_N,
	RESOURCE_GET_INTERFACES_P,
	RESOURCE_GET_INTERFACES_N,
	RESOURCE_GET_NTH_CHILD_P,
	RESOURCE_GET_NTH_CHILD_N,
	RESOURCE_GET_NUMBER_OF_CHILDREN_P,
	RESOURCE_GET_NUMBER_OF_CHILDREN_N,
	RESOURCE_GET_PROPERTIES_P,
	RESOURCE_GET_PROPERTIES_N,
	RESOURCE_GET_TYPES_P,
	RESOURCE_GET_TYPES_N,
	RESOURCE_GET_URI_PATH_P,
	RESOURCE_GET_URI_PATH_N,
	RESOURCE_NOTIFY_P,
	RESOURCE_NOTIFY_N,
	RESOURCE_SET_REQUEST_HANDLER_P,
	RESOURCE_SET_REQUEST_HANDLER_N,
	RESOURCE_UNBIND_CHILD_RESOURCE_P,
	RESOURCE_UNBIND_CHILD_RESOURCE_N,
};

static bool g_feature;
static int g_timeout_count;
static bool g_found;
static bool g_result;
static GMainLoop *g_loop;
static iotcon_resource_h g_light_resource;
static iotcon_remote_resource_h g_remote_resource;

static gboolean _resource_main_loop_quit_idle(gpointer p)
{
	FN_CALL;
	g_main_loop_quit(g_loop);
	return G_SOURCE_REMOVE;
}

static void _resource_main_loop_quit(bool result)
{
	ICUTC_INFO("result = %d", result);
	g_result = result;
	g_idle_add(_resource_main_loop_quit_idle, NULL);
}

/**
 * @function      utc_iotcon_resource_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_resource_startup(void)
{
	int ret;
	char *path;

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
 * @function      utc_iotcon_resource_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_resource_cleanup(void)
{
	icutc_free_client_ipv4_address();

	if (true == g_feature)
		iotcon_deinitialize();
}

static void _resource_request_handler(iotcon_resource_h resource,
		iotcon_request_h request, void *user_data)
{
	FN_CALL;
	int ret;
	iotcon_representation_h repr;
	iotcon_response_h response;
	ret = icutc_create_representation(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_representation() Fail(%d)", ret);
		_resource_main_loop_quit(false);
		return;
	}

	ret = iotcon_response_create(request, &response);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_create() Fail(%d)", ret);
		_resource_main_loop_quit(false);
		return;
	}

	ret = iotcon_response_set_representation(response, repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_set_representation() Fail(%d)", ret);
		iotcon_response_destroy(response);
		_resource_main_loop_quit(false);
		return;
	}

	ret = iotcon_response_set_result(response, IOTCON_RESPONSE_OK);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_set_result() Fail(%d)", ret);
		iotcon_response_destroy(response);
		_resource_main_loop_quit(false);
		return;
	}

	iotcon_representation_destroy(repr);

	/*
	* Add sleep() to avoid crash.
	* - crashed in iotivity stack when sending request/response with the same process
	* This patch will be removed after spliting request process with response process
	*/
	sleep(1);

	ret = iotcon_response_send(response);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_send() Fail(%d)", ret);
		iotcon_response_destroy(response);
		_resource_main_loop_quit(false);
		return;
	}

	iotcon_response_destroy(response);
}

static void _resource_request_handler2(iotcon_resource_h resource,
		iotcon_request_h request, void *user_data)
{
	FN_CALL;
	int ret;
	iotcon_representation_h repr;
	iotcon_response_h response;
	ret = icutc_create_representation(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_representation() Fail(%d)", ret);
		_resource_main_loop_quit(false);
		return;
	}

	ret = iotcon_response_create(request, &response);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_create() Fail(%d)", ret);
		_resource_main_loop_quit(false);
		return;
	}

	ret = iotcon_response_set_representation(response, repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_set_representation() Fail(%d)", ret);
		iotcon_response_destroy(response);
		_resource_main_loop_quit(false);
		return;
	}

	ret = iotcon_response_set_result(response, IOTCON_RESPONSE_OK);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_set_result() Fail(%d)", ret);
		iotcon_response_destroy(response);
		_resource_main_loop_quit(false);
		return;
	}

	iotcon_representation_destroy(repr);

	/*
	* Add sleep() to avoid crash.
	* - crashed in iotivity stack when sending request/response with the same process
	* This patch will be removed after spliting request process with response process
	*/
	sleep(1);

	ret = iotcon_response_send(response);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_send() Fail(%d)", ret);
		iotcon_response_destroy(response);
		_resource_main_loop_quit(false);
		return;
	}

	iotcon_response_destroy(response);
}



/**
 * @testcase      utc_iotcon_resource_create_n
 * @since_tizen   3.0
 * @description   Test fail creating a resource with invalid parameter.
 */
int utc_iotcon_resource_create_n(void)
{
	int ret;
	iotcon_resource_types_h types = NULL;
	iotcon_resource_interfaces_h ifaces = NULL;
	iotcon_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_create(NULL,
				types,
				ifaces,
				(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
				_resource_request_handler,
				NULL,
				&resource);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_types_create(&types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_add(types, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	ret = iotcon_resource_interfaces_create(&ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(ifaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(ifaces, IOTCON_INTERFACE_BATCH);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	/* uri_path is NULL */
	ret = iotcon_resource_create(NULL,
			types,
			ifaces,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			_resource_request_handler,
			NULL,
			&resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	/* resource_types is NULL */
	ret = iotcon_resource_create(LIGHT_RESOURCE_URI,
			NULL,
			ifaces,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			_resource_request_handler,
			NULL,
			&resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	/* resource_interfaces is NULL */
	ret = iotcon_resource_create(LIGHT_RESOURCE_URI,
			types,
			NULL,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			_resource_request_handler,
			NULL,
			&resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	/* cb is NULL */
	ret = iotcon_resource_create(LIGHT_RESOURCE_URI,
			types,
			ifaces,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			NULL,
			NULL,
			&resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	/* out parameter is NULL */
	ret = iotcon_resource_create(LIGHT_RESOURCE_URI,
			types,
			ifaces,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			_resource_request_handler,
			NULL,
			NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	iotcon_resource_types_destroy(types);
	return 0;
}

static void _destroy_resource()
{
	if (g_remote_resource) {
		iotcon_remote_resource_destroy(g_remote_resource);
		g_remote_resource = NULL;
	}

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

	_destroy_resource();

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
			_resource_request_handler,
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

static gboolean _resource_notify_idle(gpointer p)
{
	FN_CALL;
	int ret;
	iotcon_representation_h repr;
	icutc_create_representation(&repr);
	ret = iotcon_resource_notify(g_light_resource, repr, NULL, IOTCON_QOS_HIGH);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_notify() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		_resource_main_loop_quit(false);
		return G_SOURCE_REMOVE;
	}
	iotcon_representation_destroy(repr);
	return G_SOURCE_REMOVE;
}

static void _resource_observe_cb(iotcon_remote_resource_h resource,
		iotcon_error_e err, int sequence_number, iotcon_response_h response, void *user_data)
{
	FN_CALL;
	static int notify_count = 0;
	int tc_index = (int)user_data;

	switch (tc_index) {
	case RESOURCE_CREATE_P:
	case RESOURCE_SET_REQUEST_HANDLER_P:
		_resource_main_loop_quit(true);
		return;
	case RESOURCE_NOTIFY_P:
		if (0 == notify_count++) {
			ICUTC_INFO("RESOURCE_NOTIFY_P");
			g_idle_add(_resource_notify_idle, NULL);
			return;
		}
		_resource_main_loop_quit(true);
		return;
	default:
		ICUTC_ERR("Invalid tc_index(%d)", tc_index);
		_resource_main_loop_quit(false);
		return;
	}
}

static bool _found_resource(iotcon_remote_resource_h resource,
		iotcon_error_e err, void *user_data)
{
	FN_CALL;
	int ret;
	iotcon_query_h query;
	int tc_index = (int)user_data;
	char *host_address;

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX) {
		g_timeout_count++;
		ret = iotcon_query_create(&query);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_create() Fail(%d)", ret);
			_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_query_set_resource_type(query, LIGHT_RESOURCE_TYPE);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_set_resource_type() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY,
				query, _found_resource, user_data);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_find_resource() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_query_destroy(query);

		return IOTCON_FUNC_STOP;
	} else if (IOTCON_ERROR_NONE != err) {
		_resource_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	if (g_found)
		return IOTCON_FUNC_STOP;
	g_found = true;

	ret = iotcon_remote_resource_get_host_address(resource, &host_address);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_get_host_address() Fail(%d)", ret);
		_resource_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	ICUTC_INFO("expected host_address[%s], found host_address[%s]", g_ipv4_address, host_address);

	if (strstr(host_address, g_ipv4_address) == NULL) { // targeted resource, BUT wrong device, so skip this resource and try again
		g_found = false;
		return IOTCON_FUNC_CONTINUE;
	}

	switch (tc_index) {
	case RESOURCE_SET_REQUEST_HANDLER_P:
		ret = iotcon_resource_set_request_handler(g_light_resource,
				_resource_request_handler2, (void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_resource_set_request_handler() Fail(%d)", ret);
			_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_remote_resource_clone(resource, &g_remote_resource);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_clone() Fail(%d)", ret);
			_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_remote_resource_observe_register(g_remote_resource,
				IOTCON_OBSERVE_ACCEPT_OUT_OF_ORDER, NULL, _resource_observe_cb, (void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_observe_register() Fail(%d)", ret);
			_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		break;
	case RESOURCE_CREATE_P:
	case RESOURCE_NOTIFY_P:
		ret = iotcon_remote_resource_clone(resource, &g_remote_resource);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_clone() Fail(%d)", ret);
			_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_remote_resource_observe_register(g_remote_resource,
				IOTCON_OBSERVE_ACCEPT_OUT_OF_ORDER, NULL, _resource_observe_cb, (void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_observe_register() Fail(%d)", ret);
			_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		break;
	default:
		ICUTC_ERR("Invalid tc_index(%d)", tc_index);
		_resource_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}
	return IOTCON_FUNC_STOP;
}

static int _resource_handle_async(int tc_index)
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
			query, _found_resource, (void *)tc_index);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_find_resource() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}
	iotcon_query_destroy(query);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);

	_destroy_resource();

	if (true == g_result)
		return 0;
	else
		return 1;
}


/**
 * @testcase      utc_iotcon_resource_create_p
 * @since_tizen   3.0
 * @description   Test creating a resource.
 */
int utc_iotcon_resource_create_p(void)
{
	int ret;
	iotcon_resource_h resource = NULL;
	iotcon_resource_types_h types = NULL;
	iotcon_resource_interfaces_h ifaces = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_create(NULL,
				types,
				ifaces,
				(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
				_resource_request_handler,
				NULL,
				&resource);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _resource_handle_async(RESOURCE_CREATE_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_destroy_n
 * @since_tizen   3.0
 * @description   Test fail destroying a resource with invalid parameter.
 */
int utc_iotcon_resource_destroy_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_resource_destroy(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_destroy(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_destroy_p
 * @since_tizen   3.0
 * @description   Test destroying a resource.
 */
int utc_iotcon_resource_destroy_p(void)
{
	int ret;
	iotcon_resource_h resource;

	if (false == g_feature) {
		ret = iotcon_resource_destroy(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_destroy(resource);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_bind_child_resource_n
 * @since_tizen   3.0
 * @description   Test fail binding child resource to resource with invalid parameter.
 */
int utc_iotcon_resource_bind_child_resource_n(void)
{
	int ret;
	iotcon_resource_h resource = NULL;
	iotcon_resource_h child_resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_bind_child_resource(resource, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = icutc_create_resource(LED_RESOURCE_TYPE, LED_RESOURCE_URI, &child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	/* child is NULL */
	ret = iotcon_resource_bind_child_resource(resource, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_bind_child_resource() Fail(%d)", ret);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	/* parent is NULL */
	ret = iotcon_resource_bind_child_resource(NULL, child_resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_bind_child_resource() Fail(%d)", ret);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	/* child and parent is same */
	ret = iotcon_resource_bind_child_resource(resource, resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_bind_child_resource() Fail(%d)", ret);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(child_resource);
	iotcon_resource_destroy(resource);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_bind_child_resource_p
 * @since_tizen   3.0
 * @description   Test binding child resource to resource.
 */
int utc_iotcon_resource_bind_child_resource_p(void)
{
	int ret;
	iotcon_resource_h resource = NULL;
	iotcon_resource_h child_resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_bind_child_resource(resource, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = icutc_create_resource(LED_RESOURCE_TYPE, LED_RESOURCE_URI, &child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_bind_child_resource(resource, child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_bind_child_resource() Fail(%d)", ret);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_unbind_child_resource(resource, child_resource);
	iotcon_resource_destroy(child_resource);
	iotcon_resource_destroy(resource);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_bind_interface_n
 * @since_tizen   3.0
 * @description   Test fail binding interface to resource with invalid parameter.
 */
int utc_iotcon_resource_bind_interface_n(void)
{
	int ret;
	iotcon_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_bind_interface(NULL, IOTCON_INTERFACE_LINK);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	/* resource is NULL */
	ret = iotcon_resource_bind_interface(NULL, IOTCON_INTERFACE_LINK);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_bind_interface() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	/* duplicated */
	ret = iotcon_resource_bind_interface(resource, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_ALREADY != ret) {
		ICUTC_ERR("iotcon_resource_bind_interface() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	/* interface is NULL */
	ret = iotcon_resource_bind_interface(resource, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_bind_interface() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(resource);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_bind_interface_p
 * @since_tizen   3.0
 * @description   Test binding interface to resource.
 */
int utc_iotcon_resource_bind_interface_p(void)
{
	int ret;
	iotcon_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_bind_interface(NULL, IOTCON_INTERFACE_LINK);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_resource_bind_interface(resource, IOTCON_INTERFACE_LINK);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_bind_interface() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(resource);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_bind_type_n
 * @since_tizen   3.0
 * @description   Test fail binding type to resource with invalid parameter.
 */
int utc_iotcon_resource_bind_type_n(void)
{
	int ret;
	iotcon_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_bind_type(NULL, LIGHT_RESOURCE_TYPE2);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	/* resource is NULL */
	ret = iotcon_resource_bind_type(NULL, LIGHT_RESOURCE_TYPE2);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_bind_type() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	/* duplicated */
	ret = iotcon_resource_bind_type(resource, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_ALREADY != ret) {
		ICUTC_ERR("iotcon_resource_bind_type() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(resource);
	return 0;

}
/**
 * @testcase      utc_iotcon_resource_bind_type_p
 * @since_tizen   3.0
 * @description   Test binding type to resource.
 */
int utc_iotcon_resource_bind_type_p(void)
{
	int ret;
	iotcon_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_bind_type(NULL, LIGHT_RESOURCE_TYPE2);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_resource_bind_type(resource, LIGHT_RESOURCE_TYPE2);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_bind_type() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(resource);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_unbind_child_resource_n
 * @since_tizen   3.0
 * @description   Test fail unbinding type to resource with invalid parameter.
 */
int utc_iotcon_resource_unbind_child_resource_n(void)
{
	int ret;
	iotcon_resource_h resource = NULL;
	iotcon_resource_h child_resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_unbind_child_resource(NULL, child_resource);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = icutc_create_resource(LED_RESOURCE_TYPE, LED_RESOURCE_URI, &child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	/* child is NULL */
	ret = iotcon_resource_bind_child_resource(resource, child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_bind_child_resource() Fail(%d)", ret);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	/* parent is NULL */
	ret = iotcon_resource_unbind_child_resource(NULL, child_resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_bind_child_resource() Fail(%d)", ret);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	/* child is NULL */
	ret = iotcon_resource_unbind_child_resource(resource, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_bind_child_resource() Fail(%d)", ret);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_unbind_child_resource(resource, child_resource);
	iotcon_resource_destroy(child_resource);
	iotcon_resource_destroy(resource);

	return 0;

}

/**
 * @testcase      utc_iotcon_resource_unbind_child_resource_p
 * @since_tizen   3.0
 * @description   Test unbinding type to resource.
 */
int utc_iotcon_resource_unbind_child_resource_p(void)
{
	int ret;
	iotcon_resource_h resource = NULL;
	iotcon_resource_h child_resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_unbind_child_resource(NULL, child_resource);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = icutc_create_resource(LED_RESOURCE_TYPE, LED_RESOURCE_URI, &child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_bind_child_resource(resource, child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource() Fail(%d)", ret);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}


	ret = iotcon_resource_unbind_child_resource(resource, child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource() Fail(%d)", ret);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(child_resource);
	iotcon_resource_destroy(resource);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_notify_n
 * @since_tizen   3.0
 * @description   Test fail notifying resource with invalid parameter.
 */
int utc_iotcon_resource_notify_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_resource_notify(NULL, NULL, NULL, IOTCON_QOS_LOW);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_notify(NULL, NULL, NULL, IOTCON_QOS_LOW);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_notify_p
 * @since_tizen   3.0
 * @description   Test notifying resource.
 */
int utc_iotcon_resource_notify_p(void)
{
	int ret;
	iotcon_resource_h resource = NULL;
	iotcon_representation_h repr = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_notify(resource, repr, NULL, IOTCON_QOS_HIGH);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _resource_handle_async(RESOURCE_NOTIFY_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_set_request_handler_n
 * @since_tizen   3.0
 * @description   Test fail setting request handler to resource with invalid parameter.
 */
int utc_iotcon_resource_set_request_handler_n(void)
{
	int ret;
	iotcon_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_set_request_handler(NULL, _resource_request_handler, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_resource_set_request_handler(NULL, _resource_request_handler, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_set_request_handler() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_set_request_handler(resource, NULL, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_set_request_handler() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(resource);
	return 0;
}


/**
 * @testcase      utc_iotcon_resource_set_request_handler_p
 * @since_tizen   3.0
 * @description   Test setting request handler to resource.
 */
int utc_iotcon_resource_set_request_handler_p(void)
{
	int ret;
	iotcon_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_set_request_handler(resource, _resource_request_handler, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _resource_handle_async(RESOURCE_SET_REQUEST_HANDLER_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

	/**
	 * @testcase      utc_iotcon_resource_get_child_count_n
	 * @since_tizen   3.0
	 * @description   Test fail getting number of children from resource with invalid parameter.
	 */
int utc_iotcon_resource_get_child_count_n(void)
{
	int ret;
	unsigned int count;
	iotcon_resource_h resource = NULL;
	iotcon_resource_h child_resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_get_child_count(NULL, &count);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = icutc_create_resource(LED_RESOURCE_TYPE, LED_RESOURCE_URI, &child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_bind_child_resource(resource, child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_bind_child_resource() Fail(%d)", ret);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_get_child_count(NULL, &count);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_get_child_count() Fail(%d)", ret);
		iotcon_resource_unbind_child_resource(resource, child_resource);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}
	ret = iotcon_resource_get_child_count(resource, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_get_child_count() Fail(%d)", ret);
		iotcon_resource_unbind_child_resource(resource, child_resource);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_unbind_child_resource(resource, child_resource);
	iotcon_resource_destroy(child_resource);
	iotcon_resource_destroy(resource);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_get_child_count_p
 * @since_tizen   3.0
 * @description   Test getting number of children from resource.
 */
int utc_iotcon_resource_get_child_count_p(void)
{
	int ret;
	unsigned int count;
	iotcon_resource_h resource = NULL;
	iotcon_resource_h child_resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_get_child_count(NULL, &count);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = icutc_create_resource(LED_RESOURCE_TYPE, LED_RESOURCE_URI, &child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_bind_child_resource(resource, child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_bind_child_resource() Fail(%d)", ret);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_get_child_count(resource, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_get_child_count() Fail(%d)", ret);
		iotcon_resource_unbind_child_resource(resource, child_resource);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_unbind_child_resource(resource, child_resource);
	iotcon_resource_destroy(child_resource);
	iotcon_resource_destroy(resource);
	ICUTC_ASSERT_EQ(count, 1);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_get_nth_child_n
 * @since_tizen   3.0
 * @description   Test fail getting nth child from resource with invalid parameter.
 */
int utc_iotcon_resource_get_nth_child_n(void)
{
	int ret;
	iotcon_resource_h resource = NULL;
	iotcon_resource_h child_resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_get_nth_child(NULL, 0, &child_resource);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = icutc_create_resource(LED_RESOURCE_TYPE, LED_RESOURCE_URI, &child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_bind_child_resource(resource, child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_get_nth_child() Fail(%d)", ret);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_get_nth_child(NULL, 0, &child_resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_get_nth_child() Fail(%d)", ret);
		iotcon_resource_unbind_child_resource(resource, child_resource);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}
	ret = iotcon_resource_get_nth_child(resource, -1, &child_resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_get_nth_child() Fail(%d)", ret);
		iotcon_resource_unbind_child_resource(resource, child_resource);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}
	ret = iotcon_resource_get_nth_child(resource, 0, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_get_nth_child() Fail(%d)", ret);
		iotcon_resource_unbind_child_resource(resource, child_resource);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_unbind_child_resource(resource, child_resource);
	iotcon_resource_destroy(child_resource);
	iotcon_resource_destroy(resource);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_get_nth_child_p
 * @since_tizen   3.0
 * @description   Test getting nth child from resource.
 */
int utc_iotcon_resource_get_nth_child_p(void)
{
	int ret;
	iotcon_resource_h resource = NULL;
	iotcon_resource_h child_resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_get_nth_child(NULL, 0, &child_resource);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = icutc_create_resource(LED_RESOURCE_TYPE, LED_RESOURCE_URI, &child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_bind_child_resource(resource, child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_get_nth_child() Fail(%d)", ret);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_get_nth_child(resource, 0, &child_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_get_nth_child() Fail(%d)", ret);
		iotcon_resource_unbind_child_resource(resource, child_resource);
		iotcon_resource_destroy(child_resource);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_unbind_child_resource(resource, child_resource);
	iotcon_resource_destroy(child_resource);
	iotcon_resource_destroy(resource);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_get_uri_path_n
 * @since_tizen   3.0
 * @description   Test fail getting uri path from resource with invalid parameter.
 */
int utc_iotcon_resource_get_uri_path_n(void)
{
	int ret;
	iotcon_resource_h resource = NULL;
	char *uri_path;

	if (false == g_feature) {
		ret = iotcon_resource_get_uri_path(NULL, &uri_path);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_resource_get_uri_path(NULL, &uri_path);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_get_uri_path() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_get_uri_path(resource, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_get_uri_path() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}
	iotcon_resource_destroy(resource);
	return 0;

}

/**
 * @testcase      utc_iotcon_resource_get_uri_path_p
 * @since_tizen   3.0
 * @description   Test getting uri path from resource.
 */
int utc_iotcon_resource_get_uri_path_p(void)
{
	int ret;
	iotcon_resource_h resource = NULL;
	char *uri_path;

	if (false == g_feature) {
		ret = iotcon_resource_get_uri_path(NULL, &uri_path);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_resource_get_uri_path(resource, &uri_path);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_get_uri_path() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(resource);
	return 0;

}

/**
 * @testcase      utc_iotcon_resource_get_types_n
 * @since_tizen   3.0
 * @description   Test fail getting types from resource with invalid parameter.
 */
int utc_iotcon_resource_get_types_n(void)
{
	int ret;
	iotcon_resource_h resource = NULL;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_get_types(NULL, &types);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_resource_get_types(NULL, &types);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_get_types() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_get_types(resource, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_get_types() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(resource);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_get_types_p
 * @since_tizen   3.0
 * @description   Test getting types from resource.
 */
int utc_iotcon_resource_get_types_p(void)
{
	int ret;
	iotcon_resource_h resource = NULL;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_get_types(NULL, &types);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_resource_get_types(resource, &types);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_get_types() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(resource);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_get_interfaces_n
 * @since_tizen   3.0
 * @description   Test fail getting interfaces from resource with invalid parameter.
 */
int utc_iotcon_resource_get_interfaces_n(void)
{
	int ret;
	iotcon_resource_interfaces_h ifaces;
	iotcon_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_get_interfaces(NULL, &ifaces);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_resource_get_interfaces(NULL, &ifaces);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_get_interfaces() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_get_interfaces(resource, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_get_interfaces() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(resource);
	return 0;

}

/**
 * @testcase      utc_iotcon_resource_get_interfaces_p
 * @since_tizen   3.0
 * @description   Test getting interfaces from resource.
 */
int utc_iotcon_resource_get_interfaces_p(void)
{
	int ret;
	iotcon_resource_interfaces_h ifaces;
	iotcon_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_get_interfaces(NULL, &ifaces);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_resource_get_interfaces(resource, &ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_get_interfaces() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(resource);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_get_policies_n
 * @since_tizen   3.0
 * @description   Test fail getting policies from resource with invalid parameter.
 */
int utc_iotcon_resource_get_policies_n(void)
{
	int ret;
	uint8_t policies;
	iotcon_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_get_policies(NULL, &policies);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_resource_get_policies(NULL, &policies);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_get_policies() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_resource_get_policies(resource, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_get_policies() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(resource);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_get_policies_p
 * @since_tizen   3.0
 * @description   Test getting policies from resource.
 */
int utc_iotcon_resource_get_policies_p(void)
{
	int ret;
	uint8_t policies;
	iotcon_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_get_policies(NULL, &policies);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource(LIGHT_RESOURCE_TYPE, LIGHT_RESOURCE_URI, &resource);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_resource_get_policies(resource, &policies);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_get_policies() Fail(%d)", ret);
		iotcon_resource_destroy(resource);
		return 1;
	}

	iotcon_resource_destroy(resource);
	return 0;
}

