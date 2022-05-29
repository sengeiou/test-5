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

static bool g_telephony_call_supported = true;
static telephony_handle_list_s handle_list;
static telephony_h telephony_handle = NULL;

/**
 * @function		utc_telephony_call_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_telephony_call_startup(void)
{
	system_info_get_platform_bool("tizen.org/feature/network.telephony", &g_telephony_call_supported);
	if (g_telephony_call_supported) {
		if (telephony_init(&handle_list) == TELEPHONY_ERROR_NONE && handle_list.count > 0)
			telephony_handle = handle_list.handle[0];
	}
}

/**
 * @function		utc_telephony_call_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_telephony_call_cleanup(void)
{
	if (g_telephony_call_supported) {
		telephony_deinit(&handle_list);
		telephony_handle = NULL;
	}
}

/**
 * @testcase		utc_telephony_telephony_call_get_preferred_voice_subscription_p
 * @since_tizen		2.4
 * @description		Positive test case for getting the current value for the preferred voice call subscription.
 */
int utc_telephony_telephony_call_get_preferred_voice_subscription_p(void)
{
	telephony_call_preferred_voice_subs_e call_sub;
	int ret;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_preferred_voice_subscription(telephony_handle, &call_sub);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_call_get_preferred_voice_subscription(telephony_handle, &call_sub);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_preferred_voice_subscription_n1
 * @since_tizen		2.4
 * @description		Negative test case for getting the current value for the preferred voice call subscription. (NULL 'handle' param)
 */
int utc_telephony_telephony_call_get_preferred_voice_subscription_n1(void)
{
	telephony_call_preferred_voice_subs_e call_sub;
	int ret;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_preferred_voice_subscription(NULL, &call_sub);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_preferred_voice_subscription(NULL, &call_sub);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_preferred_voice_subscription_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting the current value for the preferred voice call subscription. (NULL 'call_sub' param)
 */
int utc_telephony_telephony_call_get_preferred_voice_subscription_n2(void)
{
	int ret;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_preferred_voice_subscription(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_preferred_voice_subscription(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_call_list_p
 * @since_tizen		2.4
 * @description		Positive test case for getting the list of the current call.
 */
int utc_telephony_telephony_call_get_call_list_p(void)
{
	telephony_call_h *call_list;
	unsigned int count;
	int ret;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_call_list(telephony_handle, &count, &call_list);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_call_get_call_list(telephony_handle, &count, &call_list);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_call_list_n1
 * @since_tizen		2.4
 * @description		Negative test case for getting the list of the current call. (NULL 'handle' param)
 */
int utc_telephony_telephony_call_get_call_list_n1(void)
{
	telephony_call_h *call_list;
	unsigned int count;
	int ret;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_call_list(NULL, &count, &call_list);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_call_list(NULL, &count, &call_list);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_call_list_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting the list of the current call. (NULL 'count' param)
 */
int utc_telephony_telephony_call_get_call_list_n2(void)
{
	telephony_call_h *call_list;
	unsigned int ret;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_call_list(telephony_handle, NULL, &call_list);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_call_list(telephony_handle, NULL, &call_list);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_call_list_n3
 * @since_tizen		2.4
 * @description		Negative test case for getting the list of the current call. (NULL 'call_list' param)
 */
int utc_telephony_telephony_call_get_call_list_n3(void)
{
	int ret;
	unsigned int count;
	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_call_list(telephony_handle, &count, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_call_list(telephony_handle, &count, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_release_call_list_p
 * @since_tizen		2.4
 * @description		Positive test case for releasing the list allocated from telephony_call_get_call_list().
 */
int utc_telephony_telephony_call_release_call_list_p(void)
{
	int ret;
	telephony_call_h *call_list;
	unsigned int count = 0;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_release_call_list(count, &call_list);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_call_list(telephony_handle, &count, &call_list);
	assert_eq(ret, TELEPHONY_ERROR_NONE);

	ret = telephony_call_release_call_list(count, &call_list);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_release_call_list_n
 * @since_tizen		2.4
 * @description		Negative test case for releasing the list allocated from telephony_call_get_call_list(). (NULL 'call_list' param)
 */
int utc_telephony_telephony_call_release_call_list_n(void)
{
	int ret;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_release_call_list(0, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_release_call_list(0, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_handle_id_n1
 * @since_tizen		2.4
 * @description		Negative test case for getting the call handle ID. (NULL 'handle' param)
 */
int utc_telephony_telephony_call_get_handle_id_n1(void)
{
	int ret;
	unsigned int handle_id;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_handle_id(NULL, &handle_id);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_handle_id(NULL, &handle_id);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_handle_id_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting the call handle ID. (NULL 'handle_id' param)
 */
int utc_telephony_telephony_call_get_handle_id_n2(void)
{
	int ret;
	telephony_call_h call_handle = NULL;

	call_handle = calloc(1, sizeof(int)); // garbage data

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_handle_id(call_handle, NULL);
		free(call_handle);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_handle_id(call_handle, NULL);
	free(call_handle);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_number_n1
 * @since_tizen		2.4
 * @description		Negative test case for getting the call number. (NULL 'handle' param)
 */
int utc_telephony_telephony_call_get_number_n1(void)
{
	int ret;
	char *number;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_number(NULL, &number);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_number(NULL, &number);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_number_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting the call number. (NULL 'number' param)
 */
int utc_telephony_telephony_call_get_number_n2(void)
{
	int ret;
	telephony_call_h call_handle = NULL;

	call_handle = calloc(1, sizeof(int)); // garbage data

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_number(call_handle, NULL);
		free(call_handle);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_number(call_handle, NULL);
	free(call_handle);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_type_n1
 * @since_tizen		2.4
 * @description		Negative test case for getting the call type. (NULL 'handle' param)
 */
int utc_telephony_telephony_call_get_type_n1(void)
{
	int ret;
	telephony_call_type_e type;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_type(NULL, &type);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_type(NULL, &type);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_type_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting the call type. (NULL 'type' param)
 */
int utc_telephony_telephony_call_get_type_n2(void)
{
	int ret;
	telephony_call_h call_handle = NULL;

	call_handle = calloc(1, sizeof(int)); // garbage data

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_type(call_handle, NULL);
		free(call_handle);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_type(call_handle, NULL);
	free(call_handle);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_status_n1
 * @since_tizen		2.3
 * @description		Negative test case for getting the call status. (NULL 'handle' param)
 */
int utc_telephony_telephony_call_get_status_n1(void)
{
	int ret;
	telephony_call_status_e status;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_status(NULL, &status);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_status(NULL, &status);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_status_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting the call status. (NULL 'status' param)
 */
int utc_telephony_telephony_call_get_status_n2(void)
{
	int ret;
	telephony_call_h call_handle = NULL;

	call_handle = calloc(1, sizeof(int)); // garbage data

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_status(call_handle, NULL);
		free(call_handle);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_status(call_handle, NULL);
	free(call_handle);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_direction_n1
 * @since_tizen		2.4
 * @description		Negative test case for getting whether the call is MO call or MT. (NULL 'handle' param)
 */
int utc_telephony_telephony_call_get_direction_n1(void)
{
	int ret;
	telephony_call_direction_e direction;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_direction(NULL, &direction);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_direction(NULL, &direction);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_direction_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting whether the call is MO call or MT. (NULL 'direction' param)
 */
int utc_telephony_telephony_call_get_direction_n2(void)
{
	int ret;
	telephony_call_h call_handle = NULL;

	call_handle = calloc(1, sizeof(int)); // garbage data

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_direction(call_handle, NULL);
		free(call_handle);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_direction(call_handle, NULL);
	free(call_handle);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_conference_status_n1
 * @since_tizen		2.4
 * @description		Negative test case for getting whether the call is conference call or not. (NULL 'handle' param)
 */
int utc_telephony_telephony_call_get_conference_status_n1(void)
{
	int ret;
	bool conf_status;

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_conference_status(NULL, &conf_status);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_conference_status(NULL, &conf_status);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_call_get_conference_status_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting whether the call is conference call or not. (NULL 'conference_status' param)
 */
int utc_telephony_telephony_call_get_conference_status_n2(void)
{
	int ret;
	telephony_call_h call_handle = NULL;

	call_handle = calloc(1, sizeof(int)); // garbage data

	if (g_telephony_call_supported == false) {
		ret = telephony_call_get_conference_status(call_handle, NULL);
		free(call_handle);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_call_get_conference_status(call_handle, NULL);
	free(call_handle);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}
