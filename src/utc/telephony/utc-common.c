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

static bool g_telephony_common_supported = true;
static telephony_handle_list_s handle_list;
static telephony_h telephony_handle = NULL;

static void _noti_cb(telephony_h handle, telephony_noti_e noti_id, void *data, void *user_data)
{
}

static void _ready_state_cb(int state, void *user_data)
{
}

/**
 * @function		utc_telephony_common_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_telephony_common_startup(void)
{
	system_info_get_platform_bool("tizen.org/feature/network.telephony", &g_telephony_common_supported);
	if (g_telephony_common_supported) {
		if (telephony_init(&handle_list) == TELEPHONY_ERROR_NONE && handle_list.count > 0)
			telephony_handle = handle_list.handle[0];
	}
}

/**
 * @function		utc_telephony_common_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_telephony_common_cleanup(void)
{
	if (g_telephony_common_supported) {
		telephony_deinit(&handle_list);
		telephony_handle = NULL;
	}
}

/**
 * @testcase		utc_telephony_telephony_init_p
 * @since_tizen		2.3
 * @description		Positive test case for acquiring the list of available handles to use the telephony API.
 */
int utc_telephony_telephony_init_p(void)
{
	int ret;
	telephony_handle_list_s handle_list2;

	if (g_telephony_common_supported == false) {
		ret = telephony_init(&handle_list2);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_init(&handle_list2);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_deinit(&handle_list2);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_init_n
 * @since_tizen		2.3
 * @description		Negative test case for acquiring the list of available handles to use the telephony API. (NULL input param)
 */
int utc_telephony_telephony_init_n(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_init(NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_init(NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_deinit_p
 * @since_tizen		2.3
 * @description		Positive test case for deinitializing the telephony handle list.
 */
int utc_telephony_telephony_deinit_p(void)
{
	int ret;
	telephony_handle_list_s handle_list2;

	if (g_telephony_common_supported == false) {
		ret = telephony_deinit(NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_init(&handle_list2);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_deinit(&handle_list2);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_deinit_n
 * @since_tizen		2.3
 * @description		Negative test case for deinitializing the telephony handle list. (NULL input param)
 */
int utc_telephony_telephony_deinit_n(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_deinit(NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_deinit(NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p1
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_SIM_STATUS)
 */
int utc_telephony_telephony_set_noti_cb_p1(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_SIM_STATUS, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_SIM_STATUS, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p2
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_SERVICE_STATE)
 */
int utc_telephony_telephony_set_noti_cb_p2(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SERVICE_STATE, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SERVICE_STATE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p3
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_CELLID)
 */
int utc_telephony_telephony_set_noti_cb_p3(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_CELLID, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_CELLID, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p4
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_ROAMING_STATUS)
 */
int utc_telephony_telephony_set_noti_cb_p4(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_ROAMING_STATUS, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_ROAMING_STATUS, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p5
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_SIGNALSTRENGTH_LEVEL)
 */
int utc_telephony_telephony_set_noti_cb_p5(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SIGNALSTRENGTH_LEVEL, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SIGNALSTRENGTH_LEVEL, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p6
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_NETWORK_NAME)
 */
int utc_telephony_telephony_set_noti_cb_p6(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_NETWORK_NAME, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_NETWORK_NAME, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p7
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_PS_TYPE)
 */
int utc_telephony_telephony_set_noti_cb_p7(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_PS_TYPE, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_PS_TYPE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p8
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_DEFAULT_DATA_SUBSCRIPTION)
 */
int utc_telephony_telephony_set_noti_cb_p8(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_DEFAULT_DATA_SUBSCRIPTION, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_DEFAULT_DATA_SUBSCRIPTION, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p9
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_DEFAULT_SUBSCRIPTION)
 */
int utc_telephony_telephony_set_noti_cb_p9(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_DEFAULT_SUBSCRIPTION, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_DEFAULT_SUBSCRIPTION, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}


/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p12
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_VOICE_CALL_STATUS_IDLE)
 */
int utc_telephony_telephony_set_noti_cb_p12(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_IDLE, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_IDLE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p13
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_VOICE_CALL_STATUS_ACTIVE)
 */
int utc_telephony_telephony_set_noti_cb_p13(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_ACTIVE, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_ACTIVE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p14
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_VOICE_CALL_STATUS_HELD)
 */
int utc_telephony_telephony_set_noti_cb_p14(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_HELD, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_HELD, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p15
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_VOICE_CALL_STATUS_DIALING)
 */
int utc_telephony_telephony_set_noti_cb_p15(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_DIALING, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_DIALING, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p16
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_VOICE_CALL_STATUS_ALERTING)
 */
int utc_telephony_telephony_set_noti_cb_p16(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_ALERTING, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_ALERTING, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p17
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_VOICE_CALL_STATUS_INCOMING)
 */
int utc_telephony_telephony_set_noti_cb_p17(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_INCOMING, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_INCOMING, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p18
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_VIDEO_CALL_STATUS_IDLE)
 */
int utc_telephony_telephony_set_noti_cb_p18(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_IDLE, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_IDLE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p19
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_VIDEO_CALL_STATUS_ACTIVE)
 */
int utc_telephony_telephony_set_noti_cb_p19(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_ACTIVE, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_ACTIVE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p20
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_VIDEO_CALL_STATUS_DIALING)
 */
int utc_telephony_telephony_set_noti_cb_p20(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_DIALING, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_DIALING, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p21
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_VIDEO_CALL_STATUS_ALERTING)
 */
int utc_telephony_telephony_set_noti_cb_p21(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_ALERTING, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_ALERTING, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p22
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_VIDEO_CALL_STATUS_INCOMING)
 */
int utc_telephony_telephony_set_noti_cb_p22(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_INCOMING, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_INCOMING, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p23
 * @since_tizen		2.3
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_CALL_PREFERRED_VOICE_SUBSCRIPTION)
 */
int utc_telephony_telephony_set_noti_cb_p23(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_CALL_PREFERRED_VOICE_SUBSCRIPTION, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_CALL_PREFERRED_VOICE_SUBSCRIPTION, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p24
 * @since_tizen		3.0
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_SIM_CALL_FORWARDING_INDICATOR_STATE)
 */
int utc_telephony_telephony_set_noti_cb_p24(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_SIM_CALL_FORWARDING_INDICATOR_STATE, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_SIM_CALL_FORWARDING_INDICATOR_STATE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p25
 * @since_tizen		3.0
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_LAC)
 */
int utc_telephony_telephony_set_noti_cb_p25(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_LAC, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_LAC, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p26
 * @since_tizen		3.0
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_TAC)
 */
int utc_telephony_telephony_set_noti_cb_p26(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_TAC, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_TAC, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p27
 * @since_tizen		3.0
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_SYSTEM_ID)
 */
int utc_telephony_telephony_set_noti_cb_p27(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SYSTEM_ID, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SYSTEM_ID, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p28
 * @since_tizen		3.0
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_NETWORK_ID)
 */
int utc_telephony_telephony_set_noti_cb_p28(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_NETWORK_ID, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_NETWORK_ID, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p29
 * @since_tizen		3.0
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_BS_ID)
 */
int utc_telephony_telephony_set_noti_cb_p29(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_ID, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_ID, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p30
 * @since_tizen		3.0
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_BS_LATITUDE)
 */
int utc_telephony_telephony_set_noti_cb_p30(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_LATITUDE, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_LATITUDE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p31
 * @since_tizen		3.0
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_NETWORK_BS_LONGITUDE)
 */
int utc_telephony_telephony_set_noti_cb_p31(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_LONGITUDE, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_LONGITUDE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_p32
 * @since_tizen		4.0
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed. (TELEPHONY_NOTI_MODEM_POWER_STATUS)
 */
int utc_telephony_telephony_set_noti_cb_p32(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_MODEM_POWER_STATUS, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_MODEM_POWER_STATUS, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_n1
 * @since_tizen		2.3
 * @description		Negative test case for setting a callback function to be invoked when the telephony state changed. (NULL input param)
 */
int utc_telephony_telephony_set_noti_cb_n1(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(NULL, TELEPHONY_NOTI_SIM_STATUS, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_set_noti_cb(NULL, TELEPHONY_NOTI_SIM_STATUS, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_set_noti_cb_n2
 * @since_tizen		2.3
 * @description		Negative test case for setting a callback function to be invoked when the telephony state changed. (invalid noti_id)
 */
int utc_telephony_telephony_set_noti_cb_n2(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_noti_cb(NULL, -1, _noti_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_set_noti_cb(NULL, -1, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p1
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_SIM_STATUS)
 */
int utc_telephony_telephony_unset_noti_cb_p1(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_SIM_STATUS);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_SIM_STATUS, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_SIM_STATUS);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p2
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_SERVICE_STATE))
 */
int utc_telephony_telephony_unset_noti_cb_p2(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SERVICE_STATE);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SERVICE_STATE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SERVICE_STATE);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p3
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_CELLID)
 */
int utc_telephony_telephony_unset_noti_cb_p3(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_CELLID);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_CELLID, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_CELLID);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p4
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_ROAMING_STATUS)
 */
int utc_telephony_telephony_unset_noti_cb_p4(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_ROAMING_STATUS);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_ROAMING_STATUS, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_ROAMING_STATUS);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p5
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_SIGNALSTRENGTH_LEVEL)
 */
int utc_telephony_telephony_unset_noti_cb_p5(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SIGNALSTRENGTH_LEVEL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SIGNALSTRENGTH_LEVEL, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SIGNALSTRENGTH_LEVEL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p6
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_NETWORK_NAME)
 */
int utc_telephony_telephony_unset_noti_cb_p6(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_NETWORK_NAME);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_NETWORK_NAME, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_NETWORK_NAME);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p7
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_PS_TYPE)
 */
int utc_telephony_telephony_unset_noti_cb_p7(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_PS_TYPE);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_PS_TYPE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_PS_TYPE);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p8
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_DEFAULT_DATA_SUBSCRIPTION)
 */
int utc_telephony_telephony_unset_noti_cb_p8(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_DEFAULT_DATA_SUBSCRIPTION);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_DEFAULT_DATA_SUBSCRIPTION, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_DEFAULT_DATA_SUBSCRIPTION);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p9
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_DEFAULT_SUBSCRIPTION)
 */
int utc_telephony_telephony_unset_noti_cb_p9(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_DEFAULT_SUBSCRIPTION);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_DEFAULT_SUBSCRIPTION, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_DEFAULT_SUBSCRIPTION);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}


/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p12
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_VOICE_CALL_STATUS_IDLE)
 */
int utc_telephony_telephony_unset_noti_cb_p12(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_IDLE);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_IDLE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_IDLE);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p13
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_VOICE_CALL_STATUS_ACTIVE)
 */
int utc_telephony_telephony_unset_noti_cb_p13(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_ACTIVE);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_ACTIVE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_ACTIVE);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p14
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_VOICE_CALL_STATUS_HELD)
 */
int utc_telephony_telephony_unset_noti_cb_p14(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_HELD);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_HELD, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_HELD);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p15
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_VOICE_CALL_STATUS_DIALING)
 */
int utc_telephony_telephony_unset_noti_cb_p15(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_DIALING);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_DIALING, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_DIALING);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p16
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_VOICE_CALL_STATUS_ALERTING)
 */
int utc_telephony_telephony_unset_noti_cb_p16(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_ALERTING);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_ALERTING, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_ALERTING);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p17
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_VOICE_CALL_STATUS_INCOMING)
 */
int utc_telephony_telephony_unset_noti_cb_p17(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_INCOMING);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_INCOMING, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VOICE_CALL_STATUS_INCOMING);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p18
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_VIDEO_CALL_STATUS_IDLE)
 */
int utc_telephony_telephony_unset_noti_cb_p18(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_IDLE);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_IDLE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_IDLE);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p19
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_VIDEO_CALL_STATUS_ACTIVE)
 */
int utc_telephony_telephony_unset_noti_cb_p19(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_ACTIVE);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_ACTIVE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_ACTIVE);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p20
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_VIDEO_CALL_STATUS_DIALING)
 */
int utc_telephony_telephony_unset_noti_cb_p20(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_DIALING);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_DIALING, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_DIALING);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p21
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_VIDEO_CALL_STATUS_ALERTING)
 */
int utc_telephony_telephony_unset_noti_cb_p21(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_ALERTING);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_ALERTING, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_ALERTING);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p22
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_VIDEO_CALL_STATUS_INCOMING)
 */
int utc_telephony_telephony_unset_noti_cb_p22(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_INCOMING);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_INCOMING, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_VIDEO_CALL_STATUS_INCOMING);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p23
 * @since_tizen		2.3
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_CALL_PREFERRED_VOICE_SUBSCRIPTION)
 */
int utc_telephony_telephony_unset_noti_cb_p23(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_CALL_PREFERRED_VOICE_SUBSCRIPTION);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_CALL_PREFERRED_VOICE_SUBSCRIPTION, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_CALL_PREFERRED_VOICE_SUBSCRIPTION);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p24
 * @since_tizen		3.0
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_SIM_CALL_FORWARDING_INDICATOR_STATE)
 */
int utc_telephony_telephony_unset_noti_cb_p24(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_SIM_CALL_FORWARDING_INDICATOR_STATE);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_SIM_CALL_FORWARDING_INDICATOR_STATE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_SIM_CALL_FORWARDING_INDICATOR_STATE);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p25
 * @since_tizen		3.0
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_LAC)
 */
int utc_telephony_telephony_unset_noti_cb_p25(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_LAC);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_LAC, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_LAC);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p26
 * @since_tizen		3.0
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_TAC)
 */
int utc_telephony_telephony_unset_noti_cb_p26(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_TAC);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_TAC, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_TAC);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p27
 * @since_tizen		3.0
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_SYSTEM_ID)
 */
int utc_telephony_telephony_unset_noti_cb_p27(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SYSTEM_ID);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SYSTEM_ID, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_SYSTEM_ID);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p28
 * @since_tizen		3.0
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_NETWORK_ID)
 */
int utc_telephony_telephony_unset_noti_cb_p28(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_NETWORK_ID);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_NETWORK_ID, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_NETWORK_ID);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p29
 * @since_tizen		3.0
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_BS_ID)
 */
int utc_telephony_telephony_unset_noti_cb_p29(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_ID);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_ID, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_ID);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p30
 * @since_tizen		3.0
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_BS_LATITUDE)
 */
int utc_telephony_telephony_unset_noti_cb_p30(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_LATITUDE);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_LATITUDE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_LATITUDE);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p31
 * @since_tizen		3.0
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_NETWORK_BS_LONGITUDE)
 */
int utc_telephony_telephony_unset_noti_cb_p31(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_LONGITUDE);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_LONGITUDE, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_NETWORK_BS_LONGITUDE);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_p32
 * @since_tizen		4.0
 * @description		Positive test case for unsetting a callback function. (TELEPHONY_NOTI_MODEM_POWER_STATUS)
 */
int utc_telephony_telephony_unset_noti_cb_p32(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_MODEM_POWER_STATUS);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_set_noti_cb(telephony_handle, TELEPHONY_NOTI_MODEM_POWER_STATUS, _noti_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_noti_cb(telephony_handle, TELEPHONY_NOTI_MODEM_POWER_STATUS);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_n1
 * @since_tizen		2.3
 * @description		Negative test case for unsetting a callback function. (NULL input param)
 */
int utc_telephony_telephony_unset_noti_cb_n1(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(NULL, TELEPHONY_NOTI_SIM_STATUS);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_unset_noti_cb(NULL, TELEPHONY_NOTI_SIM_STATUS);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_unset_noti_cb_n2
 * @since_tizen		2.3
 * @description		Negative test case for unsetting a callback function. (invalid noti_id)
 */
int utc_telephony_telephony_unset_noti_cb_n2(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_noti_cb(telephony_handle, -1);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_unset_noti_cb(telephony_handle, -1);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_get_state_p
 * @since_tizen		2.4
 * @description		Positive test case for acquiring telephony state.
 */
int utc_telephony_get_state_p(void)
{
	int ret;
	int state = 0;

	if (g_telephony_common_supported == false) {
		ret = telephony_get_state(&state);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_get_state(&state);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_get_state_n
 * @since_tizen		2.4
 * @description		Negative test case for acquiring telephony state. (NULL input param)
 */
int utc_telephony_get_state_n(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_get_state(NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_get_state(NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_set_state_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive test case for setting a callback function to be invoked when the telephony state changed.
 */
int utc_telephony_set_state_changed_cb_p(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_state_changed_cb(_ready_state_cb, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_set_state_changed_cb(_ready_state_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_state_changed_cb(_ready_state_cb);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_set_state_changed_cb_n
 * @since_tizen		2.4
 * @description		Negative test case for setting a callback function to be invoked when the telephony state changed. (NULL input param)
 */
int utc_telephony_set_state_changed_cb_n(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_set_state_changed_cb(NULL, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_set_state_changed_cb(NULL, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_unset_state_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive test case for unsetting a callback function with telephony state.
 */
int utc_telephony_unset_state_changed_cb_p(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_state_changed_cb(_ready_state_cb);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_set_state_changed_cb(_ready_state_cb, NULL);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_unset_state_changed_cb(_ready_state_cb);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_unset_state_changed_cb_n
 * @since_tizen		2.4
 * @description		Negative test case for unsetting a callback function with telephony state. (NULL input param)
 */
int utc_telephony_unset_state_changed_cb_n(void)
{
	int ret;

	if (g_telephony_common_supported == false) {
		ret = telephony_unset_state_changed_cb(NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_unset_state_changed_cb(NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}
