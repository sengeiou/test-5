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
static bool bIsDisplayStateFeatureSupported;
static bool bIsDisplayFeatureSupported;

/**
* @function 		ITs_device_display_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_display_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif
	bIsDisplayStateFeatureSupported = false;
	bIsDisplayFeatureSupported = false;
	IS_FEATURE_SUPPORTED(DISPLAY_STATE_FEATURE, bIsDisplayStateFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(DISPLAY_FEATURE_MAIN, bIsDisplayFeatureSupported, API_NAMESPACE);

	return;
}

/**
* @function 		ITs_device_display_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_display_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-device-display-testcases
*  @brief 		Integration testcases for module device-display
*  @ingroup itc-device-display
*  @{
*/


//& purpose: To get the number of display devices
//& type: auto
/**
* @testcase 		ITc_device_display_get_numbers_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		To get the number of display devices 
* @scenario			Get the number of devices that display provides
* @apicovered		device_display_get_numbers				
* @passcase			When device_display_get_numbers is successful
* @failcase			If target API device_display_get_numbers any precondition API fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_display_get_numbers_p(void)
{
	START_TEST;
	int nDeviceNumber;

	// Target API
	int nRet = device_display_get_numbers(&nDeviceNumber);
        if (false == bIsDisplayFeatureSupported)
        {
                PRINT_RESULT(DEVICE_ERROR_NOT_SUPPORTED, nRet, "device_display_get_numbers", DeviceGetError(nRet));
                return 0;
        }
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_display_get_numbers", DeviceGetError(nRet));
	CHECK_VALUE_INT(nDeviceNumber, "device_display_get_numbers");
	return 0;
}

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)  || defined(TV)) //Starts MOBILE or WEARABLE or TIZENIOT

//& purpose: To get the maximum brightness value that can be set
//& type: auto
/**
* @testcase 		ITc_device_display_get_max_brightness_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		To get the maximum brightness value that can be set
* @scenario			Get the maximum brightness value
* @apicovered		device_display_get_max_brightness				
* @passcase			When device_display_get_max_brightness is successful
* @failcase			If target API device_display_get_max_brightness any precondition API fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_display_get_max_brightness_p(void)
{
	START_TEST;

	int nDisplayIndex = 0;
	int nMaximumBrightness = 0;

	// Target API
	int nRet = device_display_get_max_brightness(nDisplayIndex, &nMaximumBrightness);
        if (false == bIsDisplayFeatureSupported)
        {
                PRINT_RESULT(DEVICE_ERROR_NOT_SUPPORTED, nRet, "device_display_get_max_brightness", DeviceGetError(nRet));
                return 0;
        }
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_display_get_max_brightness", DeviceGetError(nRet));

	if ( nMaximumBrightness < 0 )
	{
		FPRINTF("[Line : %d][%s] device_display_get_brightness returned invalid value = %d\\n", __LINE__, API_NAMESPACE, nMaximumBrightness);
		return 1;
	}

	return 0;
}

//& purpose: To set and get the display brightness value
//& type: auto
/**
* @testcase 		ITc_device_display_set_get_brightness_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		To set and get the display brightness value
* @scenario			Set the display index\n
*					Get value of display brightness
* @apicovered		device_display_set_brightness, device_display_get_brightness, device_display_get_max_brightness
* @passcase			When device_display_set_brightness and device_display_get_brightness are successful
* @failcase			If target API device_display_set_brightness or device_display_get_brightness or any precondition API fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_display_set_get_brightness_p(void)
{
	START_TEST;
	int nDisplayIndex = 0;
	int nMaximumBrightness = 0;

	//Precondition
	int nRet = device_display_get_max_brightness(nDisplayIndex, &nMaximumBrightness);
        if (false == bIsDisplayFeatureSupported)
        {
                PRINT_RESULT(DEVICE_ERROR_NOT_SUPPORTED, nRet, "device_display_get_max_brightness", DeviceGetError(nRet));
                return 0;
        }
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_display_get_max_brightness", DeviceGetError(nRet));
	CHECK_VALUE_INT(nMaximumBrightness, "device_display_get_max_brightness");

	int nSetBrightness = nMaximumBrightness;
	int nGetBrigntness = 0;

	// Target API
	nRet = device_display_set_brightness(nDisplayIndex, nSetBrightness);
	if (nRet == DEVICE_ERROR_NOT_SUPPORTED)
		return 0;
	else
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_display_set_brightness", DeviceGetError(nRet));

	// Target API
	nRet = device_display_get_brightness(nDisplayIndex, &nGetBrigntness);
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_display_get_brightness", DeviceGetError(nRet));

	if ( nGetBrigntness != nSetBrightness )
	{
		FPRINTF("[Line : %d][%s] Set/Get brightness values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
#endif  // End MOBILE or WEARABLE or TIZENIOT

//& purpose: To change and get the display state
//& type: auto
/**
* @testcase 		ITc_device_display_change_get_state_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		To change and get the display state
* @scenario			Change the display state\n
*					Get the display state
* @apicovered		device_display_change_state, device_display_get_state
* @passcase			When device_display_change_state and device_display_get_state are successful
* @failcase			If target API device_display_change_state or device_display_get_state or any precondition API fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_display_change_get_state_p(void)
{
	START_TEST;

	display_state_e getDisplayState;
#if (defined(MOBILE) || defined(TIZENIOT)) //Starts MOBILE or TIZENIOT
	display_state_e display_states[] = { DISPLAY_STATE_NORMAL,DISPLAY_STATE_SCREEN_DIM,DISPLAY_STATE_SCREEN_OFF};
#endif   // End MOBILE or TIZENIOT
#if defined(TV) || defined(WEARABLE)
	display_state_e display_states[] = { DISPLAY_STATE_NORMAL,DISPLAY_STATE_SCREEN_OFF};
#endif
	int enum_size = sizeof(display_states) / sizeof(display_states[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++)
	{
		// Target API
		int nRet = device_display_change_state(display_states[enum_counter]);
		if (false == bIsDisplayFeatureSupported)
		{
			PRINT_RESULT(DEVICE_ERROR_NOT_SUPPORTED, nRet, "device_display_change_state", DeviceGetError(nRet));
			return 0;
		}
		if (bIsDisplayStateFeatureSupported == false)
		{
			assert_eq(nRet, DEVICE_ERROR_NOT_SUPPORTED);
			return 0;
		}

		if ( nRet != DEVICE_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] device_display_change_state failed for enum = %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, DeviceGetDisplayState(display_states[enum_counter]), DeviceGetError(nRet));
			return 1;
		}

		sleep(1);
		// Target API
		nRet = device_display_get_state(&getDisplayState);
		if ( nRet != DEVICE_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] device_display_get_state failed for enum = %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, DeviceGetDisplayState(display_states[enum_counter]), DeviceGetError(nRet));
			return 1;
		}

		switch ( display_states[enum_counter] )
		{
			case DISPLAY_STATE_NORMAL:
				if ( getDisplayState != DISPLAY_STATE_NORMAL && getDisplayState != DISPLAY_STATE_SCREEN_DIM && getDisplayState != DISPLAY_STATE_SCREEN_OFF )
				{
					FPRINTF("[Line : %d][device_ITC] Set/Get brightness values mismatch \\n", __LINE__);
					return 1;
				}
				break;
			case DISPLAY_STATE_SCREEN_DIM:
				if ( getDisplayState != DISPLAY_STATE_SCREEN_DIM && getDisplayState != DISPLAY_STATE_SCREEN_OFF )
				{
					FPRINTF("[Line : %d][device_ITC] Set/Get brightness values mismatch \\n", __LINE__);
					return 1;
				}
				break;
			case DISPLAY_STATE_SCREEN_OFF:
				if ( getDisplayState != DISPLAY_STATE_SCREEN_OFF )
				{
					FPRINTF("[Line : %d][device_ITC] Set/Get brightness values mismatch \\n", __LINE__);
					return 1;
				}
				break;
			default:
				break;
		}
	}

	return 0;
}
/** @} */
/** @} */
