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

static bool g_telephony_modem_supported = true;
static telephony_handle_list_s handle_list;
static telephony_h telephony_handle = NULL;

/**
 * @function		utc_telephony_modem_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_telephony_modem_startup(void)
{
	system_info_get_platform_bool("tizen.org/feature/network.telephony", &g_telephony_modem_supported);
	if (g_telephony_modem_supported) {
		if (telephony_init(&handle_list) == TELEPHONY_ERROR_NONE && handle_list.count > 0)
			telephony_handle = handle_list.handle[0];
	}
}

/**
 * @function		utc_telephony_modem_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_telephony_modem_cleanup(void)
{
	if (g_telephony_modem_supported) {
		telephony_deinit(&handle_list);
		telephony_handle = NULL;
	}
}


/**
 * @testcase		utc_telephony_telephony_modem_get_power_status_p
 * @since_tizen		2.4
 * @description		Positive test case for getting the power status of the modem.
 */
int utc_telephony_telephony_modem_get_power_status_p(void)
{
	telephony_modem_power_status_e status;
	int ret;

	if (g_telephony_modem_supported == false) {
		ret = telephony_modem_get_power_status(telephony_handle, &status);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(telephony_handle);
	ret = telephony_modem_get_power_status(telephony_handle, &status);
	assert_eq(ret, TELEPHONY_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_modem_get_power_status_n1
 * @since_tizen		2.4
 * @description		Negative test case for getting the power status of the modem. (NULL 'handle' param)
 */
int utc_telephony_telephony_modem_get_power_status_n1(void)
{
	telephony_modem_power_status_e status;
	int ret;

	if (g_telephony_modem_supported == false) {
		ret = telephony_modem_get_power_status(NULL, &status);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_modem_get_power_status(NULL, &status);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_telephony_telephony_modem_get_power_status_n2
 * @since_tizen		2.4
 * @description		Negative test case for getting the power status of the modem. (NULL 'status' param)
 */
int utc_telephony_telephony_modem_get_power_status_n2(void)
{
	int ret;

	if (g_telephony_modem_supported == false) {
		ret = telephony_modem_get_power_status(telephony_handle, NULL);
		assert_eq(ret, TELEPHONY_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = telephony_modem_get_power_status(telephony_handle, NULL);
	assert_eq(ret, TELEPHONY_ERROR_INVALID_PARAMETER);
	return 0;
}

