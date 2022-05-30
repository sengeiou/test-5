/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "utc-intelligent-network-monitoring-common.h"



/**
 * @function        utc_inm_startup
 * @since_tizen     5.0
 * @description     Initializes inm.Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_inm_startup(void)
{
	g_bFeatureInm = inm_check_feature_supported(FEATURE_INM);
	g_bFeatureWifi = inm_check_feature_supported(FEATURE_WIFI);
	g_bFeatureEthernet = inm_check_feature_supported(FEATURE_ETHERNET);
	g_bFeatureTelephony = inm_check_feature_supported(FEATURE_TELEPHONY);
	g_bFeatureBttethering = inm_check_feature_supported(FEATURE_BT_TETHERING);

	int ret = inm_initialize(&g_hInm);
	PRINT_RETURN("inm_initialize", ret);
	if (ret != INM_ERROR_NONE) {
		g_bFeatureAllNotSupported = !g_bFeatureInm;
		return;
	}

	ret = inm_get_current_connection(g_hInm, &g_hConnection);
	if (ret != INM_ERROR_NONE)
		FPRINTF("[%s:%d] Fail to get current profile or service\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Fail to get current profile or service", __FILE__, __LINE__);
		return;

	if (g_bFeatureTelephony == false && g_bFeatureWifi == false
			&& g_bFeatureBttethering == false && g_bFeatureEthernet == false
			&& g_bFeatureInm == false) {
		g_bFeatureAllNotSupported = true;
		FPRINTF("[%s:%d] All feature is not supported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] all feature is not supported", __FILE__, __LINE__);
		return;
	}
}

/**
 * @function        utc_inm_cleanup
 * @since_tizen     5.0
 * @description     Deinitializes inm.Called after each test.
 * @parameter       NA
 * @return          NA
 */
void utc_inm_cleanup(void)
{
	int ret = inm_deinitialize(g_hInm);
	PRINT_RETURN("inm_deinitialize", ret);
	if (ret != INM_ERROR_NONE)
		return;
	g_hInm = NULL;
}


/*****************************************
 * CAPI_NETWORK_INM_SPECIFIC_MODULE
 *****************************************/


/**
 * @testcase       utc_inm_set_ethernet_cable_state_changed_cb_n
 * @since_tizen    5.0
 * @type           Negative
 * @description    inm_set_ethernet_cable_state_changed_cb should fail with invalid parameter.
 * @scenario       Verify inm_set_ethernet_cable_state_changed_cb by passing invalid parameter.
 */
int utc_inm_set_ethernet_cable_state_changed_cb_n(void)
{
	int ret;
	if (!g_bFeatureEthernet || !g_bFeatureInm) {
		ret = inm_set_ethernet_cable_state_changed_cb(NULL, NULL, NULL);
		CHECK_RETURN("inm_set_ethernet_cable_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_set_ethernet_cable_state_changed_cb(NULL,
			inm_set_ethernet_cable_state_changed_callback, NULL);
	CHECK_RETURN("inm_set_ethernet_cable_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_set_ethernet_cable_state_changed_cb(g_hInm, NULL, NULL);
	CHECK_RETURN("inm_set_ethernet_cable_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_unset_ethernet_cable_state_changed_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_unset_ethernet_cable_state_changed_cb should fail with invalid parameter.
 * @scenario        Verify inm_unset_ethernet_cable_state_changed_cb by passing invalid parameter.
 */
int utc_inm_unset_ethernet_cable_state_changed_cb_n(void)
{
	int ret;
	ret = inm_unset_ethernet_cable_state_changed_cb(NULL);

	if (!g_bFeatureEthernet || !g_bFeatureInm) {
		CHECK_RETURN("inm_unset_ethernet_cable_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_unset_ethernet_cable_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_ethernet_cable_state_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Checks for ethernet cable is attached or not.
 * @scenario        Invoking inm_get_ethernet_cable_state with valid parameter.
 */
int utc_inm_get_ethernet_cable_state_p(void)
{
	int ret;
	inm_ethernet_cable_state_e cable_state;

	ret = inm_get_ethernet_cable_state(g_hInm, &cable_state);
	if (!g_bFeatureEthernet || !g_bFeatureInm) {
		CHECK_RETURN("inm_get_ethernet_cable_state", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_ethernet_cable_state", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_ethernet_cable_state_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_get_ethernet_cable_state should fail with invalid parameter.
 * @scenario        Verify inm_get_ethernet_cable_state by passing invalid parameter.
 */
int utc_inm_get_ethernet_cable_state_n(void)
{
	int ret = INM_ERROR_NONE;
	inm_ethernet_cable_state_e cable_state;

	if (!g_bFeatureEthernet || !g_bFeatureInm) {
		ret = inm_get_ethernet_cable_state(NULL, NULL);
		CHECK_RETURN("inm_get_ethernet_cable_state", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_get_ethernet_cable_state(NULL, &cable_state);
	CHECK_RETURN("inm_get_ethernet_cable_state", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_get_ethernet_cable_state(g_hInm, NULL);
	CHECK_RETURN("inm_get_ethernet_cable_state", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_set_wifi_module_state_changed_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_set_wifi_module_state_changed_cb by passing invalid parameters
 * @scenario        Pass invalid parameters and ensure Wi-Fi module state is not notofied through callback.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_set_wifi_module_state_changed_cb_n(void)
{
	int ret = INM_ERROR_NONE;

	char *profile = NULL;

	ret = inm_set_wifi_module_state_changed_cb(NULL, NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_set_wifi_module_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_set_wifi_module_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

	FREE_MEMORY_TC(profile)

    return 0;
}

/**
 * @testcase        utc_inm_unset_wifi_module_state_changed_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_unset_wifi_module_state_changed_cb by changing the state
 * @scenario        Unset Wi-Fi module state changed callback and ensure Wi-Fi module state is not notofied through callback.
 *                  Ensure return value should be INM_ERROR_INVALID_OPERATION.
 */
int utc_inm_unset_wifi_module_state_changed_cb_n(void)
{
	int ret = INM_ERROR_NONE;

	char *profile = NULL;

	ret = inm_unset_wifi_module_state_changed_cb(NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_unset_wifi_module_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_unset_wifi_module_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

	FREE_MEMORY_TC(profile)

	return 0;
}


/**
 * @testcase          utc_inm_get_wifi_module_state_p
 * @since_tizen       5.0
 * @type              Positive
 * @description	Gets  The Wi-Fi module state.
 * @scenario          Get Wi-Fi module state. Ensure no error.
 */
int utc_inm_get_wifi_module_state_p(void)
{
	inm_wifi_module_state_e module_state;
	int ret = INM_ERROR_NONE;

	char *profile = NULL;

	ret = inm_get_wifi_module_state(g_hInm, &module_state);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_get_wifi_module_state", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_wifi_module_state", ret, INM_ERROR_NONE);
	}

	FREE_MEMORY_TC(profile);

	return 0;
}

/**
 * @testcase            utc_inm_get_wifi_module_state_n
 * @since_tizen         5.0
 * @type                Negative
 * @description	Verify  inm_get_wifi_module_state by passing invalid parameters(module_state).
 * @scenario            Pass invalid parameter and ensure wifi module state is not returned.
 *                      Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_get_wifi_module_state_n(void)
{
    int ret = INM_ERROR_NONE;

	char *profile = NULL;

	ret = inm_get_wifi_module_state(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_get_wifi_module_state", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_wifi_module_state", ret, INM_ERROR_INVALID_PARAMETER);
	}

	FREE_MEMORY_TC(profile);

    return 0;
}

/**
 * @testcase        utc_inm_set_ip_conflict_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_set_ip_conflict_cb() should be failed.
 * @scenario        Invoke inm_set_ip_conflict_cb() with invalid parameter.
 */
int utc_inm_set_ip_conflict_cb_n(void)
{
    int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm || ( g_bFeatureWifi == false && g_bFeatureEthernet ==
				false)) {
		ret = inm_set_ip_conflict_cb(NULL, NULL, NULL);
		CHECK_RETURN("inm_set_ip_conflict_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		ret = inm_set_ip_conflict_cb(NULL, inm_set_ip_conflict_callback, NULL);
		CHECK_RETURN("inm_set_ip_conflict_cb", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_set_ip_conflict_cb(g_hInm, NULL, NULL);
		CHECK_RETURN("inm_set_ip_conflict_cb", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_set_ip_conflict_cb(NULL, NULL, NULL);
		CHECK_RETURN("inm_set_ip_conflict_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase        utc_inm_unset_ip_conflict_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_unset_ip_conflict_cb() should be failed.
 * @scenario        Invoke inm_unset_ip_conflict_cb() with invalid parameter.
 */
int utc_inm_unset_ip_conflict_cb_n(void)
{
    int	ret = inm_unset_ip_conflict_cb(NULL);

	if (!g_bFeatureInm || (g_bFeatureWifi == false && g_bFeatureEthernet ==
			       false)) {
		CHECK_RETURN("inm_unset_ip_conflict_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_unset_ip_conflict_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase        utc_inm_ip_conflict_detect_is_enabled_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Checks whether IP conflict detection is enabled.
 * @scenario        Invoke inm_ip_conflict_detect_is_enabled() with valid parameter.
 */
int utc_inm_ip_conflict_detect_is_enabled_p(void)
{
	bool state;

	int ret = inm_ip_conflict_detect_is_enabled(g_hInm, &state);

	if (!g_bFeatureInm || (g_bFeatureWifi == false && g_bFeatureEthernet ==
			       false)) {
		CHECK_RETURN("inm_ip_conflict_detect_is_enabled", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_ip_conflict_detect_is_enabled", ret, INM_ERROR_NONE);
	}

    return 0;
}

/**
 * @testcase        utc_inm_ip_conflict_detect_is_enabled_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_ip_conflict_detect_is_enabled() should be failed.
 * @scenario        Invoke inm_ip_conflict_detect_is_enableds() with invalid parameter.
 */
int utc_inm_ip_conflict_detect_is_enabled_n(void)
{
	int ret = INM_ERROR_NONE;
	bool state;

	if (!g_bFeatureInm || (g_bFeatureWifi == false && g_bFeatureEthernet ==
			       false)) {
		ret = inm_ip_conflict_detect_is_enabled(NULL, &state);
		CHECK_RETURN("inm_ip_conflict_detect_is_enabled", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		ret = inm_ip_conflict_detect_is_enabled(NULL, &state);
		CHECK_RETURN("inm_ip_conflict_detect_is_enabled", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_ip_conflict_detect_is_enabled(g_hInm, NULL);
		CHECK_RETURN("inm_ip_conflict_detect_is_enabled", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_ip_conflict_detect_is_enabled(NULL, NULL);
		CHECK_RETURN("inm_ip_conflict_detect_is_enabled", ret, INM_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase        utc_inm_get_ip_conflict_state_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the state of the IP conflict.
 * @scenario        Invoke inm_get_ip_conflict_state() with valid parameter.
 */
int utc_inm_get_ip_conflict_state_p(void)
{
	inm_ip_conflict_state_e state;

	int ret = inm_get_ip_conflict_state(g_hInm, &state);

	if (!g_bFeatureInm || (g_bFeatureWifi == false && g_bFeatureEthernet ==
			       false)) {
		CHECK_RETURN("inm_get_ip_conflict_state", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_ip_conflict_state", ret,INM_ERROR_NONE);
	}

    return 0;
}

/**
 * @testcase        utc_inm_get_ip_conflict_state_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_get_ip_conflict_state() should be failed.
 * @scenario        Invoke inm_get_ip_conflict_state() with invalid parameter.
 */
int utc_inm_get_ip_conflict_state_n(void)
{
	int ret = INM_ERROR_NONE;
	inm_ip_conflict_state_e state;

	if (!g_bFeatureInm || (g_bFeatureWifi == false && g_bFeatureEthernet ==
			       false)) {
		ret = inm_get_ip_conflict_state(NULL, &state);
		CHECK_RETURN("inm_get_ip_conflict_state", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		ret = inm_get_ip_conflict_state(g_hInm, NULL);
		CHECK_RETURN("inm_get_ip_conflict_state", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_get_ip_conflict_state(NULL, &state);
		CHECK_RETURN("inm_get_ip_conflict_state", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_get_ip_conflict_state(NULL, NULL);
		CHECK_RETURN("inm_get_ip_conflict_state", ret, INM_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/* TODO: Add inm_start_tcpdump */
/* TODO: Add inm_stop_tcpdump */
/* TODO: Add inm_get_tcpdump_state */

/**
 * @testcase        utc_inm_get_statistics_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the statistics information.
 * @scenario        Invoking inm_get_statistics with valid parameter.
 */
int utc_inm_get_statistics_p(void)
{
	unsigned long long stat;

	if (g_bFeatureTelephony && g_bFeatureInm) {
		int ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, INM_STATISTICS_TYPE_LAST_SENT_DATA, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_NONE);
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, INM_STATISTICS_TYPE_LAST_RECEIVED_DATA, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_NONE);
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, INM_STATISTICS_TYPE_TOTAL_SENT_DATA, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_NONE);
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, INM_STATISTICS_TYPE_TOTAL_RECEIVED_DATA, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_NONE);
	} else {
		int ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, INM_STATISTICS_TYPE_LAST_SENT_DATA, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_NOT_SUPPORTED);
	}

	if (g_bFeatureWifi && g_bFeatureInm) {
		int ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, INM_STATISTICS_TYPE_LAST_SENT_DATA, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_NONE);
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, INM_STATISTICS_TYPE_LAST_RECEIVED_DATA, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_NONE);
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, INM_STATISTICS_TYPE_TOTAL_SENT_DATA, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_NONE);
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, INM_STATISTICS_TYPE_TOTAL_RECEIVED_DATA, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_NONE);
	} else {
		int ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, INM_STATISTICS_TYPE_LAST_SENT_DATA, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_statistics_n
 * @since_tizen     5.3
 * @type            Negative
 * @description     inm_get_statistics should fail with invalid parameter.
 * @scenario        Verify inm_get_statistics by passing invalid parameter.
 */
int utc_inm_get_statistics_n(void)
{
	int ret = INM_ERROR_NONE;
	unsigned long long stat;

	if (!g_bFeatureInm || (g_bFeatureTelephony == false && g_bFeatureWifi ==
			       false)) {
		ret = inm_get_statistics(NULL, -1, -1, NULL);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_get_statistics(NULL, -1, -1, NULL);
	CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_get_statistics(g_hInm, -1, INM_STATISTICS_TYPE_LAST_SENT_DATA, &stat);
	CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_get_statistics(g_hInm, -1, -1, &stat);
	CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_INVALID_PARAMETER);

	if (g_bFeatureTelephony) {
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, -1, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, INM_STATISTICS_TYPE_LAST_SENT_DATA, NULL);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, -1, NULL);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_INVALID_PARAMETER);
	} else {
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, -1, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_NOT_SUPPORTED);
	}

	if (g_bFeatureWifi) {
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, -1, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, INM_STATISTICS_TYPE_LAST_SENT_DATA, NULL);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, -1, NULL);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_INVALID_PARAMETER);
	} else {
		ret = inm_get_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, -1, &stat);
		CHECK_RETURN("inm_get_statistics", ret, INM_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase        utc_inm_reset_statistics_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Resets the statistics information.
 * @scenario        Invoking inm_reset_statistics with valid parameter.
 */
int utc_inm_reset_statistics_p(void)
{
	int ret = INM_ERROR_NONE;

	if (g_bFeatureTelephony && g_bFeatureInm) {
		ret = inm_reset_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, INM_STATISTICS_TYPE_LAST_SENT_DATA);
		CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_NONE);
		ret = inm_reset_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, INM_STATISTICS_TYPE_LAST_RECEIVED_DATA);
		CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_NONE);
		ret = inm_reset_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, INM_STATISTICS_TYPE_TOTAL_SENT_DATA);
		CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_NONE);
		ret = inm_reset_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, INM_STATISTICS_TYPE_TOTAL_RECEIVED_DATA);
		CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_NONE);
	} else {
		ret = inm_reset_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, INM_STATISTICS_TYPE_LAST_SENT_DATA);
		CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_NOT_SUPPORTED);
	}

	if (g_bFeatureWifi && g_bFeatureInm) {
		ret = inm_reset_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, INM_STATISTICS_TYPE_LAST_SENT_DATA);
		CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_NONE);
		ret = inm_reset_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, INM_STATISTICS_TYPE_LAST_RECEIVED_DATA);
		CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_NONE);
		ret = inm_reset_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, INM_STATISTICS_TYPE_TOTAL_SENT_DATA);
		CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_NONE);
		ret = inm_reset_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, INM_STATISTICS_TYPE_TOTAL_RECEIVED_DATA);
		CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_NONE);
	} else {
		ret = inm_reset_statistics(g_hInm, INM_CONNECTION_TYPE_WIFI, INM_STATISTICS_TYPE_LAST_SENT_DATA);
		CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase        utc_inm_reset_statistics_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_reset_statistics should fail with invalid parameter.
 * @scenario        Verify inm_reset_statistics by passing invalid parameter.
 */
int utc_inm_reset_statistics_n(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm || (g_bFeatureTelephony == false && g_bFeatureWifi ==
			       false)) {
		ret = inm_reset_statistics(NULL, -1, -1);
		CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_reset_statistics(NULL, -1, -1);
	CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_reset_statistics(g_hInm, -1, INM_STATISTICS_TYPE_LAST_SENT_DATA);
	CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_INVALID_PARAMETER);

	if (g_bFeatureTelephony) {
		ret = inm_reset_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, -1);
		CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_INVALID_PARAMETER);
	} else {
		ret = inm_reset_statistics(g_hInm, INM_CONNECTION_TYPE_CELLULAR, -1);
		CHECK_RETURN("inm_reset_statistics", ret, INM_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase        utc_inm_set_congestion_level_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_set_congestion_level_cb should fail with invalid parameter.
 * @scenario        Verify inm_set_congestion_level_cb by passing callback and user_data as NULL.
 */
int utc_inm_set_congestion_level_cb_n(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm || (g_bFeatureTelephony == false && g_bFeatureWifi ==
			       false && g_bFeatureEthernet == false)) {
		ret = inm_set_congestion_level_cb(NULL, NULL, NULL);
		CHECK_RETURN("inm_set_congestion_level_cb", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_set_congestion_level_cb(NULL, NULL, NULL);
	CHECK_RETURN("inm_set_congestion_level_cb", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_set_congestion_level_cb(g_hInm, NULL, NULL);
	CHECK_RETURN("inm_set_congestion_level_cb", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase        utc_inm_unset_congestion_level_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_unset_congestion_level_cb should fail with invalid parameter.
 * @scenario        Verify inm_unset_congestion_level_cb by passing invalid profile handle.
 */
int utc_inm_unset_congestion_level_cb_n(void)
{
	int ret = inm_unset_congestion_level_cb(NULL);

	if (!g_bFeatureInm || (g_bFeatureTelephony == false && g_bFeatureWifi ==
			       false && g_bFeatureEthernet == false)) {
		CHECK_RETURN("inm_unset_congestion_level_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_unset_congestion_level_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_congestion_level_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the level of the congestion.
 * @scenario        Invoke inm_get_congestion_level() with valid parameter.
 */
int utc_inm_get_congestion_level_p(void)
{
	inm_congestion_level_e level;

	int ret = inm_get_congestion_level(g_hInm, &level);

	if (!g_bFeatureInm || (g_bFeatureTelephony == false && g_bFeatureWifi ==
			       false && g_bFeatureEthernet == false)) {
		CHECK_RETURN("inm_get_congestion_level", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_congestion_level", ret,INM_ERROR_NONE);
	}

    return 0;
}

/**
 * @testcase        utc_inm_get_congestion_level_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_get_congestion_level() should be failed.
 * @scenario        Invoke inm_get_congestion_level() with invalid parameter.
 */
int utc_inm_get_congestion_level_n(void)
{
	int ret = INM_ERROR_NONE;
	inm_congestion_level_e level;

	/* TODO: Check the feature */
	if (!g_bFeatureWifi || !g_bFeatureInm) {
		ret = inm_get_congestion_level(NULL, &level);
		CHECK_RETURN("inm_get_congestion_level", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		ret = inm_get_congestion_level(g_hInm, NULL);
		CHECK_RETURN("inm_get_congestion_level", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_get_congestion_level(NULL, &level);
		CHECK_RETURN("inm_get_congestion_level", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_get_congestion_level(NULL, NULL);
		CHECK_RETURN("inm_get_congestion_level", ret, INM_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase        utc_inm_set_retry_tx_rate_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_set_retry_tx_rate_cb should fail with invalid parameter.
 * @scenario        Verify inm_set_retry_tx_rate_cb by passing callback and user_data as NULL.
 */
int utc_inm_set_retry_tx_rate_cb_n(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		ret = inm_set_retry_tx_rate_cb(NULL, NULL, NULL);
		CHECK_RETURN("inm_set_retry_tx_rate_cb", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_set_retry_tx_rate_cb(NULL, NULL, NULL);
	CHECK_RETURN("inm_set_retry_tx_rate_cb", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_set_retry_tx_rate_cb(g_hInm, NULL, NULL);
	CHECK_RETURN("inm_set_retry_tx_rate_cb", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase        utc_inm_unset_retry_tx_rate_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_unset_retry_tx_rate_cb should fail with invalid parameter.
 * @scenario        Verify inm_unset_retry_tx_rate_cb by passing invalid profile handle.
 */
int utc_inm_unset_retry_tx_rate_cb_n(void)
{
	int ret = inm_unset_retry_tx_rate_cb(NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_unset_retry_tx_rate_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_unset_retry_tx_rate_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_retry_tx_rate_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the Tx rate.
 * @scenario        Check AP validity and get Tx rate from AP infomation. Check the return value.
 */
int utc_inm_get_retry_tx_rate_p(void)
{
	int tx_rate = 0;
	int ret = INM_ERROR_NONE;

	ret = inm_get_retry_tx_rate(g_hInm, &tx_rate);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_get_retry_tx_rate", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_retry_tx_rate", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_retry_tx_rate_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_get_retry_tx_rate by passing invalid parameters(ap, Tx rate).
 * @scenario        Pass invalid AP information. Proper Tx rate is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_get_retry_tx_rate_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_get_retry_tx_rate(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_get_retry_tx_rate", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_retry_tx_rate", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_set_channel_interference_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_set_channel_interference_cb should fail with invalid parameter.
 * @scenario        Verify inm_set_channel_interference_cb by passing callback and user_data as NULL.
 */
int utc_inm_set_channel_interference_cb_n(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		ret = inm_set_channel_interference_cb(NULL, NULL, NULL);
		CHECK_RETURN("inm_set_channel_interference_cb", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_set_channel_interference_cb(NULL, NULL, NULL);
	CHECK_RETURN("inm_set_channel_interference_cb", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_set_channel_interference_cb(g_hInm, NULL, NULL);
	CHECK_RETURN("inm_set_channel_interference_cb", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase        utc_inm_unset_channel_interference_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_unset_channel_interference_cb should fail with invalid parameter.
 * @scenario        Verify inm_unset_channel_interference_cb by passing invalid profile handle.
 */
int utc_inm_unset_channel_interference_cb_n(void)
{
	int ret = inm_unset_channel_interference_cb(NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_unset_channel_interference_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_unset_channel_interference_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_channel_interference_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the RSSI.
 * @scenario        Check AP validity and get RSSI from AP infomation. Check the return value.
 */
int utc_inm_get_channel_interference_p(void)
{
	double interference = 0;
	int ret = INM_ERROR_NONE;

	ret = inm_get_channel_interference(g_hInm, &interference);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_get_channel_interference", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_channel_interference", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_channel_interference_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_get_channel_interference by passing invalid parameters(ap, interference).
 * @scenario        Pass invalid AP information. Proper interference is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_get_channel_interference_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_get_channel_interference(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_get_channel_interference", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_channel_interference", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/*****************************************
 * CAPI_NETWORK_INM_GENERAL_MODULE
 *****************************************/


/**
 * @testcase        utc_inm_set_cellular_state_changed_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_set_cellular_state_changed_cb should fail with invalid parameter.
 * @scenario        Verify inm_set_cellular_state_changed_cb by passing callback and user_data as NULL.
 */
int utc_inm_set_cellular_state_changed_cb_n(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureTelephony || !g_bFeatureInm) {
		ret = inm_set_cellular_state_changed_cb(NULL, NULL, NULL);
		CHECK_RETURN("inm_set_cellular_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_set_cellular_state_changed_cb(NULL, NULL, NULL);
	CHECK_RETURN("inm_set_cellular_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_set_cellular_state_changed_cb(g_hInm, NULL, NULL);
	CHECK_RETURN("inm_set_cellular_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase        utc_inm_unset_cellular_state_changed_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_unset_cellular_state_changed_cb should fail with invalid parameter.
 * @scenario        Verify inm_unset_cellular_state_changed_cb by passing invalid profile handle.
 */
int utc_inm_unset_cellular_state_changed_cb_n(void)
{
	int ret = inm_unset_cellular_state_changed_cb(NULL);

	if (!g_bFeatureTelephony || !g_bFeatureInm) {
		CHECK_RETURN("inm_unset_cellular_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_unset_cellular_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_cellular_state_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the state of the celluar.
 * @scenario        Invoke inm_get_cellular_state() with valid parameter.
 */
int utc_inm_get_cellular_state_p(void)
{
	inm_cellular_state_e state;

	int ret = inm_get_cellular_state(g_hInm, &state);

	/* TODO: Check the feature */
	if (!g_bFeatureTelephony || !g_bFeatureInm) {
		CHECK_RETURN("inm_get_cellular_state", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_cellular_state", ret, INM_ERROR_NONE);
	}

    return 0;
}

/**
 * @testcase        utc_inm_get_cellular_state_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_get_cellular_state() should be failed.
 * @scenario        Invoke inm_get_cellular_state() with invalid parameter.
 */
int utc_inm_get_cellular_state_n(void)
{
	int ret = INM_ERROR_NONE;
	inm_cellular_state_e state;

	/* TODO: Check the feature */
	if (!g_bFeatureTelephony || !g_bFeatureInm) {
		ret = inm_get_cellular_state(NULL, &state);
		CHECK_RETURN("inm_get_cellular_state", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		ret = inm_get_cellular_state(g_hInm, NULL);
		CHECK_RETURN("inm_get_cellular_state", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_get_cellular_state(NULL, &state);
		CHECK_RETURN("inm_get_cellular_state", ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_get_cellular_state(NULL, NULL);
		CHECK_RETURN("inm_get_cellular_state", ret, INM_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase        utc_inm_set_wifi_state_changed_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_set_wifi_state_changed_cb should fail with invalid parameter.
 * @scenario        Verify inm_set_wifi_state_changed_cb by passing callback and user_data as NULL.
 */
int utc_inm_set_wifi_state_changed_cb_n(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		ret = inm_set_wifi_state_changed_cb(NULL, NULL, NULL);
		CHECK_RETURN("inm_set_wifi_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_set_wifi_state_changed_cb(NULL, inm_set_wifi_state_changed_callback, NULL);
	CHECK_RETURN("inm_set_wifi_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_set_wifi_state_changed_cb(g_hInm, NULL, NULL);
	CHECK_RETURN("inm_set_wifi_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase        utc_inm_unset_wifi_state_changed_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_unset_wifi_state_changed_cb should fail with invalid parameter.
 * @scenario        Verify inm_unset_wifi_state_changed_cb by passing invalid profile handle.
 */
int utc_inm_unset_wifi_state_changed_cb_n(void)
{
	int ret = inm_unset_wifi_state_changed_cb(NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_unset_wifi_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_unset_wifi_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_wifi_state_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the Wi-Fi state.
 * @scenario        Get Wi-Fi state. Ensure no error.
 */
int utc_inm_get_wifi_state_p(void)
{
	inm_wifi_state_e state;
	int ret = INM_ERROR_NONE;

	ret = inm_get_wifi_state(g_hInm, &state);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_get_wifi_state", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_wifi_state", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_wifi_state_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_get_wifi_state by passing invalid parameters(wifi_state).
 * @scenario        Pass invalid parameter and ensure wifi state is not returned.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_get_wifi_state_n(void)
{
    int ret = INM_ERROR_NONE;

	ret = inm_get_wifi_state(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_get_wifi_state", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_wifi_state", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_set_ethernet_state_changed_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_set_ethernet_state_changed_cb should fail with invalid parameter.
 * @scenario        Verify inm_set_ethernet_state_changed_cb by passing callback and user_data as NULL.
 */
int utc_inm_set_ethernet_state_changed_cb_n(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureEthernet || !g_bFeatureInm) {
		ret = inm_set_ethernet_state_changed_cb(NULL, NULL, NULL);
		CHECK_RETURN("inm_set_ethernet_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_set_ethernet_state_changed_cb(g_hInm, NULL, NULL);
	CHECK_RETURN("inm_set_ethernet_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_set_ethernet_state_changed_cb(NULL, inm_set_ethernet_state_changed_callback, NULL);
	CHECK_RETURN("inm_set_ethernet_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase        utc_inm_unset_ethernet_state_changed_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_unset_ethernet_state_changed_cb should fail with invalid parameter.
 * @scenario        Verify inm_unset_ethernet_state_changed_cb by passing invalid profile handle.
 */
int utc_inm_unset_ethernet_state_changed_cb_n(void)
{
	int ret = inm_unset_ethernet_state_changed_cb(NULL);

	if (!g_bFeatureEthernet || !g_bFeatureInm) {
		CHECK_RETURN("inm_unset_ethernet_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_unset_ethernet_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_ethernet_state_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the ethernet state.
 * @scenario        Get ethernet state. Ensure no error.
 */
int utc_inm_get_ethernet_state_p(void)
{
	inm_ethernet_state_e state;
	int ret = INM_ERROR_NONE;

	ret = inm_get_ethernet_state(g_hInm, &state);

	if (!g_bFeatureEthernet || !g_bFeatureInm) {
		CHECK_RETURN("inm_get_ethernet_state", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_ethernet_state", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_ethernet_state_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_get_ethernet_state by passing invalid parameters(wifi_state).
 * @scenario        Pass invalid parameter and ensure ethernet state is not returned.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_get_ethernet_state_n(void)
{
    int ret = INM_ERROR_NONE;

	ret = inm_get_ethernet_state(NULL, NULL);

	if (!g_bFeatureEthernet || !g_bFeatureInm) {
		CHECK_RETURN("inm_get_ethernet_state", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_ethernet_state", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_current_connection_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the name of the default profile.
 * @scenario        Invoking inm_get_current_connection with valid parameter.
 */
int utc_inm_get_current_connection_p(void)
{
	int ret = inm_get_current_connection(g_hInm, &profile_temp);

	if (g_bFeatureAllNotSupported) {
		CHECK_RETURN("inm_get_current_connection", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_get_current_connection", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_get_current_connection_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_get_current_connection should fail with invalid parameter.
 * @scenario        Verify inm_get_current_connection by passing invalid parameter.
 */
int utc_inm_get_current_connection_n(void)
{
	int ret = INM_ERROR_NONE;
	inm_connection_h profile = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_get_current_connection(g_hInm, NULL);
		CHECK_RETURN("inm_get_current_connection", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_get_current_connection(NULL, NULL);
	CHECK_RETURN("inm_get_current_connection", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_get_current_connection(g_hInm, NULL);
	CHECK_RETURN("inm_get_current_connection", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_get_current_connection(NULL, &profile);
	CHECK_RETURN("inm_get_current_connection", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_destroy_p
 * @since_tizen 	5.0
 * @type            Positive
 * @description     Destroys the connection handle.
 * @scenario        Invoking connection_destroy with valid parameter.
 */
int utc_inm_connection_destroy_p(void)
{
	inm_connection_h profile_clone = NULL;

	int ret = inm_get_current_connection(g_hInm, &profile_temp);

	if (!g_bFeatureInm) {
		ret = inm_connection_destroy(&profile_clone);
		CHECK_RETURN("inm_connection_destroy", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	CHECK_RETURN("inm_get_current_connection", ret, INM_ERROR_NONE);

	if (profile_temp != NULL) {
		ret = inm_connection_clone(&profile_clone, profile_temp);
		CHECK_RETURN("inm_connection_clone", ret, INM_ERROR_NONE);
	}

	ret = inm_connection_destroy(&profile_clone);

	if (g_bFeatureAllNotSupported) {
		CHECK_RETURN("inm_connection_destroy", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_connection_destroy", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_connection_destroy_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_connection_destroy should fail with invalid parameter.
 * @scenario        Verify inm_connection_destroy by passing invalid parameter.
 */
int utc_inm_connection_destroy_n(void)
{
	int ret = inm_connection_destroy(NULL);

	if (g_bFeatureAllNotSupported) {
		CHECK_RETURN("inm_connection_destroy", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_connection_destroy", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_connection_clone_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Clones a profile handle.
 * @scenario        Verify inm_connection_clone with valid parameter and destroy it.
 */
int utc_inm_connection_clone_p(void)
{
	int ret = INM_ERROR_NONE;

	inm_connection_h profile_cloned = NULL;
	inm_connection_h profile_origin = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_clone(&profile_cloned, profile_origin);
		CHECK_RETURN("inm_connection_clone", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_origin);
	assert(profile_origin);

	if (profile_origin != NULL) {
		ret = inm_connection_clone(&profile_cloned, profile_origin);
		CHECK_RETURN("inm_connection_clone", ret, INM_ERROR_NONE);

		ret = inm_connection_destroy(&profile_origin);
		PRINT_RETURN("inm_connection_destroy", ret);
		ret = inm_connection_destroy(&profile_cloned);
		PRINT_RETURN("inm_connection_destroy", ret);
	}

	return 0;
}

/**
 * @testcase        utc_inm_connection_clone_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Should not Clones a profile handle.
 * @scenario        Verify inm_connection_clone by passing invalid parameters.
 */
int utc_inm_connection_clone_n(void)
{
	int ret = INM_ERROR_NONE;

	inm_connection_h profile_cloned = NULL;
	inm_connection_h profile_origin = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_clone(NULL, profile_origin);
		CHECK_RETURN("inm_connection_clone", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);
	assert(profile_any);

	ret = inm_connection_clone(NULL, profile_origin);
	CHECK_RETURN("inm_connection_clone", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_clone(NULL, profile_any);
	CHECK_RETURN("inm_connection_clone", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_clone(&profile_cloned, profile_origin);
	CHECK_RETURN("inm_connection_clone", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_get_connection_iterator_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets a profiles iterator.
 * @scenario        Invoking inm_get_connection_iterator with valid parameter.
 */
int utc_inm_get_connection_iterator_p(void)
{
	int ret = INM_ERROR_NONE;
	inm_connection_iterator_h g_hConnectionIterator;

	if (g_bFeatureAllNotSupported) {
		ret = inm_get_connection_iterator(g_hInm, &g_hConnectionIterator);
		CHECK_RETURN("inm_get_connection_iterator", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_get_connection_iterator(g_hInm, &g_hConnectionIterator);
	CHECK_RETURN("inm_get_connection_iterator", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_get_connection_iterator_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_get_connection_iterator should fail with invalid parameter.
 * @scenario        Verify inm_get_connection_iterator by passing invalid parameter.
 */
int utc_inm_get_connection_iterator_n(void)
{
	int ret = INM_ERROR_NONE;
	inm_connection_iterator_h g_hConnectionIterator;

	if (g_bFeatureAllNotSupported) {
		ret = inm_get_connection_iterator(g_hInm, &g_hConnectionIterator);
		CHECK_RETURN("inm_get_connection_iterator", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_get_connection_iterator(NULL, NULL);
	CHECK_RETURN("inm_get_connection_iterator", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_get_connection_iterator(NULL, &g_hConnectionIterator);
	CHECK_RETURN("inm_get_connection_iterator", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_get_connection_iterator(g_hInm, NULL);
	CHECK_RETURN("inm_get_connection_iterator", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_iterator_next_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Moves the profile iterator to the next position and gets a profile handle.
 * @scenario        Invoking inm_connection_iterator_next with valid parameter.
 */
int utc_inm_connection_iterator_next_p(void)
{
	int ret = INM_ERROR_NONE;
	inm_connection_iterator_h g_hConnectionIterator = NULL;
	inm_connection_h profile_h = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_iterator_next(g_hConnectionIterator, &profile_h);
		CHECK_RETURN("inm_connection_iterator_next", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_get_connection_iterator(g_hInm, &g_hConnectionIterator);
	PRINT_RETURN("inm_get_connection_iterator", ret);

	ret = inm_connection_iterator_next(g_hConnectionIterator, &profile_h);
	CHECK_RETURN("inm_connection_iterator_next", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_iterator_next_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_connection_iterator_next should fail with invalid parameter.
 * @scenario        Verify inm_connection_iterator_next by passing invalid parameter.
 */
int utc_inm_connection_iterator_next_n(void)
{
	inm_connection_h profile_h;

	int ret = inm_connection_iterator_next(NULL, &profile_h);

	if (g_bFeatureAllNotSupported) {
		CHECK_RETURN("inm_connection_iterator_next", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_connection_iterator_next", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_destroy_connection_iterator_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Destroys a connection iterator.
 * @scenario        Invoking inm_destroy_connection_iterator with valid parameter.
 */
int utc_inm_destroy_connection_iterator_p(void)
{
	int ret = INM_ERROR_NONE;
	inm_connection_iterator_h g_hConnectionIterator = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_destroy_connection_iterator(g_hConnectionIterator);
		CHECK_RETURN("inm_destroy_connection_iterator", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_get_connection_iterator(g_hInm, &g_hConnectionIterator);
	PRINT_RETURN("inm_get_connection_iterator", ret);

	ret = inm_destroy_connection_iterator(g_hConnectionIterator);
	CHECK_RETURN("inm_destroy_connection_iterator", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_destroy_connection_iterator_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_destroy_connection_iterator should fail with invalid parameter.
 * @scenario        Verify inm_destroy_connection_iterator by passing invalid parameter.
 */
int utc_inm_destroy_connection_iterator_n(void)
{
	int ret = inm_destroy_connection_iterator(NULL);

	if (g_bFeatureAllNotSupported) {
		CHECK_RETURN("inm_destroy_connection_iterator", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_destroy_connection_iterator", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/*****************************************
 * CAPI_NETWORK_CONNECTION_INM_MODULE
 *****************************************/


/**
 * @testcase        utc_inm_connection_get_id_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the connection ID.
 * @scenario        Invoking inm_connection_get_id with valid profile handle.
 */
int utc_inm_connection_get_id_p(void)
{
	char *id = NULL;
	int ret = INM_ERROR_NONE;
	inm_connection_h profile_h = NULL;

	inm_get_any_profile(&profile_h);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_id(profile_temp, &id);
		FREE_MEMORY_TC(id);
		CHECK_RETURN("inm_connection_get_id", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	profile_temp = profile_h;
	assert(profile_temp);

	ret = inm_connection_get_id(profile_temp, &id);
	FREE_MEMORY_TC(id);
	CHECK_RETURN("inm_connection_get_id", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_id_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Should not return connection ID.
 * @scenario        Verify inm_connection_get_id by passing invalid parameter.
 */
int utc_inm_connection_get_id_n(void)
{
	int ret = INM_ERROR_NONE;
	char *id = NULL;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_id(profile_inval, NULL);
		CHECK_RETURN("inm_connection_get_id", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

    ret = inm_connection_get_id(profile_inval, NULL);
    CHECK_RETURN("inm_connection_get_id", ret, INM_ERROR_INVALID_PARAMETER);
    ret = inm_connection_get_id(profile_inval, &id);
    CHECK_RETURN("inm_connection_get_id", ret, INM_ERROR_INVALID_PARAMETER);
    ret = inm_connection_get_id(profile_any, NULL);
    CHECK_RETURN("inm_connection_get_id", ret, INM_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase        utc_inm_connection_get_name_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the connection name.
 * @scenario        Get the connection name by invoking inm_connection_get_name with a valid parameter.
 */
int utc_inm_connection_get_name_p(void)
{
	int ret = INM_ERROR_NONE;
	char *name = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_name(profile_temp, &name);
		FREE_MEMORY_TC(name);
		CHECK_RETURN("inm_connection_get_name", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_temp);
	assert(profile_temp);

	ret = inm_connection_get_name(profile_temp, &name);
	FREE_MEMORY_TC(name);
	CHECK_RETURN("inm_connection_get_name", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_name_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Should not return connection handle.
 * @scenario        inm_connection_get_name by passing invalid connection handle.
 */
int utc_inm_connection_get_name_n(void)
{
	int ret = INM_ERROR_NONE;
	char *name = NULL;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;


	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_name(profile_inval, NULL);
		FREE_MEMORY_TC(name);
		CHECK_RETURN("inm_connection_get_name", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	ret = inm_connection_get_name(profile_inval, NULL);
	CHECK_RETURN("inm_connection_get_name", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_name(profile_inval, &name);
	FREE_MEMORY_TC(name);
	CHECK_RETURN("inm_connection_get_name", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_name(profile_any, NULL);
	CHECK_RETURN("inm_connection_get_name", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_type_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the network type.
 * @scenario        inm_connection_get_type should return profile type.
 */
int utc_inm_connection_get_type_p(void)
{
	int ret = INM_ERROR_NONE;
	inm_connection_type_e type;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_type(profile_temp, &type);
		CHECK_RETURN("inm_connection_get_type", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_get_type(profile_temp, &type);
	CHECK_RETURN("inm_connection_get_type", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_type_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Should not get the network type.
 * @scenario        Verify inm_connection_get_type by passing invalid parameter.
 */
int utc_inm_connection_get_type_n(void)
{
	int ret = INM_ERROR_NONE;
	inm_connection_type_e type;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_type(profile_inval, NULL);
		CHECK_RETURN("inm_connection_get_type", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	ret = inm_connection_get_type(profile_inval, NULL);
	CHECK_RETURN("inm_connection_get_type", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_type(profile_inval, &type);
	CHECK_RETURN("inm_connection_get_type", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_type(profile_any, NULL);
	CHECK_RETURN("inm_connection_get_type", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_inm_connection_get_network_interface_name_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the name of the network interface, e.g. eth0 and pdp0.
 * @scenario  		Invoking inm_connection_get_network_interface_name with valid parameter.
 */
int utc_inm_connection_get_network_interface_name_p(void)
{
	int ret = INM_ERROR_NONE;
	char *name = NULL;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_network_interface_name(profile_temp, &name);
		FREE_MEMORY_TC(name);
		CHECK_RETURN("inm_connection_get_network_interface_name", ret,INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_get_network_interface_name(profile_temp, &name);
	FREE_MEMORY_TC(name);
	CHECK_RETURN("inm_connection_get_network_interface_name", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_inm_connection_get_network_interface_name_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		should not get the name of the network interface.
 * @scenario  		Verify inm_connection_get_network_interface_name by passing invalid parameter.
 */
int utc_inm_connection_get_network_interface_name_n(void)
{
	int ret = INM_ERROR_NONE;
	char *name = NULL;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_network_interface_name(profile_inval, NULL);
		CHECK_RETURN("inm_connection_get_network_interface_name", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);
	assert(profile_any);

	ret = inm_connection_get_network_interface_name(profile_inval, NULL);
	CHECK_RETURN("inm_connection_get_network_interface_name", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_network_interface_name(profile_inval, &name);
	CHECK_RETURN("inm_connection_get_network_interface_name", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_network_interface_name(profile_any, NULL);
	CHECK_RETURN("inm_connection_get_network_interface_name", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_refresh_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Refreshes the profile information.
 * @scenario        Invoking inm_connection_refresh with valid parameter.
 */
int utc_inm_connection_refresh_p(void)
{
	int ret = INM_ERROR_NONE;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_refresh(profile_temp);
		CHECK_RETURN("inm_connection_refresh", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_refresh(profile_temp);
	CHECK_RETURN("inm_connection_refresh", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_refresh_n
 * @since_tizen     2.3
 * @type            Negative
 * @description     inm_connection_refresh should fail with invalid parameter.
 * @scenario        Verify inm_connection_refresh by passing invalid profile handle.
 */
int utc_inm_connection_refresh_n(void)
{
	inm_connection_h profile_inval = NULL;

	int ret = inm_connection_refresh(profile_inval);

	if (g_bFeatureAllNotSupported) {
		CHECK_RETURN("inm_connection_refresh", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_connection_refresh", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_state_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the network type and the state of the profile.
 * @scenario        Verify inm_connection_get_state with valid parameter.
 */
int utc_inm_connection_get_state_p(void)
{
	inm_connection_state_e state;
	int ret = INM_ERROR_NONE;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_state(profile_temp, &state);
		CHECK_RETURN("inm_connection_get_state", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_get_state(profile_temp, &state);
	CHECK_RETURN("inm_connection_get_state", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_state_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Should not get the state of the profile.
 * @scenario        Verify inm_connection_get_state by passing invalid parameter.
 */
int utc_inm_connection_get_state_n(void)
{
	int ret;
	inm_connection_state_e state;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_state(profile_inval, NULL);
		CHECK_RETURN("inm_connection_get_state", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	ret = inm_connection_get_state(profile_inval, NULL);
	CHECK_RETURN("inm_connection_get_state", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_state(profile_inval, &state);
	CHECK_RETURN("inm_connection_get_state", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_state(profile_any, NULL);
	CHECK_RETURN("inm_connection_get_state", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_ipv6_state_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets IPv6 state
 * @scenario        Invoking inm_connection_get_ipv6_state with valid parameter.
 */
int utc_inm_connection_get_ipv6_state_p(void)
{
	inm_connection_state_e state;
	int ret = INM_ERROR_NONE;

	inm_get_any_profile(&profile_temp);

	if(g_bFeatureAllNotSupported) {
		ret = inm_connection_get_ipv6_state(profile_temp, &state);
		CHECK_RETURN("inm_connection_get_ipv6_state", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);

	ret = inm_connection_get_ipv6_state(profile_temp, &state);
	CHECK_RETURN("inm_connection_get_ipv6_state", ret, INM_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_inm_connection_get_ipv6_state_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_connection_get_ipv6_state should be failed with invalid parameter.
 * @scenario        Verify inm_connection_get_ipv6_state by passing invalid parameter.
 */
int utc_inm_connection_get_ipv6_state_n(void)
{
	inm_connection_state_e state;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if(g_bFeatureAllNotSupported) {
		int ret = inm_connection_get_ipv6_state(profile_inval, NULL);
		CHECK_RETURN("inm_connection_get_ipv6_state", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	int ret = inm_connection_get_ipv6_state(profile_inval, NULL);
	CHECK_RETURN("inm_connection_get_ipv6_state", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_ipv6_state(profile_inval, &state);
	CHECK_RETURN("inm_connection_get_ipv6_state", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_ipv6_state(profile_any, NULL);
	CHECK_RETURN("inm_connection_get_ipv6_state", ret, INM_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase        utc_inm_connection_get_ip_config_type_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the IP config type.Should return the type of the IP config.
 * @scenario        Invoking inm_connection_get_ip_config_type with valid parameter.
 */
int utc_inm_connection_get_ip_config_type_p(void)
{
	inm_ip_config_type_e type;
	int ret = INM_ERROR_NONE;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_ip_config_type(profile_temp, INM_ADDRESS_FAMILY_IPV4, &type);
		CHECK_RETURN("inm_connection_get_ip_config_type", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_get_ip_config_type(profile_temp, INM_ADDRESS_FAMILY_IPV4, &type);
	CHECK_RETURN("inm_connection_get_ip_config_type", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_ip_config_type_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Should not return the type of the IP config.
 * @scenario        Verify inm_connection_get_ip_config_type by passing invalid parameter..
 */
int utc_inm_connection_get_ip_config_type_n(void)
{
	int ret;
	inm_ip_config_type_e type;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_ip_config_type(profile_inval, -1, NULL);
		CHECK_RETURN("inm_connection_get_ip_config_type", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	ret = inm_connection_get_ip_config_type(profile_inval, -1, NULL);
	CHECK_RETURN("inm_connection_get_ip_config_type", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_ip_config_type(profile_inval, INM_ADDRESS_FAMILY_IPV4, &type);
	CHECK_RETURN("inm_connection_get_ip_config_type", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_ip_config_type(profile_any, -1, &type);
	CHECK_RETURN("inm_connection_get_ip_config_type", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_ip_config_type(profile_any, INM_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("inm_connection_get_ip_config_type", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_ip_config_type(profile_inval, -1, &type);
	CHECK_RETURN("inm_connection_get_ip_config_type", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_ip_config_type(profile_any, -1, NULL);
	CHECK_RETURN("inm_connection_get_ip_config_type", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_ip_address_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the IP address.Shoudl return IP Address.
 * @scenario        Invoking inm_connection_get_ip_address with valid parameter.
 */
int utc_inm_connection_get_ip_address_p(void)
{
	char *ip_addr = NULL;
	int ret = INM_ERROR_NONE;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_ip_address(profile_temp, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
		FREE_MEMORY_TC(ip_addr);
		CHECK_RETURN("inm_connection_get_ip_address", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_get_ip_address(profile_temp, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY_TC(ip_addr);
	CHECK_RETURN("inm_connection_get_ip_address", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_ip_address_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Should not return IP Address.
 * @scenario        Verify inm_connection_get_ip_address by passing invalid parameter.
 */
int utc_inm_connection_get_ip_address_n(void)
{
	int ret = INM_ERROR_NONE;
	char *ip_addr = NULL;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_ip_address(profile_inval, -1, NULL);
		CHECK_RETURN("inm_connection_get_ip_address", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	ret = inm_connection_get_ip_address(profile_inval, -1, NULL);
	CHECK_RETURN("inm_connection_get_ip_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_ip_address(profile_inval, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
	CHECK_RETURN("inm_connection_get_ip_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_ip_address(profile_any, -1, &ip_addr);
	CHECK_RETURN("inm_connection_get_ip_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_ip_address(profile_any, INM_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("inm_connection_get_ip_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_ip_address(profile_inval, -1, &ip_addr);
	CHECK_RETURN("inm_connection_get_ip_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_ip_address(profile_any, -1, NULL);
	CHECK_RETURN("inm_connection_get_ip_address", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_subnet_mask_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the Subnet Mask.
 * @scenario        Invoking inm_connection_get_subnet_mask with valid parameter.
 */
int utc_inm_connection_get_subnet_mask_p(void)
{
	char *ip_addr = NULL;
	int ret = INM_ERROR_NONE;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_subnet_mask(profile_temp, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
		FREE_MEMORY_TC(ip_addr);
		CHECK_RETURN("inm_connection_get_subnet_mask", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_get_subnet_mask(profile_temp, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY_TC(ip_addr);
	CHECK_RETURN("inm_connection_get_subnet_mask", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_subnet_mask_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Should not return any subnet mask.
 * @scenario        Verify inm_connection_get_subnet_mask by passing invalid parameter.
 */
int utc_inm_connection_get_subnet_mask_n(void)
{
	int ret = INM_ERROR_NONE;
	char *ip_addr = NULL;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_subnet_mask(profile_inval, -1, NULL);
		CHECK_RETURN("inm_connection_get_subnet_mask", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	ret = inm_connection_get_subnet_mask(profile_inval, -1, NULL);
	CHECK_RETURN("inm_connection_get_subnet_mask", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_subnet_mask(profile_inval, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
	CHECK_RETURN("inm_connection_get_subnet_mask", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_subnet_mask(profile_any, -1, &ip_addr);
	CHECK_RETURN("inm_connection_get_subnet_mask", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_subnet_mask(profile_any, INM_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("inm_connection_get_subnet_mask", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_subnet_mask(profile_inval, -1, &ip_addr);
	CHECK_RETURN("inm_connection_get_subnet_mask", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_subnet_mask(profile_any, -1, NULL);
	CHECK_RETURN("inm_connection_get_subnet_mask", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_gateway_address_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the Gateway address.
 * @scenario        Invoking inm_connection_get_gateway_address with valid parameter.
 */
int utc_inm_connection_get_gateway_address_p(void)
{
	char *ip_addr = NULL;
	int ret = INM_ERROR_NONE;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_gateway_address(profile_temp, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
		FREE_MEMORY_TC(ip_addr);
		CHECK_RETURN("inm_connection_get_gateway_address", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_get_gateway_address(profile_temp, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY_TC(ip_addr);
	CHECK_RETURN("inm_connection_get_gateway_address", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_gateway_address_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_connection_get_gateway_address should fail with invalid parameter.
 * @scenario        Verify inm_connection_get_gateway_address by passing invalid parameter.
 */
int utc_inm_connection_get_gateway_address_n(void)
{
	int ret = INM_ERROR_NONE;
	char *ip_addr = NULL;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_gateway_address(profile_inval, -1, NULL);
		CHECK_RETURN("inm_connection_get_gateway_address", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	ret = inm_connection_get_gateway_address(profile_inval, -1, NULL);
	CHECK_RETURN("inm_connection_get_gateway_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_gateway_address(profile_inval, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
	CHECK_RETURN("inm_connection_get_gateway_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_gateway_address(profile_any, -1, &ip_addr);
	CHECK_RETURN("inm_connection_get_gateway_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_gateway_address(profile_any, INM_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("inm_connection_get_gateway_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_gateway_address(profile_inval, -1, &ip_addr);
	CHECK_RETURN("inm_connection_get_gateway_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_gateway_address(profile_any, -1, NULL);
	CHECK_RETURN("inm_connection_get_gateway_address", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_dhcp_server_address_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the DHCP server address.
 * @scenario        Invoking inm_connection_get_dhcp_server_address with valid parameter.
 */
int utc_inm_connection_get_dhcp_server_address_p(void)
{
	char *ip_addr = NULL;
	int ret = INM_ERROR_NONE;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_dhcp_server_address(profile_temp, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
		FREE_MEMORY_TC(ip_addr);
		CHECK_RETURN("inm_connection_get_dhcp_server_address", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_get_dhcp_server_address(profile_temp, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY_TC(ip_addr);
	CHECK_RETURN("inm_connection_get_dhcp_server_address", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_dhcp_server_address_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_connection_get_dhcp_server_address should fail with invalid parameter.
 * @scenario        Verify inm_connection_get_dhcp_server_address by passing invalid parameter.
 */
int utc_inm_connection_get_dhcp_server_address_n(void)
{
	int ret;
	char *ip_addr = NULL;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_dhcp_server_address(profile_inval, -1, NULL);
		CHECK_RETURN("inm_connection_get_dhcp_server_address", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	ret = inm_connection_get_dhcp_server_address(profile_inval, -1, NULL);
	CHECK_RETURN("inm_connection_get_dhcp_server_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dhcp_server_address(profile_inval, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
	CHECK_RETURN("inm_connection_get_dhcp_server_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dhcp_server_address(profile_any, -1, &ip_addr);
	CHECK_RETURN("inm_connection_get_dhcp_server_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dhcp_server_address(profile_any, INM_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("inm_connection_get_dhcp_server_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dhcp_server_address(profile_inval, -1, &ip_addr);
	CHECK_RETURN("inm_connection_get_dhcp_server_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dhcp_server_address(profile_any, -1, NULL);
	CHECK_RETURN("inm_connection_get_dhcp_server_address", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_dhcp_lease_duration_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the DHCP lease duration.
 * @scenario        Invoking inm_connection_get_dhcp_lease_duration with valid parameter.
 */
int utc_inm_connection_get_dhcp_lease_duration_p(void)
{
	int dhcp_lease_duration = 0;
	int ret = INM_ERROR_NONE;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_dhcp_lease_duration(profile_temp, INM_ADDRESS_FAMILY_IPV4, &dhcp_lease_duration);
		CHECK_RETURN("inm_connection_get_dhcp_lease_duration", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_get_dhcp_lease_duration(profile_temp, INM_ADDRESS_FAMILY_IPV4, &dhcp_lease_duration);
	CHECK_RETURN("inm_connection_get_dhcp_lease_duration", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_cinm_connection_get_dhcp_lease_duration_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_connection_get_dhcp_lease_duration should fail with invalid parameter.
 * @scenario        Verify inm_connection_get_dhcp_lease_duration by passing invalid parameter.
 */
int utc_inm_connection_get_dhcp_lease_duration_n(void)
{
	int ret;
	int dhcp_lease_duration = 0;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_dhcp_lease_duration(profile_inval, -1, NULL);
		CHECK_RETURN("inm_connection_get_dhcp_lease_duration", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	ret = inm_connection_get_dhcp_lease_duration(profile_inval, -1, NULL);
	CHECK_RETURN("inm_connection_get_dhcp_lease_duration", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dhcp_lease_duration(profile_inval, INM_ADDRESS_FAMILY_IPV4, &dhcp_lease_duration);
	CHECK_RETURN("inm_connection_get_dhcp_lease_duration", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dhcp_lease_duration(profile_any, -1, &dhcp_lease_duration);
	CHECK_RETURN("inm_connection_get_dhcp_lease_duration", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dhcp_lease_duration(profile_any, INM_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("inm_connection_get_dhcp_lease_duration", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dhcp_lease_duration(profile_inval, -1, &dhcp_lease_duration);
	CHECK_RETURN("inm_connection_get_dhcp_lease_duration", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dhcp_lease_duration(profile_any, -1, NULL);
	CHECK_RETURN("inm_connection_get_dhcp_lease_duration", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_dns_address_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the DNS address.
 * @scenario        Invoking inm_connection_get_dns_address with valid parameter.
 */
int utc_inm_connection_get_dns_address_p(void)
{
	char *ip_addr = NULL;
	int ret = INM_ERROR_NONE;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_dns_address(profile_temp, 1, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
		FREE_MEMORY_TC(ip_addr);
		CHECK_RETURN("inm_connection_get_dns_address", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_get_dns_address(profile_temp, 1, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY_TC(ip_addr);
	CHECK_RETURN("inm_connection_get_dns_address", ret, INM_ERROR_NONE);
	ret = inm_connection_get_dns_address(profile_temp, 2, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY_TC(ip_addr);
	CHECK_RETURN("inm_connection_get_dns_address", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_dns_address_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_connection_get_dns_address should fail with invalid parameter.
 * @scenario        Verify inm_connection_get_dns_address by passing invalid parameter.
 */
int utc_inm_connection_get_dns_address_n(void)
{
	int ret;
	char *ip_addr = NULL;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_dns_address(profile_inval, 1, -1, NULL);
		CHECK_RETURN("inm_connection_get_dns_address", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	ret = inm_connection_get_dns_address(profile_inval, 1, -1, NULL);
	CHECK_RETURN("inm_connection_get_dns_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dns_address(profile_inval, 1, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY_TC(ip_addr);
	CHECK_RETURN("inm_connection_get_dns_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dns_address(profile_any, 1, -1, &ip_addr);
	FREE_MEMORY_TC(ip_addr);
	CHECK_RETURN("inm_connection_get_dns_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dns_address(profile_any, 1, INM_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("inm_connection_get_dns_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dns_address(profile_inval, 1, -1, &ip_addr);
	FREE_MEMORY_TC(ip_addr);
	CHECK_RETURN("inm_connection_get_dns_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dns_address(profile_any, 1, -1, NULL);
	CHECK_RETURN("inm_connection_get_dns_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dns_address(profile_any, 99, INM_ADDRESS_FAMILY_IPV6, &ip_addr);
	FREE_MEMORY_TC(ip_addr);
	CHECK_RETURN("inm_connection_get_dns_address", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_proxy_type_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Sets the Proxy type.
 * @scenario        Invoking inm_connection_get_proxy_type with valid parameter.
 */
int utc_inm_connection_get_proxy_type_p(void)
{
	inm_proxy_type_e type;
	int ret = INM_ERROR_NONE;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_proxy_type(profile_temp, &type);
		CHECK_RETURN("inm_connection_get_proxy_type", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_get_proxy_type(profile_temp, &type);
	CHECK_RETURN("inm_connection_get_proxy_type", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_proxy_type_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_connection_get_proxy_type should fail with invalid parameter.
 * @scenario        Verify inm_connection_get_proxy_type by passing invalid parameter.
 */
int utc_inm_connection_get_proxy_type_n(void)
{
	int ret;
	inm_proxy_type_e type;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_proxy_type(profile_inval, NULL);
		CHECK_RETURN("inm_connection_get_proxy_type", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	ret = inm_connection_get_proxy_type(profile_inval, NULL);
	CHECK_RETURN("inm_connection_get_proxy_type", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_proxy_type(profile_inval, &type);
	CHECK_RETURN("inm_connection_get_proxy_type", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_proxy_type(profile_any, NULL);
	CHECK_RETURN("inm_connection_get_proxy_type", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_proxy_address_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the Proxy address.
 * @scenario        Invoking inm_connection_get_proxy_address with valid parameter.
 */
int utc_inm_connection_get_proxy_address_p(void)
{
	char *ip_addr = NULL;
	int ret = INM_ERROR_NONE;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_proxy_address(profile_temp, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
		FREE_MEMORY_TC(ip_addr);
		CHECK_RETURN("inm_connection_get_proxy_address", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_get_proxy_address(profile_temp, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_MEMORY_TC(ip_addr);
	CHECK_RETURN("inm_connection_get_proxy_address", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_proxy_address_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_connection_get_proxy_address should fail with invalid parameter.
 * @scenario        Verify inm_connection_get_proxy_address by passing invalid parameter.
 */
int utc_inm_connection_get_proxy_address_n(void)
{
	int ret = INM_ERROR_NONE;
	char *ip_addr = NULL;
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_proxy_address(profile_inval, -1, NULL);
		CHECK_RETURN("inm_connection_get_proxy_address", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	ret = inm_connection_get_proxy_address(profile_inval, -1, NULL);
	CHECK_RETURN("inm_connection_get_proxy_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_proxy_address(profile_inval, INM_ADDRESS_FAMILY_IPV4, &ip_addr);
	CHECK_RETURN("inm_connection_get_proxy_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_proxy_address(profile_any, -1, &ip_addr);
	CHECK_RETURN("inm_connection_get_proxy_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_proxy_address(profile_any, INM_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("inm_connection_get_proxy_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_proxy_address(profile_inval, -1, &ip_addr);
	CHECK_RETURN("inm_connection_get_proxy_address", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_proxy_address(profile_any, -1, NULL);
	CHECK_RETURN("inm_connection_get_proxy_address", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_dns_config_type_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets DNS configuration type
 * @scenario        Invoking inm_connection_get_dns_config_type with valid parameter.
 */
int utc_inm_connection_get_dns_config_type_p(void)
{
	inm_dns_config_type_e config_type;
	int ret = inm_get_current_connection(g_hInm, &profile_temp);
	CHECK_RETURN("inm_get_current_connection", ret, INM_ERROR_NONE);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_get_dns_config_type(profile_temp, INM_ADDRESS_FAMILY_IPV4, &config_type);
		CHECK_RETURN("inm_connection_get_dns_config_type", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);

	ret = inm_connection_get_dns_config_type(profile_temp, INM_ADDRESS_FAMILY_IPV4, &config_type);
	CHECK_RETURN("inm_connection_get_dns_config_type", ret, INM_ERROR_NONE);
	ret = inm_connection_get_dns_config_type(profile_temp, INM_ADDRESS_FAMILY_IPV6, &config_type);
	CHECK_RETURN("inm_connection_get_dns_config_type", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_dns_config_type_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_connection_get_dns_config_type should be failed with invalid parameter.
 * @scenario        Verify inm_connection_get_dns_config_type by passing invalid parameter.
 */
int utc_inm_connection_get_dns_config_type_n(void)
{
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;
	inm_dns_config_type_e config_type;

	if(g_bFeatureAllNotSupported) {
		int ret = inm_connection_get_dns_config_type(profile_inval, INM_ADDRESS_FAMILY_IPV4, NULL);
		CHECK_RETURN("inm_connection_get_dns_config_type", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	int ret = inm_connection_get_dns_config_type(profile_inval, INM_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("inm_connection_get_dns_config_type", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dns_config_type(profile_inval, INM_ADDRESS_FAMILY_IPV6, &config_type);
	CHECK_RETURN("inm_connection_get_dns_config_type", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_dns_config_type(profile_any, INM_ADDRESS_FAMILY_IPV6, NULL);
	CHECK_RETURN("inm_connection_get_dns_config_type", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_prefix_length_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets prefix length
 * @scenario        Invoking inm_connection_get_prefix_length with valid parameter.
 */
int utc_inm_connection_get_prefix_length_p(void)
{
	int length;

	if (g_bFeatureAllNotSupported) {
		int ret = inm_connection_get_prefix_length(profile_temp, INM_ADDRESS_FAMILY_IPV4, &length);
		CHECK_RETURN("inm_connection_get_prefix_length", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int ret = inm_get_current_connection(g_hInm, &profile_temp);
	CHECK_RETURN("inm_get_current_connection", ret, INM_ERROR_NONE);
	ret = inm_connection_get_prefix_length(profile_temp, INM_ADDRESS_FAMILY_IPV6, &length);
	CHECK_RETURN("inm_connection_get_prefix_length", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_prefix_length_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_connection_get_prefix_length should be failed with invalid parameter.
 * @scenario        Verify prefix_length by passing invalid parameter.
 */
int utc_inm_connection_get_prefix_length_n(void)
{
	inm_connection_h profile_inval = NULL;
	inm_connection_h profile_any = NULL;
	int length;

	if (g_bFeatureAllNotSupported) {
		int ret = inm_connection_get_prefix_length(profile_inval, INM_ADDRESS_FAMILY_IPV4, &length);
		CHECK_RETURN("inm_connection_get_prefix_length", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_any);

	int ret = inm_connection_get_prefix_length(profile_inval, INM_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("inm_connection_get_prefix_length", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_prefix_length(profile_inval, INM_ADDRESS_FAMILY_IPV4, &length);
	CHECK_RETURN("inm_connection_get_prefix_length", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_prefix_length(profile_any, INM_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("inm_connection_get_prefix_length", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase        utc_inm_connection_set_state_changed_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_connection_set_state_changed_cb should fail with invalid parameter.
 * @scenario        Verify inm_connection_set_state_changed_cb by passing callback and user_data as NULL.
 */
int utc_inm_connection_set_state_changed_cb_n(void)
{
	inm_connection_h profile_inval = NULL;
	int ret = INM_ERROR_NONE;

	inm_get_any_profile(&profile_temp);

	if (g_bFeatureAllNotSupported) {
		ret = inm_connection_set_state_changed_cb(profile_inval, NULL, NULL);
		CHECK_RETURN("inm_connection_set_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = inm_connection_set_state_changed_cb(profile_inval, NULL, NULL);
	CHECK_RETURN("inm_connection_set_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_set_state_changed_cb(profile_inval, inm_connection_state_changed_callback, NULL);
	CHECK_RETURN("inm_connection_set_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_set_state_changed_cb(profile_temp, NULL, NULL);
	CHECK_RETURN("inm_connection_set_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase        utc_inm_connection_unset_state_changed_cb_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     inm_connection_unset_state_changed_cb should fail with invalid parameter.
 * @scenario        Verify inm_connection_unset_state_changed_cb by passing invalid profile handle.
 */
int utc_inm_connection_unset_state_changed_cb_n(void)
{
	inm_connection_h profile_inval = NULL;

	int ret = inm_connection_unset_state_changed_cb(profile_inval);

	if (g_bFeatureAllNotSupported) {
		CHECK_RETURN("inm_connection_unset_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_connection_unset_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/*****************************************
 * CAPI_NETWORK_INM_WIFI_MODULE
 *****************************************/


/**
 * @testcase		utc_inm_wifi_set_scan_state_changed_cb_n
 * @since_tizen 	5.0
 * @type			Negative
 * @description 	Verify inm_wifi_set_scan_state_changed_cb by passing invalid parameters
 * @scenario		Pass invalid parameters and ensure scan state is not notofied through callback.
 *					Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_set_scan_state_changed_cb_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_set_scan_state_changed_cb(NULL, NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_set_scan_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_set_scan_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

    return 0;
}

/**
 * @testcase		utc_inm_wifi_unset_scan_state_changed_cb_n
 * @since_tizen 	5.0
 * @type			Negative
 * @description 	Verify inm_wifi_unset_scan_state_changed_cb by changing the state
 * @scenario		Unset scan state changed callback and ensure scan state is not notofied through callback.
 *					Ensure return value should be INM_ERROR_INVALID_OPERATION.
 */
int utc_inm_wifi_unset_scan_state_changed_cb_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_unset_scan_state_changed_cb(NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_unset_scan_state_changed_cb", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_unset_scan_state_changed_cb", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_get_scan_state_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the scan state.
 * @scenario        Get Wi-Fi scan state. Ensure no error.
 */
int utc_inm_wifi_get_scan_state_p(void)
{
	inm_wifi_scan_state_e scan_state;
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_get_scan_state(g_hInm, &scan_state);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_get_scan_state", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_get_scan_state", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_get_scan_state_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_get_scan_state by passing invalid parameters(scan_state).
 * @scenario        Pass invalid parameter and ensure wifi scan state is not returned.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_get_scan_state_n(void)
{
    int ret = INM_ERROR_NONE;

	ret = inm_wifi_get_scan_state(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_get_scan_state", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_get_scan_state", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_get_connected_ap_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the handle of the connected access point.
 * @scenario        When Wi-Fi is connected, connected APs will be returned.
 *                  When Wi-Fi is not connected, Initate Scan and ensure no error.
 *                  When AP is found, initiate connection and get the connected AP.
 */
int utc_inm_wifi_get_connected_ap_p(void)
{
	inm_connection_h hAP = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		ret = inm_wifi_get_connected_ap(g_hInm, &hAP);
		CHECK_RETURN("inm_wifi_get_connected_ap", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	//ret = wifi_manager_pre_connect();
	//CHECK_RETURN("wifi_manager_pre_connect", ret, INM_ERROR_NONE);

	ret = inm_wifi_get_connected_ap(g_hInm, &hAP);
	CHECK_RETURN("inm_wifi_get_connected_ap", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_wifi_get_connected_ap_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_get_connected_ap by passing invalid parameter.
 * @scenario        Pass NULL parameter and ensure INM_ERROR_INVALID_PARAMETER is reported.
 */
int utc_inm_wifi_get_connected_ap_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_get_connected_ap(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_get_connected_ap", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_get_connected_ap", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_foreach_found_ap_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the result of the scan.
 * @scenario        Get all the Access Points found during scan. Ensure no error.
 */
int utc_inm_wifi_foreach_found_ap_p(void)
{
    int ret = INM_ERROR_NONE;

	ret = inm_wifi_foreach_found_ap(g_hInm, inm_foreach_found_ap_callback, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_foreach_found_ap", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_foreach_found_ap", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_foreach_found_ap_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_foreach_found_ap by passing invalid parameters
 * @scenario        Pass invalid parameters and ensure WiFi Access points are not returned.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_foreach_found_ap_n(void)
{
    int ret = INM_ERROR_NONE;

	ret = inm_wifi_foreach_found_ap(g_hInm, NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_foreach_found_ap", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_foreach_found_ap", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/*****************************************
 * CAPI_NETWORK_INM_WIFI_AP_MODULE
 *****************************************/


 /**
  * @testcase        utc_inm_wifi_ap_get_essid_p
  * @since_tizen     5.0
  * @type            Positive
  * @description     Gets ESSID (Extended Service Set Identifier).
  * @scenario        Check AP validity and get essid from AP infomation. Check the status and
  *                  delete essid.
  */
 int utc_inm_wifi_ap_get_essid_p(void)
 {
	 char *essid = NULL;
	 int ret = INM_ERROR_NONE;

	 ret = inm_wifi_ap_get_essid(g_hConnection, &essid);
	 FREE_MEMORY_TC(essid);

	 if (!g_bFeatureWifi || !g_bFeatureInm) {
		 CHECK_RETURN("inm_wifi_ap_get_essid", ret, INM_ERROR_NOT_SUPPORTED);
	 } else {
		 CHECK_RETURN("inm_wifi_ap_get_essid", ret, INM_ERROR_NONE);
	 }

	 return 0;
 }

 /**
  * @testcase        utc_inm_wifi_ap_get_essid_n
  * @since_tizen     5.0
  * @type            Negative
  * @description     Verify inm_wifi_ap_get_essid by passing invalid parameters(ap,essid)
  * @scenario        Pass invalid AP information. Proper essid should not be returned.
  *                  Return value should be INM_ERROR_INVALID_PARAMETER.
  */
 int utc_inm_wifi_ap_get_essid_n(void)
 {
	 int ret = INM_ERROR_NONE;

	 ret = inm_wifi_ap_get_essid(NULL, NULL);

	 if (!g_bFeatureWifi || !g_bFeatureInm) {
		 CHECK_RETURN("inm_wifi_ap_get_essid", ret, INM_ERROR_NOT_SUPPORTED);
	 } else {
		 CHECK_RETURN("inm_wifi_ap_get_essid", ret, INM_ERROR_INVALID_PARAMETER);
	 }

	 return 0;
 }

 /**
  * @testcase        utc_inm_wifi_ap_get_raw_ssid_p
  * @since_tizen     5.0
  * @type            Positive
  * @description     Gets raw SSID (Service Set Identifier).
  * @scenario        Check AP validity and get raw ssid from AP infomation. Check the status and
  *                  delete raw ssid.
  */
 int utc_inm_wifi_ap_get_raw_ssid_p(void)
 {
	 char *raw_ssid = NULL;
	 int raw_ssid_len;
	 int ret = INM_ERROR_NONE;

	 ret = inm_wifi_ap_get_raw_ssid(g_hConnection, &raw_ssid, &raw_ssid_len);
	 FREE_MEMORY_TC(raw_ssid);

	 if (!g_bFeatureWifi || !g_bFeatureInm) {
		 CHECK_RETURN("inm_wifi_ap_get_raw_ssid", ret, INM_ERROR_NOT_SUPPORTED);
	 } else {
		 CHECK_RETURN("inm_wifi_ap_get_raw_ssid", ret, INM_ERROR_NONE);
	 }

	 return 0;
 }

 /**
  * @testcase        utc_inm_wifi_ap_get_raw_ssid_n
  * @since_tizen     5.0
  * @type            Negative
  * @description     Verify inm_wifi_ap_get_raw_ssid by passing invalid parameters(ap,raw_ssid,size)
  * @scenario        Pass invalid AP information. Proper raw ssid should not be returned.
  *                  Return value should be INM_ERROR_INVALID_PARAMETER.
  */
 int utc_inm_wifi_ap_get_raw_ssid_n(void)
 {
	 int ret = INM_ERROR_NONE;

	 ret = inm_wifi_ap_get_raw_ssid(NULL, NULL, NULL);

	 if (!g_bFeatureWifi || !g_bFeatureInm) {
		 CHECK_RETURN("inm_wifi_ap_get_raw_ssid", ret, INM_ERROR_NOT_SUPPORTED);
	 } else {
		 CHECK_RETURN("inm_wifi_ap_get_raw_ssid", ret, INM_ERROR_INVALID_PARAMETER);
	 }

	 return 0;
 }

 /**
 * @testcase        utc_inm_wifi_ap_get_bssid_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets BSSID (Basic Service Set Identifier).
 * @scenario        Check AP validity and get bssid from AP infomation. Check the return value
 *                  and free the bssid
 */
int utc_inm_wifi_ap_get_bssid_p(void)
{
	char *bssid = NULL;
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_bssid(g_hConnection, &bssid);
	FREE_MEMORY_TC(bssid);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
        CHECK_RETURN("inm_wifi_ap_get_bssid", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_bssid", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_bssid_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_bssid by passing invalid parameters(ap, bssid)
 * @scenario        Pass invalid AP info make sure proper bssid is not returned
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_ap_get_bssid_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_bssid(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_bssid", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_bssid", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_rssi_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the RSSI.
 * @scenario        Check AP validity and get RSSI from AP infomation. Check the return value.
 */
int utc_inm_wifi_ap_get_rssi_p(void)
{
	int rssi = 0;
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_rssi(g_hConnection, &rssi);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_rssi", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_rssi", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_rssi_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_rssi by passing invalid parameters(ap, rssi).
 * @scenario        Pass invalid AP information. Proper RSSI is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_ap_get_rssi_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_rssi(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_rssi", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_rssi", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_rssi_level_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the RSSI level.
 * @scenario        Check AP validity and get RSSI level from AP infomation. Check the return value.
 */
int utc_inm_wifi_ap_get_rssi_level_p(void)
{
	int ret = INM_ERROR_NONE;
	inm_wifi_rssi_level_e rssi_level;

	ret = inm_wifi_ap_get_rssi_level(g_hConnection, &rssi_level);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_rssi_level", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_rssi_level", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_rssi_level_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_rssi_level by passing invalid parameters(ap, rssi level).
 * @scenario        Pass invalid AP information. Proper RSSI level is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_ap_get_rssi_level_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_rssi_level(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_rssi_level", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_rssi_level", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/**
 * @testcase        utc_inm_wifi_ap_get_frequency_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the frequency band (MHz).
 * @scenario        Check AP validity and get frequesncy band from AP infomation.
 *                  Check the return value.
 */
int utc_inm_wifi_ap_get_frequency_p(void)
{
	int frequency = 0;
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_frequency(g_hConnection, &frequency);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_frequency", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_frequency", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_frequency_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_frequency by passing invalid parameters(ap,frequency).
 * @scenario        Pass invalid AP info make sure proper frequency band is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_ap_get_frequency_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_frequency(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_frequency", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_frequency", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_max_speed_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the max speed (Mbps)
 * @scenario        Check AP validity and get max speed from AP infomation. Ensure no error.
 */
int utc_inm_wifi_ap_get_max_speed_p(void)
{
	int speed = 0;
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_max_speed(g_hConnection, &speed);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_max_speed", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_max_speed", ret, INM_ERROR_NONE);
	}

    return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_max_speed_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_max_speed by passing invalid parameters(ap,max_speed).
 * @scenario        Pass invalid AP info make sure proper speed is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_ap_get_max_speed_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_max_speed(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_max_speed", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_max_speed", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_is_favorite_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Checks whether the access point is favorite or not.
 * @scenario        Check AP validity and get favourite status of the AP. Ensure no error.
 */
int utc_inm_wifi_ap_is_favorite_p(void)
{
	bool favorite = false;
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_is_favorite(g_hConnection, &favorite);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_is_favorite", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_is_favorite", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_is_favorite_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_is_favorite by passing invalid parameters(ap,favorite).
 * @scenario        Pass invalid AP info make sure proper favourite status is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_ap_is_favorite_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_is_favorite(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_is_favorite", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_is_favorite", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_is_passpoint_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Checks whether the access point is passpoint or not.
 * @scenario        Check AP validity and get whether passpoint feature is
 *                  supported by the AP
 */
int utc_inm_wifi_ap_is_passpoint_p(void)
{
	bool passpoint = false;
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_is_passpoint(g_hConnection, &passpoint);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_is_passpoint", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_is_passpoint", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_is_passpoint_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_is_passpoint by passing invalid parameters(ap,passpoint).
 * @scenario        Pass invalid AP info make sure passpoint support status is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_ap_is_passpoint_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_is_passpoint(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_is_passpoint", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_is_passpoint", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/* Security operations. */

/**
 * @testcase        utc_inm_wifi_ap_get_security_type_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the Wi-Fi security mode.
 * @scenario        Get security mechanism used for the conneciton. Ensure no error.
 */
int utc_inm_wifi_ap_get_security_type_p(void)
{
	inm_wifi_security_type_e type;
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_security_type(g_hConnection, &type);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_security_type", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_security_type", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_security_type_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_security_type by passing invalid parameters(ap, security_type).
 * @scenario        Pass invalid AP info and other parameters to  ensure security type is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_ap_get_security_type_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_security_type(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_security_type", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_security_type", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_encryption_type_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the Wi-Fi encryption type.
 * @scenario        Get the security encryption type from AP info. Ensure no error.
 */
int utc_inm_wifi_ap_get_encryption_type_p(void)
{
	inm_wifi_encryption_type_e type;
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_encryption_type(g_hConnection, &type);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_encryption_type", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_encryption_type", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_encryption_type_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_encryption_type by passing invalid parameters(ap, encryption_type).
 * @scenario        Pass invalid AP info and other parameters to  ensure WiFi encryption type is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_ap_get_encryption_type_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_encryption_type(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_encryption_type", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_encryption_type", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_is_passphrase_required_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Checks whether the passphrase is required or not.
 * @scenario        Check whether passphrase is required for encryption. Ensure no error.
 */
int utc_inm_wifi_ap_is_passphrase_required_p(void)
{
	bool required;
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_is_passphrase_required(g_hConnection, &required);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_is_passphrase_required", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_is_passphrase_required", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_is_passphrase_required_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_is_passphrase_required by passing invalid parameters(ap,required).
 * @scenario        Pass invalid AP info and other parameters to  ensure pass phrase info is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_ap_is_passphrase_required_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_is_passphrase_required(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_is_passphrase_required", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_is_passphrase_required", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_is_wps_supported_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Checks whether the WPS(Wi-Fi Protected Setup) is supported or not.
 * @scenario        Check whether WPS is supported.
 */
int utc_inm_wifi_ap_is_wps_supported_p(void)
{
	bool supported;
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_is_wps_supported(g_hConnection, &supported);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_is_wps_supported", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_is_wps_supported", ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_is_wps_supported_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_is_wps_supported by passing invalid parameters(ap, supported).
 * @scenario        Pass invalid AP info and other parameters to  ensure WPS support is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_ap_is_wps_supported_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_is_wps_supported(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_is_wps_supported", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_is_wps_supported", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_eap_passphrase_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Get EAP passphrase.
 * @scenario        Get EPA passphrase from AP info. Ensure no error.
 */
#if 0
int utc_inm_wifi_ap_get_eap_passphrase_p(void)
{
	char *user_name = NULL;
	bool is_password_set;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = inm_wifi_ap_get_security_type(g_hConnection, INM_WIFI_SECURITY_TYPE_EAP);
		CHECK_RETURN("inm_wifi_ap_get_security_type", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_wifi_ap_get_security_type(g_hConnection, INM_WIFI_SECURITY_TYPE_EAP);
	CHECK_RETURN("inm_wifi_ap_get_security_type", ret, INM_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_passphrase(g_hConnection, WIFI_EAP_USERNAME, WIFI_EAP_PASSPHRASE);
	CHECK_RETURN("wifi_manager_ap_set_eap_passphrase", ret, INM_ERROR_NONE);

	ret = inm_wifi_ap_get_eap_passphrase(g_hConnection, &user_name, &is_password_set);
	FREE_MEMORY(user_name);
	CHECK_RETURN("inm_wifi_ap_get_eap_passphrase", ret, INM_ERROR_NONE);

	return 0;
}
#endif

/**
 * @testcase        utc_inm_wifi_ap_get_eap_passphrase_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_eap_passphrase by passing invalid parameters.
 * @scenario        Pass invalid AP info and other parameters to  ensure EAP passphrase is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
#if 0
int utc_inm_wifi_ap_get_eap_passphrase_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_eap_passphrase(NULL, NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("inm_wifi_ap_get_eap_passphrase", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_eap_passphrase", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
#endif

/**
 * @testcase        utc_inm_wifi_ap_get_eap_ca_cert_file_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the CA Certificate of EAP.
 * @scenario        Get EAP certificate file name. Ensure no error.
 */
#if 0
int utc_inm_wifi_ap_get_eap_ca_cert_file_p(void)
{
	char *cert_file = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = inm_wifi_ap_get_eap_ca_cert_file(g_hConnection, &cert_file);
		CHECK_RETURN("inm_wifi_ap_get_eap_ca_cert_file", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_wifi_ap_get_security_type(g_hConnection, INM_WIFI_SECURITY_TYPE_EAP);
	CHECK_RETURN("inm_wifi_ap_get_security_type", ret, INM_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_ca_cert_file(g_hConnection, WIFI_EAP_CA_CERT);
	CHECK_RETURN("wifi_manager_ap_set_eap_ca_cert_file", ret, INM_ERROR_NONE);

	ret = inm_wifi_ap_get_eap_ca_cert_file(g_hConnection, &cert_file);
	FREE_MEMORY(cert_file);
	CHECK_RETURN("inm_wifi_ap_get_eap_ca_cert_file", ret, INM_ERROR_NONE);

	return 0;
}
#endif

/**
 * @testcase        utc_inm_wifi_ap_get_eap_ca_cert_file_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_eap_ca_cert_file by passing invalid parameters.
 * @scenario        Pass invalid AP info and other parameters to ensure EAP certificate file name is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
#if 0
int utc_inm_wifi_ap_get_eap_ca_cert_file_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_eap_ca_cert_file(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("inm_wifi_ap_get_eap_ca_cert_file", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_eap_ca_cert_file", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
#endif

/**
 * @testcase        utc_inm_wifi_ap_get_eap_client_cert_file_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the Client Certificate of EAP.
 * @scenario        Get EAP certificate filename from AP info. Ensure no error.
 */
#if 0
int utc_inm_wifi_ap_get_eap_client_cert_file_p(void)
{
	char *cert_file = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = inm_wifi_ap_get_eap_client_cert_file(g_hConnection, &cert_file);
		CHECK_RETURN("inm_wifi_ap_get_eap_client_cert_file", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hConnection, INM_WIFI_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, INM_ERROR_NONE);

	ret = inm_wifi_ap_get_eap_client_cert_file(g_hConnection, &cert_file);
	FREE_MEMORY(cert_file);
	CHECK_RETURN("inm_wifi_ap_get_eap_client_cert_file", ret, INM_ERROR_NONE);

	return 0;
}
#endif

/**
 * @testcase        utc_inm_wifi_ap_get_eap_client_cert_file_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_eap_client_cert_file	by passing invalid parameter(ap, file).
 * @scenario        Pass invalid AP info and other parameters to ensure EAP certificate file name is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
#if 0
int utc_inm_wifi_ap_get_eap_client_cert_file_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_eap_client_cert_file(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("inm_wifi_ap_get_eap_client_cert_file", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_eap_client_cert_file", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
#endif

/**
 * @testcase        utc_inm_wifi_ap_get_eap_private_key_file_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the private key file of EAP.
 * @scenario        Get EAP private key file name. Ensure no error.
 */
#if 0
int utc_inm_wifi_ap_get_eap_private_key_file_p(void)
{
	char *key_file = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = inm_wifi_ap_get_eap_private_key_file(g_hConnection, &key_file);
		CHECK_RETURN("inm_wifi_ap_get_eap_private_key_file", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_manager_ap_set_security_type(g_hConnection, INM_WIFI_SECURITY_TYPE_EAP);
	CHECK_RETURN("wifi_manager_ap_set_security_type", ret, INM_ERROR_NONE);

	ret = inm_wifi_ap_get_eap_private_key_file(g_hConnection, &key_file);
	FREE_MEMORY(key_file);
	CHECK_RETURN("inm_wifi_ap_get_eap_private_key_file", ret, INM_ERROR_NONE);

	return 0;
}
#endif

/**
 * @testcase        utc_inm_wifi_ap_get_eap_private_key_file_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_eap_private_key_file by passing invalid parameters(ap, file).
 * @scenario        Pass invalid AP info and other parameters to ensure EAP private key file name is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
#if 0
int utc_inm_wifi_ap_get_eap_private_key_file_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_eap_private_key_file(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("inm_wifi_ap_get_eap_private_key_file", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_eap_private_key_file", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
#endif

/**
 * @testcase        utc_inm_wifi_ap_get_eap_type_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets the EAP type of Wi-Fi.
 * @scenario        Get EAP type from AP info. Ensure no error.
 */
#if 0
int utc_inm_wifi_ap_get_eap_type_p(void)
{
	wifi_manager_eap_type_e type;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = inm_wifi_ap_get_eap_type(g_hConnection, &type);
		CHECK_RETURN("inm_wifi_ap_get_eap_type", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_wifi_ap_get_security_type(g_hConnection, INM_WIFI_SECURITY_TYPE_EAP);
	CHECK_RETURN("inm_wifi_ap_get_security_type", ret, INM_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_type(g_hConnection, INM_EAP_TYPE_PEAP);
	CHECK_RETURN("wifi_manager_ap_set_eap_type", ret, INM_ERROR_NONE);

	ret = inm_wifi_ap_get_eap_type(g_hConnection, &type);
    CHECK_RETURN("inm_wifi_ap_get_eap_type", ret, INM_ERROR_NONE);

    return 0;
}
#endif

/**
 * @testcase        utc_inm_wifi_ap_get_eap_type_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_eap_type by passing invalid parameters(ap, EAP_type).
 * @scenario        Pass invalid AP info and other parameters to ensure EAP type is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
#if 0
int utc_inm_wifi_ap_get_eap_type_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_eap_type(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("inm_wifi_ap_get_eap_type", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_eap_type", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
#endif

/**
 * @testcase        utc_inm_wifi_ap_get_eap_auth_type_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Get the EAP authentication type of Wi-Fi.
 * @scenario        Get EAP authentication type. Ensure no error.
 */
#if 0
int utc_inm_wifi_ap_get_eap_auth_type_p(void)
{
	wifi_manager_eap_auth_type_e type;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureWifi) {
		ret = wifi_manager_ap_set_eap_type(g_hConnection, INM_WIFI_EAP_TYPE_PEAP);
		CHECK_RETURN("wifi_manager_ap_set_eap_type", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_wifi_ap_get_security_type(g_hConnection, INM_WIFI_SECURITY_TYPE_EAP);
	CHECK_RETURN("inm_wifi_ap_get_security_type", ret, INM_ERROR_NONE);

	ret = wifi_manager_ap_set_eap_auth_type(g_hConnection, INM_WIFI_EAP_AUTH_TYPE_MD5);
	CHECK_RETURN("wifi_manager_ap_set_eap_auth_type", ret, INM_ERROR_NONE);

	ret = inm_wifi_ap_get_eap_auth_type(g_hConnection, &type);
	CHECK_RETURN("inm_wifi_ap_get_eap_auth_type", ret, INM_ERROR_NONE);

	return 0;
}
#endif

/**
 * @testcase        utc_inm_wifi_ap_get_eap_auth_type_n
 * @since_tizen 	5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_eap_auth_type by passing invalid parameters.
 * @scenario        Pass invalid AP info and other parameters to ensure EAP authentication type is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
#if 0
int utc_inm_wifi_ap_get_eap_auth_type_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_eap_auth_type(NULL, NULL);

	if (!g_bFeatureWifi) {
		CHECK_RETURN("inm_wifi_ap_get_eap_auth_type", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_eap_auth_type", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
#endif

/**
 * @testcase        utc_inm_wifi_ap_get_disconnect_reason_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Get the disconnect reason of Wi-Fi.
 * @scenario        Get disconnect reason. Ensure no error.
 */
int utc_inm_wifi_ap_get_disconnect_reason_p(void)
{
	inm_wifi_disconnect_reason_e disconnect_reason;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		ret = inm_wifi_ap_get_disconnect_reason(g_hConnection, &disconnect_reason);
		CHECK_RETURN("inm_wifi_ap_get_disconnect_reason", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_wifi_ap_get_disconnect_reason(g_hConnection, &disconnect_reason);
	CHECK_RETURN("inm_wifi_ap_get_disconnect_reason", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_disconnect_reason_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     Verify inm_wifi_ap_get_disconnect_reason by passing invalid parameters.
 * @scenario        Pass invalid AP info and other parameters to ensure disconnect reason is not returned.
 *                  Return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_wifi_ap_get_disconnect_reason_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_wifi_ap_get_disconnect_reason(NULL, NULL);

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		CHECK_RETURN("inm_wifi_ap_get_disconnect_reason", ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("inm_wifi_ap_get_disconnect_reason", ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_assoc_status_code_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Get the association status code from supplicant
 * @scenario        Invoke inm_wifi_ap_get_assoc_status_code() with valid parameter
 **/
int utc_inm_wifi_ap_get_assoc_status_code_p(void)
{
	int ret;
	inm_wifi_assoc_status_code_e status_code;

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		ret = inm_wifi_ap_get_assoc_status_code(g_hConnection, &status_code);
		assert_eq(ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		ret = inm_wifi_ap_get_assoc_status_code(g_hConnection, &status_code);
		assert_eq(ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_get_assoc_status_code_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     wifi_mamager_ap_get_assoc_status_code() should be failed.
 * @scenario        Invoke inm_wifi_ap_get_assoc_status_code() with invalid parameter
 **/
int utc_inm_wifi_ap_get_assoc_status_code_n(void)
{
	int ret;
	inm_wifi_assoc_status_code_e status_code;

	if (!g_bFeatureWifi || !g_bFeatureInm) {
		ret = inm_wifi_ap_get_assoc_status_code(NULL, NULL);
		assert_eq(ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		ret = inm_wifi_ap_get_assoc_status_code(NULL, &status_code);
		assert_eq(ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_wifi_ap_get_assoc_status_code(g_hConnection, NULL);
		assert_eq(ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_wifi_ap_get_assoc_status_code(NULL, NULL);
		assert_eq(ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_foreach_vsie_p
 * @since_tizen     5.0
 * @type            Positive
 * @description     Gets vsie from AP
 * @scenario        Invoking inm_wifi_ap_foreach_vsie_callback with valid parameter.
 */
int utc_inm_wifi_ap_foreach_vsie_p(void)
{
	if (!g_bFeatureWifi || !g_bFeatureInm) {
		int ret = inm_wifi_ap_foreach_vsie(g_hConnection,
				inm_wifi_ap_foreach_vsie_callback, NULL);
		assert_eq(ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		int ret = inm_wifi_ap_foreach_vsie(g_hConnection,
				inm_wifi_ap_foreach_vsie_callback, NULL);
		assert_eq(ret, INM_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase        utc_inm_wifi_ap_foreach_vsie_n
 * @since_tizen     5.0
 * @type            Negative
 * @description     wifi_manager_ap_foreach_ipv6_address should be failed with invalid parameter.
 * @scenario        Verify IPv6 address by passing invalid parameter.
 **/
int utc_inm_wifi_ap_foreach_vsie_n(void)
{
	if (!g_bFeatureWifi || !g_bFeatureInm) {
		int ret = inm_wifi_ap_foreach_vsie(NULL,
				inm_wifi_ap_foreach_vsie_callback, NULL);
		assert_eq(ret, INM_ERROR_NOT_SUPPORTED);
	} else {
		int ret = inm_wifi_ap_foreach_vsie(NULL,
				inm_wifi_ap_foreach_vsie_callback, NULL);
		assert_eq(ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_wifi_ap_foreach_vsie(g_hConnection, NULL, NULL);
		assert_eq(ret, INM_ERROR_INVALID_PARAMETER);
		ret = inm_wifi_ap_foreach_vsie(NULL, NULL, NULL);
		assert_eq(ret, INM_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase        utc_inm_inm_foreach_link_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Gets the link information.
 * @scenario        Get all the network interface information. Ensure no error.
 */
int utc_inm_inm_foreach_link_p(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_foreach_link(g_hInm, inm_foreach_link_callback, NULL);
	if (!g_bFeatureInm)
		CHECK_RETURN("inm_foreach_link", ret, INM_ERROR_NOT_SUPPORTED);
	else
		CHECK_RETURN("inm_foreach_link", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_inm_foreach_link_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_inm_foreach_link by passing invalid parameters
 * @scenario        Pass invalid parameters and ensure network interface information are not returned.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_inm_foreach_link_n(void)
{
	int ret = INM_ERROR_NONE;

	ret = inm_foreach_link(g_hInm, NULL, NULL);

	if (!g_bFeatureInm)
		CHECK_RETURN("inm_foreach_link", ret, INM_ERROR_NOT_SUPPORTED);
	else
		CHECK_RETURN("inm_foreach_link", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_link_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Gets the link from connection.
 * @scenario        Invoking inm_connection_get_link with valid parameter.
 */
int utc_inm_connection_get_link_p(void)
{
	inm_connection_h profile_h = NULL;
	inm_link_h link = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_connection_get_link(profile_h, &link);
		CHECK_RETURN("inm_connection_get_link", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_get_current_link(&link);
	CHECK_RETURN("inm_connection_get_link", ret, INM_ERROR_NONE);

	ret = inm_link_destroy(link);
	PRINT_RETURN("inm_link_destroy", ret);

	return 0;
}

/**
 * @testcase        utc_inm_connection_get_link_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     inm_connection_get_link should fail with invalid parameter.
 * @scenario        Verify inm_connection_get_link by passing invalid parameter.
 */
int utc_inm_connection_get_link_n(void)
{
	inm_connection_h profile_h = NULL;
	inm_link_h link = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_connection_get_link(profile_h, &link);
		CHECK_RETURN("inm_connection_get_link", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	inm_get_any_profile(&profile_h);

	ret = inm_connection_get_link(NULL, NULL);
	CHECK_RETURN("inm_connection_get_link", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_link(profile_h, NULL);
	CHECK_RETURN("inm_connection_get_link", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_connection_get_link(NULL, &link);
	CHECK_RETURN("inm_connection_get_link", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_refresh_links_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Refreshes the link information.
 * @scenario        Refreshes all the network interface information. Ensure no error.
 */
int utc_inm_refresh_links_p(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_refresh_links(g_hInm);
		CHECK_RETURN("inm_refresh_links", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_refresh_links(g_hInm);
	CHECK_RETURN("inm_refresh_links", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_refresh_links_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_refresh_links by passing invalid parameters
 * @scenario        Pass invalid parameters and inm_refresh_links() should be failed..
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_refresh_links_n(void)
{
    int ret = INM_ERROR_NONE;

	ret = inm_refresh_links(NULL);

	if (!g_bFeatureInm)
		CHECK_RETURN("inm_refresh_links", ret, INM_ERROR_NOT_SUPPORTED);
	else
		CHECK_RETURN("inm_refresh_links", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

