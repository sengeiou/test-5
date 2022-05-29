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

static bool g_telephony_sim_supported = true;
static telephony_handle_list_s handle_list;
static telephony_h telephony_handle = NULL;

/**
 * @function		utc_telephony_sim_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_telephony_sim_startup(void)
{
	system_info_get_platform_bool("tizen.org/feature/network.telephony", &g_telephony_sim_supported);
	if (g_telephony_sim_supported) {
		if (telephony_init(&handle_list) == TELEPHONY_ERROR_NONE && handle_list.count > 0)
			telephony_handle = handle_list.handle[0];
	}
}

/**
 * @function		utc_telephony_sim_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_telephony_sim_cleanup(void)
{
	if (g_telephony_sim_supported) {
		telephony_deinit(&handle_list);
		telephony_handle = NULL;
	}
}

/**
 * @testcase		utc_telephony_telephony_sim_get_operator_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the SIM operator.
 */
int utc_telephony_telephony_sim_get_operator_p(void)
{
	char *operator_name = NULL;
	int ret;
	telephony_sim_state_e sim_state;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_operator(telephony_handle, &operator_name);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_sim_get_state(telephony_handle, &sim_state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	assert_eq(sim_state, TELEPHONY_SIM_STATE_AVAILABLE);

	ret = telephony_sim_get_operator(telephony_handle, &operator_name);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	free(operator_name);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_operator_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the SIM operator. (NULL 'handle' param)
 */
int utc_telephony_telephony_sim_get_operator_n1(void)
{
	char *operator_name = NULL;
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_operator(NULL, &operator_name);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_operator(NULL, &operator_name);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_operator_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the SIM operator. (NULL 'sim_operator' param)
 */
int utc_telephony_telephony_sim_get_operator_n2(void)
{
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_operator(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_operator(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_msin_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the mobile subscription identification number of the SIM provider.
 */
int utc_telephony_telephony_sim_get_msin_p(void)
{
	char *msin = NULL;
	int ret;
	telephony_sim_state_e sim_state;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_msin(telephony_handle, &msin);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_sim_get_state(telephony_handle, &sim_state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	assert_eq(sim_state, TELEPHONY_SIM_STATE_AVAILABLE);

	ret = telephony_sim_get_msin(telephony_handle, &msin);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	free(msin);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_msin_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the mobile subscription identification number of the SIM provider. (NULL 'handle' param)
 */
int utc_telephony_telephony_sim_get_msin_n1(void)
{
	char *msin = NULL;
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_msin(NULL, &msin);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_msin(NULL, &msin);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_msin_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the mobile subscription identification number of the SIM provider. (NULL 'msin' param)
 */
int utc_telephony_telephony_sim_get_msin_n2(void)
{
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_msin(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_msin(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_spn_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the service provider name of the SIM card.
 */
int utc_telephony_telephony_sim_get_spn_p(void)
{
	char *spn = NULL;
	int ret;
	telephony_sim_state_e sim_state;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_spn(telephony_handle, &spn);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_sim_get_state(telephony_handle, &sim_state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	assert_eq(sim_state, TELEPHONY_SIM_STATE_AVAILABLE);

	ret = telephony_sim_get_spn(telephony_handle, &spn);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	free(spn);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_spn_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the service provider name of the SIM card. (NULL 'handle' param)
 */
int utc_telephony_telephony_sim_get_spn_n1(void)
{
	char *spn = NULL;
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_spn(NULL, &spn);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_spn(NULL, &spn);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_spn_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the service provider name of the SIM card. (NULL 'spn' param)
 */
int utc_telephony_telephony_sim_get_spn_n2(void)
{
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_spn(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_spn(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_is_changed_p
 * @since_tizen		2.3
 * @description		Positive test case for checking whether the current SIM card is different from previous SIM card.
 */
int utc_telephony_telephony_sim_is_changed_p(void)
{
	bool changed;
	int ret;
	telephony_sim_state_e sim_state;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_is_changed(telephony_handle, &changed);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_sim_get_state(telephony_handle, &sim_state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	assert_eq(sim_state, TELEPHONY_SIM_STATE_AVAILABLE);

	ret = telephony_sim_is_changed(telephony_handle, &changed);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_is_changed_n1
 * @since_tizen		2.3
 * @description		Negative test case for checking whether the current SIM card is different from previous SIM card. (NULL 'handle' param)
 */
int utc_telephony_telephony_sim_is_changed_n1(void)
{
	bool changed;
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_is_changed(NULL, &changed);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_is_changed(NULL, &changed);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_is_changed_n2
 * @since_tizen		2.3
 * @description		Negative test case for checking whether the current SIM card is different from previous SIM card. (NULL 'is_changed' param)
 */
int utc_telephony_telephony_sim_is_changed_n2(void)
{
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_is_changed(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_is_changed(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_state_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the state of the SIM.
 */
int utc_telephony_telephony_sim_get_state_p(void)
{
	telephony_sim_state_e sim_state;
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_state(telephony_handle, &sim_state);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_sim_get_state(telephony_handle, &sim_state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_state_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the state of the SIM. (NULL 'handle' param)
 */
int utc_telephony_telephony_sim_get_state_n1(void)
{
	telephony_sim_state_e sim_state;
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_state(NULL, &sim_state);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_state(NULL, &sim_state);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_state_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the state of the SIM. (NULL 'sim_state' param)
 */
int utc_telephony_telephony_sim_get_state_n2(void)
{
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_state(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_state(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_application_list_p
 * @since_tizen		2.4
 * @description		Positive test case for getting the list of application on UICC.
 */
int utc_telephony_telephony_sim_get_application_list_p(void)
{
	int ret;
	telephony_sim_state_e sim_state;
	unsigned int sim_card_type;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_application_list(telephony_handle, &sim_card_type);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_sim_get_state(telephony_handle, &sim_state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	assert_eq(sim_state, TELEPHONY_SIM_STATE_AVAILABLE);

	ret = telephony_sim_get_application_list(telephony_handle, &sim_card_type);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_application_list_n1
 * @since_tizen		2.4
 * @description		Negative test case for getting the list of application on UICC. (NULL 'handle' param)
 */
int utc_telephony_telephony_sim_get_application_list_n1(void)
{
	unsigned int sim_card_type;
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_application_list(NULL, &sim_card_type);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_application_list(NULL, &sim_card_type);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_application_list_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting the list of application on UICC. (NULL 'app_list' param)
 */
int utc_telephony_telephony_sim_get_application_list_n2(void)
{
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_application_list(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_application_list(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_subscriber_number_p
 * @since_tizen		2.3
 * @description		Positive test case for getting the SIM card subscriber number.
 */
int utc_telephony_telephony_sim_get_subscriber_number_p(void)
{
	char *subscriber_name = NULL;
	int ret;
	telephony_sim_state_e sim_state;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_subscriber_number(telephony_handle, &subscriber_name);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_sim_get_state(telephony_handle, &sim_state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	assert_eq(sim_state, TELEPHONY_SIM_STATE_AVAILABLE);

	ret = telephony_sim_get_subscriber_number(telephony_handle, &subscriber_name);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	free(subscriber_name);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_subscriber_number_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the SIM card subscriber number. (NULL 'handle' param)
 */
int utc_telephony_telephony_sim_get_subscriber_number_n1(void)
{
	char *subscriber_name = NULL;
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_subscriber_number(NULL, &subscriber_name);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_subscriber_number(NULL, &subscriber_name);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_subscriber_number_n2
 * @since_tizen		2.3
 * @description		Negative test case for getting the SIM card subscriber number. (NULL 'subscriber_number' param)
 */
int utc_telephony_telephony_sim_get_subscriber_number_n2(void)
{
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_subscriber_number(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_subscriber_number(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_subscriber_id_p
 * @since_tizen		2.4
 * @description		Positive test case for getting the subscriber ID.
 */
int utc_telephony_telephony_sim_get_subscriber_id_p(void)
{
	char *subscriber_id = NULL;
	int ret;
	telephony_sim_state_e sim_state;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_subscriber_id(telephony_handle, &subscriber_id);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_sim_get_state(telephony_handle, &sim_state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	assert_eq(sim_state, TELEPHONY_SIM_STATE_AVAILABLE);

	ret = telephony_sim_get_subscriber_id(telephony_handle, &subscriber_id);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	free(subscriber_id);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_subscriber_id_n1
 * @since_tizen		2.4
 * @description		Negative test case for getting the subscriber ID. (NULL 'handle' param)
 */
int utc_telephony_telephony_sim_get_subscriber_id_n1(void)
{
	char *subscriber_id = NULL;
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_subscriber_id(NULL, &subscriber_id);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_subscriber_id(NULL, &subscriber_id);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_subscriber_id_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting the subscriber ID. (NULL 'subscriber_id' param)
 */
int utc_telephony_telephony_sim_get_subscriber_id_n2(void)
{
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_subscriber_id(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_subscriber_id(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_lock_state_p
 * @since_tizen		3.0
 * @description		Positive test case for getting the lock state of the SIM.
 */
int utc_telephony_telephony_sim_get_lock_state_p(void)
{
	telephony_sim_lock_state_e sim_lock_state;
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_lock_state(telephony_handle, &sim_lock_state);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_sim_get_lock_state(telephony_handle, &sim_lock_state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_lock_state_n1
 * @since_tizen		3.0
 * @description		Negative test case for getting the lock state of the SIM. (NULL 'handle' param)
 */
int utc_telephony_telephony_sim_get_lock_state_n1(void)
{
	telephony_sim_lock_state_e sim_lock_state;
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_lock_state(NULL, &sim_lock_state);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_lock_state(NULL, &sim_lock_state);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_lock_state_n2
 * @since_tizen		3.0
 * @description		Negative test case for getting the lock state of the SIM. (NULL 'sim_lock_state' param)
 */
int utc_telephony_telephony_sim_get_lock_state_n2(void)
{
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_lock_state(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_lock_state(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_group_id1_p
 * @since_tizen		3.0
 * @description		Positive test case for getting the group id1 of the SIM card.
 */
int utc_telephony_telephony_sim_get_group_id1_p(void)
{
	char *group_id1 = NULL;
	int ret;
	telephony_sim_state_e sim_state;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_group_id1(telephony_handle, &group_id1);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_sim_get_state(telephony_handle, &sim_state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	assert_eq(sim_state, TELEPHONY_SIM_STATE_AVAILABLE);

	ret = telephony_sim_get_group_id1(telephony_handle, &group_id1);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	free(group_id1);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_group_id1_n1
 * @since_tizen		3.0
 * @description		Negative test case for getting the group id1 of the SIM card. (NULL 'handle' param)
 */
int utc_telephony_telephony_sim_get_group_id1_n1(void)
{
	char *group_id1 = NULL;
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_group_id1(NULL, &group_id1);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_group_id1(NULL, &group_id1);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_group_id1_n2
 * @since_tizen		3.0
 * @description		Negative test case for getting the group id1 of the SIM card. (NULL 'group_id1' param)
 */
int utc_telephony_telephony_sim_get_group_id1_n2(void)
{
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_group_id1(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_group_id1(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_call_forwarding_indicator_state_p
 * @since_tizen		3.0
 * @description		Positive test case for getting the call forwarding indicator state of the SIM card.
 */
int utc_telephony_telephony_sim_get_call_forwarding_indicator_state_p(void)
{
	bool state;
	int ret;
	telephony_sim_state_e sim_state;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_call_forwarding_indicator_state(telephony_handle, &state);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_sim_get_state(telephony_handle, &sim_state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	assert_eq(sim_state, TELEPHONY_SIM_STATE_AVAILABLE);

	ret = telephony_sim_get_call_forwarding_indicator_state(telephony_handle, &state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_call_forwarding_indicator_state_n1
 * @since_tizen		3.0
 * @description		Negative test case getting the call forwarding indicator state of the SIM card. (NULL 'handle' param)
 */
int utc_telephony_telephony_sim_get_call_forwarding_indicator_state_n1(void)
{
	bool state;
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_call_forwarding_indicator_state(NULL, &state);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_call_forwarding_indicator_state(NULL, &state);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_sim_get_call_forwarding_indicator_state_n2
 * @since_tizen		3.0
 * @description		Negative test case for getting the call forwarding indicator state of the SIM card. (NULL 'state' param)
 */
int utc_telephony_telephony_sim_get_call_forwarding_indicator_state_n2(void)
{
	int ret;

	if (g_telephony_sim_supported == false) {
		ret = telephony_sim_get_call_forwarding_indicator_state(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_sim_get_call_forwarding_indicator_state(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}
