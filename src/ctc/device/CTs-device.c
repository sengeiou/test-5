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
#include "CTs-device-common.h"

/** @addtogroup ctc-device
* @ingroup		ctc
* @{
*/

//& set: Device

/**
* @function 		CTs_device_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_device_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_device_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_device_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	ctc-device-testcases
* @brief 		Integration testcases for module device
* @ingroup		ctc-device
* @{
*/

//& purpose: To play and stop the custom effect of front LED
//& type: auto
/**
* @testcase			CTc_device_check_led_feature_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @scenario			Check if the led feature is supported\n
*					Play the custom effect of front led\n
*					Stop the custom effect of front led
* @apicovered		device_led_play_custom, device_led_stop_custom
* @passcase			When device_led_play_custom and device_led_stop_custom are successful.
* @failcase			If target api device_led_play_custom and device_led_stop_custom or any precondition api fails.
* @precondition		NA
* @postcondition	NA
*/
int CTc_device_check_led_feature_p(void)
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
		nRet = device_led_play_custom(on, off, color, flags[enum_counter]);
		if ( bIsLedFeatureSupported )
		{
			if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s] device_led_play_custom returned TIZEN_ERROR_NOT_SUPPORTED for supported LED feature with flag = %s\\n",
					__LINE__, API_NAMESPACE, DeviceGetLedFlag(enum_counter));
				return 1;
			}
			else if ( nRet != DEVICE_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] device_led_play_custom returned %s for supported LED feature with flag = %s\\n",
					__LINE__, API_NAMESPACE, DeviceGetError(nRet), DeviceGetLedFlag(enum_counter));
				return 1;
			}
		}
		else
		{
			if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s] device_led_play_custom returned TIZEN_ERROR_NOT_SUPPORTED for unsupported LED feature with flag = %s\\n",
					__LINE__, API_NAMESPACE, DeviceGetLedFlag(enum_counter));
			}
			else
			{
				FPRINTF("[Line : %d][%s] device_led_play_custom returned %s for unsupported LED feature with flag = %s\\n",
					__LINE__, API_NAMESPACE, DeviceGetError(nRet), DeviceGetLedFlag(enum_counter));
				return 1;
			}
		}

		usleep(5000);

		nRet = device_led_stop_custom();
		if ( bIsLedFeatureSupported )
		{
			if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s] device_led_stop_custom returned TIZEN_ERROR_NOT_SUPPORTED for supported LED feature with flag = %s\\n",
					__LINE__, API_NAMESPACE, DeviceGetLedFlag(enum_counter));
				return 1;
			}
			else if ( nRet != DEVICE_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] device_led_stop_custom returned %s for supported LED feature with flag = %s\\n",
					__LINE__, API_NAMESPACE, DeviceGetError(nRet), DeviceGetLedFlag(enum_counter));
				return 1;
			}
		}
		else
		{
			if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s] device_led_stop_custom returned TIZEN_ERROR_NOT_SUPPORTED for unsupported LED feature with flag = %s\\n",
					__LINE__, API_NAMESPACE, DeviceGetLedFlag(enum_counter));
			}
			else
			{
				FPRINTF("[Line : %d][%s] device_led_stop_custom returned %s for unsupported LED feature with flag = %s\\n",
					__LINE__, API_NAMESPACE, DeviceGetError(nRet), DeviceGetLedFlag(enum_counter));
				return 1;
			}
		}
	}
	return 0;
}

/** @} */ //end of ctc-device
/** @} */ //end of ctc-device-testcases