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
#include <device/led.h>
#include <tizen.h>
#include <system_info.h>

//& set: DeviceLed

/**
 * @testcase		utc_system_device_flash_get_max_brightness_p
 * @since_tizen		2.3
 * @description		Positive test case of device_flash_get_max_brightness.
 */
int utc_system_device_flash_get_max_brightness_p(void)
{
	int max, error;
    bool is_supported;
    system_info_get_platform_bool("http://tizen.org/feature/camera.back.flash",&is_supported);

	error = device_flash_get_max_brightness(&max);

    if(is_supported == true)
	{
        assert_eq(error, DEVICE_ERROR_NONE);
	}
	else
	{
		assert_eq(error,DEVICE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_system_device_flash_get_max_brightness_n
 * @since_tizen		2.3
 * @description		Negative test case of device_flash_get_max_brightness.
 */
int utc_system_device_flash_get_max_brightness_n(void)
{
	int error;
    bool is_supported;
    system_info_get_platform_bool("http://tizen.org/feature/camera.back.flash",&is_supported);

	error = device_flash_get_max_brightness(NULL);
    if(is_supported == true)
	{
        assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error,DEVICE_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_flash_get_brightness_p
 * @since_tizen		2.3
 * @description		Positive test case of device_flash_get_brightness.
 */
int utc_system_device_flash_get_brightness_p(void)
{
	int brightness, error;
    bool is_supported;
    system_info_get_platform_bool("http://tizen.org/feature/camera.back.flash",&is_supported);

	error = device_flash_get_brightness(&brightness);
    if(is_supported == true)
	{
        assert_eq(error, DEVICE_ERROR_NONE);
	}
	else
	{
		assert_eq(error,DEVICE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_system_device_flash_get_brightness_n
 * @since_tizen		2.3
 * @description		Negative test case of device_flash_get_brightness.
 */
int utc_system_device_flash_get_brightness_n(void)
{
	int error;
    bool is_supported;
    system_info_get_platform_bool("http://tizen.org/feature/camera.back.flash",&is_supported);

	error = device_flash_get_brightness(NULL);

    if(is_supported == true)
	{
	    assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error,DEVICE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_system_device_flash_set_brightness_p
 * @since_tizen		2.3
 * @description		Positive test case of device_flash_set_brightness.
 */
int utc_system_device_flash_set_brightness_p(void)
{
	int max, error;
    bool is_supported;
    system_info_get_platform_bool("http://tizen.org/feature/camera.back.flash",&is_supported);

	device_flash_get_max_brightness(&max);
	error = device_flash_set_brightness(max);

    if(is_supported == true)
	{
		assert_eq(error, DEVICE_ERROR_NONE);
		device_flash_set_brightness(0);
	}
	else
	{
		assert_eq(error,DEVICE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_system_device_flash_set_brightness_n
 * @since_tizen		2.3
 * @description		Negative test case of device_flash_set_brightness.
 */
int utc_system_device_flash_set_brightness_n(void)
{
	int error;
    bool is_supported;
    system_info_get_platform_bool("http://tizen.org/feature/camera.back.flash",&is_supported);

	error = device_flash_set_brightness(-1);

    if(is_supported == true)
	{
		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error,DEVICE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_system_device_led_play_custom_p
 * @since_tizen		2.3
 * @description		Positive test case of device_led_play_custom()
 */
int utc_system_device_led_play_custom_p(void)
{
	int error;
    bool is_supported;

    system_info_get_platform_bool("http://tizen.org/feature/led",&is_supported);

    error = device_led_play_custom(500, 500, 0xFFFF00, LED_CUSTOM_DUTY_ON);
    if(is_supported == true)
	{
		assert_eq(error, DEVICE_ERROR_NONE);
		device_led_stop_custom();
	}
	else
	{
		assert_eq(error,DEVICE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_system_device_led_play_custom_n_1
 * @since_tizen		2.3
 * @description		Negative test case of device_led_play_custom()
 */
int utc_system_device_led_play_custom_n_1(void)
{
	int error;

    bool is_supported;

    system_info_get_platform_bool("http://tizen.org/feature/led",&is_supported);

    error = device_led_play_custom(-1, 500, 0xFFFF00FF, LED_CUSTOM_DUTY_ON);
    if(is_supported == true)
	{
		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error,DEVICE_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_led_play_custom_n2
 * @since_tizen		2.3
 * @description		Negative test case of device_led_play_custom()
 */
int utc_system_device_led_play_custom_n2(void)
{
	int error;
    bool is_supported;

    system_info_get_platform_bool("http://tizen.org/feature/led",&is_supported);
    error = device_led_play_custom(500, -1, 0xFFFF00FF, LED_CUSTOM_DUTY_ON);

    if(is_supported == true)
	{
		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error,DEVICE_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_led_stop_custom_p
 * @since_tizen		2.3
 * @description		Positive test case of device_led_stop_custom()
 */
int utc_system_device_led_stop_custom_p(void)
{
	int error;
	bool is_supported;

    system_info_get_platform_bool("http://tizen.org/feature/led",&is_supported);

    device_led_play_custom(500, 500, 0xFFFF00, LED_CUSTOM_DUTY_ON);
    error = device_led_stop_custom();

    if(is_supported == true)
	{
		assert_eq(error, DEVICE_ERROR_NONE);
	}
	else
	{
		assert_eq(error,DEVICE_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_led_stop_custom_n
 * @since_tizen		2.3
 * @description		Negative test case of device_led_stop_custom()
 */
int utc_system_device_led_stop_custom_n(void)
{
	int error;
    bool is_supported;

    system_info_get_platform_bool("http://tizen.org/feature/led",&is_supported);
    error = device_led_stop_custom();
    if(is_supported == true)
	{
		assert_eq(error, DEVICE_ERROR_OPERATION_FAILED);
	}
	else
	{
		assert_eq(error,DEVICE_ERROR_NOT_SUPPORTED);
	}



	return 0;
}
