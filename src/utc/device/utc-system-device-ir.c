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
#include <device/ir.h>
#include <system_info.h>

#define IR_FEATURE                      "http://tizen.org/feature/consumer_ir"
//& set: DeviceIR

bool ir_available;
/**
 * @function		utc_system_device_ir_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_device_ir_startup(void)
{
	int ret;
	ret = device_ir_is_available(&ir_available);
	if (ret < 0)
		ir_available = false;
}

/**
 * @testcase		utc_system_device_ir_is_available_p
 * @since_tizen		3.0
 * @description		Positive test case of device_ir_is_available()
 */
int utc_system_device_ir_is_available_p(void)
{
	bool val, ir_avail;
	int ret;

	ret = system_info_get_platform_bool(IR_FEATURE, &ir_avail);
	if(!ir_avail) {
		ret = device_ir_is_available(&val);
		assert_eq(ret, DEVICE_ERROR_NOT_SUPPORTED);
		return 0;
	}
	ret = device_ir_is_available(&val);
	assert_eq(ret, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_ir_is_available_n
 * @since_tizen		3.0
 * @description		Negative test case of device_ir_is_available()
 */
int utc_system_device_ir_is_available_n(void)
{
	int ret;
	ret = device_ir_is_available(NULL);
	assert_eq(ret, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_ir_transmit_p
 * @since_tizen		3.0
 * @description		Positive test case of device_ir_is_available()
 */
int utc_system_device_ir_transmit_p(void)
{
	int ret;
	int pattern[5] = {100, 200, 300, 400, 500};

	if (ir_available) {
		ret = device_ir_transmit(38000, pattern, 5);
		assert_eq(ret, DEVICE_ERROR_NONE);
		return 0;
	}
	ret = device_ir_transmit(38000, pattern, 5);
	assert_eq(ret, DEVICE_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_system_device_ir_transmit_n_1
 * @since_tizen		3.0
 * @description		Negative test case of device_ir_is_available()
 */
int utc_system_device_ir_transmit_n_1(void)
{
	int ret;
	int pattern[5] = {100, 200, 300, 400, 500};

	if (ir_available) {
		ret = device_ir_transmit(38000, pattern, 0);
		assert_eq(ret, DEVICE_ERROR_INVALID_PARAMETER);
		return 0;
	}
	ret = device_ir_transmit(38000, pattern, 0);
	assert_eq(ret, DEVICE_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_system_device_ir_transmit_n_2
 * @since_tizen		3.0
 * @description		Negative test case of device_ir_is_available()
 */
int utc_system_device_ir_transmit_n_2(void)
{
	int ret;

	if (ir_available) {
		ret = device_ir_transmit(38000, NULL, 4);
		assert_eq(ret, DEVICE_ERROR_INVALID_PARAMETER);
		return 0;
	}
	ret = device_ir_transmit(38000, NULL, 4);
	assert_eq(ret, DEVICE_ERROR_NOT_SUPPORTED);

	return 0;
}
