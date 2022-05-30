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
#include "assert.h"
#include <telephony.h>
#include <system_info.h>

//& set: Telephony

static bool g_telephony_network_supported = true;
static telephony_handle_list_s handle_list;
static telephony_h telephony_handle = NULL;

/**
 * @function		utc_telephony_network_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_telephony_network_startup(void)
{
	system_info_get_platform_bool("tizen.org/feature/network.telephony", &g_telephony_network_supported);
	if (g_telephony_network_supported) {
		if (telephony_init(&handle_list) == TELEPHONY_ERROR_NONE && handle_list.count > 0)
			telephony_handle = handle_list.handle[0];
	}
}

/**
 * @function		utc_telephony_network_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_telephony_network_cleanup(void)
{
	if (g_telephony_network_supported) {
		telephony_deinit(&handle_list);
		telephony_handle = NULL;
	}
}

/**
 * @testcase		utc_telephony_telephony_network_get_lac_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the LAC of the current network.
 */
int utc_telephony_telephony_network_get_lac_p(void)
{
	int lac, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_lac(telephony_handle, &lac);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_lac(telephony_handle, &lac);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_lac_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the LAC of the current network. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_lac_n1(void)
{
	int lac, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_lac(NULL, &lac);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_lac(NULL, &lac);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_lac_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the LAC of the current network. (NULL 'lac' param)
 */
int utc_telephony_telephony_network_get_lac_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_lac(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_lac(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_cell_id_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the cell ID.
 */
int utc_telephony_telephony_network_get_cell_id_p(void)
{
	int cell_id, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_cell_id(telephony_handle, &cell_id);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_cell_id(telephony_handle, &cell_id);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_cell_id_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the cell ID. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_cell_id_n1(void)
{
	int cell_id, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_cell_id(NULL, &cell_id);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_cell_id(NULL, &cell_id);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_cell_id_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the cell ID. (NULL 'cell_id' param)
 */
int utc_telephony_telephony_network_get_cell_id_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_cell_id(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_cell_id(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_rssi_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the RSSI.
 */
int utc_telephony_telephony_network_get_rssi_p(void)
{
	telephony_network_rssi_e rssi;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_rssi(telephony_handle, &rssi);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_rssi(telephony_handle, &rssi);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_rssi_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the RSSI. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_rssi_n1(void)
{
	telephony_network_rssi_e rssi;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_rssi(NULL, &rssi);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_rssi(NULL, &rssi);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_rssi_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the RSSI. (NULL 'rssi' param)
 */
int utc_telephony_telephony_network_get_rssi_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_rssi(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_rssi(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_roaming_status_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the roaming state.
 */
int utc_telephony_telephony_network_get_roaming_status_p(void)
{
	bool roaming_status;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_roaming_status(telephony_handle, &roaming_status);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_roaming_status(telephony_handle, &roaming_status);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_roaming_status_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the roaming state. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_roaming_status_n1(void)
{
	bool roaming_status;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_roaming_status(NULL, &roaming_status);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_roaming_status(NULL, &roaming_status);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_roaming_status_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the roaming state. (NULL 'status' param)
 */
int utc_telephony_telephony_network_get_roaming_status_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_roaming_status(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_roaming_status(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_mcc_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the MCC of the current registered network.
 */
int utc_telephony_telephony_network_get_mcc_p(void)
{
	char *mcc = NULL;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_mcc(telephony_handle, &mcc);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_mcc(telephony_handle, &mcc);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	free(mcc);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_mcc_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the MCC of the current registered network. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_mcc_n1(void)
{
	char *mcc = NULL;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_mcc(NULL, &mcc);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_mcc(NULL, &mcc);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_mcc_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the MCC of the current registered network. (NULL 'mcc' param)
 */
int utc_telephony_telephony_network_get_mcc_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_mcc(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_mcc(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_mnc_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the MNC of the current registered network.
 */
int utc_telephony_telephony_network_get_mnc_p(void)
{
	char *mnc = NULL;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_mnc(telephony_handle, &mnc);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_mnc(telephony_handle, &mnc);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	free(mnc);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_mnc_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the MNC of the current registered network. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_mnc_n1(void)
{
	char *mnc = NULL;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_mnc(NULL, &mnc);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_mnc(NULL, &mnc);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_mnc_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the MNC of the current registered network. (NULL 'mnc' param)
 */
int utc_telephony_telephony_network_get_mnc_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_mnc(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_mnc(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_network_name_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the name of the current registered network.
 */
int utc_telephony_telephony_network_get_network_name_p(void)
{
	char *network_name = NULL;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_network_name(telephony_handle, &network_name);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_network_name(telephony_handle, &network_name);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	free(network_name);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_network_name_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the name of the current registered network. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_network_name_n1(void)
{
	char *network_name = NULL;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_network_name(NULL, &network_name);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_network_name(NULL, &network_name);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_network_name_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the name of the current registered network. (NULL 'network_name' param)
 */
int utc_telephony_telephony_network_get_network_name_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_network_name(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_network_name(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_type_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the network service type of the current registered network.
 */
int utc_telephony_telephony_network_get_type_p(void)
{
	telephony_network_type_e network_type;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_type(telephony_handle, &network_type);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_type(telephony_handle, &network_type);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_type_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the network service type of the current registered network. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_type_n1(void)
{
	telephony_network_type_e network_type;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_type(NULL, &network_type);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_type(NULL, &network_type);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_type_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the network service type of the current registered network. (NULL 'network_type' param)
 */
int utc_telephony_telephony_network_get_type_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_type(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_type(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_ps_type_p
 * @since_tizen		2.4
 * @description		Positive test case for getting the packet service type of the current registered network.
 */
int utc_telephony_telephony_network_get_ps_type_p(void)
{
	telephony_network_ps_type_e ps_type;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_ps_type(telephony_handle, &ps_type);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_ps_type(telephony_handle, &ps_type);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_ps_type_n1
 * @since_tizen		2.4
 * @description		Positive test case for getting the packet service type of the current registered network. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_ps_type_n1(void)
{
	telephony_network_ps_type_e ps_type;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_ps_type(NULL, &ps_type);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_ps_type(NULL, &ps_type);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_ps_type_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting the packet service type of the current registered network. (NULL 'ps_type' param)
 */
int utc_telephony_telephony_network_get_ps_type_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_ps_type(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_ps_type(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_network_name_option_p
 * @since_tizen		2.4
 * @description		Positive test case for getting the network name option of the current registered network.
 */
int utc_telephony_telephony_network_get_network_name_option_p(void)
{
	telephony_network_name_option_e network_name_option;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_network_name_option(telephony_handle, &network_name_option);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_network_name_option(telephony_handle, &network_name_option);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_network_name_option_n1
 * @since_tizen		2.4
 * @description		Negative test case for getting the network name option of the current registered network. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_network_name_option_n1(void)
{
	telephony_network_name_option_e network_name_option;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_network_name_option(NULL, &network_name_option);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_network_name_option(NULL, &network_name_option);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_network_name_option_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting the network name option of the current registered network. (NULL 'network_name_option' param)
 */
int utc_telephony_telephony_network_get_network_name_option_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_network_name_option(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_network_name_option(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_service_state_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the current network state of the telephony service.
 */
int utc_telephony_telephony_network_get_service_state_p(void)
{
	telephony_network_service_state_e service_state;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_service_state(telephony_handle, &service_state);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_service_state(telephony_handle, &service_state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_service_state_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the current network state of the telephony service. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_service_state_n1(void)
{
	telephony_network_service_state_e service_state;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_service_state(NULL, &service_state);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_service_state(NULL, &service_state);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_service_state_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the current network state of the telephony service. (NULL 'network_service_state' param)
 */
int utc_telephony_telephony_network_get_service_state_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_service_state(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_service_state(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_default_data_subscription_p
 * @since_tizen		2.4
 * @description		Positive test case for getting the current default subscription for data service.
 */
int utc_telephony_telephony_network_get_default_data_subscription_p(void)
{
	telephony_network_default_data_subs_e default_data_sub;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_default_data_subscription(telephony_handle, &default_data_sub);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_default_data_subscription(telephony_handle, &default_data_sub);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_default_data_subscription_n1
 * @since_tizen		2.4
 * @description		Negative test case for getting the current default subscription for data service. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_default_data_subscription_n1(void)
{
	telephony_network_default_data_subs_e default_data_sub;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_default_data_subscription(NULL, &default_data_sub);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_default_data_subscription(NULL, &default_data_sub);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_default_data_subscription_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting the current default subscription for data service. (NULL 'default_sub' param)
 */
int utc_telephony_telephony_network_get_default_data_subscription_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_default_data_subscription(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_default_data_subscription(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_default_subscription_p
 * @since_tizen		2.4
 * @description		Positive test case for getting the current default subscription for voice service.
 */
int utc_telephony_telephony_network_get_default_subscription_p(void)
{
	telephony_network_default_subs_e default_sub;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_default_subscription(telephony_handle, &default_sub);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_default_subscription(telephony_handle, &default_sub);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_default_subscription_n1
 * @since_tizen		2.4
 * @description		Negative test case for getting the current default subscription for voice service. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_default_subscription_n1(void)
{
	telephony_network_default_subs_e default_sub;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_default_subscription(NULL, &default_sub);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_default_subscription(NULL, &default_sub);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_default_subscription_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting the current default subscription for voice service. (NULL 'default_sub' param)
 */
int utc_telephony_telephony_network_get_default_subscription_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_default_subscription(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_default_subscription(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_selection_mode_p
 * @since_tizen			3.0
 * @description			Positive test case for getting the network selection mode.
 */
int utc_telephony_telephony_network_get_selection_mode_p(void)
{
	telephony_network_selection_mode_e mode;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_selection_mode(telephony_handle, &mode);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_selection_mode(telephony_handle, &mode);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_selection_mode_n1
 * @since_tizen		3.0
 * @description		Negative test case for getting the network selection mode. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_selection_mode_n1(void)
{
	telephony_network_selection_mode_e mode;
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_selection_mode(NULL, &mode);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_selection_mode(NULL, &mode);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_selection_mode_n2
 * @since_tizen		3.0
 * @description		Negative test case for getting the network selection mode. (NULL 'mode' param)
 */
int utc_telephony_telephony_network_get_selection_mode_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_selection_mode(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_selection_mode(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_tac_p
 * @since_tizen		3.0
 * @description		Positive test case for getting the TAC of the current location.
 */
int utc_telephony_telephony_network_get_tac_p(void)
{
	int tac, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_tac(telephony_handle, &tac);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_tac(telephony_handle, &tac);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_tac_n1
 * @since_tizen		3.0
 * @description		Negative test case for getting the TAC of the current location. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_tac_n1(void)
{
	int tac, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_tac(NULL, &tac);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_tac(NULL, &tac);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_tac_n2
 * @since_tizen		3.0
 * @description		Negative test case for getting the TAC of the current location. (NULL 'tac' param)
 */
int utc_telephony_telephony_network_get_tac_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_tac(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_tac(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_system_id_p
 * @since_tizen		3.0
 * @description		Positive test case for getting the system ID of the current location.
 */
int utc_telephony_telephony_network_get_system_id_p(void)
{
	int sid, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_system_id(telephony_handle, &sid);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_system_id(telephony_handle, &sid);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_system_id_n1
 * @since_tizen		3.0
 * @description		Negative test case for getting the system ID of the current location. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_system_id_n1(void)
{
	int sid, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_system_id(NULL, &sid);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_system_id(NULL, &sid);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_system_id_n2
 * @since_tizen		3.0
 * @description		Negative test case for getting the system ID of the current location. (NULL 'sid' param)
 */
int utc_telephony_telephony_network_get_system_id_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_system_id(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_system_id(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_network_id_p
 * @since_tizen		3.0
 * @description		Positive test case for getting the network ID of the current location.
 */
int utc_telephony_telephony_network_get_network_id_p(void)
{
	int nid, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_network_id(telephony_handle, &nid);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_network_id(telephony_handle, &nid);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_network_id_n1
 * @since_tizen		3.0
 * @description		Negative test case for getting the network ID of the current location. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_network_id_n1(void)
{
	int nid, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_network_id(NULL, &nid);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_network_id(NULL, &nid);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_network_id_n2
 * @since_tizen		3.0
 * @description		Negative test case for getting the network ID of the current location. (NULL 'nid' param)
 */
int utc_telephony_telephony_network_get_network_id_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_network_id(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_network_id(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_base_station_id_p
 * @since_tizen		3.0
 * @description		Positive test case for getting the base station ID of the current location.
 */
int utc_telephony_telephony_network_get_base_station_id_p(void)
{
	int bs_id, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_base_station_id(telephony_handle, &bs_id);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_base_station_id(telephony_handle, &bs_id);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_base_station_id_n1
 * @since_tizen		3.0
 * @description		Negative test case for getting the base station ID of the current location. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_base_station_id_n1(void)
{
	int bs_id, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_base_station_id(NULL, &bs_id);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_base_station_id(NULL, &bs_id);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_base_station_id_n2
 * @since_tizen		3.0
 * @description		Negative test case for getting the base station ID of the current location. (NULL 'bs_id' param)
 */
int utc_telephony_telephony_network_get_base_station_id_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_base_station_id(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_base_station_id(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_base_station_latitude_p
 * @since_tizen		3.0
 * @description		Positive test case for getting the base station latitude of the current location.
 */
int utc_telephony_telephony_network_get_base_station_latitude_p(void)
{
	int bs_latitude, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_base_station_latitude(telephony_handle, &bs_latitude);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_base_station_latitude(telephony_handle, &bs_latitude);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_base_station_latitude_n1
 * @since_tizen		3.0
 * @description		Negative test case for getting the base station latitude of the current location. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_base_station_latitude_n1(void)
{
	int bs_latitude, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_base_station_latitude(NULL, &bs_latitude);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_base_station_latitude(NULL, &bs_latitude);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_base_station_latitude_n2
 * @since_tizen		3.0
 * @description		Negative test case for getting the base station latitude of the current location. (NULL 'bs_latitude' param)
 */
int utc_telephony_telephony_network_get_base_station_latitude_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_base_station_latitude(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_base_station_latitude(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_base_station_longitude_p
 * @since_tizen		3.0
 * @description		Positive test case for getting the base station longitude of the current location.
 */
int utc_telephony_telephony_network_get_base_station_longitude_p(void)
{
	int bs_longitude, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_base_station_longitude(telephony_handle, &bs_longitude);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_base_station_longitude(telephony_handle, &bs_longitude);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_base_station_longitude_n1
 * @since_tizen		3.0
 * @description		Negative test case for getting the base station longitude of the current location. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_base_station_longitude_n1(void)
{
	int bs_longitude, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_base_station_longitude(NULL, &bs_longitude);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_base_station_longitude(NULL, &bs_longitude);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_base_station_longitude_n2
 * @since_tizen		3.0
 * @description		Negative test case for getting the base station longitude of the current location. (NULL 'bs_longitude' param)
 */
int utc_telephony_telephony_network_get_base_station_longitude_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_base_station_longitude(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_base_station_longitude(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_signal_strength_p
 * @since_tizen		4.0
 * @description		Positive test case for getting the signal strength with dBm.
 */
int utc_telephony_telephony_network_get_signal_strength_p(void)
{
	int dbm, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_signal_strength(telephony_handle, &dbm);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_network_get_signal_strength(telephony_handle, &dbm);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_signal_strength_n1
 * @since_tizen		4.0
 * @description		Negative test case for getting the signal strength with dBm. (NULL 'handle' param)
 */
int utc_telephony_telephony_network_get_signal_strength_n1(void)
{
	int dbm, ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_signal_strength(NULL, &dbm);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_signal_strength(NULL, &dbm);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_network_get_signal_strength_n2
 * @since_tizen		4.0
 * @description		Negative test case for getting the signal strength with dBm. (NULL 'dbm' param)
 */
int utc_telephony_telephony_network_get_signal_strength_n2(void)
{
	int ret;

	if (g_telephony_network_supported == false) {
		ret = telephony_network_get_signal_strength(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_network_get_signal_strength(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

