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

static bool g_ReturnValueState;
static bool g_bDeviceChangedCallback;
static bool bIsBATTERYFeatureSupported;
static bool bIsDisplayStateFeatureSupported;
static bool bIsDisplayFeatureSupported;
static bool bIsCameraFlashSupported;
static int nDeviceTimeoutId;

//Add  related feature here
#define BATTERY_FEATURE				"http://tizen.org/feature/battery"

/**
* @function 		ITs_device_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif

	bIsBATTERYFeatureSupported = false;
	bIsDisplayStateFeatureSupported = false;
	IS_FEATURE_SUPPORTED(BATTERY_FEATURE, bIsBATTERYFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(DISPLAY_STATE_FEATURE, bIsDisplayStateFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(DISPLAY_FEATURE_MAIN, bIsDisplayFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(DISPLAY_FEATURE, bIsCameraFlashSupported, API_NAMESPACE);
	return;
}

/**
* @function 		ITs_device_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function			DeviceChangedCallback
* @description		Called when the battery state changes.
* @parameter[OUT]	The device type to monitor
* @parameter[OUT]	The changed value
* @parameter[OUT]	The user data passed from the callback registration
* @return			NA
*/
void DeviceChangedCallback(device_callback_e type, void *value, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DeviceChangedCallback is called\\n", __LINE__, API_NAMESPACE);
#endif

	/* stop main loop */
	g_main_loop_quit(g_pDeviceMainLoop);

	g_ReturnValueState = false;
	g_bDeviceChangedCallback = true;

	int val = (int) value;
	switch ( type ) {
		case DEVICE_CALLBACK_BATTERY_CAPACITY:
			if ( val >= 0 ) {
				g_ReturnValueState = true;
			}
			break;
		case DEVICE_CALLBACK_BATTERY_LEVEL:
			switch ( val ) {
				case DEVICE_BATTERY_LEVEL_EMPTY:
				case DEVICE_BATTERY_LEVEL_CRITICAL:
				case DEVICE_BATTERY_LEVEL_LOW:
				case DEVICE_BATTERY_LEVEL_HIGH:
				case DEVICE_BATTERY_LEVEL_FULL:
					g_ReturnValueState = true;
					break;
				default:
					g_ReturnValueState = false;
					break;
			}
			break;
		case DEVICE_CALLBACK_BATTERY_CHARGING:
			if ( val == 0 || val == 1 ) {
				g_ReturnValueState = true;
			}
			break;
		case DEVICE_CALLBACK_DISPLAY_STATE:
			if ( val >= 0 ) {
				g_ReturnValueState = true;
			}
			break;
		case DEVICE_CALLBACK_FLASH_BRIGHTNESS:
			break;
		default:
			break;
	}

	return;
}

/**
* @function 		DeviceTimeout
* @description	 	Called if some callback is not invoked for a particular DeviceTimeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean DeviceTimeout(gpointer data)
{
	/* stop main loop */
	g_main_loop_quit( g_pDeviceMainLoop );

	nDeviceTimeoutId = 0;

	FPRINTF("[Line : %d][%s] Callback DeviceTimeout\\n", __LINE__, API_NAMESPACE);
	return false;
}

/** @addtogroup itc-device-testcases
*  @brief 		Integration testcases for module device
*  @ingroup 	itc-device
*  @{
*/

//& purpose: To add and remove the callback to observe device change status.
//& type: auto
/**
* @testcase 		ITc_device_add_remove_callback_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		To add and remove the callback to observe device change status.
* @scenario			Add the callback to observe device\n
*					Remove the callback
* @apicovered		device_add_callback, device_remove_callback
* @passcase			When device_add_callback and device_remove_callback is successful
* @failcase			If target api device_add_callback or device_remove_callback or any precondition api fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_add_remove_callback_p(void)
{
	START_TEST;

	device_callback_e callback_type[] = {

	#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) //Starts MOBILE or WEARABLE or TIZENIOT
		DEVICE_CALLBACK_BATTERY_CAPACITY,
		DEVICE_CALLBACK_BATTERY_LEVEL,
		DEVICE_CALLBACK_BATTERY_CHARGING,
		DEVICE_CALLBACK_FLASH_BRIGHTNESS,
	#endif  // End MOBILE or WEARABLE or TIZENIOT
		DEVICE_CALLBACK_DISPLAY_STATE
	};

	int enum_size = sizeof(callback_type) / sizeof(callback_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++)
	{
		if ((bIsBATTERYFeatureSupported == false) &&
			(callback_type[enum_counter] == DEVICE_CALLBACK_BATTERY_CAPACITY ||
			callback_type[enum_counter] == DEVICE_CALLBACK_BATTERY_LEVEL ||
			callback_type[enum_counter] == DEVICE_CALLBACK_BATTERY_CHARGING))
			continue;

		if (bIsCameraFlashSupported == false &&
			callback_type[enum_counter] == DEVICE_CALLBACK_FLASH_BRIGHTNESS)
			continue;

		if (bIsDisplayStateFeatureSupported == false &&
			callback_type[enum_counter] == DEVICE_CALLBACK_DISPLAY_STATE)
			continue;

		// Target API
		int nRet = device_add_callback(callback_type[enum_counter], DeviceChangedCallback, NULL);
		if ( nRet != DEVICE_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] device_add_callback failed for enum = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, DeviceGetCallbackType(callback_type[enum_counter]), DeviceGetError(nRet));
			return 1;
		}

		//Change display state when checking callback for DEVICE_CALLBACK_DISPLAY_STATE
		display_state_e display_state;
		if ( callback_type[enum_counter] == DEVICE_CALLBACK_DISPLAY_STATE )
		{
			g_bDeviceChangedCallback = false;
			g_ReturnValueState = false;

			//Get current display state
			device_display_get_state(&display_state);
#if (defined(MOBILE) || defined(TIZENIOT)) //Starts MOBILE or TIZENIOT
			display_state_e display_states[] = { DISPLAY_STATE_NORMAL, DISPLAY_STATE_SCREEN_DIM, DISPLAY_STATE_SCREEN_OFF };
#endif  // End MOBILE or TIZENIOT
#if defined(TV) || defined(WEARABLE)
			display_state_e display_states[] = { DISPLAY_STATE_NORMAL, DISPLAY_STATE_SCREEN_OFF };
#endif
			int states_size = sizeof(display_states) / sizeof(display_states[0]);
			int states_counter = 0;
			for ( states_counter = 0; states_counter < states_size; states_counter++ )
			{
				// Make change to the current display state
				//if ( display_state != display_states[states_counter] && device_display_change_state(display_states[states_counter]) == 0 )
				//{
				//	break;
				//}

				if ( display_state != display_states[states_counter] )
				{
					nRet = device_display_change_state(display_states[states_counter]);
					if (bIsDisplayStateFeatureSupported == false)
					{
						assert_eq(nRet, DEVICE_ERROR_NOT_SUPPORTED);
						return 0;
					}

					if ( nRet != DEVICE_ERROR_NONE )
					{
						FPRINTF("[Line : %d][%s] device_display_change_state failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DeviceGetError(nRet));
						device_remove_callback(callback_type[enum_counter], DeviceChangedCallback);
						return 1;
					}
				}
			}

			g_pDeviceMainLoop = g_main_loop_new(NULL, false);
			nDeviceTimeoutId = g_timeout_add(TIMEOUT_CB, DeviceTimeout, g_pDeviceMainLoop);
			g_main_loop_run(g_pDeviceMainLoop);
			g_main_loop_unref(g_pDeviceMainLoop);
			g_pDeviceMainLoop = NULL;
			if (nDeviceTimeoutId)
			{
				g_source_remove(nDeviceTimeoutId);
				nDeviceTimeoutId = 0;
			}

			if ( g_bDeviceChangedCallback == false )
			{
				FPRINTF("[Line : %d][%s] device_add_callback failed to invoke callback for enum = %s\\n", __LINE__, API_NAMESPACE, DeviceGetCallbackType(callback_type[enum_counter]));
				device_remove_callback(callback_type[enum_counter], DeviceChangedCallback);
				return 1;
			}
			else if (g_ReturnValueState == false)
			{
				FPRINTF("[Line : %d][%s] device_add_callback failed. Callback returned with invalid value for enum = %s\\n", __LINE__, API_NAMESPACE, DeviceGetCallbackType(callback_type[enum_counter]));
				device_remove_callback(callback_type[enum_counter], DeviceChangedCallback);
				return 1;
			}
		}

		// Target API
		nRet = device_remove_callback(callback_type[enum_counter], DeviceChangedCallback);
		if ( nRet != DEVICE_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] device_remove_callback failed for enum = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, DeviceGetCallbackType(callback_type[enum_counter]), DeviceGetError(nRet));
			return 1;
		}

		//Change display state when checking callback for DEVICE_CALLBACK_DISPLAY_STATE
		if ( callback_type[enum_counter] == DEVICE_CALLBACK_DISPLAY_STATE )
		{
			g_bDeviceChangedCallback = false;

			// Make change to the current display state
			nRet = device_display_change_state(display_state);
			if (bIsDisplayStateFeatureSupported == false)
			{
				assert_eq(nRet, DEVICE_ERROR_NOT_SUPPORTED);
				return 0;
			}

			if ( nRet != DEVICE_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] device_display_change_state failed for enum = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, DeviceGetCallbackType(callback_type[enum_counter]), DeviceGetError(nRet));
				return 1;
			}

			g_pDeviceMainLoop = g_main_loop_new(NULL, false);
			nDeviceTimeoutId = g_timeout_add(TIMEOUT_CB, DeviceTimeout, g_pDeviceMainLoop);
			g_main_loop_run(g_pDeviceMainLoop);
			g_main_loop_unref(g_pDeviceMainLoop);
			g_pDeviceMainLoop = NULL;
			if (nDeviceTimeoutId)
			{
				g_source_remove(nDeviceTimeoutId);
				nDeviceTimeoutId = 0;
			}

			if ( g_bDeviceChangedCallback == true )
			{
				FPRINTF("[Line : %d][%s] device_remove_callback. Callback invoked for enum = %s\\n", __LINE__, API_NAMESPACE, DeviceGetCallbackType(callback_type[enum_counter]));
				return 1;
			}
		}
	}

	return 0;
}

/** @} */
/** @} */
