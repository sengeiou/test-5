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
bool bIsHAPTICFeatureSupported;

//Add  related feature here
#define HAPTIC_FEATURE		"http://tizen.org/feature/feedback.vibration"

/**
* @function 		ITs_device_haptic_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_haptic_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif

	bIsHAPTICFeatureSupported = false;
	IS_FEATURE_SUPPORTED(HAPTIC_FEATURE, bIsHAPTICFeatureSupported, API_NAMESPACE);
	return;
}

/**
* @function 		ITs_device_haptic_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_haptic_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}


/** @addtogroup itc-device-haptic-testcases
*  @brief 		Integration testcases for module device-haptic
*  @ingroup itc-device-haptic
*  @{
*/

//& purpose: Vibrate for a specified time and stop
//& type: auto
/**
* @testcase 		ITc_device_haptic_vibrate_stop_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		Vibrate for a specified time and stop
* @scenario			Open haptic handle\n
*					Start haptic monotone\n
*					Stop haptic monotone\n
*					Close haptic handle
* @apicovered		device_haptic_open, device_haptic_vibrate, device_haptic_stop, device_haptic_close
* @passcase			When device_haptic_vibrate and haptic_stop_all_effects is successful
* @failcase			If target API fails or any precondition API fails
* @precondition		None
* @postcondition	None
*/
int ITc_device_haptic_vibrate_stop_p(void)
{
	START_TEST;

	int nDeviceCount;
	haptic_device_h hHapticDevice;

	//Precondition
	int nRet = device_haptic_get_count(&nDeviceCount);
	if(!bIsHAPTICFeatureSupported)
	{
		if (nRet != DEVICE_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] Feature mismatch\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else if(nRet == DEVICE_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] Feature Not supported\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_haptic_get_count", DeviceGetError(nRet));
	CHECK_VALUE_INT(nDeviceCount, "device_haptic_get_count");

	int nDeviceIndex = nDeviceCount - 1;
	nRet = device_haptic_open(nDeviceIndex, &hHapticDevice);
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_haptic_open", DeviceGetError(nRet));
	CHECK_HANDLE(hHapticDevice, "device_haptic_open");

	int nDuration = 20;
	int nFeedback = 50;	// 0~100
	haptic_effect_h pHapticEffect;

	// Target API
	nRet = device_haptic_vibrate(hHapticDevice, nDuration, nFeedback, &pHapticEffect);
	PRINT_RESULT_CLEANUP(DEVICE_ERROR_NONE, nRet, "device_haptic_vibrate", DeviceGetError(nRet), device_haptic_close(hHapticDevice));

	// Target API
	nRet = device_haptic_stop(hHapticDevice, pHapticEffect);
	PRINT_RESULT_CLEANUP(DEVICE_ERROR_NONE, nRet, "device_haptic_stop", DeviceGetError(nRet), device_haptic_close(hHapticDevice));

	//Postcondition
	nRet = device_haptic_close(hHapticDevice);
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_haptic_close", DeviceGetError(nRet));

	return 0;
}

//& purpose: Get the number of vibrators
//& type: auto
/**
* @testcase 		ITc_device_haptic_get_count_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		Gets the number of vibrators
* @scenario			Get the number of vibrators
* @apicovered		device_haptic_get_count
* @passcase			When device_haptic_get_count is successful
* @failcase			If device_haptic_get_count or any precondition API fails
* @precondition		None
* @postcondition	None
*/
int ITc_device_haptic_get_count_p(void)
{
	START_TEST;

	int nDeviceCount;
	// Target API
	int nRet = device_haptic_get_count(&nDeviceCount);
	if(!bIsHAPTICFeatureSupported)
	{
		if (nRet != DEVICE_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] Feature mismatch\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else if(nRet == DEVICE_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] Feature Not supported\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_haptic_get_count", DeviceGetError(nRet));
	CHECK_VALUE_INT(nDeviceCount, "device_haptic_get_count");

	return 0;
}

//& purpose: Open and close a haptic-vibration device
//& type: auto
/**
* @testcase 		ITc_device_haptic_open_close_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		Open and close a haptic-vibration device
* @scenario			Open haptic handle\n
*					Close haptic handle
* @apicovered		device_haptic_open, device_haptic_close, device_haptic_get_count				
* @passcase			When device_haptic_open and device_haptic_close is successful
* @failcase			If target API fails or any precondition API fails
* @precondition		None
* @postcondition	None
*/
int ITc_device_haptic_open_close_p(void)
{
	START_TEST;

	haptic_device_h hHapticDevice = NULL;

	//Precondition
	int nDeviceCount;
	int nRet = device_haptic_get_count(&nDeviceCount);
	if(!bIsHAPTICFeatureSupported)
	{
		if (nRet != DEVICE_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] Feature mismatch\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else if(nRet == DEVICE_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] Feature Not supported\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_haptic_get_count", DeviceGetError(nRet));
	CHECK_VALUE_INT(nDeviceCount, "device_haptic_get_count");

	int nDeviceIndex = nDeviceCount - 1;

	int nDuration = 20;
	int nFeedback = 50;	// 0~100
	haptic_effect_h pHapticEffect;

	// Target API
	nRet = device_haptic_open(nDeviceIndex, &hHapticDevice);
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_haptic_open", DeviceGetError(nRet));
	CHECK_HANDLE(hHapticDevice, "device_haptic_open");

	nRet = device_haptic_vibrate(hHapticDevice, nDuration, nFeedback, &pHapticEffect);

	// Target API
	nRet = device_haptic_close(hHapticDevice);
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_haptic_close", DeviceGetError(nRet));

	return 0;
}

/** @} */
/** @} */
