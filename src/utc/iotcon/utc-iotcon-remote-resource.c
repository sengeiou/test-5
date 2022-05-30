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
	REMOTE_RESOURCE_CLONE_P,
	REMOTE_RESOURCE_CLONE_N,
	REMOTE_RESOURCE_CREATE_P,
	REMOTE_RESOURCE_CREATE_N,
	REMOTE_RESOURCE_DELETE_P,
	REMOTE_RESOURCE_DELETE_N,
	REMOTE_RESOURCE_DESTROY_P,
	REMOTE_RESOURCE_DESTROY_N,
	REMOTE_RESOURCE_GET_P,
	REMOTE_RESOURCE_GET_N,
	REMOTE_RESOURCE_GET_CONNECTIVITY_TYPE_P,
	REMOTE_RESOURCE_GET_CONNECTIVITY_TYPE_N,
	REMOTE_RESOURCE_GET_DEVICE_ID_P,
	REMOTE_RESOURCE_GET_DEVICE_ID_N,
	REMOTE_RESOURCE_GET_DEVICE_NAME_P,
	REMOTE_RESOURCE_GET_DEVICE_NAME_N,
	REMOTE_RESOURCE_GET_HOST_ADDRESS_P,
	REMOTE_RESOURCE_GET_HOST_ADDRESS_N,
	REMOTE_RESOURCE_GET_INTERFACES_P,
	REMOTE_RESOURCE_GET_INTERFACES_N,
	REMOTE_RESOURCE_GET_OPTIONS_P,
	REMOTE_RESOURCE_GET_OPTIONS_N,
	REMOTE_RESOURCE_GET_PROPERTIES_P,
	REMOTE_RESOURCE_GET_PROPERTIES_N,
	REMOTE_RESOURCE_GET_TYPES_P,
	REMOTE_RESOURCE_GET_TYPES_N,
	REMOTE_RESOURCE_GET_URI_PATH_P,
	REMOTE_RESOURCE_GET_URI_PATH_N,
	REMOTE_RESOURCE_OBSERVE_REGISTER_P,
	REMOTE_RESOURCE_OBSERVE_REGISTER_N,
	REMOTE_RESOURCE_OBSERVE_DEREGISTER_P,
	REMOTE_RESOURCE_OBSERVE_DEREGISTER_N,
	REMOTE_RESOURCE_POST_P,
	REMOTE_RESOURCE_POST_N,
	REMOTE_RESOURCE_PUT_P,
	REMOTE_RESOURCE_PUT_N,
	REMOTE_RESOURCE_SET_OPTIONS_P,
	REMOTE_RESOURCE_SET_OPTIONS_N,
};

static bool g_result;
static bool g_found;
static bool g_feature;
static int g_timeout_count;
static GMainLoop *g_loop;

/* ### server side ### */
static iotcon_resource_h g_light_resource;
static iotcon_remote_resource_h g_remote_resource;
static iotcon_lite_resource_h g_lite_light_resource;

static gboolean _remote_resource_main_loop_quit_idle(gpointer p)
{
	FN_CALL;
	g_main_loop_quit(g_loop);
	return G_SOURCE_REMOVE;
}

static void _remote_resource_main_loop_quit(bool result)
{
	ICUTC_INFO("result = %d", result);
	g_result = result;
	g_idle_add(_remote_resource_main_loop_quit_idle, NULL);
}

static void _remote_resource_destroy_resource()
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

static void _remote_resource_destroy_lite_resource()
{
	if (g_lite_light_resource) {
		iotcon_lite_resource_destroy(g_lite_light_resource);
		g_lite_light_resource = NULL;
	}
}

static void _remote_resource_request_handler(iotcon_resource_h resource,
		iotcon_request_h request, void *user_data)
{
	FN_CALL;
	int ret;
	int observe_id;
	static iotcon_observers_h observers;
	iotcon_observe_type_e observe_type;

	ret = iotcon_request_get_observe_type(request, &observe_type);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_request_get_observe_type() Fail(%d)", ret);
		_remote_resource_main_loop_quit(false);
		return;
	}

	switch (observe_type) {
	case IOTCON_OBSERVE_NO_TYPE:
		break;
	case IOTCON_OBSERVE_REGISTER:
		ICUTC_INFO("IOTCON_OBSERVE_REGISTER");
		ret = iotcon_request_get_observe_id(request, &observe_id);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_request_get_observe_id() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return;
		}
		if (NULL == observers) {
			ret = iotcon_observers_create(&observers);
			if (IOTCON_ERROR_NONE != ret) {
				ICUTC_ERR("iotcon_observers_create() Fail(%d)", ret);
				_remote_resource_main_loop_quit(false);
				return;
			}
		}
		ret = iotcon_observers_add(observers, observe_id);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_observers_add() Fail(%d)", ret);
			iotcon_observers_destroy(observers);
			observers = NULL;
			_remote_resource_main_loop_quit(false);
			return;
		}
		break;
	case IOTCON_OBSERVE_DEREGISTER:
		ICUTC_INFO("IOTCON_OBSERVE_DEREGISTER");
		ret = iotcon_request_get_observe_id(request, &observe_id);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_request_get_observe_id() Fail(%d)", ret);
			iotcon_observers_destroy(observers);
			observers = NULL;
			_remote_resource_main_loop_quit(false);
			return;
		}
		ret = iotcon_observers_remove(observers, observe_id);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_observers_remove() Fail(%d)", ret);
			iotcon_observers_destroy(observers);
			observers = NULL;
			_remote_resource_main_loop_quit(false);
			return;
		}

		iotcon_observers_destroy(observers);
		observers = NULL;

		_remote_resource_main_loop_quit(true);
		return;
	}

	ret = icutc_send_ok_response(request);
	if (0 != ret) {
		ICUTC_ERR("icutc_send_ok_response() Fail(%d)", ret);
		_remote_resource_main_loop_quit(false);
		return;
	}
}

static int _remote_resource_create_resource(int tc_index)
{
	int ret;
	iotcon_resource_types_h light_types;
	iotcon_resource_interfaces_h light_ifaces;

	_remote_resource_destroy_resource();

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
			_remote_resource_request_handler,
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

static int _remote_resource_create_lite_resource()
{
	int ret;
	iotcon_attributes_h attributes = NULL;
	iotcon_resource_types_h light_types;

	ret = iotcon_resource_types_create(&light_types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_add(light_types, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(light_types);
		return 1;
	}

	ret = icutc_create_attributes(&attributes);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_attributes() Fail(%d)", ret);
		iotcon_resource_types_destroy(light_types);
		return 1;
	}

	ret = iotcon_lite_resource_create(LIGHT_RESOURCE_URI,
			light_types,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			attributes,
			NULL,
			NULL,
			&g_lite_light_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_create() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		iotcon_resource_types_destroy(light_types);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	iotcon_resource_types_destroy(light_types);

	return 0;
}


static int _remote_resource_get_uri_path_n(iotcon_remote_resource_h resource)
{
	int ret;
	char *uri_path;

	ret = iotcon_remote_resource_get_uri_path(NULL, &uri_path);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_remote_resource_get_uri_path(resource, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _remote_resource_get_uri_path_p(iotcon_remote_resource_h resource)
{
	int ret;
	char *uri_path;

	ret = iotcon_remote_resource_get_uri_path(resource, &uri_path);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _remote_resource_get_host_address_n(iotcon_remote_resource_h resource)
{
	int ret;
	char *host_address;

	ret = iotcon_remote_resource_get_host_address(NULL, &host_address);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_remote_resource_get_host_address(resource, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _remote_resource_get_host_address_p(iotcon_remote_resource_h resource)
{
	int ret;
	char *host_address;

	ret = iotcon_remote_resource_get_host_address(resource, &host_address);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _remote_resource_get_connectivity_type_n(iotcon_remote_resource_h resource)
{
	int ret;
	iotcon_connectivity_type_e connectivity_type;

	ret = iotcon_remote_resource_get_connectivity_type(NULL, &connectivity_type);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_remote_resource_get_connectivity_type(resource, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _remote_resource_get_connectivity_type_p(iotcon_remote_resource_h resource)
{
	int ret;
	iotcon_connectivity_type_e connectivity_type;

	ret = iotcon_remote_resource_get_connectivity_type(resource, &connectivity_type);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _remote_resource_get_device_id_n(iotcon_remote_resource_h resource)
{
	int ret;
	char *device_id;

	ret = iotcon_remote_resource_get_device_id(NULL, &device_id);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_remote_resource_get_device_id(resource, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _remote_resource_get_device_id_p(iotcon_remote_resource_h resource)
{
	int ret;
	char *device_id;

	ret = iotcon_remote_resource_get_device_id(resource, &device_id);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _remote_resource_get_device_name_n(iotcon_remote_resource_h resource)
{
	int ret;
	char *device_name;

	ret = iotcon_remote_resource_get_device_name(NULL, &device_name);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_remote_resource_get_device_name(resource, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _remote_resource_get_device_name_p(iotcon_remote_resource_h resource)
{
	int ret;
	char *device_name;

	ret = iotcon_remote_resource_get_device_name(resource, &device_name);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _remote_resource_get_types_n(iotcon_remote_resource_h resource)
{
	int ret;
	iotcon_resource_types_h types;

	ret = iotcon_remote_resource_get_types(NULL, &types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_remote_resource_get_types(resource, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _remote_resource_get_types_p(iotcon_remote_resource_h resource)
{
	int ret;
	iotcon_resource_types_h types;

	ret = iotcon_remote_resource_get_types(resource, &types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _remote_resource_get_interfaces_n(iotcon_remote_resource_h resource)
{
	int ret;
	iotcon_resource_interfaces_h ifaces;

	ret = iotcon_remote_resource_get_interfaces(NULL, &ifaces);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_remote_resource_get_interfaces(resource, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _remote_resource_get_interfaces_p(iotcon_remote_resource_h resource)
{
	int ret;
	iotcon_resource_interfaces_h ifaces;

	ret = iotcon_remote_resource_get_interfaces(resource, &ifaces);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _remote_resource_get_options_n(iotcon_remote_resource_h resource)
{
	int ret;
	iotcon_options_h options;

	ret = iotcon_remote_resource_get_options(NULL, &options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_remote_resource_get_options(resource, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _remote_resource_get_options_p(iotcon_remote_resource_h resource)
{
	int ret;
	iotcon_options_h options;

	ret = iotcon_remote_resource_get_options(resource, &options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _remote_resource_get_policies_n(iotcon_remote_resource_h resource)
{
	int ret;
	uint8_t policies;

	ret = iotcon_remote_resource_get_policies(NULL, &policies);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_remote_resource_get_policies(resource, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _remote_resource_get_policies_p(iotcon_remote_resource_h resource)
{
	int ret;
	uint8_t policies;

	ret = iotcon_remote_resource_get_policies(resource, &policies);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

static int _remote_resource_set_options_n(iotcon_remote_resource_h resource)
{
	int ret;
	iotcon_options_h options;

	ret = iotcon_options_create(&options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_remote_resource_set_options(NULL, options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	iotcon_options_destroy(options);

	return 0;
}

static int _remote_resource_set_options_p(iotcon_remote_resource_h resource)
{
	int ret;
	iotcon_options_h options;

	ret = iotcon_options_create(&options);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_remote_resource_set_options(resource, options);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_set_options() Fail(%d)", ret);
		iotcon_options_destroy(options);
		return 1;
	}
	iotcon_options_destroy(options);

	return 0;
}

static void _remote_resource_on_delete(iotcon_remote_resource_h resource,
		iotcon_error_e err,
		iotcon_request_type_e request_type,
		iotcon_response_h response,
		void *user_data)
{
	FN_CALL;
	int ret;

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX) {
		g_timeout_count++;
		ret = iotcon_remote_resource_delete(g_remote_resource, _remote_resource_on_delete, user_data);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_delete() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return;
		}
		return;
	} else if (IOTCON_ERROR_NONE != err) {
		ICUTC_ERR("iotcon_remote_resource_delete() Fail(%d)", err);
		_remote_resource_main_loop_quit(false);
		return;
	}
	_remote_resource_main_loop_quit(true);
}

static void _remote_resource_on_post(iotcon_remote_resource_h resource,
		iotcon_error_e err,
		iotcon_request_type_e request_type,
		iotcon_response_h response,
		void *user_data)
{
	FN_CALL;
	int ret;

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX) {
		g_timeout_count++;
		iotcon_representation_h repr;
		ret = icutc_create_representation(&repr);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("icutc_create_representation() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return;
		}
		ret = iotcon_remote_resource_post(g_remote_resource, repr, NULL,
				_remote_resource_on_post, user_data);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_get() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			_remote_resource_main_loop_quit(false);
			return;
		}
		iotcon_representation_destroy(repr);
		return;
	} else if (IOTCON_ERROR_NONE != err) {
		ICUTC_ERR("iotcon_remote_resource_post() Fail(%d)", err);
		_remote_resource_main_loop_quit(false);
		return;
	}
	_remote_resource_main_loop_quit(true);
}

static void _remote_resource_on_put(iotcon_remote_resource_h resource,
		iotcon_error_e err,
		iotcon_request_type_e request_type,
		iotcon_response_h response,
		void *user_data)
{
	FN_CALL;
	int ret;

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX) {
		g_timeout_count++;
		iotcon_representation_h repr, child_repr;
		ret = icutc_create_representation(&repr);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("icutc_create_representation() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return;
		}

		ret = icutc_create_representation(&child_repr);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("icutc_create_representation() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			_remote_resource_main_loop_quit(false);
			return;
		}

		ret = iotcon_representation_add_child(repr, child_repr);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
			iotcon_representation_destroy(child_repr);
			iotcon_representation_destroy(repr);
			_remote_resource_main_loop_quit(false);
			return;
		}
		iotcon_representation_destroy(child_repr);

		ret = iotcon_remote_resource_put(g_remote_resource, repr, NULL,
				_remote_resource_on_put, user_data);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_get() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			_remote_resource_main_loop_quit(false);
			return;
		}
		iotcon_representation_destroy(repr);
		return;
	} else if (IOTCON_ERROR_NONE != err) {
		ICUTC_ERR("iotcon_remote_resource_put() Fail(%d)", err);
		_remote_resource_main_loop_quit(false);
		return;
	}
	_remote_resource_main_loop_quit(true);
}


static void _remote_resource_on_get(iotcon_remote_resource_h resource,
		iotcon_error_e err,
		iotcon_request_type_e request_type,
		iotcon_response_h response,
		void *user_data)
{
	FN_CALL;
	int ret;

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX) {
		g_timeout_count++;
		ret = iotcon_remote_resource_get(g_remote_resource, NULL, _remote_resource_on_get, user_data);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_get() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return;
		}
		return;
	} else if (IOTCON_ERROR_NONE != err) {
		ICUTC_ERR("iotcon_remote_resource_get() Fail(%d)", err);
		_remote_resource_main_loop_quit(false);
		return;
	}
	_remote_resource_main_loop_quit(true);
}


static void _remote_resource_on_observe(iotcon_remote_resource_h resource,
		iotcon_error_e err, int sequence_number, iotcon_response_h response, void *user_data)
{
	FN_CALL;
	int ret;

	ret = iotcon_remote_resource_observe_deregister(resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_observe_deregister() Fail(%d)", ret);
		_remote_resource_main_loop_quit(false);
		return;
	}
}

static int _remote_resource_get_n(iotcon_remote_resource_h resource)
{
	int ret;

	/* cb is NULL */
	ret = iotcon_remote_resource_get(resource, NULL, NULL, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	/* remote_resource is NULL */
	ret = iotcon_remote_resource_get(NULL, NULL, _remote_resource_on_get, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _remote_resource_put_n(iotcon_remote_resource_h resource)
{
	int ret;
	iotcon_representation_h repr;

	ret = icutc_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	/* repr is NULL */
	ret = iotcon_remote_resource_put(resource, NULL, NULL, _remote_resource_on_put, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	/* cb is NULL */
	ret = iotcon_remote_resource_put(resource, repr, NULL, NULL, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	/* remote_resource is NULL */
	ret = iotcon_remote_resource_put(NULL, repr, NULL, _remote_resource_on_put, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	iotcon_representation_destroy(repr);

	return 0;
}

static int _remote_resource_post_n(iotcon_remote_resource_h resource)
{
	int ret;
	iotcon_representation_h repr;

	ret = icutc_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	/* repr is NULL */
	ret = iotcon_remote_resource_post(resource, NULL, NULL, _remote_resource_on_post, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	/* cb is NULL */
	ret = iotcon_remote_resource_post(resource, repr, NULL, NULL, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	/* remote_resource is NULL */
	ret = iotcon_remote_resource_post(NULL, repr, NULL, _remote_resource_on_post, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	iotcon_representation_destroy(repr);
	return 0;
}

static int _remote_resource_delete_n(iotcon_remote_resource_h resource)
{
	int ret;

	/* cb is NULL */
	ret = iotcon_remote_resource_delete(resource, NULL, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	/* remote_resource is NULL */
	ret = iotcon_remote_resource_delete(NULL,  _remote_resource_on_delete, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _remote_resource_observe_register_n(iotcon_remote_resource_h resource)
{
	int ret;

	/* cb is NULL */
	ret = iotcon_remote_resource_observe_register(resource,
			IOTCON_OBSERVE_IGNORE_OUT_OF_ORDER, NULL, NULL, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	/* remote_resource is NULL */
	ret = iotcon_remote_resource_observe_register(NULL,
			IOTCON_OBSERVE_IGNORE_OUT_OF_ORDER, NULL, _remote_resource_on_observe, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _remote_resource_observe_deregister_n(iotcon_remote_resource_h resource)
{
	int ret;

	/* remote_resource is NULL */
	ret = iotcon_remote_resource_observe_deregister(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	/* without register */
	ret = iotcon_remote_resource_observe_deregister(resource);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

static bool _remote_resource_found_resource(iotcon_remote_resource_h resource,
		iotcon_error_e err, void *user_data)
{
	FN_CALL;
	int ret;
	int tc_index = (int)user_data;
	iotcon_representation_h repr;
	iotcon_options_h options;
	iotcon_query_h query;
	char *host_address;

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX) {
		g_timeout_count++;
		ret = iotcon_query_create(&query);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_create() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_query_set_resource_type(query, LIGHT_RESOURCE_TYPE);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_set_resource_type() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY,
				query, _remote_resource_found_resource, user_data);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_find_resource() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_query_destroy(query);
		return IOTCON_FUNC_STOP;
	} else if (IOTCON_ERROR_NONE != err) {
		_remote_resource_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	if (g_found)
		return IOTCON_FUNC_STOP;
	g_found = true;

	ret = iotcon_remote_resource_get_host_address(resource, &host_address);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_get_host_address() Fail(%d)", ret);
		_remote_resource_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	ICUTC_INFO("expected host_address[%s], found host_address[%s]", g_ipv4_address, host_address);

	if (strstr(host_address, g_ipv4_address) == NULL) { // targeted resource, BUT wrong device, so skip this resource and try again
		g_found = false;
		return IOTCON_FUNC_CONTINUE;
	}

	ret = iotcon_options_create(&options);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_create() Fail(%d)", ret);
		_remote_resource_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}
	ret = iotcon_options_add(options, 2500, "options_value");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_add() Fail(%d)", ret);
		iotcon_options_destroy(options);
		_remote_resource_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	ret = iotcon_remote_resource_set_options(resource, options);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_set_options() Fail(%d)", ret);
		iotcon_options_destroy(options);
		_remote_resource_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}
	iotcon_options_destroy(options);

	switch (tc_index) {
	case REMOTE_RESOURCE_GET_N:
		ret = _remote_resource_get_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_PUT_N:
		ret = _remote_resource_put_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_put_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_POST_N:
		ret = _remote_resource_post_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_post_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_DELETE_N:
		ret = _remote_resource_delete_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_delete_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_OBSERVE_REGISTER_N:
		ret = _remote_resource_observe_register_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_observe_register_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_OBSERVE_DEREGISTER_N:
		ret = _remote_resource_observe_deregister_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_observe_deregister_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_P:
		ret = iotcon_remote_resource_clone(resource, &g_remote_resource);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_clone() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_query_create(&query);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_create() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_query_add(query, "key", "value");
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_add() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_remote_resource_get(g_remote_resource, query,
				_remote_resource_on_get, (void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_get() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_query_destroy(query);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_PUT_P:
		ret = iotcon_remote_resource_clone(resource, &g_remote_resource);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_clone() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = icutc_create_representation(&repr);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("icutc_create_representation() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_remote_resource_put(g_remote_resource, repr, NULL,
				_remote_resource_on_put, (void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_get() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_representation_destroy(repr);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_POST_P:
		ret = iotcon_remote_resource_clone(resource, &g_remote_resource);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_clone() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = icutc_create_representation(&repr);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("icutc_create_representation() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_remote_resource_post(g_remote_resource, repr, NULL,
				_remote_resource_on_post, (void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_post() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_representation_destroy(repr);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_DELETE_P:
		ret = iotcon_remote_resource_clone(resource, &g_remote_resource);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_clone() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_remote_resource_delete(g_remote_resource, _remote_resource_on_delete,
				(void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_delete() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_OBSERVE_REGISTER_P:
	case REMOTE_RESOURCE_OBSERVE_DEREGISTER_P:
		ret = iotcon_remote_resource_clone(resource, &g_remote_resource);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_clone() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_remote_resource_observe_register(g_remote_resource,
				IOTCON_OBSERVE_IGNORE_OUT_OF_ORDER, NULL, _remote_resource_on_observe, (void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_observe_register() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_URI_PATH_N:
		ret = _remote_resource_get_uri_path_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_uri_path_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_URI_PATH_P:
		ret = _remote_resource_get_uri_path_p(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_uri_path_p() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_HOST_ADDRESS_N:
		ret = _remote_resource_get_host_address_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_host_address_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_HOST_ADDRESS_P:
		ret = _remote_resource_get_host_address_p(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_host_address_p() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_CONNECTIVITY_TYPE_N:
		ret = _remote_resource_get_connectivity_type_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_connectivity_type_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_CONNECTIVITY_TYPE_P:
		ret = _remote_resource_get_connectivity_type_p(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_connectivity_type_p() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_DEVICE_ID_N:
		ret = _remote_resource_get_device_id_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_device_id_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_DEVICE_ID_P:
		ret = _remote_resource_get_device_id_p(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_device_id_p() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_DEVICE_NAME_N:
		ret = _remote_resource_get_device_name_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_device_name_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_DEVICE_NAME_P:
		ret = _remote_resource_get_device_name_p(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_device_name_p() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_TYPES_N:
		ret = _remote_resource_get_types_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_types_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_TYPES_P:
		ret = _remote_resource_get_types_p(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_types_p() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_INTERFACES_N:
		ret = _remote_resource_get_interfaces_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_interfaces_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_INTERFACES_P:
		ret = _remote_resource_get_interfaces_p(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_interfaces_p() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_OPTIONS_N:
		ret = _remote_resource_get_options_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_options_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_OPTIONS_P:
		ret = _remote_resource_get_options_p(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_options_p() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_PROPERTIES_N:
		ret = _remote_resource_get_policies_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_policies_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_GET_PROPERTIES_P:
		ret = _remote_resource_get_policies_p(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_get_policies_p() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_SET_OPTIONS_N:
		ret = _remote_resource_set_options_n(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_set_options_n() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case REMOTE_RESOURCE_SET_OPTIONS_P:
		ret = _remote_resource_set_options_p(resource);
		if (0 != ret) {
			ICUTC_ERR("_remote_resource_set_options_p() Fail(%d)", ret);
			_remote_resource_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_remote_resource_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	default:
		ICUTC_ERR("Invalid tc_index(%d)", tc_index);
		_remote_resource_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}
	return IOTCON_FUNC_STOP;
}

static int _remote_resource_handle_async(int tc_index)
{
	FN_CALL;
	int ret;
	iotcon_query_h query;

	g_loop = g_main_loop_new(NULL, FALSE);

	ret = _remote_resource_create_resource(tc_index);
	if (0 != ret) {
		ICUTC_ERR("_remote_resource_create_resource() Fail(%d)", ret);
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
			query, _remote_resource_found_resource, (void *)tc_index);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_find_resource() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}
	iotcon_query_destroy(query);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);

	_remote_resource_destroy_resource();

	if (true == g_result)
		return 0;
	else
		return 1;
}

static int _remote_resource_lite_handle_async(int tc_index)
{
	FN_CALL;
	int ret;
	iotcon_query_h query;

	g_loop = g_main_loop_new(NULL, FALSE);

	ret = _remote_resource_create_lite_resource();
	if (0 != ret) {
		ICUTC_ERR("_remote_resource_create_lite_resource() Fail(%d)", ret);
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
			query, _remote_resource_found_resource, (void *)tc_index);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_find_resource() Fail(%d)", ret);
		iotcon_query_destroy(query);
		return 1;
	}
	iotcon_query_destroy(query);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);

	_remote_resource_destroy_lite_resource();

	if (true == g_result)
		return 0;
	else
		return 1;
}

static int _remote_resource_create(iotcon_remote_resource_h *resource)
{
	int ret;
	iotcon_resource_types_h resource_types;
	iotcon_resource_interfaces_h resource_interfaces;
	iotcon_remote_resource_h remote_resource;

	ret = iotcon_resource_types_create(&resource_types);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_create() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_resource_types_add(resource_types, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_resource_interfaces_create(&resource_interfaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(resource_interfaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_remote_resource_create(LOCAL_HOST_ADDRESS,
			IOTCON_CONNECTIVITY_IP,
			LIGHT_RESOURCE_URI,
			IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE,
			resource_types,
			resource_interfaces,
			&remote_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	iotcon_resource_interfaces_destroy(resource_interfaces);
	iotcon_resource_types_destroy(resource_types);

	*resource = remote_resource;

	return 0;
}

/* ##################################################### */

/**
 * @function      utc_iotcon_remote_resource_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_remote_resource_startup(void)
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
 * @function      utc_iotcon_remote_resource_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_remote_resource_cleanup(void)
{
	icutc_free_client_ipv4_address();

	if (true == g_feature)
		iotcon_deinitialize();
}

/**
 * @testcase      utc_iotcon_remote_resource_create_n
 * @since_tizen   3.0
 * @description   Test fail creating a remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_create_n(void)
{
	int ret;
	iotcon_resource_types_h resource_types = NULL;
	iotcon_resource_interfaces_h resource_interfaces = NULL;
	iotcon_remote_resource_h remote_resource = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_create(NULL,
				IOTCON_CONNECTIVITY_IP,
				LIGHT_RESOURCE_URI,
				IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE,
				resource_types,
				resource_interfaces,
				&remote_resource);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_types_create(&resource_types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_add(resource_types, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_resource_interfaces_create(&resource_interfaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(resource_interfaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	/* Host address is NULL */
	ret = iotcon_remote_resource_create(NULL,
			IOTCON_CONNECTIVITY_IP,
			LIGHT_RESOURCE_URI,
			IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE,
			resource_types,
			resource_interfaces,
			&remote_resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_remote_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	/* uri_path is NULL */
	ret = iotcon_remote_resource_create(LOCAL_HOST_ADDRESS,
			IOTCON_CONNECTIVITY_IP,
			NULL,
			IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE,
			resource_types,
			resource_interfaces,
			&remote_resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_remote_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	/* resource_types is NULL */
	ret = iotcon_remote_resource_create(LOCAL_HOST_ADDRESS,
			IOTCON_CONNECTIVITY_IP,
			LIGHT_RESOURCE_URI,
			IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE,
			NULL,
			resource_interfaces,
			&remote_resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_remote_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	/* resource_interfaces is NULL */
	ret = iotcon_remote_resource_create(LOCAL_HOST_ADDRESS,
			IOTCON_CONNECTIVITY_IP,
			LIGHT_RESOURCE_URI,
			IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE,
			resource_types,
			NULL,
			&remote_resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_remote_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	/* out parameter is NULL */
	ret = iotcon_remote_resource_create(LOCAL_HOST_ADDRESS,
			IOTCON_CONNECTIVITY_IP,
			LIGHT_RESOURCE_URI,
			IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE,
			resource_types,
			resource_interfaces,
			NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_remote_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	iotcon_resource_interfaces_destroy(resource_interfaces);
	iotcon_resource_types_destroy(resource_types);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_create_p
 * @since_tizen   3.0
 * @description   Test creating a remote resource.
 */
int utc_iotcon_remote_resource_create_p(void)
{
	int ret;
	iotcon_resource_types_h resource_types = NULL;
	iotcon_resource_interfaces_h resource_interfaces = NULL;
	iotcon_remote_resource_h remote_resource;

	if (false == g_feature) {
		ret = iotcon_remote_resource_create(NULL,
				IOTCON_CONNECTIVITY_IP,
				LIGHT_RESOURCE_URI,
				IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE,
				resource_types,
				resource_interfaces,
				&remote_resource);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_create(&remote_resource);
	if (0 != ret) {
		ICUTC_ERR("_remote_resource_create() Fail(%d)", ret);
		return 1;
	}
	iotcon_remote_resource_destroy(remote_resource);

	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_destroy_n
 * @since_tizen   3.0
 * @description   Test fail destroying a remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_destroy_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_destroy(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_remote_resource_destroy(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_destroy_p
 * @since_tizen   3.0
 * @description   Test destroying a remote resource.
 */
int utc_iotcon_remote_resource_destroy_p(void)
{
	int ret;
	iotcon_resource_types_h resource_types;
	iotcon_resource_interfaces_h resource_interfaces;
	iotcon_remote_resource_h remote_resource = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_destroy(remote_resource);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_types_create(&resource_types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_add(resource_types, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_resource_interfaces_create(&resource_interfaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(resource_interfaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_remote_resource_create(LOCAL_HOST_ADDRESS,
			IOTCON_CONNECTIVITY_IP,
			LIGHT_RESOURCE_URI,
			IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE,
			resource_types,
			resource_interfaces,
			&remote_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(resource_types);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		return 1;
	}

	iotcon_resource_types_destroy(resource_types);
	iotcon_resource_interfaces_destroy(resource_interfaces);

	ret = iotcon_remote_resource_destroy(remote_resource);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_clone_n
 * @since_tizen   3.0
 * @description   Test fail cloning a remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_clone_n(void)
{
	int ret;
	iotcon_resource_types_h resource_types;
	iotcon_resource_interfaces_h resource_interfaces;
	iotcon_remote_resource_h remote_resource;
	iotcon_remote_resource_h cloned;

	if (false == g_feature) {
		ret = iotcon_remote_resource_clone(NULL, &cloned);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_types_create(&resource_types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_add(resource_types, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_resource_interfaces_create(&resource_interfaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(resource_interfaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_remote_resource_create(LOCAL_HOST_ADDRESS,
			IOTCON_CONNECTIVITY_IP,
			LIGHT_RESOURCE_URI,
			IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE,
			resource_types,
			resource_interfaces,
			&remote_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_remote_resource_clone(remote_resource, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_remote_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		iotcon_remote_resource_destroy(remote_resource);
		return 1;
	}

	ret = iotcon_remote_resource_clone(NULL, &cloned);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_remote_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		iotcon_remote_resource_destroy(remote_resource);
		return 1;
	}

	iotcon_resource_interfaces_destroy(resource_interfaces);
	iotcon_resource_types_destroy(resource_types);
	iotcon_remote_resource_destroy(remote_resource);

	return 0;

}

/**
 * @testcase      utc_iotcon_remote_resource_clone_p
 * @since_tizen   3.0
 * @description   Test cloning a remote resource.
 */
int utc_iotcon_remote_resource_clone_p(void)
{
	int ret;
	iotcon_resource_types_h resource_types;
	iotcon_resource_interfaces_h resource_interfaces;
	iotcon_remote_resource_h remote_resource;
	iotcon_remote_resource_h cloned;

	if (false == g_feature) {
		ret = iotcon_remote_resource_clone(NULL, &cloned);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_types_create(&resource_types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_add(resource_types, LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_resource_interfaces_create(&resource_interfaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(resource_interfaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_remote_resource_create(LOCAL_HOST_ADDRESS,
			IOTCON_CONNECTIVITY_IP,
			LIGHT_RESOURCE_URI,
			IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE,
			resource_types,
			resource_interfaces,
			&remote_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		return 1;
	}

	ret = iotcon_remote_resource_clone(remote_resource, &cloned);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(resource_interfaces);
		iotcon_resource_types_destroy(resource_types);
		iotcon_remote_resource_destroy(remote_resource);
		return 1;
	}

	iotcon_resource_interfaces_destroy(resource_interfaces);
	iotcon_resource_types_destroy(resource_types);
	iotcon_remote_resource_destroy(remote_resource);
	iotcon_remote_resource_destroy(cloned);

	return 0;

}

/**
 * @testcase      utc_iotcon_remote_resource_get_n
 * @since_tizen   3.0
 * @description   Test fail sending get request to remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_get_n(void)
{
	int ret;
	iotcon_remote_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get(resource, NULL, NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_p
 * @since_tizen   3.0
 * @description   Test sending get request to remote resource.
 */
int utc_iotcon_remote_resource_get_p(void)
{
	int ret;
	iotcon_remote_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get(resource, NULL, NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_put_n
 * @since_tizen   3.0
 * @description   Test fail sending put request to remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_put_n(void)
{
	int ret;
	iotcon_remote_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_put(resource, NULL, NULL, _remote_resource_on_put, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_PUT_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_put_p
 * @since_tizen   3.0
 * @description   Test sending put request to remote resource.
 */
int utc_iotcon_remote_resource_put_p(void)
{
	int ret;
	iotcon_remote_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_put(resource, NULL, NULL, _remote_resource_on_put, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_PUT_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_post_n
 * @since_tizen   3.0
 * @description   Test fail sending post request to remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_post_n(void)
{
	int ret;
	iotcon_remote_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_post(resource, NULL, NULL, _remote_resource_on_post, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_POST_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_post_p
 * @since_tizen   3.0
 * @description   Test sending post request to remote resource.
 */
int utc_iotcon_remote_resource_post_p(void)
{
	int ret;
	iotcon_remote_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_post(resource, NULL, NULL, _remote_resource_on_post, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_POST_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_post_p2
 * @since_tizen   3.0
 * @description   Test sending post request to remote lite resource.
 */
int utc_iotcon_remote_resource_post_p2(void)
{
	int ret;
	iotcon_remote_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_post(resource, NULL, NULL, _remote_resource_on_post, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_lite_handle_async(REMOTE_RESOURCE_POST_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_delete_n
 * @since_tizen   3.0
 * @description   Test fail sending delete request to remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_delete_n(void)
{
	int ret;
	iotcon_remote_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_delete(resource, NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_DELETE_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_delete_p
 * @since_tizen   3.0
 * @description   Test sending delete request to remote resource.
 */
int utc_iotcon_remote_resource_delete_p(void)
{
	int ret;
	iotcon_remote_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_delete(resource, NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_DELETE_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_observe_register_n
 * @since_tizen   3.0
 * @description   Test fail registering observe to remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_observe_register_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_observe_register(NULL,
				IOTCON_OBSERVE_IGNORE_OUT_OF_ORDER, NULL, _remote_resource_on_observe, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_OBSERVE_REGISTER_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_observe_register_p
 * @since_tizen   3.0
 * @description   Test registering observe to remote resource.
 */
int utc_iotcon_remote_resource_observe_register_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_observe_register(NULL,
				IOTCON_OBSERVE_IGNORE_OUT_OF_ORDER, NULL, _remote_resource_on_observe, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_OBSERVE_REGISTER_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_observe_deregister_n
 * @since_tizen   3.0
 * @description   Test fail deregistering observe to remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_observe_deregister_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_observe_deregister(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_OBSERVE_DEREGISTER_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_observe_deregister_p
 * @since_tizen   3.0
 * @description   Test deregistering observe to remote resource.
 */
int utc_iotcon_remote_resource_observe_deregister_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_observe_deregister(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_OBSERVE_DEREGISTER_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_uri_path_n
 * @since_tizen   3.0
 * @description   Test fail getting uri path from remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_get_uri_path_n(void)
{
	int ret;
	char *uri_path;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_uri_path(NULL, &uri_path);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_URI_PATH_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_uri_path_p
 * @since_tizen   3.0
 * @description   Test getting uri path from remote resource.
 */
int utc_iotcon_remote_resource_get_uri_path_p(void)
{
	int ret;
	char *uri_path;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_uri_path(NULL, &uri_path);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_URI_PATH_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_host_address_n
 * @since_tizen   3.0
 * @description   Test fail getting host address from remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_get_host_address_n(void)
{
	int ret;
	char *host_address;;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_host_address(NULL, &host_address);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_HOST_ADDRESS_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_host_address_p
 * @since_tizen   3.0
 * @description   Test getting host address from remote resource.
 */
int utc_iotcon_remote_resource_get_host_address_p(void)
{
	int ret;
	char *host_address;;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_host_address(NULL, &host_address);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_HOST_ADDRESS_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}


/**
 * @testcase      utc_iotcon_remote_resource_get_connectivity_type_n
 * @since_tizen   3.0
 * @description   Test fail getting connectivity type from remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_get_connectivity_type_n(void)
{
	int ret;
	iotcon_connectivity_type_e connectivity_type;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_connectivity_type(NULL, &connectivity_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_CONNECTIVITY_TYPE_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_connectivity_type_p
 * @since_tizen   3.0
 * @description   Test getting connectivity type from remote resource.
 */
int utc_iotcon_remote_resource_get_connectivity_type_p(void)
{
	int ret;
	iotcon_connectivity_type_e connectivity_type;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_connectivity_type(NULL, &connectivity_type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_CONNECTIVITY_TYPE_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}


/**
 * @testcase      utc_iotcon_remote_resource_get_device_id_n
 * @since_tizen   3.0
 * @description   Test fail getting device id from remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_get_device_id_n(void)
{
	int ret;
	char *device_id;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_device_id(NULL, &device_id);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_DEVICE_ID_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_device_id_p
 * @since_tizen   3.0
 * @description   Test getting device id from remote resource.
 */
int utc_iotcon_remote_resource_get_device_id_p(void)
{
	int ret;
	char *device_id;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_device_id(NULL, &device_id);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_DEVICE_ID_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}


/**
 * @testcase      utc_iotcon_remote_resource_get_device_name_n
 * @since_tizen   3.0
 * @description   Test fail getting device name from remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_get_device_name_n(void)
{
	int ret;
	char *device_name;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_device_name(NULL, &device_name);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_DEVICE_NAME_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_device_name_p
 * @since_tizen   3.0
 * @description   Test getting device name from remote resource.
 */
int utc_iotcon_remote_resource_get_device_name_p(void)
{
	int ret;
	char *device_name;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_device_name(NULL, &device_name);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_DEVICE_NAME_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}


/**
 * @testcase      utc_iotcon_remote_resource_get_types_n
 * @since_tizen   3.0
 * @description   Test fail getting types from remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_get_types_n(void)
{
	int ret;
	iotcon_resource_types_h types;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_types(NULL, &types);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_TYPES_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;

}

/**
 * @testcase      utc_iotcon_remote_resource_get_types_p
 * @since_tizen   3.0
 * @description   Test getting types from remote resource.
 */
int utc_iotcon_remote_resource_get_types_p(void)
{
	int ret;
	iotcon_resource_types_h types;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_types(NULL, &types);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_TYPES_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_interfaces_n
 * @since_tizen   3.0
 * @description   Test fail getting interfaces from remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_get_interfaces_n(void)
{
	int ret;
	iotcon_resource_interfaces_h ifaces;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_interfaces(NULL, &ifaces);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_INTERFACES_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_interfaces_p
 * @since_tizen   3.0
 * @description   Test getting interfaces from remote resource.
 */
int utc_iotcon_remote_resource_get_interfaces_p(void)
{
	int ret;
	iotcon_resource_interfaces_h ifaces;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_interfaces(NULL, &ifaces);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_INTERFACES_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_options_n
 * @since_tizen   3.0
 * @description   Test fail getting options from remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_get_options_n(void)
{
	int ret;
	iotcon_options_h options;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_options(NULL, &options);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_OPTIONS_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_options_p
 * @since_tizen   3.0
 * @description   Test getting options from remote resource.
 */
int utc_iotcon_remote_resource_get_options_p(void)
{
	int ret;
	iotcon_options_h options;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_options(NULL, &options);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_OPTIONS_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}


/**
 * @testcase      utc_iotcon_remote_resource_get_policies_n
 * @since_tizen   3.0
 * @description   Test fail getting policies from remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_get_policies_n(void)
{
	int ret;
	uint8_t policies;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_policies(NULL, &policies);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_PROPERTIES_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}


/**
 * @testcase      utc_iotcon_remote_resource_get_policies_p
 * @since_tizen   3.0
 * @description   Test getting policies from remote resource.
 */
int utc_iotcon_remote_resource_get_policies_p(void)
{
	int ret;
	uint8_t policies;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_policies(NULL, &policies);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_GET_PROPERTIES_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_set_options_n
 * @since_tizen   3.0
 * @description   Test fail setting options to remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_set_options_n(void)
{
	int ret;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_set_options(NULL, options);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_SET_OPTIONS_N);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_set_options_p
 * @since_tizen   3.0
 * @description   Test setting options to remote resource.
 */
int utc_iotcon_remote_resource_set_options_p(void)
{
	int ret;
	iotcon_options_h options = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_set_options(NULL, options);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_handle_async(REMOTE_RESOURCE_SET_OPTIONS_P);
	ICUTC_ASSERT_EQ(ret, 0);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_checking_interval_p
 * @since_tizen   3.0
 * @description   Test getting checking interval of remote resource.
 */
int utc_iotcon_remote_resource_get_checking_interval_p(void)
{
	int ret;
	int checking_interval = 0;
	iotcon_remote_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_checking_interval(resource, &checking_interval);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_create(&resource);
	if (0 != ret) {
		ICUTC_ERR("_remote_resource_create() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_remote_resource_get_checking_interval(resource, &checking_interval);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_get_checking_interval() Fail(%d)", ret);
		iotcon_remote_resource_destroy(resource);
		return 1;
	}

	iotcon_remote_resource_destroy(resource);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_checking_interval_n
 * @since_tizen   3.0
 * @description   Test fail getting checking interval of remote resource.
 */
int utc_iotcon_remote_resource_get_checking_interval_n(void)
{
	int ret;
	int checking_interval;
	iotcon_remote_resource_h resource;

	if (false == g_feature) {
		ret = iotcon_remote_resource_get_checking_interval(NULL, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_remote_resource_get_checking_interval(NULL, &checking_interval);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = _remote_resource_create(&resource);
	if (0 != ret) {
		ICUTC_ERR("_remote_resource_create() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_remote_resource_get_checking_interval(resource, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_remote_resource_get_checking_interval() Fail(%d)", ret);
		iotcon_remote_resource_destroy(resource);
		return 1;
	}

	iotcon_remote_resource_destroy(resource);

	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_set_checking_interval_p
 * @since_tizen   3.0
 * @description   Test setting checking interval of remote resource.
 */
int utc_iotcon_remote_resource_set_checking_interval_p(void)
{
	int ret;
	iotcon_remote_resource_h resource = NULL;

	if (false == g_feature) {
		ret = iotcon_remote_resource_set_checking_interval(resource,
				ICUTC_REMOTE_RESOURCE_TIME_INTERVAL_MAX);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _remote_resource_create(&resource);
	if (0 != ret) {
		ICUTC_ERR("_remote_resource_create() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_remote_resource_set_checking_interval(resource,
			ICUTC_REMOTE_RESOURCE_TIME_INTERVAL_MAX);

	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_set_checking_interval() Fail(%d)", ret);
		iotcon_remote_resource_destroy(resource);
		return 1;
	}

	iotcon_remote_resource_destroy(resource);
	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_set_checking_interval_n
 * @since_tizen   3.0
 * @description   Test fail setting checking interval of remote resource.
 */
int utc_iotcon_remote_resource_set_checking_interval_n(void)
{
	int ret;
	iotcon_remote_resource_h resource;

	if (false == g_feature) {
		ret = iotcon_remote_resource_set_checking_interval(NULL, -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_remote_resource_set_checking_interval(NULL, 10);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = _remote_resource_create(&resource);
	if (0 != ret) {
		ICUTC_ERR("_remote_resource_create() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_remote_resource_set_checking_interval(resource, -1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_remote_resource_set_checking_interval() Fail(%d)", ret);
		iotcon_remote_resource_destroy(resource);
		return 1;
	}

	ret = iotcon_remote_resource_set_checking_interval(resource,
			ICUTC_REMOTE_RESOURCE_TIME_INTERVAL_MAX + 1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_remote_resource_set_checking_interval() Fail(%d)", ret);
		iotcon_remote_resource_destroy(resource);
		return 1;
	}

	iotcon_remote_resource_destroy(resource);
	return 0;
}

