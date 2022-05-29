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

//& set: WifiManagerAP

/**
 * @function		utc_wifi_manager_ap_startup
 * @description		Creates the access point handle. Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_manager_ap_startup(void)
{
	g_bFeatureWifi = wifi_manager_check_feature_supported(FEATURE_WIFI);

	int ret = wifi_manager_initialize(&g_hWifi);
	PRINT_RETURN("wifi_manager_initialize", ret);

	ret = wifi_manager_ap_create(g_hWifi, WIFI_AP_NAME, &g_hWifiAP);
	PRINT_RETURN("wifi_manager_ap_create", ret);
}

/**
 * @function		utc_wifi_manager_ap_cleanup
 * @description		Destroys the access point handle. Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_manager_ap_cleanup(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (g_hWifiAP) {
		ret = wifi_manager_ap_destroy(g_hWifiAP);
		PRINT_RETURN("wifi_manager_ap_destroy", ret);
	}

	ret = wifi_manager_deinitialize(g_hWifi);
	PRINT_RETURN("wifi_manager_deinitialize", ret);
}

/**
 * @testcase		utc_wifi_manager_ap_create_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Creates the access point handle.
 * @scenario		Create access point, check the status and destroy it
 */
int utc_wifi_manager_ap_create_p(void)
{
	wifi_manager_ap_h hAp;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_create(g_hWifi, WIFI_AP_NAME, &hAp);
		CHECK_RETURN("wifi_manager_ap_create", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_create(g_hWifi, WIFI_AP_NAME, &hAp);
	CHECK_RETURN("wifi_manager_ap_create", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_destroy(hAp);
	CHECK_RETURN("wifi_manager_ap_destroy", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_create_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_create by passing Invalid ESSID, AP Information
 * @scenario		Pass invalid AP information. Access point handle shall not be created.
 */
int utc_wifi_manager_ap_create_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_create(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_create", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_create", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_hidden_create_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Creates the hidden access point handle
 * @scenario		create hidden access point, check the status and destroy it
 */
int utc_wifi_manager_ap_hidden_create_p(void)
{
	wifi_manager_ap_h hAp = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_hidden_create(g_hWifi, WIFI_AP_NAME, &hAp);
		CHECK_RETURN("wifi_manager_ap_hidden_create", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_hidden_create(g_hWifi, WIFI_AP_NAME, &hAp);
	CHECK_RETURN("wifi_manager_ap_hidden_create", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_destroy(hAp);
	CHECK_RETURN("wifi_manager_ap_destroy", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_hidden_create_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_create by passing Invalid ESSID, AP Information
 * @scenario		Pass invalid AP information. Hidden access point handle should not be created.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_hidden_create_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_hidden_create(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_hidden_create", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_hidden_create", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_clone_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Clones the access point handle.
 * @scenario		Clone access point, check the status and destroy it
 */
int utc_wifi_manager_ap_clone_p(void)
{
	wifi_manager_ap_h cloned_ap;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_clone(&cloned_ap, g_hWifiAP);
		CHECK_RETURN("wifi_manager_ap_clone", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_clone(&cloned_ap, g_hWifiAP);
	CHECK_RETURN("wifi_manager_ap_clone", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_destroy(cloned_ap);
	CHECK_RETURN("wifi_manager_ap_destroy", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_clone_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_clone API by passing the invalid parameters
 * @scenario		Pass invalid access point parameters. Access point should not be cloned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_clone_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_clone(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_clone", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_clone", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_essid_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets ESSID (Extended Service Set Identifier).
 * @scenario		Check AP validity and get essid from AP information. Check the status and
 *					delete essid.
 */
int utc_wifi_manager_ap_get_essid_p(void)
{
	char *essid = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_essid(g_hWifiAP, &essid);
	FREE_MEMORY(essid);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_essid", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_essid", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_essid_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_essid by passing invalid parameters(ap,essid)
 * @scenario		Pass invalid AP information. Proper essid should not be returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_essid_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_essid(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_essid", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_essid", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_raw_ssid_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description		Gets raw SSID (Service Set Identifier).
 * @scenario		Check AP validity and get raw ssid from AP information. Check the status and
 *					delete raw ssid.
 */
int utc_wifi_manager_ap_get_raw_ssid_p(void)
{
	char *raw_ssid = NULL;
	int raw_ssid_len;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_raw_ssid(g_hWifiAP, &raw_ssid, &raw_ssid_len);
	FREE_MEMORY(raw_ssid);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_raw_ssid", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_raw_ssid", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_raw_ssid_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_raw_ssid by passing invalid parameters(ap,raw_ssid,size)
 * @scenario		Pass invalid AP information. Proper raw ssid should not be returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_raw_ssid_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_raw_ssid(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_raw_ssid", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_raw_ssid", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_bssid_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets BSSID (Basic Service Set Identifier).
 * @scenario		Check AP validity and get bssid from AP information. Check the return value
 *					and free the bssid
 */
int utc_wifi_manager_ap_get_bssid_p(void)
{
	char *bssid = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_bssid(g_hWifiAP, &bssid);
	FREE_MEMORY(bssid);

	if (!g_bFeatureWifi) {
        CHECK_RETURN("wifi_manager_ap_get_bssid", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_bssid", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_bssid_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_bssid by passing invalid parameters(ap, bssid)
 * @scenario		Pass invalid AP info make sure proper bssid is not returned
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_bssid_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_bssid(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_bssid", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_bssid", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_rssi_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the RSSI.
 * @scenario		Check AP validity and get RSSI from AP information. Check the return value.
 */
int utc_wifi_manager_ap_get_rssi_p(void)
{
	int rssi = 0;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_rssi(g_hWifiAP, &rssi);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_rssi", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_rssi", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_rssi_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_rssi by passing invalid parameters(ap, rssi).
 * @scenario		Pass invalid AP information. Proper RSSI is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_rssi_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_rssi(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_rssi", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_rssi", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_get_rssi_level_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Gets the RSSI level.
 * @scenario        Check AP validity and get RSSI level from AP information. Check the return value.
 */
int utc_wifi_manager_ap_get_rssi_level_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;
	wifi_manager_rssi_level_e rssi_level;

	ret = wifi_manager_ap_get_rssi_level(g_hWifiAP, &rssi_level);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_rssi_level", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_rssi_level", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_get_rssi_level_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     Verify wifi_manager_ap_get_rssi_level by passing invalid parameters(ap, rssi level).
 * @scenario        Pass invalid AP information. Proper RSSI level is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_rssi_level_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_rssi_level(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_rssi_level", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_rssi_level", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/**
 * @testcase		utc_wifi_manager_ap_get_frequency_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the frequency band (MHz).
 * @scenario		Check AP validity and get frequesncy band from AP information.
 *					Check the return value.
 */
int utc_wifi_manager_ap_get_frequency_p(void)
{
	int frequency = 0;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_frequency(g_hWifiAP, &frequency);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_frequency", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_frequency", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_frequency_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_frequency by passing invalid parameters(ap,frequency).
 * @scenario		Pass invalid AP info make sure proper frequency band is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_frequency_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_frequency(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_frequency", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_frequency", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_max_speed_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Gets the max speed (Mbps)
 * @scenario		Check AP validity and get max speed from AP information. Ensure no error.
 */
int utc_wifi_manager_ap_get_max_speed_p(void)
{
	int speed = 0;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_max_speed(g_hWifiAP, &speed);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_max_speed", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_max_speed", ret, WIFI_MANAGER_ERROR_NONE);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_max_speed_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_max_speed by passing invalid parameters(ap,max_speed).
 * @scenario		Pass invalid AP info make sure proper speed is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_max_speed_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_max_speed(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_max_speed", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_max_speed", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_is_favorite_p
 * @since_tizen		3.0
 * @type			Positive
 * @description 	Checks whether the access point is favorite or not.
 * @scenario		Check AP validity and get favourite status of the AP. Ensure no error.
 */
int utc_wifi_manager_ap_is_favorite_p(void)
{
	bool favorite = false;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_is_favorite(g_hWifiAP, &favorite);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_is_favorite", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_is_favorite", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_is_favorite_n
 * @since_tizen		3.0
 * @type			Negative
 * @description 	Verify wifi_manager_ap_is_favorite by passing invalid parameters(ap,favorite).
 * @scenario		Pass invalid AP info make sure proper favourite status is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_is_favorite_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_is_favorite(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_is_favorite", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_is_favorite", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_is_passpoint_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Checks whether the access point is passpoint or not.
 * @scenario		Check AP validity and get whether passpoint feature is
 *					supported by the AP
 */
int utc_wifi_manager_ap_is_passpoint_p(void)
{
	bool passpoint = false;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_is_passpoint(g_hWifiAP, &passpoint);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_is_passpoint", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_is_passpoint", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_is_passpoint_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_is_passpoint by passing invalid parameters(ap,passpoint).
 * @scenario		Pass invalid AP info make sure passpoint support status is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_is_passpoint_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_is_passpoint(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_is_passpoint", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_is_passpoint", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_connection_state_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the connection state.
 * @scenario		Check AP validity and get connection status from AP information.
 *					Ensure no error.
 */
int utc_wifi_manager_ap_get_connection_state_p(void)
{
	wifi_manager_connection_state_e state;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_connection_state(g_hWifiAP, &state);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_connection_state", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_connection_state", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_connection_state_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_connection_state by passing invalid parameters(ap,state).
 * @scenario		Pass invalid AP info make sure connection state is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_connection_state_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_connection_state(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_connection_state", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_connection_state", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_ip_config_type_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the config type of IP
 * @scenario		Check AP validity and get IP config type whether it is Static,
 *					Dynamic, Fixed or auto
 */
int utc_wifi_manager_ap_get_ip_config_type_p(void)
{
	wifi_manager_ip_config_type_e type;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_ip_config_type(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &type);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_ip_config_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_ip_config_type", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_ip_config_type_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_ip_config_type by passing invalid parametrs(ap, address_family, type).
 * @scenario		Pass invalid AP info and other parameters to make sure ip config type is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_ip_config_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_ip_config_type(NULL, -1, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_ip_config_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_ip_config_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_ip_config_type_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Sets the config type of IP.
 * @scenario 		Set the IP configuration type for IPv4 and update AP information
 *					Ensure no error.
 */
int utc_wifi_manager_ap_set_ip_config_type_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_ip_config_type(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_MANAGER_IP_CONFIG_TYPE_STATIC);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_ip_config_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_ip_config_type", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_ip_config_type_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_ip_config_type by passing invalid parameters(ap, address_family, type).
 * @scenario		Pass invalid AP info and other parameters to make sure ip config type is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_ip_config_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_ip_config_type(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, -1);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_ip_config_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_ip_config_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_ip_address_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		brief Gets the IP address.
 * @scenario 		Get IP address of the AP and ensure no error. Free ip address.
 */
int utc_wifi_manager_ap_get_ip_address_p(void)
{
	char *ip_addr = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_ip_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &ip_addr);
		CHECK_RETURN("wifi_manager_ap_get_ip_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_ip_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.1");
	CHECK_RETURN("wifi_manager_ap_set_ip_address", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_get_ip_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY(ip_addr);
	CHECK_RETURN("wifi_manager_ap_get_ip_address", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_ip_address_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_ip_address by passing invalid parameters(ap, address_family, ip_address).
 * @scenario		Pass invalid AP info and other parameters to  make sure IP address is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_ip_address_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_ip_address(NULL, -1, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_ip_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_ip_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_ip_address_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Sets the IP address.
 * @scenario		Set IP address to AP and ensure no error.
 */
int utc_wifi_manager_ap_set_ip_address_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_ip_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.1");

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_ip_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_ip_address", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_ip_address_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_ip_address by passing invalid parameters(ap, address_family, ip_address).
 * @scenario		Pass invalid AP info and other parameters to  make sure IP address is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_ip_address_n(void)
{
    int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_ip_address(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_ip_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_ip_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_subnet_mask_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		brief Gets the subnet mask.
 * @scenario		Get subnet mask from AP information and ensure no error
 */
int utc_wifi_manager_ap_get_subnet_mask_p(void)
{
	char *ip_addr = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_subnet_mask(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY(ip_addr);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_subnet_mask", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_subnet_mask", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_subnet_mask_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_subnet_mask by passing invalid parameters(ap, address_family, subnet_mask).
 * @scenario		Pass invalid AP info and other parameters to  make sure Subnet mask is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_subnet_mask_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_subnet_mask(NULL, -1, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_subnet_mask", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_subnet_mask", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_subnet_mask_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		brief Sets the subnet mask.
 * @scenario		Set subnet mask in AP information. Ensure no error.
 */
int utc_wifi_manager_ap_set_subnet_mask_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_subnet_mask(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "255.255.255.0");

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_subnet_mask", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_subnet_mask", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_subnet_mask_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_subnet_mask by passing invalid parameters(ap, address_family,subnet_mask).
 * @scenario		Pass invalid AP info and other parameters to  make sure thesubnet mask is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_subnet_mask_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_subnet_mask(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_subnet_mask", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_subnet_mask", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_gateway_address_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		brief Gets the gateway address.
 * @scenario		Get gateway's IP address from AP information.Ensure no error.
 */
int utc_wifi_manager_ap_get_gateway_address_p(void)
{
	char *ip_addr = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_gateway_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY(ip_addr);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_gateway_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_gateway_address", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_gateway_address_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_gateway_address by passing invalid parameters(ap,address_family,gateway_addr).
 * @scenario		Pass invalid AP info and other parameters to  make sure Gateway's IP address is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_gateway_address_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_gateway_address(NULL, -1, NULL);

	if (!g_bFeatureWifi) {
        CHECK_RETURN("wifi_manager_ap_get_gateway_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_gateway_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_gateway_address_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		brief Sets the gateway address.
 * @scenario		Set Gateway's IP address in AP info. Ensure no error.
 */
int utc_wifi_manager_ap_set_gateway_address_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_gateway_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.1");

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_gateway_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_gateway_address", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_gateway_address_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_gateway_address by passing invalid parameters(ap,address_family,gateway_addr).
 * @scenario		Pass invalid AP info and other parameters to  ensure Gateway IP address is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_gateway_address_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_gateway_address(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_gateway_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_gateway_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_get_dhcp_server_address_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     brief Gets the DHCP server's IP address.
 * @scenario        Get gateway's IP address from AP information.Ensure no error.
 */
int utc_wifi_manager_ap_get_dhcp_server_address_p(void)
{
	char *ip_addr = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_dhcp_server_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY(ip_addr);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_dhcp_server_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_dhcp_server_address", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_get_dhcp_server_address_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     Verify wifi_manager_ap_get_dhcp_server_address by passing invalid parameters(ap,address_family,dhcp_server_address).
 * @scenario        Pass invalid AP info and other parameters to  make sure DHCP server's IP address is not returned.
 *				     Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_dhcp_server_address_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_dhcp_server_address(NULL, -1, NULL);

	if (!g_bFeatureWifi) {
        CHECK_RETURN("wifi_manager_ap_get_dhcp_server_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_dhcp_server_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_get_dhcp_lease_duration_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     brief Gets the DHCP lease duration in seconds.
 * @scenario        Get DHCP lease duration from AP information.Ensure no error.
 */
int utc_wifi_manager_ap_get_dhcp_lease_duration_p(void)
{
	int dhcp_lease_duration = 0;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_dhcp_lease_duration(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dhcp_lease_duration);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_dhcp_lease_duration", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_dhcp_lease_duration", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_get_dhcp_lease_duration_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     Verify wifi_manager_ap_get_dhcp_lease_duration by passing invalid parameters(ap,address_family,dhcp_server_address).
 * @scenario        Pass invalid AP info and other parameters to  make sure DHCP server's IP address is not returned.
 *				     Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_dhcp_lease_duration_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_dhcp_lease_duration(NULL, -1, NULL);

	if (!g_bFeatureWifi) {
        CHECK_RETURN("wifi_manager_ap_get_dhcp_lease_duration", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_dhcp_lease_duration", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_proxy_address_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		brief Gets the proxy address.
 * @scenario		Get proxy address from AP info. Ensure no error.
 */
int utc_wifi_manager_ap_get_proxy_address_p(void)
{
	char *proxy = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_proxy_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &proxy);
	FREE_MEMORY(proxy);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_proxy_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_proxy_address", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_proxy_address_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_proxy_address by passing invalid parameters(ap,add_family,proxy_address).
 * @scenario		Pass invalid AP info and other parameters to  ensure proxy address in not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_proxy_address_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_proxy_address(NULL, -1, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_proxy_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_proxy_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_proxy_address_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		brief Sets the proxy address.
 * @scenario		Set proxy address in AP info. Ensure no error.
 */
int utc_wifi_manager_ap_set_proxy_address_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_proxy_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.1:8080");

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_proxy_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_proxy_address", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_proxy_address_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_proxy_address by passing invalid parameters(ap,add_family,proxy_address).
 * @scenario		Pass invalid AP info and other parameters to  ensure Proxy address in not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_proxy_address_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_proxy_address(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_proxy_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_proxy_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_proxy_type_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the Proxy type.
 * @scenario		Get proxy type from AP info. Ensure no error.
 */
int utc_wifi_manager_ap_get_proxy_type_p(void)
{
	wifi_manager_proxy_type_e type;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_proxy_type(g_hWifiAP, &type);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_proxy_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_proxy_type", ret, WIFI_MANAGER_ERROR_NONE);
	}

    return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_proxy_type_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_proxy_type by passing invalid parameters(ap,proxy_type).
 * @scenario		Pass invalid AP info and other parameters to  ensure proxy type is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_proxy_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_proxy_type(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_proxy_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_proxy_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_proxy_type_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Sets the Proxy address.
 * @scenario 		Set the proxy type to manual. Ensure no error.
 */
int utc_wifi_manager_ap_set_proxy_type_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_proxy_type(g_hWifiAP, WIFI_MANAGER_PROXY_TYPE_MANUAL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_proxy_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_proxy_type", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_proxy_type_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_proxy_type by passing invalid parameters(ap, proxy_type).
 * @scenario		Pass invalid AP info and other parameters to  ensure proxy type is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_proxy_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_proxy_type(NULL, -1);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_proxy_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_proxy_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_dns_address_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the DNS address.
 * @scenario
 */
int utc_wifi_manager_ap_get_dns_address_p(void)
{
	char *dns1 = NULL;
    char *dns2 = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_dns_address(g_hWifiAP, 1, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns1);
		CHECK_RETURN("wifi_manager_ap_get_dns_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_get_dns_address(g_hWifiAP, 1, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns1);
	FREE_MEMORY(dns1);
	CHECK_RETURN("wifi_manager_ap_get_dns_address", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_get_dns_address(g_hWifiAP, 2, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns2);
	FREE_MEMORY(dns2);
	CHECK_RETURN("wifi_manager_ap_get_dns_address", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_dns_address_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_dns_address by passing invalid parameters(ap,addr_fam,DNS address).
 * @scenario		Pass invalid AP info and other parameters to  make sure DNS address is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_dns_address_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_dns_address(NULL, 1, -1, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_dns_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_dns_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_dns_address_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the DNS address.
 * @scenario		Get the dns address from AP info. Ensure no error.
 */
int utc_wifi_manager_ap_set_dns_address_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_dns_address(g_hWifiAP, 1, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.1");
		CHECK_RETURN("wifi_manager_ap_set_dns_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_dns_address(g_hWifiAP, 1, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.1");
	CHECK_RETURN("wifi_manager_ap_set_dns_address", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_dns_address(g_hWifiAP, 2, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, "192.168.11.2");
	CHECK_RETURN("wifi_manager_ap_set_dns_address", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_dns_address_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_dns_address by passing invalid parameters(ap, order, addr_fam, DNS address).
 * @scenario		Pass invalid AP info and other parameters to  make sure DNS address is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_dns_address_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_dns_address(NULL, 1, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_dns_address", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_dns_address", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_wifi_manager_ap_get_countrycode_p
 * @since_tizen         5.0
 * @type                        Positive
 * @description         Gets the country code.
 * @scenario
 */
int utc_wifi_manager_ap_get_countrycode_p(void)
{
	char *country_code = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_countrycode(g_hWifiAP, &country_code);
		CHECK_RETURN("wifi_manager_ap_get_countrycode", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_get_countrycode(g_hWifiAP, &country_code);
	FREE_MEMORY(country_code);
	CHECK_RETURN("wifi_manager_ap_get_countrycode", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_wifi_manager_ap_get_countrycode_n
 * @since_tizen         5.0
 * @type                        Negative
 * @description         Verify wifi_manager_ap_get_countrycode by passing invalid parameters(ap, country_code).
 * @scenario            Pass invalid AP info and other parameters to  make sure country code is not returned.
 *                                      Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_countrycode_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_countrycode(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_countrycode", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_countrycode", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_foreach_found_bssid_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the BSSID list
 * @scenario        Invoking wifi_manager_foreach_found_bssid with valid parameter.
 */
int utc_wifi_manager_foreach_found_bssid_p(void)
{
	if (!g_bFeatureWifi) {
		int ret = wifi_manager_foreach_found_bssid(g_hWifiAP,
				wifi_manager_ap_foreach_bssid_list_callback, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_foreach_found_bssid(g_hWifiAP,
				wifi_manager_ap_foreach_bssid_list_callback, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_foreach_found_bssid_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     wifi_manager_foreach_found_bssid should be failed with invalid parameter.
 * @scenario        Verify bssid list by passing invalid parameter.
 **/
int utc_wifi_manager_foreach_found_bssid_n(void)
{
	if (!g_bFeatureWifi) {
		int ret = wifi_manager_foreach_found_bssid(NULL,
				wifi_manager_ap_foreach_bssid_list_callback, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_foreach_found_bssid(NULL,
				wifi_manager_ap_foreach_bssid_list_callback, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_foreach_found_bssid(g_hWifiAP, NULL, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_foreach_found_bssid(NULL, NULL, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/* Security operations. */

/**
 * @testcase		utc_wifi_manager_ap_get_security_type_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the Wi-Fi security mode.
 * @scenario		Get security mechanism used for the connection. Ensure no error.
 */
int utc_wifi_manager_ap_get_security_type_p(void)
{
	wifi_manager_security_type_e type;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_security_type(g_hWifiAP, &type);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_security_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_security_type", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_security_type_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_security_type by passing invalid parameters(ap, security_type).
 * @scenario		Pass invalid AP info and other parameters to  ensure security type is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_security_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_security_type(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_security_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_security_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_security_type_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Sets the Wi-Fi security mode.
 * @scenario		Sete the security type in AP info. Ensure no error.
 */
int utc_wifi_manager_ap_set_security_type_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_WPA2_PSK);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_security_type_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_security_type by passing invalid parameters(ap, security_type).
 * @scenario		Pass invalid AP info and other parameters to  ensure security type is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_security_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_security_type(NULL, -1);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_encryption_type_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the Wi-Fi encryption type.
 * @scenario		Get the security encryption type from AP info. Ensure no error.
 */
int utc_wifi_manager_ap_get_encryption_type_p(void)
{
	wifi_manager_encryption_type_e type;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_encryption_type(g_hWifiAP, &type);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_encryption_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_encryption_type", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_encryption_type_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_encryption_type by passing invalid parameters(ap, encryption_type).
 * @scenario		Pass invalid AP info and other parameters to  ensure WiFi encryption type is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_encryption_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_encryption_type(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_encryption_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_encryption_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_encryption_type_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Sets the Wi-Fi encryption type.
 * @scenario		Set the Wi-Fi encryption type in AP info. Ensure no error.
 */
int utc_wifi_manager_ap_set_encryption_type_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_encryption_type(g_hWifiAP, WIFI_MANAGER_ENCRYPTION_TYPE_AES);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_encryption_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_encryption_type", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_encryption_type_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_encryption_type by passing invalid parameters(ap, encryption_type).
 * @scenario		Pass invalid AP info and other parameters to  ensure WiFi encryption type is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_encryption_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_encryption_type(NULL, -1);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_encryption_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_encryption_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_is_passphrase_required_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Checks whether the passphrase is required or not.
 * @scenario		Check whether passphrase is required for encryption. Ensure no error.
 */
int utc_wifi_manager_ap_is_passphrase_required_p(void)
{
	bool required;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_is_passphrase_required(g_hWifiAP, &required);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_is_passphrase_required", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_is_passphrase_required", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_is_passphrase_required_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_is_passphrase_required by passing invalid parameters(ap,required).
 * @scenario		Pass invalid AP info and other parameters to  ensure pass phrase info is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_is_passphrase_required_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_is_passphrase_required(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_is_passphrase_required", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_is_passphrase_required", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_passphrase_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Sets the passphrase.
 * @scenario		Set the pass phrase used for encryption. Ensure no error.
 */
int utc_wifi_manager_ap_set_passphrase_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_passphrase(g_hWifiAP, WIFI_AP_PASSPHRASE);
		CHECK_RETURN("wifi_manager_ap_set_passphrase", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_WPA2_PSK);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_passphrase(g_hWifiAP, WIFI_AP_PASSPHRASE);
	CHECK_RETURN("wifi_manager_ap_set_passphrase", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_passphrase_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_passphrase by passing invalid parameters(ap, passphrase).
 * @scenario		Pass invalid AP info and other parameters to  ensure pass phrase is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_passphrase_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_passphrase(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_passphrase", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_passphrase", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_is_wps_supported_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Checks whether the WPS(Wi-Fi Protected Setup) is supported or not.
 * @scenario		Check whether WPS is supported.
 */
int utc_wifi_manager_ap_is_wps_supported_p(void)
{
	bool supported;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_is_wps_supported(g_hWifiAP, &supported);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_is_wps_supported", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_is_wps_supported", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_is_wps_supported_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_is_wps_supported by passing invalid parameters(ap, supported).
 * @scenario		Pass invalid AP info and other parameters to  ensure WPS support is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_is_wps_supported_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_is_wps_supported(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_is_wps_supported", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_is_wps_supported", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/* EAP operations. */

/**
 * @testcase		utc_wifi_manager_ap_set_eap_passphrase_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Sets the passphrase of EAP.
 * @scenario		Set EAP passphrase in AP info. Ensure no error.
 */
int utc_wifi_manager_ap_set_eap_passphrase_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_eap_passphrase(g_hWifiAP, WIFI_EAP_USERNAME, WIFI_EAP_PASSPHRASE);
		CHECK_RETURN("wifi_manager_ap_set_eap_passphrase", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_passphrase(g_hWifiAP, WIFI_EAP_USERNAME, WIFI_EAP_PASSPHRASE);
	CHECK_RETURN("wifi_manager_ap_set_eap_passphrase", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_passphrase_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_eap_passphrase by passing invalid parameters(ap, user_name,password).
 * @scenario		Pass invalid AP info and other parameters to  ensure EAP passphrase is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_eap_passphrase_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_eap_passphrase(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_eap_passphrase", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_eap_passphrase", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_passphrase_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Get EAP passphrase.
 * @scenario		Get EPA passphrase from AP info. Ensure no error.
 */
int utc_wifi_manager_ap_get_eap_passphrase_p(void)
{
	char *user_name = NULL;
	bool is_password_set;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
		CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_passphrase(g_hWifiAP, WIFI_EAP_USERNAME, WIFI_EAP_PASSPHRASE);
	CHECK_RETURN("wifi_manager_ap_set_eap_passphrase", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_get_eap_passphrase(g_hWifiAP, &user_name, &is_password_set);
	FREE_MEMORY(user_name);
	CHECK_RETURN("wifi_manager_ap_get_eap_passphrase", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_passphrase_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_eap_passphrase by passing invalid parameters.
 * @scenario		Pass invalid AP info and other parameters to  ensure EAP passphrase is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_eap_passphrase_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_eap_passphrase(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_eap_passphrase", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_eap_passphrase", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_ca_cert_file_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the CA Certificate of EAP.
 * @scenario		Get EAP certificate file name. Ensure no error.
 */
int utc_wifi_manager_ap_get_eap_ca_cert_file_p(void)
{
	char *cert_file = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_eap_ca_cert_file(g_hWifiAP, &cert_file);
		CHECK_RETURN("wifi_manager_ap_get_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_ca_cert_file(g_hWifiAP, WIFI_EAP_CA_CERT);
	CHECK_RETURN("wifi_manager_ap_set_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_get_eap_ca_cert_file(g_hWifiAP, &cert_file);
	FREE_MEMORY(cert_file);
	CHECK_RETURN("wifi_manager_ap_get_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_ca_cert_file_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify wifi_manager_ap_get_eap_ca_cert_file by passing invalid parameters.
 * @scenario		Pass invalid AP info and other parameters to ensure EAP certificate file name is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_eap_ca_cert_file_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_eap_ca_cert_file(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_ca_cert_file_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Sets the CA Certificate of EAP.
 * @scenario		Set EAP certificate file name in AP info. Ensure no error.
 */
int utc_wifi_manager_ap_set_eap_ca_cert_file_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_eap_ca_cert_file(g_hWifiAP, WIFI_EAP_CA_CERT);
		CHECK_RETURN("wifi_manager_ap_set_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_ca_cert_file(g_hWifiAP, WIFI_EAP_CA_CERT);
	CHECK_RETURN("wifi_manager_ap_set_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_ca_cert_file_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_eap_ca_cert_file by passing invalid parameters.
 * @scenario		Pass invalid AP info and invalid file name to ensure EAP certificate file name is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_eap_ca_cert_file_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_eap_ca_cert_file(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_eap_ca_cert_file", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_client_cert_file_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the Client Certificate of EAP.
 * @scenario		Get EAP certificate filename from AP info. Ensure no error.
 */
int utc_wifi_manager_ap_get_eap_client_cert_file_p(void)
{
	char *cert_file = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_eap_client_cert_file(g_hWifiAP, &cert_file);
		CHECK_RETURN("wifi_manager_ap_get_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_get_eap_client_cert_file(g_hWifiAP, &cert_file);
	FREE_MEMORY(cert_file);
	CHECK_RETURN("wifi_manager_ap_get_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_client_cert_file_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_eap_client_cert_file	by passing invalid parameter(ap, file).
 * @scenario		Pass invalid AP info and other parameters to ensure EAP certificate file name is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_eap_client_cert_file_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_eap_client_cert_file(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_client_cert_file_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Sets the CA Certificate of EAP.
 * @scenario		Set EAP ceritificate file name. Ensure no error.
 */
int utc_wifi_manager_ap_set_eap_client_cert_file_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_eap_client_cert_file(g_hWifiAP, WIFI_EAP_CA_CERT);
		CHECK_RETURN("wifi_manager_ap_set_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_client_cert_file(g_hWifiAP, WIFI_EAP_CA_CERT);
	CHECK_RETURN("wifi_manager_ap_set_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_client_cert_file_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_eap_client_cert_file	by passing invalid parameter(ap, file).
 * @scenario		Pass invalid AP info and other parameters to ensure EAP certificate file name is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_eap_client_cert_file_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_eap_client_cert_file(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_eap_client_cert_file", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_private_key_file_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the private key file of EAP.
 * @scenario		Get EAP private key file name. Ensure no error.
 */
int utc_wifi_manager_ap_get_eap_private_key_file_p(void)
{
	char *key_file = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_eap_private_key_file(g_hWifiAP, &key_file);
		CHECK_RETURN("wifi_manager_ap_get_eap_private_key_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_get_eap_private_key_file(g_hWifiAP, &key_file);
	FREE_MEMORY(key_file);
	CHECK_RETURN("wifi_manager_ap_get_eap_private_key_file", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_private_key_file_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_eap_private_key_file by passing invalid parameters(ap, file).
 * @scenario		Pass invalid AP info and other parameters to ensure EAP private key file name is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_eap_private_key_file_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_eap_private_key_file(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_eap_private_key_file", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_eap_private_key_file", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_private_key_info_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Sets the private key information of EAP.
 * @scenario		Set EAP private key info in a file. Ensure no error.
 */
int utc_wifi_manager_ap_set_eap_private_key_info_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_eap_private_key_info(g_hWifiAP, WIFI_EAP_CA_CERT, WIFI_EAP_PASSPHRASE);
		CHECK_RETURN("wifi_manager_ap_set_eap_private_key_info", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_private_key_info(g_hWifiAP, WIFI_EAP_CA_CERT, WIFI_EAP_PASSPHRASE);
	CHECK_RETURN("wifi_manager_ap_set_eap_private_key_info", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_private_key_info_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_eap_private_key_info by passing invalid parameters.
 * @scenario		Pass invalid AP info and other parameters to ensure EAP private key is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_eap_private_key_info_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_eap_private_key_info(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_eap_private_key_info", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_eap_private_key_info", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_type_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Gets the EAP type of Wi-Fi.
 * @scenario		Get EAP type from AP info. Ensure no error.
 */
int utc_wifi_manager_ap_get_eap_type_p(void)
{
	wifi_manager_eap_type_e type;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_eap_type(g_hWifiAP, &type);
		CHECK_RETURN("wifi_manager_ap_get_eap_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_type(g_hWifiAP, WIFI_MANAGER_EAP_TYPE_PEAP);
	CHECK_RETURN("wifi_manager_ap_set_eap_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_get_eap_type(g_hWifiAP, &type);
    CHECK_RETURN("wifi_manager_ap_get_eap_type", ret, WIFI_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_type_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_eap_type by passing invalid parameters(ap, EAP_type).
 * @scenario		Pass invalid AP info and other parameters to ensure EAP type is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_eap_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_eap_type(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_eap_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_eap_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_type_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Sets the EAP type of Wi-Fi.
 * @scenario		Set EAP type in AP info. Ensure no error.
 */
int utc_wifi_manager_ap_set_eap_type_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_eap_type(g_hWifiAP, WIFI_MANAGER_EAP_TYPE_PEAP);
		CHECK_RETURN("wifi_manager_ap_set_eap_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_type(g_hWifiAP, WIFI_MANAGER_EAP_TYPE_PEAP);
	CHECK_RETURN("wifi_manager_ap_set_eap_type", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_type_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_set_eap_type by passing invalid parameters(ap, EAP_type).
 * @scenario		Pass invalid AP info and other parameters to ensure EAP type is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_eap_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_eap_type(NULL, -1);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_eap_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_eap_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_auth_type_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Get the EAP authentication type of Wi-Fi.
 * @scenario		Get EAP authentication type. Ensure no error.
 */
int utc_wifi_manager_ap_get_eap_auth_type_p(void)
{
	wifi_manager_eap_auth_type_e type;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_eap_type(g_hWifiAP, WIFI_MANAGER_EAP_TYPE_PEAP);
		CHECK_RETURN("wifi_manager_ap_set_eap_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_auth_type(g_hWifiAP, WIFI_MANAGER_EAP_AUTH_TYPE_MD5);
	CHECK_RETURN("wifi_manager_ap_set_eap_auth_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_get_eap_auth_type(g_hWifiAP, &type);
	CHECK_RETURN("wifi_manager_ap_get_eap_auth_type", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_auth_type_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_eap_auth_type by passing invalid parameters.
 * @scenario		Pass invalid AP info and other parameters to ensure EAP authentication type is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_eap_auth_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_eap_auth_type(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_eap_auth_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_eap_auth_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_auth_type_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Sets the EAP auth type of Wi-Fi.
 * @scenario		Set EAP authentication type in AP info. Ensure no error.
 */
int utc_wifi_manager_ap_set_eap_auth_type_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_eap_type(g_hWifiAP, WIFI_MANAGER_EAP_TYPE_PEAP);
		CHECK_RETURN("wifi_manager_ap_set_eap_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_auth_type(g_hWifiAP, WIFI_MANAGER_EAP_AUTH_TYPE_MD5);
	CHECK_RETURN("wifi_manager_ap_set_eap_auth_type", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_auth_type_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify wifi_manager_ap_set_eap_auth_type by passing invalid parameters.
 * @scenario		Pass invalid AP info and other parameters to ensure EAP authentication type is not set.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_eap_auth_type_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_set_eap_auth_type(NULL, -1);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_eap_auth_type", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_eap_auth_type", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_disconnect_reason_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description		Get the disconnect reason of Wi-Fi.
 * @scenario		Get disconnect reason. Ensure no error.
 */
int utc_wifi_manager_ap_get_disconnect_reason_p(void)
{
	wifi_manager_disconnect_reason_e disconnect_reason;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_disconnect_reason(g_hWifiAP, &disconnect_reason);
		CHECK_RETURN("wifi_manager_ap_get_disconnect_reason", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_get_disconnect_reason(g_hWifiAP, &disconnect_reason);
	CHECK_RETURN("wifi_manager_ap_get_disconnect_reason", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_disconnect_reason_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_get_disconnect_reason by passing invalid parameters.
 * @scenario		Pass invalid AP info and other parameters to ensure disconnect reason is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_disconnect_reason_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_disconnect_reason(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_disconnect_reason", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_disconnect_reason", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_refresh_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Refreshes the access point information.
 * @scenario		Scan for APs and update the AP list.
 */
int utc_wifi_manager_ap_refresh_p(void)
{
	wifi_manager_ap_h hAP = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_refresh(g_hWifiAP);
		CHECK_RETURN("wifi_manager_ap_refresh", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_pre_connect();
	CHECK_RETURN("wifi_manager_pre_connect", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_get_connected_ap(g_hWifi, &hAP);
	CHECK_RETURN("wifi_manager_get_connected_ap", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_refresh(hAP);
	CHECK_RETURN("wifi_manager_ap_refresh", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_refresh_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_refresh by passing invalid parameters(ap).
 * @scenario		Pass invalid AP handle and ensure ap ifo in no updated.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_refresh_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_refresh(NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_refresh", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_refresh", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_error_state_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description	Get the error state.
 * @scenario		Get error state. Ensure no error.
 */
int utc_wifi_manager_ap_get_error_state_p(void)
{
	wifi_manager_error_e error_state;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_error_state(g_hWifiAP, &error_state);
		CHECK_RETURN("wifi_manager_ap_get_error_state", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_get_error_state(g_hWifiAP, &error_state);
	CHECK_RETURN("wifi_manager_ap_get_error_state", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_error_state_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description	Verify wifi_manager_ap_get_error_state by passing invalid parameters.
 * @scenario		Pass invalid AP info and other parameters to ensure error state is not returned.
 *				Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_error_state_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_error_state(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_error_state", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_error_state", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/**
 * @testcase        utc_wifi_manager_ap_get_prefix_length_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Gets prefix length
 * @scenario        Invoking wifi_manager_ap_get_ipv6_state with valid parameter.
 **/
int utc_wifi_manager_ap_get_prefix_length_p(void)
{
	int length;

	if (!g_bFeatureWifi) {
		int ret = wifi_manager_ap_get_prefix_length(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &length);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_ap_get_prefix_length(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &length);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
		ret = wifi_manager_ap_get_prefix_length(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, &length);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_get_prefix_length_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     wifi_manager_ap_get_prefix_length should be failed with invalid parameter.
 * @scenario        Verify prefix_length by passing invalid parameter.
 **/
int utc_wifi_manager_ap_get_prefix_length_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_get_prefix_length(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_get_prefix_length", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_get_prefix_length", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_set_prefix_length_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Sets prefix length
 * @scenario        Invoking wifi_manager_ap_set_ipv6_state with valid parameter.
 */
int utc_wifi_manager_ap_set_prefix_length_p(void)
{
	int length = 32;

	if (!g_bFeatureWifi) {
		int ret = wifi_manager_ap_set_prefix_length(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, length);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		ret = wifi_manager_ap_set_prefix_length(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, length);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_ap_set_prefix_length(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, length);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
		ret = wifi_manager_ap_set_prefix_length(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, length);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_set_prefix_length_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     wifi_manager_ap_set_prefix_length should be failed with invalid parameter.
 * @scenario        Verify prefix_length by passing invalid parameter.
 **/
int utc_wifi_manager_ap_set_prefix_length_n(void)
{
	int ret = wifi_manager_ap_set_prefix_length(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, -1);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_set_prefix_length", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_set_prefix_length", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_get_dns_config_type_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Gets DNS configuration type
 * @scenario        Invoking wifi_manager_ap_get_dns_config_type with valid parameter.
 */
int utc_wifi_manager_ap_get_dns_config_type_p(void)
{
	wifi_manager_dns_config_type_e dns_type;

	if (!g_bFeatureWifi) {
		int ret = wifi_manager_ap_get_dns_config_type(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns_type);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_ap_get_dns_config_type(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns_type);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
		ret = wifi_manager_ap_get_dns_config_type(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, &dns_type);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_get_dns_config_type_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     wifi_manager_ap_get_dns_config_type should be failed with invalid parameter.
 * @scenario        Verify dns config type by passing invalid parameter.
 **/
int utc_wifi_manager_ap_get_dns_config_type_n(void)
{
	wifi_manager_dns_config_type_e dns_type;

	if (!g_bFeatureWifi) {
		int ret = wifi_manager_ap_get_dns_config_type(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns_type);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_ap_get_dns_config_type(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dns_type);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_ap_get_dns_config_type(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_ap_get_dns_config_type(NULL, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_set_dns_config_type_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Sets DNS configuration type
 * @scenario        Invoking wifi_manager_ap_set_dns_config_type with valid parameter.
 */
int utc_wifi_manager_ap_set_dns_config_type_p(void)
{
	if (!g_bFeatureWifi) {
		int ret = wifi_manager_ap_set_dns_config_type(g_hWifiAP,
				WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_MANAGER_DNS_CONFIG_TYPE_DYNAMIC);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_ap_set_dns_config_type(g_hWifiAP,
				WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_MANAGER_DNS_CONFIG_TYPE_STATIC);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
		ret = wifi_manager_ap_set_dns_config_type(g_hWifiAP,
				WIFI_MANAGER_ADDRESS_FAMILY_IPV6, WIFI_MANAGER_DNS_CONFIG_TYPE_DYNAMIC);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_set_dns_config_type_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     wifi_manager_ap_set_dns_config_type should be failed with invalid parameter.
 * @scenario        Verify dns config type by passing invalid parameter.
 **/
int utc_wifi_manager_ap_set_dns_config_type_n(void)
{
	if (!g_bFeatureWifi) {
		int ret = wifi_manager_ap_set_dns_config_type(NULL,
				WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_MANAGER_DNS_CONFIG_TYPE_STATIC);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_ap_set_dns_config_type(NULL,
				WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_MANAGER_DNS_CONFIG_TYPE_STATIC);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_ap_set_dns_config_type(NULL,
				WIFI_MANAGER_ADDRESS_FAMILY_IPV6, WIFI_MANAGER_DNS_CONFIG_TYPE_DYNAMIC);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_foreach_ipv6_address_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Gets IPv6 address
 * @scenario        Invoking wifi_manager_ap_foreach_ipv6_address with valid parameter.
 */
int utc_wifi_manager_ap_foreach_ipv6_address_p(void)
{
	if (!g_bFeatureWifi) {
		int ret = wifi_manager_ap_foreach_ipv6_address(g_hWifiAP,
				wifi_manager_ap_ipv6_address_callback, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_ap_foreach_ipv6_address(g_hWifiAP,
				wifi_manager_ap_ipv6_address_callback, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_foreach_ipv6_address_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     wifi_manager_ap_foreach_ipv6_address should be failed with invalid parameter.
 * @scenario        Verify IPv6 address by passing invalid parameter.
 **/
int utc_wifi_manager_ap_foreach_ipv6_address_n(void)
{
	if (!g_bFeatureWifi) {
		int ret = wifi_manager_ap_foreach_ipv6_address(NULL,
				wifi_manager_ap_ipv6_address_callback, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_ap_foreach_ipv6_address(NULL,
				wifi_manager_ap_ipv6_address_callback, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_ap_foreach_ipv6_address(g_hWifiAP, NULL, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_ap_foreach_ipv6_address(NULL, NULL, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_get_assoc_status_code_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Get the association status code from supplicant
 * @scenario        Invoke wifi_manager_ap_get_assoc_status_code() with valid parameter
 **/
int utc_wifi_manager_ap_get_assoc_status_code_p(void)
{
	int ret;
	wifi_manager_assoc_status_code_e status_code;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_assoc_status_code(g_hWifiAP, &status_code);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		ret = wifi_manager_ap_get_assoc_status_code(g_hWifiAP, &status_code);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_get_assoc_status_code_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     wifi_mamager_ap_get_assoc_status_code() should be failed.
 * @scenario        Invoke wifi_manager_ap_get_assoc_status_code() with invalid parameter
 **/
int utc_wifi_manager_ap_get_assoc_status_code_n(void)
{
	int ret;
	wifi_manager_assoc_status_code_e status_code;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_assoc_status_code(NULL, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		ret = wifi_manager_ap_get_assoc_status_code(NULL, &status_code);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_ap_get_assoc_status_code(g_hWifiAP, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_ap_get_assoc_status_code(NULL, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_foreach_vsie_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets vsie from AP
 * @scenario        Invoking wifi_manager_ap_foreach_vsie_callback with valid parameter.
 */
int utc_wifi_manager_ap_foreach_vsie_p(void)
{
	if (!g_bFeatureWifi) {
		int ret = wifi_manager_ap_foreach_vsie(g_hWifiAP,
				wifi_manager_ap_foreach_vsie_callback, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_ap_foreach_vsie(g_hWifiAP,
				wifi_manager_ap_foreach_vsie_callback, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_ap_foreach_vsie_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     wifi_manager_ap_foreach_ipv6_address should be failed with invalid parameter.
 * @scenario        Verify IPv6 address by passing invalid parameter.
 **/
int utc_wifi_manager_ap_foreach_vsie_n(void)
{
	if (!g_bFeatureWifi) {
		int ret = wifi_manager_ap_foreach_vsie(NULL,
				wifi_manager_ap_foreach_vsie_callback, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		int ret = wifi_manager_ap_foreach_vsie(NULL,
				wifi_manager_ap_foreach_vsie_callback, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_ap_foreach_vsie(g_hWifiAP, NULL, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
		ret = wifi_manager_ap_foreach_vsie(NULL, NULL, NULL);
		assert_eq(ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_destroy_p
 * @since_tizen 	3.0
 * @type			Positive
 * @description		Destroys the access point handle.
 * @scenario		Destroy AP handle. Ensure no error.
 */
int utc_wifi_manager_ap_destroy_p(void)
{
	wifi_manager_ap_h hAP = NULL;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_destroy(hAP);
		CHECK_RETURN("wifi_manager_ap_destroy", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_create(g_hWifi, WIFI_AP_NAME, &hAP);
	CHECK_RETURN("wifi_manager_ap_create", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_destroy(hAP);
	CHECK_RETURN("wifi_manager_ap_destroy", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_destroy_n
 * @since_tizen 	3.0
 * @type			Negative
 * @description		Verify wifi_manager_ap_destroy by passing invalid parameters(ap).
 * @scenario		Pass invalid AP handle ensure AP is not destroyed.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_destroy_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_destroy(NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_destroy", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_destroy", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_anonymous_identity_p
 * @since_tizen 	5.5
 * @type			Positive
 * @description		Gets the EAP Anonymous Identity.
 * @scenario		Get EAP Anonymous Identity. Ensure no error.
 */
int utc_wifi_manager_ap_get_eap_anonymous_identity_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;
	char *anonymous_identity = NULL;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_eap_anonymous_identity(g_hWifiAP, &anonymous_identity);
		CHECK_RETURN("wifi_manager_ap_get_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_anonymous_identity(g_hWifiAP, "anonymous");
	CHECK_RETURN("wifi_manager_ap_set_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_get_eap_anonymous_identity(g_hWifiAP, &anonymous_identity);
	FREE_MEMORY(anonymous_identity);
	CHECK_RETURN("wifi_manager_ap_get_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_anonymous_identity_n1
 * @since_tizen 	5.5
 * @type			Negative
 * @description 	Verify wifi_manager_ap_get_eap_anonymous_identity by passing invalid parameters.
 * @scenario		Pass invalid AP info and other parameters to ensure anonymous identity is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_eap_anonymous_identity_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;
	char *anonymous_identity = NULL;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_eap_anonymous_identity(NULL, &anonymous_identity);
		CHECK_RETURN("wifi_manager_ap_get_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		ret = wifi_manager_ap_get_eap_anonymous_identity(NULL, &anonymous_identity);
		CHECK_RETURN("wifi_manager_ap_get_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_get_eap_anonymous_identity_n2
 * @since_tizen 	5.5
 * @type			Negative
 * @description 	Verify wifi_manager_ap_get_eap_anonymous_identity by passing invalid parameters.
 * @scenario		Pass invalid AP info and other parameters to ensure anonymous identity is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_get_eap_anonymous_identity_n2(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_get_eap_anonymous_identity(g_hWifiAP, NULL);
		CHECK_RETURN("wifi_manager_ap_get_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		ret = wifi_manager_ap_get_eap_anonymous_identity(g_hWifiAP, NULL);
		CHECK_RETURN("wifi_manager_ap_get_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_anonymous_identity_p
 * @since_tizen 	5.5
 * @type			Positive
 * @description		Sets the EAP Anonymous Identity.
 * @scenario		Set EAP Anonymous Identity. Ensure no error.
 */
int utc_wifi_manager_ap_set_eap_anonymous_identity_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;
	char *anonymous_identity = "anonymous";

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_eap_anonymous_identity(g_hWifiAP, anonymous_identity);
		CHECK_RETURN("wifi_manager_ap_set_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_anonymous_identity(g_hWifiAP, anonymous_identity);
	CHECK_RETURN("wifi_manager_ap_set_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_anonymous_identity_n1
 * @since_tizen 	5.5
 * @type			Negative
 * @description 	Verify wifi_manager_ap_set_eap_anonymous_identity by passing invalid parameters.
 * @scenario		Pass invalid AP info and other parameters to ensure anonymous identity is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_eap_anonymous_identity_n1(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;
	char *anonymous_identity = "anonymous";

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_eap_anonymous_identity(NULL, anonymous_identity);
		CHECK_RETURN("wifi_manager_ap_set_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		ret = wifi_manager_ap_set_eap_anonymous_identity(NULL, anonymous_identity);
		CHECK_RETURN("wifi_manager_ap_set_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_set_eap_anonymous_identity_n2
 * @since_tizen 	5.5
 * @type			Negative
 * @description 	Verify wifi_manager_ap_set_eap_anonymous_identity by passing invalid parameters.
 * @scenario		Pass invalid AP info and other parameters to ensure anonymous identity is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_set_eap_anonymous_identity_n2(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_eap_anonymous_identity(g_hWifiAP, NULL);
		CHECK_RETURN("wifi_manager_ap_set_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		ret = wifi_manager_ap_set_eap_anonymous_identity(g_hWifiAP, NULL);
		CHECK_RETURN("wifi_manager_ap_set_eap_anonymous_identity", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_is_hidden_p
 * @since_tizen 	5.5
 * @type			Positive
 * @description		Checks whether the AP is hidden or not.
 * @scenario		Check whether AP is hidden.
 */
int utc_wifi_manager_ap_is_hidden_p(void)
{
	bool is_hidden;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_is_hidden(g_hWifiAP, &is_hidden);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_is_hidden", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_is_hidden", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_is_hidden_n1
 * @since_tizen 	5.5
 * @type			Negative
 * @description		Verify wifi_manager_ap_is_hidden by passing invalid parameters(ap, is_hidden).
 * @scenario		Pass invalid AP info to ensure is_hidden is not returned.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_is_hidden_n1(void)
{
	bool is_hidden;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_is_hidden(NULL, &is_hidden);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_is_hidden", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_is_hidden", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_ap_is_hidden_n2
 * @since_tizen 	5.5
 * @type			Negative
 * @description		Verify wifi_manager_ap_is_hidden by passing invalid parameters(ap, is_hidden).
 * @scenario		Pass invalid is_handle pointer to ensure API returns proper error code.
 *					Return value should be WIFI_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_wifi_manager_ap_is_hidden_n2(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_ap_is_hidden(g_hWifiAP, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("wifi_manager_ap_is_hidden", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_ap_is_hidden", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
