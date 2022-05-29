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
#include "CTs-location-manager-common.h"

/** @addtogroup ctc-location-manager
* @ingroup		ctc
* @{
*/

//& set: LocationManager

/**
* @function 		CTs_location_manager_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_location_manager_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Location_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_location_manager_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_location_manager_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Location_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	ctc-location-manager-testcases
* @brief 		Integration testcases for module location-manager
* @ingroup		ctc-location-manager
* @{
*/

//& purpose: Checks whether the GPS is supported or not
//& type: auto
/**
* @testcase			CTc_LocationManager_IsSupportedGps_p
* @since_tizen		2.3
* @author           SRID(sameer.g1)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @scenario			Checks if gps is supported or not
* @apicovered		system_info_get_platform_bool
* @passcase			covered api should return zero success value 
* @failcase			covered api returns negative error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_LocationManager_IsSupportedGps_p(void)
{
	START_TEST;
	
	bool bIsGpsSupported = false;
	IS_FEATURE_SUPPORTED(GPS_FEATURE, bIsGpsSupported, API_NAMESPACE);
	
	if ( !bIsGpsSupported )
	{
		FPRINTF("[Line : %d][%s] GPS feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	
	FPRINTF("[Line : %d][%s] GPS feature is supported\\n", __LINE__, API_NAMESPACE);
	
	//Check API support
	location_manager_h stManager = {0};
	int nRet = location_manager_create(LOCATIONS_METHOD_GPS, &stManager);
	if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
	{
		FPRINTF("[Line : %d][%s] location_manager_create returned TIZEN_ERROR_NOT_SUPPORTED while GPS feature is supported\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( nRet == LOCATIONS_ERROR_NONE )
	{
		 location_manager_destroy(stManager);
	}
	return 0;
}

/** @} */ //end of ctc-location-manager
/** @} */ //end of ctc-location-manager-testcases