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
	ENCAP_START_CACHING_N,
	ENCAP_START_CACHING_P,
	ENCAP_STOP_CACHING_N,
	ENCAP_STOP_CACHING_P,
	ENCAP_START_MONITORING_N,
	ENCAP_START_MONITORING_P,
	ENCAP_STOP_MONITORING_N,
	ENCAP_STOP_MONITORING_P,
	ENCAP_GET_CACHED_REPR_N,
	ENCAP_GET_CACHED_REPR_P,
};

#define ENCAP_LIGHT_RESOURCE_TYPE "core.light"
#define ENCAP_LIGHT_RESOURCE_URI "/a/light"

static bool g_found;
static int g_timeout_count;
static bool g_result;
static bool g_feature;
static GMainLoop *g_loop;
static int g_brightness = 1;
static iotcon_remote_resource_h g_remote_resource = NULL;

/* ### server side ### */
static iotcon_lite_resource_h g_lite_light_resource;

static gboolean _encap_main_loop_quit_idle(gpointer p)
{
	FN_CALL;
	g_main_loop_quit(g_loop);
	return G_SOURCE_REMOVE;
}

static void _encap_main_loop_quit(bool result)
{
	ICUTC_INFO("result = %d", result);
	g_result = result;
	g_idle_add(_encap_main_loop_quit_idle, NULL);
}

static void _encap_destroy_lite_resource()
{
	FN_CALL;
	if (g_lite_light_resource) {
		iotcon_lite_resource_destroy(g_lite_light_resource);
		g_lite_light_resource = NULL;
	}
}

static int _encap_create_lite_resource()
{
	FN_CALL;
	int ret;
	iotcon_attributes_h attributes = NULL;
	iotcon_resource_types_h types;

	ret = iotcon_resource_types_create(&types);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_create() Fail(%d)", ret);
		return ret;
	}

	ret = iotcon_resource_types_add(types, ENCAP_LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return ret;
	}

	ret = icutc_create_attributes(&attributes);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_attributes() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return ret;
	}

	/* register door resource */
	ret = iotcon_lite_resource_create(ENCAP_LIGHT_RESOURCE_URI,
			types,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			attributes,
			NULL,
			NULL,
			&g_lite_light_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_lite_resource_create() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		iotcon_resource_types_destroy(types);
		return ret;
	}

	iotcon_attributes_destroy(attributes);
	iotcon_resource_types_destroy(types);

	return 0;
}

static gboolean _update_lite_resource(gpointer p)
{
	FN_CALL;
	int ret;
	iotcon_attributes_h attributes = NULL;

	ret = icutc_create_attributes(&attributes);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_attributes() Fail(%d)", ret);
		_encap_main_loop_quit(false);
		return G_SOURCE_REMOVE;
	}

	ret = iotcon_attributes_add_bool(attributes, "bool", false);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_bool() Fail(%d)", ret);
		_encap_main_loop_quit(false);
		return G_SOURCE_REMOVE;
	}

	ret = iotcon_lite_resource_update_attributes(g_lite_light_resource, attributes);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_lite_resource_update_attributes() Fail(%d)", ret);
		_encap_main_loop_quit(false);
		return G_SOURCE_REMOVE;
	}
	iotcon_attributes_destroy(attributes);
	return G_SOURCE_REMOVE;
}

/* ### client side ### */
static void _encap_caching_cb(iotcon_remote_resource_h resource,
		iotcon_representation_h representation, void *user_data)
{
	FN_CALL;
	int ret;
	static int i = 0;
	int tc_index = (int)user_data;
	iotcon_representation_h repr = NULL;

	switch (tc_index) {
	case ENCAP_START_CACHING_P:
		ICUTC_INFO("Start caching!!(%d)", i);
		if (0 == i++) {
			g_timeout_add_seconds(3, _update_lite_resource, NULL);
			return;
		}
		iotcon_remote_resource_stop_caching(g_remote_resource);
		iotcon_remote_resource_destroy(g_remote_resource);
		_encap_main_loop_quit(true);
		return;
	case ENCAP_GET_CACHED_REPR_P:
		ret = iotcon_remote_resource_get_cached_representation(resource, &repr);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_get_cached_representation() Fail(%d)", ret);
			iotcon_remote_resource_stop_caching(g_remote_resource);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			break;
		}
		if (0 == i++)
			return;
		iotcon_remote_resource_stop_caching(g_remote_resource);
		iotcon_remote_resource_destroy(g_remote_resource);
		_encap_main_loop_quit(true);
		return;
	case ENCAP_GET_CACHED_REPR_N:
		ret = iotcon_remote_resource_get_cached_representation(NULL, &repr);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_remote_resource_get_cached_representation() Fail(%d)", ret);
			iotcon_remote_resource_stop_caching(g_remote_resource);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			break;
		}
		ret = iotcon_remote_resource_get_cached_representation(resource, NULL);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_remote_resource_get_cached_representation() Fail(%d)", ret);
			iotcon_remote_resource_stop_caching(g_remote_resource);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			break;
		}
		iotcon_remote_resource_stop_caching(g_remote_resource);
		iotcon_remote_resource_destroy(g_remote_resource);
		_encap_main_loop_quit(true);
		return;
	default:
		ICUTC_ERR("Invalid tc_index(%d)", tc_index);
		iotcon_remote_resource_stop_caching(g_remote_resource);
		iotcon_remote_resource_destroy(g_remote_resource);
		_encap_main_loop_quit(false);
		return;
	}
}

static void _encap_monitoring_cb(iotcon_remote_resource_h resource,
		iotcon_remote_resource_state_e state, void *user_data)
{
	FN_CALL;
	int ret;
	int tc_index = (int)user_data;

	if (ENCAP_STOP_MONITORING_P == tc_index) {
		ret = iotcon_remote_resource_stop_monitoring(g_remote_resource);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_stop_monitoring() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return;
		}
		iotcon_remote_resource_destroy(g_remote_resource);
		_encap_main_loop_quit(true);
	}
}

static gboolean _destroy_lite_light_resource(gpointer p)
{
	FN_CALL;
	int ret;

	ret = iotcon_lite_resource_destroy(g_lite_light_resource);
	if (IOTCON_ERROR_NONE != ret)
		ICUTC_ERR("iotcon_lite_resource_destroy() Fail(%d)", ret);

	g_lite_light_resource = NULL;

	return G_SOURCE_REMOVE;
}

static bool _encap_found_resource(iotcon_remote_resource_h resource,
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
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_query_set_resource_type(query, LIGHT_RESOURCE_TYPE);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_query_set_resource_type() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}

		ret = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY,
				query, _encap_found_resource, user_data);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_find_resource() Fail(%d)", ret);
			iotcon_query_destroy(query);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_query_destroy(query);

		return IOTCON_FUNC_STOP;
	} else if (IOTCON_ERROR_NONE != err) {
		_encap_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	if (g_found)
		return IOTCON_FUNC_STOP;
	g_found = true;

	ret = iotcon_remote_resource_get_host_address(resource, &host_address);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_get_host_address() Fail(%d)", ret);
		_encap_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	ICUTC_INFO("expected host_address[%s], found host_address[%s]", g_ipv4_address, host_address);

	if (strstr(host_address, g_ipv4_address) == NULL) { // targeted resource, BUT wrong device, so skip this resource and try again
		g_found = false;
		return IOTCON_FUNC_CONTINUE;
	}

	ret = iotcon_remote_resource_clone(resource, &g_remote_resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_remote_resource_clone() Fail(%d)", ret);
		_encap_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	switch (tc_index) {
	case ENCAP_START_CACHING_P:
		ret = iotcon_remote_resource_start_caching(g_remote_resource, _encap_caching_cb,
				(void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_start_caching() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		return IOTCON_FUNC_STOP;
	case ENCAP_STOP_CACHING_P:
		ret = iotcon_remote_resource_start_caching(g_remote_resource, _encap_caching_cb,
				(void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_start_caching() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_remote_resource_stop_caching(g_remote_resource);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_stop_caching() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_remote_resource_destroy(g_remote_resource);
		_encap_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case ENCAP_START_CACHING_N:
		ret = iotcon_remote_resource_start_caching(NULL, _encap_caching_cb, (void *)tc_index);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_remote_resource_start_caching() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_remote_resource_destroy(g_remote_resource);
		_encap_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case ENCAP_STOP_CACHING_N:
		/* without start */
		ret = iotcon_remote_resource_stop_caching(g_remote_resource);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_remote_resource_stop_caching() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_remote_resource_stop_caching(NULL);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_remote_resource_stop_caching() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_remote_resource_destroy(g_remote_resource);
		_encap_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case ENCAP_START_MONITORING_P:
		ret = iotcon_remote_resource_start_monitoring(g_remote_resource, _encap_monitoring_cb,
				(void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_start_monitoring() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_remote_resource_stop_monitoring(g_remote_resource);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_stop_monitoring() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_remote_resource_destroy(g_remote_resource);
		_encap_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case ENCAP_STOP_MONITORING_P:
		ret = iotcon_remote_resource_start_monitoring(g_remote_resource, _encap_monitoring_cb,
				(void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_start_monitoring() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		g_timeout_add_seconds(3, _destroy_lite_light_resource, NULL);
		return IOTCON_FUNC_STOP;
	case ENCAP_START_MONITORING_N:
		ret = iotcon_remote_resource_start_monitoring(NULL, _encap_monitoring_cb,
				(void *)tc_index);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_remote_resource_start_monitoring() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_remote_resource_start_monitoring(g_remote_resource, NULL,
				(void *)tc_index);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_remote_resource_start_monitoring() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_remote_resource_destroy(g_remote_resource);
		_encap_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case ENCAP_STOP_MONITORING_N:
		/* stop monitoring without start */
		ret = iotcon_remote_resource_stop_monitoring(g_remote_resource);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_remote_resource_stop_monitoring() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		ret = iotcon_remote_resource_stop_monitoring(NULL);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_remote_resource_stop_monitoring() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		iotcon_remote_resource_destroy(g_remote_resource);
		_encap_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case ENCAP_GET_CACHED_REPR_N:
	case ENCAP_GET_CACHED_REPR_P:
		ret = iotcon_remote_resource_start_caching(g_remote_resource, _encap_caching_cb,
				(void *)tc_index);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_remote_resource_start_caching() Fail(%d)", ret);
			iotcon_remote_resource_destroy(g_remote_resource);
			_encap_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		g_timeout_add_seconds(3, _update_lite_resource, NULL);
		return IOTCON_FUNC_STOP;
	default:
		ICUTC_ERR("Invalid tc_index(%d)", tc_index);
		iotcon_remote_resource_destroy(g_remote_resource);
		_encap_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	return IOTCON_FUNC_STOP;
}

static int _encap_handle_async(int tc_index)
{
	FN_CALL;
	int ret;
	iotcon_query_h query;

	g_loop = g_main_loop_new(NULL, FALSE);

	ret = _encap_create_lite_resource();
	ICUTC_ASSERT_EQ(ret, 0);

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
			query, _encap_found_resource, (void *)tc_index);
	iotcon_query_destroy(query);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	_encap_destroy_lite_resource();

	if (true == g_result)
		return 0;
	return 1;
}
/* ##################################################### */

/**
 * @function      utc_iotcon_encap_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_encap_startup(void)
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
 * @function      utc_iotcon_encap_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_encap_cleanup(void)
{
	icutc_free_client_ipv4_address();

	if (true == g_feature)
		iotcon_deinitialize();
}

/**
 * @testcase      utc_iotcon_lite_resource_create_n
 * @since_tizen   3.0
 * @description   Test fail creating a lite resource with invalid parameter.
 */
int utc_iotcon_lite_resource_create_n(void)
{
	int ret;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_lite_resource_create(ENCAP_LIGHT_RESOURCE_URI,
				types,
				(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
				NULL,
				NULL,
				NULL,
				NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_resource_types_create(&types);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_add(types, ENCAP_LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return ret;
	}

	ret = iotcon_lite_resource_create(NULL,
			types,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			NULL,
			NULL,
			NULL,
			&g_lite_light_resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_lite_resource_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		assert_eq(ret, IOTCON_ERROR_INVALID_PARAMETER);
	}

	ret = iotcon_lite_resource_create(ENCAP_LIGHT_RESOURCE_URI,
			NULL,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			NULL,
			NULL,
			NULL,
			&g_lite_light_resource);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_lite_resource_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		assert_eq(ret, IOTCON_ERROR_INVALID_PARAMETER);
	}

	ret = iotcon_lite_resource_create(ENCAP_LIGHT_RESOURCE_URI,
			types,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			NULL,
			NULL,
			NULL,
			NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_lite_resource_create() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		assert_eq(ret, IOTCON_ERROR_INVALID_PARAMETER);
	}
	iotcon_resource_types_destroy(types);

	return 0;
}

/**
 * @testcase      utc_iotcon_lite_resource_create_p
 * @since_tizen   3.0
 * @description   Test creating a lite resource.
 */
int utc_iotcon_lite_resource_create_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = _encap_create_lite_resource();
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_create_lite_resource();
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_lite_resource_destroy(g_lite_light_resource);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;
}

/**
 * @testcase      utc_iotcon_lite_resource_destroy_n
 * @since_tizen   3.0
 * @description   Test fail destroying a lite resource with invalid parameter.
 */
int utc_iotcon_lite_resource_destroy_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_lite_resource_destroy(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_lite_resource_destroy(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_lite_resource_destroy_p
 * @since_tizen   3.0
 * @description   Test destroying a lite resource.
 */
int utc_iotcon_lite_resource_destroy_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = _encap_create_lite_resource();
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_create_lite_resource();
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	_encap_destroy_lite_resource();

	return 0;
}


/**
 * @testcase      utc_iotcon_lite_resource_update_attributes_n
 * @since_tizen   3.0
 * @description   Test fail updating attributes from lite resource with invalid parameter.
 */
int utc_iotcon_lite_resource_update_attributes_n(void)
{
	int ret;
	iotcon_attributes_h attributes = NULL;

	if (false == g_feature) {
		ret = iotcon_lite_resource_update_attributes(NULL, attributes);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_create_lite_resource();
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_attributes_create(&attributes);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_lite_resource_update_attributes(NULL, attributes);
	iotcon_attributes_destroy(attributes);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	_encap_destroy_lite_resource();

	return 0;
}

/**
 * @testcase      utc_iotcon_lite_resource_update_attributes_p
 * @since_tizen   3.0
 * @description   Test updating attributes from lite resource.
 */
int utc_iotcon_lite_resource_update_attributes_p(void)
{
	int ret;
	iotcon_attributes_h attributes = NULL;

	if (false == g_feature) {
		ret = iotcon_lite_resource_update_attributes(g_lite_light_resource, attributes);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_create_lite_resource();
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_attributes_create(&attributes);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_attributes_add_int(attributes, "int", ++g_brightness);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_lite_resource_update_attributes(g_lite_light_resource, attributes);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	iotcon_attributes_destroy(attributes);
	_encap_destroy_lite_resource();

	return 0;
}

/**
 * @testcase      utc_iotcon_lite_resource_get_attributes_n
 * @since_tizen   3.0
 * @description   Test fail getting attributes from lite resource with invalid parameter.
 */
int utc_iotcon_lite_resource_get_attributes_n(void)
{
	int ret;
	iotcon_attributes_h attributes = NULL;

	if (false == g_feature) {
		ret = iotcon_lite_resource_get_attributes(NULL, &attributes);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_create_lite_resource();
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_lite_resource_get_attributes(NULL, &attributes);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	ret = iotcon_lite_resource_get_attributes(g_lite_light_resource, NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	_encap_destroy_lite_resource();

	return 0;
}

/**
 * @testcase      utc_iotcon_lite_resource_get_attributes_p
 * @since_tizen   3.0
 * @description   Test getting attributes from lite resource.
 */
int utc_iotcon_lite_resource_get_attributes_p(void)
{
	int ret;
	iotcon_attributes_h attributes = NULL;

	if (false == g_feature) {
		ret = iotcon_lite_resource_get_attributes(g_lite_light_resource, &attributes);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_create_lite_resource();
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_lite_resource_get_attributes(g_lite_light_resource, &attributes);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	_encap_destroy_lite_resource();

	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_start_caching_n
 * @since_tizen   3.0
 * @description   Test fail starting remote resource caching with invalid parameter.
 */
int utc_iotcon_remote_resource_start_caching_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_start_caching(g_remote_resource, _encap_caching_cb,
				NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_handle_async(ENCAP_START_CACHING_N);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_start_caching_p
 * @since_tizen   3.0
 * @description   Test starting remote resource caching.
 */
int utc_iotcon_remote_resource_start_caching_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_start_caching(g_remote_resource, _encap_caching_cb,
				NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_handle_async(ENCAP_START_CACHING_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_stop_caching_n
 * @since_tizen   3.0
 * @description   Test fail stopping remote resource caching with invalid parameter.
 */
int utc_iotcon_remote_resource_stop_caching_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_stop_caching(g_remote_resource);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_handle_async(ENCAP_STOP_CACHING_N);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_stop_caching_p
 * @since_tizen   3.0
 * @description   Test stopping remote resource caching.
 */
int utc_iotcon_remote_resource_stop_caching_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_stop_caching(g_remote_resource);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_handle_async(ENCAP_STOP_CACHING_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_start_monitoring_n
 * @since_tizen   3.0
 * @description   Test fail starting remote resource monitoring with invalid parameter.
 */
int utc_iotcon_remote_resource_start_monitoring_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_start_monitoring(g_remote_resource, _encap_monitoring_cb,
				NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_handle_async(ENCAP_START_MONITORING_N);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_start_monitoring_p
 * @since_tizen   3.0
 * @description   Test starting remote resource monitoring.
 */
int utc_iotcon_remote_resource_start_monitoring_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_start_monitoring(g_remote_resource, _encap_monitoring_cb,
				NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_handle_async(ENCAP_START_MONITORING_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_stop_monitoring_n
 * @since_tizen   3.0
 * @description   Test fail stopping remote resource monitoring with invalid parameter.
 */
int utc_iotcon_remote_resource_stop_monitoring_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_stop_monitoring(g_remote_resource);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_handle_async(ENCAP_STOP_MONITORING_N);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_stop_monitoring_p
 * @since_tizen   3.0
 * @description   Test stopping remote resource monitoring.
 */
int utc_iotcon_remote_resource_stop_monitoring_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_stop_monitoring(g_remote_resource);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_handle_async(ENCAP_STOP_MONITORING_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_cached_representation_n
 * @since_tizen   3.0
 * @description   Test fail getting cached representation from remote resource with invalid parameter.
 */
int utc_iotcon_remote_resource_get_cached_representation_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_start_caching(g_remote_resource, _encap_caching_cb,
				NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_handle_async(ENCAP_GET_CACHED_REPR_N);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_remote_resource_get_cached_representation_p
 * @since_tizen   3.0
 * @description   Test getting cached representation from remote resource.
 */
int utc_iotcon_remote_resource_get_cached_representation_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_remote_resource_start_caching(g_remote_resource, _encap_caching_cb,
				NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _encap_handle_async(ENCAP_GET_CACHED_REPR_P);
	ICUTC_ASSERT_EQ(ret, 0);

	return 0;
}

