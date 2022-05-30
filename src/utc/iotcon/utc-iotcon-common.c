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
#include <iotcon.h>
#include <wifi-manager.h>

#include "tct_common.h"
#include "utc-iotcon-common.h"

#define API_NAMESPACE			"[IOTCON]"

static const char *icutc_svr_db_file = "icutc_svr_db.dat";

int icutc_send_ok_response(iotcon_request_h request)
{
	FN_CALL;
	int ret;
	iotcon_response_h response = NULL;
	iotcon_options_h options = NULL;
	iotcon_representation_h repr = NULL;

	ret = iotcon_response_create(request, &response);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_create() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_options_create(&options);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_create() Fail(%d)", ret);
		iotcon_response_destroy(response);
		return 1;
	}

	ret = iotcon_options_add(options, 2048, "1");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_options_add() Fail(%d)", ret);
		iotcon_options_destroy(options);
		iotcon_response_destroy(response);
		return 1;
	}

	ret = iotcon_response_set_result(response, IOTCON_RESPONSE_OK);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_set_result() Fail(%d)", ret);
		iotcon_options_destroy(options);
		iotcon_response_destroy(response);
		return 1;
	}

	ret = iotcon_response_set_options(response, options);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_send() Fail(%d)", ret);
		iotcon_options_destroy(options);
		iotcon_response_destroy(response);
		return 1;
	}

	ret = icutc_create_representation(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_representation() Fail(%d)", ret);
		iotcon_options_destroy(options);
		iotcon_response_destroy(response);
		return 1;
	}

	ret = iotcon_response_set_representation(response, repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_set_representation() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		iotcon_options_destroy(options);
		iotcon_response_destroy(response);
		return 1;
	}

	/* for preventing crash */
	sleep(1);

	ret = iotcon_response_send(response);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_response_send() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		iotcon_options_destroy(options);
		iotcon_response_destroy(response);
		return 1;
	}

	iotcon_representation_destroy(repr);
	iotcon_options_destroy(options);
	iotcon_response_destroy(response);

	return 0;
}

int icutc_create_resource_types(const char *type, iotcon_resource_types_h *types_h)
{
	int ret;
	iotcon_resource_types_h types;

	ret = iotcon_resource_types_create(&types);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_create() Fail(%d)", ret);
		return ret;
	}

	ret = iotcon_resource_types_add(types, type);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return ret;
	}

	*types_h = types;
	return 0;
}

int icutc_create_resource_interfaces(iotcon_resource_interfaces_h *ifaces_h)
{
	int ret;
	iotcon_resource_interfaces_h ifaces;

	ret = iotcon_resource_interfaces_create(&ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_create() Fail(%d)", ret);
		return ret;
	}

	ret = iotcon_resource_interfaces_add(ifaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		return ret;
	}

	ret = iotcon_resource_interfaces_add(ifaces, IOTCON_INTERFACE_BATCH);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		return ret;
	}

	*ifaces_h = ifaces;

	return 0;
}

static void _icutc_request_handler(iotcon_resource_h resource,
		iotcon_request_h request, void *user_data)
{
	FN_CALL;
}

int icutc_create_resource(const char *resource_type, const char *resource_uri,
		iotcon_resource_h *resource_handle)
{
	int ret;
	iotcon_resource_h resource = NULL;
	iotcon_resource_types_h types;
	iotcon_resource_interfaces_h ifaces;

	ret = icutc_create_resource_types(resource_type, &types);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource_types() Fail(%d)", ret);
		return ret;
	}

	ret = icutc_create_resource_interfaces(&ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource_interfaces() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		return ret;
	}

	ret = iotcon_resource_create(resource_uri,
			types,
			ifaces,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			_icutc_request_handler,
			NULL,
			&resource);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		iotcon_resource_types_destroy(types);
		return ret;
	}
	iotcon_resource_interfaces_destroy(ifaces);
	iotcon_resource_types_destroy(types);

	*resource_handle = resource;
	return 0;
}

int icutc_create_attributes(iotcon_attributes_h *attributes_h)
{
	int ret;
	iotcon_attributes_h attributes, val_attributes;
	unsigned char byte_str[3] = {70, 71, 72};
	iotcon_list_h list1, list2, list3, list4, list5, list6, list7;

	ret = iotcon_attributes_create(&attributes);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_create() Fail(%d)", ret);
		return ret;
	}

	ret = iotcon_attributes_add_int(attributes, "int", 1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_int() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_attributes_add_bool(attributes, "bool", true);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_bool() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_attributes_add_double(attributes, "double", 1.1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_double() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_attributes_add_null(attributes, "null");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_null() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_attributes_add_str(attributes, "str", "string");
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_attributes_add_byte_str(attributes, "bytestr", byte_str, 3);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_byte_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	/* attributes */
	ret = iotcon_attributes_create(&val_attributes);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_create() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_attributes_add_int(val_attributes, "val_attributes", 10);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_int() Fail(%d)", ret);
		iotcon_attributes_destroy(val_attributes);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_attributes_add_attributes(attributes, "attributes", val_attributes);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(val_attributes);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	/* attributes list */
	ret = iotcon_list_create(IOTCON_TYPE_ATTRIBUTES, &list6);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_create() Fail(%d)", ret);
		iotcon_attributes_destroy(val_attributes);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_list_add_attributes(list6, val_attributes, -1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_add_attributes() Fail(%d)", ret);
		iotcon_list_destroy(list6);
		iotcon_attributes_destroy(val_attributes);
		iotcon_attributes_destroy(attributes);
		return ret;
	}
	iotcon_attributes_destroy(val_attributes);

	ret = iotcon_attributes_add_list(attributes, "attributes_list", list6);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_list() Fail(%d)", ret);
		iotcon_list_destroy(list6);
		iotcon_attributes_destroy(attributes);
		return ret;
	}
	iotcon_list_destroy(list6);

	/* int list */
	ret = iotcon_list_create(IOTCON_TYPE_INT, &list1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_create() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_list_add_int(list1, 1, -1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_add_int() Fail(%d)", ret);
		iotcon_list_destroy(list1);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_attributes_add_list(attributes, "int_list", list1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_list() Fail(%d)", ret);
		iotcon_list_destroy(list1);
		iotcon_attributes_destroy(attributes);
		return ret;
	}
	iotcon_list_destroy(list1);

	/* boolean list */
	ret = iotcon_list_create(IOTCON_TYPE_BOOL, &list2);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_create() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_list_add_bool(list2, true, -1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_add_bool() Fail(%d)", ret);
		iotcon_list_destroy(list2);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_attributes_add_list(attributes, "bool_list", list2);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_list() Fail(%d)", ret);
		iotcon_list_destroy(list2);
		iotcon_attributes_destroy(attributes);
		return ret;
	}
	iotcon_list_destroy(list2);

	/* string list */
	ret = iotcon_list_create(IOTCON_TYPE_STR, &list3);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_create() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_list_add_str(list3, "string", -1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_add_str() Fail(%d)", ret);
		iotcon_list_destroy(list3);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_attributes_add_list(attributes, "str_list", list3);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_list() Fail(%d)", ret);
		iotcon_list_destroy(list3);
		iotcon_attributes_destroy(attributes);
		return ret;
	}
	iotcon_list_destroy(list3);

	/* byte string list */
	ret = iotcon_list_create(IOTCON_TYPE_BYTE_STR, &list4);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_create() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_list_add_byte_str(list4, byte_str, 3, -1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_add_byte_str() Fail(%d)", ret);
		iotcon_list_destroy(list4);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_attributes_add_list(attributes, "byte_str_list", list4);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_list() Fail(%d)", ret);
		iotcon_list_destroy(list4);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	/* list list */
	ret = iotcon_list_create(IOTCON_TYPE_LIST, &list5);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_create() Fail(%d)", ret);
		iotcon_list_destroy(list4);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_list_add_list(list5, list4, -1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_add_list() Fail(%d)", ret);
		iotcon_list_destroy(list5);
		iotcon_list_destroy(list4);
		iotcon_attributes_destroy(attributes);
		return ret;
	}
	iotcon_list_destroy(list4);

	ret = iotcon_attributes_add_list(attributes, "list_list", list5);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_list() Fail(%d)", ret);
		iotcon_list_destroy(list5);
		iotcon_attributes_destroy(attributes);
		return ret;
	}
	iotcon_list_destroy(list5);

	/* double list */
	ret = iotcon_list_create(IOTCON_TYPE_DOUBLE, &list7);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_create() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret = iotcon_list_add_double(list7, 1.1, -1);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_add_double() Fail(%d)", ret);
		iotcon_list_destroy(list7);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	ret =iotcon_attributes_add_list(attributes, "double_list", list7);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_add_list() Fail(%d)", ret);
		iotcon_list_destroy(list7);
		iotcon_attributes_destroy(attributes);
		return ret;
	}

	iotcon_list_destroy(list7);

	*attributes_h = attributes;

	return 0;
}

int icutc_create_representation(iotcon_representation_h *representation)
{
	int ret;
	char *uri_path = "/uri_path";
	iotcon_attributes_h attributes;
	iotcon_representation_h repr;
	iotcon_resource_types_h types;
	iotcon_resource_interfaces_h ifaces;

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		return ret;
	}

	/* uri path */
	ret = iotcon_representation_set_uri_path(repr, uri_path);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_set_uri_path() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return ret;
	}

	/* resource types */
	ret = icutc_create_resource_types(LIGHT_RESOURCE_TYPE, &types);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource_types() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return ret;
	}

	ret = iotcon_representation_set_resource_types(repr, types);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_set_resource_types() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		iotcon_representation_destroy(repr);
		return ret;
	}

	iotcon_resource_types_destroy(types);

	/* resource interfaces */
	ret = icutc_create_resource_interfaces(&ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_resource_interfaces() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return ret;
	}

	ret = iotcon_representation_set_resource_interfaces(repr, ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_set_resource_interfaces() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		iotcon_representation_destroy(repr);
		return ret;
	}

	iotcon_resource_interfaces_destroy(ifaces);

	/* attributes */
	ret = icutc_create_attributes(&attributes);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("icutc_create_attributes() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return ret;
	}

	ret = iotcon_representation_set_attributes(repr, attributes);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_set_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		iotcon_representation_destroy(repr);
		return ret;
	}

	iotcon_attributes_destroy(attributes);
	*representation = repr;

	return 0;
}

void icutc_check_wifi_state()
{
	int ret;
	wifi_manager_h wifi = NULL;
	wifi_manager_connection_state_e connection_state;
	bool activated;

	ret = wifi_manager_initialize(&wifi);
	if (WIFI_MANAGER_ERROR_NONE != ret) {
		ICUTC_ERR("wifi_manager_initialize() Fail(%d)", ret);
		return;
	}

	ret = wifi_manager_is_activated(wifi, &activated);
	if (WIFI_MANAGER_ERROR_NONE != ret) {
		ICUTC_ERR("wifi_manager_is_activated() Fail(%d)", ret);
		wifi_manager_deinitialize(wifi);
		return;
	} else if (false == activated) {
		ICUTC_ERR("wifi is not activated");
		wifi_manager_deinitialize(wifi);
		return;
	}

	ret = wifi_manager_get_connection_state(wifi, &connection_state);
	if (WIFI_MANAGER_ERROR_NONE != ret) {
		ICUTC_ERR("wifi_manager_get_connection_state() Fail(%d)", ret);
		wifi_manager_deinitialize(wifi);
		return;
	}

	switch (connection_state) {
	case WIFI_MANAGER_CONNECTION_STATE_CONNECTED:
		ICUTC_INFO("WIFI_MANAGER_CONNECTION_STATE_CONNECTED");
		break;
	case WIFI_MANAGER_CONNECTION_STATE_FAILURE:
		ICUTC_ERR("WIFI_MANAGER_CONNECTION_STATE_FAILURE");
		break;
	case WIFI_MANAGER_CONNECTION_STATE_DISCONNECTED:
		ICUTC_ERR("WIFI_MANAGER_CONNECTION_STATE_DISCONNECTED");
		break;
	case WIFI_MANAGER_CONNECTION_STATE_ASSOCIATION:
		ICUTC_ERR("WIFI_MANAGER_CONNECTION_STATE_ASSOCIATION");
		break;
	case WIFI_MANAGER_CONNECTION_STATE_CONFIGURATION:
		ICUTC_ERR("WIFI_MANAGER_CONNECTION_STATE_CONFIGURATION");
		break;
	default:
		ICUTC_ERR("Invalid connection state(%d)", connection_state);
	}

	wifi_manager_deinitialize(wifi);

}

int icutc_get_svr_db_path(char **path)
{
	FN_CALL;
	char file_path[PATH_MAX] = {0};
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

	if (false == GetValueForTCTSetting("DEVICE_USER_30", pszValue, API_NAMESPACE)) {
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
		return -1;
	}

	PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_USER_30' Values Received = %s\\n",
			__LINE__, API_NAMESPACE,  pszValue);

	snprintf(file_path, sizeof(file_path), "%s/apps_rw/core-iotcon-tests/data/%s", pszValue,
			icutc_svr_db_file);

	*path = strdup(file_path);
	ICUTC_INFO("path: %s", *path);

	return 0;
}

void icutc_get_client_ipv4_address(void)
{
	g_ipv4_address = NULL;
	g_conn_h = NULL;

	g_bFeatureWifi = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
	g_bFeatureEthernet = TCTCheckSystemInfoFeatureSupported(ETHERNET_FEATURE, API_NAMESPACE);
	ICUTC_INFO("g_bFeatureWifi(%d), g_bFeatureEthernet(%d)", g_bFeatureWifi, g_bFeatureEthernet);

	if ((g_bFeatureWifi == true) || (g_bFeatureEthernet == true)) {
		int nRet = 0;

		nRet = connection_create(&g_conn_h);
		if (nRet != CONNECTION_ERROR_NONE) {
			ICUTC_ERR("(1/3) connection_create() FAIL(nRet = 0x%x)", nRet);
			return;
		}

		nRet = connection_get_ip_address(g_conn_h, CONNECTION_ADDRESS_FAMILY_IPV4, &g_ipv4_address);
		if (nRet != CONNECTION_ERROR_NONE) {
			ICUTC_ERR("(2/3) connection_get_ip_address() FAIL(nRet = 0x%x)", nRet);
		} else {
			ICUTC_INFO("g_ipv4_address(%s)", g_ipv4_address);
		}

		if (g_conn_h != NULL) {
			nRet = connection_destroy(g_conn_h);
			if (nRet != CONNECTION_ERROR_NONE) {
				ICUTC_ERR("(3/3) connection_destroy() FAIL(nRet = 0x%x)", nRet);
				return;
			}
		}
	} else {
		ICUTC_INFO("Wi-Fi and Ethernet are both NOT SUPPORTED");
	}
}

void icutc_free_client_ipv4_address(void)
{
	ICUTC_INFO("g_free() g_ipv4_address(%s)", g_ipv4_address);

	if (g_ipv4_address != NULL) {
		g_free(g_ipv4_address);
	}

	ICUTC_INFO("g_free() g_ipv4_address done");
}

