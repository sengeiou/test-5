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

//& set: WifiManagerTDLS
/**
 * @function		utc_wifi_manager_tdls_startup
 * @since_tizen		3.0
 * @description		Initializes Wi-Fi.Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_manager_tdls_startup(void)
{
	g_bFeatureWifi = wifi_manager_check_feature_supported(FEATURE_WIFI);
	g_bFeatureWifiTDLS= wifi_manager_check_feature_supported(FEATURE_WIFI_TDLS);

	int ret = wifi_manager_initialize(&g_hWifi);
	PRINT_RETURN("wifi_manager_initialize", ret);
}

/**
 * @function		utc_wifi_manager_tdls_cleanup
 * @since_tizen		3.0
 * @description		Deinitializes Wi-Fi.Called after each test.
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_manager_tdls_cleanup(void)
{
	int ret = wifi_manager_deinitialize(g_hWifi);
	PRINT_RETURN("wifi_manager_deinitialize", ret);
}

/**
 * @testcase        utc_wifi_manager_tdls_start_discovery_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     Discovers devices that support TDLS.
 * @scenario        Discovers devices that support TDLS.
 */
int utc_wifi_manager_tdls_start_discovery_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_tdls_start_discovery(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		CHECK_RETURN("wifi_manager_tdls_start_discovery", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_tdls_start_discovery", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_tdls_connect_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     Connects to a peer device.
 * @scenario        Connects to a peer device.
 */
int utc_wifi_manager_tdls_connect_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_tdls_connect(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		CHECK_RETURN("wifi_manager_tdls_connect", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_tdls_connect", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_tdls_enable_channel_switching_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     Enable a TDLS channel switching request.
 * @scenario        Enable a TDLS channel switching request.
 */
int utc_wifi_manager_tdls_enable_channel_switching_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_tdls_enable_channel_switching(NULL, NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		CHECK_RETURN("wifi_manager_tdls_enable_channel_switching", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_tdls_enable_channel_switching", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_tdls_disable_channel_switching_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     Disable a TDLS channel switching request.
 * @scenario        Disable a TDLS channel switching request.
 */
int utc_wifi_manager_tdls_disable_channel_switching_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_tdls_disable_channel_switching(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		CHECK_RETURN("wifi_manager_tdls_disable_channel_switching", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_tdls_disable_channel_switching", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_tdls_disconnect_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Disconnects the connected peer.
 * @scenario		Disconnects the connected peer for tdls.
 */
int utc_wifi_manager_tdls_disconnect_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_tdls_disconnect(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		CHECK_RETURN("wifi_manager_tdls_disconnect", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_tdls_disconnect", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_tdls_get_connected_peer_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Gets Peer Mac address of Connected peer.
 * @scenario		Gets Peer Mac address of Connected peer for tdls.
 */
int utc_wifi_manager_tdls_get_connected_peer_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_tdls_get_connected_peer(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		CHECK_RETURN("wifi_manager_tdls_get_connected_peer", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_tdls_get_connected_peer", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_tdls_set_state_changed_cb_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Registers the callback called when TDLS state is changed.
 * @scenario		Registers the callback called when TDLS state is changed.
 */
int utc_wifi_manager_tdls_set_state_changed_cb_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_tdls_set_state_changed_cb(g_hWifi, wifi_manager_tdls_state_changed_callback, NULL);

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		CHECK_RETURN("wifi_manager_tdls_set_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_tdls_set_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_tdls_set_state_changed_cb_n
 * @since_tizen		3.0
 * @type			Negative
 * @description		Registers the callback called when TDLS state is changed.
 * @scenario		Registers the callback called when TDLS state is changed.
 */
int utc_wifi_manager_tdls_set_state_changed_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_tdls_set_state_changed_cb(NULL, NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		CHECK_RETURN("wifi_manager_tdls_set_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_tdls_set_state_changed_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_wifi_manager_tdls_unset_state_changed_cb_p
 * @since_tizen		3.0
 * @type			Positive
 * @description		Registers the callback called when TDLS state is changed.
 * @scenario		Registers the callback called when TDLS state is changed.
 */
int utc_wifi_manager_tdls_unset_state_changed_cb_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		ret = wifi_manager_tdls_unset_state_changed_cb(g_hWifi);
		CHECK_RETURN("wifi_manager_tdls_unset_state_changed_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_tdls_set_state_changed_cb(g_hWifi, wifi_manager_tdls_state_changed_callback, NULL);
	CHECK_RETURN("wifi_manager_tdls_set_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_tdls_unset_state_changed_cb(g_hWifi);
	CHECK_RETURN("wifi_manager_tdls_unset_state_changed_cb", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_manager_tdls_unset_state_changed_cb_n
 * @since_tizen		3.0
 * @type			Positive
 * @description		Registers the callback called when TDLS state is changed.
 * @scenario		Registers the callback called when TDLS state is changed.
 */
int utc_wifi_manager_tdls_unset_state_changed_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_tdls_unset_state_changed_cb(NULL);

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		CHECK_RETURN("", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_tdls_set_discovered_cb_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Registers the callback called when TDLS peer is discovered.
 * @scenario		Registers the callback called when TDLS peer is discovered.
 */
int utc_wifi_manager_tdls_set_discovered_cb_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_tdls_set_discovered_cb(g_hWifi, wifi_manager_tdls_discovered_callback, NULL);

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		CHECK_RETURN("wifi_manager_tdls_set_discovered_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_tdls_set_discovered_cb", ret, WIFI_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_tdls_set_discovered_cb_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     Registers the callback called when TDLS peer is discovered.
 * @scenario        Registers the callback called when TDLS peer is discovered.
 */
int utc_wifi_manager_tdls_set_discovered_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_tdls_set_discovered_cb(NULL, NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		CHECK_RETURN("wifi_manager_tdls_set_discovered_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("wifi_manager_tdls_set_discovered_cb", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_wifi_manager_tdls_unset_discovered_cb_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Registers the callback called when TDLS peer is discovered.
 * @scenario        Registers the callback called when TDLS peer is discovered.
 */
int utc_wifi_manager_tdls_unset_discovered_cb_p(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		ret = wifi_manager_tdls_unset_discovered_cb(g_hWifi);
		CHECK_RETURN("wifi_manager_tdls_unset_discovered_cb", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_tdls_set_discovered_cb(g_hWifi, wifi_manager_tdls_discovered_callback, NULL);
	CHECK_RETURN("wifi_manager_tdls_set_discovered_cb", ret, WIFI_MANAGER_ERROR_NONE);

	ret = wifi_manager_tdls_unset_discovered_cb(g_hWifi);
	CHECK_RETURN("wifi_manager_tdls_unset_discovered_cb", ret, WIFI_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_wifi_manager_tdls_unset_discovered_cb_n
 * @since_tizen     4.0
 * @type            Positive
 * @description     Registers the callback called when TDLS peer is discovered.
 * @scenario        Registers the callback called when TDLS peer is discovered.
 */
int utc_wifi_manager_tdls_unset_discovered_cb_n(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_tdls_unset_discovered_cb(NULL);

	if (!g_bFeatureWifi || !g_bFeatureWifiTDLS) {
		CHECK_RETURN("", ret, WIFI_MANAGER_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("", ret, WIFI_MANAGER_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


