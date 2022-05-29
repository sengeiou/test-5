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

#include "utc-connection-common.h"

static void test_network_state_changed_cb(connection_type_e state, void* user_data)
{
	PRINT_RETURN("test_network_state_changed_cb", CONNECTION_ERROR_NONE);
	QUIT_GMAIN_LOOP;
}

static void test_ip_address_changed_cb(const char* ipv4_address, const char* ipv6_address, void* user_data)
{
	PRINT_RETURN("test_ip_address_changed_cb", CONNECTION_ERROR_NONE);
	QUIT_GMAIN_LOOP;
}

static void test_proxy_address_changed_cb(const char* ipv4_address, const char* ipv6_address, void* user_data)
{
	PRINT_RETURN("test_proxy_address_changed_cb", CONNECTION_ERROR_NONE);
	QUIT_GMAIN_LOOP;
}

static void test_connection_opened_callback(connection_error_e result, void* user_data)
{
	PRINT_RETURN("test_connection_opened_callback", result);
	g_CallbackRet = result;
	QUIT_GMAIN_LOOP;
}

static void test_connection_closed_callback(connection_error_e result, void* user_data)
{
	PRINT_RETURN("test_connection_closed_callback", result);
	g_CallbackRet = result;
	QUIT_GMAIN_LOOP;
}

static void test_connection_set_default_callback(connection_error_e result, void* user_data)
{
	PRINT_RETURN("test_connection_set_default_callback", result);
	g_CallbackRet = result;
	QUIT_GMAIN_LOOP;
}

static void test_connection_reset_profile_callback(connection_error_e result, void* user_data)
{
	PRINT_RETURN("test_connection_reset_profile_callback", result);
	g_CallbackRet = result;
	QUIT_GMAIN_LOOP;
}

static bool test_connection_ipv6_address_callback(char *ipv6_address, void *user_data)
{
	PRINT_RETURN("test_connection_ipv6_address_callback", CONNECTION_ERROR_NONE);
	return true;
}

static void test_connection_internet_state_changed_callback(connection_internet_state_e state, void* user_data)
{
	PRINT_RETURN("test_connection_internet_state_changed_callback", CONNECTION_ERROR_NONE);
}

static int test_get_profile_by_name(connection_profile_h *profile, char *name)
{
	connection_profile_h profile_h;
	connection_profile_iterator_h profile_iter;
	char *profile_name = NULL;
	size_t name_len = strlen(name);

	int  rv = connection_get_profile_iterator(connection, CONNECTION_ITERATOR_TYPE_REGISTERED, &profile_iter);
	PRINT_RETURN("connection_get_profile_iterator", rv);

	if (CONNECTION_ERROR_NONE != rv)
		return -1;

	while (connection_profile_iterator_has_next(profile_iter)) {
		rv = connection_profile_iterator_next(profile_iter, &profile_h);
		PRINT_RETURN("connection_profile_iterator_next", rv);
		if (CONNECTION_ERROR_NONE != rv)
			return -1;

		rv = connection_profile_get_name(profile_h, &profile_name);
		PRINT_RETURN("connection_profile_get_name", rv);
		if (CONNECTION_ERROR_NONE != rv)
			return -1;

		size_t profile_name_len = strlen(profile_name);
		if (strncmp(name, profile_name,
					name_len > profile_name_len ? name_len : profile_name_len) == 0)
			break;
	}

	rv = connection_profile_clone(profile, profile_h);
	PRINT_RETURN("connection_profile_clone", rv);

	if (CONNECTION_ERROR_NONE != rv)
		return -1;

	return 1;
}

/**
 * @function		utc_network_connection_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_network_connection_startup(void)
{
	wifi_supported = connection_check_feature_supported(FEATURE_WIFI);
	telephony_supported = connection_check_feature_supported(FEATURE_TELEPHONY);
	bt_tethering_supported = connection_check_feature_supported(FEATURE_BT_TETHERING);
	ethernet_supported = connection_check_feature_supported(FEATURE_ETHERNET);

	if (telephony_supported == false && wifi_supported == false
			&& bt_tethering_supported == false && ethernet_supported == false) {
		all_features_not_supported = true;
		FPRINTF("[%s:%d] all feature is not supported\\n", __FILE__, __LINE__);
		return ;
	}

	int ret = connection_create(&connection);
	PRINT_RETURN("connection_create", ret);
	if (ret != CONNECTION_ERROR_NONE)
		return;

	if (telephony_supported) {
		if (!profile_cellular) {
			ret = connection_profile_create(CONNECTION_PROFILE_TYPE_CELLULAR, CUSTOM_PROFILE_NAME, &profile_cellular);
			PRINT_RETURN("connection_profile_create", ret);
		}
	}
}

/**
 * @function		utc_network_connection_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_network_connection_cleanup(void)
{
	int ret;

	if (profile_cellular) {
		ret = connection_profile_destroy(profile_cellular);
		PRINT_RETURN("connection_profile_destroy", ret);
		profile_cellular = NULL;
	}

	if (profile_temp) {
		ret = connection_profile_destroy(profile_temp);
		PRINT_RETURN("connection_profile_destroy", ret);
		profile_temp = NULL;
	}

	if (connection) {
		ret = connection_destroy(connection);
		PRINT_RETURN("connection_destroy", ret);
		connection = NULL;
	}
}

/**
 * @testcase		utc_connection_create_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Creates a handle for managing data connections.
 * @scenario  		Invoking connection_create with valid parameter.Destroy and create Connection.
 */
int utc_connection_create_p(void)
{
	int ret;

	if (all_features_not_supported) {
		ret = connection_create(&connection);
		CHECK_RETURN("connection_create", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (connection) {
		ret = connection_destroy(connection);
		PRINT_RETURN("connection_destroy", ret);
		connection = NULL;
	}

	ret = connection_create(&connection);
	CHECK_RETURN("connection_create", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_create_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_create should fail with invalid parameter.
 * @scenario  		Verify connection_create by passing NULL parameter.
 */
int utc_connection_create_n(void)
{
	int ret;

	if (all_features_not_supported) {
		ret = connection_create(&connection);
		CHECK_RETURN("connection_create", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (connection) {
		ret = connection_destroy(connection);
		PRINT_RETURN("connection_destroy", ret);
		connection = NULL;
	}

	ret = connection_create(NULL);
	CHECK_RETURN("connection_create", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_get_ip_address_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the IP address of the current connection.
 * @scenario  		Invoking connection_get_ip_address with valid parameter.
 */
int utc_connection_get_ip_address_p(void)
{
	char *ip_address = NULL;

	int ret = connection_get_ip_address(connection, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_address);
	FREE_RESOURCE(ip_address);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_get_ip_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_get_ip_address", ret, CONNECTION_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_connection_get_ip_address_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_get_ip_address should fail with invalid parameter.
 * @scenario  		Verify connection_get_ip_address by passing invalid parameter.
 */
int utc_connection_get_ip_address_n(void)
{
	int ret;
	char *ip_address = NULL;

	if (all_features_not_supported) {
		ret = connection_get_ip_address(connection, -100, NULL);
		CHECK_RETURN("connection_get_ip_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_ip_address(NULL, -100, NULL);
	CHECK_RETURN("connection_get_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_ip_address(NULL, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_address);
	FREE_RESOURCE(ip_address);
	CHECK_RETURN("connection_get_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_ip_address(connection, -100, &ip_address);
	FREE_RESOURCE(ip_address);
	CHECK_RETURN("connection_get_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_ip_address(connection, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_get_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_ip_address(NULL, -100, &ip_address);
	FREE_RESOURCE(ip_address);
	CHECK_RETURN("connection_get_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_ip_address(NULL, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_get_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_ip_address(connection, -100, NULL);
	CHECK_RETURN("connection_get_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_get_proxy_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the proxy address of the current connection.
 * @scenario  		Invoking connection_get_proxy with valid parameter.
 */
int utc_connection_get_proxy_p(void)
{
	char *proxy = NULL;

	int ret = connection_get_proxy(connection, CONNECTION_ADDRESS_FAMILY_IPV4, &proxy);
	FREE_RESOURCE(proxy);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_get_proxy", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_get_proxy", ret, CONNECTION_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_connection_get_proxy_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_get_proxy should fail with invalid parameter.
 * @scenario  		Verify connection_get_proxy by passing invalid parameter.
 */
int utc_connection_get_proxy_n(void)
{
	int ret;
	char *proxy = NULL;

	if (all_features_not_supported) {
		ret = connection_get_proxy(connection, -100, NULL);
		CHECK_RETURN("connection_get_proxy", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_proxy(NULL, -100, NULL);
	CHECK_RETURN("connection_get_proxy", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_proxy(NULL, CONNECTION_ADDRESS_FAMILY_IPV4, &proxy);
	FREE_RESOURCE(proxy);
	CHECK_RETURN("connection_get_proxy", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_proxy(connection, -100, &proxy);
	FREE_RESOURCE(proxy);
	CHECK_RETURN("connection_get_proxy", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_proxy(connection, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_get_proxy", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_proxy(NULL, -100, &proxy);
	FREE_RESOURCE(proxy);
	CHECK_RETURN("connection_get_proxy", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_proxy(NULL, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_get_proxy", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_proxy(connection, -100, NULL);
	CHECK_RETURN("connection_get_proxy", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_get_type_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_get_type should fail with invalid parameter.
 * @scenario  		Verify connection_get_type by passing invalid parameter.
 */
int utc_connection_get_type_n(void)
{
	int ret;
	connection_type_e state;

	if (all_features_not_supported) {
		ret = connection_get_type(connection, NULL);
		CHECK_RETURN("connection_get_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_type(NULL, NULL);
	CHECK_RETURN("connection_get_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_type(NULL, &state);
	CHECK_RETURN("connection_get_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_type(connection, NULL);
	CHECK_RETURN("connection_get_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_get_type_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the type of the current profile for data connection.
 * @scenario  		Invoking connection_get_type with valid parameter.
 */
int utc_connection_get_type_p(void)
{
	connection_type_e state;

	int ret = connection_get_type(connection, &state);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_get_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_get_type", ret, CONNECTION_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_connection_is_metered_network_n
 * @since_tizen 	4.0
 * @type		Negative
 * @description		connection_is_metered_network should fail with invalid parameter.
 * @scenario  		Verify utc_connection_is_metered_network_n by passing invalid parameter.
 */
int utc_connection_is_metered_network_n(void)
{
	int ret;
	bool state;

	if (all_features_not_supported) {
		ret = connection_is_metered_network(connection, NULL);
		CHECK_RETURN("connection_is_metered_network", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_is_metered_network(NULL, NULL);
	CHECK_RETURN("connection_is_metered_network", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_is_metered_network(NULL, &state);
	CHECK_RETURN("connection_is_metered_network", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_is_metered_network(connection, NULL);
	CHECK_RETURN("connection_is_metered_network", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_is_metered_network_p
 * @since_tizen 	4.0
 * @type		Positive
 * @description		Gets if the current connection is metered.
 * @scenario  		Invoking utc_connection_is_metered_network_p with valid parameter.
 */
int utc_connection_is_metered_network_p(void)
{
	bool state = false;
	connection_type_e type;

	int ret = connection_is_metered_network(connection, &state);
	int err = connection_get_type(connection, &type);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_is_metered_network", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else if (state) {
		CHECK_RETURN("connection_is_metered_network", type, CONNECTION_TYPE_CELLULAR);
	} else {
		CHECK_RETURN("connection_is_metered_network", ret, CONNECTION_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_connection_get_cellular_state_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_get_cellular_state should fail with invalid parameter.
 * @scenario  		Verify connection_get_cellular_state by passing invalid parameter.
 */
int utc_connection_get_cellular_state_n(void)
{
	connection_cellular_state_e state;

	if (!telephony_supported) {
		int ret = connection_get_cellular_state(NULL, NULL);
		CHECK_RETURN("connection_get_cellular_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int ret = connection_get_cellular_state(NULL, NULL);
	CHECK_RETURN("connection_get_cellular_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_cellular_state(NULL, &state);
	CHECK_RETURN("connection_get_cellular_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_cellular_state(connection, NULL);
	CHECK_RETURN("connection_get_cellular_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_get_cellular_state_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the state of cellular connection.
 * @scenario  		Invoking connection_get_cellular_state with valid parameter.
 */
int utc_connection_get_cellular_state_p(void)
{
	connection_cellular_state_e state;

	if (!telephony_supported) {
		int ret = connection_get_cellular_state(connection, &state);
		CHECK_RETURN("connection_get_cellular_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int ret = connection_get_cellular_state(connection, &state);
	CHECK_RETURN("connection_get_cellular_state", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_get_ethernet_state_n
 * @since_tizen 	2.4
 * @type		Negative
 * @description		connection_get_ethernet_state should fail with invalid parameter.
 * @scenario  		Verify connection_get_ethernet_state by passing invalid parameter.
 */
int utc_connection_get_ethernet_state_n(void)
{
	connection_ethernet_state_e state;

	if (!ethernet_supported) {
		int ret = connection_get_ethernet_state(NULL, NULL);
		CHECK_RETURN("connection_get_ethernet_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int ret = connection_get_ethernet_state(NULL, NULL);
	CHECK_RETURN("connection_get_ethernet_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_ethernet_state(NULL, &state);
	CHECK_RETURN("connection_get_ethernet_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_ethernet_state(connection, NULL);
	CHECK_RETURN("connection_get_ethernet_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_get_ethernet_state_p
 * @since_tizen 	2.4
 * @type		Positive
 * @description		Gets the state of the Ethernet.
 * @scenario  		Invoking connection_get_ethernet_state with valid parameter.
 */
int utc_connection_get_ethernet_state_p(void)
{
	connection_ethernet_state_e state;

	if (!ethernet_supported) {
		int ret = connection_get_ethernet_state(connection, &state);
		CHECK_RETURN("connection_get_ethernet_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int ret = connection_get_ethernet_state(connection, &state);
	CHECK_RETURN("connection_get_ethernet_state", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_get_wifi_state_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_get_wifi_state should fail with invalid parameter.
 * @scenario  		Verify connection_get_wifi_state by passing invalid parameter.
 */
int utc_connection_get_wifi_state_n(void)
{
	connection_wifi_state_e state;

	if (!wifi_supported) {
		int ret = connection_get_wifi_state(NULL, NULL);
		CHECK_RETURN("connection_get_wifi_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int ret = connection_get_wifi_state(NULL, NULL);
	CHECK_RETURN("connection_get_wifi_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_wifi_state(NULL, &state);
	CHECK_RETURN("connection_get_wifi_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_wifi_state(connection, NULL);
	CHECK_RETURN("connection_get_wifi_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_get_wifi_state_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the state of the Wi-Fi.
 * @scenario  		Invoking connection_get_wifi_state with valid parameter.
 */
int utc_connection_get_wifi_state_p(void)
{
	connection_wifi_state_e state;

	if (!wifi_supported) {
		int ret = connection_get_wifi_state(connection, &state);
		CHECK_RETURN("connection_get_wifi_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int ret = connection_get_wifi_state(connection, &state);
	CHECK_RETURN("connection_get_wifi_state", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_get_bt_state_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_get_bt_state should fail with invalid parameter.
 * @scenario  		Verify connection_get_bt_state by passing invalid parameter.
 */
int utc_connection_get_bt_state_n(void)
{
	connection_bt_state_e state;

	if (!bt_tethering_supported) {
		int ret = connection_get_bt_state(NULL, NULL);
		CHECK_RETURN("connection_get_bt_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int ret = connection_get_bt_state(NULL, NULL);
	CHECK_RETURN("connection_get_bt_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_bt_state(NULL, &state);
	CHECK_RETURN("connection_get_bt_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_bt_state(connection, NULL);
	CHECK_RETURN("connection_get_bt_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_get_bt_state_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the state of the Bluetooth.The returned state is for the Bluetooth connection state.
 * @scenario  		Invoking connection_get_bt_state with valid parameter.
 */
int utc_connection_get_bt_state_p(void)
{
	connection_bt_state_e state;

	if (!bt_tethering_supported) {
		int ret = connection_get_bt_state(connection, &state);
		CHECK_RETURN("connection_get_bt_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int ret = connection_get_bt_state(connection, &state);
	CHECK_RETURN("connection_get_bt_state", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_get_mac_address_n
 * @since_tizen 	2.4
 * @type		Negative
 * @description		connection_get_mac_address should fail with invalid parameter.
 * @scenario  		Verify connection_get_mac_address by passing invalid parameter.
 */
int utc_connection_get_mac_address_n(void)
{
	int ret;
	char *mac_addr = NULL;

	if (wifi_supported == false && ethernet_supported == false) {
		ret = connection_get_mac_address(connection, CONNECTION_TYPE_WIFI, &mac_addr);
		CHECK_RETURN("connection_get_mac_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (wifi_supported) {
		ret = connection_get_mac_address(NULL, CONNECTION_TYPE_WIFI, &mac_addr);
		FREE_RESOURCE(mac_addr);
		CHECK_RETURN("connection_get_mac_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		ret = connection_get_mac_address(connection, CONNECTION_TYPE_ETHERNET, NULL);
		FREE_RESOURCE(mac_addr);
		CHECK_RETURN("connection_get_mac_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_connection_get_mac_address_p
 * @since_tizen 	2.4
 * @type		Positive
 * @description		Gets the MAC address of the Wi-Fi or ethernet.
 * @scenario  		Invoking connection_get_mac_address with valid parameter.
 */
int utc_connection_get_mac_address_p(void)
{
	int ret;
	char *mac_addr = NULL;

	if (wifi_supported) {
		ret = connection_get_mac_address(connection, CONNECTION_TYPE_WIFI, &mac_addr);
		assert(mac_addr); FREE_RESOURCE(mac_addr);
		CHECK_RETURN("connection_get_mac_address", ret, CONNECTION_ERROR_NONE);
	} else if(ethernet_supported) {
		ret = connection_get_mac_address(connection, CONNECTION_TYPE_ETHERNET, &mac_addr);
		assert(mac_addr); FREE_RESOURCE(mac_addr);
		CHECK_RETURN("connection_get_mac_address", ret, CONNECTION_ERROR_NONE);
	} else {
		ret = connection_get_mac_address(connection, CONNECTION_TYPE_WIFI, &mac_addr);
		FREE_RESOURCE(mac_addr);
		CHECK_RETURN("connection_get_mac_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_set_ethernet_cable_state_chaged_cb_n
 * @since_tizen 	2.4
 * @type		Negative
 * @description		connection_set_ethernet_cable_state_chaged_cb should fail with invalid parameter.
 * @scenario  		Verify connection_set_ethernet_cable_state_chaged_cb by passing invalid parameter.
 */
int utc_connection_set_ethernet_cable_state_chaged_cb_n(void)
{
	int ret;
	if (ethernet_supported == false) {
		ret = connection_set_ethernet_cable_state_chaged_cb(NULL, NULL, NULL);
		CHECK_RETURN("connection_set_ethernet_cable_state_chaged_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_set_ethernet_cable_state_chaged_cb(NULL,
			test_connection_set_default_callback, NULL);
	CHECK_RETURN("connection_set_ethernet_cable_state_chaged_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_set_ethernet_cable_state_chaged_cb(connection, NULL, NULL);
	CHECK_RETURN("connection_set_ethernet_cable_state_chaged_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_unset_ethernet_cable_state_chaged_cb_n
 * @since_tizen 	2.4
 * @type		Negative
 * @description		connection_unset_ethernet_cable_state_chaged_cb should fail with invalid parameter.
 * @scenario  		Verify connection_unset_ethernet_cable_state_chaged_cb by passing invalid parameter.
 */
int utc_connection_unset_ethernet_cable_state_chaged_cb_n(void)
{
	int ret;
	ret = connection_unset_ethernet_cable_state_chaged_cb(NULL);

	if (ethernet_supported == false) {
		CHECK_RETURN("connection_unset_ethernet_cable_state_chaged_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_unset_ethernet_cable_state_chaged_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_connection_get_ethernet_cable_state_n
 * @since_tizen 	2.4
 * @type		Negative
 * @description		connection_get_ethernet_cable_state should fail with invalid parameter.
 * @scenario  		Verify connection_get_ethernet_cable_state by passing invalid parameter.
 */
int utc_connection_get_ethernet_cable_state_n(void)
{
	int ret;
	connection_ethernet_cable_state_e cable_state;

	if (ethernet_supported == false) {
		ret = connection_get_ethernet_cable_state(NULL, NULL);
		CHECK_RETURN("connection_get_ethernet_cable_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_ethernet_cable_state(NULL, &cable_state);
	CHECK_RETURN("connection_get_ethernet_cable_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_ethernet_cable_state(connection, NULL);
	CHECK_RETURN("connection_get_ethernet_cable_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_get_ethernet_cable_state_p
 * @since_tizen 	2.4
 * @type		Positive
 * @description		Checks for ethernet cable is attached or not.
 * @scenario  		Invoking connection_get_ethernet_cable_state with valid parameter.
 */
int utc_connection_get_ethernet_cable_state_p(void)
{
	int ret;
	connection_ethernet_cable_state_e cable_state;

	ret = connection_get_ethernet_cable_state(connection, &cable_state);
	if (ethernet_supported == false) {
		CHECK_RETURN("connection_get_ethernet_cable_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_get_ethernet_cable_state", ret, CONNECTION_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_connection_get_current_profile_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the name of the default profile.
 * @scenario  		Invoking connection_get_current_profile with valid parameter.
 */
int utc_connection_get_current_profile_p(void)
{
	int ret = connection_get_current_profile(connection, &profile_temp);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_get_current_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_get_current_profile", ret, CONNECTION_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_connection_get_current_profile_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_get_current_profile should fail with invalid parameter.
 * @scenario  		Verify connection_get_current_profile by passing invalid parameter.
 */
int utc_connection_get_current_profile_n(void)
{
	int ret;
	connection_profile_h profile = NULL;

	if (all_features_not_supported) {
		ret = connection_get_current_profile(connection, NULL);
		CHECK_RETURN("connection_get_current_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_current_profile(NULL, NULL);
	CHECK_RETURN("connection_get_current_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_current_profile(connection, NULL);
	CHECK_RETURN("connection_get_current_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_current_profile(NULL, &profile);
	CHECK_RETURN("connection_get_current_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_get_default_cellular_service_profile_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the default profile which provides the given cellular service.
 * @scenario  		Invoking connection_get_default_cellular_service_profile with valid parameter.
 */
int utc_connection_get_default_cellular_service_profile_p(void)
{
	connection_profile_h profile = NULL;

	if(!telephony_supported) {
		int ret = connection_get_default_cellular_service_profile(connection, CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET, &profile);
		CHECK_RETURN("connection_get_default_cellular_service_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	connection_cellular_state_e state;
	int ret = connection_get_cellular_state(connection, &state);
	PRINT_RETURN("connection_get_cellular_state", ret);
	if (state == CONNECTION_CELLULAR_STATE_OUT_OF_SERVICE)
		return 0;

	int service_type = CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET;
	ret = connection_get_default_cellular_service_profile(connection, service_type, &profile);
	CHECK_RETURN("connection_get_default_cellular_service_profile", ret, CONNECTION_ERROR_NONE);

	service_type = CONNECTION_CELLULAR_SERVICE_TYPE_MMS;
	ret = connection_get_default_cellular_service_profile(connection, service_type, &profile);
	CHECK_RETURN("connection_get_default_cellular_service_profile", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_get_default_cellular_service_profile_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_get_default_cellular_service_profile should fail with invalid parameter.
 * @scenario  		Verify connection_get_default_cellular_service_profile by passing invalid parameter.
 */
int utc_connection_get_default_cellular_service_profile_n(void)
{
	connection_profile_h profile = NULL;

	if (!telephony_supported) {
		int ret = connection_get_default_cellular_service_profile(NULL, CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET, NULL);
		CHECK_RETURN("connection_get_default_cellular_service_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int service_type = CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET;
	int ret = connection_get_default_cellular_service_profile(NULL, service_type, NULL);
	CHECK_RETURN("connection_get_default_cellular_service_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	service_type = CONNECTION_CELLULAR_SERVICE_TYPE_MMS;
	ret = connection_get_default_cellular_service_profile(connection, service_type, NULL);
	CHECK_RETURN("connection_get_default_cellular_service_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	service_type = CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET;
	ret = connection_get_default_cellular_service_profile(NULL, service_type, &profile);
	CHECK_RETURN("connection_get_default_cellular_service_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;

}

/**
 * @testcase		utc_connection_set_default_cellular_service_profile_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the default profile which provides the given cellular service.
 * @scenario  		Invoking connection_set_default_cellular_service_profile with valid parameter.
 */
int utc_connection_set_default_cellular_service_profile_p(void)
{
	int service_type = CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET;

	if (!telephony_supported) {
		int ret = connection_set_default_cellular_service_profile(connection, service_type, profile_cellular);
		CHECK_RETURN("connection_set_default_cellular_service_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	connection_cellular_state_e state;
	int ret = connection_get_cellular_state(connection, &state);
	PRINT_RETURN("connection_get_cellular_state", ret);
	if (state == CONNECTION_CELLULAR_STATE_OUT_OF_SERVICE)
		return 0;

	ret = connection_get_default_cellular_service_profile(connection, service_type, &profile_cellular);
	CHECK_RETURN("connection_set_default_cellular_service_profile", ret, CONNECTION_ERROR_NONE);

	ret = connection_set_default_cellular_service_profile(connection, service_type, profile_cellular);
	CHECK_RETURN("connection_set_default_cellular_service_profile", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_set_default_cellular_service_profile_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_set_default_cellular_service_profile should fail with invalid parameter.
 * @scenario  		Verify connection_set_default_cellular_service_profile by passing invalid parameter.
 */
int utc_connection_set_default_cellular_service_profile_n(void)
{
	int service_type = CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET;

	if (!telephony_supported) {
		int ret = connection_set_default_cellular_service_profile(NULL, service_type, NULL);
		CHECK_RETURN("connection_set_default_cellular_service_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int ret = connection_set_default_cellular_service_profile(NULL, service_type, NULL);
	CHECK_RETURN("connection_set_default_cellular_service_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_set_default_cellular_service_profile(connection, service_type, NULL);
	CHECK_RETURN("connection_set_default_cellular_service_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	service_type = CONNECTION_CELLULAR_SERVICE_TYPE_TETHERING;
	ret = connection_get_default_cellular_service_profile(NULL, service_type, profile_cellular);
	CHECK_RETURN("connection_set_default_cellular_service_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_set_default_cellular_service_profile_async_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the default profile which provides the given cellular service, asynchronously.
 * @scenario  		Invoking connection_set_default_cellular_service_profile_async with valid parameter.
 */
int utc_connection_set_default_cellular_service_profile_async_p(void)
{
	int service_type = CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET;

	if (!telephony_supported) {
		int ret = connection_set_default_cellular_service_profile_async(connection, service_type, NULL, test_connection_set_default_callback, NULL);
		CHECK_RETURN("connection_set_default_cellular_service_profile_async", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	connection_cellular_state_e state;
	int ret = connection_get_cellular_state(connection, &state);
	PRINT_RETURN("connection_get_cellular_state", ret);
	if (state == CONNECTION_CELLULAR_STATE_OUT_OF_SERVICE)
		return 0;

	ret = connection_get_default_cellular_service_profile(connection, service_type, &profile_cellular);
	CHECK_RETURN("connection_set_default_cellular_service_profile_async", ret, CONNECTION_ERROR_NONE);

	ret = connection_set_default_cellular_service_profile_async(connection, service_type, profile_cellular, test_connection_set_default_callback, NULL);
	RUN_GMAIN_LOOP;
	CHECK_RETURN("connection_set_default_cellular_service_profile_async", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_set_default_cellular_service_profile_async_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_set_default_cellular_service_profile_async should fail with invalid parameter.
 * @scenario  		Verify connection_set_default_cellular_service_profile_async by passing invalid parameter.
 */
int utc_connection_set_default_cellular_service_profile_async_n(void)
{
	int service_type = CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET;

	if (!telephony_supported) {
		int ret = connection_set_default_cellular_service_profile_async(NULL, service_type, NULL, NULL, NULL);
		CHECK_RETURN("connection_set_default_cellular_service_profile_async", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int ret = connection_set_default_cellular_service_profile_async(NULL, service_type, NULL, NULL, NULL);
	CHECK_RETURN("connection_set_default_cellular_service_profile_async", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_set_default_cellular_service_profile_async(connection, service_type, profile_cellular, NULL, NULL);
	CHECK_RETURN("connection_set_default_cellular_service_profile_async", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_set_default_cellular_service_profile_async(connection, service_type, NULL, test_connection_set_default_callback, NULL);
	CHECK_RETURN("connection_set_default_cellular_service_profile_async", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	service_type = CONNECTION_CELLULAR_SERVICE_TYPE_TETHERING;
	ret = connection_set_default_cellular_service_profile_async(NULL, service_type, profile_cellular, test_connection_set_default_callback, NULL);
	CHECK_RETURN("connection_set_default_cellular_service_profile_async", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_set_type_changed_cb_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_set_type_changed_cb should fail with invalid parameter.
 * @scenario  		Verify connection_set_type_changed_cb by passing invalid parameter.
 */
int utc_connection_set_type_changed_cb_n(void)
{
	int ret;

	if (all_features_not_supported) {
		ret = connection_set_type_changed_cb(connection, NULL, NULL);
		CHECK_RETURN("connection_set_type_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_set_type_changed_cb(NULL, NULL, NULL);
	CHECK_RETURN("connection_set_type_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_set_type_changed_cb(NULL, test_network_state_changed_cb, NULL);
	CHECK_RETURN("connection_set_type_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_set_type_changed_cb(connection, NULL, NULL);
	CHECK_RETURN("connection_set_type_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_set_type_changed_cb_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Registers the callback that is called when the type of the current connection is changed.
 * @scenario  		Invoking connection_set_type_changed_cb with valid parameter.
 */
int utc_connection_set_type_changed_cb_p(void)
{
	int ret;

	if (all_features_not_supported) {
		ret = connection_set_type_changed_cb(connection, NULL, NULL);
		CHECK_RETURN("connection_set_type_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_set_type_changed_cb(connection, test_network_state_changed_cb, NULL);
	RUN_GMAIN_LOOP;
	CHECK_RETURN("connection_set_type_changed_cb", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_unset_type_changed_cb_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_unset_type_changed_cb should fail with invalid parameter.
 * @scenario  		Verify connection_unset_type_changed_cb by passing invalid parameter.
 */
int utc_connection_unset_type_changed_cb_n(void)
{
	int ret = connection_unset_type_changed_cb(NULL);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_unset_type_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_unset_type_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_connection_unset_type_changed_cb_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Unregisters the callback that is called when the type of current connection is changed.
 * @scenario  		Invoking connection_unset_type_changed_cb with valid parameter.
 */
int utc_connection_unset_type_changed_cb_p(void)
{
	int ret = connection_unset_type_changed_cb(connection);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_unset_type_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_unset_type_changed_cb", ret, CONNECTION_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_connection_set_ip_address_changed_cb_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_set_ip_address_changed_cb should fail with invalid parameter.
 * @scenario  		Verify connection_set_ip_address_changed_cb by passing invalid parameter.
 */
int utc_connection_set_ip_address_changed_cb_n(void)
{
	int ret;

	if (all_features_not_supported) {
		ret = connection_set_ip_address_changed_cb(connection, NULL, NULL);
		CHECK_RETURN("connection_set_ip_address_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_set_ip_address_changed_cb(NULL, NULL, NULL);
	CHECK_RETURN("connection_set_ip_address_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_set_ip_address_changed_cb(NULL, test_ip_address_changed_cb, NULL);
	CHECK_RETURN("connection_set_ip_address_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_set_ip_address_changed_cb(connection, NULL, NULL);
	CHECK_RETURN("connection_set_ip_address_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_set_ip_address_changed_cb_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Registers the callback that is called when the IP address is changed.
 * @scenario  		Invoking connection_set_ip_address_changed_cb with valid parameter.
 */
int utc_connection_set_ip_address_changed_cb_p(void)
{
	int ret;

	if (all_features_not_supported) {
		ret = connection_set_ip_address_changed_cb(connection, NULL, NULL);
		CHECK_RETURN("connection_set_ip_address_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_set_ip_address_changed_cb(connection, test_ip_address_changed_cb, NULL);
	RUN_GMAIN_LOOP;
	CHECK_RETURN("connection_set_ip_address_changed_cb", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_unset_ip_address_changed_cb_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_unset_ip_address_changed_cb should fail with invalid parameter.
 * @scenario  		Verify connection_unset_ip_address_changed_cb by passing invalid parameter.
 */
int utc_connection_unset_ip_address_changed_cb_n(void)
{
	int ret = connection_unset_ip_address_changed_cb(NULL);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_set_ip_address_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_set_ip_address_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_connection_unset_ip_address_changed_cb_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Unregisters the callback that is called when the IP address is changed.
 * @scenario  		Invoking connection_unset_ip_address_changed_cb with valid parameter.
 */
int utc_connection_unset_ip_address_changed_cb_p(void)
{
	int ret = connection_unset_ip_address_changed_cb(connection);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_unset_ip_address_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_unset_ip_address_changed_cb", ret, CONNECTION_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_connection_set_proxy_address_changed_cb_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_set_proxy_address_changed_cb should fail with invalid parameter.
 * @scenario  		Verify connection_set_proxy_address_changed_cb by passing invalid parameter.
 */
int utc_connection_set_proxy_address_changed_cb_n(void)
{
	int ret;

	if (all_features_not_supported) {
		ret = connection_set_proxy_address_changed_cb(connection, NULL, NULL);
		CHECK_RETURN("connection_set_proxy_address_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_set_proxy_address_changed_cb(NULL, NULL, NULL);
	CHECK_RETURN("connection_set_proxy_address_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_set_proxy_address_changed_cb(NULL, test_proxy_address_changed_cb, NULL);
	CHECK_RETURN("connection_set_proxy_address_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_set_proxy_address_changed_cb(connection, NULL, NULL);
	CHECK_RETURN("connection_set_proxy_address_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_set_proxy_address_changed_cb_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Registers the callback that is called when the proxy address is changed.
 * @scenario  		Invoking connection_set_proxy_address_changed_cb with valid parameter.
 */
int utc_connection_set_proxy_address_changed_cb_p(void)
{
	int ret;

	if (all_features_not_supported) {
		ret = connection_set_proxy_address_changed_cb(connection, NULL, NULL);
		CHECK_RETURN("connection_set_proxy_address_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_set_proxy_address_changed_cb(connection, test_proxy_address_changed_cb, NULL);
	RUN_GMAIN_LOOP;
	CHECK_RETURN("connection_set_proxy_address_changed_cb", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_unset_proxy_address_changed_cb_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_unset_proxy_address_changed_cb should fail with invalid parameter.
 * @scenario  		Verify connection_unset_proxy_address_changed_cb by passing invalid parameter.
 */
int utc_connection_unset_proxy_address_changed_cb_n(void)
{
    int ret = connection_unset_proxy_address_changed_cb(NULL);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_unset_proxy_address_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_unset_proxy_address_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_connection_unset_proxy_address_changed_cb_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Unregisters the callback that is called when the proxy address is changed.
 * @scenario  		Invoking connection_unset_proxy_address_changed_cb with valid parameter.
 */
int utc_connection_unset_proxy_address_changed_cb_p(void)
{
	int ret = connection_unset_proxy_address_changed_cb(connection);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_unset_proxy_address_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_unset_proxy_address_changed_cb", ret, CONNECTION_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_connection_get_statistics_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the statistics information.
 * @scenario  		Invoking connection_get_statistics with valid parameter.
 */
int utc_connection_get_statistics_p(void)
{
	long long stat;

	if (telephony_supported) {
		int ret = connection_get_statistics(connection, CONNECTION_TYPE_CELLULAR, CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_NONE);
		ret = connection_get_statistics(connection, CONNECTION_TYPE_CELLULAR, CONNECTION_STATISTICS_TYPE_LAST_RECEIVED_DATA, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_NONE);
		ret = connection_get_statistics(connection, CONNECTION_TYPE_CELLULAR, CONNECTION_STATISTICS_TYPE_TOTAL_SENT_DATA, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_NONE);
		ret = connection_get_statistics(connection, CONNECTION_TYPE_CELLULAR, CONNECTION_STATISTICS_TYPE_TOTAL_RECEIVED_DATA, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_get_statistics(connection, CONNECTION_TYPE_CELLULAR, CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	if (wifi_supported) {
		int ret = connection_get_statistics(connection, CONNECTION_TYPE_WIFI, CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_NONE);
		ret = connection_get_statistics(connection, CONNECTION_TYPE_WIFI, CONNECTION_STATISTICS_TYPE_LAST_RECEIVED_DATA, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_NONE);
		ret = connection_get_statistics(connection, CONNECTION_TYPE_WIFI, CONNECTION_STATISTICS_TYPE_TOTAL_SENT_DATA, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_NONE);
		ret = connection_get_statistics(connection, CONNECTION_TYPE_WIFI, CONNECTION_STATISTICS_TYPE_TOTAL_RECEIVED_DATA, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_get_statistics(connection, CONNECTION_TYPE_WIFI, CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_get_statistics_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_get_statistics should fail with invalid parameter.
 * @scenario  		Verify connection_get_statistics by passing invalid parameter.
 */
int utc_connection_get_statistics_n(void)
{
	int ret;
	long long stat;

	if (telephony_supported == false && wifi_supported == false){
		ret = connection_get_statistics(NULL, -1, -1, NULL);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_statistics(NULL, -1, -1, NULL);
	CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_statistics(connection, -1, CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA, &stat);
	CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_statistics(connection, -1, -1, &stat);
	CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	if (telephony_supported) {
		ret = connection_get_statistics(connection, CONNECTION_TYPE_CELLULAR, -1, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_get_statistics(connection, CONNECTION_TYPE_CELLULAR, CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA, NULL);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_get_statistics(connection, CONNECTION_TYPE_CELLULAR, -1, NULL);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		ret = connection_get_statistics(connection, CONNECTION_TYPE_CELLULAR, -1, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	if (wifi_supported) {
		ret = connection_get_statistics(connection, CONNECTION_TYPE_WIFI, -1, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_get_statistics(connection, CONNECTION_TYPE_WIFI, CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA, NULL);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_get_statistics(connection, CONNECTION_TYPE_WIFI, -1, NULL);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		ret = connection_get_statistics(connection, CONNECTION_TYPE_WIFI, -1, &stat);
		CHECK_RETURN("connection_get_statistics", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_reset_statistics_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Resets the statistics information.
 * @scenario  		Invoking connection_reset_statistics with valid parameter.
 */
int utc_connection_reset_statistics_p(void)
{
	int ret = 0;
	if (telephony_supported) {
		ret = connection_reset_statistics(connection, CONNECTION_TYPE_CELLULAR, CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA);
		CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_NONE);
		ret = connection_reset_statistics(connection, CONNECTION_TYPE_CELLULAR, CONNECTION_STATISTICS_TYPE_LAST_RECEIVED_DATA);
		CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_NONE);
		ret = connection_reset_statistics(connection, CONNECTION_TYPE_CELLULAR, CONNECTION_STATISTICS_TYPE_TOTAL_SENT_DATA);
		CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_NONE);
		ret = connection_reset_statistics(connection, CONNECTION_TYPE_CELLULAR, CONNECTION_STATISTICS_TYPE_TOTAL_RECEIVED_DATA);
		CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_NONE);
	} else {
		ret = connection_reset_statistics(connection, CONNECTION_TYPE_CELLULAR, CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA);
		CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	if (wifi_supported) {
		ret = connection_reset_statistics(connection, CONNECTION_TYPE_WIFI, CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA);
		CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_NONE);
		ret = connection_reset_statistics(connection, CONNECTION_TYPE_WIFI, CONNECTION_STATISTICS_TYPE_LAST_RECEIVED_DATA);
		CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_NONE);
		ret = connection_reset_statistics(connection, CONNECTION_TYPE_WIFI, CONNECTION_STATISTICS_TYPE_TOTAL_SENT_DATA);
		CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_NONE);
		ret = connection_reset_statistics(connection, CONNECTION_TYPE_WIFI, CONNECTION_STATISTICS_TYPE_TOTAL_RECEIVED_DATA);
		CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_NONE);
	} else {
		ret = connection_reset_statistics(connection, CONNECTION_TYPE_WIFI, CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA);
		CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_reset_statistics_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_reset_statistics should fail with invalid parameter.
 * @scenario  		Verify connection_reset_statistics by passing invalid parameter.
 */
int utc_connection_reset_statistics_n(void)
{
	int ret;
	if (telephony_supported == false && wifi_supported == false) {
		ret = connection_reset_statistics(NULL, -1, -1);
		CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_reset_statistics(NULL, -1, -1);
	CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_reset_statistics(connection, -1, CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA);
	CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	if (telephony_supported) {
		ret = connection_reset_statistics(connection, CONNECTION_TYPE_CELLULAR, -1);
		CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		ret = connection_reset_statistics(connection, CONNECTION_TYPE_CELLULAR, -1);
		CHECK_RETURN("connection_reset_statistics", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_add_route_n1
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_add_route should fail with invalid parameter.
 * @scenario  		Verify connection_add_route by passing invalid parameter.
 */
int utc_connection_add_route_n1(void)
{
	int ret;

	if (all_features_not_supported) {
		ret = connection_add_route(connection, NULL, NULL);
		CHECK_RETURN("connection_add_route", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_add_route(NULL, NULL, NULL);
	CHECK_RETURN("connection_add_route", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_add_route(NULL, "pdp0", "192.168.129.3");
	CHECK_RETURN("connection_add_route", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_add_route(connection, "pdp0", NULL);
	CHECK_RETURN("connection_add_route", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_add_route(connection, NULL, "192.168.129.3");
	CHECK_RETURN("connection_add_route", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_add_route_n2
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Adds a IPv4 route to the routing table.You can get the @a interface_name from connection_profile_get_network_interface_name() of opened profile.
 * @scenario  		Invoking connection_add_route with valid parameter.
 */
int utc_connection_add_route_n2(void)
{
	int ret;
	char* interface_name = NULL;

	if (all_features_not_supported) {
		ret = connection_add_route(connection, interface_name, "192.168.129.3");
		CHECK_RETURN("connection_add_route", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_current_profile(connection, &profile_temp);
	PRINT_RETURN("connection_get_current_profile", ret);

	ret = connection_profile_get_network_interface_name(profile_temp, &interface_name);
	PRINT_RETURN("connection_get_current_profile", ret);

	ret = connection_add_route(connection, interface_name, "192.168.129.3");
	FREE_RESOURCE(interface_name);
	CHECK_RETURN("connection_add_route", ret, CONNECTION_ERROR_PERMISSION_DENIED);

	return 0;
}

/**
 * @testcase		utc_connection_remove_route_n1
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_remove_route should fail with invalid parameter.
 * @scenario  		Verify connection_remove_route by passing invalid parameter.
 */
int utc_connection_remove_route_n1(void)
{
	int ret;

	if (all_features_not_supported) {
		ret = connection_remove_route(NULL, NULL, NULL);
		CHECK_RETURN("connection_remove_route", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_remove_route(NULL, NULL, NULL);
	CHECK_RETURN("connection_remove_route", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_remove_route(NULL, "pdp0", "192.168.129.3");
	CHECK_RETURN("connection_remove_route", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_remove_route(connection, "pdp0", NULL);
	CHECK_RETURN("connection_remove_route", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_add_route(connection, NULL, "192.168.129.3");
	CHECK_RETURN("connection_remove_route", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_remove_route_n2
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Removes a IPv4 route from the routing table.get the @a interface_name from connection_profile_get_network_interface_name() of opened profile.
 * @scenario  		Invoking connection_remove_route with valid parameter.
 */
int utc_connection_remove_route_n2(void)
{
	int ret;
	char* interface_name = NULL;

	if (all_features_not_supported) {
		ret = connection_remove_route(connection, interface_name, "192.168.129.3");
		CHECK_RETURN("connection_remove_route", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_current_profile(connection, &profile_temp);
	PRINT_RETURN("connection_get_current_profile", ret);

	ret = connection_profile_get_network_interface_name(profile_temp, &interface_name);
	PRINT_RETURN("connection_profile_get_network_interface_name", ret);

	ret = connection_remove_route(connection, interface_name, "192.168.129.3");
	FREE_RESOURCE(interface_name);
	CHECK_RETURN("connection_remove_route", ret, CONNECTION_ERROR_PERMISSION_DENIED);

	return 0;
}

/**
 * @testcase		utc_connection_add_route_ipv6_n1
 * @since_tizen 	2.3.1
 * @type		Negative
 * @description		connection_add_route_ipv6 should fail with invalid parameter.
 * @scenario  		Verify connection_add_route_ipv6 by passing invalid parameter.
 */
int utc_connection_add_route_ipv6_n1(void)
{
	int ret;

	if (telephony_supported == false && wifi_supported == false && ethernet_supported == false) {
		ret = connection_add_route_ipv6(NULL, NULL, NULL, NULL);
		CHECK_RETURN("connection_add_route_ipv6", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_add_route_ipv6(NULL, NULL, NULL, NULL);
	CHECK_RETURN("connection_add_route_ipv6", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_add_route_ipv6(connection, NULL, "2001:db8:1:0::1", "fe80::");
	CHECK_RETURN("connection_add_route_ipv6", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_add_route_ipv6(connection, NULL, NULL, "fe80::");
	CHECK_RETURN("connection_add_route_ipv6", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_add_route_ipv6_n2
 * @since_tizen 	2.3.1
 * @type		Positive
 * @description		Adds a IPv6 route to the routing table.
 * @scenario  		Invoking connection_add_route_ipv6 with valid parameter.
 */
int utc_connection_add_route_ipv6_n2(void)
{
	int ret;
	char* interface_name = NULL;

	if (telephony_supported == false && wifi_supported == false && ethernet_supported == false) {
		ret = connection_add_route_ipv6(connection, interface_name, "2001:db8:1:0::1", "fe80::");
		CHECK_RETURN("connection_add_route_ipv6", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_current_profile(connection, &profile_temp);
	PRINT_RETURN("connection_get_current_profile", ret);
	ret = connection_profile_get_network_interface_name(profile_temp, &interface_name);
	PRINT_RETURN("connection_profile_get_network_interface_name", ret);

	ret = connection_add_route_ipv6(connection, interface_name, "2001:db8:1:0::1", "fe80::");
	FREE_RESOURCE(interface_name);
	CHECK_RETURN("connection_add_route_ipv6", ret, CONNECTION_ERROR_PERMISSION_DENIED);

	return 0;
}

/**
 * @testcase		utc_connection_remove_route_ipv6_n1
 * @since_tizen 	2.3.1
 * @type		Negative
 * @description		connection_add_route_ipv6 should fail with invalid parameter.
 * @scenario  		Verify connection_add_route_ipv6 by passing invalid parameter.
 */
int utc_connection_remove_route_ipv6_n1(void)
{
	int ret;

	if (all_features_not_supported) {
		ret = connection_remove_route_ipv6(NULL, NULL, NULL, NULL);
		CHECK_RETURN("connection_remove_route_ipv6", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_remove_route_ipv6(NULL, NULL, NULL, NULL);
	CHECK_RETURN("connection_remove_route_ipv6", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_remove_route_ipv6(connection, NULL, "2001:db8:1:0::1", "fe80::");
	CHECK_RETURN("connection_remove_route_ipv6", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_remove_route_ipv6(connection, NULL, NULL, "fe80::");
	CHECK_RETURN("connection_remove_route_ipv6", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_remove_route_ipv6_n2
 * @since_tizen 	2.3.1
 * @type		Positive
 * @description		Removes a IPV6 route from the routing table.
 * @scenario  		Invoking connection_remove_route_ipv6 with valid parameter.
 */
int utc_connection_remove_route_ipv6_n2(void)
{
	int ret;
	char* interface_name = NULL;

	if (telephony_supported == false && wifi_supported == false && ethernet_supported == false) {
		ret = connection_remove_route_ipv6(connection, interface_name, "2001:db8:1:0::1", "fe80::");
		FREE_RESOURCE(interface_name);
		CHECK_RETURN("connection_remove_route_ipv6", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_current_profile(connection, &profile_temp);
	PRINT_RETURN("connection_get_current_profile", ret);
	ret = connection_profile_get_network_interface_name(profile_temp, &interface_name);
	PRINT_RETURN("connection_profile_get_network_interface_name", ret);

	ret = connection_remove_route_ipv6(connection, interface_name, "2001:db8:1:0::1", "fe80::");
	FREE_RESOURCE(interface_name);
	CHECK_RETURN("connection_remove_route_ipv6", ret, CONNECTION_ERROR_PERMISSION_DENIED);

	return 0;
}

/**
 * @testcase        utc_connection_add_route_entry_n1
 * @since_tizen     4.0
 * @type            Negative
 * @description     connection_add_route_entry should fail with invalid parameter.
 * @scenario  		Verify connection_add_route_entry by passing invalid parameter.
 */
int utc_connection_add_route_entry_n1(void)
{
	int ret;

	if (telephony_supported == false && wifi_supported == false && ethernet_supported == false) {
		ret = connection_add_route_entry(NULL, -1, NULL, NULL, NULL);
		CHECK_RETURN("connection_add_route_entry", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_add_route_entry(NULL, -1, NULL, NULL, NULL);
	CHECK_RETURN("connection_add_route_entry", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_add_route_entry(connection, -1, NULL, "2001:db8:1:0::1", "fe80::");
	CHECK_RETURN("connection_add_route_entry", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_add_route_entry(connection, -1, NULL, NULL, "fe80::");
	CHECK_RETURN("connection_add_route_entry", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_connection_add_route_entry_n2
 * @since_tizen     4.0
 * @type            Positive
 * @description     Adds a route to the routing table.
 * @scenario  		Invoking connection_add_route_entry with valid parameter.
 */
int utc_connection_add_route_entry_n2(void)
{
	int ret;
	char* interface_name = NULL;

	if (telephony_supported == false && wifi_supported == false && ethernet_supported == false) {
		ret = connection_add_route_entry(connection, CONNECTION_ADDRESS_FAMILY_IPV6, interface_name, "2001:db8:1:0::1", "fe80::");
		CHECK_RETURN("connection_add_route_entry", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_current_profile(connection, &profile_temp);
	PRINT_RETURN("connection_get_current_profile", ret);
	connection_profile_get_network_interface_name(profile_temp, &interface_name);
	PRINT_RETURN("connection_profile_get_network_interface_name", ret);

	ret = connection_add_route_entry(connection, CONNECTION_ADDRESS_FAMILY_IPV6, interface_name, "2001:db8:1:0::1", "fe80::");
	FREE_RESOURCE(interface_name);
	CHECK_RETURN("connection_add_route_entry", ret, CONNECTION_ERROR_PERMISSION_DENIED);

	return 0;
}

/**
 * @testcase        utc_connection_remove_route_entry_n1
 * @since_tizen     4.0
 * @type            Negative
 * @description     connection_add_route_entry should fail with invalid parameter.
 * @scenario        Verify connection_add_route_entry by passing invalid parameter.
 */
int utc_connection_remove_route_entry_n1(void)
{
	int ret;

	if (all_features_not_supported) {
		ret = connection_remove_route_entry(NULL, -1, NULL, NULL, NULL);
		CHECK_RETURN("connection_remove_route_entry", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_remove_route_entry(NULL, -1, NULL, NULL, NULL);
	CHECK_RETURN("connection_remove_route_entry", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_remove_route_entry(connection, -1, NULL, "2001:db8:1:0::1", "fe80::");
	CHECK_RETURN("connection_remove_route_entry", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	ret = connection_remove_route_entry(connection, -1, NULL, NULL, "fe80::");
	CHECK_RETURN("connection_remove_route_entry", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_connection_remove_route_entry_n2
 * @since_tizen 	4.0
 * @type            Positive
 * @description     Removes a route from the routing table.
 * @scenario        Invoking connection_remove_route_entry with valid parameter.
 */
int utc_connection_remove_route_entry_n2(void)
{
	int ret;
	char* interface_name = NULL;

	if (telephony_supported == false && wifi_supported == false && ethernet_supported == false) {
		ret = connection_remove_route_entry(connection, CONNECTION_ADDRESS_FAMILY_IPV6, interface_name, "2001:db8:1:0::1", "fe80::");
		FREE_RESOURCE(interface_name);
		CHECK_RETURN("connection_remove_route_entry", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_current_profile(connection, &profile_temp);
	PRINT_RETURN("connection_get_current_profile", ret);
	connection_profile_get_network_interface_name(profile_temp, &interface_name);
	PRINT_RETURN("connection_profile_get_network_interface_name", ret);

	ret = connection_remove_route_entry(connection, CONNECTION_ADDRESS_FAMILY_IPV6, interface_name, "2001:db8:1:0::1", "fe80::");
	FREE_RESOURCE(interface_name);
	CHECK_RETURN("connection_remove_route_entry", ret, CONNECTION_ERROR_PERMISSION_DENIED);

	return 0;
}

/**
 * @testcase		utc_connection_get_profile_iterator_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_get_profile_iterator should fail with invalid parameter.
 * @scenario  		Verify connection_get_profile_iterator by passing invalid parameter.
 */
int utc_connection_get_profile_iterator_n(void)
{
	int ret;
	connection_profile_iterator_h profile_iter;

	if (all_features_not_supported) {
		ret = connection_get_profile_iterator(connection, 3, &profile_iter);
		CHECK_RETURN("connection_get_profile_iterator", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_profile_iterator(NULL, 3, NULL);
	CHECK_RETURN("connection_get_profile_iterator", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_profile_iterator(NULL, CONNECTION_ITERATOR_TYPE_CONNECTED, &profile_iter);
	CHECK_RETURN("connection_get_profile_iterator", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_get_profile_iterator(connection, 3, &profile_iter);
	CHECK_RETURN("connection_get_profile_iterator", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_get_profile_iterator_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets a profiles iterator.
 * @scenario  		Invoking connection_get_profile_iterator with valid parameter.
 */
int utc_connection_get_profile_iterator_p(void)
{
	int ret;
	connection_profile_iterator_h profile_iter;

	if (all_features_not_supported) {
		ret = connection_get_profile_iterator(connection, CONNECTION_ITERATOR_TYPE_CONNECTED, &profile_iter);
		CHECK_RETURN("connection_get_profile_iterator", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_profile_iterator(connection, CONNECTION_ITERATOR_TYPE_CONNECTED, &profile_iter);
	CHECK_RETURN("connection_get_profile_iterator", ret, CONNECTION_ERROR_NONE);
	ret = connection_get_profile_iterator(connection, CONNECTION_ITERATOR_TYPE_REGISTERED, &profile_iter);
	CHECK_RETURN("connection_get_profile_iterator", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_destroy_profile_iterator_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_destroy_profile_iterator should fail with invalid parameter.
 * @scenario  		Verify connection_destroy_profile_iterator by passing invalid parameter.
 */
int utc_connection_destroy_profile_iterator_n(void)
{
	int ret = connection_destroy_profile_iterator(NULL);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_destroy_profile_iterator", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_destroy_profile_iterator", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_connection_destroy_profile_iterator_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Destroys a profiles iterator.
 * @scenario  		Invoking connection_destroy_profile_iterator with valid parameter.
 */
int utc_connection_destroy_profile_iterator_p(void)
{
	int ret;
	connection_profile_iterator_h profile_iter = NULL;

	if (all_features_not_supported) {
		ret = connection_destroy_profile_iterator(profile_iter);
		CHECK_RETURN("connection_destroy_profile_iterator", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_profile_iterator(connection, CONNECTION_ITERATOR_TYPE_CONNECTED, &profile_iter);
	PRINT_RETURN("connection_get_profile_iterator", ret);

	ret = connection_destroy_profile_iterator(profile_iter);
	CHECK_RETURN("connection_destroy_profile_iterator", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_iterator_has_next_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_iterator_has_next should fail with invalid parameter.
 * @scenario  		Verify connection_profile_iterator_has_next by passing invalid parameter.
 */
int utc_connection_profile_iterator_has_next_n(void)
{
	int ret = connection_profile_iterator_has_next(NULL);
	if (all_features_not_supported) {
		CHECK_RETURN("connection_profile_iterator_has_next", get_last_result(), CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_profile_iterator_has_next", ret, false);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_iterator_has_next_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Checks whether the next element of a profile iterator exists or not.
 * @scenario  		Invoking connection_profile_iterator_has_next with valid parameter.
 */
int utc_connection_profile_iterator_has_next_p(void)
{
	int ret;
	connection_profile_iterator_h profile_iter = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_iterator_has_next(profile_iter);
		CHECK_RETURN("connection_profile_iterator_has_next", get_last_result(), CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_profile_iterator(connection, CONNECTION_ITERATOR_TYPE_REGISTERED, &profile_iter);
	PRINT_RETURN("connection_get_profile_iterator", ret);

	ret = connection_profile_iterator_has_next(profile_iter);
	CHECK_RETURN("connection_profile_iterator_has_next", ret, true);

	ret = connection_destroy_profile_iterator(profile_iter);
	PRINT_RETURN("connection_destroy_profile_iterator", ret);

	return 0;
}

/**
 * @testcase		utc_connection_profile_iterator_next_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_iterator_next should fail with invalid parameter.
 * @scenario  		Verify connection_profile_iterator_next by passing invalid parameter.
 */
int utc_connection_profile_iterator_next_n(void)
{
	connection_profile_h profile_h;

	int ret = connection_profile_iterator_next(NULL, &profile_h);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_profile_iterator_next", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_profile_iterator_next", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_iterator_next_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Moves the profile iterator to the next position and gets a profile handle.
 * @scenario  		Invoking connection_profile_iterator_next with valid parameter.
 */
int utc_connection_profile_iterator_next_p(void)
{
	int ret;
	connection_profile_iterator_h profile_iter = NULL;
	connection_profile_h profile_h = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_iterator_next(profile_iter, &profile_h);
		CHECK_RETURN("connection_profile_iterator_next", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_get_profile_iterator(connection, CONNECTION_ITERATOR_TYPE_CONNECTED, &profile_iter);
	PRINT_RETURN("connection_get_profile_iterator", ret);

	while (connection_profile_iterator_has_next(profile_iter)) {
		ret = connection_profile_iterator_next(profile_iter, &profile_h);
		CHECK_RETURN("connection_profile_iterator_next", ret, CONNECTION_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_connection_add_profile_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Creates a profile handle.The profile name, which you get from connection_profile_get_name(), will include the keyword you set.
 * @scenario  		Invoking connection_profile_create with valid parameter.
 */
int utc_connection_add_profile_p(void)
{
    if (telephony_supported) {
        int ret = connection_profile_create(CONNECTION_PROFILE_TYPE_CELLULAR, CUSTOM_PROFILE_NAME, &profile_cellular);
        PRINT_RETURN("connection_profile_create", ret);
        ret = connection_profile_set_cellular_service_type(profile_cellular, CONNECTION_CELLULAR_SERVICE_TYPE_APPLICATION);
        PRINT_RETURN("connection_profile_set_cellular_service_type", ret);

	connection_cellular_state_e state;
	ret = connection_get_cellular_state(connection, &state);
        PRINT_RETURN("connection_get_cellular_state", ret);

	if (state == CONNECTION_CELLULAR_STATE_OUT_OF_SERVICE) {
		fprintf(stderr, "Cellular state is out of service at %s:%d", __FILE__, __LINE__);
		return 0;
	}

        ret = connection_add_profile(connection, profile_cellular);
        CHECK_RETURN("connection_add_profile", ret, CONNECTION_ERROR_NONE);
    } else {
        int ret = connection_add_profile(connection, profile_cellular);
        CHECK_RETURN("connection_add_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
    }
    sleep(5);
    return 0;
}

/**
 * @testcase		utc_connection_add_profile_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_add_profile should fail with invalid parameter.
 * @scenario  		Verify connection_add_profile by passing invalid parameter.
 */
int utc_connection_add_profile_n(void)
{
    connection_profile_h profile = NULL;

    if (telephony_supported) {
        int ret = connection_add_profile(NULL, NULL);
        CHECK_RETURN("connection_add_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
        ret = connection_add_profile(NULL, &profile);
        CHECK_RETURN("connection_add_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
        ret = connection_add_profile(connection, NULL);
        CHECK_RETURN("connection_add_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
    } else {
        int ret = connection_add_profile(NULL, NULL);
        CHECK_RETURN("connection_add_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
    }
    return 0;
}

/**
 * @testcase		utc_connection_close_profile_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Closes a connection of profile.
 * @scenario  		Invoking connection_close_profile with valid parameter.
 */
int utc_connection_close_profile_p(void)
{
	int ret;
	connection_cellular_state_e state;

	if (!telephony_supported && !wifi_supported && !bt_tethering_supported) {
		ret = connection_close_profile(connection, profile_temp, test_connection_closed_callback, NULL);
		CHECK_RETURN("connection_close_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (telephony_supported) {
		ret = connection_get_cellular_state(connection, &state);
		PRINT_RETURN("connection_get_cellular_state", ret);
		if (state == CONNECTION_CELLULAR_STATE_OUT_OF_SERVICE) {
			fprintf(stderr, "Cellular state is out of service at %s:%d", __FILE__, __LINE__);
			return 0;
		}
	}

	ret = connection_get_current_profile(connection, &profile_temp);
	PRINT_RETURN("connection_get_current_profile", ret);

	ret = connection_close_profile(connection, profile_temp, test_connection_closed_callback, NULL);
	PRINT_RETURN("connection_close_profile", ret);
	RUN_GMAIN_LOOP;
	CHECK_RETURN(CALLBACK_RETURN, g_CallbackRet, CONNECTION_ERROR_NONE);

	sleep(10);
	return 0;
}

/**
 * @testcase		utc_connection_close_profile_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_close_profile should fail with invalid parameter.
 * @scenario  		Verify connection_close_profile by passing invalid parameter.
 */
int utc_connection_close_profile_n(void)
{
	int ret;
	connection_profile_h profile = NULL;

	if (!telephony_supported && !wifi_supported && !bt_tethering_supported) {
		ret = connection_close_profile(NULL, NULL, NULL, NULL);
		CHECK_RETURN("connection_close_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_close_profile(NULL, NULL, NULL, NULL);
	CHECK_RETURN("connection_close_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_close_profile(NULL, profile, test_connection_closed_callback, NULL);
	CHECK_RETURN("connection_close_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_close_profile(connection, profile, NULL, NULL);
	CHECK_RETURN("connection_close_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_remove_profile_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Removes an existing profile.
 * @scenario  		Invoking connection_remove_profile with valid parameter.
 */
int utc_connection_remove_profile_p(void)
{
	int ret;
	connection_profile_h profile_h = NULL;

	if (!telephony_supported && !wifi_supported) {
		ret = connection_remove_profile(connection, profile_temp);
		CHECK_RETURN("connection_remove_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (telephony_supported) {
		connection_cellular_state_e state;
		ret = connection_get_cellular_state(connection, &state);
		PRINT_RETURN("connection_get_cellular_state", ret);

		/* Profile Add/Remove method is not allowed when the cellular is in out-of-service state  */
		if (state == CONNECTION_CELLULAR_STATE_OUT_OF_SERVICE) {
			fprintf(stderr, "Cellular state is out of service at %s:%d", __FILE__, __LINE__);
			return 0;
		}

		test_get_profile_by_name(&profile_temp, CUSTOM_PROFILE_NAME);
		ret = connection_remove_profile(connection, profile_temp);
		CHECK_RETURN("connection_remove_profile", ret, CONNECTION_ERROR_NONE);
	} else {
		/**
		 * The purpose of this TC is to remove the added profile in the utc_connection_add_profile_p
		 * and this scenario only works with telephony profile.
		 */
		connection_cellular_state_e state;
		ret = connection_get_cellular_state(connection, &state);
		CHECK_RETURN("connection_get_cellular_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_remove_profile_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_remove_profile should fail with invalid parameter.
 * @scenario  		Verify connection_remove_profile by passing invalid parameter.
 */
int utc_connection_remove_profile_n(void)
{
	int ret;
	connection_profile_h profile = NULL;

	if (!telephony_supported && !wifi_supported) {
		ret = connection_remove_profile(NULL, NULL);
		CHECK_RETURN("connection_remove_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_remove_profile(NULL, NULL);
	CHECK_RETURN("connection_remove_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_remove_profile(NULL, profile);
	CHECK_RETURN("connection_remove_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_remove_profile(connection, NULL);
	CHECK_RETURN("connection_remove_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_update_profile_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Updates an existing profile.
 * @scenario  		Invoking connection_update_profile with valid parameter.
 */
int utc_connection_update_profile_p(void)
{
	connection_profile_h profile_h = NULL;
	int ret = test_get_any_profile(&profile_h);

	if (!telephony_supported && !wifi_supported && !ethernet_supported) {
		ret = connection_update_profile(connection, profile_temp);
		CHECK_RETURN("connection_update_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_h);
	profile_temp = profile_h;

	ret = connection_update_profile(connection, profile_temp);
	CHECK_RETURN("connection_update_profile", ret, CONNECTION_ERROR_NONE);

	sleep(5);
	return 0;
}

/**
 * @testcase		utc_connection_update_profile_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_update_profile should fail with invalid parameter.
 * @scenario  		Verify connection_update_profile by passing invalid parameter.
 */
int utc_connection_update_profile_n(void)
{
	int ret;
	connection_profile_h profile = NULL;

	if (!telephony_supported && !wifi_supported && !ethernet_supported) {
		ret = connection_update_profile(NULL, NULL);
		CHECK_RETURN("connection_update_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_update_profile(NULL, NULL);
	CHECK_RETURN("connection_update_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_update_profile(NULL, profile);
	CHECK_RETURN("connection_update_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_update_profile(connection, NULL);
	CHECK_RETURN("connection_update_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_open_profile_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Opens a connection of profile, asynchronously.
 * @scenario  		Invoking connection_open_profile with valid parameter.
 */
int utc_connection_open_profile_p(void)
{
	connection_profile_h profile_h = NULL;
	int ret = test_get_any_profile(&profile_h);

	if (!telephony_supported && !wifi_supported && !bt_tethering_supported) {
		ret = connection_open_profile(connection, profile_temp, test_connection_opened_callback, NULL);
		CHECK_RETURN("connection_open_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_h);
	profile_temp = profile_h;
	ret = connection_open_profile(connection, profile_temp, test_connection_opened_callback, NULL);
	RUN_GMAIN_LOOP;
	CHECK_RETURN("connection_open_profile", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_open_profile_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_open_profile should fail with invalid parameter.
 * @scenario  		Verify connection_open_profile by passing invalid parameter.
 */
int utc_connection_open_profile_n(void)
{
	int ret;
	connection_profile_h profile = NULL;

	if (!telephony_supported && !wifi_supported && !bt_tethering_supported) {
		ret = connection_open_profile(NULL, NULL, NULL, NULL);
		CHECK_RETURN("connection_open_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_open_profile(NULL, NULL, NULL, NULL);
	CHECK_RETURN("connection_open_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_open_profile(NULL, profile, test_connection_opened_callback, NULL);
	CHECK_RETURN("connection_open_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_open_profile(connection, profile, NULL, NULL);
	CHECK_RETURN("connection_open_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_reset_profile_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Resets the cellular profile.
 * @scenario  		Invoking connection_reset_profile with valid parameter.
 */
int utc_connection_reset_profile_p(void)
{
	if (telephony_supported) {
		int ret = connection_reset_profile(connection, CONNECTION_RESET_DEFAULT_PROFILE,
				0, test_connection_reset_profile_callback, NULL);
		PRINT_RETURN("connection_reset_profile", ret);
		RUN_GMAIN_LOOP;
		CHECK_RETURN(CALLBACK_RETURN, g_CallbackRet, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_reset_profile(connection, CONNECTION_RESET_DEFAULT_PROFILE,
				0, test_connection_reset_profile_callback, NULL);
		RUN_GMAIN_LOOP;
		CHECK_RETURN("connection_reset_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_reset_profile_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_reset_profile should fail with invalid parameter.
 * @scenario  		Verify connection_reset_profile by passing invalid parameter.
 */
int utc_connection_reset_profile_n(void)
{
	if (telephony_supported) {
		int ret = connection_reset_profile(NULL, CONNECTION_RESET_DEFAULT_PROFILE,
				0, test_connection_reset_profile_callback, NULL);
		CHECK_RETURN("connection_reset_profile", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_reset_profile(NULL, CONNECTION_RESET_DEFAULT_PROFILE,
				0, test_connection_reset_profile_callback, NULL);
		CHECK_RETURN("connection_reset_profile", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

    return 0;
}

/**
 * @testcase        utc_connection_foreach_ipv6_address_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Gets IPv6 addresses
 * @scenario        Invoking connection_foreach_ipv6_address with valid parameter.
 */
int utc_connection_foreach_ipv6_address_p(void)
{
	int ret;

	if (telephony_supported) {
		ret = connection_foreach_ipv6_address(connection, CONNECTION_TYPE_CELLULAR,
				test_connection_ipv6_address_callback, NULL);
		CHECK_RETURN("connection_foreach_ipv6_address", ret, CONNECTION_ERROR_NONE);
	} else if (wifi_supported) {
		ret = connection_foreach_ipv6_address(connection, CONNECTION_TYPE_WIFI,
				test_connection_ipv6_address_callback, NULL);
		CHECK_RETURN("connection_foreach_ipv6_address", ret, CONNECTION_ERROR_NONE);
	} else if (ethernet_supported) {
		ret = connection_foreach_ipv6_address(connection, CONNECTION_TYPE_ETHERNET,
				test_connection_ipv6_address_callback, NULL);
		CHECK_RETURN("connection_foreach_ipv6_address", ret, CONNECTION_ERROR_NONE);
	} else {
		ret = connection_foreach_ipv6_address(connection, CONNECTION_TYPE_WIFI,
				test_connection_ipv6_address_callback, NULL);
		CHECK_RETURN("connection_foreach_ipv6_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

    return 0;
}

/**
 * @testcase        utc_connection_foreach_ipv6_address_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     connection_foreach_ipv6_address should fail with invalid parameter.
 * @scenario        Verify connection_foreach_ipv6_address by passing invalid parameter.
 */
int utc_connection_foreach_ipv6_address_n(void)
{
	int ret;

	if (telephony_supported) {
		ret = connection_foreach_ipv6_address(NULL, CONNECTION_TYPE_CELLULAR,
				test_connection_ipv6_address_callback, NULL);
		CHECK_RETURN("connection_foreach_ipv6_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else if (wifi_supported) {
		ret = connection_foreach_ipv6_address(NULL, CONNECTION_TYPE_WIFI,
				test_connection_ipv6_address_callback, NULL);
		CHECK_RETURN("connection_foreach_ipv6_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else if (ethernet_supported) {
		ret = connection_foreach_ipv6_address(NULL, CONNECTION_TYPE_ETHERNET,
				test_connection_ipv6_address_callback, NULL);
		CHECK_RETURN("connection_foreach_ipv6_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		ret = connection_foreach_ipv6_address(NULL, CONNECTION_TYPE_WIFI,
				test_connection_ipv6_address_callback, NULL);
		CHECK_RETURN("connection_foreach_ipv6_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase       utc_connection_set_ethernet_cable_state_changed_cb_n
 * @since_tizen    4.0
 * @type           Negative
 * @description    connection_set_ethernet_cable_state_changed_cb should fail with invalid parameter.
 * @scenario       Verify connection_set_ethernet_cable_state_changed_cb by passing invalid parameter.
 */
int utc_connection_set_ethernet_cable_state_changed_cb_n(void)
{
	int ret;
	if (ethernet_supported == false) {
		ret = connection_set_ethernet_cable_state_changed_cb(NULL, NULL, NULL);
		CHECK_RETURN("connection_set_ethernet_cable_state_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_set_ethernet_cable_state_changed_cb(NULL,
			test_connection_set_default_callback, NULL);
	CHECK_RETURN("connection_set_ethernet_cable_state_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_set_ethernet_cable_state_changed_cb(connection, NULL, NULL);
	CHECK_RETURN("connection_set_ethernet_cable_state_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_connection_unset_ethernet_cable_state_changed_cb_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     connection_unset_ethernet_cable_state_changed_cb should fail with invalid parameter.
 * @scenario        Verify connection_unset_ethernet_cable_state_changed_cb by passing invalid parameter.
 */
int utc_connection_unset_ethernet_cable_state_changed_cb_n(void)
{
	int ret;
	ret = connection_unset_ethernet_cable_state_changed_cb(NULL);

	if (ethernet_supported == false) {
		CHECK_RETURN("connection_unset_ethernet_cable_state_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_unset_ethernet_cable_state_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase       utc_connection_set_internet_state_changed_cb_p
 * @since_tizen    5.5
 * @type           Positive
 * @description    Set internet state changed callback.
 * @scenario       Verify connection_set_internet_state_changed_cb by passing valid parameter.
 */
int utc_connection_set_internet_state_changed_cb_p(void)
{
	int ret;
	ret = connection_set_internet_state_changed_cb(connection,
			       test_connection_internet_state_changed_callback, NULL);

	CHECK_RETURN("connection_set_internet_state_changed_cb", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_connection_set_internet_state_changed_cb_n1
 * @since_tizen     5.5
 * @type            Negative
 * @description     connection_set_internet_state_changed_cb should fail when connection is NULL.
 * @scenario        Verify connection_set_internet_state_changed_cb by passing connection as NULL.
 */
int utc_connection_set_internet_state_changed_cb_n1(void)
{
	int ret;
	ret = connection_set_internet_state_changed_cb(NULL,
			       test_connection_internet_state_changed_callback, NULL);

	CHECK_RETURN("connection_set_internet_state_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase       utc_connection_set_internet_state_changed_cb_n2
 * @since_tizen    5.5
 * @type           Negative
 * @description    connection_set_internet_state_changed_cb should fail when callback is NULL.
 * @scenario       Verify connection_set_internet_state_changed_cb by passing callback as NULL.
 */
int utc_connection_set_internet_state_changed_cb_n2(void)
{
	int ret;
	ret = connection_set_internet_state_changed_cb(connection, NULL, NULL);

	CHECK_RETURN("connection_set_internet_state_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_connection_unset_internet_state_changed_cb_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Unset internet state changed callback.
 * @scenario        Verify connection_unset_internet_state_changed_cb by passing valid parameter.
 */
int utc_connection_unset_internet_state_changed_cb_p(void)
{
	int ret;
	ret = connection_unset_internet_state_changed_cb(connection);

	CHECK_RETURN("connection_unset_internet_state_changed_cb", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_connection_unset_internet_state_changed_cb_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     connection_unset_internet_state_changed_cb should fail when connection is NULL.
 * @scenario        Verify connection_unset_internet_state_changed_cb by passing connection as NULL.
 */
int utc_connection_unset_internet_state_changed_cb_n(void)
{
	int ret;
	ret = connection_unset_internet_state_changed_cb(NULL);

	CHECK_RETURN("connection_unset_internet_state_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_destroy_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Destroys the connection handle.
 * @scenario  		Invoking connection_destroy with valid parameter.
 */
int utc_connection_destroy_p(void)
{
	int ret = connection_destroy(connection);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_destroy", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_destroy", ret, CONNECTION_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_connection_destroy_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_destroy should fail with invalid parameter.
 * @scenario  		Verify connection_destroy by passing invalid parameter.
 */
int utc_connection_destroy_n(void)
{
	int ret = connection_destroy(NULL);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_destroy", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_destroy", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
