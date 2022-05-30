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

#include "utc-wifi-manager-common.h"

//& set: WifiManagerConfig

/**
 * @function		utc_wifi_manager_config_startup
 * @since_tizen		3.0
 * @description		Initializes Wi-Fi.Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_manager_config_startup(void)
{
	g_bFeatureWifi = wifi_manager_check_feature_supported(FEATURE_WIFI);

	int ret = wifi_manager_initialize(&g_hWifi);
	PRINT_RETURN("wifi_manager_initialize", ret);

	ret = wifi_manager_config_create(g_hWifi, WIFI_CONFIG_NAME, WIFI_CONFIG_PASSWORD, WIFI_MANAGER_SECURITY_TYPE_EAP, &g_hWifiConfig);
	PRINT_RETURN("wifi_manager_config_create", ret);
}

/**
 * @function		utc_wifi_manager_config_cleanup
 * @since_tizen		3.0
 * @description		Deinitializes Wi-Fi.Called after each test.
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_manager_config_cleanup(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (g_hWifiConfig) {
		ret = wifi_manager_config_destroy(g_hWifiConfig);
		PRINT_RETURN("wifi_manager_config_destroy", ret);
	}

	ret = wifi_manager_deinitialize(g_hWifi);
	PRINT_RETURN("wifi_manager_deinitialize", ret);
}

/**
 * @testcase		utc_wifi_manager_config_create_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets access point configuration handle.
 * @scenario		Initialize Wi-Fi. Gets access point configuration handle.
 */
int utc_wifi_manager_config_create_p(void)
{
	wifi_manager_config_h config = NULL;
	char name[WIFI_CONFIG_LEN] = WIFI_CONFIG_NAME;
	char passphrase[WIFI_CONFIG_LEN] = WIFI_CONFIG_PASSWORD;
	wifi_manager_security_type_e security_type = WIFI_MANAGER_SECURITY_TYPE_WPA2_PSK;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_create(g_hWifi, name, passphrase, security_type, &config);
		CHECK_RETURN("wifi_manager_config_create", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_create(g_hWifi, name, passphrase, security_type, &config);
	CHECK_RETURN("wifi_manager_config_create", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_destroy(config);
	CHECK_RETURN("wifi_manager_config_destroy", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_create_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets access point configuration handle.
 * @scenario		Gets access point configuration handle with invalid parameters. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_create_n(void)
{
	wifi_manager_config_h config = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_create(NULL, NULL, NULL, -1, &config);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_create", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_create", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_save_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Saves Wi-Fi configuration of access point.
 * @scenario		Initialize Wi-Fi. Create & save access point configuration handle.
 */
int utc_wifi_manager_config_save_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_save(g_hWifi, g_hWifiConfig);
		CHECK_RETURN("wifi_manager_config_save", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_save(g_hWifi, g_hWifiConfig);
	CHECK_RETURN("wifi_manager_config_save", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_remove(g_hWifi, g_hWifiConfig);
	CHECK_RETURN("wifi_manager_config_remove", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_save_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets access point configuration handle.
 * @scenario		Save configuration with invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_save_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_save(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_save", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_save", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_destroy_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Saves Wi-Fi configuration of access point.
 * @scenario		Initialize Wi-Fi. Create & destroy configuration handle.
 */
int utc_wifi_manager_config_destroy_p(void)
{
	wifi_manager_config_h config = NULL;
	char name[WIFI_CONFIG_LEN] = WIFI_CONFIG_NAME;
	char passphrase[WIFI_CONFIG_LEN] = WIFI_CONFIG_PASSWORD;
	wifi_manager_security_type_e security_type = WIFI_MANAGER_SECURITY_TYPE_WPA2_PSK;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_destroy(config);
		CHECK_RETURN("wifi_manager_config_destroy", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_create(g_hWifi, name, passphrase, security_type, &config);
	CHECK_RETURN("wifi_manager_config_create", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_destroy(config);
	CHECK_RETURN("wifi_manager_config_destroy", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_destroy_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets access point configuration handle.
 * @scenario		Destroy configuration with invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_destroy_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_destroy(NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_destroy", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_destroy", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_foreach_configuration_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Load Wi-Fi configuration of access point.
 * @scenario		Initialize Wi-Fi. Create configuration & Load configuration handle.
 */
int utc_wifi_manager_config_foreach_configuration_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_foreach_configuration(g_hWifi, wifi_manager_foreach_configuration_cb, NULL);
		CHECK_RETURN("wifi_manager_config_foreach_configuration", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_save(g_hWifi, g_hWifiConfig);
	CHECK_RETURN("wifi_manager_config_save", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_foreach_configuration(g_hWifi, wifi_manager_foreach_configuration_cb, NULL);
	CHECK_RETURN("wifi_manager_config_foreach_configuration", ret, WIFI_MANAGER_ERROR_NONE);
	CHECK_RETURN(CALLBACK_RETURN, g_nCallbackRet, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_remove(g_hWifi, g_hWifiConfig);
	CHECK_RETURN("wifi_manager_config_remove", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_foreach_configuration_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Load access point configuration handle.
 * @scenario		Load configuration with invalid callback handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_foreach_configuration_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_foreach_configuration(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_foreach_configuration", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_foreach_configuration", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_clone_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Clones the access point configuration handle.
 * @scenario		Initialize Wi-Fi. Create configuration & Clones the access point configuration handle.
 */
int utc_wifi_manager_config_clone_p(void)
{
	wifi_manager_config_h cloned_config = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_clone(g_hWifiConfig, &cloned_config);
		CHECK_RETURN("wifi_manager_config_clone", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_clone(g_hWifiConfig, &cloned_config);
	CHECK_RETURN("wifi_manager_config_clone", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_destroy(cloned_config);
	CHECK_RETURN("wifi_manager_config_destroy", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_clone_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Load access point configuration handle.
 * @scenario		clone configuration with invalid configuration handles. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_clone_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_clone(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_clone", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_clone", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_remove_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Remove Wi-Fi configuration of access point.
 * @scenario		Initialize Wi-Fi. Create configuration & Remove configuration handle.
 */
int utc_wifi_manager_config_remove_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_remove(g_hWifi, g_hWifiConfig);
		CHECK_RETURN("wifi_manager_config_remove", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_save(g_hWifi, g_hWifiConfig);
	CHECK_RETURN("wifi_manager_config_save", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_remove(g_hWifi, g_hWifiConfig);
	CHECK_RETURN("wifi_manager_config_remove", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_remove_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Remove access point configuration handle.
 * @scenario		Remove configuration with invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_remove_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_remove(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_remove", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_remove", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_name_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets the name of access point from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Gets the name of access point from configuration.
 */
int utc_wifi_manager_config_get_name_p(void)
{
	char *config_name = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_name(g_hWifiConfig, &config_name);
	FREE_MEMORY(config_name);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_name", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_name", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_name_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets the name of access point from configuration.
 * @scenario		Gets the name of access point from invalid configuration handles. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_name_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_name(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_name", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_name", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_security_type_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets the security type of access point from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Gets the security type of access point from configuration.
 */
int utc_wifi_manager_config_get_security_type_p(void)
{
	wifi_manager_security_type_e config_security_type;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_security_type(g_hWifiConfig, &config_security_type);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_security_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_security_type", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_security_type_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets the security type of access point from configuration.
 * @scenario		Gets the security type of access point from invalid configuration handles. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_security_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_security_type(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_security_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_security_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_security_type_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Sets access point proxy address configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets access point proxy address configuration.
 */
int utc_wifi_manager_config_set_proxy_address_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_proxy_address(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_CONFIG_PROXY);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_proxy_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_proxy_address", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_proxy_address_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets the security type of access point from configuration.
 * @scenario		Set the proxy address of access point from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_proxy_address_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_proxy_address(NULL, -1, WIFI_CONFIG_PROXY);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_proxy_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_proxy_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_proxy_address_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets the proxy address of access point from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point proxy address configuration.
 */
int utc_wifi_manager_config_get_proxy_address_p(void)
{
	char *proxy;
	wifi_manager_address_family_e address_family = WIFI_MANAGER_ADDRESS_FAMILY_IPV4;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_proxy_address(g_hWifiConfig, &address_family, &proxy);
		CHECK_RETURN("wifi_manager_config_get_proxy_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_proxy_address(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_CONFIG_PROXY);
	CHECK_RETURN("wifi_manager_config_set_proxy_address", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_proxy_address(g_hWifiConfig, &address_family, &proxy);
	FREE_MEMORY(proxy);
	CHECK_RETURN("wifi_manager_config_get_proxy_address", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_proxy_address_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets the proxy address of access point from configuration.
 * @scenario		Gets the proxy address of access point from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_proxy_address_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_proxy_address(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_proxy_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_proxy_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_hidden_ap_property_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Sets access point hidden ssid configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Gets access point hidden ssid configuration.
 */
int utc_wifi_manager_config_set_hidden_ap_property_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_hidden_ap_property(g_hWifiConfig, TRUE);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_hidden_ap_property", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_hidden_ap_property", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_hidden_ap_property_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Sets access point hidden ssid configuration.
 * @scenario		Sets the access point hidden ssid from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_hidden_ap_property_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_hidden_ap_property(NULL, TRUE);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_hidden_ap_property", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_hidden_ap_property", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_hidden_ap_property_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets access point hidden ssid configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point hidden ssid configuration.
 */
int utc_wifi_manager_config_get_hidden_ap_property_p(void)
{
	bool hidden_ssid = FALSE;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_hidden_ap_property(g_hWifiConfig, &hidden_ssid);
		CHECK_RETURN("wifi_manager_config_get_hidden_ap_property", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_hidden_ap_property(g_hWifiConfig, TRUE);
	CHECK_RETURN("wifi_manager_config_set_hidden_ap_property", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_hidden_ap_property(g_hWifiConfig, &hidden_ssid);
	CHECK_RETURN("wifi_manager_config_get_hidden_ap_property", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_hidden_ap_property_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets access point hidden ssid configuration.
 * @scenario		Gets the access point hidden ssid from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_hidden_ap_property_n(void)
{
	bool hidden_ssid = FALSE;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_hidden_ap_property(NULL, &hidden_ssid);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_hidden_ap_property", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_hidden_ap_property", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_anonymous_identity_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets access point anonymous identity from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point anonymous identity from configuration.
 */
int utc_wifi_manager_config_get_eap_anonymous_identity_p(void)
{
	char *anonymous_identity = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_eap_anonymous_identity(g_hWifiConfig, &anonymous_identity);
		CHECK_RETURN("wifi_manager_config_get_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_hidden_ap_property(g_hWifiConfig, TRUE);
	CHECK_RETURN("wifi_manager_config_set_hidden_ap_property", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_set_eap_anonymous_identity(g_hWifiConfig, WIFI_CONFIG_AN_ID);
	CHECK_RETURN("wifi_manager_config_set_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_eap_anonymous_identity(g_hWifiConfig, &anonymous_identity);
	CHECK_RETURN(VALID_VALUE, strncmp(WIFI_CONFIG_AN_ID, anonymous_identity, strlen(WIFI_CONFIG_AN_ID)), 0);
	FREE_MEMORY(anonymous_identity);
	CHECK_RETURN("wifi_manager_config_get_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_anonymous_identity_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets access point anonymous identity from configuration.
 * @scenario		Gets access point anonymous identity from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_eap_anonymous_identity_n(void)
{
	char *anonymous_identity;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_eap_anonymous_identity(NULL, &anonymous_identity);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_anonymous_identity_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Sets access point anonymous identity to configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point anonymous identity from configuration.
 */
int utc_wifi_manager_config_set_eap_anonymous_identity_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_set_eap_anonymous_identity(g_hWifiConfig, WIFI_CONFIG_AN_ID);
		CHECK_RETURN("wifi_manager_config_set_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_hidden_ap_property(g_hWifiConfig, TRUE);
	CHECK_RETURN("wifi_manager_config_set_hidden_ap_property", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_set_eap_anonymous_identity(g_hWifiConfig, WIFI_CONFIG_AN_ID);
	CHECK_RETURN("wifi_manager_config_set_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_anonymous_identity_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Sets access point anonymous identity to configuration.
 * @scenario		Sets access point anonymous identity from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_eap_anonymous_identity_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_anonymous_identity(NULL, WIFI_CONFIG_AN_ID);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_ca_cert_file_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets access point cacert file from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point cacert file from configuration.
 */
int utc_wifi_manager_config_get_eap_ca_cert_file_p(void)
{
	char *ca_cert;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_eap_ca_cert_file(g_hWifiConfig, &ca_cert);
		CHECK_RETURN("wifi_manager_config_get_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_eap_ca_cert_file(g_hWifiConfig, WIFI_CONFIG_CA_CERT_FILE);
	CHECK_RETURN("wifi_manager_config_set_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_eap_ca_cert_file(g_hWifiConfig, &ca_cert);
	CHECK_RETURN(VALID_VALUE, strncmp(ca_cert, WIFI_CONFIG_CA_CERT_FILE, strlen(ca_cert)), 0);
	FREE_MEMORY(ca_cert);
	CHECK_RETURN("wifi_manager_config_get_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NONE);	

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_ca_cert_file_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets access point cacert file from configuration.
 * @scenario		Gets access point cacert file from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_eap_ca_cert_file_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_eap_ca_cert_file(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_ca_cert_file_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Sets access point cacert file from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point cacert file from configuration.
 */
int utc_wifi_manager_config_set_eap_ca_cert_file_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_ca_cert_file(g_hWifiConfig, WIFI_CONFIG_CA_CERT_FILE);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_ca_cert_file_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Sets access point cacert file from configuration.
 * @scenario		Sets access point cacert file from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_eap_ca_cert_file_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_ca_cert_file(NULL, WIFI_CONFIG_CA_CERT_FILE);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_client_cert_file_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets access point client cert file to configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point client cert file from configuration.
 */
int utc_wifi_manager_config_get_eap_client_cert_file_p(void)
{
	char *client_cert;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_eap_client_cert_file(g_hWifiConfig, &client_cert);
		CHECK_RETURN("wifi_manager_config_get_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_eap_client_cert_file(g_hWifiConfig, WIFI_CONFIG_PRIVATE_KEY, WIFI_CONFIG_CLIENT_CERT);
	CHECK_RETURN("wifi_manager_config_set_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_eap_client_cert_file(g_hWifiConfig, &client_cert);
	CHECK_RETURN(VALID_VALUE, strncmp(client_cert, WIFI_CONFIG_CLIENT_CERT, strlen(client_cert)), 0);
	FREE_MEMORY(client_cert);
	CHECK_RETURN("wifi_manager_config_get_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_client_cert_file_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets access point client cert file to configuration.
 * @scenario		Gets access point client cert file from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_eap_client_cert_file_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_eap_client_cert_file(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_client_cert_file_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Sets access point client cert file to configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point client cert file from configuration.
 */
int utc_wifi_manager_config_set_eap_client_cert_file_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_client_cert_file(g_hWifiConfig, WIFI_CONFIG_PRIVATE_KEY, WIFI_CONFIG_CLIENT_CERT);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_client_cert_file_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Sets access point client cert file to configuration.
 * @scenario		Sets access point client cert file from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_eap_client_cert_file_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_client_cert_file(NULL, WIFI_CONFIG_PRIVATE_KEY, WIFI_CONFIG_CLIENT_CERT);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_identity_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets access point identity from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point identity from configuration.
 */
int utc_wifi_manager_config_get_eap_identity_p(void)
{
	char *identity;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_eap_identity(g_hWifiConfig, &identity);
		CHECK_RETURN("", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_eap_identity(g_hWifiConfig, WIFI_CONFIG_IDENTITY);
	CHECK_RETURN("wifi_manager_config_get_eap_identity", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_eap_identity(g_hWifiConfig, &identity);
	CHECK_RETURN(VALID_VALUE, strncmp(identity, WIFI_CONFIG_IDENTITY, strlen(identity)), 0);
	FREE_MEMORY(identity);
	CHECK_RETURN("wifi_manager_config_get_eap_identity", ret, WIFI_MANAGER_ERROR_NONE);

	

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_identity_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets access point identity from configuration.
 * @scenario		Gets access point identity from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_eap_identity_n(void)
{
	char *identity;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_eap_identity(NULL, &identity);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_eap_identity", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_eap_identity", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_identity_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Sets access point identity from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point identity from configuration.
 */
int utc_wifi_manager_config_set_eap_identity_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_identity(g_hWifiConfig, WIFI_CONFIG_IDENTITY);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_identity", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_identity", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_identity_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Sets access point identity from configuration.
 * @scenario		Sets access point identity from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_eap_identity_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_identity(NULL, WIFI_CONFIG_IDENTITY);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_identity", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_identity", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_type_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets access point eap type from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point eap type from configuration.
 */
int utc_wifi_manager_config_get_eap_type_p(void)
{
	wifi_manager_eap_type_e eap_type;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_eap_type(g_hWifiConfig, &eap_type);
		CHECK_RETURN("wifi_manager_config_get_eap_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_eap_type(g_hWifiConfig, WIFI_MANAGER_EAP_TYPE_AKA);
	CHECK_RETURN("wifi_manager_config_set_eap_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_eap_type(g_hWifiConfig, &eap_type);
	CHECK_RETURN("wifi_manager_config_get_eap_type", ret, WIFI_MANAGER_ERROR_NONE);

	CHECK_RETURN(VALID_VALUE, eap_type, WIFI_MANAGER_EAP_TYPE_AKA);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_type_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets access point eap type from configuration.
 * @scenario		Gets access point eap type from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_eap_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_eap_type(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_eap_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_eap_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_type_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Sets access point eap type from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point eap type from configuration.
 */
int utc_wifi_manager_config_set_eap_type_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_type(g_hWifiConfig, WIFI_MANAGER_EAP_TYPE_SIM);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_type", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_type_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Sets access point eap type from configuration.
 * @scenario		Sets access point eap type from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_eap_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_type(NULL, WIFI_MANAGER_EAP_TYPE_SIM);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_auth_type_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets access point eap auth type from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point eap auth type from configuration.
 */
int utc_wifi_manager_config_get_eap_auth_type_p(void)
{
	wifi_manager_eap_auth_type_e eap_auth_type;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_eap_auth_type(g_hWifiConfig, &eap_auth_type);
        CHECK_RETURN("wifi_manager_config_get_eap_auth_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
    }

	ret = wifi_manager_config_set_eap_auth_type(g_hWifiConfig, WIFI_MANAGER_EAP_AUTH_TYPE_MSCHAPV2);
	CHECK_RETURN("wifi_manager_config_set_eap_auth_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_eap_auth_type(g_hWifiConfig, &eap_auth_type);
	CHECK_RETURN("wifi_manager_config_get_eap_auth_type", ret, WIFI_MANAGER_ERROR_NONE);

	CHECK_RETURN(VALID_VALUE, eap_auth_type, WIFI_MANAGER_EAP_AUTH_TYPE_MSCHAPV2);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_auth_type_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets access point eap auth type from configuration.
 * @scenario		Gets access point eap auth type from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_eap_auth_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_eap_auth_type(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_eap_auth_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_eap_auth_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_auth_type_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Sets access point eap auth type from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point eap auth type from configuration.
 */
int utc_wifi_manager_config_set_eap_auth_type_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_auth_type(g_hWifiConfig, WIFI_MANAGER_EAP_AUTH_TYPE_MSCHAPV2);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_auth_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_auth_type", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_auth_type_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Sets access point eap auth type from configuration.
 * @scenario		Sets access point eap auth type from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_eap_auth_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_auth_type(NULL, -1);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_auth_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_auth_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_subject_match_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets access point subject match from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point subject match from configuration.
 */
int utc_wifi_manager_config_get_eap_subject_match_p(void)
{
	char *subject_match;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_eap_subject_match(g_hWifiConfig, &subject_match);
		CHECK_RETURN("wifi_manager_config_get_eap_subject_match", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_eap_subject_match(g_hWifiConfig, WIFI_CONFIG_SUBJECT_MATCH);
	CHECK_RETURN("wifi_manager_config_set_eap_subject_match", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_eap_subject_match(g_hWifiConfig, &subject_match);
	CHECK_RETURN(VALID_VALUE, strncmp(subject_match, WIFI_CONFIG_SUBJECT_MATCH, strlen(subject_match)), 0);
	FREE_MEMORY(subject_match);
	CHECK_RETURN("wifi_manager_config_get_eap_subject_match", ret, WIFI_MANAGER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_subject_match_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets access point subject match from configuration.
 * @scenario		Gets access point subject match from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_eap_subject_match_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_eap_subject_match(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_eap_subject_match", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_eap_subject_match", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_subject_match_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		sets access point subject match from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration & Sets & Gets access point subject match from configuration.
 */
int utc_wifi_manager_config_set_eap_subject_match_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_subject_match(g_hWifiConfig, WIFI_CONFIG_SUBJECT_MATCH);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_subject_match", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_subject_match", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_subject_match_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Sets access point subject match from configuration.
 * @scenario		Sets access point subject match from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_eap_subject_match_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_subject_match(NULL, WIFI_CONFIG_SUBJECT_MATCH);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_subject_match", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_subject_match", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_private_key_file_p
 * @since_tizen		5.0
 * @type			Positive
 * @description		Gets access point private-key file from configuration.
 * @scenario		Initialize Wi-Fi. Create configuration and Sets & Gets access point private-key file from configuration.
 */
int utc_wifi_manager_config_get_eap_private_key_file_p(void)
{
	char *file;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_eap_private_key_file(g_hWifiConfig, &file);
		CHECK_RETURN("wifi_manager_config_get_eap_private_key_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_eap_private_key_info(g_hWifiConfig, WIFI_CONFIG_PRIVATE_KEY_FILE, WIFI_CONFIG_PRIVATE_KEY);
	CHECK_RETURN("wifi_manager_config_set_eap_private_key_info", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_eap_private_key_file(g_hWifiConfig, &file);
	FREE_MEMORY(file);
	CHECK_RETURN("wifi_manager_config_get_eap_private_key_file", ret, WIFI_MANAGER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_eap_private_key_file_n1
 * @since_tizen		5.0
 * @type			Negative
 * @description		Gets access point private-key file from configuration.
 * @scenario		Gets access point private-key file from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_eap_private_key_file_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_eap_private_key_file(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_eap_private_key_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_eap_private_key_file", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_private_key_info_p
 * @since_tizen		5.0
 * @type			Positive
 * @description		Sets access point private-key file and info to configuration.
 * @scenario		Initialize Wi-Fi. Create configuration and Sets access point private-key file and info to configuration.
 */
int utc_wifi_manager_config_set_eap_private_key_info_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_private_key_info(g_hWifiConfig, WIFI_CONFIG_PRIVATE_KEY_FILE, WIFI_CONFIG_PRIVATE_KEY);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_private_key_info", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_private_key_info", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_eap_private_key_info_n1
 * @since_tizen		5.0
 * @type			Negative
 * @description		Sets access point private-key file and info to configuration.
 * @scenario		Sets access point client cert file from invalid configuration handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_eap_private_key_info_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_eap_private_key_info(NULL, WIFI_CONFIG_PRIVATE_KEY_FILE, WIFI_CONFIG_PRIVATE_KEY);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_eap_private_key_info", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_eap_private_key_info", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_ip_config_type_p
 * @since_tizen 	5.0
 * @type			Positive
 * @description		Gets the config type of IP
 * @scenario		Check AP validity and get IP config type whether it is Static,
 *					Dynamic, Fixed or auto
 */
int utc_wifi_manager_config_get_ip_config_type_p(void)
{
	wifi_manager_ip_config_type_e type;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_ip_config_type(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &type);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_ip_config_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_ip_config_type", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_ip_config_type_n1
 * @since_tizen 	5.0
 * @type			Negative
 * @description		Verify wifi_manager_config_get_ip_config_type by passing invalid parametrs(config, address_family, type).
 * @scenario		Pass invalid AP info and other parameters to make sure ip config type is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_ip_config_type_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_ip_config_type(NULL, -1, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_ip_config_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_ip_config_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_ip_config_type_p
 * @since_tizen		5.0
 * @type			Positive
 * @description		Sets the config type of IP.
 * @scenario 		Set the IP configuration type for IPv4 and update AP information
 *					Ensure no error.
 */
int utc_wifi_manager_config_set_ip_config_type_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_ip_config_type(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_MANAGER_IP_CONFIG_TYPE_STATIC);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_ip_config_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_ip_config_type", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_ip_config_type_n1
 * @since_tizen		5.0
 * @type			Negative
 * @description		Verify wifi_manager_config_set_ip_config_type by passing invalid parameters(config, address_family, type).
 * @scenario		Pass invalid AP info and other parameters to make sure ip config type is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_ip_config_type_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_ip_config_type(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_MANAGER_IP_CONFIG_TYPE_STATIC);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_ip_config_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_ip_config_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_ip_address_p
 * @since_tizen 	5.0
 * @type			Positive
 * @description		brief Gets the IP address.
 * @scenario 		Get IP address of the AP and ensure no error. Free ip address.
 */
int utc_wifi_manager_config_get_ip_address_p(void)
{
	char *ip_addr = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_ip_address(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &ip_addr);
		CHECK_RETURN("wifi_manager_config_get_ip_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_ip_address(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.10");
	CHECK_RETURN("wifi_manager_config_set_ip_address", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_ip_address(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY(ip_addr);
	CHECK_RETURN("wifi_manager_config_get_ip_address", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_ip_address_n1
 * @since_tizen 	5.0
 * @type			Negative
 * @description		Verify wifi_manager_config_get_ip_address by passing invalid parameters(config, address_family, ip_address).
 * @scenario		Pass invalid AP info and other parameters to  make sure IP address is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_ip_address_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_ip_address(NULL, -1, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_ip_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_ip_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_ip_address_p
 * @since_tizen 	5.0
 * @type			Positive
 * @description		Sets the IP address.
 * @scenario		Set IP address to AP and ensure no error.
 */
int utc_wifi_manager_config_set_ip_address_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_ip_address(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.10");

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_ip_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_ip_address", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_ip_address_n1
 * @since_tizen		5.0
 * @type			Negative
 * @description		Verify wifi_manager_config_set_ip_address by passing invalid parameters(config, address_family, ip_address).
 * @scenario		Pass invalid AP info and other parameters to  make sure IP address is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_ip_address_n1(void)
{
    int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_ip_address(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_ip_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_ip_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_subnet_mask_p
 * @since_tizen		5.0
 * @type			Positive
 * @description		brief Gets the subnet mask.
 * @scenario		Get subnet mask from AP information and ensure no error
 */
int utc_wifi_manager_config_get_subnet_mask_p(void)
{
	char *ip_addr = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_subnet_mask(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &ip_addr);
		CHECK_RETURN("wifi_manager_config_get_subnet_mask", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_subnet_mask(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "255.255.255.0");
	CHECK_RETURN("wifi_manager_config_set_subnet_mask", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_subnet_mask(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY(ip_addr);
	CHECK_RETURN("wifi_manager_config_get_subnet_mask", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_subnet_mask_n1
 * @since_tizen		5.0
 * @type			Negative
 * @description		Verify wifi_manager_config_get_subnet_mask by passing invalid parameters(config, address_family, subnet_mask).
 * @scenario		Pass invalid AP info and other parameters to  make sure Subnet mask is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_subnet_mask_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_subnet_mask(NULL, -1, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_subnet_mask", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_subnet_mask", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_subnet_mask_p
 * @since_tizen 	5.0
 * @type			Positive
 * @description		brief Sets the subnet mask.
 * @scenario		Set subnet mask in AP information. Ensure no error.
 */
int utc_wifi_manager_config_set_subnet_mask_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_subnet_mask(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "255.255.255.0");

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_subnet_mask", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_subnet_mask", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_subnet_mask_n1
 * @since_tizen 	5.0
 * @type			Negative
 * @description		Verify wifi_manager_config_set_subnet_mask by passing invalid parameters(config, address_family,subnet_mask).
 * @scenario		Pass invalid AP info and other parameters to  make sure thesubnet mask is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_subnet_mask_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_subnet_mask(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_subnet_mask", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_subnet_mask", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_gateway_address_p
 * @since_tizen 	5.0
 * @type			Positive
 * @description		brief Gets the gateway address.
 * @scenario		Get gateway's IP address from AP information.Ensure no error.
 */
int utc_wifi_manager_config_get_gateway_address_p(void)
{
	char *ip_addr = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_gateway_address(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &ip_addr);
		CHECK_RETURN("wifi_manager_config_get_gateway_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_gateway_address(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.1");
	CHECK_RETURN("wifi_manager_config_set_gateway_address", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_gateway_address(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY(ip_addr);
	CHECK_RETURN("wifi_manager_config_get_gateway_address", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_gateway_address_n1
 * @since_tizen 	5.0
 * @type			Negative
 * @description		Verify wifi_manager_config_get_gateway_address by passing invalid parameters(config,address_family,gateway_addr).
 * @scenario		Pass invalid AP info and other parameters to  make sure Gateway's IP address is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_gateway_address_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_gateway_address(NULL, -1, NULL);

	if (!g_bFeatureWifi) {
        CHECK_RETURN("wifi_manager_config_get_gateway_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_gateway_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_gateway_address_p
 * @since_tizen 	5.0
 * @type			Positive
 * @description		brief Sets the gateway address.
 * @scenario		Set Gateway's IP address in AP info. Ensure no error.
 */
int utc_wifi_manager_config_set_gateway_address_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_gateway_address(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.1");

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_gateway_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_gateway_address", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_gateway_address_n1
 * @since_tizen 	5.0
 * @type			Negative
 * @description		Verify wifi_manager_config_set_gateway_address by passing invalid parameters(config,address_family,gateway_addr).
 * @scenario		Pass invalid AP info and other parameters to  ensure Gateway IP address is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_gateway_address_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_gateway_address(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_gateway_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_gateway_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_config_get_dns_config_type_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets DNS configuration type
 * @scenario        Invoking wifi_manager_config_get_dns_config_type with valid parameter.
 */
int utc_wifi_manager_config_get_dns_config_type_p(void)
{
	wifi_manager_dns_config_type_e dns_type;

	if (!g_bFeatureWifi) {
		int ret = wifi_manager_config_get_dns_config_type(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns_type);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_config_get_dns_config_type(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns_type);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
		ret = wifi_manager_config_get_dns_config_type(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, &dns_type);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_config_get_dns_config_type_n1
 * @since_tizen     5.0
 * @type            Negative
 * @description     wifi_manager_config_get_dns_config_type should be failed with invalid parameter.
 * @scenario        Verify dns config type by passing invalid parameter.
 **/
int utc_wifi_manager_config_get_dns_config_type_n1(void)
{
	wifi_manager_dns_config_type_e dns_type;

	if (!g_bFeatureWifi) {
		int ret = wifi_manager_config_get_dns_config_type(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns_type);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_config_get_dns_config_type(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns_type);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_config_get_dns_config_type(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_config_get_dns_config_type(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_config_set_dns_config_type_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Sets DNS configuration type
 * @scenario        Invoking wifi_manager_config_set_dns_config_type with valid parameter.
 */
int utc_wifi_manager_config_set_dns_config_type_p(void)
{
	if (!g_bFeatureWifi) {
		int ret = wifi_manager_config_set_dns_config_type(g_hWifiConfig,
				WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_MANAGER_DNS_CONFIG_TYPE_DYNAMIC);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_config_set_dns_config_type(g_hWifiConfig,
				WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_MANAGER_DNS_CONFIG_TYPE_STATIC);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
		ret = wifi_manager_config_set_dns_config_type(g_hWifiConfig,
				WIFI_MANAGER_ADDRESS_FAMILY_IPV6, WIFI_MANAGER_DNS_CONFIG_TYPE_DYNAMIC);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_config_set_dns_config_type_n1
 * @since_tizen     5.0
 * @type            Negative
 * @description     wifi_manager_config_set_dns_config_type should be failed with invalid parameter.
 * @scenario        Verify dns config type by passing invalid parameter.
 **/
int utc_wifi_manager_config_set_dns_config_type_n1(void)
{
	if (!g_bFeatureWifi) {
		int ret = wifi_manager_config_set_dns_config_type(NULL,
				WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_MANAGER_DNS_CONFIG_TYPE_STATIC);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_config_set_dns_config_type(NULL,
				WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_MANAGER_DNS_CONFIG_TYPE_STATIC);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_config_set_dns_config_type(NULL,
				WIFI_MANAGER_ADDRESS_FAMILY_IPV6, WIFI_MANAGER_DNS_CONFIG_TYPE_DYNAMIC);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_dns_address_p
 * @since_tizen 	5.0
 * @type			Positive
 * @description		Gets the DNS address.
 * @scenario
 */
int utc_wifi_manager_config_get_dns_address_p(void)
{
	char *dns1 = NULL;
	char *dns2 = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_dns_address(g_hWifiConfig, 1, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns1);
		CHECK_RETURN("wifi_manager_config_get_dns_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_dns_address(g_hWifiConfig, 1, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.1");
	CHECK_RETURN("wifi_manager_config_set_dns_address", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_set_dns_address(g_hWifiConfig, 2, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.2");
	CHECK_RETURN("wifi_manager_config_set_dns_address", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_dns_address(g_hWifiConfig, 1, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns1);
	FREE_MEMORY(dns1);
	CHECK_RETURN("wifi_manager_config_get_dns_address", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_get_dns_address(g_hWifiConfig, 2, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns2);
	FREE_MEMORY(dns2);
	CHECK_RETURN("wifi_manager_config_get_dns_address", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_get_dns_address_n1
 * @since_tizen 	5.0
 * @type			Negative
 * @description		Verify wifi_manager_config_get_dns_address by passing invalid parameters(config,addr_fam,DNS address).
 * @scenario		Pass invalid AP info and other parameters to  make sure DNS address is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_get_dns_address_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_dns_address(NULL, 1, -1, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_dns_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_dns_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_dns_address_p
 * @since_tizen 	5.0
 * @type			Positive
 * @description		Gets the DNS address.
 * @scenario		Get the dns address from AP info. Ensure no error.
 */
int utc_wifi_manager_config_set_dns_address_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_set_dns_address(g_hWifiConfig, 1, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.1");
		CHECK_RETURN("wifi_manager_config_set_dns_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_config_set_dns_address(g_hWifiConfig, 1, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.1");
	CHECK_RETURN("wifi_manager_config_set_dns_address", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_config_set_dns_address(g_hWifiConfig, 2, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.2");
	CHECK_RETURN("wifi_manager_config_set_dns_address", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_config_set_dns_address_n1
 * @since_tizen 	5.0
 * @type			Negative
 * @description		Verify wifi_manager_config_set_dns_address by passing invalid parameters(config, order, addr_fam, DNS address).
 * @scenario		Pass invalid AP info and other parameters to  make sure DNS address is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_config_set_dns_address_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_set_dns_address(NULL, 1, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_dns_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_dns_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_config_get_prefix_length_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets prefix length
 * @scenario        Invoking wifi_manager_config_get_prefix_length with valid parameter.
 **/
int utc_wifi_manager_config_get_prefix_length_p(void)
{
	int length;
	int prefix_length = 64;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_get_prefix_length(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, &length);
		CHECK_RETURN("wifi_manager_config_get_prefix_length", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		ret = wifi_manager_config_set_subnet_mask(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "255.255.255.0");
		CHECK_RETURN("wifi_manager_config_set_subnet_mask", ret, WIFI_MANAGER_ERROR_NONE);
		ret = wifi_manager_config_get_prefix_length(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &length);
		CHECK_RETURN("wifi_manager_config_get_prefix_length", ret, WIFI_MANAGER_ERROR_NONE);

		ret = wifi_manager_config_set_prefix_length(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, prefix_length);
		CHECK_RETURN("wifi_manager_config_set_prefix_length", ret, WIFI_MANAGER_ERROR_NONE);
		ret = wifi_manager_config_get_prefix_length(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, &length);
		CHECK_RETURN("wifi_manager_config_get_prefix_length", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_config_get_prefix_length_n1
 * @since_tizen     5.0
 * @type            Negative
 * @description     wifi_manager_config_get_prefix_length should be failed with invalid parameter.
 * @scenario        Verify prefix_length by passing invalid parameter.
 **/
int utc_wifi_manager_config_get_prefix_length_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_config_get_prefix_length(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_get_prefix_length", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_get_prefix_length", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_config_set_prefix_length_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Sets IPv6 prefix length
 * @scenario        Invoking wifi_manager_config_set_prefix_length with valid parameter.
 */
int utc_wifi_manager_config_set_prefix_length_p(void)
{
	int length = 64;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_config_set_prefix_length(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, length);
		CHECK_RETURN("wifi_manager_config_set_prefix_length", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		ret = wifi_manager_config_set_prefix_length(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, length);
		CHECK_RETURN("wifi_manager_config_set_prefix_length", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_config_set_prefix_length_n1
 * @since_tizen     5.0
 * @type            Negative
 * @description     wifi_manager_config_set_prefix_length should be failed with invalid parameter.
 * @scenario        Verify prefix_length by passing invalid parameter.
 **/
int utc_wifi_manager_config_set_prefix_length_n1(void)
{
	int ret = wifi_manager_config_set_prefix_length(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, -1);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_config_set_prefix_length", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_config_set_prefix_length", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
