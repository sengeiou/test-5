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
bool bIsBatteryFeatureSupported;

/** @addtogroup itc-device
*  @ingroup itc
*  @{
*/

//& set: Device
bool g_bDeviceBatteryLevelCallback;
bool g_bDeviceBatteryWarnCallback;
bool g_bDeviceBatteryCallback;
bool g_bDeviceBatteryRemainingTimeChangedCallback;

//Add  related feature here
#define BATTERY_FEATURE				"http://tizen.org/feature/battery"

/**
* @function 		ITs_device_battery_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_battery_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	bIsBatteryFeatureSupported = false;
        IS_FEATURE_SUPPORTED(BATTERY_FEATURE, bIsBatteryFeatureSupported, API_NAMESPACE);

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_device_battery_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_battery_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-device-battery-testcases
*  @brief 		Integration testcases for module device-battery
*  @ingroup 	itc-device-battery
*  @{
*/


//& purpose: To get the battery charge percentage. 
//& type: auto
/**
* @testcase 		ITc_device_battery_get_percent_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		To get the battery charge percentage. 
* @scenario			Get the percentage of battery
* @apicovered		device_battery_get_percent
* @passcase			When device_battery_get_percent is successful
* @failcase			If target API device_battery_get_percent any precondition API fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_battery_get_percent_p(void)
{
	START_TEST;

	int nPercent = 0;

	// Target API
	int nRet = device_battery_get_percent(&nPercent);
	if(!bIsBatteryFeatureSupported)
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
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_battery_get_percent", DeviceGetError(nRet));

	if ( nPercent < 0  || nPercent > 100 )
	{
		FPRINTF("[Line : %d][%s] device_battery_get_percent returned invalid value = %d\\n", __LINE__, API_NAMESPACE, nPercent);
		return 1;
	}

	return 0;
}

//& purpose: To check whether the battery is fully charged.
//& type: auto
/**
* @testcase 		ITc_device_battery_is_charging_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		To check whether the battery is fully charged. 
* @scenario			Check the battery of device whether fully charged or not
* @apicovered		device_battery_is_charging
* @passcase			When device_battery_is_charging is successful
* @failcase			If target API device_battery_is_charging any precondition API fails
* @precondition		USB should be connected to target device.
* @postcondition	NA
*/
int ITc_device_battery_is_charging_p(void)
{
	START_TEST;

	bool bCharging =false;
	device_battery_status_e status;

	// Target API
	int nRet = device_battery_is_charging(&bCharging);
	if(!bIsBatteryFeatureSupported)
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
	/* If there is no battery on the target during the auto tests,
	 * status is "Not Charging", and apis can be operated improperly.
	 * Thus battery apis need to be handled as no error state in the case. */
	if (device_battery_get_status(&status) == DEVICE_ERROR_NONE &&
		status == DEVICE_BATTERY_STATUS_NOT_CHARGING) {
		FPRINTF("[Line : %d][%s]  Not Charging", __LINE__, API_NAMESPACE);
		return 0;
	}

	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_battery_is_charging", DeviceGetError(nRet));

	if (bCharging){
		FPRINTF("[Line : %d][%s]  Battery is charging", __LINE__, API_NAMESPACE);
	}
	else {
		FPRINTF("[Line : %d][%s]  Battery is discharging", __LINE__, API_NAMESPACE);
	}

	return 0;
}

//& purpose: To get the battery level status. 
//& type: auto
/**
* @testcase 		ITc_device_battery_get_level_status_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		To get the battery level status. 
* @scenario			Plug the device for getting charged
* @apicovered		device_battery_get_level_status
* @passcase			When device_battery_get_level_status is successful
* @failcase			If target API device_battery_get_level_status any precondition API fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_battery_get_level_status_p(void)
{
	START_TEST;

	device_battery_level_e eDeviceBatteryLevel;

	// Target API
	int nRet = device_battery_get_level_status(&eDeviceBatteryLevel);
	if(!bIsBatteryFeatureSupported)
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
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_battery_get_level_status", DeviceGetError(nRet));

	if ( eDeviceBatteryLevel == DEVICE_BATTERY_LEVEL_EMPTY )
	{
		FPRINTF("[Line : %d][%s] device_battery_get_level_status failed with battery level empty\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}


//& purpose: To get the battery health information.
//& type: auto
/**
* @testcase 		ITc_device_battery_get_health_p
* @since_tizen		3.0
* @author           SRID(arvin.mittal)
* @reviewer         SRID(a.pandia1)
* @type 			auto
* @description		To get the battery health information.
* @scenario			Gets the battery health information.
* @apicovered		device_battery_get_health
* @passcase			When device_battery_get_health is successful
* @failcase			If target API device_battery_get_health fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_battery_get_health_p(void)
{
	START_TEST;

	device_battery_health_e eDeviceBatteryHealth = -1;
	device_battery_status_e status;

	// Target API
	int nRet = device_battery_get_health(&eDeviceBatteryHealth);
	if(!bIsBatteryFeatureSupported)
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


	/* If there is no battery on the target during the auto tests,
	 * status is "Not Charging", and apis can be operated improperly.
	 * Thus battery apis need to be handled as no error state in the case. */
	if (device_battery_get_status(&status) == DEVICE_ERROR_NONE &&
		status == DEVICE_BATTERY_STATUS_NOT_CHARGING) {
		nRet = DEVICE_ERROR_NONE;
		eDeviceBatteryHealth = DEVICE_BATTERY_HEALTH_DEAD;
	}

	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_battery_get_health", DeviceGetError(nRet));

	if (  eDeviceBatteryHealth < DEVICE_BATTERY_HEALTH_GOOD || eDeviceBatteryHealth > DEVICE_BATTERY_HEALTH_OVER_VOLTAGE)
	{
		FPRINTF("[Line : %d][%s] device_battery_get_health failed with invalid value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: To get the battery power source information.
//& type: auto
/**
* @testcase 		ITc_device_battery_get_power_source_p
* @since_tizen		3.0
* @author           SRID(arvin.mittal)
* @reviewer         SRID(a.pandia1)
* @type 			auto
* @description		To get the battery power source information.
* @scenario			Gets the battery power source information.
* @apicovered		device_battery_get_power_source
* @passcase			When device_battery_get_power_source is successful
* @failcase			If target API device_battery_get_power_source fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_battery_get_power_source_p(void)
{
	START_TEST;

	device_battery_power_source_e eDeviceBatteryPowerSource = -1;

	// Target API
	int nRet = device_battery_get_power_source(&eDeviceBatteryPowerSource);
	if(!bIsBatteryFeatureSupported)
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

	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_battery_get_power_source", DeviceGetError(nRet));

	//If device is connected via USB then DEVICE_BATTERY_POWER_SOURCE_USB is used, otherwise it needs to be changed.
	if ( eDeviceBatteryPowerSource < DEVICE_BATTERY_POWER_SOURCE_NONE || eDeviceBatteryPowerSource > DEVICE_BATTERY_POWER_SOURCE_WIRELESS)
	{
		FPRINTF("[Line : %d][%s] device_battery_get_power_source failed with wrong value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: To get the battery properties.
//& type: auto
/**
* @testcase 		ITc_device_battery_get_property_p
* @since_tizen		3.0
* @author           SRID(arvin.mittal)
* @reviewer         SRID(a.pandia1)
* @type 			auto
* @description		To get the battery properties.
* @scenario			Gets the battery properties.
* @apicovered		device_battery_get_property
* @passcase			When device_battery_get_property is successful
* @failcase			If target API device_battery_get_property fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_battery_get_property_p(void)
{
	START_TEST;

	device_battery_status_e eDeviceBatteryStatus = -1;
	device_battery_property_e eDeviceBatteryProperty[] = {DEVICE_BATTERY_PROPERTY_CAPACITY, DEVICE_BATTERY_PROPERTY_CURRENT_NOW, DEVICE_BATTERY_PROPERTY_CURRENT_AVERAGE, DEVICE_BATTERY_PROPERTY_VOLTAGE_NOW, DEVICE_BATTERY_PROPERTY_VOLTAGE_AVERAGE, DEVICE_BATTERY_PROPERTY_TEMPERATURE};
	int nDeviceBatteryPropertyArraySize = sizeof(eDeviceBatteryProperty) / sizeof(eDeviceBatteryProperty[0]);
	int nValue;
	int nRet, nLoopCount;

	// Target API
	for(nLoopCount = 0; nLoopCount < nDeviceBatteryPropertyArraySize; nLoopCount++)
	{
		nValue = -1;
		nRet = device_battery_get_property(eDeviceBatteryProperty[nLoopCount], &nValue);
		if(!bIsBatteryFeatureSupported)
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

		PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_battery_get_property", DeviceGetError(nRet));

		device_battery_get_status(&eDeviceBatteryStatus);
		PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_battery_get_status", DeviceGetError(nRet));
	}

	return 0;
}

//& purpose: To get the battery power source information.
//& type: auto
/**
* @testcase 		ITc_device_battery_get_status_p
* @since_tizen		3.0
* @author           SRID(arvin.mittal)
* @reviewer         SRID(a.pandia1)
* @type 			auto
* @description		To get the battery power source information.
* @scenario			Gets the battery power source information.
* @apicovered		device_battery_get_status
* @passcase			When device_battery_get_status is successful
* @failcase			If target API device_battery_get_status fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_battery_get_status_p(void)
{
	START_TEST;

	device_battery_status_e eDeviceBatteryStatus = -1;

	// Target API
	int nRet = device_battery_get_status(&eDeviceBatteryStatus);
	if(!bIsBatteryFeatureSupported)
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

	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_battery_get_status", DeviceGetError(nRet));

	if (  eDeviceBatteryStatus < DEVICE_BATTERY_STATUS_CHARGING || eDeviceBatteryStatus > DEVICE_BATTERY_STATUS_NOT_CHARGING)
	{
		FPRINTF("[Line : %d][%s] device_battery_get_status failed with wrong value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

/** @} */
/** @} */
