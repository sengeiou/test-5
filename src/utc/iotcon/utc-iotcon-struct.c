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
	/* iotcon_response_h */
	RESPONSE_CREATE_P,
	RESPONSE_CREATE_N,
	RESPONSE_DESTROY_N,
	RESPONSE_DESTROY_P,
	RESPONSE_GET_OPTIONS_P,
	RESPONSE_GET_OPTIONS_N,
	RESPONSE_GET_REPRESENTATION_P,
	RESPONSE_GET_REPRESENTATION_N,
	RESPONSE_GET_RESULT_P,
	RESPONSE_GET_RESULT_N,
	RESPONSE_SET_OPTIONS_P,
	RESPONSE_SET_OPTIONS_N,
	RESPONSE_SET_REPRESENTATION_P,
	RESPONSE_SET_REPRESENTATION_N,
	RESPONSE_SET_RESULT_P,
	RESPONSE_SET_RESULT_N,
	RESPONSE_SEND_P,
	RESPONSE_SEND_N,
	/* iotcon_request_h */
	REQUEST_GET_CONNECTIVITY_TYPE_P,
	REQUEST_GET_CONNECTIVITY_TYPE_N,
	REQUEST_GET_HOST_ADDRESS_P,
	REQUEST_GET_HOST_ADDRESS_N,
	REQUEST_GET_OBSERVE_ID_P,
	REQUEST_GET_OBSERVE_ID_N,
	REQUEST_GET_OBSERVE_TYPE_P,
	REQUEST_GET_OBSERVE_TYPE_N,
	REQUEST_GET_OPTIONS_P,
	REQUEST_GET_OPTIONS_N,
	REQUEST_GET_QUERY_P,
	REQUEST_GET_QUERY_N,
	REQUEST_GET_REPRESENTATION_P,
	REQUEST_GET_REPRESENTATION_N,
	REQUEST_GET_REQUEST_TYPE_P,
	REQUEST_GET_REQUEST_TYPE_N,
	/* iotcon_observers_h */
	/* iotcon_resource_h */
	/* iotcon_resource_types_h */
	/* iotcon_query_h */
};

static bool g_found;
static int g_timeout_count;
static bool g_result;
static bool g_feature;
static GMainLoop *g_loop;

/* ### server side ### */
static iotcon_resource_h g_light_resource;
static iotcon_remote_resource_h g_remote_resource;

static gboolean _struct_main_loop_quit_idle(gpointer p)
{
	FN_CALL;
	if (g_loop != NULL)
		g_main_loop_quit(g_loop);
	return G_SOURCE_REMOVE;
}

static void _struct_main_loop_quit(bool result)
{
	ICUTC_INFO("result = %d", result);
	g_result = result;
	g_idle_add(_struct_main_loop_quit_idle, NULL);
}

static int _struct_response_create_n(iotcon_request_h request)
{
	int ret;
	iotcon_response_h response;

	ret = iotcon_response_create(request, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_response_create(NULL, &response);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _struct_response_create_p(iotcon_request_h request)
{
	int ret;
	iotcon_response_h response;

	ret = iotcon_response_create(request, &response);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	iotcon_response_destroy(response);

	return 0;
}

static int _struct_response_destroy_n(iotcon_request_h request)
{
	int ret;

	ret = iotcon_response_destroy(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _struct_response_destroy_p(iotcon_request_h request)
{
	int ret;
	iotcon_response_h response;

	ret = iotcon_response_create(request, &response);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_response_destroy(response);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _struct_response_set_result_n(iotcon_request_h request)
{
	int ret;
	iotcon_response_h response;

	ret = iotcon_response_create(request, &response);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_response_set_result(response, -1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_response_set_result() Fail(%d)", ret);
		iotcon_response_destroy(response);
		return 0;
	}

	ret = iotcon_response_set_result(NULL, IOTCON_RESPONSE_OK);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_response_set_result() Fail(%d)", ret);
		iotcon_response_destroy(response);
		return 0;
	}

	iotcon_response_destroy(response);

	return 0;
}

static int _struct_response_set_result_p(iotcon_request_h request)
{
	int i;
	int ret;
	iotcon_response_h response;

	ret = iotcon_response_create(request, &response);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	for (i = IOTCON_RESPONSE_OK; i <= IOTCON_RESPONSE_FORBIDDEN; i++) {
		ret = iotcon_response_set_result(response, i);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_response_set_result() Fail(%d)", ret);
			iotcon_response_destroy(response);
			return 0;
		}
	}
	iotcon_response_destroy(response);

	return 0;
}

static int _struct_response_set_representation_n(iotcon_request_h request)
{
	int ret;
	iotcon_representation_h repr;

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		return 0;
	}

	ret = iotcon_response_set_representation(NULL, repr);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_response_set_representation() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 0;
	}

	iotcon_representation_destroy(repr);
	return 0;
}

static int _struct_response_set_representation_p(iotcon_request_h request)
{
	int ret;
	iotcon_response_h response;
	iotcon_representation_h repr;

	ret = iotcon_response_create(request, &response);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_create() Fail(%d)", ret);
		return 0;
	}

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		iotcon_response_destroy(response);
		return 0;
	}

	ret = iotcon_response_set_representation(response, repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_set_representation() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		iotcon_response_destroy(response);
		return 0;
	}
	iotcon_representation_destroy(repr);
	iotcon_response_destroy(response);
	return 0;
}

static int _struct_response_set_options_n(iotcon_request_h request)
{
	int ret;
	iotcon_options_h options;

	ret = iotcon_options_create(&options);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_create() Fail(%d)", ret);
		return 0;
	}

	ret = iotcon_response_set_options(NULL, options);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_response_set_options() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 0;
	}

	iotcon_options_destroy(options);
	return 0;
}

static int _struct_response_set_options_p(iotcon_request_h request)
{
	int ret;
	iotcon_response_h response;
	iotcon_options_h options;

	ret = iotcon_response_create(request, &response);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_create() Fail(%d)", ret);
		return 0;
	}

	ret = iotcon_options_create(&options);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_create() Fail(%d)", ret);
		iotcon_response_destroy(response);
		return 0;
	}

	ret = iotcon_response_set_options(response, options);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_set_options() Fail(%d)", ret);
		iotcon_options_destroy(options);
		iotcon_response_destroy(response);
		return 0;
	}
	iotcon_options_destroy(options);
	iotcon_response_destroy(response);
	return 0;
}

static int _struct_request_get_representation_n(iotcon_request_h request)
{
	int ret;
	iotcon_representation_h repr;

	ret = iotcon_request_get_representation(NULL, &repr);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_request_get_representation(request, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _struct_request_get_representation_p(iotcon_request_h request)
{
	int ret;
	iotcon_representation_h repr;

	ret = iotcon_request_get_representation(request, &repr);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _struct_request_get_type_n(iotcon_request_h request)
{
	int ret;
	iotcon_request_type_e request_type;

	ret = iotcon_request_get_request_type(NULL, &request_type);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_request_get_request_type(request, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _struct_request_get_type_p(iotcon_request_h request)
{
	int ret;
	iotcon_request_type_e request_type;

	ret = iotcon_request_get_request_type(request, &request_type);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _struct_request_get_connectivity_type_n(iotcon_request_h request)
{
	int ret;
	iotcon_connectivity_type_e conn_type;

	ret = iotcon_request_get_connectivity_type(NULL, &conn_type);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_request_get_connectivity_type(request, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _struct_request_get_connectivity_type_p(iotcon_request_h request)
{
	int ret;
	iotcon_connectivity_type_e conn_type;

	ret = iotcon_request_get_connectivity_type(request, &conn_type);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _struct_request_get_options_n(iotcon_request_h request)
{
	int ret;
	iotcon_options_h options;

	ret = iotcon_request_get_options(NULL, &options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_request_get_options(request, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _struct_request_get_options_p(iotcon_request_h request)
{
	int ret;
	iotcon_options_h options = NULL;

	ret = iotcon_request_get_options(request, &options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);
	ICUTC_ASSERT_NEQ(options, NULL);
	ICUTC_INFO("options : %p", options);

	return 0;
}

static int _struct_request_get_host_address_n(iotcon_request_h request)
{
	int ret;
	char *host_address;

	ret = iotcon_request_get_host_address(NULL, &host_address);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_request_get_host_address(request, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _struct_request_get_host_address_p(iotcon_request_h request)
{
	int ret;
	char *host_address;

	ret = iotcon_request_get_host_address(request, &host_address);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _struct_request_get_query_n(iotcon_request_h request)
{
	int ret;
	iotcon_query_h query;

	ret = iotcon_request_get_query(NULL, &query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_request_get_query(request, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _struct_request_get_query_p(iotcon_request_h request)
{
	int ret;
	iotcon_query_h query = NULL;

	ret = iotcon_request_get_query(request, &query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);
	ICUTC_ASSERT_NEQ(query, NULL);
	ICUTC_INFO("query : %p", query);

	return 0;
}

static int _struct_request_get_observe_id_n(iotcon_request_h request)
{
	int ret;
	int observe_id;

	ret = iotcon_request_get_observe_id(NULL, &observe_id);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_request_get_observe_id(request, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _struct_request_get_observe_id_p(iotcon_request_h request)
{
	int ret;
	int observe_id;

	ret = iotcon_request_get_observe_id(request, &observe_id);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _struct_request_get_observe_type_n(iotcon_request_h request)
{
	int ret;
	iotcon_observe_type_e observe_type;

	ret = iotcon_request_get_observe_type(NULL, &observe_type);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_request_get_observe_type(request, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _struct_request_get_observe_type_p(iotcon_request_h request)
{
	int ret;
	iotcon_observe_type_e observe_type;

	ret = iotcon_request_get_observe_type(request, &observe_type);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}


static void _struct_request_handler(iotcon_resource_h resource, iotcon_request_h request,
		void *user_data)
{
	FN_CALL;
	int ret;
	int tc_index = (int)user_data;

	switch (tc_index) {
	case RESPONSE_CREATE_N:
		ret = _struct_response_create_n(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_create_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case RESPONSE_CREATE_P:
		ret = _struct_response_create_p(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_create_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case RESPONSE_DESTROY_N:
		ret = _struct_response_destroy_n(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_destroy_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case RESPONSE_DESTROY_P:
		ret = _struct_response_destroy_p(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_destroy_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case RESPONSE_SET_RESULT_N:
		ret = _struct_response_set_result_n(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_set_result_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case RESPONSE_SET_RESULT_P:
		ret = _struct_response_set_result_p(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_set_result_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case RESPONSE_SET_REPRESENTATION_N:
		ret = _struct_response_set_representation_n(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_set_representation_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case RESPONSE_SET_REPRESENTATION_P:
		ret = _struct_response_set_representation_p(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_set_representation_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case RESPONSE_SET_OPTIONS_N:
		ret = _struct_response_set_options_n(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_set_options_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case RESPONSE_SET_OPTIONS_P:
		ret = _struct_response_set_options_p(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_set_options_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_REPRESENTATION_N:
		ret = _struct_request_get_representation_n(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_representation_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_REPRESENTATION_P:
		ret = _struct_request_get_representation_p(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_representation_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_REQUEST_TYPE_N:
		ret = _struct_request_get_type_n(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_type_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_REQUEST_TYPE_P:
		ret = _struct_request_get_type_p(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_type_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_CONNECTIVITY_TYPE_N:
		ret = _struct_request_get_connectivity_type_n(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_connectivity_type_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_CONNECTIVITY_TYPE_P:
		ret = _struct_request_get_connectivity_type_p(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_connectivity_type_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_OPTIONS_N:
		ret = _struct_request_get_options_n(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_options_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_OPTIONS_P:
		ret = _struct_request_get_options_p(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_options_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_HOST_ADDRESS_N:
		ret = _struct_request_get_host_address_n(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_host_address_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_HOST_ADDRESS_P:
		ret = _struct_request_get_host_address_p(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_host_address_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_QUERY_N:
		ret = _struct_request_get_query_n(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_query_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_QUERY_P:
		ret = _struct_request_get_query_p(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_query_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_OBSERVE_ID_N:
		ret = _struct_request_get_observe_id_n(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_observe_id_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_OBSERVE_ID_P:
		ret = _struct_request_get_observe_id_p(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_observe_id_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_OBSERVE_TYPE_N:
		ret = _struct_request_get_observe_type_n(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_observe_type_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case REQUEST_GET_OBSERVE_TYPE_P:
		ret = _struct_request_get_observe_type_p(request);
		if (0 != ret) {
			ICUTC_ERR("_struct_request_get_observe_type_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		break;
	case RESPONSE_SEND_P:
	default:
		break;
	}

	ret = icutc_send_ok_response(request);
	if (0 != ret) {
		ICUTC_ERR("icutc_send_ok_response() Fail(%d)", ret);
		_struct_main_loop_quit(false);
		return;
	}
}

static void _struct_destroy_resource()
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

static int _struct_create_resource(int tc_index)
{
	int ret;
	iotcon_resource_types_h light_types;
	iotcon_resource_interfaces_h light_ifaces;

	_struct_destroy_resource();

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
			_struct_request_handler,
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

static int _struct_response_get_options_n(iotcon_response_h response)
{
	int ret;
	iotcon_options_h options;

	ret = iotcon_response_get_options(response, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_response_get_options(NULL, &options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _struct_response_get_options_p(iotcon_response_h response)
{
	int ret;
	iotcon_options_h options;

	ret = iotcon_response_get_options(response, &options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _struct_response_get_representation_n(iotcon_response_h response)
{
	int ret;
	iotcon_representation_h representation;

	ret = iotcon_response_get_representation(response, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_response_get_representation(NULL, &representation);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _struct_response_get_representation_p(iotcon_response_h response)
{
	int ret;
	iotcon_representation_h representation;

	ret = iotcon_response_get_representation(response, &representation);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _struct_response_get_result_n(iotcon_response_h response)
{
	int ret;
	iotcon_response_result_e result;

	ret = iotcon_response_get_result(response, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_response_get_result(NULL, &result);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _struct_response_get_result_p(iotcon_response_h response)
{
	int ret;
	iotcon_response_result_e result;

	ret = iotcon_response_get_result(response, &result);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static void _struct_on_get(iotcon_remote_resource_h resource,	iotcon_error_e err,
		iotcon_request_type_e request_type, iotcon_response_h response, void *user_data)
{
	FN_CALL;
	int ret;
	int tc_index = (int)user_data;

	if (NULL == resource) {
		ICUTC_ERR("resource is NULL");
		_struct_main_loop_quit(false);
		return;
	}

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX) {
		g_timeout_count++;
		ret = iotcon_remote_resource_get(g_remote_resource, NULL, _struct_on_get, user_data);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_get() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		return;
	} else if (IOTCON_ERROR_NONE != err) {
		ICUTC_ERR("iotcon_remote_resource_get() Fail(%d)", err);
		_struct_main_loop_quit(false);
		return;
	}

	if (IOTCON_REQUEST_GET != request_type) {
		ICUTC_ERR("Invalid request type (%d)", request_type);
		_struct_main_loop_quit(false);
		return;
	}

	switch (tc_index) {
	case RESPONSE_GET_OPTIONS_N:
		ret = _struct_response_get_options_n(response);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_get_options_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		_struct_main_loop_quit(true);
		return;
	case RESPONSE_GET_OPTIONS_P:
		ret = _struct_response_get_options_p(response);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_get_options_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		_struct_main_loop_quit(true);
		return;
	case RESPONSE_GET_REPRESENTATION_N:
		ret = _struct_response_get_representation_n(response);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_get_representation_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		_struct_main_loop_quit(true);
		return;
	case RESPONSE_GET_REPRESENTATION_P:
		ret = _struct_response_get_representation_p(response);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_get_representation_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		_struct_main_loop_quit(true);
		return;
	case RESPONSE_GET_RESULT_N:
		ret = _struct_response_get_result_n(response);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_get_result_n() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		_struct_main_loop_quit(true);
		return;
	case RESPONSE_GET_RESULT_P:
		ret = _struct_response_get_result_p(response);
		if (0 != ret) {
			ICUTC_ERR("_struct_response_get_result_p() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return;
		}
		_struct_main_loop_quit(true);
		return;
	case RESPONSE_CREATE_N:
	case RESPONSE_CREATE_P:
	case RESPONSE_DESTROY_N:
	case RESPONSE_DESTROY_P:
	case RESPONSE_SET_RESULT_N:
	case RESPONSE_SET_RESULT_P:
	case RESPONSE_SET_REPRESENTATION_N:
	case RESPONSE_SET_REPRESENTATION_P:
	case RESPONSE_SET_OPTIONS_N:
	case RESPONSE_SET_OPTIONS_P:
	case RESPONSE_SEND_P:
	case REQUEST_GET_REPRESENTATION_N:
	case REQUEST_GET_REPRESENTATION_P:
	case REQUEST_GET_REQUEST_TYPE_N:
	case REQUEST_GET_REQUEST_TYPE_P:
	case REQUEST_GET_CONNECTIVITY_TYPE_N:
	case REQUEST_GET_CONNECTIVITY_TYPE_P:
	case REQUEST_GET_OPTIONS_N:
	case REQUEST_GET_OPTIONS_P:
	case REQUEST_GET_HOST_ADDRESS_N:
	case REQUEST_GET_HOST_ADDRESS_P:
	case REQUEST_GET_QUERY_N:
	case REQUEST_GET_QUERY_P:
	case REQUEST_GET_OBSERVE_ID_N:
	case REQUEST_GET_OBSERVE_ID_P:
	case REQUEST_GET_OBSERVE_TYPE_N:
	case REQUEST_GET_OBSERVE_TYPE_P:
		_struct_main_loop_quit(true);
		return;
	default:
		ICUTC_ERR("Invalid tc_index(%d)", tc_index);
		_struct_main_loop_quit(false);
		return;
	}
}

static bool _struct_found_resource(iotcon_remote_resource_h resource,
		iotcon_error_e err, void *user_data)
{
	FN_CALL;
	int ret;
	int tc_index = (int)user_data;
	iotcon_query_h query;
	iotcon_options_h options;
	char *host_address;

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX) {
		g_timeout_count++;

		ret = iotcon_query_create(&query);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_create() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_query_set_resource_type(query, LIGHT_RESOURCE_TYPE);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_set_resource_type() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_struct_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY,
				query, _struct_found_resource, user_data);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_find_resource() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_struct_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_query_destroy(query);

		return IOTCON_FUNC_STOP;
	} else if (IOTCON_ERROR_NONE != err) {
		_struct_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	if (g_found)
		return IOTCON_FUNC_STOP;
	g_found = true;

	ret = iotcon_remote_resource_get_host_address(resource, &host_address);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_get_host_address() Fail(%d)", ret);
		_struct_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	ICUTC_INFO("expected host_address[%s], found host_address[%s]", g_ipv4_address, host_address);

	if (strstr(host_address, g_ipv4_address) == NULL) { // targeted resource, BUT wrong device, so skip this resource and try again
		g_found = false;
		return IOTCON_FUNC_CONTINUE;
	}

	switch (tc_index) {
	case REQUEST_GET_REPRESENTATION_N:
	case REQUEST_GET_REPRESENTATION_P:
	case REQUEST_GET_REQUEST_TYPE_N:
	case REQUEST_GET_REQUEST_TYPE_P:
	case REQUEST_GET_CONNECTIVITY_TYPE_N:
	case REQUEST_GET_CONNECTIVITY_TYPE_P:
	case REQUEST_GET_OPTIONS_N:
	case REQUEST_GET_OPTIONS_P:
	case REQUEST_GET_HOST_ADDRESS_N:
	case REQUEST_GET_HOST_ADDRESS_P:
	case REQUEST_GET_QUERY_N:
	case REQUEST_GET_QUERY_P:
	case REQUEST_GET_OBSERVE_ID_N:
	case REQUEST_GET_OBSERVE_ID_P:
	case REQUEST_GET_OBSERVE_TYPE_N:
	case REQUEST_GET_OBSERVE_TYPE_P:
	case RESPONSE_CREATE_N:
	case RESPONSE_CREATE_P:
	case RESPONSE_DESTROY_N:
	case RESPONSE_DESTROY_P:
	case RESPONSE_GET_OPTIONS_N:
	case RESPONSE_GET_OPTIONS_P:
	case RESPONSE_GET_REPRESENTATION_N:
	case RESPONSE_GET_REPRESENTATION_P:
	case RESPONSE_GET_RESULT_N:
	case RESPONSE_GET_RESULT_P:
	case RESPONSE_SET_RESULT_N:
	case RESPONSE_SET_RESULT_P:
	case RESPONSE_SET_REPRESENTATION_N:
	case RESPONSE_SET_REPRESENTATION_P:
	case RESPONSE_SET_OPTIONS_N:
	case RESPONSE_SET_OPTIONS_P:
	case RESPONSE_SEND_P:
		ret = iotcon_remote_resource_clone(resource, &g_remote_resource);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_clone() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		/* Add query */
		ret = iotcon_query_create(&query);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_create() Fail(%d)", ret);
			_struct_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_query_add(query, "key", "value");
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_add() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_struct_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		/* Add options */
		ret = iotcon_options_create(&options);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_options_create() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_struct_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_options_add(options, 2048, "data");
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_options_add() Fail(%d)", ret);
			iotcon_query_destroy(query);
			iotcon_options_destroy(options);
			_struct_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_remote_resource_set_options(g_remote_resource, options);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_set_options() Fail(%d)", ret);
			iotcon_query_destroy(query);
			iotcon_options_destroy(options);
			_struct_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_options_destroy(options);

		ret = iotcon_remote_resource_get(g_remote_resource, query, _struct_on_get, (void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_clone() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_struct_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		iotcon_query_destroy(query);
		break;
	default:
		ICUTC_ERR("Invalid tc_index(%d)", tc_index);
		_struct_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}
	return IOTCON_FUNC_STOP;
}

static int _struct_handle_async(int tc_index)
{
	FN_CALL;
	int ret;
	iotcon_query_h query;

	g_loop = g_main_loop_new(NULL, FALSE);

	ret = _struct_create_resource(tc_index);
	if (0 != ret) {
		ICUTC_ERR("_struct_create_resource() Fail(%d)", ret);
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
			query, _struct_found_resource, (void *)tc_index);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_find_resource() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}
	iotcon_query_destroy(query);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	_struct_destroy_resource();

	if (true == g_result)
		return 0;
	else
		return 1;
}
/* ##################################################### */

//& set: Iotcon
#define ICL_OPTIONID_MIN 2048
#define ICL_OPTIONID_MAX 3000

/**
 * @function      utc_iotcon_struct_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_struct_startup(void)
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
 * @function      utc_iotcon_struct_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_struct_cleanup(void)
{
	icutc_free_client_ipv4_address();

	if (true == g_feature)
		iotcon_deinitialize();
}

/**
 * @testcase      utc_iotcon_options_create_n
 * @since_tizen   3.0
 * @description   Test fail creating a options with invalid parameter.
 */
int utc_iotcon_options_create_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_options_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_options_create(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_options_create_p
 * @since_tizen   3.0
 * @description   Test creating a options.
 */
int utc_iotcon_options_create_p(void)
{
	int ret;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_options_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_options_create(&options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	iotcon_options_destroy(options);

	return 0;
}

/**
 * @testcase      utc_iotcon_options_destroy_n
 * @since_tizen   3.0
 * @description   Test fail destroying a options with invalid parameter.
 */
int utc_iotcon_options_destroy_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_options_destroy(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_options_destroy(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase      utc_iotcon_options_destroy_p
 * @since_tizen   3.0
 * @description   Test destroying a options.
 */
int utc_iotcon_options_destroy_p(void)
{
	int ret;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_options_destroy(options);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_options_create(&options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_options_destroy(options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);
	return 0;
}

/**
 * @testcase      utc_iotcon_options_add_n
 * @since_tizen   3.0
 * @description   Test fail adding option to options with invalid parameter.
 */
int utc_iotcon_options_add_n(void)
{
	int ret;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_options_add(NULL, ICL_OPTIONID_MIN, "data");
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_options_add(NULL, ICL_OPTIONID_MIN, "data");
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_options_create(&options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_options_add(options, ICL_OPTIONID_MIN, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_options_add() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}

	/* check id range : ICL_OPTIONID_MIN <= id <= ICL_OPTIONID_MAX */
	ret = iotcon_options_add(options, ICL_OPTIONID_MIN - 1, "data");
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_options_add() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}

	ret = iotcon_options_add(options, ICL_OPTIONID_MAX + 1, "data");
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_options_add() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}

	iotcon_options_destroy(options);

	return 0;
}

/**
 * @testcase      utc_iotcon_options_add_p
 * @since_tizen   3.0
 * @description   Test adding option to options.
 */
int utc_iotcon_options_add_p(void)
{
	int ret;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_options_add(NULL, ICL_OPTIONID_MIN, "data");
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_options_create(&options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_options_add(options, ICL_OPTIONID_MIN, "data");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_add() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}

	iotcon_options_destroy(options);

	return 0;
}

/**
 * @testcase      utc_iotcon_options_remove_n
 * @since_tizen   3.0
 * @description   Test fail removing option from options with invalid parameter.
 */
int utc_iotcon_options_remove_n(void)
{
	int ret;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_options_remove(NULL, 0);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_options_remove(NULL, 0);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_options_create(&options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	/* in case of no data */
	ret = iotcon_options_remove(options, 0);
	if (IOTCON_ERROR_NONE == ret) {
		ICUTC_ERR("iotcon_options_remove() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}

	iotcon_options_destroy(options);

	return 0;
}

/**
 * @testcase      utc_iotcon_options_remove_p
 * @since_tizen   3.0
 * @description   Test removing option from options.
 */
int utc_iotcon_options_remove_p(void)
{
	int ret;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_options_remove(NULL, 0);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_options_create(&options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_options_add(options, ICL_OPTIONID_MIN, "data");
	if (IOTCON_ERROR_NONE != ret) {
		iotcon_options_destroy(options);
		return 1;
	}

	ret = iotcon_options_remove(options, ICL_OPTIONID_MIN);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_remove() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}

	iotcon_options_destroy(options);

	return 0;
}

/**
 * @testcase      utc_iotcon_options_lookup_n
 * @since_tizen   3.0
 * @description   Test fail getting option from options with invalid parameter.
 */
int utc_iotcon_options_lookup_n(void)
{
	int ret;
	char *data;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_options_lookup(NULL, ICL_OPTIONID_MIN, &data);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_options_lookup(NULL, ICL_OPTIONID_MIN, &data);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_options_lookup(options, ICL_OPTIONID_MIN, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_options_lookup_p
 * @since_tizen   3.0
 * @description   Test getting option from options.
 */
int utc_iotcon_options_lookup_p(void)
{
	int ret;
	char *data;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_options_lookup(NULL, ICL_OPTIONID_MIN, &data);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_options_create(&options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_options_add(options, ICL_OPTIONID_MIN, "data");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_add() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}

	ret = iotcon_options_lookup(options, ICL_OPTIONID_MIN, &data);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_lookup() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}
	if (0 != strcmp(data, "data")) {
		ICUTC_ERR("data(%s) is not data", data);
		iotcon_options_destroy(options);
		return 1;
	}

	/* normal case */
	ret = iotcon_options_add(options, ICL_OPTIONID_MIN, "data");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_add() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}

	ret = iotcon_options_lookup(options, ICL_OPTIONID_MIN, &data);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_lookup() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}
	if (0 != strcmp("data", data)) {
		ICUTC_ERR("data(%s) is not data", data);
		iotcon_options_destroy(options);
		return 1;
	}

	iotcon_options_destroy(options);

	return 0;
}

static bool _iotcon_options_foreach_cb(unsigned short id, const char *data,
		void *user_data)
{
	if (user_data)
		++ (*((int *)user_data));

	return IOTCON_FUNC_CONTINUE;
}

/**
 * @testcase      utc_iotcon_options_foreach_n
 * @since_tizen   3.0
 * @description   Test fail iterating option from options with invalid parameter.
 */
int utc_iotcon_options_foreach_n(void)
{
	int ret;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_options_foreach(NULL, _iotcon_options_foreach_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_options_foreach(NULL, _iotcon_options_foreach_cb, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_options_foreach(options, NULL, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_options_foreach_p
 * @since_tizen   3.0
 * @description   Test iterating option from options.
 */
int utc_iotcon_options_foreach_p(void)
{
	int ret;
	int count =0;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_options_foreach(NULL, _iotcon_options_foreach_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_options_create(&options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_options_add(options, ICL_OPTIONID_MIN, "data1");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_add() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}

	ret = iotcon_options_add(options, ICL_OPTIONID_MIN + 1, "data2");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_add() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}

	ret = iotcon_options_foreach(options, _iotcon_options_foreach_cb, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_foreach() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}
	if (2 != count) {
		iotcon_options_destroy(options);
		return 1;
	}

	iotcon_options_destroy(options);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_create_n
 * @since_tizen   3.0
 * @description   Test fail creating a query with invalid parameter.
 */
int utc_iotcon_query_create_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_query_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase      utc_iotcon_query_create_p
 * @since_tizen   3.0
 * @description   Test creating a query.
 */
int utc_iotcon_query_create_p(void)
{
	int ret;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	iotcon_query_destroy(query);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_destroy_n
 * @since_tizen   3.0
 * @description   Test fail destroying a query with invalid parameter.
 */
int utc_iotcon_query_destroy_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_query_destroy(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_destroy(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase      utc_iotcon_query_destroy_p
 * @since_tizen   3.0
 * @description   Test destroying a query.
 */
int utc_iotcon_query_destroy_p(void)
{
	int ret;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_destroy(query);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_destroy(query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);
	return 0;
}

/**
 * @testcase      utc_iotcon_query_set_resource_type_n
 * @since_tizen   3.0
 * @description   Test fail setting resource types to query with invalid parameter.
 */
int utc_iotcon_query_set_resource_type_n(void)
{
	int ret;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_set_resource_type(NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_set_resource_type(NULL, LIGHT_RESOURCE_TYPE);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	iotcon_query_destroy(query);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_set_resource_type_p
 * @since_tizen   3.0
 * @description   Test setting resource types to query.
 */
int utc_iotcon_query_set_resource_type_p(void)
{
	int ret;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_set_resource_type(NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_set_resource_type(query, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_set_resource_type() Fail(%d)", ret);
		return 1;
	}

	iotcon_query_destroy(query);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_get_resource_type_n
 * @since_tizen   3.0
 * @description   Test fail getting resource types from query with invalid parameter.
 */
int utc_iotcon_query_get_resource_type_n(void)
{
	int ret;
	char *type;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_get_resource_type(NULL, &type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_set_resource_type(query, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_set_resource_type() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_query_get_resource_type(NULL, &type);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_query_get_resource_type(query, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	iotcon_query_destroy(query);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_get_resource_type_p
 * @since_tizen   3.0
 * @description   Test getting resource types from query.
 */
int utc_iotcon_query_get_resource_type_p(void)
{
	int ret;
	char *type;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_get_resource_type(NULL, &type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_set_resource_type(query, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_set_resource_type() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_query_get_resource_type(query, &type);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	iotcon_query_destroy(query);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_set_interface_n
 * @since_tizen   3.0
 * @description   Test fail setting interface to query with invalid parameter.
 */
int utc_iotcon_query_set_interface_n(void)
{
	int ret;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_set_interface(NULL, IOTCON_INTERFACE_DEFAULT);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_set_interface(NULL, IOTCON_INTERFACE_DEFAULT);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	iotcon_query_destroy(query);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_set_interface_p
 * @since_tizen   3.0
 * @description   Test setting interface to query.
 */
int utc_iotcon_query_set_interface_p(void)
{
	int ret;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_set_interface(NULL, IOTCON_INTERFACE_DEFAULT);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_set_interface(query, IOTCON_INTERFACE_DEFAULT);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	iotcon_query_destroy(query);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_get_interface_n
 * @since_tizen   3.0
 * @description   Test fail getting interface from query with invalid parameter.
 */
int utc_iotcon_query_get_interface_n(void)
{
	int ret;
	char *iface;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_get_interface(NULL, &iface);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_set_interface(query, IOTCON_INTERFACE_DEFAULT);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_get_interface(NULL, &iface);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	iotcon_query_destroy(query);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_get_interface_p
 * @since_tizen   3.0
 * @description   Test getting interface from query.
 */
int utc_iotcon_query_get_interface_p(void)
{
	int ret;
	char *iface;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_get_interface(NULL, &iface);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_set_interface(query, IOTCON_INTERFACE_DEFAULT);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_get_interface(query, &iface);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	iotcon_query_destroy(query);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_add_n
 * @since_tizen   3.0
 * @description   Test fail adding value to query with invalid parameter.
 */
int utc_iotcon_query_add_n(void)
{
	int ret;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_add(NULL, "key", "value");
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_add(NULL, "key", "value");
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_query_add(query, NULL, "value");
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_query_add(query, "key", NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_add_p
 * @since_tizen   3.0
 * @description   Test adding value to query.
 */
int utc_iotcon_query_add_p(void)
{
	int ret;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_add(NULL, "key", "value");
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_add(query, "key", "val");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_add() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}

	iotcon_query_destroy(query);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_remove_n
 * @since_tizen   3.0
 * @description   Test fail removing value from query with invalid parameter.
 */
int utc_iotcon_query_remove_n(void)
{
	int ret;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_remove(NULL, "key");
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_remove(NULL, "key");
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_query_remove(query, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	/* in case of no data */
	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_remove(query, "key");
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_query_remove() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}

	iotcon_query_destroy(query);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_remove_p
 * @since_tizen   3.0
 * @description   Test removing value from query.
 */
int utc_iotcon_query_remove_p(void)
{
	int ret;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_remove(NULL, "key");
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_add(query, "key", "val");
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_remove(query, "key");
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	iotcon_query_destroy(query);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_lookup_n
 * @since_tizen   3.0
 * @description   Test fail finding value from query with invalid parameter.
 */
int utc_iotcon_query_lookup_n(void)
{
	int ret;
	char *data;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_lookup(NULL, "key", &data);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_lookup(NULL, "key", &data);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_query_lookup(query, NULL, &data);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_query_lookup(query, "key", NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_lookup_p
 * @since_tizen   3.0
 * @description   Test finding value from query.
 */
int utc_iotcon_query_lookup_p(void)
{
	int ret;
	char *data;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_lookup(NULL, "key", &data);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	/* normal case */
	ret = iotcon_query_add(query, "key", "val");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_add() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}

	ret = iotcon_query_lookup(query, "key", &data);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_lookup() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}
	if (0 != strcmp("val", data)) {
		iotcon_query_destroy(query);
		return 1;
	}

	iotcon_query_destroy(query);

	return 0;
}

static bool _iotcon_query_foreach_cb(const char *key, const char *value,
		void *user_data)
{
	if (user_data)
		++ (*((int *)user_data));

	return IOTCON_FUNC_CONTINUE;
}

/**
 * @testcase      utc_iotcon_query_foreach_n
 * @since_tizen   3.0
 * @description   Test fail iterating value from query with invalid parameter.
 */
int utc_iotcon_query_foreach_n(void)
{
	int ret;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_foreach(NULL, _iotcon_query_foreach_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_foreach(NULL, _iotcon_query_foreach_cb, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_query_foreach(query, NULL, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_query_foreach_p
 * @since_tizen   3.0
 * @description   Test iterating value from query.
 */
int utc_iotcon_query_foreach_p(void)
{
	int ret;
	int count =0;
	iotcon_query_h query = NULL;

	if (false == g_feature) {
		ret = iotcon_query_foreach(NULL, _iotcon_query_foreach_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_query_create(&query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_query_add(query, "key1", "val1");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_add() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}

	ret = iotcon_query_add(query, "key2", "val2");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_add() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}

	ret = iotcon_query_add(query, "key3", "val3");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_add() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}

	ret = iotcon_query_foreach(query, _iotcon_query_foreach_cb, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_query_foreach() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}
	if (3 != count) {
		iotcon_query_destroy(query);
		return 1;
	}

	iotcon_query_destroy(query);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_types_create_n
 * @since_tizen   3.0
 * @description   Test fail creating resource types with invalid parameter.
 */
int utc_iotcon_resource_types_create_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_resource_types_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_types_create(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_types_create_p
 * @since_tizen   3.0
 * @description   Test creating resource types.
 */
int utc_iotcon_resource_types_create_p(void)
{
	int ret;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_types_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_types_create(&types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	iotcon_resource_types_destroy(types);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_types_destroy_n
 * @since_tizen   3.0
 * @description   Test fail destroying resource types with invalid parameter.
 */
int utc_iotcon_resource_types_destroy_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_resource_types_destroy(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_types_destroy(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_types_destroy_p
 * @since_tizen   3.0
 * @description   Test destroying resource types.
 */
int utc_iotcon_resource_types_destroy_p(void)
{
	int ret;
	iotcon_resource_types_h resource_types = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_types_destroy(resource_types);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_types_create(&resource_types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_destroy(resource_types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_types_add_n
 * @since_tizen   3.0
 * @description   Test fail adding type to resource types with invalid parameter.
 */
int utc_iotcon_resource_types_add_n(void)
{
	int ret;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_types_add(NULL, LIGHT_RESOURCE_TYPE);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_types_create(&types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_add(NULL, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	ret = iotcon_resource_types_add(types, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	iotcon_resource_types_destroy(types);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_types_add_p
 * @since_tizen   3.0
 * @description   Test adding type to resource types.
 */
int utc_iotcon_resource_types_add_p(void)
{
	int ret;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_types_add(NULL, LIGHT_RESOURCE_TYPE);
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

	iotcon_resource_types_destroy(types);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_types_remove_n
 * @since_tizen   3.0
 * @description   Test fail removing type from resource types with invalid parameter.
 */
int utc_iotcon_resource_types_remove_n(void)
{
	int ret;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_types_remove(NULL, LIGHT_RESOURCE_TYPE);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_types_remove(NULL, LIGHT_RESOURCE_TYPE);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_resource_types_remove(types, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	/* in case of no data */
	ret = iotcon_resource_types_create(&types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_remove(types, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_resource_types_remove() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	iotcon_resource_types_destroy(types);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_types_remove_p
 * @since_tizen   3.0
 * @description   Test removing type from resource types.
 */
int utc_iotcon_resource_types_remove_p(void)
{
	int ret;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_types_remove(NULL, LIGHT_RESOURCE_TYPE);
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

	ret = iotcon_resource_types_remove(types, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_remove() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	iotcon_resource_types_destroy(types);

	return 0;
}

static bool _iotcon_resource_types_foreach_cb(const char *type, void *user_data)
{
	if (user_data)
		++(*((int *)user_data));

	return IOTCON_FUNC_CONTINUE;
}

/**
 * @testcase      utc_iotcon_resource_types_foreach_n
 * @since_tizen   3.0
 * @description   Test fail iterating type from resource types with invalid parameter.
 */
int utc_iotcon_resource_types_foreach_n(void)
{
	int ret;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_types_foreach(NULL, _iotcon_resource_types_foreach_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_types_create(&types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_foreach(NULL, _iotcon_resource_types_foreach_cb, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_types_foreach() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	ret = iotcon_resource_types_foreach(types, NULL, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_types_foreach() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	iotcon_resource_types_destroy(types);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_types_foreach_p
 * @since_tizen   3.0
 * @description   Test iterating type from resource types.
 */
int utc_iotcon_resource_types_foreach_p(void)
{
	int ret;
	int count =0;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_types_foreach(NULL, _iotcon_resource_types_foreach_cb, NULL);
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

	ret = iotcon_resource_types_add(types, LIGHT_RESOURCE_TYPE2);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	ret = iotcon_resource_types_add(types, LIGHT_RESOURCE_TYPE3);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	ret = iotcon_resource_types_foreach(types, _iotcon_resource_types_foreach_cb, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_foreach() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}
	if (3 != count) {
		iotcon_resource_types_destroy(types);
		return 1;
	}

	iotcon_resource_types_destroy(types);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_types_clone_n
 * @since_tizen   3.0
 * @description   Test fail cloning resource types with invalid parameter.
 */
int utc_iotcon_resource_types_clone_n(void)
{
	int ret;
	iotcon_resource_types_h types;
	iotcon_resource_types_h types_clone;

	if (false == g_feature) {
		ret = iotcon_resource_types_clone(NULL, &types_clone);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource_types(LIGHT_RESOURCE_TYPE, &types);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource_types() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_resource_types_clone(NULL, &types_clone);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_types_clone() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}
	ret = iotcon_resource_types_clone(types, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_types_clone() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	iotcon_resource_types_destroy(types);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_types_clone_p
 * @since_tizen   3.0
 * @description   Test cloning resource types.
 */
int utc_iotcon_resource_types_clone_p(void)
{
	int ret;
	iotcon_resource_types_h types;
	iotcon_resource_types_h types_clone;

	if (false == g_feature) {
		ret = iotcon_resource_types_clone(NULL, &types_clone);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource_types(LIGHT_RESOURCE_TYPE, &types);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource_types() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_resource_types_clone(types, &types_clone);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_clone() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return 1;
	}

	iotcon_resource_types_destroy(types_clone);
	iotcon_resource_types_destroy(types);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_interfaces_create_n
 * @since_tizen   3.0
 * @description   Test fail creating resource interfaces with invalid parameter.
 */
int utc_iotcon_resource_interfaces_create_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_resource_interfaces_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_interfaces_create(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_interfaces_create_p
 * @since_tizen   3.0
 * @description   Test creating resource interfaces.
 */
int utc_iotcon_resource_interfaces_create_p(void)
{
	int ret;
	iotcon_resource_interfaces_h ifaces = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_interfaces_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_interfaces_create(&ifaces);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	iotcon_resource_interfaces_destroy(ifaces);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_interfaces_destroy_n
 * @since_tizen   3.0
 * @description   Test fail destroying resource interfaces with invalid parameter.
 */
int utc_iotcon_resource_interfaces_destroy_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_resource_interfaces_destroy(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_interfaces_destroy(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_interfaces_destroy_p
 * @since_tizen   3.0
 * @description   Test destroying resource interfaces.
 */
int utc_iotcon_resource_interfaces_destroy_p(void)
{
	int ret;
	iotcon_resource_interfaces_h ifaces = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_interfaces_destroy(ifaces);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_interfaces_create(&ifaces);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_interfaces_destroy(ifaces);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_interfaces_add_n
 * @since_tizen   3.0
 * @description   Test fail adding interface to resource interfaces with invalid parameter.
 */
int utc_iotcon_resource_interfaces_add_n(void)
{
	int ret;
	iotcon_resource_interfaces_h interfaces = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_interfaces_add(NULL, IOTCON_INTERFACE_DEFAULT);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_interfaces_create(&interfaces);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_interfaces_add(NULL, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(interfaces);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(interfaces, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(interfaces);
		return 1;
	}

	iotcon_resource_interfaces_destroy(interfaces);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_interfaces_add_p
 * @since_tizen   3.0
 * @description   Test adding interface to resource interfaces.
 */
int utc_iotcon_resource_interfaces_add_p(void)
{
	int ret;
	iotcon_resource_interfaces_h interfaces = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_interfaces_add(interfaces, IOTCON_INTERFACE_DEFAULT);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_interfaces_create(&interfaces);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_interfaces_add(interfaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(interfaces);
		return 1;
	}

	iotcon_resource_interfaces_destroy(interfaces);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_interfaces_remove_n
 * @since_tizen   3.0
 * @description   Test fail removing interface from resource interfaces with invalid parameter.
 */
int utc_iotcon_resource_interfaces_remove_n(void)
{
	int ret;
	iotcon_resource_interfaces_h interfaces = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_interfaces_remove(NULL, IOTCON_INTERFACE_DEFAULT);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_interfaces_remove(NULL, IOTCON_INTERFACE_DEFAULT);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_resource_interfaces_remove(interfaces, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	/* in case of no data */
	ret = iotcon_resource_interfaces_create(&interfaces);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_interfaces_remove(interfaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_remove() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(interfaces);
		return 1;
	}

	iotcon_resource_interfaces_destroy(interfaces);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_interfaces_remove_p
 * @since_tizen   3.0
 * @description   Test removing interface from resource interfaces.
 */
int utc_iotcon_resource_interfaces_remove_p(void)
{
	int ret;
	iotcon_resource_interfaces_h interfaces = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_interfaces_remove(NULL, IOTCON_INTERFACE_DEFAULT);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_interfaces_create(&interfaces);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_interfaces_add(interfaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(interfaces);
		return 1;
	}

	ret = iotcon_resource_interfaces_remove(interfaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_remove() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(interfaces);
		return 1;
	}

	iotcon_resource_interfaces_destroy(interfaces);

	return 0;
}

static bool _iotcon_resource_interfaces_foreach_cb(const char *interface, void *user_data)
{
	if (user_data)
		++(*((int *)user_data));

	return IOTCON_FUNC_CONTINUE;
}

/**
 * @testcase      utc_iotcon_resource_interfaces_foreach_n
 * @since_tizen   3.0
 * @description   Test fail iterating interface from resource interfaces with invalid parameter.
 */
int utc_iotcon_resource_interfaces_foreach_n(void)
{
	int ret;
	iotcon_resource_interfaces_h interfaces = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_interfaces_foreach(NULL,
				_iotcon_resource_interfaces_foreach_cb,
				NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_interfaces_create(&interfaces);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_interfaces_foreach(NULL,
			_iotcon_resource_interfaces_foreach_cb,
			NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_foreach() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(interfaces);
		return 1;
	}

	ret = iotcon_resource_interfaces_foreach(interfaces, NULL, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_foreach() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(interfaces);
		return 1;
	}

	iotcon_resource_interfaces_destroy(interfaces);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_interfaces_foreach_p
 * @since_tizen   3.0
 * @description   Test iterating interface from resource interfaces.
 */
int utc_iotcon_resource_interfaces_foreach_p(void)
{
	int ret;
	int count =0;
	iotcon_resource_interfaces_h interfaces = NULL;

	if (false == g_feature) {
		ret = iotcon_resource_interfaces_foreach(NULL,
				_iotcon_resource_interfaces_foreach_cb,
				NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_interfaces_create(&interfaces);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_interfaces_add(interfaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(interfaces);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(interfaces, IOTCON_INTERFACE_BATCH);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(interfaces);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(interfaces, IOTCON_INTERFACE_LINK);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(interfaces);
		return 1;
	}

	ret = iotcon_resource_interfaces_foreach(interfaces,
			_iotcon_resource_interfaces_foreach_cb,
			&count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_foreach() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(interfaces);
		return 1;
	}
	if (3 != count) {
		iotcon_resource_interfaces_destroy(interfaces);
		return 1;
	}

	iotcon_resource_interfaces_destroy(interfaces);

	return 0;
}

/**
 * @testcase      utc_iotcon_resource_interfaces_clone_n
 * @since_tizen   3.0
 * @description   Test fail cloning resource interfaces with invalid parameter.
 */
int utc_iotcon_resource_interfaces_clone_n(void)
{
	int ret;
	iotcon_resource_interfaces_h ifaces;
	iotcon_resource_interfaces_h ifaces_clone;

	if (false == g_feature) {
		ret = iotcon_resource_interfaces_clone(NULL, &ifaces_clone);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource_interfaces(&ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource_interfaces() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_resource_interfaces_clone(NULL, &ifaces_clone);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_clone() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		return 1;
	}
	ret = iotcon_resource_interfaces_clone(ifaces, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_clone() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		return 1;
	}

	iotcon_resource_interfaces_destroy(ifaces);
	return 0;
}

/**
 * @testcase      utc_iotcon_resource_interfaces_clone_p
 * @since_tizen   3.0
 * @description   Test cloning resource interfaces.
 */
int utc_iotcon_resource_interfaces_clone_p(void)
{
	int ret;
	iotcon_resource_interfaces_h ifaces;
	iotcon_resource_interfaces_h ifaces_clone;

	if (false == g_feature) {
		ret = iotcon_resource_interfaces_clone(NULL, &ifaces_clone);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_create_resource_interfaces(&ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource_interfaces() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_resource_interfaces_clone(ifaces, &ifaces_clone);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_clone() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		return 1;
	}

	iotcon_resource_interfaces_destroy(ifaces_clone);
	iotcon_resource_interfaces_destroy(ifaces);
	return 0;
}

/**
 * @testcase      utc_iotcon_observers_create_n
 * @since_tizen   3.0
 * @description   Test fail creating observers with invalid parameter.
 */
int utc_iotcon_observers_create_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_observers_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_observers_create(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_observer_create_p
 * @since_tizen   3.0
 * @description   Test creating observers.
 */
int utc_iotcon_observer_create_p(void)
{
	int ret;
	iotcon_observers_h observers;

	if (false == g_feature) {
		ret = iotcon_observers_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_observers_create(&observers);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	iotcon_observers_destroy(observers);

	return 0;
}

/**
 * @testcase      utc_iotcon_observers_destroy_n
 * @since_tizen   3.0
 * @description   Test fail destroying observers with invalid parameter.
 */
int utc_iotcon_observers_destroy_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_observers_destroy(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_observers_destroy(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase      utc_iotcon_observers_destroy_p
 * @since_tizen   3.0
 * @description   Test destroying observers.
 */
int utc_iotcon_observers_destroy_p(void)
{
	int ret;
	iotcon_observers_h observers = NULL;

	if (false == g_feature) {
		ret = iotcon_observers_destroy(observers);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_observers_create(&observers);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_observers_destroy(observers);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);
	return 0;
}

/**
 * @testcase      utc_iotcon_observers_add_n
 * @since_tizen   3.0
 * @description   Test fail adding observer to observers with invalid parameter.
 */
int utc_iotcon_observers_add_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_observers_add(NULL, 1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_observers_add(NULL, 1);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_observers_add_p
 * @since_tizen   3.0
 * @description   Test adding observer to observers.
 */
int utc_iotcon_observers_add_p(void)
{
	int ret;
	iotcon_observers_h observers;

	if (false == g_feature) {
		ret = iotcon_observers_add(NULL, 1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_observers_create(&observers);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_observers_add(observers, 1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_observers_add() Fail(%d)", ret);
		iotcon_observers_destroy(observers);
		return 1;
	}

	iotcon_observers_destroy(observers);

	return 0;
}

/**
 * @testcase      utc_iotcon_observers_remove_n
 * @since_tizen   3.0
 * @description   Test fail removing observer from observers with invalid parameter.
 */
int utc_iotcon_observers_remove_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_observers_remove(NULL, 1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_observers_remove(NULL, 1);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_observers_remove_p
 * @since_tizen   3.0
 * @description   Test removing observer from observers.
 */
int utc_iotcon_observers_remove_p(void)
{
	int ret;
	iotcon_observers_h observers;

	if (false == g_feature) {
		ret = iotcon_observers_remove(NULL, 1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_observers_create(&observers);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_observers_add(observers, 1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_observers_add() Fail(%d)", ret);
		iotcon_observers_destroy(observers);
		return 1;
	}

	ret = iotcon_observers_remove(observers, 1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_observers_remove() Fail(%d)", ret);
		iotcon_observers_destroy(observers);
		return 1;
	}

	iotcon_observers_destroy(observers);

	return 0;
}

/**
 * @testcase      utc_iotcon_request_get_representation_n
 * @since_tizen   3.0
 * @description   Test fail getting representation from request with invalid parameter.
 */
int utc_iotcon_request_get_representation_n(void)
{
	int ret;
	iotcon_representation_h repr;

	if (false == g_feature) {
		ret = iotcon_request_get_representation(NULL, &repr);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_REPRESENTATION_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_request_get_representation_p
 * @since_tizen   3.0
 * @description   Test getting representation from request.
 */
int utc_iotcon_request_get_representation_p(void)
{
	int ret;
	iotcon_representation_h repr;

	if (false == g_feature) {
		ret = iotcon_request_get_representation(NULL, &repr);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_REPRESENTATION_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_request_get_request_type_n
 * @since_tizen   3.0
 * @description   Test fail getting request type from request with invalid parameter.
 */
int utc_iotcon_request_get_request_type_n(void)
{
	int ret;
	iotcon_request_type_e request_type;

	if (false == g_feature) {
		ret = iotcon_request_get_request_type(NULL, &request_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_REQUEST_TYPE_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_request_get_request_type_p
 * @since_tizen   3.0
 * @description   Test getting request type from request.
 */
int utc_iotcon_request_get_request_type_p(void)
{
	int ret;
	iotcon_request_type_e request_type;

	if (false == g_feature) {
		ret = iotcon_request_get_request_type(NULL, &request_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_REQUEST_TYPE_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_request_get_connectivity_type_n
 * @since_tizen   3.0
 * @description   Test fail getting connectivity type from request with invalid parameter.
 */
int utc_iotcon_request_get_connectivity_type_n(void)
{
	int ret;
	iotcon_connectivity_type_e conn_type;

	if (false == g_feature) {
		ret = iotcon_request_get_connectivity_type(NULL, &conn_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_CONNECTIVITY_TYPE_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_request_get_connectivity_type_p
 * @since_tizen   3.0
 * @description   Test getting connectivity type from request.
 */
int utc_iotcon_request_get_connectivity_type_p(void)
{
	int ret;
	iotcon_connectivity_type_e conn_type;

	if (false == g_feature) {
		ret = iotcon_request_get_connectivity_type(NULL, &conn_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_CONNECTIVITY_TYPE_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}


/**
 * @testcase      utc_iotcon_request_get_options_n
 * @since_tizen   3.0
 * @description   Test fail getting optiions from request with invalid parameter.
 */
int utc_iotcon_request_get_options_n(void)
{
	int ret;
	iotcon_options_h options;

	if (false == g_feature) {
		ret = iotcon_request_get_options(NULL, &options);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_OPTIONS_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_request_get_options_p
 * @since_tizen   3.0
 * @description   Test getting optiions from request.
 */
int utc_iotcon_request_get_options_p(void)
{
	int ret;
	iotcon_options_h options;

	if (false == g_feature) {
		ret = iotcon_request_get_options(NULL, &options);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_OPTIONS_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_request_get_host_address_n
 * @since_tizen   3.0
 * @description   Test fail getting host address from request with invalid parameter.
 */
int utc_iotcon_request_get_host_address_n(void)
{
	int ret;
	char *host_address;

	if (false == g_feature) {
		ret = iotcon_request_get_host_address(NULL, &host_address);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_HOST_ADDRESS_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;

}

/**
 * @testcase      utc_iotcon_request_get_host_address_p
 * @since_tizen   3.0
 * @description   Test getting host address from request.
 */
int utc_iotcon_request_get_host_address_p(void)
{
	int ret;
	char *host_address;

	if (false == g_feature) {
		ret = iotcon_request_get_host_address(NULL, &host_address);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_HOST_ADDRESS_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_request_get_query_n
 * @since_tizen   3.0
 * @description   Test fail getting query from request with invalid parameter.
 */
int utc_iotcon_request_get_query_n(void)
{
	int ret;
	iotcon_query_h query;

	if (false == g_feature) {
		ret = iotcon_request_get_query(NULL, &query);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_QUERY_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_request_get_query_p
 * @since_tizen   3.0
 * @description   Test getting query from request.
 */
int utc_iotcon_request_get_query_p(void)
{
	int ret;
	iotcon_query_h query;

	if (false == g_feature) {
		ret = iotcon_request_get_query(NULL, &query);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_QUERY_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_request_get_observe_id_n
 * @since_tizen   3.0
 * @description   Test fail getting observe id from request with invalid parameter.
 */
int utc_iotcon_request_get_observe_id_n(void)
{
	int ret;
	int observe_id;

	if (false == g_feature) {
		ret = iotcon_request_get_observe_id(NULL, &observe_id);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_OBSERVE_ID_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_request_get_observe_id_p
 * @since_tizen   3.0
 * @description   Test getting observe id from request.
 */
int utc_iotcon_request_get_observe_id_p(void)
{
	int ret;
	int observe_id;

	if (false == g_feature) {
		ret = iotcon_request_get_observe_id(NULL, &observe_id);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_OBSERVE_ID_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}


/**
 * @testcase      utc_iotcon_request_get_observe_type_n
 * @since_tizen   3.0
 * @description   Test fail getting observe type from request with invalid parameter.
 */
int utc_iotcon_request_get_observe_type_n(void)
{
	int ret;
	iotcon_observe_type_e observe_type;

	if (false == g_feature) {
		ret = iotcon_request_get_observe_type(NULL, &observe_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_OBSERVE_TYPE_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}


/**
 * @testcase      utc_iotcon_request_get_observe_type_p
 * @since_tizen   3.0
 * @description   Test getting observe type from request.
 */
int utc_iotcon_request_get_observe_type_p(void)
{
	int ret;
	iotcon_observe_type_e observe_type;

	if (false == g_feature) {
		ret = iotcon_request_get_observe_type(NULL, &observe_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(REQUEST_GET_OBSERVE_TYPE_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_create_n
 * @since_tizen   3.0
 * @description   Test fail creating resopnse with invalid parameter.
 */
int utc_iotcon_response_create_n(void)
{
	int ret;
	iotcon_response_h response;

	if (false == g_feature) {
		ret = iotcon_response_create(NULL, &response);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_CREATE_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_create_p
 * @since_tizen   3.0
 * @description   Test creating resopnse
 */
int utc_iotcon_response_create_p(void)
{
	int ret;
	iotcon_response_h response;

	if (false == g_feature) {
		ret = iotcon_response_create(NULL, &response);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_CREATE_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_destroy_n
 * @since_tizen   3.0
 * @description   Test fail destroying resopnse with invalid parameter.
 */
int utc_iotcon_response_destroy_n(void)
{
	int ret;
	iotcon_response_h response = NULL;

	if (false == g_feature) {
		ret = iotcon_response_destroy(response);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_DESTROY_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_destroy_p
 * @since_tizen   3.0
 * @description   Test destroying resopnse.
 */
int utc_iotcon_response_destroy_p(void)
{
	int ret;
	iotcon_response_h response = NULL;

	if (false == g_feature) {
		ret = iotcon_response_destroy(response);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_DESTROY_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_get_options_n
 * @since_tizen   3.0
 * @description   Test fail getting options from response with invalid parameter.
 */
int utc_iotcon_response_get_options_n(void)
{
	int ret;
	iotcon_options_h options;

	if (false == g_feature) {
		ret = iotcon_response_get_options(NULL, &options);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_GET_OPTIONS_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_get_options_p
 * @since_tizen   3.0
 * @description   Test getting options from response.
 */
int utc_iotcon_response_get_options_p(void)
{
	int ret;
	iotcon_options_h options;

	if (false == g_feature) {
		ret = iotcon_response_get_options(NULL, &options);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_GET_OPTIONS_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_get_representation_n
 * @since_tizen   3.0
 * @description   Test fail getting representation from response with invalid parameter.
 */
int utc_iotcon_response_get_representation_n(void)
{
	int ret;
	iotcon_representation_h repr;

	if (false == g_feature) {
		ret = iotcon_response_get_representation(NULL, &repr);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_GET_REPRESENTATION_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;

}

/**
 * @testcase      utc_iotcon_response_get_representation_p
 * @since_tizen   3.0
 * @description   Test getting representation from response.
 */
int utc_iotcon_response_get_representation_p(void)
{
	int ret;
	iotcon_representation_h repr;

	if (false == g_feature) {
		ret = iotcon_response_get_representation(NULL, &repr);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_GET_REPRESENTATION_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_get_result_n
 * @since_tizen   3.0
 * @description   Test fail getting result from response with invalid parameter.
 */
int utc_iotcon_response_get_result_n(void)
{
	int ret;
	iotcon_response_result_e result;

	if (false == g_feature) {
		ret = iotcon_response_get_result(NULL, &result);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_GET_RESULT_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_get_result_p
 * @since_tizen   3.0
 * @description   Test getting result from response.
 */
int utc_iotcon_response_get_result_p(void)
{
	int ret;
	iotcon_response_result_e result;

	if (false == g_feature) {
		ret = iotcon_response_get_result(NULL, &result);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_GET_RESULT_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_set_result_n
 * @since_tizen   3.0
 * @description   Test fail setting result to response with invalid parameter.
 */
int utc_iotcon_response_set_result_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_response_set_result(NULL, IOTCON_RESPONSE_OK);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_SET_RESULT_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_set_result_p
 * @since_tizen   3.0
 * @description   Test setting result to response.
 */
int utc_iotcon_response_set_result_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_response_set_result(NULL, IOTCON_RESPONSE_OK);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_SET_RESULT_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_set_representation_n
 * @since_tizen   3.0
 * @description   Test fail setting representation to response with invalid parameter.
 */
int utc_iotcon_response_set_representation_n(void)
{
	int ret;
	iotcon_representation_h repr = NULL;

	if (false == g_feature) {
		ret = iotcon_response_set_representation(NULL, repr);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_SET_REPRESENTATION_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_set_representation_p
 * @since_tizen   3.0
 * @description   Test setting representation to response.
 */
int utc_iotcon_response_set_representation_p(void)
{
	int ret;
	iotcon_representation_h repr = NULL;

	if (false == g_feature) {
		ret = iotcon_response_set_representation(NULL, repr);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_SET_REPRESENTATION_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_set_options_n
 * @since_tizen   3.0
 * @description   Test fail setting options to response with invalid parameter.
 */
int utc_iotcon_response_set_options_n(void)
{
	int ret;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_response_set_options(NULL, options);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_SET_OPTIONS_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_response_set_options_p
 * @since_tizen   3.0
 * @description   Test setting options to response.
 */
int utc_iotcon_response_set_options_p(void)
{
	int ret;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_response_set_options(NULL, options);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_SET_OPTIONS_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;

}

/**
 * @testcase      utc_iotcon_response_send_n
 * @since_tizen   3.0
 * @description   Test fail sending response with invalid parameter.
 */
int utc_iotcon_response_send_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_response_send(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_response_send(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_response_send_p
 * @since_tizen   3.0
 * @description   Test sending response.
 */
int utc_iotcon_response_send_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_response_send(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _struct_handle_async(RESPONSE_SEND_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

