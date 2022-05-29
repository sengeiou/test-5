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
static bool bIsDisplayFeatureSupported;
static bool bIsDisplayStateFeatureSupported;

/**
* @function 		ITs_device_power_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_power_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif
	bIsDisplayFeatureSupported = false;
	IS_FEATURE_SUPPORTED(DISPLAY_FEATURE_MAIN, bIsDisplayFeatureSupported, API_NAMESPACE);

	bIsDisplayStateFeatureSupported = false;
	IS_FEATURE_SUPPORTED(DISPLAY_STATE_FEATURE, bIsDisplayStateFeatureSupported, API_NAMESPACE);
	return;
}

/**
* @function 		ITs_device_power_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_power_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-device-power-testcases
*  @brief 		Integration testcases for module device-power
*  @ingroup 	itc-device-power
*  @{
*/

//& purpose Locks a given power state for a specified time then gets the power state and unlocks it
//& type: auto
/**
* @testcase 		ITc_device_power_request_release_lock_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		Locks & Gets the current power state and then unlocks it.
* @scenario			Lock a given power state for a specified time\n
*					Unlocks the power lock\n
* 					Get the current power state
* @apicovered		device_power_request_lock, device_power_release_lock
* @passcase			if Locks and Unlocks the valid power state successfully
* @failcase			if Failed to Lock or Unlock and Get the valid power state
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_power_request_release_lock_p(void)
{
	START_TEST;

	power_lock_e power_locks[] = { POWER_LOCK_CPU, POWER_LOCK_DISPLAY, POWER_LOCK_DISPLAY_DIM };
	int enum_size = sizeof(power_locks) / sizeof(power_locks[0]);
	int enum_counter = 0;

	if ((bIsDisplayFeatureSupported == false) || (bIsDisplayStateFeatureSupported == false))
		return 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++)
	{
		// Target API
		int nRet = device_power_request_lock(power_locks[enum_counter], 10);
		if ( nRet != DEVICE_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] device_power_request_lock failed for enum = %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, DeviceGetPowerLock(power_locks[enum_counter]), DeviceGetError(nRet));
			return 1;
		}

		// Target API
		nRet  = device_power_release_lock(power_locks[enum_counter]);
		if ( nRet != DEVICE_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] device_power_release_lock failed for enum = %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, DeviceGetPowerLock(power_locks[enum_counter]), DeviceGetError(nRet));
			return 1;
		}
	}

	return 0;
}

//& purpose Changes the current power state to normal/dim state
//& type: auto
/**
* @testcase 		ITc_power_wakeup_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		Changes the current power state to normal/dim state
* @scenario			Change the current power state
* @apicovered		device_power_wakeup
* @passcase			if device_power_wakeup is successfully
* @failcase			if device_power_wakeup Failed
* @precondition		NA
* @postcondition	The device will be in POWER_STATE_NORMAL state.
*/
int ITc_power_wakeup_p(void)
{
	START_TEST;

	// Target API
	int nRet = device_power_wakeup(false);
	if (bIsDisplayStateFeatureSupported == false)
	{
		assert_eq(nRet, DEVICE_ERROR_NOT_SUPPORTED);
		return 0;
	}
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_power_wakeup", DeviceGetError(nRet));

	return 0;
}
/** @} */
/** @} */
