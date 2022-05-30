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
#include "CTs-system-info-common.h"

/** @addtogroup ctc-system-info
* @ingroup		ctc
* @{
*/

//& set: SystemInfo

/**
* @function 		CTs_system_info_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_system_info_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_System_Info_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_system_info_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_system_info_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_System_Info_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& purpose: Device screen BPP(Bit per pixels) get test 
//& type: auto
/**
* @testcase			CTc_SystemInfo_DisplayBPP_p
* @since_tizen		2.3
* @author			 SRID(parshant.v)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @scenario			Gets the Device Screen BPP(Bit per pixels)\n
*					Checks the BPP values with standard Screen BPP
* @apicovered		system_info_get_platform_int
* @passcase			If covered API is success and gives valid output value.
* @failcase			If covered API is not success or gives invalid output value.
* @precondition		NA
* @postcondition	NA
*/
int CTc_SystemInfo_DisplayBPP_p(void)
{
	START_TEST;

	int nScreenBPP = 0;
	int nRet = system_info_get_platform_int(SCREEN_BPP_FEATURE, &nScreenBPP);
	PRINT_RESULT(SYSTEM_INFO_ERROR_NONE, nRet, "system_info_get_platform_int", SystemInfoGetErrorCode(nRet));
	FPRINTF("[Line : %d][%s] Screen BPP : %d\\n", __LINE__, API_NAMESPACE, nScreenBPP);

	return 0;
}


//& purpose: A purpose of checking if support USB host
//&type: auto
/**
* @testcase			CTc_SystemInfo_IsSupportedUsbHost_p
* @since_tizen		2.3
* @author			 SRID(parshant.v)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @scenario			Checks the device if supports USB host
* @apicovered		system_info_get_platform_bool
* @passcase			Covered API return zero success value
* @failcase			Covered API returns negative error value 
* @precondition		NA
* @postcondition	NA
*/
int CTc_SystemInfo_IsSupportedUsbHost_p(void)
{
	START_TEST;

	bool bIsSupportedUsbHost = false;
	int nRet = system_info_get_platform_bool(USB_HOST_FEATURE, &bIsSupportedUsbHost);	
	PRINT_RESULT(SYSTEM_INFO_ERROR_NONE, nRet, "system_info_get_platform_bool", SystemInfoGetErrorCode(nRet));
	
	if ( !bIsSupportedUsbHost )
	{
		FPRINTF("[Line : %d][%s] Device doesn't Support USB host\\n", __LINE__, API_NAMESPACE);
	}
	return 0;
}

//& purpose: A purpose of checking if support USB accessory
//&type: auto
/**
* @testcase			CTc_SystemInfo_IsSupportedUsbAccessory_p
* @since_tizen		2.3
* @author			 SRID(parshant.v)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @scenario			Checks the device if supports USB Accessory
* @apicovered		system_info_get_platform_bool
* @passcase			covered API return zero success value
* @failcase			covered API returns negative error value 
* @precondition		NA
* @postcondition	NA
*/
int CTc_SystemInfo_IsSupportedUsbAccessory_p(void)
{
	START_TEST;

	bool bIsSupportedUsbAccessory = false;
	int nRet = system_info_get_platform_bool(USB_ACCESSORY_FEATURE, &bIsSupportedUsbAccessory);	
	PRINT_RESULT(SYSTEM_INFO_ERROR_NONE, nRet, "system_info_get_platform_bool", SystemInfoGetErrorCode(nRet));
	
	if ( !bIsSupportedUsbAccessory )
	{
		FPRINTF("[Line : %d][%s] Device doesn't Support USB Accessory\\n", __LINE__, API_NAMESPACE);
	}
	return 0;
}

/** @} */ //end of ctc-system-info
/** @} */ //end of ctc-system-info-testcases
