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

//& set: WifiManager

/**
 * @function		utc_wifi_manager_startup
 * @since_tizen		3.0
 * @description		Initializes Wi-Fi.Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_manager_startup(void)
{
	g_bFeatureWifi = wifi_manager_check_feature_supported(FEATURE_WIFI);

	int ret = wifi_manager_initialize(&g_hWifi);
	PRINT_RETURN("wifi_manager_initialize", ret);
}

/**
 * @function		utc_wifi_manager_cleanup
 * @since_tizen		3.0
 * @description		Deinitializes Wi-Fi.Called after each test.
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_manager_cleanup(void)
{
	int ret = wifi_manager_deinitialize(g_hWifi);
	PRINT_RETURN("wifi_manager_deinitialize", ret);
}

/**
 * @testcase		utc_wifi_manager_initialize_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Initializes Wi-Fi Manager.
 * @scenario		Initialize Wi-Fi Manager. If already initialized, deinitialize and initialize again.
 */
int utc_wifi_manager_initialize_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_initialize(&g_hWifi);
		CHECK_RETURN("wifi_manager_initialize", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_deinitialize(g_hWifi);
	CHECK_RETURN("wifi_manager_deinitialize", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_initialize(&g_hWifi);
	CHECK_RETURN("wifi_manager_initialize", ret, WIFI_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_manager_initialize_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Initializes Wi-Fi Manager.
 * @scenario		Initialize Wi-Fi Manager consecutively. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_OPERATION.
 */
int utc_wifi_manager_initialize_n(void)
{
    int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_initialize(NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_initialize", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_initialize", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_activate_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify wifi_manager_activate by passing invalid parameters(callback).
 * @scenario		Activate Wi-Fi repititively and ensure no unexpected behaviour.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_OPERATION.
 */
int utc_wifi_manager_activate_n(void)
{
    int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_activate(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_activate", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_activate", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/**
 * @testcase		utc_wifi_manager_activate_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description 	Activates Wi-Fi asynchronously.
 * @scenario		Activate and Deactivate Wi-Fi. Respective callbacks shall be
 *					triggeted on action completion.
 */
int utc_wifi_manager_activate_p(void)
{
	bool activated;
	int retry_count = 0;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
		CHECK_RETURN("wifi_manager_activate", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_is_activated(g_hWifi, &activated);
	CHECK_RETURN("wifi_manager_is_activated", ret, WIFI_MANAGER_ERROR_NONE);

	if (activated) {
		ret = wifi_manager_deactivate(g_hWifi, wifi_manager_deactivated_callback, NULL);
		PRINT_RETURN("wifi_manager_deactivate", ret);

		RUN_GMAIN_LOOP;
	}

	ret = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
	PRINT_RETURN("wifi_manager_activate", ret);

	RUN_GMAIN_LOOP;

	while (retry_count < WIFI_ACTIVATION_RETRY &&
			g_nCallbackRet != WIFI_MANAGER_ERROR_NONE) {
		sleep(5);
		ret = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
		PRINT_RETURN("wifi_manager_activate", ret);
		retry_count++;

		RUN_GMAIN_LOOP;
	}

	CHECK_RETURN(CALLBACK_RETURN, g_nCallbackRet, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_activate_with_wifi_picker_tested_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify wifi_manager_activate_with_wifi_picker_tested passing invalid parameters(callback).
 * @scenario		Pass invalid callback or user data and ensure wifi is not initialized and activated.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_OPERATION.
 */
int utc_wifi_manager_activate_with_wifi_picker_tested_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_activate_with_wifi_picker_tested(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_activate_with_wifi_picker_tested", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_activate_with_wifi_picker_tested", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_activate_with_wifi_picker_tested_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Disconnect Wi-Fi
 * @scenario		Disconnect Wi-Fi and ensure the picker tested callback is triggered.
 */
int utc_wifi_manager_activate_with_wifi_picker_tested_p(void)
{
	bool activated;
	int retry_count = 0;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_activate_with_wifi_picker_tested(g_hWifi, wifi_manager_activated_with_picker_callback, NULL);
		CHECK_RETURN("wifi_manager_activate_with_wifi_picker_tested", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_is_activated(g_hWifi, &activated);
	CHECK_RETURN("wifi_manager_is_activated", ret, WIFI_MANAGER_ERROR_NONE);

	if (activated) {
		ret = wifi_manager_deactivate(g_hWifi, wifi_manager_deactivated_callback, NULL);
		PRINT_RETURN("wifi_manager_deactivate", ret);

		RUN_GMAIN_LOOP;
	}

	ret = wifi_manager_activate_with_wifi_picker_tested(g_hWifi, wifi_manager_activated_with_picker_callback, NULL);
	PRINT_RETURN("wifi_manager_activate_with_wifi_picker_tested", ret);

	RUN_GMAIN_LOOP;

	while (retry_count < WIFI_ACTIVATION_RETRY &&
			g_nCallbackRet != WIFI_MANAGER_ERROR_NONE) {
		sleep(5);
		ret = wifi_manager_activate_with_wifi_picker_tested(g_hWifi, wifi_manager_activated_with_picker_callback, NULL);
		PRINT_RETURN("wifi_manager_activate_with_wifi_picker_tested", ret);
		retry_count++;

		RUN_GMAIN_LOOP;
	}

	CHECK_RETURN(CALLBACK_RETURN, g_nCallbackRet, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_is_activated_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description 	Checks whether Wi-Fi is activated.
 * @scenario		Check whether the Wi-Fi is activated. Ensure no error.
 */
int utc_wifi_manager_is_activated_p(void)
{
	bool activated;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_is_activated(g_hWifi, &activated);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_is_activated", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_is_activated", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_is_activated_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify wifi_manager_is_activated by passing invalid parameters(callbacated).
 * @scenario		Pass invalid parameter and ensure wifi activation status is not returned.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_is_activated_n(void)
{
    int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_is_activated(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_is_activated", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_is_activated", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_get_connection_state_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the connection state.
 * @scenario		Get Wi-Fi connection state. Ensure no error.
 */
int utc_wifi_manager_get_connection_state_p(void)
{
	wifi_manager_connection_state_e conn_state;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_get_connection_state(g_hWifi, &conn_state);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_get_connection_state", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_get_connection_state", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_get_connection_state_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_get_connection_state by passing invalid parameters(connection_state).
 * @scenario		Pass invalid parameter and ensure wifi connection state is not returned.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_get_connection_state_n(void)
{
    int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_get_connection_state(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_get_connection_state", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_get_connection_state", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_get_module_state_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description	Gets the Wi-Fi module state.
 * @scenario		Get Wi-Fi module state. Ensure no error.
 */
int utc_wifi_manager_get_module_state_p(void)
{
	wifi_manager_module_state_e module_state;
	int ret = WIFI_MANAGER_ERROR_NONE;

	char *profile = NULL;

	ret = wifi_manager_get_module_state(g_hWifi, &module_state);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_get_module_state", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_get_module_state", ret, WIFI_MANAGER_ERROR_NONE);
	}

	if (profile)
		free(profile);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_get_module_state_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description	Verify wifi_manager_get_module_state by passing invalid parameters(module_state).
 * @scenario		Pass invalid parameter and ensure wifi module state is not returned.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_get_module_state_n(void)
{
    int ret = WIFI_MANAGER_ERROR_NONE;

	char *profile = NULL;

	ret = wifi_manager_get_module_state(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_get_module_state", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_get_module_state", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	if (profile)
		free(profile);

    return 0;
}



/**
 * @testcase		utc_wifi_manager_get_mac_address_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description 	Gets the local MAC address.
 * @scenario		Get local mac address of the device. Ensure no error.
 */
int utc_wifi_manager_get_mac_address_p(void)
{
	char *mac_address = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_get_mac_address(g_hWifi, &mac_address);
		CHECK_RETURN("wifi_manager_get_mac_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_pre_activate();
	CHECK_RETURN("wifi_manager_pre_activate", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_get_mac_address(g_hWifi, &mac_address);
	FREE_MEMORY(mac_address);
	CHECK_RETURN("wifi_manager_get_mac_address", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_get_mac_address_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify wifi_manager_get_mac_address by passing invalid parameters
 * @scenario		Pass invalid parameter and ensure mac address is not returned.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_get_mac_address_n(void)
{
    int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_get_mac_address(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_get_mac_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_get_mac_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_foreach_found_ap_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description 	Gets the result of the scan.
 * @scenario		Get all the Access Points found during scan. Ensure no error.
 */
int utc_wifi_manager_foreach_found_ap_p(void)
{
    int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_foreach_found_ap(g_hWifi, wifi_manager_foreach_found_ap_callback, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_foreach_found_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_foreach_found_ap", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_foreach_found_ap_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify wifi_manager_foreach_found_ap by passing invalid parameters
 * @scenario		Pass invalid parameters and ensure WiFi Access points are not returned.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_foreach_found_ap_n(void)
{
    int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_foreach_found_ap(g_hWifi, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_foreach_found_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_foreach_found_ap", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_scan_specific_ap_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify wifi_manager_scan_specific_ap by passing invalid parameters
 * @scenario		Pass invalid essid and ensure any AP is not returned.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_scan_specific_ap_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_scan_specific_ap(g_hWifi, NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_scan_specific_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_scan_specific_ap", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_scan_specific_ap_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Starts specific ap scan, asynchronously.
 * @scenario		Scan for specific ESSID. When AP is found the callback is triggered.
 */
int utc_wifi_manager_scan_specific_ap_p(void)
{
	int ret;
	char ap_name[CONFIG_VALUE_LEN_MAX];

	if (!g_bFeatureWifi) {
		ret = wifi_manager_scan_specific_ap(g_hWifi, ap_name, wifi_manager_scanned_specific_ap_callback, NULL);
		CHECK_RETURN("wifi_manager_scan_specific_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!wifi_manager_get_value_from_configfile("WIFI_WPSACCESSPOINTNAME", ap_name)) {
		FPRINTF("[%s:%d] wifi_manager_get_value_from_configfile(WIFI_WPSACCESSPOINTNAME) failed \\n", __FILE__, __LINE__);
		return -1;
	}

	ret = wifi_manager_scan_specific_ap(g_hWifi, ap_name, wifi_manager_scanned_specific_ap_callback, NULL);
	PRINT_RETURN("wifi_manager_scan_specific_ap", ret);
	RUN_GMAIN_LOOP;
	CHECK_RETURN(CALLBACK_RETURN, ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_foreach_found_specific_ap_n
 * @since_tizen		3.0
 * @type			Negative
 * @description 	Verify wifi_manager_foreach_found_specific_ap by passing invalid parameters
 * @scenario		Pass invalid parameters and ensure any AP is not returned.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_foreach_found_specific_ap_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_foreach_found_specific_ap(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_foreach_found_specific_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_foreach_found_specific_ap", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_foreach_found_specific_ap_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets the result of specific ap scan.
 * @scenario		Scan for Specitic ESSID. When AP is found, callback is triggered.
 */
int utc_wifi_manager_foreach_found_specific_ap_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_foreach_found_specific_ap(g_hWifi, wifi_manager_foreach_found_specific_ap_callback, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_foreach_found_specific_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_foreach_found_specific_ap", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_set_device_state_changed_cb_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description 	Registers the callback called when the device state is changed.
 * @scenario		Get device ON / OFF status through callback.
 */
int utc_wifi_manager_set_device_state_changed_cb_p(void)
{
    int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_set_device_state_changed_cb(g_hWifi, wifi_manager_device_state_changed_callback, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_set_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_set_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_set_device_state_changed_cb_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify wifi_manager_set_device_state_changed_cb by passing invalid parameters
 * @scenario		Pass invalid parameters and ensure device state is not notofied through callback.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_set_device_state_changed_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_set_device_state_changed_cb(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_set_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_set_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_unset_device_state_changed_cb_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description 	Registers the callback called when the device state is changed.
 * @scenario		When the device power state is changed, devicd state is notified through callback.
 */
int utc_wifi_manager_unset_device_state_changed_cb_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_unset_device_state_changed_cb(g_hWifi);
		CHECK_RETURN("wifi_manager_unset_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_set_device_state_changed_cb(g_hWifi, wifi_manager_device_state_changed_callback, NULL);
	CHECK_RETURN("wifi_manager_set_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_unset_device_state_changed_cb(g_hWifi);
	CHECK_RETURN("wifi_manager_unset_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_unset_device_state_changed_cb_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify wifi_manager_unset_device_state_changed_cb by changing the state
 * @scenario		Unset device state changed callback and ensure device state is not notofied through callback.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_OPERATION.
 */
int utc_wifi_manager_unset_device_state_changed_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_unset_device_state_changed_cb(NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_unset_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_unset_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_set_background_scan_cb_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description 	Registers the callback called when the background scan is finished periodically.
 * @scenario		Set background scan. Whenevet an AP is found, callback is triggered.
 */
int utc_wifi_manager_set_background_scan_cb_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_set_background_scan_cb(g_hWifi, wifi_manager_background_scanned_callback, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_set_background_scan_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_set_background_scan_cb", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_set_background_scan_cb_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_set_background_scan_cb by passing invalid parameters
 * @scenario		Pass invalid callback function and ensure device state is not notofied through callback.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_set_background_scan_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_set_background_scan_cb(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_set_background_scan_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_set_background_scan_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_unset_background_scan_cb_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Registers the callback called when the background scan is finished periodically.
 * @scenario		Scan complete callback is triggered on completion.
 *					Unset BG scan callback. Ensure no error.
 */
int utc_wifi_manager_unset_background_scan_cb_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_unset_background_scan_cb(g_hWifi);
		CHECK_RETURN("wifi_manager_unset_background_scan_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_set_background_scan_cb(g_hWifi, wifi_manager_background_scanned_callback, NULL);
	CHECK_RETURN("wifi_manager_set_background_scan_cb", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_unset_background_scan_cb(g_hWifi);
	CHECK_RETURN("wifi_manager_unset_background_scan_cb", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_unset_background_scan_cb_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_unset_background_scan_cb
 * @scenario		Unset BG Scan callback repeatedly and ensure no unexpected behaviour..
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_OPERATION.
 */
int utc_wifi_manager_unset_background_scan_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_unset_background_scan_cb(NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_unset_background_scan_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_unset_background_scan_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_set_scan_state_changed_cb_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Registers the callback called when the scan state is changed.
 * @scenario		Get scan status through callback.
 */
int utc_wifi_manager_set_scan_state_changed_cb_p(void)
{
    int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_set_scan_state_changed_cb(g_hWifi, wifi_manager_scan_state_changed_callback, NULL);
		CHECK_RETURN("wifi_manager_set_scan_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_pre_activate();
	CHECK_RETURN("wifi_manager_pre_activate", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_set_scan_state_changed_cb(g_hWifi, wifi_manager_scan_state_changed_callback, NULL);

	ret = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
	PRINT_RETURN("wifi_manager_scan", ret);
	RUN_GMAIN_LOOP;

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_set_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_set_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_set_scan_state_changed_cb_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify wifi_manager_set_scan_state_changed_cb by passing invalid parameters
 * @scenario		Pass invalid parameters and ensure scan state is not notofied through callback.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_set_scan_state_changed_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_set_scan_state_changed_cb(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_set_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_set_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_unset_scan_state_changed_cb_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Registers the callback called when the scan state is changed.
 * @scenario		When the scan state is changed, scan state is notified through callback.
 */
int utc_wifi_manager_unset_scan_state_changed_cb_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_unset_scan_state_changed_cb(g_hWifi);
		CHECK_RETURN("wifi_manager_unset_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_set_scan_state_changed_cb(g_hWifi, wifi_manager_scan_state_changed_callback, NULL);
	CHECK_RETURN("wifi_manager_set_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
	PRINT_RETURN("wifi_manager_scan", ret);
	RUN_GMAIN_LOOP;

	ret = wifi_manager_unset_scan_state_changed_cb(g_hWifi);
	CHECK_RETURN("wifi_manager_unset_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_unset_scan_state_changed_cb_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify wifi_manager_unset_scan_state_changed_cb by changing the state
 * @scenario		Unset scan state changed callback and ensure scan state is not notofied through callback.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_OPERATION.
 */
int utc_wifi_manager_unset_scan_state_changed_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_unset_scan_state_changed_cb(NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_unset_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_unset_device_state_changed_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_set_connection_state_changed_cb_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description 	Registers the callback called when the connection state is changed.
 * @scenario		Callback is triggered when the device is connected or disconnected.
 */
int utc_wifi_manager_set_connection_state_changed_cb_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_set_connection_state_changed_cb(g_hWifi, wifi_manager_connection_state_changed_callback, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_set_connection_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_set_connection_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_manager_wifi_set_connection_state_changed_cb_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify wifi_manager_unset_background_scan_cb by passing invalid parameters.
 * @scenario		Register NULL for callback and ensure Invalid operation is reported.
 */
int utc_wifi_manager_set_connection_state_changed_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_set_connection_state_changed_cb(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_set_connection_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_set_connection_state_changed_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_unset_connection_state_changed_cb_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description 	Unregisters the callback called when the connection state is changed.
 * @scenario		Connection state callback shall never be triggered once the callback is unregistered.
 */
int utc_wifi_manager_unset_connection_state_changed_cb_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_unset_connection_state_changed_cb(g_hWifi);
		CHECK_RETURN("wifi_manager_unset_connection_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_set_connection_state_changed_cb(g_hWifi, wifi_manager_connection_state_changed_callback, NULL);
	CHECK_RETURN("wifi_manager_set_connection_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_unset_connection_state_changed_cb(g_hWifi);
	CHECK_RETURN("wifi_manager_unset_connection_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_unset_connection_state_changed_cb_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Unregisters the callback called when the connection state is changed.
 * @scenario		Unset connection state callback repeatedly. There should be no unexpected behaviour.
 *					Ensure WIFI_MANAGER_ERROR_INVALID_OPERATION is reported.
 */
int utc_wifi_manager_unset_connection_state_changed_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_unset_connection_state_changed_cb(NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_unset_connection_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_unset_connection_state_changed_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_set_rssi_level_changed_cb_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description 	Registers callback called when the RSSI of connected Wi-Fi is changed.
 * @scenario		Callback is triggered whenever the is a change in signal strength.
 */
int utc_wifi_manager_set_rssi_level_changed_cb_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_set_rssi_level_changed_cb(g_hWifi, wifi_manager_rssi_level_changed_callback, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_set_rssi_level_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_set_rssi_level_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_set_rssi_level_changed_cb_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify wifi_manager_set_rssi_level_changed_cb by passing invalid parameters.
 * @scenario		Register Null callback and ensure WIFI_MANAGER_ERROR_INVALID_OPERATION is reported.
 */
int utc_wifi_manager_set_rssi_level_changed_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_set_rssi_level_changed_cb(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_set_rssi_level_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_set_rssi_level_changed_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_unset_rssi_level_changed_cb_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Registers callback called when the RSSI of connected Wi-Fi is changed.
 * @scenario		Register and Unregister RSSI level changed callback. Ensure no error.
 */
int utc_wifi_manager_unset_rssi_level_changed_cb_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_unset_rssi_level_changed_cb(g_hWifi);
		CHECK_RETURN("wifi_manager_unset_rssi_level_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_set_rssi_level_changed_cb(g_hWifi, wifi_manager_rssi_level_changed_callback, NULL);
	CHECK_RETURN("wifi_manager_set_rssi_level_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_unset_rssi_level_changed_cb(g_hWifi);
	CHECK_RETURN("wifi_manager_unset_rssi_level_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_unset_rssi_level_changed_cb_n
 * @since_tizen		3.0
 * @type			Negative
 * @description 	Unregisters callback called when the RSSI of connected Wi-Fi is changed.
 * @scenario		Unset RSSI level changed callback repeatedly and ensure no strange behaviour.
 *					Ensure WIFI_MANAGER_ERROR_INVALID_OPERATION error is reported
 */
int utc_wifi_manager_unset_rssi_level_changed_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_unset_rssi_level_changed_cb(NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_unset_rssi_level_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_unset_rssi_level_changed_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_set_module_state_changed_cb_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify wifi_manager_set_module_state_changed_cb by passing invalid parameters
 * @scenario		Pass invalid parameters and ensure Wi-Fi module state is not notofied through callback.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_set_module_state_changed_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	char *profile = NULL;

	ret = wifi_manager_set_module_state_changed_cb(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_set_module_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_set_module_state_changed_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	if (profile)
		free(profile);

    return 0;
}

/**
 * @testcase		utc_wifi_manager_unset_module_state_changed_cb_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify wifi_manager_unset_module_state_changed_cb by changing the state
 * @scenario		Unset Wi-Fi module state changed callback and ensure Wi-Fi module state is not notofied through callback.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_OPERATION.
 */
int utc_wifi_manager_unset_module_state_changed_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	char *profile = NULL;

	ret = wifi_manager_unset_module_state_changed_cb(NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_unset_module_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_unset_module_state_changed_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	if (profile)
		free(profile);

	return 0;
}


/**
 * @testcase		utc_wifi_manager_deinitialize_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description 	Deinitializes Wi-Fi.
 * @scenario		Deinitialize Wi-Fi and ensure Wi-Fi is Deinitialized properly. Ensure no error.
 */
int utc_wifi_manager_deinitialize_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_deinitialize(g_hWifi);
		CHECK_RETURN("wifi_manager_deinitialize", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_deinitialize(g_hWifi);
	CHECK_RETURN("wifi_manager_deinitialize", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_initialize(&g_hWifi);
	CHECK_RETURN("wifi_manager_initialize", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_deinitialize_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify wifi_manager_deinitialize by calling it twice.
 * @scenario		Deinitialize Wi-Fi repeatedly and ensure no unexpected behaviour.
 *					Ensure WIFI_MANAGER_ERROR_INVALID_OPERATION error is reported
 */
int utc_wifi_manager_deinitialize_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_deinitialize(NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_deinitialize", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_deinitialize", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_get_network_interface_name_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the name of the network interface.
 * @scenario		Activate WiFi and get the network interface name. If Wi-Fi is not activated immediately
 *					Wi-Fi interface name callback will be triggered on Wi-Fi activation.
 */
int utc_wifi_manager_get_network_interface_name_p(void)
{
	char* intf_name = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_get_network_interface_name(g_hWifi, &intf_name);
		CHECK_RETURN("wifi_manager_get_network_interface_name", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_pre_activate();
	CHECK_RETURN("wifi_manager_pre_activate", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_get_network_interface_name(g_hWifi, &intf_name);
	CHECK_RETURN("wifi_manager_get_network_interface_name", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_get_network_interface_name_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_get_network_interface_name by passing invalid parameter.
 * @scenario		Pass NULL parameter and ensure invalid parameter is reported.
 */
int utc_wifi_manager_get_network_interface_name_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_get_network_interface_name(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_get_network_interface_name", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_get_network_interface_name", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_scan_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Refreshes the access point information.
 * @scenario		When Wi-Fi scan is initiated,  Callback will be triggered on scan completion.
 *					When Wi-Fi is activated, Scan will be initiated and callback will be triggered on scan done.
 */
int utc_wifi_manager_scan_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
		CHECK_RETURN("wifi_manager_scan", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_pre_activate();
	CHECK_RETURN("wifi_manager_pre_activate", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
	PRINT_RETURN("wifi_manager_scan", ret);
	RUN_GMAIN_LOOP;
	CHECK_RETURN(CALLBACK_RETURN, ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_scan_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_scan by passing invalid parameters.
 * @scenario		Pass Invalid paramers to wifi scan and ensure WIFI_MANAGER_ERROR_INVALID_PARAMETER is reported.
 */
int utc_wifi_manager_scan_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_scan(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_scan", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_scan", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_get_scan_state_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Gets the scan state.
 * @scenario        Get Wi-Fi scan state. Ensure no error.
 */
int utc_wifi_manager_get_scan_state_p(void)
{
	wifi_manager_scan_state_e scan_state;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_get_scan_state(g_hWifi, &scan_state);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_get_scan_state", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_get_scan_state", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_get_scan_state_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     Verify wifi_manager_get_scan_state by passing invalid parameters(scan_state).
 * @scenario        Pass invalid parameter and ensure wifi scan state is not returned.
 *                  Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_get_scan_state_n(void)
{
    int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_get_scan_state(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_get_scan_state", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_get_scan_state", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_deactivate_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_deactivate by passing invalid parameters.
 * @scenario		Deactivate Wi-Fi after deinitialization and ensure WIFI_MANAGER_ERROR_INVALID_OPERATION is reported.
 */
int utc_wifi_manager_deactivate_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_deactivate(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_deactivate", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_deactivate", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_deactivate_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Deactivates Wi-Fi asynchronously.
 * @scenario		Actiate WiFi if it is in deactivated state and vice versa.
 *					WiFi activation state is reported through callback
 */
int utc_wifi_manager_deactivate_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_deactivate(g_hWifi, wifi_manager_deactivated_callback, NULL);
		CHECK_RETURN("wifi_manager_deactivate", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}


	ret = wifi_manager_pre_activate();
	CHECK_RETURN("wifi_manager_pre_activate", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_deactivate(g_hWifi, wifi_manager_deactivated_callback, NULL);
	PRINT_RETURN("wifi_manager_deactivate", ret);
	RUN_GMAIN_LOOP;
	CHECK_RETURN(CALLBACK_RETURN, ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_connect_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_connect by passing invalid parameters.
 * @scenario		Try to connect Wi-Fi before initialization and ensure WIFI_MANAGER_ERROR_INVALID_OPERATION is reported.
 */
int utc_wifi_manager_connect_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_connect(NULL, NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_connect", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_connect", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_connect_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Connects the access point asynchronously..
 * @scenario		Create AP handle and activate Wi-Fi. On acivattion Wi-Fi connection will
 *					be initiated to the AP.
 */
int utc_wifi_manager_connect_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_connect(g_hWifi, g_hWifiAP, wifi_manager_connected_callback, NULL);
		CHECK_RETURN("wifi_manager_connect", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_pre_connect();
	CHECK_RETURN("wifi_manager_pre_connect", ret, WIFI_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase            utc_wifi_manager_connect_hidden_ap_n
 * @since_tizen         4.0
 * @type                        Negative
 * @description         Verify wifi_manager_connect_hidden_ap by passing invalid parameters.
 * @scenario            Try to connect hidden AP before initialization and ensure WIFI_MANAGER_ERROR_INVALID_PARAMETER is reported.
 */
int utc_wifi_manager_connect_hidden_ap_n(void)
{
        int ret = WIFI_MANAGER_ERROR_NONE;

        ret = wifi_manager_connect_hidden_ap(NULL, NULL, 0, NULL, NULL, NULL);

        if (!g_bFeatureWifi) {
                CHECK_RETURN("wifi_manager_connect_hidden_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
        } else {
                CHECK_RETURN("wifi_manager_connect_hidden_ap", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
        }

        return 0;
}

/**
 * @testcase            utc_wifi_manager_connect_hidden_ap_n2
 * @since_tizen         4.0
 * @type                        Negative
 * @description         Verify wifi_manager_connect_hidden_ap by passing invalid parameters.
 * @scenario            Try to connect hidden AP with invalid ssid and ensure WIFI_MANAGER_ERROR_INVALID_PARAMETER is reported.
 */
int utc_wifi_manager_connect_hidden_ap_n2(void)
{
        int ret = WIFI_MANAGER_ERROR_NONE;

        ret = wifi_manager_connect_hidden_ap(g_hWifi, NULL, 0, NULL, NULL, NULL);

        if (!g_bFeatureWifi) {
                CHECK_RETURN("wifi_manager_connect_hidden_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
        } else {
                CHECK_RETURN("wifi_manager_connect_hidden_ap", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
        }

        return 0;
}

/**
 * @testcase            utc_wifi_manager_connect_hidden_ap_p
 * @since_tizen         4.0
 * @type                        Positive
 * @description         Connects the hidden access point asynchronously..
 * @scenario            Connect hidden AP. When AP is found the callback is triggered.
 */
int utc_wifi_manager_connect_hidden_ap_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;
	char ap_name[CONFIG_VALUE_LEN_MAX] = {0,};
	char ap_passphrase[CONFIG_VALUE_LEN_MAX] = {0,};
	wifi_manager_security_type_e type;

	if (!wifi_manager_get_value_from_configfile("WIFI_WPSACCESSPOINTNAME", ap_name)) {
		FPRINTF("[%s:%d] wifi_manager_get_value_from_configfile(WIFI_WPSACCESSPOINTNAME) failed \\n", __FILE__, __LINE__);
		return -1;
	}

	if (!wifi_manager_get_value_from_configfile("WIFI_ACCESSPOINTPIN", ap_passphrase)) {
		FPRINTF("[%s:%d] wifi_manager_get_value_from_configfile(WIFI_ACCESSPOINTPIN) failed \\n", __FILE__, __LINE__);
		return -1;
	}

	if (!g_bFeatureWifi) {
		ret = wifi_manager_connect_hidden_ap(g_hWifi, ap_name, 2, ap_passphrase, wifi_manager_connected_callback, NULL);
		CHECK_RETURN("wifi_manager_connect_hidden_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
	CHECK_RETURN("wifi_manager_scan", ret, WIFI_MANAGER_ERROR_NONE);
	RUN_GMAIN_LOOP;

	CHECK_RETURN(CALLBACK_RETURN, ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_foreach_found_ap(g_hWifi, wifi_manager_found_ap_callback, ap_name);
	CHECK_RETURN("wifi_manager_foreach_found_ap", ret, WIFI_MANAGER_ERROR_NONE);

	if (g_nCallbackRet != WIFI_MANAGER_ERROR_NONE) {
		/* AP is not found due to wrong environment or wrong user input */
		FPRINTF("[%s:%d] No AP found!\\n", __FILE__, __LINE__);
		return 0;
	}

	ret = wifi_manager_ap_get_security_type(g_hWifiAP, &type);
	CHECK_RETURN("wifi_manager_ap_get_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_connect_hidden_ap(g_hWifi, ap_name, type, ap_passphrase, wifi_manager_connected_callback, NULL);
	if (ret != WIFI_MANAGER_ERROR_NONE &&
			(type == WIFI_MANAGER_SECURITY_TYPE_WPA2_PSK || type == WIFI_MANAGER_SECURITY_TYPE_WPA_FT_PSK)) {
		PRINT_RETURN("wifi_manager_connect_hidden_ap", ret);
		/**
		 * wifi_manager_connect_hidden_ap treats WPA2_PSK or FT_WPA as WPA.
		 * This will be improved later.
		 */
		ret = wifi_manager_connect_hidden_ap(g_hWifi, ap_name,
				WIFI_MANAGER_SECURITY_TYPE_WPA_PSK, ap_passphrase, wifi_manager_connected_callback, NULL);
	}

	/* wifi_manager_connect_hidden_ap invokes the callback only if there is no error */
	CHECK_RETURN("wifi_manager_connect_hidden_ap", ret, WIFI_MANAGER_ERROR_NONE);

	RUN_GMAIN_LOOP;
	return 0;
}

/**
 * @testcase		utc_wifi_manager_update_ap_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_update_ap by passing invalid parameters.
 * @scenario		Pass Invalid paramers to update AP and ensure WIFI_MANAGER_ERROR_INVALID_PARAMETER is reported.
 */
int utc_wifi_manager_update_ap_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_update_ap(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_update_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_update_ap", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_update_ap_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Updates an existing AP.
 * @scenario		Updates the proxy address from AP info. Ensure no error.
 */
int utc_wifi_manager_update_ap_p(void)
{
	wifi_manager_ap_h hAP = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_update_ap(g_hWifi, g_hWifiAP);
		CHECK_RETURN("wifi_manager_update_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_pre_connect();
	CHECK_RETURN("wifi_manager_pre_connect", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_get_connected_ap(g_hWifi, &hAP);
	CHECK_RETURN("wifi_manager_get_connected_ap", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_proxy_address(hAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.1");
	CHECK_RETURN("wifi_manager_ap_set_gateway_address", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_update_ap(g_hWifi, hAP);
	CHECK_RETURN("wifi_manager_update_ap", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_forget_ap_async(g_hWifi, hAP,
					   wifi_manager_forget_ap_async_callback, NULL);
	CHECK_RETURN("wifi_manager_forget_ap_async", ret, WIFI_MANAGER_ERROR_NONE);
	RUN_GMAIN_LOOP;
    return 0;
}

/**
 * @testcase		utc_wifi_manager_disconnect_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify wifi_disconnect by passing invalid parameters.
 * @scenario		Try to disconnect Wi-Fi after deinitilaization and ensure WIFI_MANAGER_ERROR_INVALID_OPERATION is reported.
 */
int utc_wifi_manager_disconnect_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_disconnect(NULL, NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_disconnect", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
    } else {
	    CHECK_RETURN("wifi_manager_disconnect", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_disconnect_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Disconnects the access point asynchronously.
 * @scenario		Create AP handle and activate Wi-Fi. On acivattion Wi-Fi Disconnection will
 *					be initiated.
 */
int utc_wifi_manager_disconnect_p(void)
{
	wifi_manager_ap_h hAP = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_disconnect(g_hWifi, g_hWifiAP, wifi_manager_disconnected_callback, NULL);
		CHECK_RETURN("wifi_manager_disconnect", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_pre_connect();
	CHECK_RETURN("wifi_manager_pre_connect", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_get_connected_ap(g_hWifi, &hAP);
	CHECK_RETURN("wifi_manager_get_connected_ap", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_disconnect(g_hWifi, hAP, wifi_manager_disconnected_callback, NULL);
	PRINT_RETURN("wifi_manager_get_connected_ap", ret);
	RUN_GMAIN_LOOP;
	CHECK_RETURN(CALLBACK_RETURN, ret, WIFI_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_manager_connect_by_wps_pin_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify wifi_manager_connect_by_wps_pin by passing invalid parameters.
 * @scenario		Try to connect to an AP by WPA with invalid PIN. Ensure WIFI_MANAGER_ERROR_INVALID_OPERATION is reported.
 */
int utc_wifi_manager_connect_by_wps_pin_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_connect_by_wps_pin(NULL, NULL, NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_connect_by_wps_pin", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_connect_by_wps_pin", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_connect_by_wps_pbc_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify wifi_manager_connect_by_wps_pbc by passing invalid parameters.
 * @scenario		Try to connect to an AP by WPA after Wi-Fi deinitialization.
 *					Ensure no strange behaviour and WIFI_MANAGER_ERROR_INVALID_OPERATION is reported.
 */
int utc_wifi_manager_connect_by_wps_pbc_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_connect_by_wps_pbc(NULL, NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_connect_by_wps_pbc", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_connect_by_wps_pbc", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_connect_by_wps_pin_without_ssid_n
 * @since_tizen		4.0
 * @type			Negative
 * @description		Verify wifi_manager_connect_by_wps_pin_without_ssid by passing invalid parameters.
 * @scenario		Try to connect to an AP by WPA with invalid PIN. Ensure WIFI_MANAGER_ERROR_INVALID_OPERATION is reported.
 */
int utc_wifi_manager_connect_by_wps_pin_without_ssid_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_connect_by_wps_pin_without_ssid(NULL, NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_connect_by_wps_pin_without_ssid", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_connect_by_wps_pin_without_ssid", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_connect_by_wps_pbc_without_ssid_n
 * @since_tizen		4.0
 * @type			Negative
 * @description		Verify wifi_manager_connect_by_wps_pbc_without_ssid by passing invalid parameters.
 * @scenario		Try to connect to an AP by WPA after Wi-Fi deinitialization.
 *					Ensure no strange behaviour and WIFI_MANAGER_ERROR_INVALID_OPERATION is reported.
 */
int utc_wifi_manager_connect_by_wps_pbc_without_ssid_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_connect_by_wps_pbc_without_ssid(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_connect_by_wps_pbc_without_ssid", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_connect_by_wps_pbc_without_ssid", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_cancel_wps_n
 * @since_tizen		4.0
 * @type			Negative
 * @description		Verify wifi_manager_cancel_wps by passing invalid parameters.
 * @scenario		Try to connect to an AP by WPA after Wi-Fi deinitialization.
 *					Ensure no strange behaviour and WIFI_MANAGER_ERROR_INVALID_OPERATION is reported.
 */
int utc_wifi_manager_cancel_wps_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_cancel_wps(NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_cancel_wps", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_cancel_wps", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_get_connected_ap_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the handle of the connected access point.
 * @scenario		When Wi-Fi is connected, connected APs will be returned.
 *					When Wi-Fi is not connected, Initiate Scan and ensure no error.
 *					When AP is found, initiate connection and get the connected AP.
 */
int utc_wifi_manager_get_connected_ap_p(void)
{
	wifi_manager_ap_h hAP = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_get_connected_ap(g_hWifi, &hAP);
		CHECK_RETURN("wifi_manager_get_connected_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_pre_connect();
	CHECK_RETURN("wifi_manager_pre_connect", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_get_connected_ap(g_hWifi, &hAP);
	CHECK_RETURN("wifi_manager_get_connected_ap", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_get_connected_ap_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_get_connected_ap by passing invalid parameter.
 * @scenario		Pass NULL parameter and ensure WIFI_MANAGER_ERROR_INVALID_PARAMETER is reported.
 */
int utc_wifi_manager_get_connected_ap_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_get_connected_ap(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_get_connected_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_get_connected_ap", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_forget_ap_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify wifi_forget_ap by passing invalid parameters.
 * @scenario		Try to forget the invalid AP.
 *					Ensure no strange behaviour and WIFI_MANAGER_ERROR_INVALID_PARAMETER is reported.
 */
int utc_wifi_manager_forget_ap_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_forget_ap(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_forget_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_forget_ap", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_forget_ap_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Deletes the information of stored access point and disconnects it when it connected.
 * @scenario		Forget a valid Access Point and Ensure no error.
 */
int utc_wifi_manager_forget_ap_p(void)
{
	wifi_manager_ap_h hAP = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_forget_ap(g_hWifi, hAP);
		CHECK_RETURN("wifi_manager_forget_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_pre_connect();
	CHECK_RETURN("wifi_manager_pre_connect", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_get_connected_ap(g_hWifi, &hAP);
	CHECK_RETURN("wifi_manager_get_connected_ap", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_set_connection_state_changed_cb(g_hWifi, wifi_manager_forget_ap_callback, NULL);
	CHECK_RETURN("wifi_manager_set_connection_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_forget_ap(g_hWifi, hAP);
	CHECK_RETURN("wifi_manager_forget_ap", ret, WIFI_MANAGER_ERROR_NONE);

	RUN_GMAIN_LOOP;

	ret = wifi_manager_unset_connection_state_changed_cb(g_hWifi);
	CHECK_RETURN("wifi_manager_unset_connection_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_forget_ap_async_n
 * @since_tizen		5.0
 * @type			Negative
 * @description		Verify wifi_forget_ap_async by passing invalid parameters.
 * @scenario		Try to forget the invalid AP.
 *					Ensure no strange behaviour and WIFI_MANAGER_ERROR_INVALID_PARAMETER is reported.
 */
int utc_wifi_manager_forget_ap_async_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_forget_ap_async(NULL, NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_forget_ap_async", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_forget_ap_async", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_forget_ap_async_p
 * @since_tizen		5.0
 * @type			Positive
 * @description		Deletes the information of stored access point and disconnects it when it connected asynchronously.
 * @scenario		Forget a valid Access Point and Ensure no error.
 */
int utc_wifi_manager_forget_ap_async_p(void)
{
	wifi_manager_ap_h hAP = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_forget_ap_async(g_hWifi, hAP,
						   wifi_manager_forget_ap_async_callback,
						   NULL);
		CHECK_RETURN("wifi_manager_forget_ap_async", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_pre_connect();
	CHECK_RETURN("wifi_manager_pre_connect", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_get_connected_ap(g_hWifi, &hAP);
	CHECK_RETURN("wifi_manager_get_connected_ap", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_set_connection_state_changed_cb(g_hWifi, wifi_manager_connection_state_changed_callback, NULL);
	CHECK_RETURN("wifi_manager_set_connection_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_forget_ap_async(g_hWifi, hAP,
					   wifi_manager_forget_ap_async_callback, NULL);
	CHECK_RETURN("wifi_manager_forget_ap_async", ret, WIFI_MANAGER_ERROR_NONE);
	RUN_GMAIN_LOOP;
	CHECK_RETURN(CALLBACK_RETURN, g_nCallbackRet, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_pre_connect();
	CHECK_RETURN("wifi_manager_pre_connect", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_unset_connection_state_changed_cb(g_hWifi);
	CHECK_RETURN("wifi_manager_unset_connection_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_bssid_scan_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify wifi_manager_bssid_scan by passing invalid parameters
 * @scenario		Pass invalid callback and ensure any callback is not returned.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_bssid_scan_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_bssid_scan(g_hWifi, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_bssid_scan", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_bssid_scan", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_bssid_scan_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description		Starts bssid scan, asynchronously.
 * @scenario		Scan for the APs with BSSID, ESSID and RSSI info.
 *					When bssid scan is finished callback is triggered.
 */
int utc_wifi_manager_bssid_scan_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_bssid_scan(g_hWifi, wifi_manager_bssid_scanned_callback, NULL);
		CHECK_RETURN("wifi_manager_bssid_scan", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_pre_activate();
	CHECK_RETURN("wifi_manager_pre_activate", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_bssid_scan(g_hWifi, wifi_manager_bssid_scanned_callback, NULL);
	PRINT_RETURN("wifi_manager_bssid_scan", ret);
	RUN_GMAIN_LOOP;
	CHECK_RETURN(CALLBACK_RETURN, ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_foreach_found_bssid_ap_n
 * @since_tizen		4.0
 * @type			Negative
 * @description 	Verify wifi_manager_foreach_found_bssid_ap by passing invalid parameters
 * @scenario		Pass invalid parameters and ensure any AP is not returned.
 *					Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_foreach_found_bssid_ap_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_foreach_found_bssid_ap(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_foreach_found_bssid_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_foreach_found_bssid_ap", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_foreach_found_bssid_ap_p
 * @since_tizen		4.0
 * @type			Positive
 * @description		Gets the result of bssid ap scan.
 * @scenario		Scan for BSSID, ESSID, RSSI. When AP is found, callback is triggered.
 */
int utc_wifi_manager_foreach_found_bssid_ap_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_foreach_found_bssid_ap(g_hWifi, wifi_manager_foreach_found_bssid_ap_callback, NULL);
		CHECK_RETURN("wifi_manager_foreach_found_bssid_ap", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_pre_deactivate();
	CHECK_RETURN("wifi_manager_pre_deactivate", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_bssid_scan(g_hWifi, wifi_manager_bssid_scanned_callback, NULL);
	PRINT_RETURN("wifi_manager_bssid_scan", ret);
	RUN_GMAIN_LOOP;

	ret = wifi_manager_foreach_found_bssid_ap(g_hWifi, wifi_manager_foreach_found_bssid_ap_callback, NULL);
	CHECK_RETURN("wifi_manager_foreach_found_bssid_ap", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_specific_scan_create_p
 * @since_tizen		4.0
 * @type			Positive
 * @description		Gets specific AP multi scan handle.
 * @scenario		Initialize Wi-Fi. Create & destroy specific AP multi scan handle.
 */
int utc_wifi_manager_specific_scan_create_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;
	wifi_manager_specific_scan_h specific_scan = NULL;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_specific_scan_create(g_hWifi, &specific_scan);
		CHECK_RETURN("wifi_manager_specific_scan_create", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_specific_scan_create(g_hWifi, &specific_scan);
	CHECK_RETURN("wifi_manager_specific_scan_create", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_specific_scan_destroy(g_hWifi, specific_scan);
	CHECK_RETURN("wifi_manager_specific_scan_destroy", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_specific_scan_create_n
 * @since_tizen		4.0
 * @type			Negative
 * @description		Gets specific AP multi scan handle.
 * @scenario		Gets specific AP multi scan handle with invalid parameter. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_specific_scan_create_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;
	wifi_manager_specific_scan_h specific_scan = NULL;

	ret = wifi_manager_specific_scan_create(NULL, &specific_scan);
	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_specific_scan_create", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_specific_scan_create", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_specific_scan_destroy_p
 * @since_tizen		4.0
 * @type			Positive
 * @description		Gets specific AP multi scan handle.
 * @scenario		Initialize Wi-Fi. Create & destroy specific AP multi scan handle.
 */
int utc_wifi_manager_specific_scan_destroy_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;
	wifi_manager_specific_scan_h specific_scan = NULL;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_specific_scan_destroy(g_hWifi, specific_scan);
		CHECK_RETURN("wifi_manager_specific_scan_destroy", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_specific_scan_create(g_hWifi, &specific_scan);
	CHECK_RETURN("wifi_manager_specific_scan_create", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_specific_scan_destroy(g_hWifi, specific_scan);
	CHECK_RETURN("wifi_manager_specific_scan_destroy", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_specific_scan_destroy_n
 * @since_tizen		4.0
 * @type			Negative
 * @description		Gets specific AP multi scan handle.
 * @scenario		Initialize Wi-Fi. Destroy specific AP multi scan handle with invalid parameter.
 */
int utc_wifi_manager_specific_scan_destroy_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_specific_scan_destroy(g_hWifi, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_specific_scan_destroy", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_specific_scan_destroy", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_specific_scan_set_ssid_p
 * @since_tizen		4.0
 * @type			Positive
 * @description		Sets specific AP SSID in multi scan handle.
 * @scenario		Sets specifci AP SSID in multi scan handle.
 */
int utc_wifi_manager_specific_scan_set_ssid_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;
	char ssid[CONFIG_VALUE_LEN_MAX];
	wifi_manager_specific_scan_h specific_scan = NULL;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_specific_scan_set_ssid(specific_scan, ssid);
		CHECK_RETURN("wifi_manager_specific_scan_set_ssid", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!wifi_manager_get_value_from_configfile("WIFI_WPSACCESSPOINTNAME", ssid)) {
		FPRINTF("[%s:%d] wifi_manager_get_value_from_configfile(WIFI_WPSACCESSPOINTNAME) failed \\n", __FILE__, __LINE__);
		return -1;
	}

	ret = wifi_manager_specific_scan_create(g_hWifi, &specific_scan);
	CHECK_RETURN("wifi_manager_specific_scan_create", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_specific_scan_set_ssid(specific_scan, ssid);
	CHECK_RETURN("wifi_manager_specific_scan_set_ssid", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_specific_scan_destroy(g_hWifi, specific_scan);
	CHECK_RETURN("wifi_manager_specific_scan_destroy", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_specific_scan_set_ssid_n
 * @since_tizen		4.0
 * @type			Negative
 * @description		Sets specific AP SSID in multi scan handle.
 * @scenario		Sets invalid parameter in multi scan handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_specific_scan_set_ssid_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_specific_scan_set_ssid(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_specific_scan_set_ssid", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_specific_scan_set_ssid", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_specific_scan_set_freq_p
 * @since_tizen		4.0
 * @type			Positive
 * @description		Sets specific AP frequency in multi scan handle.
 * @scenario		Sets specifci AP frequency in multi scan handle.
 */
int utc_wifi_manager_specific_scan_set_freq_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;
	wifi_manager_specific_scan_h specific_scan = NULL;
	int freq = 2412;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_specific_scan_set_freq(specific_scan, freq);
		CHECK_RETURN("wifi_manager_specific_scan_set_freq", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_specific_scan_create(g_hWifi, &specific_scan);
	CHECK_RETURN("wifi_manager_specific_scan_create", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_specific_scan_set_freq(specific_scan, freq);
	CHECK_RETURN("wifi_manager_specific_scan_set_freq", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_specific_scan_destroy(g_hWifi, specific_scan);
	CHECK_RETURN("wifi_manager_specific_scan_destroy", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_specific_scan_set_freq_n
 * @since_tizen		4.0
 * @type			Negative
 * @description		Sets specific AP frequency in multi scan handle.
 * @scenario		Sets invalid parameter in multi scan handle. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_specific_scan_set_freq_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_specific_scan_set_freq(NULL, 0);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_specific_scan_set_freq", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_specific_scan_set_freq", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_specific_ap_start_multi_scan_p
 * @since_tizen		4.0
 * @type			Positive
 * @description		Starts specific AP multi scan, asynchronously.
 * @scenario		Scan for specific AP set in multi scan handle. When scan is done the callback is triggered.
 */
int utc_wifi_manager_specific_ap_start_multi_scan_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;
	wifi_manager_specific_scan_h specific_scan = NULL;
	char ssid[CONFIG_VALUE_LEN_MAX];

	if (!g_bFeatureWifi) {
		ret = wifi_manager_specific_ap_start_multi_scan(g_hWifi, specific_scan, wifi_manager_multi_scan_callback, NULL);
		CHECK_RETURN("wifi_manager_specific_ap_start_multi_scan", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!wifi_manager_get_value_from_configfile("WIFI_WPSACCESSPOINTNAME", ssid)) {
		FPRINTF("[%s:%d] wifi_manager_get_value_from_configfile(WIFI_WPSACCESSPOINTNAME) failed \\n", __FILE__, __LINE__);
		return -1;
	}

	ret = wifi_manager_specific_scan_create(g_hWifi, &specific_scan);
	CHECK_RETURN("wifi_manager_specific_scan_create", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_specific_scan_set_ssid(specific_scan, ssid);
	CHECK_RETURN("wifi_manager_specific_scan_set_ssid", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_specific_ap_start_multi_scan(g_hWifi, specific_scan, wifi_manager_multi_scan_callback, NULL);
	PRINT_RETURN("wifi_manager_specific_ap_start_multi_scan", ret);
	RUN_GMAIN_LOOP;
	CHECK_RETURN(CALLBACK_RETURN, ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_specific_scan_destroy(g_hWifi, specific_scan);
	CHECK_RETURN("wifi_manager_specific_scan_destroy", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_specific_ap_start_multi_scan_n
 * @since_tizen		4.0
 * @type			Negative
 * @description		Starts specific AP multi scan, asynchronously.
 * @scenario		Scan for specific AP set in multi scan handle with invalid parameter. Ensure return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_specific_ap_start_multi_scan_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_specific_ap_start_multi_scan(g_hWifi, NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_specific_ap_start_multi_scan", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_specific_ap_start_multi_scan", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_add_vsie_p
 * @since_tizen		5.0
 * @type			Positive
 * @description		Add the Wi-Fi VSIE to a specific frame type.
 * @scenario		Invoke wifi_manager_add_vsie() with valid parameter.
 */
int utc_wifi_manager_add_vsie_p(void)
{
	int ret;
	const char *vsie_str = "dd0411223301";

	if (!g_bFeatureWifi) {
		ret = wifi_manager_add_vsie(g_hWifi, WIFI_MANAGER_VSIE_FRAME_PROBE_REQ, vsie_str);
		CHECK_RETURN("wifi_manager_add_vsie", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_add_vsie(g_hWifi, WIFI_MANAGER_VSIE_FRAME_PROBE_REQ, vsie_str);
		CHECK_RETURN("wifi_manager_add_vsie", ret, WIFI_MANAGER_ERROR_NONE);
		ret = wifi_manager_add_vsie(g_hWifi, WIFI_MANAGER_VSIE_FRAME_ASSOC_REQ, vsie_str);
		CHECK_RETURN("wifi_manager_add_vsie", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_add_vsie_n
 * @since_tizen		5.0
 * @type			Negative
 * @description		wifi_manager_add_vsie() should be failed.
 * @scenario		Invoke wifi_manager_add_vsie() with invalid parameter.
 */
int utc_wifi_manager_add_vsie_n(void)
{
	int ret;
	const char *vsie_str = "dd0411223301";

	if (!g_bFeatureWifi) {
		ret = wifi_manager_add_vsie(NULL, WIFI_MANAGER_VSIE_FRAME_PROBE_REQ, NULL);
		CHECK_RETURN("wifi_manager_add_vsie", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_add_vsie(NULL, WIFI_MANAGER_VSIE_FRAME_PROBE_REQ, vsie_str);
		CHECK_RETURN("wifi_manager_add_vsie", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_add_vsie(g_hWifi, WIFI_MANAGER_VSIE_FRAME_ASSOC_REQ, NULL);
		CHECK_RETURN("wifi_manager_add_vsie", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_add_vsie(NULL, WIFI_MANAGER_VSIE_FRAME_REASSOC, NULL);
		CHECK_RETURN("wifi_manager_add_vsie", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);

		ret = wifi_manager_add_vsie(g_hWifi, -5, vsie_str);
		CHECK_RETURN("wifi_manager_add_vsie", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_get_vsie_p
 * @since_tizen		5.0
 * @type			Positive
 * @description		get the Wi-Fi VSIE from a specific frame type.
 * @scenario		Invoke wifi_manager_get_vsie() with valid parameter.
 */
int utc_wifi_manager_get_vsie_p(void)
{
	int ret;
	char *vsie_str = NULL;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_get_vsie(g_hWifi, WIFI_MANAGER_VSIE_FRAME_PROBE_REQ, &vsie_str);
		CHECK_RETURN("wifi_manager_get_vsie", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_get_vsie(g_hWifi, WIFI_MANAGER_VSIE_FRAME_PROBE_REQ, &vsie_str);
		CHECK_RETURN("wifi_manager_get_vsie", ret, WIFI_MANAGER_ERROR_NONE);
		free(vsie_str);

		ret = wifi_manager_get_vsie(g_hWifi, WIFI_MANAGER_VSIE_FRAME_ASSOC_REQ, &vsie_str);
		CHECK_RETURN("wifi_manager_get_vsie", ret, WIFI_MANAGER_ERROR_NONE);
		free(vsie_str);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_get_vsie_n
 * @since_tizen		5.0
 * @type			Negative
 * @description		wifi_manager_get_vsie() should be failed.
 * @scenario		Invoke wifi_manager_get_vsie() with valid parameter.
 */
int utc_wifi_manager_get_vsie_n(void)
{
	int ret;
	char *vsie_str = NULL;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_get_vsie(NULL, -5,  NULL);
		CHECK_RETURN("wifi_manager_get_vsie", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_get_vsie(NULL, WIFI_MANAGER_VSIE_FRAME_PROBE_REQ, &vsie_str);
		CHECK_RETURN("wifi_manager_get_vsie", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_get_vsie(g_hWifi, WIFI_MANAGER_VSIE_FRAME_ASSOC_REQ, NULL);
		CHECK_RETURN("wifi_manager_get_vsie", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_get_vsie(NULL, WIFI_MANAGER_VSIE_FRAME_REASSOC, NULL);
		CHECK_RETURN("wifi_manager_get_vsie", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_get_vsie(NULL, -5, NULL);
		CHECK_RETURN("wifi_manager_get_vsie", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_get_vsie(g_hWifi, -5, &vsie_str);
		CHECK_RETURN("wifi_manager_get_vsie", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_remove_vsie_p
 * @since_tizen		5.0
 * @type			Positive
 * @description		remove the Wi-Fi VSIE from a specific frame type.
 * @scenario		Invoke wifi_manager_remove_vsie() with valid parameter.
 */
int utc_wifi_manager_remove_vsie_p(void)
{
	int ret;
	const char *vsie_str = "dd0411223301";

	if (!g_bFeatureWifi) {
		ret = wifi_manager_remove_vsie(g_hWifi, WIFI_MANAGER_VSIE_FRAME_PROBE_REQ, vsie_str);
		CHECK_RETURN("wifi_manager_remove_vsie", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_remove_vsie(g_hWifi, WIFI_MANAGER_VSIE_FRAME_PROBE_REQ, vsie_str);
		CHECK_RETURN("wifi_manager_remove_vsie", ret, WIFI_MANAGER_ERROR_NONE);
		ret = wifi_manager_remove_vsie(g_hWifi, WIFI_MANAGER_VSIE_FRAME_ASSOC_REQ, vsie_str);
		CHECK_RETURN("wifi_manager_remove_vsie", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_remove_vsie_n
 * @since_tizen		5.0
 * @type			Negative
 * @description		wifi_manager_remove_vsie() should be failed.
 * @scenario		Invoke wifi_manager_remove_vsie() with invalid parameter.
 */
int utc_wifi_manager_remove_vsie_n(void)
{
	int ret;
	const char *vsie_str = "dd0411223301";

	if (!g_bFeatureWifi) {
		ret = wifi_manager_remove_vsie(NULL, -5, NULL);
		CHECK_RETURN("wifi_manager_remove_vsie", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_remove_vsie(NULL, WIFI_MANAGER_VSIE_FRAME_ASSOC_REQ, vsie_str);
		CHECK_RETURN("wifi_manager_remove_vsie", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_remove_vsie(g_hWifi, WIFI_MANAGER_VSIE_FRAME_REASSOC, NULL);
		CHECK_RETURN("wifi_manager_remove_vsie", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_remove_vsie(NULL, -5, NULL);
		CHECK_RETURN("wifi_manager_remove_vsie", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);

		/*
		 * operation failed error is returned when VSIE string doesn't exist.
		 */
		ret = wifi_manager_remove_vsie(g_hWifi, WIFI_MANAGER_VSIE_FRAME_PROBE_REQ, vsie_str);
		CHECK_RETURN("wifi_manager_remove_vsie", ret, WIFI_MANAGER_ERROR_OPERATION_FAILED);

		ret = wifi_manager_remove_vsie(g_hWifi, -5, vsie_str);
		CHECK_RETURN("wifi_manager_remove_vsie", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_set_ip_conflict_cb_n
 * @since_tizen 	5.0
 * @type			Negative
 * @description 	wifi_manager_set_ip_conflict_cb() should be failed.
 * @scenario		Invoke wifi_manager_set_ip_conflict_cb() with invalid parameter.
 */
int utc_wifi_manager_set_ip_conflict_cb_n(void)
{
    int ret;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_set_ip_conflict_cb(NULL, NULL, NULL);
		CHECK_RETURN("wifi_manager_set_ip_conflict_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		ret = wifi_manager_set_ip_conflict_cb(NULL, wifi_manager_ip_conflict_callback, NULL);
		CHECK_RETURN("wifi_manager_set_ip_conflict_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_set_ip_conflict_cb(g_hWifi, NULL, NULL);
		CHECK_RETURN("wifi_manager_set_ip_conflict_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_set_ip_conflict_cb(NULL, NULL, NULL);
		CHECK_RETURN("wifi_manager_set_ip_conflict_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_unset_ip_conflict_cb_n
 * @since_tizen 	5.0
 * @type			Negative
 * @description 	wifi_manager_unset_ip_conflict_cb() should be failed.
 * @scenario		Invoke wifi_manager_unset_ip_conflict_cb() with invalid parameter.
 */
int utc_wifi_manager_unset_ip_conflict_cb_n(void)
{
    int	ret = wifi_manager_unset_ip_conflict_cb(NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_unset_ip_conflict_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_unset_ip_conflict_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_set_ip_conflict_detect_enable_p
 * @since_tizen 	5.0
 * @type			Positive
 * @description 	Enables or disables IP conflict detection.
 * @scenario		Invoke wifi_manager_set_ip_conflict_detect_enable() with valid parameter.
 */
int utc_wifi_manager_set_ip_conflict_detect_enable_p(void)
{
    int ret;
	bool state;



	if (!g_bFeatureWifi) {
		ret = wifi_manager_set_ip_conflict_detect_enable(g_hWifi, true);
		CHECK_RETURN("wifi_manager_set_ip_conflict_detect_enable", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		ret = wifi_manager_ip_conflict_detect_is_enabled(g_hWifi, &state);
		CHECK_RETURN("wifi_manager_ip_conflict_detect_is_enabled", ret, WIFI_MANAGER_ERROR_NONE);

		if (state)
			ret = wifi_manager_set_ip_conflict_detect_enable(g_hWifi, false);
		else
			ret = wifi_manager_set_ip_conflict_detect_enable(g_hWifi, true);

		CHECK_RETURN("wifi_manager_set_ip_conflict_detect_enable", ret, WIFI_MANAGER_ERROR_NONE);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_set_ip_conflict_detect_enable_n
 * @since_tizen 	5.0
 * @type			Negative
 * @description 	wifi_manager_set_ip_conflict_detect_enable() should be failed.
 * @scenario		Invoke wifi_manager_set_ip_conflict_detect_enable() with invalid parameter.
 */
int utc_wifi_manager_set_ip_conflict_detect_enable_n(void)
{
    int ret = wifi_manager_set_ip_conflict_detect_enable(NULL, true);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_set_ip_conflict_detect_enable", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_set_ip_conflict_detect_enable", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_ip_conflict_detect_is_enabled_p
 * @since_tizen 	5.0
 * @type			Positive
 * @description 	Checks whether IP conflict detection is enabled.
 * @scenario		Invoke wifi_manager_ip_conflict_detect_is_enabled() with valid parameter.
 */
int utc_wifi_manager_ip_conflict_detect_is_enabled_p(void)
{
	bool state;

	int ret = wifi_manager_ip_conflict_detect_is_enabled(g_hWifi, &state);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ip_conflict_detect_is_enabled", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ip_conflict_detect_is_enabled", ret, WIFI_MANAGER_ERROR_NONE);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_ip_conflict_detect_is_enabled_n
 * @since_tizen 	5.0
 * @type			Negative
 * @description 	wifi_manager_ip_conflict_detect_is_enabled() should be failed.
 * @scenario		Invoke wifi_manager_ip_conflict_detect_is_enabled() with invalid parameter.
 */
int utc_wifi_manager_ip_conflict_detect_is_enabled_n(void)
{
	int ret;
	bool state;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ip_conflict_detect_is_enabled(NULL, &state);
		CHECK_RETURN("wifi_manager_ip_conflict_detect_is_enabled", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		ret = wifi_manager_ip_conflict_detect_is_enabled(NULL, &state);
		CHECK_RETURN("wifi_manager_ip_conflict_detect_is_enabled", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_ip_conflict_detect_is_enabled(g_hWifi, NULL);
		CHECK_RETURN("wifi_manager_ip_conflict_detect_is_enabled", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_ip_conflict_detect_is_enabled(NULL, NULL);
		CHECK_RETURN("wifi_manager_ip_conflict_detect_is_enabled", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_get_ip_conflict_state_p
 * @since_tizen 	5.0
 * @type			Positive
 * @description 	Gets the state of the IP conflict.
 * @scenario		Invoke wifi_manager_get_ip_conflict_state() with valid parameter.
 */
int utc_wifi_manager_get_ip_conflict_state_p(void)
{
	wifi_manager_ip_conflict_state_e state;

	int ret = wifi_manager_get_ip_conflict_state(g_hWifi, &state);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_get_ip_conflict_state", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_get_ip_conflict_state", ret, WIFI_MANAGER_ERROR_NONE);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_get_ip_conflict_state_n
 * @since_tizen 	5.0
 * @type			Negative
 * @description 	wifi_manager_get_ip_conflict_state() should be failed.
 * @scenario		Invoke wifi_manager_get_ip_conflict_state() with invalid parameter.
 */
int utc_wifi_manager_get_ip_conflict_state_n(void)
{
	int ret;
	wifi_manager_ip_conflict_state_e state;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_get_ip_conflict_state(NULL, &state);
		CHECK_RETURN("wifi_manager_get_ip_conflict_state", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		ret = wifi_manager_get_ip_conflict_state(g_hWifi, NULL);
		CHECK_RETURN("wifi_manager_get_ip_conflict_state", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_get_ip_conflict_state(NULL, &state);
		CHECK_RETURN("wifi_manager_get_ip_conflict_state", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_get_ip_conflict_state(NULL, NULL);
		CHECK_RETURN("wifi_manager_get_ip_conflict_state", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_get_wps_generated_pin_p
 * @since_tizen		5.0
 * @type			Positive
 * @description		get the WPS generated PIN code.
 * @scenario		Invoke wifi_manager_get_wps_generated_pin() with valid parameter.
 */
int utc_wifi_manager_get_wps_generated_pin_p(void)
{
	int ret;
	char *wps_pin = NULL;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_get_wps_generated_pin(g_hWifi, &wps_pin);
		CHECK_RETURN("wifi_manager_get_wps_generated_pin", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_get_wps_generated_pin(g_hWifi, &wps_pin);
		CHECK_RETURN("wifi_manager_get_wps_generated_pin", ret, WIFI_MANAGER_ERROR_NONE);
		free(wps_pin);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_get_wps_generated_pin_n
 * @since_tizen		5.0
 * @type			Negative
 * @description		wifi_manager_get_wps_generated_pin() should be failed.
 * @scenario		Invoke wifi_manager_get_wps_generated_pin() with valid parameter.
 */
int utc_wifi_manager_get_wps_generated_pin_n(void)
{
	int ret;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_get_wps_generated_pin(NULL, NULL);
		CHECK_RETURN("wifi_manager_get_wps_generated_pin", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_get_wps_generated_pin(NULL, NULL);
		CHECK_RETURN("wifi_manager_get_wps_generated_pin", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_is_5ghz_band_supported_p
 * @since_tizen		5.5
 * @type			Positive
 * @description		Gets whether 5Ghz Wi-Fi band is supported.
 * @scenario		Invoke wifi_manager_is_5ghz_band_supported() with valid parameter.
 */
int utc_wifi_manager_is_5ghz_band_supported_p(void)
{
	int ret;
	bool supported = false;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_is_5ghz_band_supported(g_hWifi, &supported);
		CHECK_RETURN("wifi_manager_is_5ghz_band_supported", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_is_5ghz_band_supported(g_hWifi, &supported);
		CHECK_RETURN("wifi_manager_is_5ghz_band_supported", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_is_5ghz_band_supported_n1
 * @since_tizen		5.5
 * @type			Negative
 * @description		wifi_manager_is_5ghz_band_supported() should be failed.
 * @scenario		Invoke wifi_manager_is_5ghz_band_supported() with invalid parameter.
 */
int utc_wifi_manager_is_5ghz_band_supported_n1(void)
{
	int ret;
	bool supported = false;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_is_5ghz_band_supported(NULL, &supported);
		CHECK_RETURN("wifi_manager_is_5ghz_band_supported", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_is_5ghz_band_supported(NULL, &supported);
		CHECK_RETURN("wifi_manager_is_5ghz_band_supported", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_is_5ghz_band_supported_n2
 * @since_tizen		5.5
 * @type			Negative
 * @description		wifi_manager_is_5ghz_band_supported() should be failed.
 * @scenario		Invoke wifi_manager_is_5ghz_band_supported() with invalid parameter.
 */
int utc_wifi_manager_is_5ghz_band_supported_n2(void)
{
	int ret;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_is_5ghz_band_supported(g_hWifi, NULL);
		CHECK_RETURN("wifi_manager_is_5ghz_band_supported", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_is_5ghz_band_supported(g_hWifi, NULL);
		CHECK_RETURN("wifi_manager_is_5ghz_band_supported", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_specific_scan_get_max_ssids_p
 * @since_tizen		5.5
 * @type			Positive
 * @description		Gets the maximum number of SSIDs supported by wlan chipset for scan operation.
 * @scenario		Invoke wifi_manager_specific_scan_get_max_ssids() with valid parameter.
 */
int utc_wifi_manager_specific_scan_get_max_ssids_p(void)
{
	int ret;
	int max_scan_ssids = 0;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_specific_scan_get_max_ssids(g_hWifi, &max_scan_ssids);
		CHECK_RETURN("wifi_manager_specific_scan_get_max_ssids", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_specific_scan_get_max_ssids(g_hWifi, &max_scan_ssids);
		CHECK_RETURN("wifi_manager_specific_scan_get_max_ssids", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_specific_scan_get_max_ssids_n1
 * @since_tizen		5.5
 * @type			Negative
 * @description		wifi_manager_specific_scan_get_max_ssids() should be failed.
 * @scenario		Invoke wifi_manager_specific_scan_get_max_ssids() with invalid parameter.
 */
int utc_wifi_manager_specific_scan_get_max_ssids_n1(void)
{
	int ret;
	int max_scan_ssids = 0;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_specific_scan_get_max_ssids(NULL, &max_scan_ssids);
		CHECK_RETURN("wifi_manager_specific_scan_get_max_ssids", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_specific_scan_get_max_ssids(NULL, &max_scan_ssids);
		CHECK_RETURN("wifi_manager_specific_scan_get_max_ssids", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_specific_scan_get_max_ssids_n2
 * @since_tizen		5.5
 * @type			Negative
 * @description		wifi_manager_specific_scan_get_max_ssids() should be failed.
 * @scenario		Invoke wifi_manager_specific_scan_get_max_ssids() with invalid parameter.
 */
int utc_wifi_manager_specific_scan_get_max_ssids_n2(void)
{
	int ret;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_specific_scan_get_max_ssids(g_hWifi, NULL);
		CHECK_RETURN("wifi_manager_specific_scan_get_max_ssids", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		ret = wifi_manager_specific_scan_get_max_ssids(g_hWifi, NULL);
		CHECK_RETURN("wifi_manager_specific_scan_get_max_ssids", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
