//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#include <device/temperature.h>
#include "ITs-device-common.h"

bool g_bIsThermalAPFeatureSupported;
bool g_bIsThermalCPFeatureSupported;
bool g_bIsThermalBATTERYFeatureSupported;

/** @addtogroup itc-device
*  @ingroup itc
*  @{
*/


//& set: Device

/**
* @function 		ITs_device_thermal_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_thermal_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsThermalAPFeatureSupported = TCTCheckSystemInfoFeatureSupported(THERMAL_AP_FEATURE, API_NAMESPACE);
	g_bIsThermalCPFeatureSupported = TCTCheckSystemInfoFeatureSupported(THERMAL_CP_FEATURE, API_NAMESPACE);
	g_bIsThermalBATTERYFeatureSupported = TCTCheckSystemInfoFeatureSupported(THERMAL_BATTERY_FEATURE, API_NAMESPACE);

	return;
}

/**
* @function 		ITs_device_thermal_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_thermal_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}


/** @addtogroup itc-device-thermal
*  @brief 		Integration testcases for module device-thermal
*  @ingroup 	itc-device-thermal
*  @{
*/

//& purpose: Gets the temperature value.
//& type: auto
/**
* @testcase 		ITc_device_thermal_get_temperature_p
* @since_tizen		5.5
* @author           SRID(priya.kohli)
* @reviewer         SRID(manoj.g2)
* @type 			auto
* @description		Gets the temperature value.
* @scenario			Gets the temperature value in degrees Celsius.
* @apicovered		device_thermal_get_temperature
* @passcase			If target api device_thermal_get_temperature returns 0.
* @failcase			If target api device_thermal_get_temperature fails.
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_thermal_get_temperature_p(void)
{
	START_TEST;

	int nRet = -1;
	int nThermalType;

	device_thermal_e eDeviceThermalType[] = {DEVICE_THERMAL_AP,
											DEVICE_THERMAL_CP,
											DEVICE_THERMAL_BATTERY};

	int nEnumCounter = 0;
	int nEnumSize = sizeof(eDeviceThermalType) / sizeof(eDeviceThermalType[0]);

	for (nEnumCounter=0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		int nValue;
		nThermalType = eDeviceThermalType[nEnumCounter];
		nRet = device_thermal_get_temperature(nThermalType, &nValue);
		if ( (!g_bIsThermalAPFeatureSupported && nThermalType == DEVICE_THERMAL_AP) || (!g_bIsThermalCPFeatureSupported && nThermalType == DEVICE_THERMAL_CP) || (!g_bIsThermalBATTERYFeatureSupported && nThermalType == DEVICE_THERMAL_BATTERY) )
		{
			PRINT_RESULT(DEVICE_ERROR_NOT_SUPPORTED, nRet, "device_thermal_get_temperature", "Feature Mismatch");
			continue;
		}
		PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_thermal_get_temperature", DeviceGetError(nRet));
		if(nValue < 0)
		{
			FPRINTF("[Line : %d][%s] device_thermal_get_temperature returns negative nValue value = %d\\n", __LINE__, API_NAMESPACE,  nValue);
			return 1;
		}
	}

	return 0;
}

/** @} */
/** @} */
