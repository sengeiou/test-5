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
#include "ITs-device-common.h"

/** @addtogroup itc-device
*  @ingroup itc
*  @{
*/


//& set: Device

/**
* @function 		ITs_device_led_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_device_led_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function 		ITs_device_led_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_device_led_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}


/** @addtogroup itc-device-flash-led
*  @brief 		Integration testcases for module device-led
*  @ingroup 	itc-device-led
*  @{
*/

//& purpose: To get maximum brightness value of camera flash LED
//& type: auto
/**
* @testcase 		ITc_device_flash_get_max_brightness_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		To get maximum brightness value of camera flash LED 
* @scenario			Get the maximum brightness value 
* @apicovered		device_flash_get_max_brightness				
* @passcase			When device_flash_get_max_brightness is successful
* @failcase			If target API device_flash_get_max_brightness any precondition API fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_flash_get_max_brightness_p(void)
{
	START_TEST;

	int nMaximumBrightness = -1;
	bool bIsDisplayFeatureSupported = false;
	IS_FEATURE_SUPPORTED(DISPLAY_FEATURE, bIsDisplayFeatureSupported, API_NAMESPACE);

	// Target API
	int nRet = device_flash_get_max_brightness(&nMaximumBrightness);

	if ( !bIsDisplayFeatureSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] device_flash_get_max_brightness failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s\\n",
				__LINE__, API_NAMESPACE, DeviceGetError(nRet));
			return 1;
		}

		FPRINTF("[Line : %d][%s] device_flash_get_max_brightness is unsupported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_flash_get_max_brightness", DeviceGetError(nRet));

	if ( 0 > nMaximumBrightness )
	{
		FPRINTF("[Line : %d][%s] device_flash_get_max_brightness return invalid value = %d\\n",
			__LINE__, API_NAMESPACE, nMaximumBrightness);
		return 1;
	}

	return 0;
}

//& purpose: To set and get the brightness value of the camera flash LED
//& type: auto
/**
* @testcase 		ITc_device_flash_set_get_brightness_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		To set and get the brightness value of the camera flash LED
* @scenario			Set the brightness value\n
*					Invoke the callback\n
*					Get the brightness value\n
*					Compare set and get
* @apicovered		device_flash_set_brightness, device_flash_get_brightness
* @passcase			When device_flash_set_brightness and device_flash_get_brightness are successful
* @failcase			If target API device_flash_set_brightness and device_flash_get_brightness or any precondition API fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_flash_set_get_brightness_p(void)
{
	START_TEST;

	int nSetBrightness = 0;
	int nGetBrightness;
	bool bIsDisplayFeatureSupported = false;
	IS_FEATURE_SUPPORTED(DISPLAY_FEATURE, bIsDisplayFeatureSupported, API_NAMESPACE);

	// Target API
	int nRet = device_flash_set_brightness(nSetBrightness);
	if ( !bIsDisplayFeatureSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] device_flash_set_brightness failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s\\n",
				__LINE__, API_NAMESPACE, DeviceGetError(nRet));
			return 1;
		}

		FPRINTF("[Line : %d][%s] device_flash_set_brightness is unsupported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_flash_set_brightness", DeviceGetError(nRet));

	usleep(2000);

	// Target API
	nRet = device_flash_get_brightness(&nGetBrightness);
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_flash_get_brightness", DeviceGetError(nRet));

	if (nSetBrightness != nGetBrightness)
	{
		FPRINTF("[Line : %d][%s] Set/Get brightness values of flash LED mismatched\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: To play and stop the custom effect of front LED
//& type: auto
/**
* @testcase 		ITc_device_led_play_stop_custom_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		To play and stop the custom effect on front LED
* @scenario			Play the custom effect of front led\n
*					Stop the custom effect of front led
* @apicovered		device_led_play_custom, device_led_stop_custom
* @passcase			When device_led_play_custom and device_led_stop_custom are successful
* @failcase			If target API device_led_play_custom and device_led_stop_custom or any precondition API fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_led_play_stop_custom_p(void)
{
	START_TEST;

	bool bIsLedFeatureSupported = false;
	IS_FEATURE_SUPPORTED(LED_FEATURE, bIsLedFeatureSupported, API_NAMESPACE);

	int nRet = 0;
	int on = 1000;						//Turn on time in milliseconds
	int off = 1000;						//Turn off time in milliseconds
	unsigned int color = 0xFF101010;	//Color value
	unsigned int flags[] = { LED_CUSTOM_DUTY_ON, LED_CUSTOM_DEFAULT };	//LED_CUSTOM_FLAGS

	int enum_size = sizeof(flags) / sizeof(flags[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		// Target API
		nRet = device_led_play_custom(on, off, color, flags[enum_counter]);
		if ( !bIsLedFeatureSupported )
		{
			if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s] device_led_play_custom failed to return TIZEN_ERROR_NOT_SUPPORTED for flag = %s, error returned = %s\\n",
					__LINE__, API_NAMESPACE, DeviceGetLedFlag(flags[enum_counter]), DeviceGetError(nRet));
				return 1;
			}

			FPRINTF("[Line : %d][%s] device_led_play_custom is unsupported for flag = %s. Skipping test\\n",
				__LINE__, API_NAMESPACE, DeviceGetLedFlag(flags[enum_counter]));
			continue;
		}

		if ( nRet != DEVICE_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] device_led_play_custom failed for flag = %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, DeviceGetLedFlag(flags[enum_counter]), DeviceGetError(nRet));
			return 1;
		}

		usleep(5000);

		// Target API
		nRet = device_led_stop_custom();
		if ( nRet != DEVICE_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] device_led_stop_custom failed for flag = %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, DeviceGetLedFlag(flags[enum_counter]), DeviceGetError(nRet));
			return 1;
		}
	}

	return 0;
}

/** @} */
/** @} */
