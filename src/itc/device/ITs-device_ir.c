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

bool bIsIRFeatureSupported ;

/**
* @function 		ITs_device_battery_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_ir_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Device_p\\n", __LINE__, API_NAMESPACE);
#endif

	bIsIRFeatureSupported = false;
	IS_FEATURE_SUPPORTED(IR_FEATURE, bIsIRFeatureSupported, API_NAMESPACE);
	return;
}

/**
* @function 		ITs_device_battery_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_device_ir_cleanup(void)
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

//& purpose: To gets the information whether IR module is available.
//& type: auto
/**
* @testcase 			ITc_device_ir_is_available_p
* @since_tizen		3.0
* @author          	SRID(nibha.sharma)
* @reviewer       	SRID(a.pandia1)
* @type 				auto
* @description		To gets the information whether IR module is available.
* @scenario			 gets the information whether IR module is available
* @apicovered		device_ir_is_available				
* @passcase			When device_ir_is_available is successful
* @failcase			If target API device_ir_is_available fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_ir_is_available_p(void)
{
	START_TEST;
	
	bool  bAvailable;
	
	// Target API
	int nRet = device_ir_is_available(&bAvailable);
	if ( !bIsIRFeatureSupported )
	{
		if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
		{
				FPRINTF("[Line : %d][%s] device_ir_is_available return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature,\\n", __LINE__, API_NAMESPACE);
				return 0;
		}
		FPRINTF("[Line : %d][%s] device_ir_is_available failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s\\n", __LINE__, API_NAMESPACE, DeviceGetError(nRet));
		return 1;
	}
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_ir_is_available", DeviceGetError(nRet));

	return 0;
}

//& purpose: Transmits IR command.
//& type: auto
/**
* @testcase 			ITc_device_ir_transmit_p
* @since_tizen		3.0
* @author          	SRID(nibha.sharma)
* @reviewer       	SRID(a.pandia1)
* @type 				auto
* @description		Transmits IR command.
* @scenario			Transmits IR command.
* @apicovered		device_ir_transmit				
* @passcase			When device_ir_transmit is successful
* @failcase			If target API device_ir_transmit fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_device_ir_transmit_p(void)
{
	START_TEST;
	
	int nCarrierFreq = 1000;
	int nPattern[2]={0,1};
	int nSize = 2;

	// Target API
	int nRet = device_ir_transmit(nCarrierFreq,nPattern,nSize);
	if ( !bIsIRFeatureSupported )
	{
		if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
		{
				FPRINTF("[Line : %d][%s] device_ir_transmit return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature,\\n", __LINE__, API_NAMESPACE);
				return 0;
		}
		FPRINTF("[Line : %d][%s] device_ir_transmit failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s\\n", __LINE__, API_NAMESPACE, DeviceGetError(nRet));
		return 1;
	}
	PRINT_RESULT(DEVICE_ERROR_NONE, nRet, "device_ir_transmit", DeviceGetError(nRet));

	return 0;
}

/** @} */
/** @} */
